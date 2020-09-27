#pragma once

#include "Define.h"
#include <boost/thread.hpp>
#include <boost/shared_ptr.hpp>

#include <boost/interprocess/sync/interprocess_semaphore.hpp>
#include <boost/thread/mutex.hpp>

class CRadarCore;
class CBXCCore;
class CTool;
class CSceneResolution;

class MessageDispatch
{
public:
	MessageDispatch(const CRadarCore * Radar, const CBXCCore *Bxc, CSceneResolution* scenres);
	~MessageDispatch();

	friend class CTool;
private:

	void DDSDataFunction_Thread();
	void CheckFunction_Thread();
public:

	/// <summary>	系统复位. </summary> wujl
	void TPC_SysResetRequest_ddsfunc(TPC_SysResetRequest Reset);

	/// <summary>	系统中止. </summary> wujl
	void TPC_SysHaltRequest_ddsfunc(TPC_SysHaltRequest Halt);

	/// <summary>	系统自检. </summary> wujl
	void TPC_SysBitRequest_ddsfunc(TPC_SysBitRequest SelfCheck);

	/// <summary>	启动加载. </summary> wujl
	void TPC_ScnDldRequest_ddsfunc(TPC_ScnDldRequest Load);

	/// <summary>	系统预位. </summary> wujl
	void TPC_SysRdyRequest_ddsfunc(TPC_SysRdyRequest PrePosition);

	/// <summary>	运行控制. </summary> wujl
	void TPC_SysCtrlRequest_ddsfunc(TPC_SysCtrlRequest RunControl);

	/// <summary>	通信查询. </summary> wujl
	void TPC_SysStqRequest_ddsfunc(TPC_SysStqRequest StateSeek);

	/// <summary>	平台更新. </summary> wujl
	void TPC_ScnPlatUpdate_ddsfunc(TPC_ScnPlatUpdate MotionUpdate);

	/// <summary>	辐射源事件. </summary> wujl
	void TPC_ScnEmtEvent_ddsfunc(TPC_ScnEmtEvent EmtEvent);

	/// <summary>	点迹上报. </summary> wujl
	void TPC_RadPltNotify_ddsfunc(TPC_RadPltNotify Tarce);

	/// <summary>	航迹上报. </summary> wujl
	void TPC_RadTrkNotify_ddsfunc(TPC_RadTrkNotify track);

	
	//以下是 现没使用的
	void SysModeSet_ddsfunc(SysModeSetptr ModeSet);
	void TPC_ScnSimEvent_ddsfunc(TPC_ScnSimEvent EventPub);
	void UpdateNavigationInfo_ddsfunc(UpdateNavigationInfoptr UpdateNavigation);
	void UpdateScenarioData_ddsfunc(UpdateScenarioDataptr UpdateScenario);


	void waitRdyRequestback(int times = 2000);
private:
	void virtualSendtoDDS(int type);
private:
	const CRadarCore * _radar;
	const CBXCCore * _bxc;
	CSceneResolution * _scenR;
	boost::shared_ptr<boost::thread> _DispatchThread;

};

