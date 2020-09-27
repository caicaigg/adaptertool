#include "stdafx.h"

#include<stdio.h>
#include <assert.h>

#include <pugixml.hpp>

#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/lexical_cast.hpp>
#include <DailyLog.h>


#include "DDSCore.h"
#include "Debug.h"
#include "Client.h"
#include "DataManager.h"

using namespace CDataManager;

// char topicName[] = { "SysReset", "SysConclude", "SysSelfCheck", "SysLoad", "SysPrePosition", "SysModeSet", "SysRunControl", "SysStateSeek",
// 					"EntityMotionParam", "SysMotionUpdate", "SimEventParamBase", "SimEventParam2", "SimEventParam101","SimEventParam102",
// 					"SimEventParam103", "SimEventParam104", "MissileSend201",  "MissileBomb202", "ShiftTarget203","ShiftGuide204",
// 					"SimEventDescribe", "SysEventPub", "UpdateNavigationInfo", "UpdateScenarioData" };


#define  TOPIC_DDS_RECV_INIT_CIA(recvInitPath) \
		CIA_STATUS status = Hwa_CIA_Init(recvInitPath); \
		if (status == CIA_ERROR) \
		{ \
			_LOG("DDS接收初始化CIA失败!\n"); \
			return false; \
		} 

#define  TOPIC_DDS_SEND_INIT_CIA(sendInitPath) \
		CIA_STATUS status = Hwa_CIA_Init(sendInitPath); \
		if (status == CIA_ERROR) \
		{ \
			_LOG("DDD发送初始化CIA失败!\n"); \
			return false; \
		} 

template <typename T, typename T1>
void OnRecvData(const void *pBuf, uint uCount)
{
	int i = 0;
	//uCount 的值会很大，在打断点之后；现只拷贝一次
	for (uint i = 0; i < uCount; i++)
	{
		
		int size = sizeof(T);
		T *tmpdata = new T;

		memcpy(tmpdata, (const char*)pBuf + i * sizeof(T), size);

		//auto data = boost::make_shared<T>(*tmpData);
		//void * data = tmpData;
 	
		T1 tmpobject;

		BaseTypePtr base = boost::make_shared<BaseType>();
		base->type = tmpobject.DataType;
		//memcpy(base->data, tmpData, size);
		base->data = tmpdata;

 		QueueData_DDS()->SetData(base);
		
	}
}


CDDSCore::CDDSCore()
{
	//初始化DDS域值

}

CDDSCore::~CDDSCore()
{
}

bool CDDSCore::Initialize()
{
	_DDSValue = ToolConfig::Instance()->GetDDSValue();
	assert(_DDSValue);

	//DDS初始化
	if (!DDSInit())
	{
		return false;
	}
	return true;
}

bool CDDSCore::DDSInit()
{
	if (!DDS_Recv_Init())
	{
		_LOG("DDS接收初始化失败！\n");
		return false;
	}

// 	if (!DDS_Send_Init())
// 	{
// 		//LogError
// 		_LOG("DDS发送初始化失败！\n");
// 		return false;
// 	}
	return true;
}

