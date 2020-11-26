#include "stdafx.h"
#include "DataManager.h"

#include <boost/foreach.hpp>
#include <boost\exception\all.hpp>
#include <pugixml.hpp>

using namespace CDataManager;

DMFileLoadTransfer::DMFileLoadTransfer()
{
}

DMFileLoadTransfer::~DMFileLoadTransfer()
{
}

bool CDataManager::DMFileLoadTransfer::Initialize()
{
	bool flag = false;

	TransferMapFile(ToolConfig::Instance()->GetMapFilePath());

	TransferScenaioFile(ToolConfig::Instance()->GetScnFilePath());

	TransferRadarFile(ToolConfig::Instance()->GetRadarFilePath());

	flag = CheckInfos();

	return flag;
}

void CDataManager::DMFileLoadTransfer::TransferScenaioFile(std::string ScnFile)
{
	if (ScnFile.empty())
	{
		ScnFile = "Scn_0000_0214.xml";
	}

	std::string allfilename(ScnFile);

	pugi::xml_document xdoc;
	pugi::xml_parse_result loadret = xdoc.load_file(allfilename.c_str());
	if (loadret.status != pugi::status_ok)
	{
		_LOG(std::string(allfilename) + "配置文件打开失败！");
		return;
	}

	memset(&_scn._Sceninfo, 0, sizeof(LVCScenBaseInfo));
	_scn._Entitylist.clear();

	pugi::xml_node scn_node = xdoc.select_single_node("Scenario").node();
	pugi::xml_node conf_node = scn_node.select_single_node("MilEntList").node();
	for (pugi::xml_node xnode = conf_node.first_child(); xnode != nullptr;
		xnode = xnode.next_sibling())
	{
		std::string valueName = xnode.name();
		if (valueName == "MilEnt")
		{
			int tmp = 0;
			LVCEntityInfo ett;
			
			ett.id = strtoul(xnode.attribute("id").value(), NULL, 0);
			ett.name.assign(xnode.attribute("name").value());

			ett.initState.lon = xnode.child("InitInfo").attribute("lon").as_double();
			ett.initState.lat = xnode.child("InitInfo").attribute("lat").as_double();
			ett.initState.alt = xnode.child("InitInfo").attribute("alt").as_double();
			ett.initState.Heading = xnode.child("InitInfo").attribute("yaw").as_double();
			ett.initState.pitch = xnode.child("InitInfo").attribute("pitch").as_double();
			ett.initState.roll = xnode.child("InitInfo").attribute("roll").as_double();
			ett.initState.speed = xnode.child("InitInfo").attribute("spd").as_double();

			//雷达装备
			pugi::xml_node eq_node = xnode.select_single_node("EquipList").node();
			for (pugi::xml_node eqnode = eq_node.first_child(); eqnode != nullptr;
				eqnode = eqnode.next_sibling())
			{
				EquipInfo equip;
				equip.id = eqnode.attribute("EntId").as_int();
				ett.equipList.push_back(equip);
			}

			_scn._Entitylist.push_back(ett);
// 			_radarip = ipnode.attribute("Value").value();
// 			_radarport = portnode.attribute("Value").as_int();
// 			_radarrecvport = recvportnode.attribute("Value").as_int();
		}
	}

}

