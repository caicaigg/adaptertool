#include "stdafx.h"
#include "Tool.h"
#include "Tool_p.h"

#include "RadarCore.h"
#include "DDSCore.h"
#include "BXCCore.h"
#include "SceneResolution.h"
#include "MessageDispatch.h"
#include "MessageReport.h"
#include "DataManager.h"



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
	std::cout << "软件准备" << std::endl;
	if (!ToolConfig::Instance()->Initialize())
	{
		std::cout << "toolconfig初始化失败！" << std::endl;
		return false;
	}
	if (!InitConfig::Instance()->Initialize())
	{
		std::cout << "initconfig初始化失败！" << std::endl;
		return false;
	}
	if (!CDataManager::DMFileLoadTransfer::Instance()->Initialize())
	{
		std::cout << "xml初始读取数据错误！" << std::endl;
		return false;
	}
	if (!InitDDSIn())
	{
		std::cout << "DDS初始化失败！" << std::endl;
		return false;
	}
	if (!InitRadarIn())
	{
		std::cout << "radar初始化失败！" << std::endl;
		return false;
	}
	if (!InitBXCIn())
	{
		std::cout << "bxc初始化失败！" << std::endl;
		return false;
	}

	//
	_p->_MsgDispatch = new MessageDispatch(Radar(),BXC(),ScenResolution());
	_p->_MsgReport = new MessageReport(DDS(),const_cast<CRadarCore*>(Radar()));
	//开启处理线程

	std::cout << "准备完成！" << std::endl;
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

const CDDSCore * CTool::DDS()
{
	return _p->_ddsIn;
}

const CRadarCore * CTool::Radar()
{
	return _p->_radarIn;
}

const CBXCCore * CTool::BXC()
{
	return _p->_bxcIn;
}

CSceneResolution * CTool::ScenResolution()
{
	return _p->_scenIn;
}

#include "DataManager.h"
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
		//下发测试
	case 1:
		_p->_MsgDispatch->TPC_SysResetRequest_ddsfunc(TPC_SysResetRequest());
		break;
	case 2:
		_p->_MsgDispatch->TPC_SysHaltRequest_ddsfunc(TPC_SysHaltRequest());
		break;
	case 3:
		_p->_MsgDispatch->TPC_SysBitRequest_ddsfunc(TPC_SysBitRequest());
		break;
	case 4:
		_p->_MsgDispatch->TPC_ScnDldRequest_ddsfunc(TPC_ScnDldRequest());
		break;
	case 5:
		_p->_MsgDispatch->TPC_SysRdyRequest_ddsfunc(TPC_SysRdyRequest());
		break;
	case 6:
		_p->_MsgDispatch->SysModeSet_ddsfunc(nullptr);
		break;
	case 7:
	{
// 		SysRunControlptr runcon = boost::make_shared<SysRunControl>();
// 		runcon->CommondID = 0;
		TPC_SysCtrlRequest ctr;
		ctr.cmdCode = 0;
		_p->_MsgDispatch->TPC_SysCtrlRequest_ddsfunc(ctr);
		break;
	}
	case 71:
	{
		TPC_SysCtrlRequest ctr;
		ctr.cmdCode = 1;
		_p->_MsgDispatch->TPC_SysCtrlRequest_ddsfunc(ctr);
		break;
	}
	case 8:
		_p->_MsgDispatch->TPC_SysStqRequest_ddsfunc(TPC_SysStqRequest());
		break;
	case 9:
		_p->_MsgDispatch->TPC_ScnPlatUpdate_ddsfunc(TPC_ScnPlatUpdate());
		break;
	case 10:
		_p->_MsgDispatch->TPC_ScnSimEvent_ddsfunc(TPC_ScnSimEvent());
		break;
	case 11:
		_p->_MsgDispatch->UpdateNavigationInfo_ddsfunc(nullptr);
		break;
	case 12:
		_p->_MsgDispatch->UpdateScenarioData_ddsfunc(nullptr);
		break;
		//上传测试
	case 111:
	{
		const buffer_type Buffer(400,'f');
		QueueData_TCP()->SetData(Buffer);
		break;
	}
	case 999:
	{
		std::string str;
		std::stringstream stream;
		int i = 0;
		stream << ++i << ":复位" << std::endl;
		stream << ++i << ":中断" << std::endl;
		stream << ++i << ":自检" << std::endl;
		stream << ++i << ":系统加载" << std::endl;
		stream << ++i << ":系统预位" << std::endl;
		stream << ++i << ":模式设置" << std::endl;
		stream << ++i << ":运行控制" << std::endl;
		stream << ++i << ":状态查询" << std::endl;
		stream << ++i << ":平台运动更新" << std::endl;
		stream << ++i << ":仿真事件发布" << std::endl;
		stream << ++i << ":平台惯导更新" << std::endl;
		stream << ++i << ":场景融合更新" << std::endl;
		std::cout << stream.str();
		break;
	}
		
	default:
		std::cout << "输入类型不对:" << a << std::endl;
		break;
	}
}
#endif