#include <Windows.h>
#include<stdio.h>
#include <iostream>
#include "..\..\include\cia_interface.h"


struct TestData///<测试数据，可任意定义要求成员变量为简单数据类型（非指针、引用以及容器类）即类可以用memcpy拷贝即可。
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

class SysSelfCheck : public DataTypeBase
{
	DECLARE_DATATYPE(SysSelfCheck);
	UINT32 TargetSubSysID;			//目标子系统ID
	UINT32 SelfCheckMode;			//自检方式
	UINT32 EquipmentNum;			//设备数量
	UINT32 EquipmentID[32];			//设备ID
};


void myread(const void *pBuf, uint uCount)//回调函数
{
	std::cout << "收到数据" << std::endl;
	for (uint i = 0; i < uCount; i++)
	{
// 		TestData d = *(TestData*)((const char*)pBuf + i*sizeof(TestData));
// 		printf("n=%d,d=%f,str=%s \n", d.n, d.d, d.str);
	}
	printf("\n");
}

int main (int argc, char *argv[])
{
	char* tpname = "ScnPlatUpdate";///<Topic名称
	int nn = sizeof(TestData);
	//初始化
	CIA_STATUS status = Hwa_CIA_Init("H:\\lvc29\\03sdk\\config\\test_reciver_test.xml");
	if (status<0)
	{
		printf("初始化CIA失败！\n");
		printf("%s", CIA_Get_LastError());
		return -1;
	}
	//获取TestData的句柄
	CIA_HANDLE hd = Hwa_CIA_GetHandle(1, tpname);
	if (hd == CIA_ERROR)
	{
		printf("获取句柄失败！\n");
		return -1;
	}
	TestData d[5];
	uint uGotNum=1;
	int n = 0;
	Hwa_CIA_Set_Read_Callback(hd,myread);//回调方式接收TestData

	printf("等待数据：\n");
	while (true)
	{
		if (getchar() == 'q')
			break;
		//status = Hwa_CIA_Read(hd, (void *)&d, 5, &uGotNum);//读多个数据
		////status = Hwa_CIA_ReadLatest(hd, (void *)&d);//读最新数据（一次收到多个数据时）
		//if (status == CIA_OK && uGotNum > 0)
		//{
		//	if (status == CIA_OK)
		//		printf("n=%d,d=%f,str=%s \n", d[0].n, d[0].d, d[0].str);
		//	break;
		//}
		Sleep(20);
	}
	//退出关闭DDS
	Hwa_CIA_Close();
	Sleep(2000);
	printf("close\n");
	return 0;
}
