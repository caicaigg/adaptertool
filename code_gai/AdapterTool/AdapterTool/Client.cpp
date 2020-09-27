#include "stdafx.h"
#include "Client.h"
#include "Debug.h"
#include "DataManager.h"
#include <boost/function.hpp>


#define Right_TimeQ 3000
#define Right_TimeD 2000
#define Warning_TimeD 1000

//#define _LOG_AHead(s) _LOG( _ModeName + s)

RadarClient::RadarClient()
{
	//int len = sizeof(ST_BEAM_INFO[100]);
	memset(_deal_buf,0,1024);
	_CheckComSemaphore = CreateSemaphore(NULL,0,1,NULL);
}


RadarClient::~RadarClient()
{
}

bool RadarClient::Initialize()
{
	Init(ToolConfig::Instance()->GetRadarIPValue(), 
		ToolConfig::Instance()->GetRadarPortValue(), 
		ToolConfig::Instance()->GetRecvRadarPortValue(),
		boost::bind(&RadarClient::TcpRecvDataFunction, this,_1),
		"Radar");

	//SetDealbuff(_deal_buf,&_deal_buflen);
	SetSemaphore(&_CheckComSemaphore);

	_Recvthread = new boost::thread(&RadarClient::run, this);
	
	_CheckThread = boost::make_shared<boost::thread>(&RadarClient::CheckFunction_Thread, this);

// 	_DataSemaphore = CreateSemaphore(NULL,0,100,NULL);
// 	_DataThread = boost::make_shared<boost::thread>(&RadarClient::DataFunction_Thread, this);

	return true;
}


void RadarClient::ReportEvent(int EventCommand)
{
	//虚构一次 逻辑tcp发送 队列

// 	SMessageFormat Head;
// 	Head._CodeStartSign = 0x1F1F; //虚构
// 	Head._DataLenth = MSGHEADER;
// 	Head._DataLenth += MSGEND;
// 	Head._SourceAddress = 0;
// 	Head._TargetAddress = 0;
// 	Head._CommandNum = 0;
// 	Head._CommandCode = EventCommand; //Q
// 	Head._Version = VERSION_LVC29;
// 	Head._Property = PROPERTY_LVC29;
// 	Head._MessageOrder = 0;
// 	Head._TotalNumOfMessage = 1;
// 	Head._CurrentSerialNum = 1;
// 
// 	Head._CheckCode = CHECKCODE_LVC29;
// 	Head._CodeEndSign = ENDCODE_LVC29;
// 
// 	buffer_type tmpRecvBuff;
// 	for (int i = 0; i < sizeof(SMessageFormat); ++i)
// 	{
// 		tmpRecvBuff.push_back( * ((char*)&Head+i) );
// 	}
// 	QueueData_UDP()->SetData(tmpRecvBuff);

}

void RadarClient::run()
{
	
	CTcpConnectClient::run();
}


void RadarClient::TransferHead(SMessageFormat& Head, const buffer_type & buffer)
{
	int type = 0;

	memcpy(&Head, &buffer[0], MSGHEADER);
}

void RadarClient::Pack(SMessageFormat & Head, char * PackInfo)
{
	Head._CodeStartSign = 0x7e7e;

}

void RadarClient::CheckFunction_Thread()
{
	//延时检查周期
	int TimeDelayCheck = Right_TimeD;
	//额外延时周期
	int TimeQ = Right_TimeQ;

	int recon_number = 0;

	DMCommunicationQueryPackage package;
	while(1)
	{
		if (TimeQ == 0)
		{
			//_LOG("1s发送 通信查询 radar");
		}
		else
		{
			//_LOG("5s发送 通信查询 radar");
		}

		//发送
		sendDMCommunicationQueryPackage(package);

		DWORD rs = WaitForSingleObject(_CheckComSemaphore,TimeDelayCheck);
		if (rs == WAIT_TIMEOUT)
		{
			_LOG_AHead("通信查询超时");
			if (Warning_TimeD == TimeDelayCheck)
			{
				//第二已发送,给DDS上报

				ReportEvent(0xFF);

			}
			TimeDelayCheck = Warning_TimeD;
			TimeQ = 0;

			//通信机制，超时重连，（针对服务器异常退出）
			if (recon_number++ >= 5 )
			{
				CTcpConnectClient::reconn_handler();
			}
		}
		else if (rs == WAIT_OBJECT_0)
		{
			if (TimeQ != Right_TimeQ || TimeDelayCheck != Right_TimeD)
			{
				TimeQ = Right_TimeQ;
				TimeDelayCheck = Right_TimeD;
				recon_number = 0;
			}
		}

		Sleep(TimeQ);
		// 		SysSelfCheck_ddsfunc(nullptr);
		// 		Sleep(1);
		// 		SysLoad_ddsfunc(nullptr);
		// 		Sleep(1);
	}
}

