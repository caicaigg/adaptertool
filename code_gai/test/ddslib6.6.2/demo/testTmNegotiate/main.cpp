#include <Windows.h>
//#include "..\..\include\ddslib.h"
#include "..\..\include\TimeMgr.h"

int main (int argc, char *argv[])
{
	//֪ͨ��ʽʱ���ƽ�
	TimeMgr* myDDSTm = TimeMgr::GetInstancePtr();///<���õ���
	myDDSTm->initMember(TMG_Negotiate);
	double curTime,step=1;
	if(!myDDSTm->registerFederate(curTime))
	{
		printf("ע���Աʧ��:%s\n",myDDSTm->getLastError().c_str());
		return 0;
	}
	Sleep(1000);
	printf("��ʼ���桭��\n");
	//double curTm;
	int i = 100;
	while(i--)
	{
		if(!myDDSTm->RequestTimeAdvance(curTime+step))
		{
			printf("����ʱ���ƽ�ʧ��:%s",myDDSTm->getLastError().c_str());
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