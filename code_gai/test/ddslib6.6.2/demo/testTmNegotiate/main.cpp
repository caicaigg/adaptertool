#include <Windows.h>
//#include "..\..\include\ddslib.h"
#include "..\..\include\TimeMgr.h"

int main (int argc, char *argv[])
{
	//通知方式时间推进
	TimeMgr* myDDSTm = TimeMgr::GetInstancePtr();///<采用单例
	myDDSTm->initMember(TMG_Negotiate);
	double curTime,step=1;
	if(!myDDSTm->registerFederate(curTime))
	{
		printf("注册邦员失败:%s\n",myDDSTm->getLastError().c_str());
		return 0;
	}
	Sleep(1000);
	printf("开始仿真……\n");
	//double curTm;
	int i = 100;
	while(i--)
	{
		if(!myDDSTm->RequestTimeAdvance(curTime+step))
		{
			printf("请求时间推进失败:%s",myDDSTm->getLastError().c_str());
			return 0;
		}
		while (!myDDSTm->hasTimeAdvanced(curTime))
			Sleep(5);
		printf("current time:%8.3f\n",curTime);
		//if (getchar() == 'q')
		//	break;

		Sleep(5);
	}
	myDDSTm->unregister();
	Sleep(500);
	return 0;
}