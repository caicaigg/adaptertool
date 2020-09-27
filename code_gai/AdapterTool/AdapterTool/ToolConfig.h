#pragma once

#include <string>
#include <boost/thread/mutex.hpp>



class ToolConfig
{
public:
	~ToolConfig();
protected:
	ToolConfig();

public:
	static ToolConfig * Instance();
	bool Initialize(std::string ConfigFilePath = "");

	const std::string GetRadarIPValue() const;
	const std::string GetBXCIPValue() const;
	const std::string GetBXCUdpIPValue() const;
	const int GetRadarPortValue() const;
	const int GetBXCPortValue() const;
	const int GetRecvRadarPortValue() const;
	const int GetRecvBXCPortValue() const;
	const int GetBXCUdpPortValue() const;
	const int GetRecvBXCUdpPortValue() const;
	const int GetDDSValue() const;
	
	const double GetTmpHeading() const;

	const int GetPoxiRadarID() const;
	const int GetPoxiBXCID() const;

	const std::string GetScnFilePath() const;
	const std::string GetRadarFilePath() const;
	const std::string GetMapFilePath() const;
private:
	static ToolConfig * _my;
	static boost::mutex * _mutex;
	std::string _defaultFileName;

private:
	std::string _bxcip;
	std::string _bxcudpip;
	std::string _radarip;

	std::string _scnFilePath;
	std::string _radarFilePath;
	std::string _MapFilePath;

	int _radarID;
	int _bxcID;

	int _bxcport;
	int _bxcrecvport;
	int _bxcudpport;
	int _bxcudprecvport;
	int _radarport;
	int _radarrecvport;
	int _ddsvalue;

	double _tmpHeading;
};


