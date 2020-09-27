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
	/// <summary>	������Ӧ. </summary> wujl
	void RMCommandAnswerPackage_tcpfunc(RMCommandAnswerPackage & package);

	/// <summary>	�����ϱ�. </summary> wujl
	void RMPantReportPackage_tcpfunc(RMPantReportPackage & package);

	/// <summary>	�״��Լ��ϱ�. </summary> wujl
	void RMRadarSelfTestResult_tcpfunc(RMRadarSelfTestResult & package);

	/// <summary>	��У���Լ��ϱ�. </summary> wujl
	void RMCACSelfTestResult_tcpfunc(RMCACSelfTestResult & package);

	/// <summary>	�״������ϱ�. </summary> wujl
	void RMRadarCoordinateReport_tcpfunc(RMRadarCoordinateReport & package);

	/// <summary>	�㼣�����ϱ�. </summary> wujl
	void RMPointTraceReport_tcpfunc(RMPointTraceReport & package);

	/// <summary>	���������ϱ�. </summary> wujl
	void RMFlightTraceReport_tcpfunc(RMFlightTraceReport & package);

	/// <summary>	�״﹤�������ϱ�. </summary> wujl
	void RMRadarWorkParamReport_tcpfunc(RMRadarWorkParamReport & package);
	
	/// <summary>	�״﹤��״̬�ر�. </summary> wujl
	void RMRadarRunControlReport_tcpfunc(RMRadarRunControlReport & package);

	/// <summary>	��˳�����״̬�ظ�. </summary> wujl
	void RMCACControlStateReport_tcpfunc(RMCACControlStateReport & package);

	/// <summary> ���ػظ��ϱ�. </summary> wujl
	void TPC_ScnDldNotify_tcpfunc(TPC_ScnDldNotify & package);

	/// <summary> Ԥλ�ظ��ϱ�. </summary> wujl
	void TPC_SysRdyNotify_tcpfunc(TPC_SysRdyNotify & package);

private:
	void  ReCliveBmazim(int &bmazim);
private:
	const CDDSCore * _dds;
	boost::shared_ptr<boost::thread> _ReportThread;
	CRadarCore *_radar;
	
	char _buffRadarParam[657];
};

