#pragma once

#include <string>
#include <boost/thread.hpp>

class CRadarCore;
class CDDSCore;
class CBXCCore;
class CSceneResolution;
class CTestLvc;
class MessageDispatch;
class MessageReport;

//对象私有成员
struct ToolPrivate
{
	ToolPrivate();

	std::string _LastErr;
	CRadarCore * _radarIn;
	CDDSCore * _ddsIn;
	CBXCCore * _bxcIn;
	CSceneResolution * _scenIn;
	CTestLvc * _testLvc;
	MessageReport * _MsgReport;
	MessageDispatch * _MsgDispatch;


	boost::thread *_DDSDataThr;
	boost::thread *_TCPDataThr;
};

