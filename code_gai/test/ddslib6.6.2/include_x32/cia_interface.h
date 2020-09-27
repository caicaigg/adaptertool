/********************************************************************
	created:	2016/07/22
	created:	22:7:2016   9:06
	filename: 	D:\prj\zhuzhou\ddslib\ddslib\cia_interface.h
	file path:	D:\prj\zhuzhou\ddslib\ddslib
	file base:	cia_interface
	file ext:	h
	author:		MYS
	
	purpose:	CIA调用接口头文件，静态调用时使用，需要链接ddslib.lib库，头文件定义了导出函数接口
*********************************************************************/
#ifndef __CIA_INTERFACE_H__
#define __CIA_INTERFACE_H__
#include "ddalib_export.h"
typedef int CIA_STATUS;
typedef int CIA_HANDLE;
typedef unsigned int ulong;
typedef void(*readFunctionCallback)(const void *pBuf, ulong uCount);
typedef void(*readCallback)();
//#define  TRUE 1
//#define  FALSE 0
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
	CIA_ERROR_ROLE   = 0x01,
	CIA_INFO_ROLE    = 0x02,
	CIA_WARNING_ROLE = 0x04,
	CIA_DEBUG_ROLE   = 0x08
};

extern "C" _DDSLIB_API CIA_STATUS  Hwa_CIA_Init				(char * strConfPath);
extern "C" _DDSLIB_API CIA_HANDLE  Hwa_CIA_GetHandle		(unsigned long ulRegion, char *strDataName);
extern "C" _DDSLIB_API CIA_STATUS  Hwa_CIA_Read				(CIA_HANDLE hHandle, void *pBuf, ulong uCount, ulong *uGotNum);
extern "C" _DDSLIB_API CIA_STATUS  Hwa_CIA_Set_Read_Callback(CIA_HANDLE hHandle, readFunctionCallback fun);
extern "C" _DDSLIB_API CIA_STATUS  Hwa_CIA_ReadLatest		(CIA_HANDLE hHandle, void *pBuf);
extern "C" _DDSLIB_API CIA_STATUS  Hwa_CIA_Write			(CIA_HANDLE hHandle, void *pBuf);
extern "C" _DDSLIB_API CIA_STATUS  Hwa_CIA_Close			(void);
extern "C" _DDSLIB_API void		   CIA_Trace_Enable			(int flag);
extern "C" _DDSLIB_API const char* CIA_Get_LastError		();//返回当前出错信息

class dds_wait;
extern "C" _DDSLIB_API dds_wait* dds_createWait();//创建wait
extern "C" _DDSLIB_API void dds_releaseWait(dds_wait* wt);//释放wait

#endif // __CIA_INTERFACE_H__

