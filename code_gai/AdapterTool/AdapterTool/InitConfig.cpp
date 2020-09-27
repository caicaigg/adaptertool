#include "stdafx.h"
#include "InitConfig.h"

#include <pugixml.hpp>
#include <DailyLog.h>


InitConfig::InitConfig()
	:_defaultFileName("RadarInitInfo.config")
{
	memset(&_init, 0, sizeof(CENTER2RADAR_INIT));
}

InitConfig::~InitConfig()
{
	delete _mutex;
}

InitConfig * InitConfig::Instance()
{
	if (_config == nullptr)
	{
		_mutex->lock();
		if (_config == nullptr)
		{
			_config = new InitConfig();
		}
		_mutex->unlock();
	}
	return _config;

}


bool InitConfig::Initialize(std::string ConfigFilePath /*=""*/)
{
	if (ConfigFilePath.empty())
	{
		ConfigFilePath = _defaultFileName;
	}

	std::string allfilename;
	allfilename.append("config\\");
	allfilename.append(ConfigFilePath);

	pugi::xml_document xdoc;
	pugi::xml_parse_result loadret = xdoc.load_file(allfilename.c_str());
	if (loadret.status != pugi::status_ok)
	{
		_LOG("配置文件打开失败！");
		return false;
	}

	pugi::xml_node conf_node = xdoc.select_single_node("InitInfo").node();
	pugi::xml_node radar_node = conf_node.select_single_node("Radar").node();

	if (radar_node)
	{
		if (pugi::xml_node xnode = radar_node.child("ucStart"))
		{
			_init.ucStart = strtoint(xnode.child_value());
		}
		if (pugi::xml_node xnode = radar_node.child("usPscCtrl"))
		{
			_init.usPscCtrl = strtoint(xnode.child_value());
		}
		if (pugi::xml_node xnode = radar_node.child("disCmdDbf"))
		{
			_init.disCmdDbf = strtoint(xnode.child_value());
		}
		if (pugi::xml_node xnode = radar_node.child("disCmdDbfNum"))
		{
			_init.disCmdDbfNum = strtoint(xnode.child_value());
		}
		if (pugi::xml_node xnode = radar_node.child("disCmdShadow"))
		{
			_init.disCmdShadow = strtoint(xnode.child_value());
		}
		if (pugi::xml_node xnode = radar_node.child("auxShadowB"))
		{
			_init.auxShadowB = strtoint(xnode.child_value());
		}
		if (pugi::xml_node xnode = radar_node.child("disCmdPower"))
		{
			_init.disCmdPower = strtoint(xnode.child_value());
		}
		if (pugi::xml_node xnode = radar_node.child("disCmdMutiFake"))
		{
			_init.disCmdMutiFake = strtoint(xnode.child_value());
		}
		if (pugi::xml_node xnode = radar_node.child("ucMode"))
		{
			_init.ucMode = strtoint(xnode.child_value());
		}
		if (pugi::xml_node xnode = radar_node.child("ucMainPulseFrq"))
		{
			_init.ucMainPulseFrq = strtoint(xnode.child_value());
		}
		if (pugi::xml_node xnode = radar_node.child("ucFtCvrPulseFrq"))
		{
			_init.ucFtCvrPulseFrq = strtoint(xnode.child_value());
		}
		if (pugi::xml_node xnode = radar_node.child("ucBkCvrPulseFrq"))
		{
			_init.ucBkCvrPulseFrq = strtoint(xnode.child_value());
		}
		if (pugi::xml_node xnode = radar_node.child("usMainWaveCode"))
		{
			_init.usMainWaveCode = strtoint(xnode.child_value());
		}
		if (pugi::xml_node xnode = radar_node.child("ucFtCvrCtrl"))
		{
			_init.ucFtCvrCtrl = strtoint(xnode.child_value());
		}
		if (pugi::xml_node xnode = radar_node.child("ucBkCvrCtrl"))
		{
			_init.ucBkCvrCtrl = strtoint(xnode.child_value());
		}
		if (pugi::xml_node xnode = radar_node.child("ucFtCvrDirCtrl"))
		{
			_init.ucFtCvrDirCtrl = strtoint(xnode.child_value());
		}
		if (pugi::xml_node xnode = radar_node.child("ucBkCvrDirCtrl"))
		{
			_init.ucBkCvrDirCtrl = strtoint(xnode.child_value());
		}
		if (pugi::xml_node xnode = radar_node.child("usFtCvrIntvl"))
		{
			_init.usFtCvrIntvl = strtoint(xnode.child_value());
		}
		if (pugi::xml_node xnode = radar_node.child("usBkCvrIntvl"))
		{
			_init.usBkCvrIntvl = strtoint(xnode.child_value());
		}
		if (pugi::xml_node xnode = radar_node.child("usFtCvrWaveCode"))
		{
			_init.usFtCvrWaveCode = strtoint(xnode.child_value());
		}
		if (pugi::xml_node xnode = radar_node.child("usBkCvrWaveCode"))
		{
			_init.usBkCvrWaveCode = strtoint(xnode.child_value());
		}
		if (pugi::xml_node xnode = radar_node.child("uiFtCvrA"))
		{
			_init.uiFtCvrA = strtoint(xnode.child_value());
		}
		if (pugi::xml_node xnode = radar_node.child("iFtCvrE"))
		{
			_init.iFtCvrE = strtoint(xnode.child_value());
		}
		if (pugi::xml_node xnode = radar_node.child("uiBkCvrA"))
		{
			_init.uiBkCvrA = strtoint(xnode.child_value());
		}
		if (pugi::xml_node xnode = radar_node.child("iBkCvrE"))
		{
			_init.iBkCvrE = strtoint(xnode.child_value());
		}
		if (pugi::xml_node xnode = radar_node.child("ucPassFollow"))
		{
			_init.ucPassFollow = strtoint(xnode.child_value());
		}
		if (pugi::xml_node xnode = radar_node.child("ucSectorEf0"))
		{
			_init.ucSectorEf[0] = strtoint(xnode.child_value());
		}
		if (pugi::xml_node xnode = radar_node.child("ucSectorEf1"))
		{
			_init.ucSectorEf[1] = strtoint(xnode.child_value());
		}

		pugi::xml_node stSector_node = radar_node.child("stSector");
		int sectori = 0;
		for (pugi::xml_node xnode = stSector_node.first_child(); xnode != nullptr;
			xnode = xnode.next_sibling(),++sectori)
		{
			_init.stSector[sectori].usStartA = strtoint(xnode.child("usStartA").child_value());
			_init.stSector[sectori].usEndA = strtoint(xnode.child("usEndA").child_value());
			_init.stSector[sectori].usStartE = strtoint(xnode.child("usStartE").child_value());
			_init.stSector[sectori].usEndE = strtoint(xnode.child("usEndE").child_value());
		}

		if (pugi::xml_node xnode = radar_node.child("disCmdAsync"))
		{
			_init.disCmdAsync = strtoint(xnode.child_value());
		}
		if (pugi::xml_node xnode = radar_node.child("ucSearchArea1"))
		{
			_init.ucSearchArea1 = strtoint(xnode.child_value());
		}
		if (pugi::xml_node xnode = radar_node.child("ucSearchArea2"))
		{
			_init.ucSearchArea2 = strtoint(xnode.child_value());
		}

		pugi::xml_node seach_node = radar_node.child("SEARCH_AREA_DATA");
		int seachi = 0;
		for (pugi::xml_node xnode = seach_node.first_child(); xnode != nullptr;
			xnode = xnode.next_sibling(),++seachi)
		{
			_init.stSearchAreaData[seachi].usStartA = strtoint(xnode.child("usStartA").child_value());
			_init.stSearchAreaData[seachi].usEndA = strtoint(xnode.child("usEndA").child_value());
			_init.stSearchAreaData[seachi].usStartE = strtoint(xnode.child("usStartE").child_value());
			_init.stSearchAreaData[seachi].usEndE = strtoint(xnode.child("usEndE").child_value());
		}
	}

	return true;
}



const CENTER2RADAR_INIT & InitConfig::GetRadarInfo() const
{
	return _init;
}

int InitConfig::strtoint(const char* str)
{
	
	try
	{
		if (nullptr == str)
		{
			throw;
		}
		int tmpi = strtoul(str, nullptr, 0);

		return tmpi;
	}
	catch (...)
	{
		return -1;
	}

}

InitConfig * InitConfig::_config = nullptr;
boost::mutex * InitConfig::_mutex = new boost::mutex();
