#include "PhysicalLayer.h"

////////////////////////////////////////////////////////////
/*
Constructor.
*/
PhysicalLayer::PhysicalLayer()
{
}
////////////////////////////////////////////////////////////
/*
Destructor.
*/
PhysicalLayer::~PhysicalLayer()
{
}
////////////////////////////////////////////////////////////
/*
This method sets a pointer to a DataLinkLayer object. This
enables this object to use methods on the DLL object.
*/
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
////////////////////////////////////////////////////////////
/*
This method should be executed in its own thread. It controls
the all functionality of the Physical Layer.
*/
bool PhysicalLayer::activate()
{
	// Start the recorder
	if (!recorder.start())
	{
		cerr << "Error starting recorder" << endl;
		return false;
	}

	while (!killStatus)	// If kill method has been called from other thread, the loop will break and the thread terminate
	{
		// Check if a new message has been recieved
		if (recorder.getRecieveCompleteStatus())
		{
			std::vector<int> messageIntBuffer = recorder.getMessage(); // Copy message from recorder
			recorder.setRecieveCompleteStatus(false);	// Set recieveComplete to false (ready for new message)
			std::vector<unsigned char> messageCharBuffer = lc.DTMFtoChar(messageIntBuffer); // LineDecode the data

			// Keep trying to send to DLL
			while (linked_DLL->receiveData(messageCharBuffer,1) == false)
			{
				sf::sleep(sf::milliseconds(100));
			}
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
			sf::sleep(sf::milliseconds(sendBuffer.size() * 25 + 50));

			// Start recorder
			//recorder.start();
			recorder.setStatus(true);

			// Set recievedFromDLLStatus to false (ready to send new message)
			recievedFromDLLStatus = false;
		}
	}

	return false;
}
////////////////////////////////////////////////////////////
/*
This method can be called from Data Link Layer to push data
to the Physical layer.
*/
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
////////////////////////////////////////////////////////////
/*
This method will tell activate method to terminate.
*/
void PhysicalLayer::kill()
{
	killStatus = true;
}
