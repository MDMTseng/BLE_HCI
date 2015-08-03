/*
 * HCI_Base.hpp
 *
 *     2$$$$2; '1$$$$$$$$$$$$$$$2; '1$$$$$|
       8&&&&&&2: :2$$$$$$$$$$$$|  |0&&&&&&1
       8&&88&&01:                ;28&&8&82:
       8&&0:|$&&8$|           :10&&82;|1'::
       8&&0   :28&&81:      |$&&&$1'   ;$&1
       8&&0      |$&&&1  :28&&01:     |&&&1
       8&&0        :1::1$&&82;        1&&&1
       8&&0           ;$801':'        1&&&1
       8&&0             ' :$&82;      1&&&1
       8&&0                ;28&&01:   :28&1
       8&&8                  '1$&&8$|, '''|
       8&81                     :10&&000&1,
       2|   '11111111111111111111120&&&&&&1
          :20888888888888888888888888888881



 *
 *  Created on: Jul 30, 2015
 *      Author: ctseng
 */
#ifndef HCI_API_GPFW
#define HCI_API_GPFW

#define uchar unsigned char
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
class HCI_Base {
public:
	typedef enum _HCI_PACKET_TYPE_ {
		HCI_ACK=0,
		HCI_COMMAND = 0x01, HCI_ACL = 0x02, HCI_SCL = 0x03, HCI_EVENT = 0x04,
		HCI_VENDOR=14,HCI_LINKCTRL=15
	} eHCI_PACKET_TYPE;

	//note: paramL is the length in bytes, not the number of params
	//each param may not have the same size
	static int HCI_CMDPkg_Gen(uchar* buffer, int buffMaxL, uint16_t OPCode,
			uchar paramL, uchar* params);
	static uchar* HCI_Pkg_ACL(uchar* buffer, int buffMaxL, uint16_t handle, uchar PB,
			uchar BC, int dataL, uchar* data);//TODO


	typedef union Header_3WireUart {
		uint32_t num;
		struct {
			unsigned int seqNum :3;
			unsigned int ackNum :3;
			unsigned int dataIntegrity :1;
			unsigned int reliablePkg:1;
			unsigned int pkgType :4;
			unsigned int payloadL :12;
			unsigned int headerChecksum :8;
		} elements;
		uchar _4bytes[4];
	} Header_3WireUart;
	/*
	 *
	 */
	static int const HCI_3WUART_HEADERSIZE=sizeof(Header_3WireUart);
	static int const HCI_CMDPkg_Gen_PADDING=3;//CMD package header length=3


	static int HCI_3WUART_PK(uchar* buffer, int buffMaxL,
			uchar seqNum,uchar ackNum,bool dataIntegrity,bool reliablePkg,uchar pkgType,
			uchar* payload, int payloadL);
	static int HCI_3WUART_PK(uchar* buffer, int buffMaxL,
				Header_3WireUart header,
				uchar* payload, int payloadL);
	static int HCI_3WUART_PK(uchar* buffer, int buffMaxL,
				uint32_t header,
				uchar* payload, int payloadL);
	static int HCI_3WUART_UNPK(uchar* inputPack, int inputPackL,Header_3WireUart* header , uchar** payload) ;




	static int HCI_SLIP_ENC(uchar* buffer, int buffMaxL, uchar* rawPkg, int pkgL,
			bool OOFSWFlowCtrl);


	class SLIP_DEC_Info {//simple object for HCI_SLIP_DEC_ByteFeed function

		void InitBuffer(int bufferL)
		{
			buffer=new uchar[bufferL];
			bufferMaxL=bufferL;
		}

		void Init(int bufferL)
		{
			InitBuffer( bufferL);
			packL=0;
			state=ready;
		}

	public:
		uchar *buffer;
		int bufferMaxL;
		int packL;
		uchar state;
		enum states{
			init,ready,recv,escape
		};
		SLIP_DEC_Info(int bufferL)
		{Init(bufferL);}

		~SLIP_DEC_Info()
		{
			delete buffer;
		}
	};





	static int HCI_SLIP_DEC_ByteFeed(SLIP_DEC_Info *SLIPInfo,uchar incomingByte);//TODO


