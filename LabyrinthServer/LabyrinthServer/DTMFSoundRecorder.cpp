#include "DTMFSoundRecorder.h"
#include <fstream>

namespace sf
{
	////////////////////////////////////////////////////////////
	/*
	This constructor sets the amount of samples to be processed
	by the Goertzel algorithm. It also sets the processing interval.
	*/
	DTMFSoundRecorder::DTMFSoundRecorder()
		: goertzel(DTMF_analyze_length)
	{
		setProcessingInterval(sf::milliseconds(100));
	}
	////////////////////////////////////////////////////////////
	/*
	This method starts the recorder with a sampling rate of 8000Hz.
	*/
	bool DTMFSoundRecorder::start()
	{
		if (SoundRecorder::start(8000))
			return true;
		return false;
	}
	////////////////////////////////////////////////////////////
	/*
	This method returns wether or not the recorder is currently
	recording.
	*/
	bool DTMFSoundRecorder::getStatus()
	{
		if (recStatus)
			return true;
		else
			return false;
	}
	bool DTMFSoundRecorder::setStatus(bool stat)
	{
		recStatus = stat;
		return recStatus;
	}
	////////////////////////////////////////////////////////////
	/*
	This method returns true, if the recorder is recieving a message
	*/
	bool DTMFSoundRecorder::getRecieveStatus()
	{
		if (startFlagStatus == 3)
			return true;
		return false;
	}
	////////////////////////////////////////////////////////////
	/*
	This method returns recieveComplete. That is returns true if
	a new message has been recieved and is ready for processing.
	*/
	bool DTMFSoundRecorder::getRecieveCompleteStatus()
	{
		return recieveComplete;
	}
	////////////////////////////////////////////////////////////
	/*
	This method sets recieveComplete.
	*/
	void DTMFSoundRecorder::setRecieveCompleteStatus(bool status)
	{
		recieveComplete = status;
	}
	////////////////////////////////////////////////////////////
	/*
	This method returns the recieved message.
	*/
	std::vector<int> DTMFSoundRecorder::getMessage()
	{
		return recieveBuffer;
	}
	////////////////////////////////////////////////////////////
	/*
	This method executes when start() is called.
	*/
	bool DTMFSoundRecorder::onStart()
	{
		data.clear();
		recStatus = true;
		return true;
	}
	////////////////////////////////////////////////////////////
	/*
	
	*/
	bool DTMFSoundRecorder::onProcessSamples(const Int16* samples, std::size_t sampleCount)
	{
		// Append recorded samples to vector data
		std::copy(samples, samples + sampleCount, std::back_inserter(data));

		if (recStatus == false)
		{
			data.clear();
			return true;
		}
		
		/////////////////////////////////
		// If waiting for 1. startflagbit
		/////////////////////////////////
		if (startFlagStatus == 0)		// If not recieving data run this
		{
			long long int meanSq = processor.meanSquare(data, sampleIndex, 10);		// Compute meanSquare of first 10 samples
			while (meanSq >= 0)				// meanSq is -1 if too few samples are available
			{
				if (meanSq < 40000000)		// If sound level is too low delete the analyzed data, and set sampleIndex to 0
				{
					data.erase(data.begin(), data.begin() + sampleIndex + 9);
					sampleIndex = 0;
					//std::cout << "Mode 1: Too low" << std::endl; // DEBUG
				}
				else						// If sound level is high increase sampleIndex by 10
				{
					sampleIndex += 10;
					//std::cout << "Mode 1: Sufficient level (" << sampleIndex << ")" << std::endl; // DEBUG
				}
				if (sampleIndex == DTMF_tone_length)		// Run Goertzel if sound level has been high for enough samples
				{
					if (goertzel.testFrequency(data, (DTMF_tone_length - DTMF_analyze_length) / 2) == 0)		// If samples are first startflagbit (0) set startFlagStatus to 1
					{
						startFlagStatus = 1;
					//	std::cout << "Mode 1: First startbit detected" << std::endl; // DEBUG
					}
					data.erase(data.begin(), data.begin() + DTMF_tone_length - 1);	// Delete analyze data
					sampleIndex = 0;								// Reset sampleIndex counter
					if (startFlagStatus == 1)
						break;
					//std::cout << "Mode 1: First startbit NOT detected" << std::endl; // DEBUG
				}
				meanSq = processor.meanSquare(data, sampleIndex, 10);
			}
		}

		/////////////////////////////////
		// If waiting for 2. startflagbit
		/////////////////////////////////
		while (startFlagStatus == 1 && data.size() >= DTMF_tone_length)
		{
			int GOutput = goertzel.testFrequency(data, (DTMF_tone_length - DTMF_analyze_length) / 2);
			if ( GOutput == 1)			// If samples are second startflagbit (1) set startFlagStatus to 2 else reset startFlagStatus
			{
				startFlagStatus = 2;
				//std::cout << "Mode 2: Second startflag detected" << std::endl; // DEBUG
			} 
			else if (GOutput == 0)
			{
				//std::cout << "Mode 2: First startflag detected" << std::endl; // DEBUG
			}
			else
			{
				startFlagStatus = 0;
				//std::cout << "Mode 2: Second startflag NOT detected" << std::endl; // DEBUG
			}
			data.erase(data.begin(), data.begin() + DTMF_tone_length - 1);	// Delete analyze data
		}
		
		/////////////////////////////////
		// If waiting for 3. startflagbit
		/////////////////////////////////
		while (startFlagStatus == 2 && data.size() >= DTMF_tone_length)
		{
			// If third startflagbit (2) set startFlagStatus to 3 and endFlagStatus to 0
			if (goertzel.testFrequency(data, (DTMF_tone_length - DTMF_analyze_length) / 2) == 2)
			{
				//std::cout << "Mode 3: Third startflag detected" << std::endl; // DEBUG
				if (recieveComplete)	// If recieveComplete is true previously analyzed message has not ben handled
				{
					//std::cout << "Mode 3: Old message not yet handlet" << std::endl; // DEBUG
					break;				// Break to wait
				}
				startFlagStatus = 3;
				endFlagStatus = 0;
				recieveBuffer.clear();	// Prepare buffer for data
			}
			// Else reset startFlagStatus
			else
			{
				startFlagStatus = 0;
				//std::cout << "Mode 3: Third startflag NOT detected" << std::endl; // DEBUG
			}
			data.erase(data.begin(), data.begin() + DTMF_tone_length - 1);	// Delete analyze data
		}

		/////////////////////////////////
		// If recieving message
		/////////////////////////////////
		while (startFlagStatus == 3 && data.size() >= DTMF_tone_length)	// When enough samples are available
		{
			// Analyze and check tone
			int tone = goertzel.testFrequency(data, (DTMF_tone_length - DTMF_analyze_length) / 2);

			// If no tone detected reset startFlagStatus
			if (tone == -1)
			{
				startFlagStatus = 0;
				//std::cout << "RecieveMode: No tone detected" << std::endl; // DEBUG
			}
			// If possible first endflagbit set endFlagStatus to 1
			else if (tone == 0)
			{
				endFlagStatus = 1;
				recieveBuffer.push_back(tone);
				//std::cout << "RecieveMode 1: First endbit detected" << std::endl; // DEBUG
			}
			// If possible second endflagbit set endFlagStatus to 2
			else if (tone == 1 && endFlagStatus == 1)
			{
				endFlagStatus = 2;
				recieveBuffer.push_back(tone);
				//std::cout << "RecieveMode 2: Second endbit detected" << std::endl; // DEBUG
			}
			// If third endflagbit 
			else if (tone == 2 && endFlagStatus == 2)
			{
				recieveBuffer.pop_back();	// Pop back flagbits
				recieveBuffer.pop_back();
				startFlagStatus = 0;		// Reset startFalgStatus
				//std::cout << "RecieveMode 3: Third endbit detected" << std::endl; // DEBUG
				/*std::cout << "Modtaget: ";
				for (size_t i = 0; i < recieveBuffer.size(); i++)
				{
					std::cout << std::setw(3) << recieveBuffer[i];
				}
				std::cout << std::endl;*/
				recieveComplete = true;
			}
			else
			{
				endFlagStatus = 0;
				recieveBuffer.push_back(tone);
				//std::cout << "RecieveMode: Tone detected = " << tone << std::endl; // DEBUG
			}
			// Delete analyzed data
			data.erase(data.begin(), data.begin() + DTMF_tone_length - 1);
		}
		return true;
	}
	////////////////////////////////////////////////////////////
	/*
	This method runs whenever the soundrecorder is stopped.
	*/
	void DTMFSoundRecorder::onStop()
	{
		recStatus = false;
	}
	////////////////////////////////////////////////////////////
} // namespace sf