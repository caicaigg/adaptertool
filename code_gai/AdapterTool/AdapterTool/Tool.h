#pragma once
#include <string>
#include "Define.h"
#include "Tool_p.h"


//工具主程序
//启动日志模块，DDS模块，雷达标校车接口模块

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



#pragma region DDS接收消息队列,处理接口
private:

	void DDSDataFunction_Thread();

	/// <summary>	系统复位. </summary> wujl 
	void SysReset_ddsfunc(SysResetptr Reset);

	/// <summary>	系统终止. </summary> wujl 
	void SysConclude_ddsfunc(SysConcludeptr Conclud);

	/// <summary>	系统自检. </summary> wujl 
	void SysSelfCheck_ddsfunc(SysSelfCheckptr SelfCheck);

	/// <summary>	系统加载. </summary> wujl 
	void SysLoad_ddsfunc(SysLoadptr Load);

	/// <summary>	系统预位. </summary> wujl 
	void SysPrePosition_ddsfunc(SysPrePositionptr PrePosition);

	/// <summary>	模式设置. </summary> wujl 
	void SysModeSet_ddsfunc(SysModeSetptr ModeSet);

	/// <summary>	运行控制. </summary> wujl 
	void SysRunControl_ddsfunc(SysRunControlptr RunControl);

	/// <summary>	状态查询. </summary> wujl 
	void SysStateSeek_ddsfunc(SysStateSeekptr StateSeek);

	/// <summary>	平台运动更新. </summary> wujl 
	void SysMotionUpdate_ddsfunc(SysMotionUpdateptr MotionUpdate);

	/// <summary>	仿真事件发布. </summary> wujl 
	void SysEventPub_ddsfunc(SysEventPubptr EventPub);

	/// <summary>	平台惯导更新. </summary> wujl 
	void UpdateNavigationInfo_ddsfunc(UpdateNavigationInfoptr UpdateNavigation);

	/// <summary>	场景融合更新. </summary> wujl 
	void UpdateScenarioData_ddsfunc(UpdateScenarioDataptr UpdateScenario);

#pragma endregion DDS接收消息,处理接口

#pragma region TCP接收消息队列,处理接口
private:
	void TCPDataFunction_Thread();

	/// <summary>	命令响应:接收到通信查询命令后立即上报. </summary> wujl 
	void RMCommandAnswerPackage_tcpfunc(RMCommandAnswerPackage& package);

	/// <summary>	心跳上报:在系统通信空闲时定时发送. </summary> wujl 
	void RMPantReportPackage_tcpfunc(RMPantReportPackage& package);

	/// <summary>	雷达自检上报. </summary> wujl 
	void RMRadarSelfTestResult_tcpfunc(RMRadarSelfTestResult& package);

	/// <summary>	标校车自检上报. </summary> wujl 
	void RMCACSelfTestResult_tcpfunc(RMCACSelfTestResult& package);

	/// <summary>	雷达坐标上报. </summary> wujl 
	void RMRadarCoordinateReport_tcpfunc(RMRadarCoordinateReport& package);

	/// <summary>	点迹数据上报. </summary> wujl 
	void RMPointTraceReport_tcpfunc(RMPointTraceReport& package);

	/// <summary>	航迹数据上报. </summary> wujl 
	void RMFlightTraceReport_tcpfunc(RMFlightTraceReport& package);

	/// <summary>	雷达工作参数上报. </summary> wujl 
	void RMRadarWorkParamReport_tcpfunc(RMRadarWorkParamReport& package);

#pragma endregion TCP接收消息队列,处理接口
	
#ifdef LVC29_RADAR_DEBUG
	void cin_cmd_char();
#endif // !

private:
	ToolPrivate * _p;
};