void RadarClient::sendDMCommunicationQueryPackage(const DMCommunicationQueryPackage CommunicationQuery)
{
	SMessageFormat Head;
	//Pack(msg, (char*)&CommunicationQuery, sizeof(DMCommunicationQueryPackage));

	int len = MSGHEADER+MSGEND;

	Head._CodeStartSign = 0x7e7e;
	Head._DataLenth = MSGHEADER;
	Head._DataLenth += MSGEND;
	Head._SourceAddress = 0;
	Head._TargetAddress = 0;
	Head._CommandNum = RunWaterNumber();
	Head._CommandCode = _LVC_DM_TXCX;
	Head._Version = VERSION_LVC29;
	Head._Property = PROPERTY_LVC29;
	Head._MessageOrder = MessageOrderNumber();
	Head._TotalNumOfMessage = 1;
	Head._CurrentSerialNum = 1;
	if (sizeof(CommunicationQuery) == 1)
	{
		//len += sizeof(CommunicationQuery);
	}
	Head._CheckCode = CHECKCODE_LVC29;
	Head._CodeEndSign = ENDCODE_LVC29;

	write( (char*)&Head,len);
}

void RadarClient::sendDMSystemSelfCheckPackage(const DMSystemSelfCheckPackage SelfCheck)
{
	SMessageFormat Head;
	int len = MSGHEADER+MSGEND;

	Head._CodeStartSign = 0x7e7e;
	Head._DataLenth = MSGHEADER;
	Head._DataLenth += MSGEND;
	Head._SourceAddress = 0;
	Head._TargetAddress = 0;
	Head._CommandNum = RunWaterNumber();
	Head._CommandCode = _LVC_DM_XTZJ;
	Head._Version = VERSION_LVC29;
	Head._Property = PROPERTY_LVC29;
	Head._MessageOrder = MessageOrderNumber();
	Head._TotalNumOfMessage = 1;
	Head._CurrentSerialNum = 1;
	if (sizeof(SelfCheck) == 1)
	{
		//len += sizeof(SelfCheck);
	}
	Head._CheckCode = CHECKCODE_LVC29;
	Head._CodeEndSign = ENDCODE_LVC29;

	
	write((char*)&Head,len);

}

void RadarClient::sendDMRadarInitConfigPackage(const CENTER2RADAR_INIT RadarInit)
{
	SMessageFormat Head;

	Head._CodeStartSign = 0x7e7e;
	Head._DataLenth = MSGHEADER;
	Head._DataLenth += MSGEND;
	Head._SourceAddress = 0;
	Head._TargetAddress = 0;
	Head._CommandNum = RunWaterNumber();
	Head._CommandCode = _LVC_DM_LDCSHPZ;
	Head._Version = VERSION_LVC29;
	Head._Property = PROPERTY_LVC29;
	Head._MessageOrder = MessageOrderNumber();
	Head._TotalNumOfMessage = 1;
	Head._CurrentSerialNum = 1;
	if (sizeof(RadarInit) == 1)
	{

	}
	Head._CheckCode = CHECKCODE_LVC29;
	Head._CodeEndSign = ENDCODE_LVC29;

	int len = 0;

	char* buff = new char[MSGHEADER + MSGEND + sizeof(CENTER2RADAR_INIT)+1];

	//头
	memcpy(buff, &Head, MSGHEADER);
	len = MSGHEADER;

	//消息
	memcpy(buff+len, &RadarInit, sizeof(CENTER2RADAR_INIT));
	len += sizeof(CENTER2RADAR_INIT);

	//尾
	memcpy(buff+len, (char *)&Head + MSGHEADER, MSGEND);
	len += MSGEND;

	Head._DataLenth = len;

	write((char*)buff,len);
}

void RadarClient::sendDMRadarLocationQueryPackage(const DMRadarLocationQueryPackage LocationQuery)
{
	SMessageFormat Head;
	int len = MSGHEADER+MSGEND;

	Head._CodeStartSign = 0x7e7e;
	Head._DataLenth = MSGHEADER;
	Head._DataLenth += MSGEND;
	Head._SourceAddress = 0;
	Head._TargetAddress = 0;
	Head._CommandNum = RunWaterNumber();
	Head._CommandCode = _LVC_DM_LDZBCX;
	Head._Version = VERSION_LVC29;
	Head._Property = PROPERTY_LVC29;
	Head._MessageOrder = MessageOrderNumber();
	Head._TotalNumOfMessage = 1;
	Head._CurrentSerialNum = 1;
	if (sizeof(LocationQuery) == 1)
	{
		//len += sizeof(LocationQuery);
	}
	Head._CheckCode = CHECKCODE_LVC29;
	Head._CodeEndSign = ENDCODE_LVC29;

	write((char*)&Head,len);
}

