#pragma once
#include "Random_Maze.h"
#include "DTMFSoundRecorder.h"
#include "ToneArray.h"
#include "LineCode.h"
#include <iostream>
#include "DataLinkLayer.h"

class PhysicalLayer
{
public:
	PhysicalLayer();
	~PhysicalLayer();

	bool setDLL(DataLinkLayer *aDLL);
	bool activate();
	bool fromDLLtoPL(std::vector<unsigned char> data);
	void kill();

protected:
	sf::DTMFSoundRecorder recorder;
	LineCode lc;
	ToneArray player;
	DataLinkLayer *linked_DLL;
	bool recievedFromDLLStatus = false;
	std::vector<unsigned char> dataSendBuffer;
	bool killStatus = false;
};

