/*!
 * \file DDSMgr.h
 *
 * \author Administrator
 * \date 十二月 2015
 *
 * CMParticipant 参与者监控
 */
#ifndef __DDSMGR_H__
#define __DDSMGR_H__

#include "ddalib_export.h"
#include <list>
using namespace std;

struct DDSParticpantProduct 
{
	unsigned int systemid;
	char ExecName[64];//sacpp_builtintopics_sub.exe
	char ParticipantName[64];//sacpp_builtintopics_sub.exe
	unsigned int PID;
	char NodeName[64];//WORKHP
	unsigned int FederationId;//3d51ced3
	char VendorId[64];//1.2
	//
	unsigned int instance_states;//DDS::ALIVE_INSTANCE_STATE
};
class DDSMgrData;
class _DDSLIB_API DDSMgr
{
public:
	typedef void (* DDSParticpantCB)(DDSParticpantProduct& product);
	enum CallBackType{ CBK_Particpant};
	static DDSMgr &GetInstance();
	static DDSMgr* GetInstancePtr();
	//Participant
	unsigned int getCurrentSystemId();//获取当前进程systemid
	void getAllHistoricalParticpant(int& count, DDSParticpantProduct nds[]);//获取所有参与者（DDS服务参与者除外：Built-in participant,splicedaemon,cmsoap,durability,ddsi2 ）
	bool setCallBack(CallBackType typ,DDSParticpantCB pcb);

	//end Participant
	string getLastError();
	///////////////
	//timer使用：检测成员退出
	void run();
	void start();
	void stop();
private:
	bool init();
	void getProductFromXml(const char* strxml,DDSParticpantProduct &pdt);
	DDSMgr(void);
	~DDSMgr(void);
	DDSMgrData *m_ddsmgrData;
	volatile bool m_isRun;
};
#endif // __DDSMGR_H__