void CDataManager::DMFileLoadTransfer::TransferRadarFile(std::string RadarFile)
{
	if (RadarFile.empty())
	{
		RadarFile = "Rds_0000_0009.xml";
	}

	std::string allfilename(RadarFile);

	pugi::xml_document xdoc;
	pugi::xml_parse_result loadret = xdoc.load_file(allfilename.c_str());
	if (loadret.status != pugi::status_ok)
	{
		_LOG(std::string(allfilename) + "配置文件打开失败！");
		return;
	}


	pugi::xml_node root_node = xdoc.select_single_node("Root").node();
	for (pugi::xml_node xnode = root_node.first_child(); xnode != nullptr;
		xnode = xnode.next_sibling())
	{
		RadarInfo radar;
		std::string valueName = xnode.name();
		if (valueName == "RdsInst")
		{
			radar.id = strtoul(xnode.attribute("id").value(), NULL, 0);
			radar.name.assign(xnode.attribute("name").value());
			//radar.desc.assign(xnode.attribute("desc").value());

			pugi::xml_node atn_node = xnode.select_single_node("AtnAchParam").node();
			AtnAchParam atnachparam;
			atnachparam.atnArrayID = atn_node.attribute("x").as_int();

			for (pugi::xml_node xatnnode = atn_node.first_child(); xatnnode != nullptr;
				xatnnode = xatnnode.next_sibling())
			{
				antennal ant;

				ant.x = xatnnode.attribute("x").as_double();
				ant.y = xatnnode.attribute("y").as_double();
				ant.z = xatnnode.attribute("z").as_double();
				ant.heading = xatnnode.attribute("yaw").as_double();
				ant.pitch = xatnnode.attribute("pitch").as_double();
				ant.roll = xatnnode.attribute("roll").as_double();

				radar.AtnAchParamList.params.push_back(ant);
			}

			//
			pugi::xml_node init_node = xnode.select_single_node("InitConfig").node();
			
			_ModeID = strtoul( init_node.attribute("modeID").value(), NULL, 0);
			_startTM = strtoul(init_node.attribute("startTM").value(), NULL, 0);

			_radar = radar;
			break;
		}
	}
}

void CDataManager::DMFileLoadTransfer::TransferMapFile(std::string MapFile)
{
	if (MapFile.empty())
	{
		MapFile = "Map_0000_0214.xml";
	}

	std::string allfilename(MapFile);

	pugi::xml_document xdoc;
	pugi::xml_parse_result loadret = xdoc.load_file(allfilename.c_str(),pugi::parse_default,pugi::encoding_utf8);
	if (loadret.status != pugi::status_ok)
	{
		_LOG(std::string(allfilename) + "配置文件打开失败！");
		return;
	}

	_entityMap.clear();

	pugi::xml_node scn_node = xdoc.select_single_node("Root").node();
	pugi::xml_node conf_node = scn_node.select_single_node("MilEntList").node();
	for (pugi::xml_node xnode = conf_node.first_child(); xnode != nullptr;
		xnode = xnode.next_sibling())
	{
		std::string valueName = xnode.name();
		if (valueName == "MilEnt")
		{
			LVCEntityMapInfo EttMap;
			EttMap.id = strtoul(xnode.attribute("id").value(), NULL, 0);
			char buf[100] = { "" };
			std::wstring str;
			memcpy(buf,xnode.attribute("name").value(),100);
			EttMap.name.assign(xnode.attribute("name").value());
			
			//std::cout << EttMap.name << std::endl;
			//radar.desc.assign(xnode.attribute("desc").value());

			pugi::xml_node equipList_node = xnode.select_single_node("MappingList").node();
			for (pugi::xml_node equip_node = equipList_node.first_child(); equip_node != nullptr;
				equip_node = equip_node.next_sibling())
			{
				MapEquip equip;

				equip.subid = strtoul(equip_node.attribute("subSysId").value(),NULL,0);
				equip.subname.assign(equip_node.attribute("subSysName").value());
				equip.subtype = equip_node.attribute("subSysType").as_int();
				equip.desc.assign(equip_node.attribute("desc").value());

				EttMap.MapQuipList.push_back(equip);
			}

			_entityMap.push_back(EttMap);
		}
	}
}

bool CDataManager::DMFileLoadTransfer::CheckInfos()
{
	if (!checkRadarEntity() || !checkTargetEntity())
	{
		return false;
	}
}

bool CDataManager::DMFileLoadTransfer::checkRadarEntity()
{
	int poxiradarID = ToolConfig::Instance()->GetPoxiRadarID();
	int radarettid = 0;
	int RadarNumber = 0;
	BOOST_FOREACH(auto it, _entityMap)
	{
		BOOST_FOREACH(auto equip, it.MapQuipList)
		{
			if (equip.subid == poxiradarID)
			{
				radarettid = it.id;
				++RadarNumber;
			}
		}
	}
	if (RadarNumber > 1)
	{
		std::cout << "Map文件中有多个Radarid" << ";id号：" << poxiradarID << std::endl;
	}

	int RadarNumbertmp = 0;
	for (int i = 0; i < _scn._Entitylist.size(); ++i)
	{
		if (_scn._Entitylist[i].id == radarettid)
		{
			_RadarEntity = _scn._Entitylist[i];
			++RadarNumbertmp;
		}
	}
	if (RadarNumbertmp > 1)
	{
		std::cout << "Scn文件中雷达id有重复！" << std::endl;
	}

	if (1 == RadarNumber && 1 == RadarNumbertmp)
	{
		return true;
	}

	return false;
}

