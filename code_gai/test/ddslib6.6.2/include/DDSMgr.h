/*!
 * \file DDSMgr.h
 *
 * \author Administrator
 * \date ʮ���� 2015
 *
 * CMParticipant �����߼��
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
	unsigned int getCurrentSystemId();//��ȡ��ǰ����systemid
	void getAllHistoricalParticpant(int& count, DDSParticpantProduct nds[]);//��ȡ���в����ߣ�DDS��������߳��⣺Built-in participant,splicedaemon,cmsoap,durability,ddsi2 ��
	bool setCallBack(CallBackType typ,DDSParticpantCB pcb);

	//end Participant
	string getLastError();
	///////////////
	//timerʹ�ã�����Ա�˳�
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


