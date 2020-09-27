#pragma once
#include "Client.h"

//��У������Ҫ�ӿ���

class CBXCCore
{
public:
	CBXCCore();
	~CBXCCore();

public:
	//c
	bool Initialize();

	/// <summary>	����ģ��������. </summary> wujl 
	void SendBGC2_TO_TSPackage(const BGC2_TO_TS Data) const;

	/// <summary>	����ͨ�Ų�ѯ. </summary> wujl 
	void SendDMCommunicationQueryPackage(const DMCommunicationQueryPackage CommunicationQuery) const;

	/// <summary>	�����Լ�. </summary> wujl 
	void SendDMSystemSelfCheckPackage(const DMSystemSelfCheckPackage SelfCheck) const;

	/// <summary>	���Ϳ���״̬��ѯ. </summary> wujl 
	void SendDMAalibrationMarkCarInitPackage(const DMAalibrationMarkCarInitPackage ControlState) const;
private:
	BXCClient *_BClient;
};

