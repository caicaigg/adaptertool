#include <Windows.h>
//#include "ddslib.h"
#include "TimeMgr.h"
#include <conio.h>

int main (int argc, char *argv[])
{
	//����������
	printf("ѡ����������1.֪ͨģʽ   2.Э��ģʽ\n");
	int c = getch();
	TimeMgrServer* myDDSTmSvr = TimeMgrServer::GetInstancePtr();///<���õ���

	if(c=='1')
	{
		if(!myDDSTmSvr->initSvr(TMG_Notice))
			printf("��ʼ��ʧ��:%s\n",myDDSTmSvr->getLastError().c_str());
	}
	else if(c=='2')
	{
		if(!myDDSTmSvr->initSvr(TMG_Negotiate))
			printf("��ʼ��ʧ��:%s\n",myDDSTmSvr->getLastError().c_str());
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