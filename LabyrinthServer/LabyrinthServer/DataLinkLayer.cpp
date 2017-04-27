#include "DataLinkLayer.h"
#include "PhysicalLayer.h"


DataLinkLayer::DataLinkLayer(){}

void DataLinkLayer::setPtr(Tiny_State *alPtr,PhysicalLayer &ptr, DataLinkLayer &ptrD, mutex &mu)
{
	mutPtr = &mu;
	ptrPL = &ptr;
	ptrDLL = &ptrD;
	ptrAL = alPtr;
}


void DataLinkLayer::waitDLL()
{
	while (true)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(10));

		if (dataReceived)
		{
			switch (dataDirection)
			{
			case 1: // From physical layer
				sendDataToApp();
				dataReceived = false;
				break;
			case 2:// From applications layer
				sendDatatoPsy();
				dataReceived = false;
				break;

			case 207: // ACK received
				ackReceived = true;
				dataReceived = false;
				break;


			default:
				cout << "forkert type" << endl;
				dataReceived = false;
				break;
			}
		}
	}
}

bool DataLinkLayer::receiveData(vector<unsigned char> vecc, int dir)
{
	for (auto i : vecc)
		cout << i << ",";
	if (dataReceived)
		return false;
	dataDirection = dir;
	data = vecc;
	datatemp = vecc;
    dataReceived = true;
	return true;
}

char DataLinkLayer::getFrameNum()
{
	
	return 'a';
}

void DataLinkLayer::sendDatatoPsy()
{
	/// Received data for Application layer

	//cout << "Received this vector data in DLL from Application Layer:" << endl;
	//for (int i = 0; i < (signed)data.size(); i++)
	//{
	//	cout << (int)data[i] << " ";
	//}
	//cout << endl << endl;


	/// put on header : Framenumber
		
	DllFrame dllframe;
	dllframe.addFrameNumber(data);

	/// put on header : datatype

	dllframe.isMessage(data);

	/// add datasize

	dllframe.addDataSize(data);

	/// convert to one byte

	dllframe.makeByte(data);
	/// create CRC check
	Crc crc;
	crc.addCrc(data);

	/// send data to physical layer
	while (ptrPL->fromDLLtoPL(data) == false)
		sf::sleep(sf::milliseconds(30));

	/*wait for ACK*/
	for (size_t i = 0; i < 50; i++)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(100)); // wait and check for ACK
		if (ptrDLL->ackReceived)
			break;
	}


	if (!ptrDLL->ackReceived && numberOfResend != 2)
	{
		
		cout << "No ACK was received - trying to send again" << endl;
		data = datatemp;
		dllframe.decrFrameNum();
		cout << "number of resend: " << numberOfResend << endl;
		numberOfResend++;
		sendDatatoPsy();
	}
	if (!ptrDLL->ackReceived && numberOfResend == 2)
	{
		cout << "Sending of data failed - too many attempts" << endl;
		numberOfResend = 0;
	}

	ptrDLL->ackReceived = false;
}

void DataLinkLayer::sendDataToApp()
{
	/// Received data for Physical layer
	//std::this_thread::sleep_for(std::chrono::milliseconds(100));
	/*cout << "Received this vector data in DLL from Physical Layer:" << endl;
	for (int i = 0; i < (signed)data.size(); i++)
	{
		cout << (int)data[i] << " ";
	}
	cout << endl << endl;*/

	/// make CRC check
	for (auto i : data)
		cout << i << ",";
	Crc crc;

	DllFrame dllcheck;

	if(dllcheck.checkTypeNum(data) == 1)
	{
		if (true)//crc.checkCrc(data))
		{
			
			if (latestFrameSent == dllcheck.checkFrameNumber(data)) /// Same frame as last time, just send ACK
			{
				cout << "Frame was already received - destroying this object, and waiting for new" << endl;
				messageACK();
			}


			if (latestFrameSent != dllcheck.checkFrameNumber(data)) /// A new frame, send to AL and check for true/false
			{
				/// send data to applications layer
				
				vector<unsigned char>datatemp = data;
				datatemp.pop_back();
				datatemp.erase(datatemp.begin(), datatemp.begin() + 1);
				

				//unsigned char move;
				messageACK();
				ptrAL->requestRecieved(datatemp);
				cout << endl;
				latestFrameSent = dllcheck.checkFrameNumber(data);
			}
		}
	}
	if (data[0] == 2)
	{
		ackReceived = true;
	}
}
void DataLinkLayer::messageACK()
{
	cout << "Sending ACK" << endl;
	vector<unsigned char> ACK = { unsigned char(2),'A','C','K'};
	ptrPL->fromDLLtoPL(ACK);
}

DataLinkLayer::~DataLinkLayer(void)
{
	cout << "DLL destructor is called\n------------------------" << endl << endl;
}


