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

	/// <summary>	ϵͳ��λ. </summary> wujl
	void TPC_SysResetRequest_ddsfunc(TPC_SysResetRequest Reset);

	/// <summary>	ϵͳ��ֹ. </summary> wujl
	void TPC_SysHaltRequest_ddsfunc(TPC_SysHaltRequest Halt);

	/// <summary>	ϵͳ�Լ�. </summary> wujl
	void TPC_SysBitRequest_ddsfunc(TPC_SysBitRequest SelfCheck);

	/// <summary>	��������. </summary> wujl
	void TPC_ScnDldRequest_ddsfunc(TPC_ScnDldRequest Load);

	/// <summary>	ϵͳԤλ. </summary> wujl
	void TPC_SysRdyRequest_ddsfunc(TPC_SysRdyRequest PrePosition);

	/// <summary>	���п���. </summary> wujl
	void TPC_SysCtrlRequest_ddsfunc(TPC_SysCtrlRequest RunControl);

	/// <summary>	ͨ�Ų�ѯ. </summary> wujl
	void TPC_SysStqRequest_ddsfunc(TPC_SysStqRequest StateSeek);

	/// <summary>	ƽ̨����. </summary> wujl
	void TPC_ScnPlatUpdate_ddsfunc(TPC_ScnPlatUpdate MotionUpdate);

	/// <summary>	����Դ�¼�. </summary> wujl
	void TPC_ScnEmtEvent_ddsfunc(TPC_ScnEmtEvent EmtEvent);

	/// <summary>	�㼣�ϱ�. </summary> wujl
	void TPC_RadPltNotify_ddsfunc(TPC_RadPltNotify Tarce);

	/// <summary>	�����ϱ�. </summary> wujl
	void TPC_RadTrkNotify_ddsfunc(TPC_RadTrkNotify track);

	
	//������ ��ûʹ�õ�
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

