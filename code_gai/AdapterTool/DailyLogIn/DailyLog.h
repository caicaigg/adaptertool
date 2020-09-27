#pragma once
#include "DailyLogGlobal.h"
#include <string>
//#include <mutex>
#include <boost/thread/mutex.hpp>
#include "Util.h"

//Ĭ��·�� ./lvclog.txt
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
	//����д�ļ����ʹ������
	void LogOnce(std::string FilePath,std::string log);

	//ͬһ�ӿ������Ƶ��
	void LogOften(std::string log);



private:
	void WriteFile(std::string log);
	void PrintfLog(std::string log);

	Util *_defaultLog;

	static DailyLog *_Log;
	static boost::mutex* _mutex;
};

