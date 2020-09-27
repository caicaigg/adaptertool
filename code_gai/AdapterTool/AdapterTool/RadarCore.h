#pragma once
#include "Client.h"


//雷达车的主要接口类
class CRadarCore
{
public:
	CRadarCore();
	~CRadarCore();
public:
	bool Initialize();

public:
	/// <summary>	解析包头. </summary> wujl 
	void TransferHead(SMessageFormat& Head, const buffer_type & buffer);

#pragma region TCP发送接口
public:
	/// <summary>	发送通信查询. </summary> wujl 
	void SendDMCommunicationQueryPackage(const DMCommunicationQueryPackage CommunicationQuery) const;

	/// <summary>	发送自检. </summary> wujl 
	void SendDMSystemSelfCheckPackage(const DMSystemSelfCheckPackage SelfCheck) const;

	/// <summary>	发送雷达初始化配置. </summary> wujl 
	void SendDMRadarInitConfigPackage(const CENTER2RADAR_INIT RadarInit) const;

	/// <summary>	发送雷达坐标查询. </summary> wujl 
	void SendDMRadarLocationQueryPackage(const DMRadarLocationQueryPackage LocationQuery) const;

	/// <summary>	发送运行控制命令. </summary> wujl 
	void SendDMRunControlPackage(const DMRunControlPackage RunControl) const;

	/// <summary>	发送标校车初始化配置. </summary> wujl 
	//void SendDMAalibrationMarkCarInitPackage(const DMAalibrationMarkCarInitPackage AMCInit) const;

	/// <summary>	发送实时目标参数. </summary> wujl 
	void SendDMTargetRealTimePackage(const DMTargetRealTimePackage Targets) const;


	/// <summary>	发送启动. </summary> wujl 
	//void SendStartUp(const SelfCheck SelfCheck);

	/// <summary>	发送停止. </summary> wujl 
	//void SendRecvStop(const SelfCheck SelfCheck);

#pragma endregion TCP发送接口

private:
	RadarClient *_RClient;

};

