#pragma once
#include <string>
#include "Define.h"
#include "Tool_p.h"


//����������
//������־ģ�飬DDSģ�飬�״��У���ӿ�ģ��

struct ToolPrivate;

class CTool
{
public:
	CTool();
	~CTool();

public:
	bool Initialize();
	void run();

public:
	const std::string& GetLastError();
	
	
private:
	bool InitDDSIn();
	bool InitRadarIn();
	bool InitBXCIn();

private:
	const CDDSCore * DDS();
	const CRadarCore * Radar();
	const CBXCCore * BXC();
	CSceneResolution * ScenResolution();



#pragma region DDS������Ϣ����,����ӿ�
private:

	void DDSDataFunction_Thread();

	/// <summary>	ϵͳ��λ. </summary> wujl 
	void SysReset_ddsfunc(SysResetptr Reset);

	/// <summary>	ϵͳ��ֹ. </summary> wujl 
	void SysConclude_ddsfunc(SysConcludeptr Conclud);

	/// <summary>	ϵͳ�Լ�. </summary> wujl 
	void SysSelfCheck_ddsfunc(SysSelfCheckptr SelfCheck);

	/// <summary>	ϵͳ����. </summary> wujl 
	void SysLoad_ddsfunc(SysLoadptr Load);

	/// <summary>	ϵͳԤλ. </summary> wujl 
	void SysPrePosition_ddsfunc(SysPrePositionptr PrePosition);

	/// <summary>	ģʽ����. </summary> wujl 
	void SysModeSet_ddsfunc(SysModeSetptr ModeSet);

	/// <summary>	���п���. </summary> wujl 
	void SysRunControl_ddsfunc(SysRunControlptr RunControl);

	/// <summary>	״̬��ѯ. </summary> wujl 
	void SysStateSeek_ddsfunc(SysStateSeekptr StateSeek);

	/// <summary>	ƽ̨�˶�����. </summary> wujl 
	void SysMotionUpdate_ddsfunc(SysMotionUpdateptr MotionUpdate);

	/// <summary>	�����¼�����. </summary> wujl 
	void SysEventPub_ddsfunc(SysEventPubptr EventPub);

	/// <summary>	ƽ̨�ߵ�����. </summary> wujl 
	void UpdateNavigationInfo_ddsfunc(UpdateNavigationInfoptr UpdateNavigation);

	/// <summary>	�����ںϸ���. </summary> wujl 
	void UpdateScenarioData_ddsfunc(UpdateScenarioDataptr UpdateScenario);

#pragma endregion DDS������Ϣ,����ӿ�

#pragma region TCP������Ϣ����,����ӿ�
private:
	void TCPDataFunction_Thread();

	/// <summary>	������Ӧ:���յ�ͨ�Ų�ѯ����������ϱ�. </summary> wujl 
	void RMCommandAnswerPackage_tcpfunc(RMCommandAnswerPackage& package);

	/// <summary>	�����ϱ�:��ϵͳͨ�ſ���ʱ��ʱ����. </summary> wujl 
	void RMPantReportPackage_tcpfunc(RMPantReportPackage& package);

	/// <summary>	�״��Լ��ϱ�. </summary> wujl 
	void RMRadarSelfTestResult_tcpfunc(RMRadarSelfTestResult& package);

	/// <summary>	��У���Լ��ϱ�. </summary> wujl 
	void RMCACSelfTestResult_tcpfunc(RMCACSelfTestResult& package);

	/// <summary>	�״������ϱ�. </summary> wujl 
	void RMRadarCoordinateReport_tcpfunc(RMRadarCoordinateReport& package);

	/// <summary>	�㼣�����ϱ�. </summary> wujl 
	void RMPointTraceReport_tcpfunc(RMPointTraceReport& package);

	/// <summary>	���������ϱ�. </summary> wujl 
	void RMFlightTraceReport_tcpfunc(RMFlightTraceReport& package);

	/// <summary>	�״﹤�������ϱ�. </summary> wujl 
	void RMRadarWorkParamReport_tcpfunc(RMRadarWorkParamReport& package);

#pragma endregion TCP������Ϣ����,����ӿ�
	
#ifdef LVC29_RADAR_DEBUG
	void cin_cmd_char();
#endif // !

private:
	ToolPrivate * _p;
};