	static uint16_t Calculate_CRC_CCITT(const  uchar* buffer, int size);
};
/*
 * exp::
 *
 *
 *using namespace HCI_CMD_OP;
 *
 *
 *LINKPOLI_CMD::PARK_MODE
 *LINKPOLI_CMD::OGF_
 *
 *or
 *HCI_CMD_OP::LINKPOLI_CMD::PARK_MODE
 *
 */
namespace HCI_CMD_OP {

class LINKCTRL_CMD {
public:

	static const int16_t OGF_ = 0x0001;
	static const int16_t INQUIRY = 0x0001;
	static const int16_t INQUIRY_CANCEL = 0x0002;
	static const int16_t PERIODIC_INQUIRY_MODE = 0x0003;
	static const int16_t EXIT_PERIODIC_INQUIRY_MODE = 0x0004;
	static const int16_t CREATE_CONNECTION = 0x0005;
	static const int16_t DISCONNECT = 0x0006;
	static const int16_t ADD_SCO_CONNECTION = 0x0007;
	static const int16_t ACCEPT_CONNECTION_REQUEST = 0x0009;
	static const int16_t REJECT_CONNECTION_REQUEST = 0x000A;
	static const int16_t LINK_KEY_REQUEST_REPLY = 0x000B;
	static const int16_t LINK_KEY_REQUEST_NEGATIVE_REPLY = 0x000C;
	static const int16_t PIN_CODE_REQUEST_REPLY = 0x000D;
	static const int16_t PIN_CODE_REQUEST_NEGATIVE_REPLY = 0x000E;
	static const int16_t CHANGE_CONNECTION_PACKET_TYPE = 0x000F;
	static const int16_t AUTHENTICATION_REQUESTED = 0x0011;
	static const int16_t SET_CONNECTION_ENCRYPTION = 0x0013;
	static const int16_t CHANGE_CONNECTION_LINK_KEY = 0x0015;
	static const int16_t MASTER_LINK_KEY = 0x0017;
	static const int16_t REMOTE_NAME_REQUEST = 0x0019;
	static const int16_t READ_REMOTE_SUPPORTED_FEATURES = 0x001B;
	static const int16_t READ_REMOTE_VERSION_INFORMATION = 0x001D;
	static const int16_t READ_CLOCK_OFFSET = 0x001F;
	/* HCI Command Code OCF Definitions (Link Control - Version 1.2).    */
	static const int16_t CREATE_CONNECTION_CANCEL = 0x0008;
	static const int16_t REMOTE_NAME_REQUEST_CANCEL = 0x001A;
	static const int16_t READ_REMOTE_EXTENDED_FEATURES = 0x001C;
	static const int16_t READ_LMP_HANDLE = 0x0020;
	static const int16_t SETUP_SYNCHRONOUS_CONNECTION = 0x0028;
	static const int16_t ACCEPT_SYNCHRONOUS_CONNECTION = 0x0029;
	static const int16_t REJECT_SYNCHRONOUS_CONNECTION = 0x002A;

	/* HCI Command Code OCF Definitions (Link Control - Version 2.1 +    */
	/* EDR).                                                             */
	static const int16_t IO_CAPABILITY_REQUEST_REPLY = 0x002B;
	static const int16_t USER_CONFIRMATION_REQUEST_REPLY = 0x002C;
	static const int16_t USER_CONFIRMATION_REQUEST_NEGATIVE_REPLY = 0x002D;
	static const int16_t USER_PASSKEY_REQUEST_REPLY = 0x002E;
	static const int16_t USER_PASSKEY_REQUEST_NEGATIVE_REPLY = 0x002F;
	static const int16_t REMOTE_OOB_DATA_REQUEST_REPLY = 0x0030;
	static const int16_t REMOTE_OOB_DATA_REQUEST_NEGATIVE_REPLY = 0x0033;
	static const int16_t IO_CAPABILITY_REQUEST_NEGATIVE_REPLY = 0x0034;

