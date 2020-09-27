//��̬���ط�ʽ,������lib
#include <Windows.h>
#include<stdio.h>
#include "..\..\include\cia_interface.h"

struct TestData
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

class SysRunControl : public DataTypeBase
{
	DECLARE_DATATYPE(SysRunControl);

	UINT32 TargetSubSysID;			//Ŀ����ϵͳID
	UINT32 CommondID;				//0-��ʼ��1-������2-��ͣ��3-�ָ���4-��ֹ
	UINT32 TYear;					//ԤԼִ��ʱ�䣺�ꣻȡֵ��Χ��2000-2099
	UINT32 TMouth;					//ԤԼִ��ʱ�䣺�£�ȡֵ��Χ��1-12
	UINT32 TDay;					//ԤԼִ��ʱ�䣺�գ�ȡֵ��Χ��1-31
	UINT32 THour;					//ԤԼִ��ʱ�䣺ʱ��ȡֵ��Χ��0-23
	UINT32 TMinute;					//ԤԼִ��ʱ�䣺�֣�ȡֵ��Χ��0-59
	UINT32 TSecond;					//ԤԼִ��ʱ�䣺�룻ȡֵ��Χ��0-59
	UINT32 ExpTestID;				//��������ID
};

class SysSelfCheck : public DataTypeBase
{
	DECLARE_DATATYPE(SysSelfCheck);
	UINT32 TargetSubSysID;			//Ŀ����ϵͳID
	UINT32 SelfCheckMode;			//�Լ췽ʽ
	UINT32 EquipmentNum;			//�豸����
	UINT32 EquipmentID[32];			//�豸ID
};


int main (int argc, char *argv[])
{
	char* tpname = "SysBitReply";///<Topic����
	CIA_STATUS status = Hwa_CIA_Init("H:\\lvc29\\03sdk\\config\\test_reciver.xml");
	if (status < 0)
	{
		printf("��ʼ��CIAʧ�ܣ�\n");
		return -1;
	}

	CIA_HANDLE hd = Hwa_CIA_GetHandle(1, tpname);
	if (hd == CIA_ERROR)
	{
		printf("��ȡ���ʧ�ܣ�\n");
		return -1;
	}

	SysRunControl d;
	int len = sizeof(SysRunControl);
	int writenum = 0;
	for (int i = 0; 1; i++)
	{
		if (!writenum)
		{
			printf("���뷢�����ݸ�����");
			scanf("%d", &writenum);
			if (writenum<0)
				break;
		}
		writenum--;

// 		d.n = i;
// 		d.d = 23;
// 		sprintf(d.str, "��������");
		SysSelfCheck check;
// 		d.DataType = 0xFF07;
// 		d.CommondID = 0;
		status = Hwa_CIA_Write(hd, (void *)&check);
		if (status == CIA_OK)
		{
			//printf("�������ݳɹ�!\n");
			//printf("%d,", d.n);
		}
		else
			printf("��������ʧ�ܣ�\n");

		//Sleep(10);
	}
	Sleep(2000);
	Hwa_CIA_Close();
}