bool CDDSCore::DDS_Recv_Init()
{
	std::string allfilename;
	allfilename.append("config\\");
	allfilename.append("test_reciver.xml");

	char recvInitPath[256] = { "" };
	memcpy(recvInitPath, allfilename.c_str(), allfilename.size());
	//TOPIC_DDS_RECV_INIT_CIA(recvInitPath);
	CIA_STATUS status = Hwa_CIA_Init(recvInitPath);
	if (status == CIA_ERROR)
	{
		_LOG("DDS接收初始化CIA失败!\n");
		return false;
	}


 	DDS_Recv_CallBack("SysResetRequest", OnRecvData<TPC_SysResetRequest, SysReset>);//没填xml
 	DDS_Recv_CallBack("SysHaltRequest",  OnRecvData<TPC_SysHaltRequest, SysConclude>);
 	DDS_Recv_CallBack("SysBitRequest",   OnRecvData<TPC_SysBitRequest, SysSelfCheck>);
 	DDS_Recv_CallBack("ScnDldRequest",   OnRecvData<TPC_ScnDldRequest, SysLoad>);
 	DDS_Recv_CallBack("SysRdyRequest",   OnRecvData<TPC_SysRdyRequest, SysPrePosition>);
// 	DDS_Recv_CallBack("SysModeSet",      OnRecvData<SysModeSet, SysReset>);

 	DDS_Recv_CallBack("SysCtrlRequest",  OnRecvData<TPC_SysCtrlRequest, SysRunControl>);
 	DDS_Recv_CallBack("SysStqRequest",   OnRecvData<TPC_SysStqRequest, SysStateSeek>);
 	DDS_Recv_CallBack("ScnPlatUpdate", OnRecvData<TPC_ScnPlatUpdate, SysMotionUpdate>);
//  	DDS_Recv_CallBack("ScnEventUpdate",  OnRecvData<TPC_ScnSimEvent, SysEventPub>);//没填xml
// 
// // 	DDS_Recv_CallBack("SysResetReply",   OnRecvData<SysResetReply>);
// // 	DDS_Recv_CallBack("SysHaltNotify",   OnRecvData<HaltNotify>);
// //	DDS_Recv_CallBack("SysBitReply",     OnRecvData<SelfCheckReply>);
// // 	DDS_Recv_CallBack("SysDldNotify",    OnRecvData<DldNotify>);
// // 	DDS_Recv_CallBack("SysRdyNotify",    OnRecvData<RdyNotify>);
// // 	DDS_Recv_CallBack("SysModeReply",    OnRecvData<ModeReply>);
// // 	DDS_Recv_CallBack("SysCtrlReply",    OnRecvData<SysCtrlReply>);
// // 	DDS_Recv_CallBack("SysStqReply",     OnRecvData<SysStqReply>);
// 
// 	DDS_Recv_CallBack("OwnInsUpdate",    OnRecvData<UpdateNavigationInfo>);
// 	DDS_Recv_CallBack("ScnMixUpdate",    OnRecvData<UpdateScenarioData>);

	return true;
}

bool CDDSCore::DDS_Send_Init()
{
	char * sendInitPath = "E:\\test_sender.xml";
	//TOPIC_DDS_SEND_INIT_CIA(sendInitPath);
	CIA_STATUS status = Hwa_CIA_Init(sendInitPath); 
	if (status == CIA_ERROR)
	{
		_LOG("DDD发送初始化CIA失败!\n");
		return false;
	}

	return true;
}

bool CDDSCore::DDS_Recv_CallBack(char * tpname, DDRRecvCallBackFunc func)
{
	CIA_HANDLE hd = Hwa_CIA_GetHandle(1,tpname);
	if (hd == CIA_ERROR)
	{
		_LOG("接收回调获取句柄失败！\n");
		return false;
	}

	char * buf = new char[1024 * 100];
	uint i;
	CIA_STATUS readrs = Hwa_CIA_Read(hd,buf,2,&i);

	CIA_STATUS rs = Hwa_CIA_Set_Read_Callback(hd, func);//回调方式接收

	return true;
}

bool CDDSCore::DDS_Send_Data(char * tpname, void * data) const
{
	CIA_HANDLE hd = Hwa_CIA_GetHandle(1,tpname);
	if (hd == CIA_ERROR)
	{
		std::stringstream stream;
		stream << hd;
		_LOG(std::string("发送数据获取句柄失败！错误码：").append(stream.str()));
		return false;
	}
	CIA_STATUS status = Hwa_CIA_Write(hd, data);
	if (status == CIA_OK)
	{
		return true;
	}
	else
	{
		std::stringstream stream;
		stream << status;
		_LOG(std::string("发送数据失败原因：").append(stream.str()));
		return false;
	}
}
// 
// void CDDSCore::SendDDS(int TopicType, DataTypeBase* Data) const
// {
// 	const char * tpname = GetTopicName(TopicType);
// 
// 	if (DDS_Send_Data(const_cast<char*>(tpname), Data))
// 	{
// 		_LOG(std::string(tpname).append(",发送成功！"));
// 	}
// 	else
// 	{
// 		_LOG(std::string(tpname).append("DDS_Send_Data()发送失败！"));
// 	}
// }

void CDDSCore::SendDDS(int TopicType, void* Data) const
{
	const char * tpname = GetTopicName(TopicType);
	if (!tpname)
	{
		_LOG(std::string("未找到主题，").append(boost::lexical_cast<std::string>(TopicType)));
	}

	if (DDS_Send_Data(const_cast<char*>(tpname), Data))
	{
		//_LOG(std::string(tpname).append(",发送成功！"));
	}
	else
	{
		_LOG(std::string(tpname).append("DDS_Send_Data()发送失败！"));
	}
}

