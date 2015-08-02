/*
 * HCI_Base.cpp
 *
 *  Created on: Jul 30, 2015
 *      Author: ctseng
 */


#include "HCI_Base.hpp"
#include <string.h>



/*
 * HCI_Pkg_CMD:: HCI command package
 *
 * |OP(16)|paramL(8)|params(paramL)|
 *
 */
int HCI_Base::HCI_CMDPkg_Gen(char* buffer, int buffL, uint16_t OPCode,
		char paramL, char* params){


	if(buffL<3+paramL)return -1;


	if(params!=buffer+3)
		memcpy ( buffer+3, params, paramL);

	uint16_t* OPSection=(uint16_t*)buffer;
	*(OPSection)++=OPCode;
	buffer=(char*)OPSection;
	*buffer++=paramL;

	return 3+paramL;
}

/*
 * HCI_Pkg_ENC is to encoding a packet
 *
 * (input)rawPkg => Slip Pkg =>  (coded Pkg output) [C0,Slip Pkg,C0]
 *
 *  Slip Pkg=>
 *  0xC0=>0xDB,0xDC
 *  0xDB=>0xDB,0xDD
 *  0x11=>0xDB,0xDE(if OOFSWFlowCtrl==true)
 *  0x13=>0xDB,0xDF(if OOFSWFlowCtrl==true)
 *
 * rawPkg and buffer can be the same, but be careful the output length could be longer than Pkg info
 *
*/
int HCI_Base::HCI_Pkg_ENC(char* buffer, int buffL,char* rawPkg, int rawPkgL,bool OOFSWFlowCtrl)
{
	int extendN=0;

	for(int i=0;i<rawPkgL;i++)//find how much char need to be replaced
	{
		unsigned char tmp=rawPkg[i];
		if(tmp==0xC0||tmp==0xDB)extendN++;
		else if(OOFSWFlowCtrl&&(tmp==0x11||tmp==0x13))extendN++;
	}


	int ENCPkgL=rawPkgL+extendN+2;
	if(ENCPkgL>buffL)return -1;

	//Write backward

	buffer+=ENCPkgL-1;//set ptr to the end of encoded Pkg

	*buffer--=0xC0;//tail
	for(int i=rawPkgL-1;;i--)
	{
		unsigned char  tmp=rawPkg[i];

		if(tmp==0xC0){

			*buffer--=0xDC;
			*buffer=0xDB;

		}else if(tmp==0xDB){

			*buffer--=0xDD;
			*buffer=0xDB;

		}else if(OOFSWFlowCtrl&&tmp==0x11){
			*buffer--=0xDE;
			*buffer=0xDB;

		}else if(OOFSWFlowCtrl&&tmp==0x13){

			*buffer--=0xDF;
			*buffer=0xDB;

		}else{

			*buffer=tmp;
		}

		buffer--;

		if(i==0)break;
	}

	*buffer=0xC0;//head

	return ENCPkgL;


}

