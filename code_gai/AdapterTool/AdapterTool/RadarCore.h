#pragma once
#include "Client.h"


//�״ﳵ����Ҫ�ӿ���
class CRadarCore
{
public:
	CRadarCore();
	~CRadarCore();
public:
	bool Initialize();

public:
	/// <summary>	������ͷ. </summary> wujl 
	void TransferHead(SMessageFormat& Head, const buffer_type & buffer);

#pragma region TCP���ͽӿ�
public:
	/// <summary>	����ͨ�Ų�ѯ. </summary> wujl 
	void SendDMCommunicationQueryPackage(const DMCommunicationQueryPackage CommunicationQuery) const;

	/// <summary>	�����Լ�. </summary> wujl 
	void SendDMSystemSelfCheckPackage(const DMSystemSelfCheckPackage SelfCheck) const;

	/// <summary>	�����״��ʼ������. </summary> wujl 
	void SendDMRadarInitConfigPackage(const CENTER2RADAR_INIT RadarInit) const;

	/// <summary>	�����״������ѯ. </summary> wujl 
	void SendDMRadarLocationQueryPackage(const DMRadarLocationQueryPackage LocationQuery) const;

	/// <summary>	�������п�������. </summary> wujl 
	void SendDMRunControlPackage(const DMRunControlPackage RunControl) const;

	/// <summary>	���ͱ�У����ʼ������. </summary> wujl 
	//void SendDMAalibrationMarkCarInitPackage(const DMAalibrationMarkCarInitPackage AMCInit) const;

	/// <summary>	����ʵʱĿ�����. </summary> wujl 
	void SendDMTargetRealTimePackage(const DMTargetRealTimePackage Targets) const;


	/// <summary>	��������. </summary> wujl 
	//void SendStartUp(const SelfCheck SelfCheck);

	/// <summary>	����ֹͣ. </summary> wujl 
	//void SendRecvStop(const SelfCheck SelfCheck);

#pragma endregion TCP���ͽӿ�

private:
	RadarClient *_RClient;

};