void RadarClient::sendDMRunControlPackage(const DMRunControlPackage RunControl)
{
	SMessageFormat Head;

	Head._CodeStartSign = 0x7e7e;
	Head._DataLenth = MSGHEADER;
	Head._DataLenth += MSGEND;
	Head._SourceAddress = 0;
	Head._TargetAddress = 0;
	Head._CommandNum = RunWaterNumber();
	Head._CommandCode = _LVC_DM_XYKZ;
	Head._Version = VERSION_LVC29;
	Head._Property = PROPERTY_LVC29;
	Head._MessageOrder = MessageOrderNumber();
	Head._TotalNumOfMessage = 1;
	Head._CurrentSerialNum = 1;

	Head._CheckCode = CHECKCODE_LVC29;
	Head._CodeEndSign = ENDCODE_LVC29;

	int len = 0;

	char* buff = new char[MSGHEADER + MSGEND + sizeof(DMRunControlPackage) + 1];

	//头
	memcpy(buff, &Head, MSGHEADER);
	len = MSGHEADER;

	//消息
	memcpy(buff+len, &RunControl, sizeof(DMRunControlPackage));
	len += sizeof(DMRunControlPackage);

	//尾
	memcpy(buff+ len, (char *)&Head + MSGHEADER, MSGEND);
	len += MSGEND;

	Head._DataLenth = len;
	write((char*)buff, len);
}
 
// void RadarClient::sendDMAalibrationMarkCarInitPackage(const DMAalibrationMarkCarInitPackage AMCInit)
// {
// 	SMessageFormat Head;
// 
// 	Head._CodeStartSign = 0x7e7e;
// 	Head._DataLenth = MSGHEADER;
// 	Head._DataLenth += MSGEND;
// 	Head._SourceAddress = 0;
// 	Head._TargetAddress = 0;
// 	Head._CommandNum = RunWaterNumber();
// 	Head._CommandCode = _LVC_DM_BJCCSHPZ;
// 	Head._Version = VERSION_LVC29;
// 	Head._Property = PROPERTY_LVC29;
// 	Head._MessageOrder = MessageOrderNumber();
// 	Head._TotalNumOfMessage = 1;
// 	Head._CurrentSerialNum = 1;
// 
// 	Head._CheckCode = CHECKCODE_LVC29;
// 	Head._CodeEndSign = ENDCODE_LVC29;
// 
// 	int len = 0;
// 
// 	char* buff = new char[MSGHEADER + MSGEND + sizeof(DMAalibrationMarkCarInitPackage) + 1];
// 
// 	//头
// 	memcpy(buff, &Head, MSGHEADER);
// 	len = MSGHEADER;
// 
// 	//消息
// 	memcpy(buff + len, &AMCInit._ScenarioMode, sizeof(AMCInit._ScenarioMode));
// 	len += sizeof(AMCInit._ScenarioMode);
// 
// 	memcpy(buff + len, &AMCInit._TargetTotalNum, sizeof(AMCInit._TargetTotalNum));
// 	len += sizeof(AMCInit._TargetTotalNum);
// 
// 	if (AMCInit._TargetTotalNum != AMCInit._TargretInformation.size())
// 	{
// 		_LOG("目标数据个数，与目标信息数组个数不对应！");
// 	}
// 	for (int i = 0; i < AMCInit._TargetTotalNum; ++i)
// 	{
// 		memcpy(buff + len, &AMCInit._TargretInformation[i], sizeof(DMAMCInitializeOfTarget));
// 		len += sizeof(AMCInit._TargetTotalNum);
// 	}
// 
// 	//尾
// 	memcpy(buff + len, (char *)&Head + MSGHEADER , MSGEND);
// 	len += MSGEND;
// 
// 	Head._DataLenth = len;
// 
// 	write((char*)buff, len);
// }