bool CDataManager::DMFileLoadTransfer::checkTargetEntity()
{
	int poxibxcID = ToolConfig::Instance()->GetPoxiBXCID();
	int bxcettid = 0;
	int bxcNumber = 0;

	_TargetList.clear();

	BOOST_FOREACH(auto it, _entityMap)
	{
		BOOST_FOREACH(auto equip, it.MapQuipList)
		{
			if (equip.subid == poxibxcID)
			{
				bxcettid = it.id;
				++bxcNumber;

				int bxcNumbertmp = 0;
				for (int i = 0; i < _scn._Entitylist.size(); ++i)
				{
					if (_scn._Entitylist[i].id == bxcettid)
					{
						_TargetList.push_back(_scn._Entitylist[i]);
						++bxcNumbertmp;
					}
				}

				if (bxcNumbertmp > 1)
				{
					std::cout << "Scn文件中目标id有重复！" << std::endl;
				}
			}
		}
	}

	if (!_TargetList.empty())
	{
		return true;
	}

	return false;
}

const LVCScenarioFile & CDataManager::DMFileLoadTransfer::GetScenarioInfo() const
{
	return _scn;
}

const RadarInfo& CDataManager::DMFileLoadTransfer::GetRadarsInfo() const
{
	//Q 数据完整性应该没有考虑好，这些判断没意义
	bool flag = false;
	for (size_t i = 0; i < _RadarEntity.equipList.size(); i++)
	{
		if (_radar.id == _RadarEntity.equipList[i].id)
		{
			flag = true;
			break;
		}
	}

	if (!flag)
	{
		std::cout << "GetRadarsInfo()，没有获取正确的数据！" << std::endl;
	}
	
	return _radar;
}

const LVCEntityMapInfoVec & CDataManager::DMFileLoadTransfer::GetMapInfo() const
{
	return _entityMap;
}

int CDataManager::DMFileLoadTransfer::GetModeID()
{
	return _ModeID;
}

int CDataManager::DMFileLoadTransfer::GetStartTM()
{
	return _startTM;
}

bool DMFileLoadTransfer::GetRadarEntity(LVCEntityInfo & EntityInfo)
{
	//
	if (-1 != _RadarEntity.id )
	{
		EntityInfo = _RadarEntity;
		return true;
	}
	return false;
}

bool DMFileLoadTransfer::GetTargetEntity(std::vector<LVCEntityInfo> & EntityInfoList)
{
	if (!_TargetList.empty())
	{
		for (int i = 0; i < _TargetList.size(); ++i)
		{
			EntityInfoList.push_back(_TargetList[i]);
		}
		
		return true;
	}

	return false;
}

DMSceneResolution::DMSceneResolution()
{
}

DMSceneResolution::~DMSceneResolution()
{
}

const double CDataManager::DMSceneResolution::GetAlphaValue() const
{
	return _alpha;
}

void CDataManager::DMSceneResolution::SetAlphaValue(double Alpha)
{
	_alpha = Alpha;
}

void CDataManager::DMSceneResolution::SetData(const TPC_ScnPlatUpdate& plat)
{
	_mutex.lock();
	if (_Queue.size() < 500)
	{
		_Queue.push(plat);
	}
	else
	{
		_LOG("DMSceneResolution Queue size > 500!");
	}
	_mutex.unlock();

	//_UpdataSemaphore->post();
}

const TPC_ScnPlatUpdate CDataManager::DMSceneResolution::GetData()
{
	_tlock lock(_mutex);

	TPC_ScnPlatUpdate base;
	memset(&base, 0, sizeof(TPC_ScnPlatUpdate));
	if (_Queue.size() >= 1)
	{
		base = _Queue.front();

		//if (_Queue.size() > 1)
		//{
			_Queue.pop();
		//}
	}
	//获取数据后，数据所有权就交给获取数据的模块，出现异常，由获取模块处理

	return base;
}

