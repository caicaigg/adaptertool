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
	std::cout << "���׼��" << std::endl;
	if (!ToolConfig::Instance()->Initialize())
	{
		std::cout << "toolconfig��ʼ��ʧ�ܣ�" << std::endl;
		return false;
	}
	if (!InitConfig::Instance()->Initialize())
	{
		std::cout << "initconfig��ʼ��ʧ�ܣ�" << std::endl;
		return false;
	}
	if (!CDataManager::DMFileLoadTransfer::Instance()->Initialize())
	{
		std::cout << "xml��ʼ��ȡ���ݴ���" << std::endl;
		return false;
	}
	if (!InitDDSIn())
	{
		std::cout << "DDS��ʼ��ʧ�ܣ�" << std::endl;
		return false;
	}
	if (!InitRadarIn())
	{
		std::cout << "radar��ʼ��ʧ�ܣ�" << std::endl;
		return false;
	}
	if (!InitBXCIn())
	{
		std::cout << "bxc��ʼ��ʧ�ܣ�" << std::endl;
		return false;
	}

	//
	_p->_MsgDispatch = new MessageDispatch(Radar(),BXC(),ScenResolution());
	_p->_MsgReport = new MessageReport(DDS(),const_cast<CRadarCore*>(Radar()));
	//���������߳�

	std::cout << "׼����ɣ�" << std::endl;
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
		//�·�����
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
		//�ϴ�����
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
		stream << ++i << ":��λ" << std::endl;
		stream << ++i << ":�ж�" << std::endl;
		stream << ++i << ":�Լ�" << std::endl;
		stream << ++i << ":ϵͳ����" << std::endl;
		stream << ++i << ":ϵͳԤλ" << std::endl;
		stream << ++i << ":ģʽ����" << std::endl;
		stream << ++i << ":���п���" << std::endl;
		stream << ++i << ":״̬��ѯ" << std::endl;
		stream << ++i << ":ƽ̨�˶�����" << std::endl;
		stream << ++i << ":�����¼�����" << std::endl;
		stream << ++i << ":ƽ̨�ߵ�����" << std::endl;
		stream << ++i << ":�����ںϸ���" << std::endl;
		std::cout << stream.str();
		break;
	}
		
	default:
		std::cout << "�������Ͳ���:" << a << std::endl;
		break;
	}
}
#endif