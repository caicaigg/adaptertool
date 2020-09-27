#pragma once

#include <string>
#include <boost/thread/mutex.hpp>

#include "Define.h"



//初始化配置文件信息 wujl
class InitConfig
{
public:
	~InitConfig();
protected:
	InitConfig();

public:
	static InitConfig * Instance();
	bool Initialize(std::string ConfigFilePath = "");

	const CENTER2RADAR_INIT & GetRadarInfo() const;
private:
	int strtoint(const char* str);
private:
	static InitConfig * _config;
	static boost::mutex * _mutex;
	std::string _defaultFileName;

private:

	CENTER2RADAR_INIT _init;
};