	/* HCI Command Code OCF Definitions (Link Control - Version 3.0 +    */
	/* HS).                                                              */
	static const int16_t CREATE_PHYSICAL_LINK = 0x0035;
	static const int16_t ACCEPT_PHYSICAL_LINK_REQUEST = 0x0036;
	static const int16_t DISCONNECT_PHYSICAL_LINK = 0x0037;
	static const int16_t CREATE_LOGICAL_LINK = 0x0038;
	static const int16_t ACCEPT_LOGICAL_LINK = 0x0039;
	static const int16_t DISCONNECT_LOGICAL_LINK = 0x003A;
	static const int16_t LOGICAL_LINK_CANCEL = 0x003B;
	static const int16_t FLOW_SPEC_MODIFY = 0x003C;

};

class LINKPOLI_CMD {
public:
	static const int16_t OGF_ = 0x0002;
	/* HCI Command Code OCF Definitions (Link Policy).                   */
	static const int16_t HOLD_MODE = 0x0001;
	static const int16_t SNIFF_MODE = 0x0003;
	static const int16_t EXIT_SNIFF_MODE = 0x0004;
	static const int16_t PARK_MODE = 0x0005;
	static const int16_t EXIT_PARK_MODE = 0x0006;
	static const int16_t QOS_SETUP = 0x0007;
	static const int16_t ROLE_DISCOVERY = 0x0009;
	static const int16_t SWITCH_ROLE = 0x000B;
	static const int16_t READ_LINK_POLICY_SETTINGS = 0x000C;
	static const int16_t WRITE_LINK_POLICY_SETTINGS = 0x000D;

	/* HCI Command Code OCF Definitions (Link Policy - Version 1.2).     */
	static const int16_t READ_DEFAULT_LINK_POLICY_SETTINGS = 0x000E;
	static const int16_t WRITE_DEFAULT_LINK_POLICY_SETTINGS = 0x000F;
	static const int16_t FLOW_SPECIFICATION = 0x0010;

