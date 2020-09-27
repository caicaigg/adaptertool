#include <Windows.h>
#include<stdio.h>
#include <iostream>
#include "..\..\include\cia_interface.h"


struct TestData///<�������ݣ������ⶨ��Ҫ���Ա����Ϊ���������ͣ���ָ�롢�����Լ������ࣩ���������memcpy�������ɡ�
{
	int n;
	double d;
	char str[32];
};


#define DECLARE_DATATYPE(ClassName) \
	public:\
		ClassName(){} \
		virtual ~ClassName(){}

class DataTypeBase /*: public boost::enable_shared_from_this<CBase>*/
{
public:
	DataTypeBase()
	{}
	virtual ~DataTypeBase()
	{}
	UINT32 DataType;
};

class SysReset : public DataTypeBase
{
	DECLARE_DATATYPE(SysReset);

	UINT32 TargetSubSysID;			//Ŀ����ϵͳID
	UINT32 EquipmentNum;			//�豸����
	UINT32 EquipmentID[32];			//�豸ID
};

class SysSelfCheck : public DataTypeBase
{
	DECLARE_DATATYPE(SysSelfCheck);
	UINT32 TargetSubSysID;			//Ŀ����ϵͳID
	UINT32 SelfCheckMode;			//�Լ췽ʽ
	UINT32 EquipmentNum;			//�豸����
	UINT32 EquipmentID[32];			//�豸ID
};


void myread(const void *pBuf, uint uCount)//�ص�����
{
	std::cout << "�յ�����" << std::endl;
	for (uint i = 0; i < uCount; i++)
	{
// 		TestData d = *(TestData*)((const char*)pBuf + i*sizeof(TestData));
// 		printf("n=%d,d=%f,str=%s \n", d.n, d.d, d.str);
	}
	printf("\n");
}

int main (int argc, char *argv[])
{
	char* tpname = "ScnPlatUpdate";///<Topic����
	int nn = sizeof(TestData);
	//��ʼ��
	CIA_STATUS status = Hwa_CIA_Init("H:\\lvc29\\03sdk\\config\\test_reciver_test.xml");
	if (status<0)
	{
		printf("��ʼ��CIAʧ�ܣ�\n");
		printf("%s", CIA_Get_LastError());
		return -1;
	}
	//��ȡTestData�ľ��
	CIA_HANDLE hd = Hwa_CIA_GetHandle(1, tpname);
	if (hd == CIA_ERROR)
	{
		printf("��ȡ���ʧ�ܣ�\n");
		return -1;
	}
	TestData d[5];
	uint uGotNum=1;
	int n = 0;
	Hwa_CIA_Set_Read_Callback(hd,myread);//�ص���ʽ����TestData

	printf("�ȴ����ݣ�\n");
	while (true)
	{
		if (getchar() == 'q')
			break;
		//status = Hwa_CIA_Read(hd, (void *)&d, 5, &uGotNum);//���������
		////status = Hwa_CIA_ReadLatest(hd, (void *)&d);//���������ݣ�һ���յ��������ʱ��
		//if (status == CIA_OK && uGotNum > 0)
		//{
		//	if (status == CIA_OK)
		//		printf("n=%d,d=%f,str=%s \n", d[0].n, d[0].d, d[0].str);
		//	break;
		//}
		Sleep(20);
	}
	//�˳��ر�DDS
	Hwa_CIA_Close();
	Sleep(2000);
	printf("close\n");
	return 0;
}
