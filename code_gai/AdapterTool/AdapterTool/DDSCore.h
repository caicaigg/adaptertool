#pragma once

#include <cia_interface.h>
#include "Define.h"
#include "DataManager.h"

class RadarClient;

typedef void(*DDRRecvCallBackFunc)(const void *pBuf, uint uCount);

//DDS收发
class CDDSCore
{
public:
	CDDSCore();
	~CDDSCore();

#ifdef LVC29_RADAR_DEBUG
	friend class CTestLvc;
#endif

public:
	bool Initialize();
	bool DDSInit();
	bool DDS_Recv_Init();
	bool DDS_Send_Init();

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	DDS接收回调. </summary>
	///
	/// <remarks>	万炎, 2020/08/09. </remarks>
	///
	/// <param name="tpname">	 	主题名称. </param>
	/// <param name="func">			函数指针. </param>
	///
	/// <returns>	调用成功返回true，否则返回false. </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	bool DDS_Recv_CallBack(char * tpname, DDRRecvCallBackFunc func);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	DDS发送数据接口. </summary>
	///
	/// <remarks>	万炎, 2020/08/09. </remarks>
	///
	/// <param name="tpname">	 	主题名称. </param>
	/// <param name="data">			数据指针. </param>
	///
	/// <returns>	调用成功返回true，否则返回false. </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	bool DDS_Send_Data(char * tpname, void * data) const;

protected:
	void RecvDDS();

public:
	void SendSelfCheckBack();

	//void SendDDS(int TopicType, DataTypeBase* Data) const;

	void SendDDS(int TopicType, void* Data) const;

	const char * GetTopicName(int TopicType) const;

private:
	int _DDSValue;

};

#ifdef LVC29_RADAR_DEBUG

//中间测试层，支持主动调用DDS接收到数据后的回调接口，
class CTestLvc
{
public:
	CTestLvc();
	~CTestLvc();


public:
	void SelfCheckTS();
	void LaunchLoadTS();
	void StartUpCommandTS();
	void StopCommandTS();
	void BreakCommandTS();
	void EntityDataTS();

private:
	CDDSCore * _dds;
};

#endif