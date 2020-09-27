#ifndef __TIMEMGR_H__
#define __TIMEMGR_H__
/********************************************************************
	created:	2014/12/29
	created:	29:12:2014   16:57
	filename: 	d:\test\ddslib_src\ddslib\TimeMgr.cpp
	file path:	d:\test\ddslib_src\ddslib
	file base:	TimeMgr
	file ext:	cpp
	author:		MYS
	
	purpose:	DDSʱ���������֧������ģʽʱ�����1��֪ͨ��ʽʱ������ɷ���������ʱ��ָ֪ͨ�������Ա�Խ��յ���ʱ��ָ֪ͨ���ʱ��
	2��Э�̷�ʽ����ʱ���������ڵ㷢��ʱ���ƽ������ɷ���������ʱ���ƽ�����ʱ���ƽ�ָ֪ͨ��֪ͨ����ڵ�
	ʱ������÷���
	1��֪ͨ��ʽ��
	�������ˣ�
			a)��ʼ����initSvr��
			b)����ʱ�����startSerrvice();
	����ڵ㣺
			a)��ʼ����initMember��
			b)�ǼǷ���ʱ�䲽����registerTimeStep��

			c)ѭ����ѯʱ���ƽ�ָ֪ͨ��շ����ݡ�(hasTimeAdvanced)
			d)�����˳���
			��ע�� unregister();
	2��Э�̷�ʽ����ʱ�����
	�������ˣ�
			a)��ʼ����initSvr��
			b)����ʱ�����startSerrvice();
	����ڵ㣺
			a)��ʼ����initMember��
			b)ע���Ա����ȡ��ǰ����ʱ�� ��registerFederate��

			c)����ʱ���ƽ�����(RequestTimeAdvance)
			d)ѭ����ѯʱ���ƽ�ָ֪ͨ��շ����ݡ�(hasTimeAdvanced)
			e)�ظ�c)��d)

			f)�����˳���
			��ע�� unregister();
*********************************************************************/
#include <list>
#include "ddalib_export.h"
using namespace std;

class TimeMgrData;
class TimeMgrSvrData;
enum TimeMgType{ TMG_Notice,TMG_Negotiate };
//����ڵ����ӿ�
class _DDSLIB_API TimeMgr
{
public:
	static TimeMgr & GetInstance();
	static TimeMgr* GetInstancePtr();
	///��ѯ�����ʱ���ƽ�����,����-1����ѯʧ��
	int queryServerTmTyp();
//��ʼ��  
	///����ڵ��ʼ�����˺���ֻ����һ��
	bool initMember(TimeMgType typ);//typ��������������һ��
	//************************************
	// Method:    �ڵ�ע�ᣬ���˺���ֻ����һ�Σ���TMG_Noticeʱ������ô˺�����
	// ������     ftimeΪ����ע��ʱ����ʱ�䡣
	// ����ֵ:    Ϊ�������,������falseʱ������getLastError�ɻ�ȡ������Ϣ��
	//************************************
	bool registerFederate(double &ftime);
	//************************************
	// Method:    �ǼǷ���ʱ�䲽������TMG_Notice����ʱʹ��
	//            ��������δ����ʱ���س�ʱ��Ϣ,��λms
	//************************************
	bool registerTimeStep(unsigned int step);
	
	//************************************
	// Method:    ��ע�ᣬ֪ͨserver�˳�Ա�˳�������ʱ�����ģʽ���ô˺�����ע��
	// ����ֵ:    ��ע��ɹ�����true
	//************************************
	bool unregister();

	//************************************
	// Method:    ���ص�ǰ��Ա�Ƿ��Ѿ�ע��
	// ����ֵ:    
	//************************************
	bool hasregistered();
//
	///ʱ���ƽ�����TMG_Negotiateʱʹ��
	bool RequestTimeAdvance(double t);///<����ʱ���ƽ���t,t������ڵ��ڵ�ǰʱ��,������������(Э�̲�����ʽ��Ч)
	///��ѯʱ���ƽ�ָ֪ͨ��
	bool hasTimeAdvanced(double& t);///<��ѯʱ���ƽ�ָ֪ͨ��,����ֵ��true:���յ�ָ֪ͨ�ʱ���ƽ���t��false��δ�յ�ָ֪ͨ������ƽ���ʱ��δ����
//
	inline string getLastError(){ return *m_errString;}
	double currentTime();///<��ǰʱ��
protected:
	TimeMgr(void);
	~TimeMgr(void);
private:
	string *m_errString;
	TimeMgrData *m_timeMgrData;
	bool m_hasregistered;
};
enum regnodeEnum{ REGNODE_REGISTER, REGNODE_UNREGISTER };

struct regnode
{
	regnode(){};
	regnode(unsigned int nd, int nSec, int nMicroSec, unsigned int hd, regnodeEnum s);
	unsigned int sysid;
	double step;
	unsigned int hand;
	regnodeEnum state;
};
//���������Ʒ���ӿ�
class _DDSLIB_API TimeMgrServer
{
public:
	static TimeMgrServer & GetInstance();
	static TimeMgrServer* GetInstancePtr();
//	
	bool initSvr(TimeMgType typ,bool autoStart = true);///<��������ʼ����typ�������������ͣ�autoStart = true��ʼ������Զ���ʼʱ���ƽ�
//
	void startSerrvice();//�������񣬽���ע�ᡢ�Ǽ�
	void stopSerrvice();//��ֹʱ�����
	bool isRunning();//�жϷ����Ƿ�������
	void start();//��ʼʱ���ƽ�
	void pause();//��ͣʱ���ƽ�
	void restart(); /*����ʱ��������¿�ʼ,
					//TMG_Negotiate��֪ͨ������ע���Աʱ���ƽ���0��������hasTimeAdvanced�ɻ�ȡt=0;
				    // TMG_Notice:�����ѵǼǳ�Ա���0ʱ�̿�ʼ�ƽ���
					*/
//
	inline string getLastError(){ return *m_errString;}
	double currentTime();///<��ǰʱ��,S
	void getUpdateNode(int &ncount, regnode nd[]);
	//void setTestHeard(bool);//�����Ƿ����Ա���ߣ�trueʱ�Զ�����Ӧ��ʱ��Ա�˳���������Լ������С�
	/////////////////////////////////////////////////
	//�ڲ�����
	DWORD WINAPI reciveData();
	DWORD WINAPI timeAdvance();
	void updateDDSProduct(unsigned int sysid,unsigned int inst_state);
	//
protected:
	TimeMgrServer(void);
	~TimeMgrServer(void);
private:
	string *m_errString;
	TimeMgrSvrData *m_timeMgrData;
	volatile bool m_isRun;
	volatile bool m_hasPause;
	volatile bool m_brestart;
};
#endif // __TIMEMGR_H__