	/* HCI Command Code OCF Definitions (Link Policy - Version 2.1 +     */
	/* EDR).                                                             */
	static const int16_t SNIFF_SUBRATING = 0x0011;

};

class CTRLERBASE_CMD {
public:
	static const int16_t OGF_ = 0x0003;
	/* HCI Command Code OCF Definitions (Host Control and Baseband).     */
	static const int16_t SET_EVENT_MASK = 0x0001;
	static const int16_t RESET = 0x0003;
	static const int16_t SET_EVENT_FILTER = 0x0005;
	static const int16_t FLUSH = 0x0008;
	static const int16_t READ_PIN_TYPE = 0x0009;
	static const int16_t WRITE_PIN_TYPE = 0x000A;
	static const int16_t CREATE_NEW_UNIT_KEY = 0x000B;
	static const int16_t READ_STORED_LINK_KEY = 0x000D;
	static const int16_t WRITE_STORED_LINK_KEY = 0x0011;
	static const int16_t DELETE_STORED_LINK_KEY = 0x0012;
	static const int16_t CHANGE_LOCAL_NAME = 0x0013;
	static const int16_t WRITE_LOCAL_NAME = 0x0013;
	static const int16_t READ_LOCAL_NAME = 0x0014;
	static const int16_t READ_CONNECTION_ACCEPT_TIMEOUT = 0x0015;
	static const int16_t WRITE_CONNECTION_ACCEPT_TIMEOUT = 0x0016;
	static const int16_t READ_PAGE_TIMEOUT = 0x0017;
	static const int16_t WRITE_PAGE_TIMEOUT = 0x0018;
	static const int16_t READ_SCAN_ENABLE = 0x0019;
	static const int16_t WRITE_SCAN_ENABLE = 0x001A;
	static const int16_t READ_PAGE_SCAN_ACTIVITY = 0x001B;
	static const int16_t WRITE_PAGE_SCAN_ACTIVITY = 0x001C;
	static const int16_t READ_INQUIRY_SCAN_ACTIVITY = 0x001D;
	static const int16_t WRITE_INQUIRY_SCAN_ACTIVITY = 0x001E;
	static const int16_t READ_AUTHENTICATION_ENABLE = 0x001F;
	static const int16_t WRITE_AUTHENTICATION_ENABLE = 0x0020;
	static const int16_t READ_ENCRYPTION_MODE = 0x0021;
	static const int16_t WRITE_ENCRYPTION_MODE = 0x0022;
	static const int16_t READ_CLASS_OF_DEVICE = 0x0023;
	static const int16_t WRITE_CLASS_OF_DEVICE = 0x0024;
	static const int16_t READ_VOICE_SETTING = 0x0025;
	static const int16_t WRITE_VOICE_SETTING = 0x0026;
	static const int16_t READ_AUTOMATIC_FLUSH_TIMEOUT = 0x0027;
	static const int16_t WRITE_AUTOMATIC_FLUSH_TIMEOUT = 0x0028;
	static const int16_t READ_NUM_BROADCAST_RETRANSMISSIONS = 0x0029;
	static const int16_t WRITE_NUM_BROADCAST_RETRANSMISSIONS = 0x002A;
	static const int16_t READ_HOLD_MODE_ACTIVITY = 0x002B;
	static const int16_t WRITE_HOLD_MODE_ACTIVITY = 0x002C;
	static const int16_t READ_TRANSMIT_POWER_LEVEL = 0x002D;
	static const int16_t READ_SCO_FLOW_CONTROL_ENABLE = 0x002E;
	static const int16_t READ_SYNCHRONOUS_FLOW_CONTROL_ENABLE = 0x002E;
	static const int16_t WRITE_SCO_FLOW_CONTROL_ENABLE = 0x002F;
	static const int16_t WRITE_SYNCHRONOUS_FLOW_CONTROL_ENABLE = 0x002F;
	static const int16_t SET_HOST_CONTROLLER_TO_HOST_FLOW_CONTROL = 0x0031;
	static const int16_t HOST_BUFFER_SIZE = 0x0033;
	static const int16_t HOST_NUMBER_OF_COMPLETED_PACKETS = 0x0035;
	static const int16_t READ_LINK_SUPERVISION_TIMEOUT = 0x0036;
	static const int16_t WRITE_LINK_SUPERVISION_TIMEOUT = 0x0037;
	static const int16_t READ_NUMBER_OF_SUPPORTED_IAC = 0x0038;
	static const int16_t READ_CURRENT_IAC_LAP = 0x0039;
	static const int16_t WRITE_CURRENT_IAC_LAP = 0x003A;
	static const int16_t READ_PAGE_SCAN_PERIOD_MODE = 0x003B;
	static const int16_t WRITE_PAGE_SCAN_PERIOD_MODE = 0x003C;
	static const int16_t READ_PAGE_SCAN_MODE = 0x003D;
	static const int16_t WRITE_PAGE_SCAN_MODE = 0x003E;

	/* HCI Command Code OCF Definitions (Host Control and Baseband -     */
	/* Version 1.2).                                                     */
	static const int16_t SET_AFH_HOST_CHANNEL_CLASSIFICATION = 0x003F;
	static const int16_t READ_INQUIRY_SCAN_TYPE = 0x0042;
	static const int16_t WRITE_INQUIRY_SCAN_TYPE = 0x0043;
	static const int16_t READ_INQUIRY_MODE = 0x0044;
	static const int16_t WRITE_INQUIRY_MODE = 0x0045;
	static const int16_t READ_PAGE_SCAN_TYPE = 0x0046;
	static const int16_t WRITE_PAGE_SCAN_TYPE = 0x0047;
	static const int16_t READ_AFH_CHANNEL_ASSESSMENT_MODE = 0x0048;
	static const int16_t WRITE_AFH_CHANNEL_ASSESSMENT_MODE = 0x0049;

	/* HCI Command Code OCF Definitions (Host Control and Baseband -     */
	/* Version 2.1 + EDR).                                               */
	static const int16_t READ_EXTENDED_INQUIRY_RESPONSE = 0x0051;
	static const int16_t WRITE_EXTENDED_INQUIRY_RESPONSE = 0x0052;
	static const int16_t REFRESH_ENCRYPTION_KEY = 0x0053;
	static const int16_t READ_SIMPLE_PAIRING_MODE = 0x0055;
	static const int16_t WRITE_SIMPLE_PAIRING_MODE = 0x0056;
	static const int16_t READ_LOCAL_OOB_DATA = 0x0057;
	static const int16_t READ_INQUIRY_RESPONSE_TRANSMIT_POWER_LEVEL = 0x0058;
	static const int16_t WRITE_INQUIRY_TRANSMIT_POWER_LEVEL = 0x0059;
	static const int16_t READ_DEFAULT_ERRONEOUS_DATA_REPORTING = 0x005A;
	static const int16_t WRITE_DEFAULT_ERRONEOUS_DATA_REPORTING = 0x005B;
	static const int16_t ENHANCED_FLUSH = 0x005F;
	static const int16_t SEND_KEYPRESS_NOTIFICATION = 0x0060;

