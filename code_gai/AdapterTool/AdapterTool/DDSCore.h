#pragma once

#include <cia_interface.h>
#include "Define.h"
#include "DataManager.h"

class RadarClient;

typedef void(*DDRRecvCallBackFunc)(const void *pBuf, uint uCount);

//DDS�շ�
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
	/// <summary>	DDS���ջص�. </summary>
	///
	/// <remarks>	����, 2020/08/09. </remarks>
	///
	/// <param name="tpname">	 	��������. </param>
	/// <param name="func">			����ָ��. </param>
	///
	/// <returns>	���óɹ�����true�����򷵻�false. </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	bool DDS_Recv_CallBack(char * tpname, DDRRecvCallBackFunc func);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	DDS�������ݽӿ�. </summary>
	///
	/// <remarks>	����, 2020/08/09. </remarks>
	///
	/// <param name="tpname">	 	��������. </param>
	/// <param name="data">			����ָ��. </param>
	///
	/// <returns>	���óɹ�����true�����򷵻�false. </returns>
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

//�м���Բ㣬֧����������DDS���յ����ݺ�Ļص��ӿڣ�
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