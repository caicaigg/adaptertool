#pragma once
#include "DailyLogGlobal.h"
#include <string>
//#include <mutex>
#include <boost/thread/mutex.hpp>
#include "Util.h"

//默认路径 ./lvclog.txt
#define _LOG(str) \
	DailyLog::Instance()->LogOften(str)

#define _LOG_FILE(file,str) \
	DailyLog::Instance()->LogOnce(file,str)

class DAILYLOGIN_DECL DailyLog
{
private:
	DailyLog();
public:
	virtual ~DailyLog();

public:
	static DailyLog * Instance();

public:
	//立即写文件，和窗口输出
	void LogOnce(std::string FilePath,std::string log);

	//同一接口里，调用频繁
	void LogOften(std::string log);



private:
	void WriteFile(std::string log);
	void PrintfLog(std::string log);

	Util *_defaultLog;

	static DailyLog *_Log;
	static boost::mutex* _mutex;
};

