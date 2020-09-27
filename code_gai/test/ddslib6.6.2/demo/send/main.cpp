//动态加载方式,不链接lib
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

	UINT32 TargetSubSysID;			//目标子系统ID
	UINT32 EquipmentNum;			//设备数量
	UINT32 EquipmentID[32];			//设备ID
};

class SysRunControl : public DataTypeBase
{
	DECLARE_DATATYPE(SysRunControl);

	UINT32 TargetSubSysID;			//目标子系统ID
	UINT32 CommondID;				//0-开始，1-结束，2-暂停，3-恢复，4-终止
	UINT32 TYear;					//预约执行时间：年；取值范围：2000-2099
	UINT32 TMouth;					//预约执行时间：月；取值范围：1-12
	UINT32 TDay;					//预约执行时间：日；取值范围：1-31
	UINT32 THour;					//预约执行时间：时；取值范围：0-23
	UINT32 TMinute;					//预约执行时间：分；取值范围：0-59
	UINT32 TSecond;					//预约执行时间：秒；取值范围：0-59
	UINT32 ExpTestID;				//试验任务ID
};

class SysSelfCheck : public DataTypeBase
{
	DECLARE_DATATYPE(SysSelfCheck);
	UINT32 TargetSubSysID;			//目标子系统ID
	UINT32 SelfCheckMode;			//自检方式
	UINT32 EquipmentNum;			//设备数量
	UINT32 EquipmentID[32];			//设备ID
};


int main (int argc, char *argv[])
{
	char* tpname = "SysBitReply";///<Topic名称
	CIA_STATUS status = Hwa_CIA_Init("H:\\lvc29\\03sdk\\config\\test_reciver.xml");
	if (status < 0)
	{
		printf("初始化CIA失败！\n");
		return -1;
	}

	CIA_HANDLE hd = Hwa_CIA_GetHandle(1, tpname);
	if (hd == CIA_ERROR)
	{
		printf("获取句柄失败！\n");
		return -1;
	}

	SysRunControl d;
	int len = sizeof(SysRunControl);
	int writenum = 0;
	for (int i = 0; 1; i++)
	{
		if (!writenum)
		{
			printf("输入发送数据个数：");
			scanf("%d", &writenum);
			if (writenum<0)
				break;
		}
		writenum--;

// 		d.n = i;
// 		d.d = 23;
// 		sprintf(d.str, "测试数据");
		SysSelfCheck check;
// 		d.DataType = 0xFF07;
// 		d.CommondID = 0;
		status = Hwa_CIA_Write(hd, (void *)&check);
		if (status == CIA_OK)
		{
			//printf("发送数据成功!\n");
			//printf("%d,", d.n);
		}
		else
			printf("发送数据失败！\n");

		//Sleep(10);
	}
	Sleep(2000);
	Hwa_CIA_Close();
}
