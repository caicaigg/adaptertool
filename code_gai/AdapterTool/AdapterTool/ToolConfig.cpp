#include "stdafx.h"
#include "ToolConfig.h"

#include <pugixml.hpp>

#include <DailyLog.h>



ToolConfig::ToolConfig()
	:_defaultFileName("AdapterToolConfig.config")
	, _bxcrecvport(0)
	, _bxcport(0)
	, _radarport(0)
	, _radarrecvport(0)
	, _bxcip("")
	, _radarip("")
{

}

ToolConfig::~ToolConfig()
{
	delete _mutex;
}


ToolConfig * ToolConfig::Instance()
{
	if (_my == nullptr)
	{
		_mutex->lock();
		if (_my == nullptr)
		{
			_my = new ToolConfig();
		}
		_mutex->unlock();
	}
	return _my;

}

bool ToolConfig::Initialize(std::string ConfigFilePath /*=""*/)
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

	pugi::xml_node conf_node = xdoc.select_single_node("ConfigItem").node();
	for (pugi::xml_node xnode = conf_node.first_child(); xnode != nullptr;
		xnode = xnode.next_sibling())
	{
		std::string valueName = xnode.name();
		if (valueName == "Radar")
		{
			pugi::xml_node ipnode = xnode.child("IP");
			pugi::xml_node portnode = xnode.child("Port");
			pugi::xml_node recvportnode = xnode.child("RecvPort");
			_radarip = ipnode.attribute("Value").value();
			_radarport = portnode.attribute("Value").as_int();
			_radarrecvport = recvportnode.attribute("Value").as_int();
		}
		else if (valueName == "BXC")
		{
			pugi::xml_node ipnode = xnode.child("IP");
			pugi::xml_node portnode = xnode.child("Port");
			pugi::xml_node recvportnode = xnode.child("RecvPort");
			_bxcip = ipnode.attribute("Value").value();
			_bxcport = portnode.attribute("Value").as_int();
			_bxcrecvport = recvportnode.attribute("Value").as_int();
		}
		else if (valueName == "BXC_UDP")
		{
			pugi::xml_node ipnode = xnode.child("IP");
			pugi::xml_node portnode = xnode.child("Port");
			pugi::xml_node recvportnode = xnode.child("RecvPort");
			_bxcudpip = ipnode.attribute("Value").value();
			_bxcudpport = portnode.attribute("Value").as_int();
			_bxcudprecvport = recvportnode.attribute("Value").as_int();
		}
		else if (valueName == "LoadFile")
		{
			pugi::xml_node scnnode = xnode.child("ScnFile");
			pugi::xml_node radarnode = xnode.child("RadarFile");
			pugi::xml_node mapnode = xnode.child("MapFile");
			_scnFilePath = scnnode.attribute("Value").value();
			_radarFilePath = radarnode.attribute("Value").value();
			_MapFilePath = mapnode.attribute("Value").value();
		}
		else if (valueName == "Map")
		{
			pugi::xml_node radarnode = xnode.child("Radar");
			pugi::xml_node bxcnode = xnode.child("BXC");
			_radarID = strtoul(radarnode.attribute("ID").value(), NULL, 0);
			_bxcID = strtoul(bxcnode.attribute("ID").value(), NULL, 0);
		}
		else if (valueName == "DDS")
		{
			_ddsvalue = xnode.attribute("Value").as_int();
		}
		else if (valueName == "TMPHeading")
		{
			_tmpHeading = xnode.attribute("Value").as_double();
		}
	}

	if (_radarip.empty()
		|| _bxcip.empty()
		|| _radarport == 0
		|| _bxcport == 0
		|| _ddsvalue == 0)
		return false;

	return true;
}

const std::string ToolConfig::GetRadarIPValue() const
{
	return _radarip;
}

const std::string ToolConfig::GetBXCIPValue() const
{
	return _bxcip;
}

const std::string ToolConfig::GetBXCUdpIPValue() const
{
	return _bxcudpip;
}

const int ToolConfig::GetRadarPortValue() const
{
	return _radarport;
}

const int ToolConfig::GetBXCPortValue() const
{
	return _bxcport;
}

const int ToolConfig::GetRecvRadarPortValue() const
{
	return _radarrecvport;
}

const int ToolConfig::GetRecvBXCPortValue() const
{
	return _bxcrecvport;
}

const int ToolConfig::GetBXCUdpPortValue() const
{
	return _bxcudpport;
}

const int ToolConfig::GetRecvBXCUdpPortValue() const
{
	return _bxcudprecvport;
}

const int ToolConfig::GetDDSValue() const
{
	return _ddsvalue;
}

const double ToolConfig::GetTmpHeading() const
{
	return _tmpHeading;
}

const int ToolConfig::GetPoxiRadarID() const
{
	return _radarID;
}

const int ToolConfig::GetPoxiBXCID() const
{
	return _bxcID;
}

const std::string ToolConfig::GetScnFilePath() const
{
	return _scnFilePath;
}

const std::string ToolConfig::GetRadarFilePath() const
{
	return _radarFilePath;
}

const std::string ToolConfig::GetMapFilePath() const
{
	return _MapFilePath;
}

ToolConfig * ToolConfig::_my = nullptr;
boost::mutex * ToolConfig::_mutex = new boost::mutex();

