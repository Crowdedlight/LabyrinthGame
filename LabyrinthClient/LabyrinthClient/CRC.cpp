//
//  CRC.cpp
//  CRC
//
//  Created by Katrine Maria Nielsen on 27/10/15.
//  Copyright © 2015 Katrine Maria Nielsen. All rights reserved.
//
#include "CRC.hpp"

Crc::Crc(){}


void Crc::createLookUp()
{
    genPol = 29;
    lookUpTable = new unsigned char[256];
    int i=0;

    for (int divident = 0; divident < 255; divident++)
    {
        unsigned char currByte = (unsigned char)divident;
        for (unsigned char bit = 0; bit < 8; bit++)
        {
            if ((currByte & 128) != 0)
            {
                currByte <<= 1;
                currByte ^= genPol;
            }
            else
            {
                currByte <<= 1;
            }
        }
        lookUpTable[divident] = currByte;
        i++;
    }
}

void Crc::addCrc(vector<unsigned char> &Data)
{
    createLookUp();
    unsigned char crc8 = 0;
    for(int i=0; i<Data.size(); i++)
        {
            unsigned char data = (unsigned char)(Data[i] ^ crc8);
            crc8 = (int)(lookUpTable[data]);
        }
    Data.push_back((int)crc8);
}

bool Crc::checkCrc(vector<unsigned char> &Data)
{
    createLookUp();
    unsigned char crc8 = 0;
    for(int i=0; i<Data.size(); i++)
    {
        unsigned char data = (unsigned char)(Data[i] ^ crc8);
        crc8 = (int)(lookUpTable[data]);
    }
    if (crc8 == 0)
	{
		return true;
	}
       
    return false;
}

Crc::~Crc(){}