#include "stdafx.h"
#include "Tool.h"
#include "Tool_p.h"

#include "DataManager.h"

#include "RadarCore.h"
#include "DDSCore.h"
#include "BXCCore.h"
#include "SceneResolution.h"
#include "Debug.h"



ToolPrivate::ToolPrivate()
	:_radarIn(new CRadarCore)
	,_ddsIn(new CDDSCore)
	,_bxcIn(new CBXCCore)
	,_scenIn(new CSceneResolution)
#ifdef LVC29_RADAR_DEBUG
	,_testLvc(new CTestLvc)
#endif
	
{

}


CTool::CTool()
	:_p(new ToolPrivate())
{
}


CTool::~CTool()
{
}

bool CTool::Initialize()
{
	//
	MyConfig::Instance()->Initialize();

	if (!InitDDSIn())
	{
		return false;
	}
	if (!InitRadarIn())
	{
		return false;
	}
	if (!InitBXCIn())
	{
		return false;
	}

	//开启处理线程
	_p->_DDSDataThr = new boost::thread(&CTool::DDSDataFunction_Thread, this);
	_p->_TCPDataThr = new boost::thread(&CTool::TCPDataFunction_Thread, this);

	return true;
}

void CTool::run()
{
	do
	{
#ifdef LVC29_RADAR_DEBUG
		cin_cmd_char();
#endif
		Sleep(10);
	} while (1);
}

const std::string & CTool::GetLastError()
{
	return _p->_LastErr;
}

bool CTool::InitDDSIn()
{
	_p->_ddsIn->Initialize();
	return true;
}

bool CTool::InitRadarIn()
{
	_p->_radarIn->Initialize();
	//_p->_radarIn->SendSelfCheck(SelfCheck());
	return true;
}

bool CTool::InitBXCIn()
{
	_p->_bxcIn->Initialize();
	return true;
}


