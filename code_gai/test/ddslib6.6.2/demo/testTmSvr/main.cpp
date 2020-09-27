#include <Windows.h>
//#include "ddslib.h"
#include "TimeMgr.h"
#include <conio.h>

int main (int argc, char *argv[])
{
	//服务器控制
	printf("选择服务器类别：1.通知模式   2.协商模式\n");
	int c = getch();
	TimeMgrServer* myDDSTmSvr = TimeMgrServer::GetInstancePtr();///<采用单例

	if(c=='1')
	{
		if(!myDDSTmSvr->initSvr(TMG_Notice))
			printf("初始化失败:%s\n",myDDSTmSvr->getLastError().c_str());
	}
	else if(c=='2')
	{
		if(!myDDSTmSvr->initSvr(TMG_Negotiate))
			printf("初始化失败:%s\n",myDDSTmSvr->getLastError().c_str());
	}
	else
		return -1;
	myDDSTmSvr->startSerrvice();
	Sleep(1000);
	//printf("waiting data:\n");
	while(myDDSTmSvr->isRunning())
	{
		if(getchar()=='q')
			myDDSTmSvr->stopSerrvice();
		Sleep(1000);
	}

	return 0;
}