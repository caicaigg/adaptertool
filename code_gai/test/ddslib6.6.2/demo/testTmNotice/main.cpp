#include <Windows.h>
#include "..\..\include\TimeMgr.h"
int main (int argc, char *argv[])
{
	//֪ͨ��ʽʱ���ƽ�
	TimeMgr* myDDSTm = TimeMgr::GetInstancePtr();///<���õ���
	if(!myDDSTm->initMember(TMG_Notice))
		printf("��ʼ��ʧ��:%s\n",myDDSTm->getLastError().c_str());

	if(!myDDSTm->registerTimeStep(15))
		printf("�ǼǷ���ʱ�䲽��ʧ��:%s\n",myDDSTm->getLastError().c_str());
	Sleep(1000);
	printf("��ʼ���桭��\n");
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