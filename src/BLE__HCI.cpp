#include <iostream>
#include "HCI_Base.hpp"
HCI_Base hci_x;
using namespace std;
using namespace HCI_CMD_OP;

void PrintHexArr(char*buffer, int bufL) {
	printf("%d:", bufL);
	for (int i = 0; i < bufL; i++)
		printf("%02X ", (unsigned char) buffer[i]);
	printf("\n");

}
char buff[60];
int main() {

	char parameters[] = "sdsdsds";
	parameters[2] = (unsigned int) 0xC0;
	parameters[3] = (unsigned int) 0xDB;
	parameters[4] = (unsigned int) 0x11;



	memcpy ( buff, parameters, sizeof(parameters));
	PrintHexArr(buff, sizeof(parameters));

	int PakL = HCI_Base::HCI_CMDPkg_Gen(buff, sizeof(buff),
			Utils::OCFOGF2OP(LINKPOLI_CMD::PARK_MODE, LINKPOLI_CMD::OGF_),
			sizeof(parameters), parameters);
	if (PakL > 0) {
		int ENPL = HCI_Base::HCI_Pkg_ENC(buff, sizeof(buff), buff, PakL, false);
		PrintHexArr(buff, ENPL);
	}

	return 0;
}
