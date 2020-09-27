// AdapterTool.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "Tool.h"
#include "OwnException.h"

#include <iostream>
#include <DailyLog.h>

int main()
{
	try
	{
		CTool tool;
		tool.Initialize();
		tool.run();
	}
	catch (const OwnException& e)
	{
		std::cout << __FILE__ << __LINE__ << ";异常错误：" << e.what() << std::endl;
		_LOG(e.what());
		system("pause");
	}
	
    return 0;
}

