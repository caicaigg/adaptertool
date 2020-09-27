#pragma once
#include "Client.h"

//标校车的主要接口类

class CBXCCore
{
public:
	CBXCCore();
	~CBXCCore();

public:
	//c
	bool Initialize();

	/// <summary>	发送模拟器数据. </summary> wujl 
	void SendBGC2_TO_TSPackage(const BGC2_TO_TS Data) const;

	/// <summary>	发送通信查询. </summary> wujl 
	void SendDMCommunicationQueryPackage(const DMCommunicationQueryPackage CommunicationQuery) const;

	/// <summary>	发送自检. </summary> wujl 
	void SendDMSystemSelfCheckPackage(const DMSystemSelfCheckPackage SelfCheck) const;

	/// <summary>	发送控制状态查询. </summary> wujl 
	void SendDMAalibrationMarkCarInitPackage(const DMAalibrationMarkCarInitPackage ControlState) const;
private:
	BXCClient *_BClient;
};

