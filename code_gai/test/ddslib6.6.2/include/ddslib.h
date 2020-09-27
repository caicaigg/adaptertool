#ifndef __DDSLIB_H__
#define __DDSLIB_H__
#include <string>
#include "ddalib_export.h"
#include "CommBase.h"
/********************************************************************
	created:	2014/11/05
	created:	5:11:2014   21:17
	filename: 	ddslib.h
	file base:	ddslib
	file ext:	h
	author:		mys
	
	purpose:	dds访问接口，publish、subscribe只在程序初始化时调用一次，sendData、recvData可以在任意地方使用
	收发数据注意匹配topicName和partitiontName，第一个参数index 唯一索引 可以不用管填任意值
*********************************************************************/
#include <vector>
#include <list>


class DDSEntityManager;
struct ddslibdata;
class dds_wait;
class _DDSLIB_API ddslib: public CommBase<ddslib>
{
	__CommBase(ddslib)
public:
	sender_handle publish(int bufSize, const char* topicName, const char* partitiontName = defaultPartitiontName);
	receiver_handle subscribe(int bufSize, const char* topicName, const char* partitiontName = defaultPartitiontName);
	bool unpublish(const char* topicName, const char* partitiontName = defaultPartitiontName);
	bool unsubscribe(const char* topicName, const char* partitiontName = defaultPartitiontName);
	//sender_handle publish(const char* topicName, const char* partitiontName = defaultPartitiontName);
	//receiver_handle subscribe(const char* topicName, const char* partitiontName = defaultPartitiontName);
	bool sendData(int index, const void* data,const char* topicName,const char* partitiontName = defaultPartitiontName);
	bool sendData   (int index, sender_handle hand, const void* data);
	int recvData(int& index, char* data, const char* topicName,const char* partitiontName = defaultPartitiontName);//return recived data bytes ret=0:NOData;ret<0:error)
	int recvData(int& index, char* data, receiver_handle hand);//return recived data bytes ret=0:NOData;ret<0:error)
	int recvDatas(std::list<int>& index, char* data,const int max_recv,const char* topicName,const char* partitiontName = defaultPartitiontName);///<一次读取多个数据，返回实际读取数据个数，max_recv为要读取最大数量，index为实际读取数据id列表,data为T[max_recv]数组，且数组长度不小于max_recv
	int recvDatas(std::list<int>& index, char* data,const int max_recv,receiver_handle hand);
	int getDataSize(const char *topicName, const char *partitiontName  = defaultPartitiontName);
	inline const char* getLastError(){ return m_errString->c_str(); };
	bool clear(const char* topicName,const char* partitiontName  = defaultPartitiontName);///<清除当前缓冲区，即将所有已接收未读取的数据全部取出
	dds_wait* createWait();
	void releaseWait(dds_wait* wt);
private:
	ddslib(void);
	~ddslib(void);

	DDSEntityManager* m_ddsmgr;
	ddslibdata*       m_psdata;
	std::string*	  m_errString;
};
/********************************************************************
dds_wait：
说明：dds_wait的功能就是等待指定数据，addWait添加要等待的数据（可多次调用添加多个等待topic）
调用wait(double ftm=-1)后当前线程挂起直到函数返回，函数返回条件：1、有数据到达（addWait中指定的数据）立即返回， 2、等待ftm秒无数据则超时返回
*********************************************************************/
struct dds_wait_data;
class _DDSLIB_API dds_wait
{
public:
	dds_wait(DDSEntityManager* ddsmgr);
	~dds_wait();
	bool addWait(const char *topicName, const char *partitiontName= defaultPartitiontName);
	bool wait(double ftm=-1);//等待ftm秒或有指定数据到达函数返回，用于等待接收数据时使用,-1表示无限等待，返回值：是否有数据到达
	const char* getLastError();
private:
	DDSEntityManager* m_ddsmgr;
	dds_wait_data* m_waitdata;
};
//////////////////////////////////////////////////////////////////////////

#ifdef _DDSLIB
extern "C" _DDSLIB_API sender_handle publish(int dataSize, const char* tblname, const char* dbname);
extern "C" _DDSLIB_API receiver_handle subscribe(int dataSize, const char* tblname, const char* dbname);
extern "C" _DDSLIB_API bool sendData   (int index, const void* data,const char* tblname,const char* dbname);
extern "C" _DDSLIB_API int recvData(int& index,char* data,const char* tblname,const char* dbname);
extern "C" _DDSLIB_API const char* getLastError();
#endif
#endif//__DDSLIB_H__