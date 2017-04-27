//
//  DllFrame.cpp
//  BeskedNummer
//
//  Created by Katrine Maria Nielsen on 11/11/15.
//  Copyright © 2015 Katrine Maria Nielsen. All rights reserved.
//
#include "DllFrame.hpp"

DllFrame::DllFrame()
{
    
}

void DllFrame::isMessage(vector<unsigned char> &Data)
{
    Data.insert(Data.begin(), 64);
}
void DllFrame::isAcknowledge(vector<unsigned char> &Data)
{
    Data.insert(Data.begin(), 128);
}

void DllFrame::isSystem(vector<unsigned char> &Data)
{
     Data.insert(Data.begin(), 192);
}


void DllFrame::addFrameNumber(vector<unsigned char> &Data)
{
    bitset<8> tal;

	if (frameNum == 3)
		frameNum = 0;
		
		frameNum++;
      for (int i = 0; i < 8; ++i)
      {
          tal[i] = ((frameNum >> i) & 1);
      }
		
	 
	  tal = tal << 4;
    
	  Data.insert(Data.begin(), (unsigned char)tal.to_ullong());
	 
	  cout << "framenummer: " << (int)frameNum << endl;
}

void DllFrame::decrFrameNum()
{
	frameNum--;
}

void DllFrame::addDataSize(vector<unsigned char> &Data)
{
	cout << "datasize " << Data.size() << endl;
    Data.insert(Data.begin(), (Data.size()-2));
}

void DllFrame::makeByte(vector<unsigned char> &Data)
{
    unsigned char newByte = Data[0]+Data[1]+Data[2];
    for (int i = 0; i < 3; i++)
    {
        Data.erase(Data.begin());
    }
    
    Data.insert(Data.begin(), newByte);

}


int DllFrame::checkFrameNumber(vector<unsigned char> &Data)
{
    bitset<8>(tal);
    for (int i = 0; i < 8; ++i)
    {
        tal[i] = ((Data[0] >> i) & 1);
    }
    bitset<2> fNum;
    fNum[1] = tal[5];
    fNum[0] = tal[4];
    unsigned long check = fNum.to_ulong();
	return check;
}

int DllFrame::checkDataSize(vector<unsigned char> &Data)
{
    bitset<8>(tal);
    for (int i = 0; i < 8; ++i)
    {
        tal[i] = ((Data[0] >> i) & 1);
    }
    bitset<4> dSize;
    
    dSize[3] = tal[3];
    dSize[2] = tal[2];
    dSize[1] = tal[1];
    dSize[0] = tal[0];
    unsigned long check = dSize.to_ulong();
	return check;
}

int DllFrame::checkTypeNum(vector<unsigned char> &Data)
{
	bitset<8>(tal);
	for (int i = 0; i < 8; ++i)
	{
		tal[i] = ((Data[0] >> i) & 1);
	}
	bitset<2> typeNum;
	typeNum[1] = tal[7];
	typeNum[0] = tal[6];
	unsigned long check = typeNum.to_ulong();
	return check;
}

DllFrame::~DllFrame()
{
    
}
