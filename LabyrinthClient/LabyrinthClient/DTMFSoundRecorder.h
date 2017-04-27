#pragma once
#include <SFML/Audio/SoundRecorder.hpp>
#include <vector>
#include <algorithm>		// std::copy()
#include <iterator>			// std::back_inserter()
#include <iostream>
#include "SoundProcessor.h"
#include "Goertzel.h"

#define DTMF_tone_length 200		// Length of the tone in samples
#define DTMF_analyze_length 150		// Amount of samples to be analyzed

namespace sf
{
	class DTMFSoundRecorder : public SoundRecorder
	{
	public:
		DTMFSoundRecorder();
		bool start();
		bool getStatus();
		bool setStatus(bool stat);
		bool getRecieveStatus();
		bool getRecieveCompleteStatus();
		void setRecieveCompleteStatus(bool status);
		std::vector<int> getMessage();
	protected:
		virtual bool onStart();
		virtual bool onProcessSamples(const Int16* samples, std::size_t sampleCount);
		virtual void onStop();
	private:
		std::vector<Int16> data;		// Temporary sample buffer to hold the recorded data
		std::vector<int> recieveBuffer;	// Temporary vector to hold data while recieving
		bool recieveComplete = false;	// Has a full frame been recieved
		bool recStatus = false;			// Is the recorder recording
		int startFlagStatus = 0;		// 0 = not recieving, 1 = first startflagbit recieved, 2 = second startflagbit recieved, 3 third startflagbit recieved (recieving message)
		int endFlagStatus = 0;			// 0 = no enflagbits recieved, 1 = first endflagbit recieved, 2 = second endflagbit recieved
		unsigned int sampleIndex = 0;	// Temporary index to indicate how many samples have been analyzed
		SoundProcessor processor;
		Goertzel goertzel;
	};
}