	/* HCI Command Code OCF Definitions (Host Control and Baseband -     */
	/* Version 3.0 + HS).                                                */
	static const int16_t READ_LOGICAL_LINK_ACCEPT_TIMEOUT = 0x0061;
	static const int16_t WRITE_LOGICAL_LINK_ACCEPT_TIMEOUT = 0x0062;
	static const int16_t SET_EVENT_MASK_PAGE_2 = 0x0063;
	static const int16_t READ_LOCATION_DATA = 0x0064;
	static const int16_t WRITE_LOCATION_DATA = 0x0065;
	static const int16_t READ_FLOW_CONTROL_MODE = 0x0066;
	static const int16_t WRITE_FLOW_CONTROL_MODE = 0x0067;
	static const int16_t READ_ENHANCED_TRANSMIT_POWER_LEVEL = 0x0068;
	static const int16_t READ_BEST_EFFORT_FLUSH_TIMEOUT = 0x0069;
	static const int16_t WRITE_BEST_EFFORT_FLUSH_TIMEOUT = 0x006A;
	static const int16_t SHORT_RANGE_MODE = 0x006B;

	/* HCI Command Code OCF Definitions (Host Control and Baseband -     */
	/* Version 4.0 + LE).                                                */
	static const int16_t READ_LE_HOST_SUPPORTED = 0x006C;
	static const int16_t WRITE_LE_HOST_SUPPORTED = 0x006D;
};

class INFO_PARAM {
	static const int16_t OGF_ = 0x0004;
public:
	/* HCI Command Code OCF Definitions (Informational Parameters).      */
	static const int16_t READ_LOCAL_VERSION_INFORMATION = 0x0001;
	static const int16_t READ_LOCAL_SUPPORTED_FEATURES = 0x0003;
	static const int16_t READ_BUFFER_SIZE = 0x0005;
	static const int16_t READ_COUNTRY_CODE = 0x0007;
	static const int16_t READ_BD_ADDR = 0x0009;

	/* HCI Command Code OCF Definitions (Informational Parameters -      */
	/* Version 1.2)                                                      */
	static const int16_t READ_LOCAL_SUPPORTED_COMMANDS = 0x0002;
	static const int16_t READ_LOCAL_EXTENDED_FEATURES = 0x0004;

	/* HCI Command Code OCF Definitions (Informational Parameters -      */
	/* Version 3.0 + HS).                                                */
	static const int16_t READ_DATA_BLOCK_SIZE = 0x000A;
};

class STATUS_PARAM {
public:

	static const int16_t OGF_ = 0x0005;
	/* HCI Command Code OCF Definitions (Status Parameters).             */
	static const int16_t READ_FAILED_CONTACT_COUNTER = 0x0001;
	static const int16_t RESET_FAILED_CONTACT_COUNTER = 0x0002;
	static const int16_t GET_LINK_QUALITY = 0x0003;
	static const int16_t READ_RSSI = 0x0005;

	/* HCI Command Code OCF Definitions (Status Parameters - Version     */
	/* 1.2).                                                             */
	static const int16_t READ_AFH_CHANNEL_MAP = 0x0006;
	static const int16_t READ_CLOCK = 0x0007;