const TPC_ScnPlatUpdate CDataManager::DMSceneResolution::GetData_forLook()
{
	_tlock lock(_mutex);

	TPC_ScnPlatUpdate base;
	memset(&base, 0, sizeof(TPC_ScnPlatUpdate));
	if (_Queue.size() >= 1)
	{
		base = _Queue.front();

	}
	//获取数据后，数据所有权就交给获取数据的模块，出现异常，由获取模块处理

	return base;
}

bool CDataManager::DMSceneResolution::tryGetData()
{
	if (_Queue.size() > 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void CDataManager::DMSceneResolution::ReleaseCmd(int no)
{
	for (int i = 0; i < no; ++i)
		_UpdataSemaphore->post();
}

void CDataManager::DMSceneResolution::WaitCmd(int ns /*=0*/)
{
	if (ns != 0)
	{
		boost::posix_time::ptime time = boost::posix_time::microsec_clock::local_time();
		_UpdataSemaphore->timed_wait(time + boost::posix_time::milliseconds(ns));
	}
	else
	{
		do
		{
			boost::posix_time::ptime time = boost::posix_time::microsec_clock::local_time();
			bool rs = _UpdataSemaphore->timed_wait(time + boost::posix_time::milliseconds(50));
			if (rs) //false: time out; true: posted;
			{
				break;
			}
			//_CmdSemaphore->wait();
		} while (1);

	}
}






DMNetworkInfo::DMNetworkInfo()
{
}

DMNetworkInfo::~DMNetworkInfo()
{
}







DDSQueueData::DDSQueueData()
	:_ReleaseForce(false)
	, _rdyRequestbackFlag(false)
	, TPC_SysRdyNotify_tcpfunc_rs(0)
{
	//_CmdSemaphore = CreateSemaphoreA(NULL, 0, 100, NULL);
	//_DataSemaphore = CreateSemaphoreA(NULL, 0, 100, NULL);
	_CmdSemaphore = new boost::interprocess::interprocess_semaphore(0);
	_RdyRequestSemaphore = new boost::interprocess::interprocess_semaphore(0);
}

DDSQueueData::~DDSQueueData()
{

}

bool CDataManager::DDSQueueData::Initialize()
{
	_ddsmutex.lock();

	//0
	_Queue.swap(std::queue<BaseTypePtr>());


	if (_CmdSemaphore)
	{
		// 初始为0
		while (_CmdSemaphore->try_wait())
		{
			_CmdSemaphore->wait();
		}

		//释放正所有等待的信号量(这里没有必要处理这个逻辑!)
		//ReleaseSpForce();
	}

	_ddsmutex.unlock();
	return true;
}

void CDataManager::DDSQueueData::Stop()
{
	//使所有信号量post 失效，不再增加信号量值，
	//数据量大的临界值，报警，或者让push 失效，不再继续插入
	//停止()的作用，让set可以继续，但是不再能get数据，达到中断程序的效果

}

boost::interprocess::interprocess_semaphore * CDataManager::DDSQueueData::GetRdyRequestSemaphore()
{
	return _RdyRequestSemaphore;
}

bool CDataManager::DDSQueueData::WaitRdyRequest(int times)
{
// 	boost::posix_time::ptime time = boost::posix_time::microsec_clock::local_time();
// 	bool rs = _RdyRequestSemaphore->timed_wait(time + boost::posix_time::milliseconds(times));


	return _rdyRequestbackFlag;
}

void CDataManager::DDSQueueData::ReleaseRdyRequest()
{
	_rdyRequestbackFlag = true;
}

int CDataManager::DDSQueueData::GetTPC_SysRdyNotify_tcpfunc_rs()
{
	return TPC_SysRdyNotify_tcpfunc_rs;
}

void CDataManager::DDSQueueData::SetTPC_SysRdyNotify_tcpfunc_rs(int rs)
{
	TPC_SysRdyNotify_tcpfunc_rs = rs;
}

void DDSQueueData::SetData(const BaseTypePtr Base)
{
	_ddsmutex.lock();
	
	//_Queue.push(boost::const_pointer_cast<DataTypeBase>(Base));
	if (_Queue.size() < 500)
	{
		_Queue.push(Base);
	}
	else
	{
		_LOG("DDSQueueData Queue size > 500!");
	}

	_ddsmutex.unlock();

	//释放
	_CmdSemaphore->post();
}

const BaseTypePtr DDSQueueData::GetData()
{
	_ddsmutex.lock();

	BaseTypePtr  base = nullptr;
	if (_Queue.size() >= 1)
	{
		base = _Queue.front();
		//DataTypeBaseptr base = _Queue.front();
		//获取数据后，数据所有权就交给获取数据的模块，出现异常，由获取模块处理
		_Queue.pop();
	}

	_ddsmutex.unlock();
	return base;
}

void DDSQueueData::ReleaseCmd(int no)
{
	for(int i = 0; i < no;++i)
		_CmdSemaphore->post();
}

void DDSQueueData::WaitCmd(int ns)
{
	if (ns != 0)
	{
		boost::posix_time::ptime time = boost::posix_time::microsec_clock::local_time();
		_CmdSemaphore->timed_wait(time+boost::posix_time::milliseconds(ns));
	}
	else
	{
		//一直等待 wait() 
		do
		{
			//sem_exception
			boost::posix_time::ptime time = boost::posix_time::microsec_clock::local_time();
			bool rs = _CmdSemaphore->timed_wait(time + boost::posix_time::milliseconds(50));
			if (rs || _ReleaseForce) //false: time out; true: posted;
			{
				break;
			}
			//_CmdSemaphore->wait();
		} while (1);
		
	}
		
}

void DDSQueueData::ReleaseSpForce()
{
	_ReleaseForce = true;
}




TCPQueueData::TCPQueueData()
{
	_TCPSemaphore = new boost::interprocess::interprocess_semaphore(0);
}

TCPQueueData::~TCPQueueData()
{

}

void CDataManager::TCPQueueData::SetData(const buffer_type & Buffer)
{
	_tcpmutex.lock();
	if (_Queue.size() < 500)
	{
		_Queue.push(Buffer);
	}
	else
	{
		_LOG("TCPQueueData Queue size > 500!");
	}
	_tcpmutex.unlock();

	_TCPSemaphore->post();
}

const buffer_type CDataManager::TCPQueueData::GetData()
{
	_tcplock lock(_tcpmutex);

	buffer_type base;
	if (_Queue.size() >= 1)
	{
		base = _Queue.front();
		//获取数据后，数据所有权就交给获取数据的模块，出现异常，由获取模块处理
		_Queue.pop();
	}


	return base;
}

void CDataManager::TCPQueueData::ReleaseCmd(int no)
{
	for (int i = 0; i < no; ++i)
		_TCPSemaphore->post();
}

void CDataManager::TCPQueueData::WaitCmd(int ns /*=0*/)
{
	if (ns != 0)
	{
		boost::posix_time::ptime time = boost::posix_time::microsec_clock::local_time();
		_TCPSemaphore->timed_wait(time + boost::posix_time::milliseconds(ns));
	}
	else
	{
		do
		{
			boost::posix_time::ptime time = boost::posix_time::microsec_clock::local_time();
			bool rs = _TCPSemaphore->timed_wait(time + boost::posix_time::milliseconds(50));
			if (rs) //false: time out; true: posted;
			{
				break;
			}
			//_CmdSemaphore->wait();
		} while (1);

	}
}

void CDataManager::TCPQueueData::SetAgilityType(int RadarID, int state)
{
	std::map<int, int>::iterator it = _AgilityMap.find(RadarID);
	if (it != _AgilityMap.end())
	{
		it->second = state;
	}
	else
	{
		_AgilityMap.insert(std::pair<int, int>(RadarID, state));
	}
}

int CDataManager::TCPQueueData::GetAgilityType(int RadarID)
{
	std::map<int, int>::iterator it = _AgilityMap.find(RadarID);
	if (it != _AgilityMap.end())
	{
		return it->second;
	}
	return -1;
}

void CDataManager::TCPQueueData::SetBeamValue(int RadarID, int value)
{
	std::map<int, int>::iterator it = _BeamValueMap.find(RadarID);
	if (it != _BeamValueMap.end())
	{
		it->second = value;
	}
	else
	{
		_BeamValueMap.insert(std::pair<int, int>(RadarID, value));
	}
}

int CDataManager::TCPQueueData::GetBeamValue(int RadarID)
{
	std::map<int, int>::iterator it = _BeamValueMap.find(RadarID);
	if (it != _BeamValueMap.end())
	{
		return it->second;
	}
	return -1;
}