void RadarClient::sendDMTargetRealTimePackage(const DMTargetRealTimePackage Targets)
{
	SMessageFormat Head;

	Head._CodeStartSign = 0x7e7e;
	Head._DataLenth = MSGHEADER;
	Head._DataLenth += MSGEND;
	Head._SourceAddress = 0;
	Head._TargetAddress = 0;
	Head._CommandNum = RunWaterNumber();
	Head._CommandCode = _LVC_DM_SSMBCS;
	Head._Version = VERSION_LVC29;
	Head._Property = PROPERTY_LVC29;
	Head._MessageOrder = MessageOrderNumber();
	Head._TotalNumOfMessage = 1;
	Head._CurrentSerialNum = 1;

	Head._CheckCode = CHECKCODE_LVC29;
	Head._CodeEndSign = ENDCODE_LVC29;

	int len = 0;

	char* buff = new char[MSGHEADER + MSGEND + sizeof(DMTargetRealTimePackage)+1];

	//头
	memcpy(buff, &Head, MSGHEADER); 
	len = MSGHEADER;

	//消息
	memcpy(buff + len, &Targets._TargetTotalNum, sizeof(Targets._TargetTotalNum)); 
	len += sizeof(Targets._TargetTotalNum);

	if (Targets._TargetTotalNum != Targets._TargretInformation.size())
	{
		_LOG("目标数据个数，与目标信息数组个数不对应！");
	}
	for (int i = 0; i < Targets._TargetTotalNum; ++i)
	{
		memcpy(buff+len, &Targets._TargretInformation[i], sizeof(DMAMCInitializeOfTarget));
		len += sizeof(Targets._TargetTotalNum);
	}

	//尾
	memcpy(buff+len, (char *)&Head + MSGHEADER, MSGEND);
	len += MSGEND;

	Head._DataLenth = len;

	write((char*)buff,len);
}

bool RadarClient::tryTransferHead(const buffer_type & buffer)
{
	if (buffer.empty())
	{
		_LOG("接收的数据长度为空；");
		return false;
	}

	if (buffer.size() < MSGHEADER+MSGEND)
	{
		_LOG("接收的数据小于最小包头；");
		return false;
	}
	return true;
}

void RadarClient::TcpRecvDataFunction(const buffer_type& Buffer)
{
	if (!tryTransferHead(Buffer))
	{
		return;
	}

	QueueData_TCP()->SetData(Buffer);
	//memcpy( (char *)(&hd)+beginlen, &Buffer[0], endlen);
}






BXCClient::BXCClient()
{
	memset(_deal_buf,0,1024);
	_CheckComSemaphore = CreateSemaphore(NULL,0,1,NULL);
	_DataSemaphore = CreateSemaphore(NULL,0,100,NULL);
}

BXCClient::~BXCClient()
{
}

bool BXCClient::Initialize()
{
	//TCP
	CTcpConnectClient::Init(ToolConfig::Instance()->GetBXCIPValue(),
		ToolConfig::Instance()->GetBXCPortValue(),
		ToolConfig::Instance()->GetRecvBXCPortValue(),
		boost::bind(&BXCClient::RecvDataFunction,this,_1),
		"BXC");

	CTcpConnectClient::SetSemaphore(&_CheckComSemaphore);


	_TcpRecvthread = new boost::thread(&CTcpConnectClient::run, this,nullptr);

	_CheckThread = boost::make_shared<boost::thread>(&BXCClient::CheckFunction_Thread, this);
	

	//UDP
	CUDPConnectClient::Init(ToolConfig::Instance()->GetBXCUdpIPValue(),
		ToolConfig::Instance()->GetBXCUdpPortValue(),
		ToolConfig::Instance()->GetRecvBXCUdpPortValue(),
		boost::bind(&BXCClient::RecvDataFunction, this, _1),
		"BXC");

	//_UdpRecvthread = new boost::thread(&CUDPConnectClient::run, this);

	return true;
}

void BXCClient::CheckFunction_Thread()
{
	//延时检查周期
	int TimeDelayCheck = Right_TimeD;
	//额外延时周期
	int TimeQ = Right_TimeQ;

	//超时重连
	int recon_number = 0;

	DMCommunicationQueryPackage package;
	while(1)
	{
		if (TimeQ == 0)
		{
			//_LOG("1s发送 通信查询");
		}
		else
		{
			//_LOG("5s发送 通信查询");
		}

		sendDMCommunicationQueryPackage(package);

		DWORD rs = WaitForSingleObject(_CheckComSemaphore,TimeDelayCheck);
		if (rs == WAIT_TIMEOUT)
		{
			_LOG("bxc 通信查询超时");

			TimeDelayCheck = Warning_TimeD;
			
			TimeQ = 0;
			//通信机制，超时重连，（针对服务器异常退出）
			if (recon_number++ > 5)
			{
				CTcpConnectClient::reconn_handler();
			}
		}
		else if (rs == WAIT_OBJECT_0)
		{
			if (TimeQ != Right_TimeQ || TimeDelayCheck != Right_TimeD)
			{
				TimeQ = Right_TimeQ;
				TimeDelayCheck = Right_TimeD;
				recon_number = 0;
			}
		}

		Sleep(TimeQ);
	}
}


