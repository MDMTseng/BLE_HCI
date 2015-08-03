#include <iostream>
#include "HCI_Base.hpp"
#include <time.h>
#include <stdlib.h>
HCI_Base hci_x;
using namespace std;
using namespace HCI_CMD_OP;

void PrintHexArr(unsigned char*buffer, int bufL) {
	printf("%03d>>", bufL);
	for (int i = 0; i < bufL; i++)
		printf("%02X ", (unsigned char) buffer[i]);
	printf("\n");

}
unsigned char buff[250];
int main() {
	srand(time(NULL));
	HCI_Base::Header_3WireUart header={0};
	header.elements.seqNum=7;
	header.elements.ackNum=7;
	header.elements.payloadL=0xaFF;




	char parameters[] = "sdsdsds";
	parameters[0] = (unsigned int) 0xFF;
	parameters[2] = (unsigned int) 0xC0;
	parameters[3] = (unsigned int) 0xDB;
	parameters[4] = (unsigned int) 0x11;


	printf("Origin Data   \t");
	PrintHexArr((unsigned char*)parameters, sizeof(parameters));


	int PakL = HCI_Base::HCI_CMDPkg_Gen(buff, sizeof(buff),
			Utils::OCFOGF2OP(LINKPOLI_CMD::PARK_MODE, LINKPOLI_CMD::OGF_),
			sizeof(parameters), (unsigned char*)parameters);
	printf("HCI_CMDPkg_Gen\t");
	PrintHexArr(buff, PakL);



	PakL = HCI_Base::HCI_3WUART_PK(
			buff, sizeof(buff),0,0,true,false,HCI_Base::HCI_ACK,buff, PakL);
	printf("HCI_3WUART_PK  \t");
	PrintHexArr(buff, PakL);




	int ENPL=0;
	if (PakL > 0) {
		ENPL = HCI_Base::HCI_SLIP_ENC(buff, sizeof(buff), buff, PakL, false);
		printf("HCI_SLIP_ENC  \t");
		PrintHexArr(buff, ENPL);
	}



	int repeat=30;
	int noiseLevel=5;//0~255
	printf("\n\n simulate RECV SLIP pkg %d times (noise Level:%d) \n\n",repeat,noiseLevel);

	HCI_Base::SLIP_DEC_Info SLIPInfo(250);

	for(int ii=0;ii<repeat;ii++)for(int i=0;i<ENPL;i++)
	{
		unsigned char tmp=rand();
		tmp=(tmp>noiseLevel)?buff[i]:rand();//simulate noise
		//while(uart.getchar(&incomingByte))// should like this
		if(HCI_Base::HCI_SLIP_DEC_ByteFeed(&SLIPInfo,tmp)>0)
		{

			/*printf("HCI_SLIP_DEC  \t");
			PrintHexArr(SLIPInfo.buffer, SLIPInfo.packL);*/


			//buff[10]=0;
			unsigned char *payload;
			int UNPKL= HCI_Base::HCI_3WUART_UNPK(SLIPInfo.buffer, SLIPInfo.packL,&header, &payload) ;
			printf("HCI_3WUART_UNPK\t");
			PrintHexArr(payload, UNPKL);
		}
	}


	return 0;
}
