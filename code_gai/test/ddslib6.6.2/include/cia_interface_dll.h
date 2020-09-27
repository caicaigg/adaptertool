/********************************************************************
	created:	2016/07/22
	created:	22:7:2016   9:08
	filename: 	D:\prj\zhuzhou\ddslib\ddslib\cia_interface_dll.h
	file path:	D:\prj\zhuzhou\ddslib\ddslib
	file base:	cia_interface_dll
	file ext:	h
	author:		MYS
	
	purpose:	CIA调用接口头文件，动态调用时使用，不用链接ddslib.lib库
	接口按照一般dll动态加载方式使用即可，可不使用此头文件，只是为了方便使用函数
*********************************************************************/
#ifndef __CIA_INTERFACE_DLL_H__
#define __CIA_INTERFACE_DLL_H__

typedef int CIA_STATUS;
typedef int CIA_HANDLE;
typedef unsigned int ulong;
typedef void(*readFunctionCallback)(const void *pBuf, ulong uCount);

#define  TRUE 1
#define  FALSE 0
#define  RECV_ALL 1
#define  SAMPLE 0
enum CIA_MESSAGE
{
	CIA_NO_DATA			= -7,
	CIA_OLD_DATA		= -6,
	CIA_INVALID_PAR		= -5,//参数错误，句柄不存在
	CIA_CHKSUM_ERROR	= -4,
	CIA_NO_NEW_DATA		= -3,//没有数据更新
	CIA_FIFO_OVERFLOW	= -2,
	CIA_ERROR			= -1,//错误
	CIA_OK				= 0//正常
};
enum CIA_Trace_ROLE
{
	CIA_ERROR_ROLE = 0x01,
	CIA_INFO_ROLE = 0x02,
	CIA_WARNING_ROLE = 0x04,
	CIA_DEBUG_ROLE = 0x08
};

typedef CIA_STATUS (*dds_Hwa_CIA_Init)(char * strConfPath);
dds_Hwa_CIA_Init Hwa_CIA_Init;
typedef CIA_HANDLE (*dds_Hwa_CIA_GetHandle)(unsigned long ulRegion, char *strDataName);
dds_Hwa_CIA_GetHandle Hwa_CIA_GetHandle;
typedef CIA_STATUS (*dds_Hwa_CIA_Read)(CIA_HANDLE hHandle, void *pBuf, ulong uCount, ulong *uGotNum);
dds_Hwa_CIA_Read Hwa_CIA_Read;
typedef CIA_STATUS (*dds_Hwa_CIA_Set_Read_Callback)(CIA_HANDLE hHandle, readFunctionCallback fun);
dds_Hwa_CIA_Set_Read_Callback Hwa_CIA_Set_Read_Callback;
typedef CIA_STATUS (*dds_Hwa_CIA_ReadLatest)(CIA_HANDLE hHandle, void *pBuf);
dds_Hwa_CIA_ReadLatest Hwa_CIA_ReadLatest;
typedef CIA_STATUS (*dds_Hwa_CIA_Write)(CIA_HANDLE hHandle, void *pBuf);
dds_Hwa_CIA_Write Hwa_CIA_Write;
typedef CIA_STATUS (*dds_Hwa_CIA_Close)(void);
dds_Hwa_CIA_Close Hwa_CIA_Close;
typedef void (*dds_CIA_Trace_Enable)(int flag);
dds_CIA_Trace_Enable CIA_Trace_Enable;


//function call macros
#ifdef _DEBUG
#define DDSDLL "ddslibd.dll"
#else
#define DDSDLL "ddslib.dll"
#endif

#define FunDef(s)\
	s = (dds_##s)GetProcAddress(hinst, #s);

#define InitDDS()\
	HINSTANCE hinst = LoadLibraryA(DDSDLL); \
	FunDef(Hwa_CIA_Init)\
	FunDef(Hwa_CIA_GetHandle)\
	FunDef(Hwa_CIA_Read)\
	FunDef(Hwa_CIA_Set_Read_Callback)\
	FunDef(Hwa_CIA_ReadLatest)\
	FunDef(Hwa_CIA_Write)\
	FunDef(Hwa_CIA_Close)\
	FunDef(CIA_Trace_Enable)\
////
#endif // __CIA_INTERFACE_DLL_H__

