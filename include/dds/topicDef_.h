/*!
 * �� �� ����topicDef.h
 * �����ռ䣺
 * ��    �ܣ�DDS���乫�����ݶ����ļ���xml�ļ���Topic���ó����밴���ļ����峤�ȶ���
 *	ע�⣺�����ַ������ݲ���utf-8����
 * ��    �ߣ�MYS
 * ͨ    Ѷ��
 * �������ڣ�
 * �� �� �ţ�V1.0.0.0
 * �޸���־��
 *
 *
*/
#pragma once

//�豸����
#define MAXDEVICECOUNT	32	
//���ݿ����
#define MAXDATACOUNT		32

#pragma pack(push, 4)

//Topic���ݳ���
const unsigned int G_TDS_SysBitRequest = 140;			//ϵͳ/�豸�Լ�
const unsigned int G_TDS_SysResetRequest = 136;			//ϵͳ/�豸��λ
const unsigned int G_TDS_RadBitRFRequest = 40;			//����ջ��Լ�-��Ƶ
const unsigned int G_TDS_RadBitSDRequest = 40;			//����ջ��Լ�-Ƶ��
const unsigned int G_TDS_ScnDldRequest = 24;			//������������
const unsigned int G_TDS_SysCtrlRequest = 36;			//ϵͳ���п���
const unsigned int G_TDS_SysStqRequest = 4;				//ϵͳ/�豸״̬��ѯ
const unsigned int G_TDS_ScnPlatUpdate = 3084;			//����ƽ̨���ݸ���
const unsigned int G_TDS_ScnEmtEvent = 1672;			//��������Դ�¼�
const unsigned int G_TDS_ScnWpnEvent = 520;				//���������¼�
const unsigned int G_TDS_RPScnPlatUpdate = 3084;		//�����ط�ƽ̨���ݸ���
const unsigned int G_TDS_RPScnEmtEvent = 1672;			//�����طŷ���Դ�¼�
const unsigned int G_TDS_RPScnWpnEvent = 520;			//�����ط������¼�
const unsigned int G_TDS_ScnDatMixNotify = 232;			//��������Դ�ں�����
const unsigned int G_TDS_SysBitReply = 16524;			//ϵͳ/�豸�Լ�ظ�
const unsigned int G_TDS_ScnDldNotify = 260;			//�����������ػظ�
const unsigned int G_TDS_SysRdyNotify = 268;			//ϵͳԤλ�ϱ�
const unsigned int G_TDS_SysStqReply = 16524;			//ϵͳ/�豸״̬��ѯ�ظ�
const unsigned int G_TDS_RadBitSPNotify = 8200;			//����ջ��Լ�-Ƶ���ϱ�
const unsigned int G_TDS_DevInstNotify = 2384;			//�豸����ָ���ϱ�
const unsigned int G_TDS_RadPltNotify = 184;			//�״�㼣�ϱ�
const unsigned int G_TDS_RadTrkNotify = 104;			//�״ﺽ���ϱ�
const unsigned int G_TDS_RadParmNotify = 56;			//�״﹤�������ϱ�
const unsigned int G_TDS_SutChsNotify = 264;			//SUT��ѡ�����ϱ�
const unsigned int G_TDS_SimSutEvent = 1;				//SUT�����¼���Ԥ����

//1.ϵͳ�Լ�
struct TPC_SysBitRequest
{
	int subSysId;					///<Ŀ����ϵͳID
	int bitMdl;						///<�Լ췽ʽ 0-�ϵ��Լ죬1-ά���Լ�
	int bitDevCnt;					///<�Լ��豸����N
	int devId[MAXDEVICECOUNT];		///<�豸Id,��Ч��N
};
//2.ϵͳ��λ
struct TPC_SysResetRequest
{
	int subSysId;					///<Ŀ����ϵͳID
	int resetDevCnt;				///<��λ�豸����N
	int devId[MAXDEVICECOUNT];		///<�豸Id,��Ч��N
};

