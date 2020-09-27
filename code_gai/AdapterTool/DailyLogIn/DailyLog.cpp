#include "DailyLog.h"
#include "Util.h"
#include "LogDebug.h"


DailyLog::DailyLog()
	:_defaultLog(nullptr)
{
}


DailyLog::~DailyLog()
{
	delete _defaultLog;
	_defaultLog = nullptr;
}

DailyLog * DailyLog::Instance()
{
	if (_Log == nullptr)
	{
		_mutex->lock();
		if (_Log == nullptr)
		{
			_Log = new DailyLog;
		}
		_mutex->unlock();
	}
	return _Log;
}

void DailyLog::LogOnce(std::string FilePath, std::string log)
{
#ifdef LOG_W_FILE
	Util util(FilePath);
	util.Stream()<<log.c_str();
	//util.cout() << log.c_str();
	//std::cout << log.c_str();
#endif
}

void DailyLog::LogOften(std::string log)
{
#ifdef LOG_W_FILE
	if (_defaultLog)
	{
		_defaultLog->Stream() << log.c_str();
		//(*_defaultLog) << log;
		//std::cout << log.c_str() <<std::endl;
	}
	else
	{
		_defaultLog = new Util("lvclog.txt");
		_defaultLog->Stream() << log.c_str();
		std::cout << log.c_str() <<std::endl;
	}
#endif
}

void DailyLog::WriteFile(std::string log)
{

}

void DailyLog::PrintfLog(std::string log)
{
}


DailyLog* DailyLog::_Log = nullptr;
boost::mutex* DailyLog::_mutex = new boost::mutex;