#define CASE_DDSTYPE(TypeValue,Data) \
	case TypeValue: \
		if (Data##ptr Data##tmp = boost::dynamic_pointer_cast<Data>(base)) \
		{ \
			Data##_ddsfunc(Data##tmp);\
		} \
		else \
		{ \
			_LOG("枚举型号，和数据类型不匹配！"); \
		} \
		break;

#pragma region DDS接收消息处理模块

void CTool::DDSDataFunction_Thread()
{
	do
	{
		QueueData_DDS()->WaitCmd();

		if (DataTypeBaseptr base = QueueData_DDS()->GetData())
		{
			switch (base->DataType)
			{
				CASE_DDSTYPE(DDSTYPE_SysResetRequest, SysReset);
				CASE_DDSTYPE(DDSTYPE_SysHaltRequest, SysConclude);
				CASE_DDSTYPE(DDSTYPE_SysBitRequest, SysSelfCheck);
				CASE_DDSTYPE(DDSTYPE_SysDldRequest, SysLoad);
				CASE_DDSTYPE(DDSTYPE_SysRdyRequest, SysPrePosition);
				CASE_DDSTYPE(DDSTYPE_SysModeSet, SysModeSet);
				CASE_DDSTYPE(DDSTYPE_SysCtrlRequest, SysRunControl);
				CASE_DDSTYPE(DDSTYPE_SysStqRequest, SysStateSeek);
				CASE_DDSTYPE(DDSTYPE_ScnPlatUpdate, SysMotionUpdate);
				CASE_DDSTYPE(DDSTYPE_ScnEventUpdate, SysEventPub);
				CASE_DDSTYPE(DDSTYPE_OwnInsUpdate, UpdateNavigationInfo);
				CASE_DDSTYPE(DDSTYPE_ScnMixUpdate, UpdateScenarioData);

			default:
				break;
			}

		}

	} while (true);
}

void CTool::SysReset_ddsfunc(SysResetptr Reset)
{
	Reset = boost::make_shared<SysReset>();
	Reset->DataType = 0xFF01;
	
}

void CTool::SysConclude_ddsfunc(SysConcludeptr Conclud)
{
	//中间层数据处理

	DMRunControlPackage package;
	package._WorkCodeID = 2;//终止
	_p->_radarIn->SendDMRunControlPackage(package);
}

void CTool::SysSelfCheck_ddsfunc(SysSelfCheckptr SelfCheck)
{

	DMSystemSelfCheckPackage package;

	_p->_radarIn->SendDMSystemSelfCheckPackage(package);
}

void CTool::SysLoad_ddsfunc(SysLoadptr Load)
{
	//启动加载，文件
}

void CTool::SysPrePosition_ddsfunc(SysPrePositionptr PrePosition)
{
	DMRadarInitConfigPackage package;

	_p->_radarIn->SendDMRadarInitConfigPackage(package);

	DMAalibrationMarkCarInitPackage amcpackage;
	_p->_radarIn->SendDMAalibrationMarkCarInitPackage(amcpackage);
}

void CTool::SysModeSet_ddsfunc(SysModeSetptr ModeSet)
{
	//?
}

void CTool::SysRunControl_ddsfunc(SysRunControlptr RunControl)
{
	DMRunControlPackage package;
	package._WorkCodeID = RunControl->CommondID;//运行？
	_p->_radarIn->SendDMRunControlPackage(package);
}

void CTool::SysStateSeek_ddsfunc(SysStateSeekptr StateSeek)
{

	//通信查询
	DMCommunicationQueryPackage package;

	_p->_radarIn->SendDMCommunicationQueryPackage(package);
}

void CTool::SysMotionUpdate_ddsfunc(SysMotionUpdateptr MotionUpdate)
{
	DMTargetRealTimePackage RealTimePackage;
	_p->_radarIn->SendDMTargetRealTimePackage(RealTimePackage);
}

void CTool::SysEventPub_ddsfunc(SysEventPubptr EventPub)
{
	//
}

void CTool::UpdateNavigationInfo_ddsfunc(UpdateNavigationInfoptr UpdateNavigation)
{
	//发送给SUT适配单元
}

void CTool::UpdateScenarioData_ddsfunc(UpdateScenarioDataptr UpdateScenario)
{
	//空
}


#pragma endregion DDS接收消息处理模块

#define CASE_TCPTYPE(TypeValue,Data) \
	case TypeValue: { Data data; \
		memcpy(&data, &buffer[0 + 9 * 2 + 2 * 1], sizeof(Data)); \
		Data##_tcpfunc(data);\
		}\
		break;

#pragma region Tcp接收消息处理模块

void CTool::TCPDataFunction_Thread()
{
	do
	{
		QueueData_TCP()->WaitCmd();

		buffer_type buffer = QueueData_TCP()->GetData();
		if (!buffer.empty())
		{
			//解析头
			SMessageFormat msghead;
			_p->_radarIn->TransferHead(msghead, buffer);

			//雷达接口测试！
			//处理消息，DDS发送
			switch (msghead._CommandCode)
			{
				CASE_TCPTYPE(_LVC_RM_MLXY, RMCommandAnswerPackage);
				CASE_TCPTYPE(_LVC_RM_XTSB, RMPantReportPackage);
				CASE_TCPTYPE(_LVC_RM_LDZJSB, RMRadarSelfTestResult);
				CASE_TCPTYPE(_LVC_RM_BJCZJSB, RMCACSelfTestResult);
				CASE_TCPTYPE(_LVC_RM_LDZBSB, RMRadarCoordinateReport);
				CASE_TCPTYPE(_LVC_RM_DJSJ, RMPointTraceReport);
				CASE_TCPTYPE(_LVC_RM_HJSJ, RMFlightTraceReport);
				CASE_TCPTYPE(_LVC_RM_LDGZCS, RMRadarWorkParamReport);


			default:
				break;
			}

		}

	} while (true);
}


void CTool::RMCommandAnswerPackage_tcpfunc(RMCommandAnswerPackage& package)
{

}

void CTool::RMPantReportPackage_tcpfunc(RMPantReportPackage& package)
{
}

void CTool::RMRadarSelfTestResult_tcpfunc(RMRadarSelfTestResult& package)
{
}

void CTool::RMCACSelfTestResult_tcpfunc(RMCACSelfTestResult& package)
{
}

void CTool::RMRadarCoordinateReport_tcpfunc(RMRadarCoordinateReport& package)
{
}

void CTool::RMPointTraceReport_tcpfunc(RMPointTraceReport& package)
{
}

void CTool::RMFlightTraceReport_tcpfunc(RMFlightTraceReport& package)
{
}

void CTool::RMRadarWorkParamReport_tcpfunc(RMRadarWorkParamReport& package)
{
}
#pragma endregion Tcp接收消息处理模块




#ifdef LVC29_RADAR_DEBUG
void CTool::cin_cmd_char()
{
	int a = 0;
	char buf[100] = { "" };
	std::cin >> buf;

	try
	{
		a = atoi(buf);
	}
	catch (...)
	{
	}

	switch (a)
	{
	case 1:
		SysReset_ddsfunc();
		break;

	default:
		std::cout << "输入类型不对:" << a << std::endl;
		break;
	}
}
#endif