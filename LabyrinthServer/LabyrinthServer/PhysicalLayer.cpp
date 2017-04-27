#include "PhysicalLayer.h"


PhysicalLayer::PhysicalLayer()
{
}

PhysicalLayer::~PhysicalLayer()
{
}

bool PhysicalLayer::setDLL(DataLinkLayer *aDLL)
{
	try
	{
		linked_DLL = aDLL;
	}
	catch (const std::exception&)
	{
		return false;
	}
	return true;
}

bool PhysicalLayer::activate()
{
	if (!recorder.start())
	{
		cerr << "Error starting recorder" << endl;
		return false;
	}

	while (!killStatus)
	{
		// Check if a new message has been recieved
		if (recorder.getRecieveCompleteStatus())
		{
			std::vector<int> messageIntBuffer = recorder.getMessage(); // Copy message from recorder
			recorder.setRecieveCompleteStatus(false);	// Set recieveComplete to false (ready for new message)
			std::vector<unsigned char> messageCharBuffer = lc.DTMFtoChar(messageIntBuffer); // LineDecode the data

			// Keep trying to send to DLL
			while (linked_DLL->receiveData(messageCharBuffer, 1) == false)
				sf::sleep(sf::milliseconds(100));
		}

		// Check if message should be sent
		if (recievedFromDLLStatus)
		{
			// LineDecode message
			std::vector<int> sendBuffer = lc.charToDTMF(dataSendBuffer);

			// Check if recorder is currently recieving a message
			while (recorder.getRecieveStatus())
				sf::sleep(sf::milliseconds(50));

			// Stop recorder
			//recorder.stop();
			recorder.setStatus(false);
			// Play message
			player.playBuffer(sendBuffer);
			sf::sleep(sf::milliseconds(sendBuffer.size() * 25));

			// Start recorder
			//recorder.start();
			recorder.setStatus(true);

			// Set recievedFromDLLStatus to false (ready to send new message)
			recievedFromDLLStatus = false;
		}
	}

	return false;
}

bool PhysicalLayer::fromDLLtoPL(std::vector<unsigned char> data)
{
	// If old message not processed return false
	if (recievedFromDLLStatus)
		return false;

	// Copy data
	dataSendBuffer = data;
	recievedFromDLLStatus = true;
	return true;
}

void PhysicalLayer::kill()
{
	killStatus = true;
}