//3.����ջ��Լ� - �źŷ���			
struct TPC_RadBitRFRequest
{
	int		subSysId;					///<Ŀ����ϵͳID
	int		devId;						///<�豸Id
	int		sigRFSw;					///<��Ƶ���� 1-����Ƶ��0-����Ƶ
	int		sigMod;						///<�ź���ʽ 0-��������1-����
	double	plsFreq;					///<Ƶ��
	double	plsPrd;						///<�ظ�����
	double	plsPW;						///<����
};
//4.����ջ��Լ� - �źż��			
struct TPC_RadBitSDRequest
{
	int		subSysId;					///<Ŀ����ϵͳID
	int		bStart;						///<Ƶ���ϱ� 1-��ʼ��0-ֹͣ
	int		sigMod;						///<�ź���ʽ  0-��������1-����
	double	plsCntFreq;					///<����Ƶ��	 400-18000
	double	montPlsBW;					///<������
	double	freqRes;					///<Ƶ�ʷֱ���
};
//5.��������
struct TPC_ScnDldRequest
{
	int subSysId;						///<Ŀ����ϵͳID
	int scnId;							///<����ID
	int scnFileMD5[4];					///<xml�ļ�MD5�������ļ�������У��
};
//6.���п���
struct TPC_SysCtrlRequest
{
	int subSysId;						///<Ŀ����ϵͳID
	int cmdCode;						///<�����룺0-��ʼ��1-������2-��ͣ��3-�ָ���4�Ժ�Ԥ������ͣ/�ָ��Ƚϸ��ӣ������һ������
	int excTime[6];						///<ִ��ʱ�䣺��,�£��գ�ʱ���֣���
	int tskId;							///<��������Id
};
//7.״̬��ѯ
struct TPC_SysStqRequest
{
	int subSysId;						///<Ŀ����ϵͳID
};
//8.1 ƽ̨����
struct ScnPlat
{
	int	  plat_id;					///<ƽ̨Id
	float lon;						///< ����
	float lat;						///< γ��
	float alt;						///< �߶�
	float hdg;						///< ƫ�� վ��ֱ�ǣ������죩����ϵ�£�����ʸ��������ϵƽ��н�
	float pch;						///< ����
	float rol;						///< ���
	float spdEast;					///<�ٶȶ��� վ��ֱ�ǣ������죩����ϵ�������ٶȣ���������
	float spdNorth;					///<�ٶȱ���
	float spdUp;					///<�ٶ�����
	float accEast;					///<���ٶȶ���
	float accorth;					///<���ٶȱ���
	float accUp;					///<���ٶ�����
	float ROThdg;					///<���ٶ�ƫ��
	float ROTpch;					///<���ٶȸ���
	float ROTrol;					///<���ٶȺ��
};
//8.����ƽ̨����
struct TPC_ScnPlatUpdate
{
	int		simNo;					///<��������������
	int		sunPlatCnt;				///<SUTƽ̨����M 1-16
	ScnPlat sutPlat[16];			///<SUTƽ̨���ݿ�,��Ч��M
	int		emtPlatCnt;				///<����Դƽ̨����N 1-1024
	ScnPlat emtPlat[MAXDATACOUNT];	///<����Դƽ̨���ݿ�,��Ч��N
};
//9.1����Դ�¼�
struct EmtEvtAttr
{
	int platId;						//����ƽ̨Id����ƽ̨�����е�Idһ��
	int	emtId;						//����ԴId
	int entCode;					//�¼���,0:�ػ���2��ģʽ�л���3������Ŀ���л���4��Ԥ��
	int tgtMdl;						//Ŀ��ģʽId:�¼�Ϊģʽ�л�ʱ��Ч��Ŀ�깤��ģʽId
	int trkTgtCnt;					//����Ŀ������
	int trkTgtIdLst[8];				//����Ŀ��id�б�
};
//9.����Դ�¼�	
struct TPC_ScnEmtEvent
{
	int			simNo;						///<��������������
	int			emtEvtCnt;					///<����Դ�¼�����N
	EmtEvtAttr	emtEvt[MAXDATACOUNT];		///<����Դ�¼���,��Ч��N
};
//10.1�����¼��¼���
struct WpnEvtAttr
{
	int	ownPlatId;					//����ƽ̨Id
	int tgtPlatId;					//Ŀ��ƽ̨Id
	int wpnId;						//����Id
	int evtId;						//�¼�Id 0-���䣬1-��ը��2�Ժ�Ԥ����
};
//10.�����¼�	
struct TPC_ScnWpnEvent
{
	int			simNo;				///<��������������
	int			wpnEvtCnt;				///<�����¼�����N
	WpnEvtAttr	wpnEvt[MAXDATACOUNT];		///<�����¼�,��Ч��N
};
//11.�ط� - ����ƽ̨����	
struct TPC_RPScnPlatUpdate
{
	int		simNo;					///<��������������
	int		sunPlatCnt;				///<SUTƽ̨����M 1-16
	ScnPlat sutPlat[16];			///<SUTƽ̨���ݿ�,��Ч��M
	int		emtPlatCnt;				///<����Դƽ̨����N 
	ScnPlat emtPlat[MAXDATACOUNT];			///<����Դƽ̨���ݿ�,��Ч��N
};
//12.�ط� - ����Դ�¼�	
struct TPC_RPScnEmtEvent
{
	int			simNo;				///<��������������
	int			emtEvtCnt;			///<����Դ�¼�����N
	EmtEvtAttr	emtEvt[MAXDATACOUNT];		///<����Դ�¼���,��Ч��N
};
//13.�ط� - �����¼�	
struct TPC_RPScnWpnEvent
{
	int			simNo;				///<��������������
	int			wpnEvtCnt;				///<�����¼�����N
	WpnEvtAttr	wpnEvt[MAXDATACOUNT];		///<�����¼�,��Ч��N
};
//////////////////////////////////////////////////////////////////////////
//�ظ�����
//14.��������Դ�ں��ϱ���Ϣ
typedef struct TPC_ScnDatMixNotify
{
	//int			simNo;							///<��������������
	int			simTime[7];						///<����ʱ��,��,�£��գ�ʱ���֣���,����
	int			platId;							///<ƽ̨Id
	int			emtId;							///<����ԴId
	int			platForce;						///<ƽ̨�������� 0-δ���壬1-�ҷ���2-�з���3-�ѷ���4-������5�Ժ�Ԥ����
	int			platCat;						///<ƽ̨���� 0-δ֪��1-����̶���2-�����ƶ���3-ˮ�棬4-ˮ�£�5-������6-�̶���7-��ת��8-���˻���9-���ǣ�10-����ƽ̨��12-��Я��13�Ժ�Ԥ��
	int			emtTyp;							///<����Դ ����0-δ֪��1-�����״2-�Կվ����״3-�Ժ������״4-�Ϳվ����״5-�����״6-Ŀ��ָʾ�״7-����״8-Ԥ���״9-����Ԥ���״10-���������״11-�����״12-�����Ƶ��״13-���������״14-���׹����״15-�๦���״16-����ĩ�Ƶ��״17-��ը��׼�״18-����״19-ս������״20-��λ���У���״21-�Ŀ�����У���״22-���չ����״23-�����״24-���θ����״25-��½�����״26-�ۿڼ����״27-�����״28-�����״29-����ʶ������30-�����״31-�����״�
	double		platPos[3];						///<ƽ̨λ��,���� γ�� �߶�
	double		platAzim;						///<ƽ̨��λ
	double		platElev;						///<ƽ̨����
	double		platSdist;						///<ƽ̨б��
	double		tgtRadSpd;						///<Ŀ�꾶���ٶ� ��Ϊ�ӽ�����ΪԶ��
	double		tgtTagSpd;						///<Ŀ�������ٶ� ��Ϊ��ʱ�룬��Ϊ˳ʱ��
	double		sigPowCode;						///<�źŹ�����  dBm - 120 - 100
	int			emtWkMod;						///<����Դ����ģʽ 0-δ֪��1-������2-���٣�3-�Ƶ���4-TWS��5-TAS��6�Ժ�Ԥ��
	int			emtPlorMod;						///<����Դ������ʽ 0-δ֪��1-��Բ������2-��Բ������3-��ֱ������4-ˮƽ������5-б������6-������ѡ��7-�������룬8-�����ݱ䣬9-������Բ������10-������Բ������11�Ժ�Ԥ��
	int			sigFM;							///<�źŵ��Ʒ�ʽ 0-������1-���棬2-�����Ե�Ƶ��3-���Ե�Ƶ��4-������룬5-������룬6-Ƶ�ʱ��룬7-Ƶ�ʷּ���8�Ժ�Ԥ��
	double		sigScanProd;					///<ɨ������
	double		beamDwlTm;						///<��λפ��ʱ��
	double		IntfDur;						///<��ɴ�����
	int			sigRFTyp;						///<�ź�Ƶ������ 0-������1-�̶���2-��䣬3-�ּ���4-���룬5-�ݱ䣬6-��Ƶ�β7-������Ƶ�ʵ��ƣ�8-������������ƣ�9-�������������ƣ�10-����Ƶ�ʱ��룬11�Ժ�Ԥ��
	int			sigRFCnt;						///<�ź�Ƶ����
	double		sigRFMed;						///<�ź�Ƶ����ֵ
	double		sigRFRng;						///<�ź�Ƶ�ʷ�Χ
	int			sigPRITyp;						///<�ź�PRI���� 0-������1-�̶���2-���䣬3-������4-�ݱ䣬5-�β6-���룬7-���䣬8-��������9�Ժ�Ԥ��
	int			sigPRICnt;						///<�ź�PRI����
	double		sigPRIMed;						///<�ź�PRI��ֵ
	double		sigPRIRng;						///<�ź�PRI��Χ
	int			sigPWTyp;						///<�ź�PW���� 0-������1-�̶���2-�仯��3�Ժ�Ԥ��
	int			sigPWCnt;						///<�ź�PW����
	double		sigPWMed;						///<�ź�PW��ֵ
	double		sigPWRng;						///<�ź�PW��Χ
}TPCSCNEMT;
//15.1 �豸����
struct  DevPara
{
	int  devId;							//�豸Id
	int	 bitResult;						///<�豸�Լ�/����״̬��� 0-�ɹ���1-ʧ�ܣ�3�Ժ�Ԥ���� 
	char para[512];						//�����飬������ϵͳ�ṩ��xml���и�ʽ������
};
//15.�Լ�ظ�	
struct TPC_SysBitReply
{
	int		subSysId;							///<Ŀ����ϵͳID
	int		sysBitCnt;							///<�豸�Լ�������N
	DevPara sysBitData[MAXDEVICECOUNT];			///<�豸�Լ���,��Ч��N
};
//16.���ػظ�	
struct TPC_ScnDldNotify
{
	int subSysId;								///<Ŀ����ϵͳID
	int retResult;								///<ִ�н�� 0-�ɹ���1-ʧ�ܣ�2�Ժ�Ԥ��
	char errMsg[256];							///<�������� �����ϵͳִ�н������ʧ�ܣ���ͬʱ���ش��������ַ���
};
//17.Ԥλ�ϱ�	
struct TPC_SysRdyNotify
{
	int subSysId;								///<Ŀ����ϵͳID
	int devId;									///<�豸Id ���豸��������Ψһ��ʶ��0xffffffffʱ��ʾ�豸ȫԤλ����ϵͳ�������׼��
	int retResult;								///<ִ�н�� 0-�ɹ���1-ʧ�ܣ�2�Ժ�Ԥ��
	char errMsg[256];							///<�������� �����ϵͳִ�н������ʧ�ܣ���ͬʱ���ش��������ַ���
};
//18.״̬�ظ�	
struct TPC_SysStqReply
{
	int subSysId;								///<Ŀ����ϵͳID
	int retResult;								///<��ϵͳ״̬��ѯ��� 0 - ������1 - �쳣��2�Ժ�Ԥ����
	int	devCnt;									///<�豸����N
	DevPara devState[MAXDEVICECOUNT]; 			///<�豸״̬,������Ч����N
};
//19.����ջ��Լ� - Ƶ���ϱ�	
struct TPC_RadBitSPNotify
{
	int subSysId;								///<Ŀ����ϵͳID
	int	devCnt;									///<Ƶ�׵���N
	double FreqRange[1024]; 					///<Ƶ�����,������Ч����N
};
//20.1 ָ�����
struct CmdParaDef
{
	char	paraName[32];						//��������
	double	val;								//����ֵ
	char	strUnit[32];						//������λ
};
//20.�豸����ָ���ϱ�	
struct TPC_DevInstNotify
{
	int			subSysId;							///<Ŀ����ϵͳID
	int			devId;								///<�豸Id
	char		cmdName[64];						///<ָ�������ַ���
	int			cmpParaCnt;							///<ָ���������N
	CmdParaDef	cmpPara[MAXDATACOUNT]; 				///<ָ�����,������Ч����N
};
//21.�㼣�ϱ�	
struct TPC_RadPltNotify
{
	int			radId;							///<�״�Id,ʵ�ʷ����״��豸��ʶ��0-38�״1-�׿��״2-23���״3֮��Ԥ��
	int			pltId;							///<�㼣Id
	int			pltRecTime[7];					///<�㼣ʱ��,��,�£��գ�ʱ���֣���,����
	double		pltDst;							///<�㼣����
	double		pltDop;							///<�㼣������
	int			vertBeamNo;						///<��ֱ������
	int			horzBeamNo;						///<ˮƽ������
	int			FCCnt;							///<Ƶ����
	int			FCFlag;							///<Ƶ����ʶ
	int			plsGrpFlag;						///<�����ʶ
	int			ERCnt;							///<EP��
	double		begDst;							///<��ʼ����
	double		endDst;							///<��������
	double		begDrc;							///<��ʼ��λ
	double		endDrc;							///<������λ
	double		orgAD;							///<ԭʼAD
	double		bgAD;							///<����AD
	double		begDstRange;					///<��ʼ�������
	double		endDstRange;					///<�����������
	double		begDrcRange;					///<��ʼ��λ����
	double		endDrcRange;					///<������λ����
	double		beamRange;						///<��������
	double		fanLev;							///<�����ȼ�
	int			pltQuality;						///<�㼣����
	int			pltFlat;						///<�㼣��־
};
//22.�����ϱ�	
struct TPC_RadTrkNotify
{
	int			radId;							///<�״�Id,ʵ�ʷ����״��豸��ʶ��0-38�״1-�׿��״2-23���״3֮��Ԥ��
	int			trkId;							///<�㼣Id
	int			trkRecTime[7];					///<�㼣ʱ��,��,�£��գ�ʱ���֣���,����
	double		calDst;							///<Ԥ�����
	double		calAzim;						///<Ԥ�ⷽλ
	int			IFFCode;						///<IFF����
	double		observeDst;						///<�۲����
	double		observeDrc;						///<�۲ⷽλ
	int			trkQuality;						///<��������
	int			mod1Ans;						///<�����״�ģʽ1Ӧ��
	int			mod2Ans;						///<�����״�ģʽ2Ӧ��
	int			mod3aAns;						///<�����״�ģʽ3 / AӦ��
	double		SSRAlt;							///<�����״�߶�
};
//23.�״�����ϱ�	
struct TPC_RadParmNotify
{
	int			radId;							///<�״�Id,ʵ�ʷ����״��豸��ʶ��0-38�״1-�׿��״2-23���״3֮��Ԥ��
	int			trkId;							///<�㼣Id
	int			recTime[7];						///<�㼣ʱ��,��,�£��գ�ʱ���֣���,����
	int			OpModId;						///<����ģʽId
	int			freqCode;						///<Ƶ����
	int			syncPulse;						///<ͬ������
	double		ISR;							///<���ű�

};
//24.��ѡ�ϱ�	
typedef struct TPC_SutChsNotify
{
	int			sutPlatId;						///<SUT�ڳ����е����������ڶ��ػ�����
	int			recTime[7];						///<��ѡ����ʱ��,��,�£��գ�ʱ���֣���,����
	int			tgtBatchNum;					///<Ŀ������
	int			tgtForce;						///<Ŀ��������� 0-δ���壬1-�ҷ���2-�з���3-�ѷ���4-������5�Ժ�Ԥ����
	int			tgtPlatCat;						///<Ŀ��ƽ̨���� 0-δ֪��1-����̶���2-�����ƶ���3-ˮ�棬4-ˮ�£�5-������6-�̶���7-��ת��8-���˻���9-���ǣ�10-����ƽ̨��12-��Я��13�Ժ�Ԥ��
	int			tgtThreatGrade;					///<Ŀ����в�ȼ�
	int			emtTyp;							///<����Դ ����0-δ֪��1-�����״2-�Կվ����״3-�Ժ������״4-�Ϳվ����״5-�����״6-Ŀ��ָʾ�״7-����״8-Ԥ���״9-����Ԥ���״10-���������״11-�����״12-�����Ƶ��״13-���������״14-���׹����״15-�๦���״16-����ĩ�Ƶ��״17-��ը��׼�״18-����״19-ս������״20-��λ���У���״21-�Ŀ�����У���״22-���չ����״23-�����״24-���θ����״25-��½�����״26-�ۿڼ����״27-�����״28-�����״29-����ʶ������30-�����״31-�����״�
	double		tgtPos[3];						///<Ŀ��λ��,���� γ�� �߶�
	double		tgtAzim;						///<Ŀ�귽λ
	double		tgtElev;						///<Ŀ�긩��
	double		tgtAzimVar;						///<Ŀ�귽λ����
	double		tgtElevVar;						///<Ŀ�긩������
	double		tgtSdist;						///<Ŀ��б��
	double		tgtSdistVar;					///<Ŀ��б�෽��
	double		tgtRadSpd;						///<Ŀ�꾶���ٶ� ��Ϊ�ӽ�����ΪԶ��
	double		tgtTagSpd;						///<Ŀ�������ٶ� ��Ϊ��ʱ�룬��Ϊ˳ʱ��
	int			emtCode;						///<���������
	int			emtWkMod;						///<����Դ����ģʽ 0-δ֪��1-������2-���٣�3-�Ƶ���4-TWS��5-TAS��6�Ժ�Ԥ��
	int			emtPlorMod;						///<����Դ������ʽ 0-δ֪��1-��Բ������2-��Բ������3-��ֱ������4-ˮƽ������5-б������6-������ѡ��7-�������룬8-�����ݱ䣬9-������Բ������10-������Բ������11�Ժ�Ԥ��
	int			sigFM;							///<�źŵ��Ʒ�ʽ 0-������1-���棬2-�����Ե�Ƶ��3-���Ե�Ƶ��4-������룬5-������룬6-Ƶ�ʱ��룬7-Ƶ�ʷּ���8�Ժ�Ԥ��
	double		sigScanProd;					///<ɨ������
	double		beamDwlTm;						///<��λפ��ʱ��
	double		IntfDur;						///<��ɴ�����
	int			sigState;						///<�źŻ״̬ 0-���źţ�1-��źţ�2-��ʱ��ʧ�źţ�3-��ʧ�����źţ�4-��ʧ�źţ�5�Ժ�Ԥ��
	int			sigIntfMark;					///<�źŸ��ű�� 0-δ���ţ�1-��Դ���ţ�2-��Դ���ţ�3-��Դ���ż���Դ���ţ�4-HPECM��5�Ժ�Ԥ��
	int			sigFreqTyp;						///<�ź�Ƶ������ 0-������1-�̶���2-��䣬3-�ּ���4-���룬5-�ݱ䣬6-��Ƶ�β7-������Ƶ�ʵ��ƣ�8-������������ƣ�9-�������������ƣ�10-����Ƶ�ʱ��룬11�Ժ�Ԥ��
	int			sigFPCnt;						///<�ź�Ƶ����
	double		sigFreqMed;						///<�ź�Ƶ����ֵ
	double		sigFreqRng;						///<�ź�Ƶ�ʷ�Χ
	int			sigPRITyp;						///<�ź�PRI���� 0-������1-�̶���2-���䣬3-������4-�ݱ䣬5-�β6-���룬7-���䣬8-��������9�Ժ�Ԥ��
	int			sigPRICnt;						///<�ź�PRI����
	double		sigPRIMed;						///<�ź�PRI��ֵ
	double		sigPRIRng;						///<�ź�PRI��Χ
	int			sigPWTyp;						///<�ź�PW���� 0-������1-�̶���2-�仯��3�Ժ�Ԥ��
	int			sigPWCnt;						///<�ź�PW����
	double		sigPWMed;						///<�ź�PW��ֵ
	double		sigPWRng;						///<�ź�PW��Χ
}TPCSUTEPL;
//25.SUT�¼�	
struct TPC_SimSutEvent
{
	//����
};

#pragma pack(pop)