	/* HCI Command Code OCF Definitions (Status Parameters - Version 3.0 */
	/* + HS).                                                            */
	static const int16_t READ_ENCRYPTION_KEY_SIZE = 0x0008;
	static const int16_t READ_LOCAL_AMP_INFO = 0x0009;
	static const int16_t READ_LOCAL_AMP_ASSOC = 0x000A;
	static const int16_t WRITE_REMOTE_AMP_ASSOC = 0x000B;
};

class TEST_CMD {
public:
	static const int16_t OGF_ = 0x0006;
	/* HCI Command Code OCF Definitions (Testing Commands).              */
	static const int16_t READ_LOOPBACK_MODE = 0x0001;
	static const int16_t WRITE_LOOPBACK_MODE = 0x0002;
	static const int16_t ENABLE_DEVICE_UNDER_TEST_MODE = 0x0003;

	/* HCI Command Code OCF Definitions (Testing Commands - Version 2.1 +*/
	/* EDR).                                                             */
	static const int16_t WRITE_SIMPLE_PAIRING_DEBUG_MODE = 0x0004;

	/* HCI Command Code OCF Definitions (Testing Commands - Version 3.0 +*/
	/* HS).                                                              */
	static const int16_t ENABLE_AMP_RECEIVER_REPORTS = 0x0007;
	static const int16_t AMP_TEST_END = 0x0008;
	static const int16_t AMP_TEST = 0x0009;
};

class LECTRLER_CMD {
public:
	static const int16_t OGF_ = 0x0008;
	/* HCI Command Code OCF Definitions (LE Commands - Version 4.0 + LE).*/
	static const int16_t LE_SET_EVENT_MASK = 0x0001;
	static const int16_t LE_READ_BUFFER_SIZE = 0x0002;
	static const int16_t LE_READ_LOCAL_SUPPORTED_FEATURES = 0x0003;
	static const int16_t LE_SET_RANDOM_ADDRESS = 0x0005;
	static const int16_t LE_SET_ADVERTISING_PARAMETERS = 0x0006;
	static const int16_t LE_READ_ADVERTISING_CHANNEL_TX_POWER = 0x0007;
	static const int16_t LE_SET_ADVERTISING_DATA = 0x0008;
	static const int16_t LE_SET_SCAN_RESPONSE_DATA = 0x0009;
	static const int16_t LE_SET_ADVERTISE_ENABLE = 0x000A;
	static const int16_t LE_SET_SCAN_PARAMETERS = 0x000B;
	static const int16_t LE_SET_SCAN_ENABLE = 0x000C;
	static const int16_t LE_CREATE_CONNECTION = 0x000D;
	static const int16_t LE_CREATE_CONNECTION_CANCEL = 0x000E;
	static const int16_t LE_READ_WHITE_LIST_SIZE = 0x000F;
	static const int16_t LE_CLEAR_WHITE_LIST = 0x0010;
	static const int16_t LE_ADD_DEVICE_TO_WHITE_LIST = 0x0011;
	static const int16_t LE_REMOVE_DEVICE_FROM_WHITE_LIST = 0x0012;
	static const int16_t LE_CONNECTION_UPDATE = 0x0013;
	static const int16_t LE_SET_HOST_CHANNEL_CLASSIFICATION = 0x0014;
	static const int16_t LE_READ_CHANNEL_MAP = 0x0015;
	static const int16_t LE_READ_REMOTE_USED_FEATURES = 0x0016;
	static const int16_t LE_ENCRYPT = 0x0017;
	static const int16_t LE_RAND = 0x0018;
	static const int16_t LE_START_ENCRYPTION = 0x0019;
	static const int16_t LE_LONG_TERM_KEY_REQUEST_REPLY = 0x001A;
	static const int16_t LE_LONG_TERM_KEY_REQUEST_NEGATIVE_REPLY = 0x001B;
	static const int16_t LE_READ_SUPPORTED_STATES = 0x001C;
	static const int16_t LE_RECEIVER_TEST = 0x001D;
	static const int16_t LE_TRANSMITTER_TEST = 0x001E;
	static const int16_t LE_TEST_END = 0x001F;
};

typedef union OCFOGF_OP {
	uint16_t code;
	struct {
		unsigned int ocf :10;
		unsigned int ogf :6;
	} op;
} OCFOGF_OP;
class Utils {
public:
	static uint16_t OCFOGF2OP(unsigned int ocf, unsigned int ogf) {
		OCFOGF_OP res;
		res.op.ocf = ocf;
		res.op.ogf = ogf;
		return res.code;
	}
};
}
;

#endif