void BXCClient::RecvDataFunction(const buffer_type& Buffer)
{
	QueueData_TCP()->SetData(Buffer);
}

void BXCClient::UdpSendFunction()
{
	//boost::make_shared<boost::thread>(&CUDPConnectClient::BXC_TestData_TMP, this,_1,_2);
}

void BXCClient::sendBGC2_TO_TSPackage(const BGC2_TO_TS& Data)
{
	char* buff = new char[sizeof(BGC2_TO_TS)];

	memcpy(buff, (char *)&Data, sizeof(BGC2_TO_TS));


	write((char*)buff, sizeof(BGC2_TO_TS));
}

void BXCClient::sendDMCommunicationQueryPackage(const DMCommunicationQueryPackage CommunicationQuery)
{
	SMessageFormat Head;
	//Pack(msg, (char*)&CommunicationQuery, sizeof(DMCommunicationQueryPackage));

	int len = MSGHEADER+MSGEND;

	Head._CodeStartSign = 0x7e7e;
	Head._DataLenth = MSGHEADER;
	Head._DataLenth += MSGEND;
	Head._SourceAddress = 0;
	Head._TargetAddress = 0;
	Head._CommandNum = CTcpConnectClient::RunWaterNumber();
	Head._CommandCode = _LVC_DM_TXCX;
	Head._Version = VERSION_LVC29;
	Head._Property = PROPERTY_LVC29;
	Head._MessageOrder = CTcpConnectClient::MessageOrderNumber();
	Head._TotalNumOfMessage = 1;
	Head._CurrentSerialNum = 1;
	if (sizeof(CommunicationQuery) == 1)
	{
		//len += sizeof(CommunicationQuery);
	}
	Head._CheckCode = CHECKCODE_LVC29;
	Head._CodeEndSign = ENDCODE_LVC29;

	write( (char*)&Head,len);
}

void BXCClient::sendDMSystemSelfCheckPackage(const DMSystemSelfCheckPackage SelfCheck)
{
	SMessageFormat Head;
	int len = MSGHEADER+MSGEND;

	Head._CodeStartSign = 0x7e7e;
	Head._DataLenth = MSGHEADER;
	Head._DataLenth += MSGEND;
	Head._SourceAddress = 0;
	Head._TargetAddress = 0;
	Head._CommandNum = CTcpConnectClient::RunWaterNumber();
	Head._CommandCode = _LVC_DM_XTZJ;
	Head._Version = VERSION_LVC29;
	Head._Property = PROPERTY_LVC29;
	Head._MessageOrder = CTcpConnectClient::MessageOrderNumber();
	Head._TotalNumOfMessage = 1;
	Head._CurrentSerialNum = 1;
	if (sizeof(SelfCheck) == 1)
	{
		//len += sizeof(SelfCheck);
	}
	Head._CheckCode = CHECKCODE_LVC29;
	Head._CodeEndSign = ENDCODE_LVC29;


	write((char*)&Head,len);
}

void BXCClient::sendDMAalibrationMarkCarInitPackage(const DMAalibrationMarkCarInitPackage ControlState)
{
	SMessageFormat Head;

	Head._CodeStartSign = 0x7e7e;
	Head._DataLenth = MSGHEADER;
	Head._DataLenth += MSGEND;
	Head._SourceAddress = 0;
	Head._TargetAddress = 0;
	Head._CommandNum = CTcpConnectClient::RunWaterNumber();
	Head._CommandCode = _LVC_DM_BJCCSHPZ;
	Head._Version = VERSION_LVC29;
	Head._Property = PROPERTY_LVC29;
	Head._MessageOrder = CTcpConnectClient::MessageOrderNumber();
	Head._TotalNumOfMessage = 1;
	Head._CurrentSerialNum = 1;

	Head._CheckCode = CHECKCODE_LVC29;
	Head._CodeEndSign = ENDCODE_LVC29;

	int len = 0;

	char* buff = new char[MSGHEADER + MSGEND + sizeof(DMAalibrationMarkCarInitPackage) + 1];

	//头
	memcpy(buff, &Head, MSGHEADER);
	len = MSGHEADER;

	//消息
	memcpy(buff + len, &ControlState, sizeof(DMAalibrationMarkCarInitPackage));
	len += sizeof(DMAalibrationMarkCarInitPackage);

	//尾
	memcpy(buff + len, (char *)&Head + MSGHEADER, MSGEND);
	len += MSGEND;

	Head._DataLenth = len;

	write((char*)buff, len);
}
