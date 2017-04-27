//
//  DllFrame.hpp
//  BeskedNummer
//
//  Created by Katrine Maria Nielsen on 11/11/15.
//  Copyright © 2015 Katrine Maria Nielsen. All rights reserved.
//

#ifndef DllFrame_hpp
#define DllFrame_hpp



#include <bitset> 
#include <stdio.h>
#include <vector>
#include <iostream>
#include <stdlib.h>

using namespace std;

class DllFrame
{
public:
    DllFrame();
    void addFrameNumber(vector<unsigned char> &Data);
    int checkFrameNumber(vector<unsigned char> &Data);
	int checkTypeNum(vector<unsigned char> &Data);
	void decrFrameNum();
    void addDataSize(vector<unsigned char> &Data);
    int checkDataSize(vector<unsigned char> &Data);
    void isMessage(vector<unsigned char> &Data);
    void isAcknowledge(vector<unsigned char> &Data);
    void isSystem(vector<unsigned char> &Data);
    void makeByte(vector<unsigned char> &Data);
    ~DllFrame();
protected:
    vector<unsigned char> data;
    char byte;
    static unsigned char frameNum;
    
};


#endif /* DllFrame_hpp */
