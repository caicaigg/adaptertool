#pragma once


#include "Define.h"
#include <boost/thread.hpp>
#include <boost/shared_ptr.hpp>

class CDDSCore;
class CRadarCore;

class MessageReport
{
public:
	MessageReport(const CDDSCore * DDS, CRadarCore *Radar);
	~MessageReport();

public:

private:

	/// <summary>	. </summary> wujl
	void TCPDataFunction_Thread();

private:
	/// <summary>	命令响应. </summary> wujl
	void RMCommandAnswerPackage_tcpfunc(RMCommandAnswerPackage & package);

	/// <summary>	心跳上报. </summary> wujl
	void RMPantReportPackage_tcpfunc(RMPantReportPackage & package);

	/// <summary>	雷达自检上报. </summary> wujl
	void RMRadarSelfTestResult_tcpfunc(RMRadarSelfTestResult & package);

	/// <summary>	标校车自检上报. </summary> wujl
	void RMCACSelfTestResult_tcpfunc(RMCACSelfTestResult & package);

	/// <summary>	雷达坐标上报. </summary> wujl
	void RMRadarCoordinateReport_tcpfunc(RMRadarCoordinateReport & package);

	/// <summary>	点迹数据上报. </summary> wujl
	void RMPointTraceReport_tcpfunc(RMPointTraceReport & package);

	/// <summary>	航迹数据上报. </summary> wujl
	void RMFlightTraceReport_tcpfunc(RMFlightTraceReport & package);

	/// <summary>	雷达工作参数上报. </summary> wujl
	void RMRadarWorkParamReport_tcpfunc(RMRadarWorkParamReport & package);
	
	/// <summary>	雷达工作状态回报. </summary> wujl
	void RMRadarRunControlReport_tcpfunc(RMRadarRunControlReport & package);

	/// <summary>	标杆车控制状态回复. </summary> wujl
	void RMCACControlStateReport_tcpfunc(RMCACControlStateReport & package);

	/// <summary> 加载回复上报. </summary> wujl
	void TPC_ScnDldNotify_tcpfunc(TPC_ScnDldNotify & package);

	/// <summary> 预位回复上报. </summary> wujl
	void TPC_SysRdyNotify_tcpfunc(TPC_SysRdyNotify & package);

private:
	void  ReCliveBmazim(int &bmazim);
private:
	const CDDSCore * _dds;
	boost::shared_ptr<boost::thread> _ReportThread;
	CRadarCore *_radar;
	
	char _buffRadarParam[657];
};

