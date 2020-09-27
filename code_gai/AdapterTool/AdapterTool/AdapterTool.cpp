// AdapterTool.cpp : �������̨Ӧ�ó������ڵ㡣
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
		std::cout << __FILE__ << __LINE__ << ";�쳣����" << e.what() << std::endl;
		_LOG(e.what());
		system("pause");
	}
	
    return 0;
}

