//
//  CRC.hpp
//  CRC
//
//  Created by Katrine Maria Nielsen on 27/10/15.
//  Copyright © 2015 Katrine Maria Nielsen. All rights reserved.
//

#ifndef CRC_hpp
#define CRC_hpp

#include <stdio.h>
#include <iostream>
#include <vector>
#include <bitset>
#include <math.h>
#include <stdint.h>

using namespace std;

class Crc
{
public:
    Crc();
    void createLookUp();
    void addCrc(vector<unsigned char> &data);
    bool checkCrc(vector<unsigned char> &data);
    ~Crc();
protected:
    int divisor;
    int dataword;
    int crc;
    unsigned char* lookUpTable;
    unsigned char genPol;
};
#endif 
/* CRC_hpp */