const char * CDDSCore::GetTopicName(int TopicType) const
{
	switch (TopicType)
	{
		//下发
	case DDSTYPE_SysResetRequest:
		return TOPIC_S_SysResetRequest;
	case DDSTYPE_SysHaltRequest:
		return TOPIC_S_SysHaltRequest;
	case DDSTYPE_SysBitRequest:
		return TOPIC_S_SYSBITREQUEST;
	case DDSTYPE_ScnDldRequest:
		return TOPIC_S_ScnDldRequest;
	case DDSTYPE_SysRdyRequest:
		return TOPIC_S_SysRdyRequest;
	case DDSTYPE_SysModeSet:
		return TOPIC_S_SysModeSet;
	case DDSTYPE_SysCtrlRequest:
		return TOPIC_S_SysCtrlRequest;
	case DDSTYPE_SysStqRequest:
		return TOPIC_S_SysStqRequest;
	case DDSTYPE_ScnPlatUpdate:
		return TOPIC_S_ScnPlatUpdate;
	case DDSTYPE_ScnEventUpdate:
		return TOPIC_S_ScnEventUpdate;
	case DDSTYPE_OwnInsUpdate:
		return TOPIC_S_OwnInsUpdate;
	case DDSTYPE_ScnMixUpdate:
		return TOPIC_S_ScnMixUpdate;

		//上报
	case DDSTYPE_SysResetReply:
		return TOPIC_P_SysResetReply;
	case DDSTYPE_SysHaltNotify:
		return TOPIC_P_SysHaltNotify;
	case DDSTYPE_SysBitReply:
		return TOPIC_P_SysBitReply;
	case DDSTYPE_SysDldNotify:
		return TOPIC_P_SysDldNotify;
	case DDSTYPE_SysRdyNotify:
		return TOPIC_P_SysRdyNotify;
	case DDSTYPE_SysModeReply:
		return TOPIC_P_SysModeReply;
	case DDSTYPE_SysCtrlReply:
		return TOPIC_P_SysCtrlReply;
	case DDSTYPE_SysStqReply:
		return TOPIC_P_SysStqReply;
	case DDSTYPE_RadEventReport:
		return TOPIC_P_RadEventReport;
	case DDSTYPE_RadPltReport:
		return TOPIC_P_RadPltReport;
	case DDSTYPE_RadTrkReport:
		return TOPIC_P_RadTrkReport;
	case DDSTYPE_EwEventReport:
		return TOPIC_P_EwEventReport;
	case DDSTYPE_EwSortReport:
		return TOPIC_P_EwSortReport;
	case DDSTYPE_EwSpecReport:
		return TOPIC_P_EwSpecReport;
	case DDSTYPE_EwPDWReport:
		return TOPIC_P_EwPDWReport;
	case DDSTYPE_EwTgtLocReport:
		return TOPIC_P_EwTgtLocReport;
	case DDSTYPE_ReportSysStop:
		return TOPIC_P_ReportSysStop;
	case DDSTYPE_RadParmNotify:
		return TOPIC_P_RadParmNotify;
	default:
		break;
	}
	return nullptr;
}

/////////////////////////////////////////////////////////////
// radar接口模块 测试代码
////////////////////////////////////////////////////////////
#ifdef LVC29_RADAR_DEBUG

CTestLvc::CTestLvc()
	:_dds(new CDDSCore())
{
}

CTestLvc::~CTestLvc()
{
}

void CTestLvc::SelfCheckTS()
{
	//_dds->onRecvSelfCheck_dds();
}

void CTestLvc::LaunchLoadTS()
{
	//_dds->onRecvLaunchLoad_dds();
}

void CTestLvc::StartUpCommandTS()
{
	//_dds->onRecvStartUpCommand_dds();
}

void CTestLvc::StopCommandTS()
{
	//_dds->onRecvStopCommand();
}

void CTestLvc::BreakCommandTS()
{
	//_dds->onRecvBreakCommand_dds();
}

void CTestLvc::EntityDataTS()
{
	//_dds->onRecvEntityMotionData_dds();
}

#endif