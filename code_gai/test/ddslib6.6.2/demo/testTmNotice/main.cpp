#include <Windows.h>
#include "..\..\include\TimeMgr.h"
int main (int argc, char *argv[])
{
	//通知方式时间推进
	TimeMgr* myDDSTm = TimeMgr::GetInstancePtr();///<采用单例
	if(!myDDSTm->initMember(TMG_Notice))
		printf("初始化失败:%s\n",myDDSTm->getLastError().c_str());

	if(!myDDSTm->registerTimeStep(15))
		printf("登记仿真时间步长失败:%s\n",myDDSTm->getLastError().c_str());
	Sleep(1000);
	printf("开始仿真……\n");
	double curTm;
	while(true)
	{
		while (!myDDSTm->hasTimeAdvanced(curTm))
			Sleep(5);
		printf("current time:%8.3f\n", curTm);
		Sleep(5);
	}

	return 0;
}