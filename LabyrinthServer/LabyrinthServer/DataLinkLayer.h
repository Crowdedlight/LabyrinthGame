#pragma once

#define _FrameType data[0]
#define _FrameNumber  data[2]
#define _FrameData data[1]
#define _ACKpiggy data[4]

#include <string>
#include <vector>
#include <iostream>
#include <mutex>

#include "DllFrame.hpp"
#include "Game_State.h"
#include "CRC.hpp"

class PhysicalLayer;

using namespace std;

class DataLinkLayer
{
public:
	DataLinkLayer();
	char getFrameNum();
	void waitDLL();
	void sendDatatoPsy();
	void sendDataToApp();
	void messageACK();
	void setPtr(Tiny_State *alptr,PhysicalLayer &ptr, DataLinkLayer &ptrDLL, mutex &mut);
	bool receiveData(vector<unsigned char> vecc, int dir);
	~DataLinkLayer(void);
protected:

	mutex *mutPtr;
	Tiny_State *ptrAL;
	PhysicalLayer *ptrPL;
	DataLinkLayer *ptrDLL;
	vector<unsigned char> data;
	vector<unsigned char> datatemp;
	static unsigned char latestFrameSent;
	bool dataReceived;
	bool ackReceived;
	int dataDirection;
	int numberOfResend;
	int dataType;
	
};

