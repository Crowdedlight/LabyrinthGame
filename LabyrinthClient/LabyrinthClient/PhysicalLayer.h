#pragma once
#include "Random_Maze.h"
#include "DTMFSoundRecorder.h"
#include "ToneArray.h"
#include "LineCode.h"
#include "DataLinkLayer.h"
#include <iostream>

class PhysicalLayer
{
public:
	PhysicalLayer();
	~PhysicalLayer();

	bool setDLL(DataLinkLayer *aDLL);		// Set pointer to a DLL to push data to
	bool activate();						// Activate Physical Layer
	bool fromDLLtoPL(std::vector<unsigned char> data);	// Push data from Data Link Layer to Physical Layer
	void kill();							// Tell activate to terminate

protected:
	sf::DTMFSoundRecorder recorder;			// Object to handle recording
	LineCode lc;							// Object to handle linecoding and -decoding
	ToneArray player;						// Object to handle playback
	DataLinkLayer *linked_DLL;				// Pointer to Data Link Layer
	bool recievedFromDLLStatus = false;		// Indicate if message recieved fro DLL
	std::vector<unsigned char> dataSendBuffer;	
	bool killStatus = false;				// Indicate if activate should terminate
};

