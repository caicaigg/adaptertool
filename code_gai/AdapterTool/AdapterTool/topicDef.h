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
//Ƶ��/���ܵ�/������������
#define MAXSEQLEN	32

#pragma pack(push, 1)

//Topic���ݳ���
// const unsigned int G_TDS_SysHaltRequest				= 1    ;					//1ϵͳ��ͣ���޲���
// const unsigned int G_TDS_SysBitRequest				= 140  ;					//2ϵͳ/�豸�Լ�
// const unsigned int G_TDS_SysResetRequest				= 136  ;					//3ϵͳ/�豸��λ
// const unsigned int G_TDS_RadBitRFRequest2			= 102420;				//4��Ƶ����
// const unsigned int G_TDS_RadBitRFRequest				= 48;					//4����ջ��Լ�-��Ƶ
// const unsigned int G_TDS_RadBitSDRequest				= 32   ;					//5����ջ��Լ�-Ƶ��  			36
// const unsigned int G_TDS_ScnDldRequest				= 24   ;					//6������������
// const unsigned int G_TDS_SysRdyRequest				= 4    ;					//7ϵͳԤλ
// const unsigned int G_TDS_SysCtrlRequest				= 36   ;					//8ϵͳ���п���
// const unsigned int G_TDS_SysStqRequest				= 4    ;					//9ϵͳ/�豸״̬��ѯ
// const unsigned int G_TDS_ScnPlatUpdate				= 2316 ;					//10����ƽ̨���ݸ���
// const unsigned int G_TDS_ScnEmtEvent					= 2056 ;					//11��������Դ�¼�
// const unsigned int G_TDS_ScnWpnEvent					= 520  ;					//12���������¼�
// const unsigned int G_TDS_RPScnDldRequest				= 24   ;					//13�ط�-������������
// const unsigned int G_TDS_RPScnPlatUpdate				= 2316 ;					//14�����ط�ƽ̨���ݸ���
// const unsigned int G_TDS_RPScnEmtEvent				= 2056 ;					//15�����طŷ���Դ�¼�
// const unsigned int G_TDS_RPScnWpnEvent				= 520  ;					//16�����ط������¼�
// const unsigned int G_TDS_OwnInsUpdate				= 148  ;					//17�ػ��ߵ����ݸ���	
// const unsigned int G_TDS_ScnSimEvent					= 7688 ;					//18���������¼�
// const unsigned int G_TDS_ScnDatMixNotify				= 615  ;					//��������Դ�ں������ϱ�     228
// const unsigned int G_TDS_SysHaltNotify				= 516  ;					//ϵͳ��ͣ�ϱ�
// const unsigned int G_TDS_SysBitReply					= 8460 ;					//20ϵͳ/�豸�Լ�ظ�
// const unsigned int G_TDS_ScnDldNotify				= 264  ;					//�����������ػظ�
// const unsigned int G_TDS_SysRdyNotify				= 8460 ;					//ϵͳԤλ�ϱ�			
// const unsigned int G_TDS_SysStqReply					= 16524;					//ϵͳ/�豸״̬��ѯ�ظ�
// const unsigned int G_TDS_RadBitSPNotify				= 8220 ;					//����ջ��Լ�-Ƶ���ϱ�		
// const unsigned int G_TDS_DevInstNotify				= 2380 ;					//25�豸����ָ���ϱ�			2384
// const unsigned int G_TDS_RadPltNotify				= 180  ;					//�״�㼣�ϱ�			184
// const unsigned int G_TDS_RadTrkNotify				= 96   ;					//�״ﺽ���ϱ�			104
// const unsigned int G_TDS_RadParmNotify				= 5700 ;					//�״﹤�������ϱ�
// const unsigned int G_TDS_SutChsNotify				= 515  ;					//SUT��ѡ�����ϱ�		452
// const unsigned int G_TDS_ECMSPNotify					= 8216 ;					//30ECMƵ���ϱ�
// const unsigned int G_TDS_SimSutEvent					= 1    ;					//SUT�����¼���Ԥ����
// const unsigned int G_TDS_VehicleHPRUpt				= 900  ;					//���泵������̬���ݸ���
// const unsigned int G_TDS_ExtPlatUpdate				= 2080 ;					//�ⲿƽ̨��������
// const unsigned int G_TDS_ExtEmtEvetn					= 100  ;					//�ⲿ����Դ�¼�����
// const unsigned int G_TDS_ExtSutAntScEvent			= 68   ;					//�ⲿSUT����ɨ���¼�����

//																				 
//����ֵ��������
const enum { ACK_SUCCESS = 0, ACK_FAILE =1};
typedef unsigned char uchar;
typedef unsigned int uint;
//1.ϵͳ��ͣ
struct TPC_SysHaltRequest
{
};
//2.ϵͳ�Լ�
struct TPC_SysBitRequest
{
	int subSysId;					///<Ŀ����ϵͳID
	int bitMdl;						///<�Լ췽ʽ 0-�ϵ��Լ죬1-ά���Լ�
	int bitDevCnt;					///<�Լ��豸����N
	int devId[MAXDEVICECOUNT];		///<�豸Id,��Ч��N
};
//3.ϵͳ��λ
struct TPC_SysResetRequest
{
	int subSysId;					///<Ŀ����ϵͳID
	int resetDevCnt;					///<��λ�豸����N
	int devId[MAXDEVICECOUNT];		///<�豸Id,��Ч��N
};

//4.����ջ��Լ� - �źŷ���			
struct TPC_RadBitRFRequest
{
	int		subSysId;					///<Ŀ����ϵͳID
	int		devId;						///<�豸Id
	int		sigRFSw;						///<��Ƶ���� 1-����Ƶ��0-����Ƶ
	int		sigMod;						///<�ź���ʽ 0-��������1-����
	double	plsFreq;						///<Ƶ��
	double	plsPrd;						///<�ظ�����
	double	plsPW;						///<����
	double	sigAzim;						///<�źŷ�λ����
};
//4.����ջ��Լ� - �źŷ���2,�����źŷ���ʱ���ݸ����ź�
struct TPC_RadBitRFRequest2
{
	int		subSysId;					///<Ŀ����ϵͳID
	int		devId;						///<�豸Id
	int		sigRFSw;						///<��Ƶ���� 1-����Ƶ��0-����Ƶ
	double	sigAzim;						///<�źŷ�λ����
	char    sig[102400];					///<�źŲ���dom
};
//5.����ջ��Լ� - �źż��			
struct TPC_RadBitSDRequest
{
	int		subSysId;					///<Ŀ����ϵͳID
	int		bStart;						///<Ƶ���ϱ� 1-��ʼ��0-ֹͣ
	double	plsCntFreq;					///<����Ƶ��	 400-18000
	double	montPlsBW;					///<������
	double	freqRes;					///<Ƶ�ʷֱ���
};
//6.��������
struct TPC_ScnDldRequest
{
	int subSysId;						///<Ŀ����ϵͳID
	int scnId;							///<����ID
	int scnFileMD5[4];					///<xml�ļ�MD5�������ļ�������У��
};
//7.ϵͳԤλ
struct TPC_SysRdyRequest
{
	int subSysId;						///<Ŀ����ϵͳID
};
//8.���п���
struct TPC_SysCtrlRequest
{
	int subSysId;						///<Ŀ����ϵͳID
	int cmdCode;							///<�����룺0-��ʼ��1-������2-��ͣ��3-�ָ���4-��ʼ�طţ�5-ֹͣ�طţ�6-��ͣ�طţ�7-�ָ��طţ�8�Ժ�Ԥ������ͣ/�ָ��Ƚϸ��ӣ������һ������
	int excTime[6];						///<ִ��ʱ�䣺��,�£��գ�ʱ���֣���
	int tskId;							///<��������Id
};
//9.״̬��ѯ
struct TPC_SysStqRequest
{
	int subSysId;						///<Ŀ����ϵͳID
};
//10.1 ƽ̨����
struct ScnPlat
{
	int	  plat_id;					///<ƽ̨Id
	INT32 lon;						///< ����
	INT32 lat;						///< γ��
	float alt;						///< �߶�
	float hdg;						///< ƫ�� վ��ֱ�ǣ������죩����ϵ�£�����ʸ��������ϵƽ��н�
	float pch;						///< ����
	float rol;						///< ���
	float spdEast;					///<�ٶȶ��� վ��ֱ�ǣ������죩����ϵ�������ٶȣ���������
	float spdNorth;					///<�ٶȱ���
	float spdUp;						///<�ٶ�����
	float accEast;					///<���ٶȶ���
	float accorth;					///<���ٶȱ���
	float accUp;						///<���ٶ�����
	float ROThdg;					///<���ٶ�ƫ��
	float ROTpch;					///<���ٶȸ���
	float ROTrol;					///<���ٶȺ��
};
//10.����ƽ̨����
struct TPC_ScnPlatUpdate
{
	int		simNo;					///<��������������
	int		sutPlatCnt;				///<SUTƽ̨����M 1-16
	ScnPlat sutPlat[4];				///<SUTƽ̨���ݿ�,��Ч��M
	int		emtPlatCnt;				///<����Դƽ̨����N 1-1024
	ScnPlat emtPlat[MAXDATACOUNT];	///<����Դƽ̨���ݿ�,��Ч��N
};
//11.1����Դ�¼�
struct EmtEvtAttr
{
	int		platId;						//����ƽ̨Id����ƽ̨�����е�Idһ��
	int		emtId;						//����ԴId
	int		tmOff;						//��s	0 - 10000	��Ե�ǰ������ĵ�ʱ��ƫ�ƣ��ø�ϸ��ʱ����������������ɢ�¼�
	int		entCode;						//�¼���,0:�ػ���2��ģʽ�л���3������Ŀ���л���4-Ŀ�귢�֣��״�Ƕȣ���5-Ŀ�궪ʧ��6-�����ţ�7-���߷���ͼ���£�8-�Ժ�Ԥ����
	int		tgtMdl;						//Ŀ��ģʽId:�¼�Ϊģʽ�л�ʱ��Ч��Ŀ�깤��ģʽId
	int		trkTgtCnt;					//����Ŀ������
	int		trkTgtIdLst[8];				//����Ŀ��id�б�
	char		csfNm[8];					//<�Զ��巽��ͼ�ļ�����
};
//11.����Դ�¼�	
struct TPC_ScnEmtEvent
{
	int			simNo;						///<��������������
	int			emtEvtCnt;					///<����Դ�¼�����N
	EmtEvtAttr	emtEvt[MAXDATACOUNT];		///<����Դ�¼���,��Ч��N
};
//12.1�����¼��¼���
struct WpnEvtAttr
{
	int		ownPlatId;					//����ƽ̨Id
	int		tgtPlatId;					//Ŀ��ƽ̨Id
	int		wpnId;						//����Id
	int		evtId;						//�¼�Id 0-���䣬1-��ը��2�Ժ�Ԥ����
};
//12.�����¼�	
struct TPC_ScnWpnEvent
{
	int			simNo;						///<��������������
	int			wpnEvtCnt;					///<�����¼�����N
	WpnEvtAttr	wpnEvt[MAXDATACOUNT];		///<�����¼�,��Ч��N
};
//13.�ط�-������������	
struct TPC_RPScnDldRequest
{
	int subSysId;						///<Ŀ����ϵͳID
	int scnId;							///<����ID
	int scnFileMD5[4];					///<xml�ļ�MD5�������ļ�������У��
};
//14.�ط� - ����ƽ̨����	
struct TPC_RPScnPlatUpdate
{		
	int			simNo;						///<��������������
	int			sunPlatCnt;					///<SUTƽ̨����M 1-16
	ScnPlat		sutPlat[1];					///<SUTƽ̨���ݿ�,��Ч��M
	int			emtPlatCnt;					///<����Դƽ̨����N 
	ScnPlat		emtPlat[MAXDATACOUNT];		///<����Դƽ̨���ݿ�,��Ч��N
};
//15.�ط� - ����Դ�¼�	
struct TPC_RPScnEmtEvent
{
	int			simNo;						///<��������������
	int			emtEvtCnt;					///<����Դ�¼�����N
	EmtEvtAttr	emtEvt[MAXDATACOUNT];		///<����Դ�¼���,��Ч��N
};
//16.�ط� - �����¼�	
struct TPC_RPScnWpnEvent
{
	int			simNo;						///<��������������
	int			wpnEvtCnt;					///<�����¼�����N
	WpnEvtAttr	wpnEvt[MAXDATACOUNT];		///<�����¼�,��Ч��N
};
//17.�ػ��ߵ����ݸ���	
typedef struct TPC_OwnInsUpdate
{
	int			simNo;						///<��������������
	double		ownLon;						///<�ػ����ȣ���
	double		ownLat;						///<�ػ�γ�ȣ���
	double		altBaro;						///<��ѹ�߶ȣ�m
	double		altRad;						///<�״�߶ȣ�m
	double		ownPitch;					///<�����ǣ���
	double		ownRoll;						///<��ת�ǣ���
	double		hdgTrue;						///<�溽�򣬡�
	double		hdgMag;						///<�ź��򣬡�
	double		velEst;						///<�����ٶȣ�m/s
	double		velNth;						///<�����ٶȣ�m/s
	double		velUp;						///<�����ٶȣ�m/s
	double		ownTas;						///<����٣�m/s
	double		grdSpd;						///<���٣�m/s
	double		ackAng;						///<���ǣ���
	double		sldAng;						///<�໬�ǣ���
	double		aclEst;						///<������ٶȣ�m/s^2
	double		aclNst;						///<������ٶȣ�m/s^2
	double		aclUp;						///<������ٶȣ�m/s^2
}TPCOSINS;
//18.1�״﹤��ģʽ�л����¼�	
struct SubEvt_RadWkm
{
	int			swFlg;					///<����λ��0-�ػ���1-������2-ģʽ�л�
	int			tgtWkm;					///<Ŀ�깤��ģʽ������Ϊģʽ�л�ʱ��Ч��Ŀ�깤��ģʽId
};
//18.2�״ﲨλ�л����¼�
struct SubEvt_RadBdw
{
	int			tgtBdwId;				///<Ŀ�겨λId����λId��1��ʼ����ͳһ��ʽ���岨λ���Ź��򣬲�λId��Ӧ��λ����ʸ������
	int			wfmNum;					///<��ǰ��λ����������1~4
	int			wfmLst[4];				///<����Id�б�����Id��Ӧװ������ģ���ļ��в��β���������ӦId
};
//18.3�״ﲨ���л����¼�
struct SubEvt_RadWfm
{
	int			tgtWfmId;				///<Ŀ�겨��Id������Id��Ӧװ������ģ���ļ��в��β���������ӦId
};
//18.4�״����Ŀ���л����¼�
struct SubEvt_RadTrk
{
	int			trkTgtCnt;					///<����Ŀ��������1~32�������ڸ���ģʽ��STT��MTT��TAS�ȣ���Ч������Ŀ������
	int			trkTgtIdLst[32];				///<����Ŀ��Id�б�
};
//18.5�״ﲨ�������л����¼�
struct SubEvt_RadDbf
{
	double		bmPtnFreq;					///<��������ͼƵ�㣺0~100000��MHz
	double		bmPtnStep;					///<��������ͼ������0~10��deg
	int			bmPtnType;					///<��������ͼ���ͣ�0-��λ��1-����
	int			bmPtnPtNum;					///<��������ͼ��Ч������1-720
	//float		bmPtnPtSeq[720];				///<��������ͼ�����У�-200~200��dB
};
//18.6�����������¼�
struct SubEvt_Msl
{
	int			ownPlatId;					///<��������ƽ̨Id
	int			tgtPlatId;					///<����Ŀ��ƽ̨Id
	int			wpnId;						///<��������Id
	int			initGdWkmId;					///<��ʼ�Ƶ�ģʽId
	int			evtCode;						///<�����¼��룺201-���䣬202-��ը��203-Ŀ���л���204-�Ƶ�ģʽ�л�
	int			hitFlag;						///<���б�ʶ��0-�ѰУ�1-���У��¼�Ϊ������ըʱ��Ч
	int			altTgtId;					///<�л�Ŀ��ƽ̨Id���¼�ΪĿ���л�ʱ��Ч
	int			altGdWkmId;					///<�л��Ƶ�ģʽId���¼�Ϊ�Ƶ�ģʽ�л�ʱ��Ч
};
//18.7�����¼�	
struct SimEvt
{
	int			platId;						///<����ƽ̨Id����ƽ̨�����е�Idһ��
	int			emtId;						///<װ��Id
	int			tmOff;						///<ʱ��ƫ��ʱ�䣺0~10000����s��	��Ե�ǰ������ĵ�ʱ��ƫ�ƣ��ø�ϸ��ʱ����������������ɢ�¼�
	int			evtCode;						///<�¼��룺0-�ػ���1-������2-ģʽ�л�
											///<			101-�״ﲨλ�л���102-�״ﲨ���л���103-�״����Ŀ���л���104-�״ﲨ�������л�
											///<			201-�������䣬202-������ը��203-����Ŀ���л���204-�����Ƶ�ģʽ�л�
	SubEvt_RadWkm	seRadWkm;				///<�״�ģʽ�л����¼���
	SubEvt_RadBdw	seRadBdw;				///<�״ﲨλ�л����¼���
	SubEvt_RadWfm	seRadWfm;				///<�״ﲨ���л����¼���
	SubEvt_RadTrk	seRadTrk;				///<�״�����л����¼���
	SubEvt_RadDbf	seRadDbf;				///<�״ﲨ�������л����¼���
	SubEvt_Msl		seRadMsl;				///<�����л����¼���
};
//18.�����¼��·�	
struct TPC_ScnSimEvent
{
	int			simNo;						///<��������������
	int			simEvtCnt;					///<����Դ�¼�����N
	SimEvt		simEvtSeq[MAXDATACOUNT];		///<�¼�����
};

//////////////////////////////////////////////////////////////////////////
//�ظ�����
//41.��������Դ�ں��ϱ���Ϣ
typedef struct TPC_ScnDatMixNotify
{
	int			simTime[7];						///<����ʱ��,��,�£��գ�ʱ���֣���,����
	int			sutId;							///<�ں��ϱ���Ӧ��Sut����ƽ̨Id��Sutƽ̨�ӽǣ�Ԥ������δ����Զೡ��
	int			platId;							///<ƽ̨Id
	int			emtId;							///<����ԴId
	uchar		platForce;						///<ƽ̨�������� 0-δ���壬1-�ҷ���2-�з���3-�ѷ���4-������5�Ժ�Ԥ����
	uchar		platCat;						///<ƽ̨���� 0-δ֪��1-����̶���2-�����ƶ���3-ˮ�棬4-ˮ�£�5-������6-�̶���7-��ת��8-���˻���9-���ǣ�10-����ƽ̨��12-��Я��13�Ժ�Ԥ��
	uchar		emtTyp;							///<����Դ ����0-δ֪��1-�����״2-�Կվ����״3-�Ժ������״4-�Ϳվ����״5-�����״6-Ŀ��ָʾ�״7-����״8-Ԥ���״9-����Ԥ���״10-���������״11-�����״12-�����Ƶ��״13-���������״14-���׹����״15-�๦���״16-����ĩ�Ƶ��״17-��ը��׼�״18-����״19-ս������״20-��λ���У���״21-�Ŀ�����У���״22-���չ����״23-�����״24-���θ����״25-��½�����״26-�ۿڼ����״27-�����״28-�����״29-����ʶ������30-�����״31-�����״�
	float		platPos[3];						///<ƽ̨λ��,���� γ�� �߶�
	float		platAzim;						///<ƽ̨��λ
	float		platElev;						///<ƽ̨����
	float		platSdist;						///<ƽ̨б��
	float		tgtRadSpd;						///<Ŀ�꾶���ٶ� ��Ϊ�ӽ�����ΪԶ��
	float		tgtTagSpd;						///<Ŀ�������ٶ� ��Ϊ��ʱ�룬��Ϊ˳ʱ��
	float		sigPowCode;						///<�źŹ���ֵ  dBm - 120 - 100
	uchar		emtWkMod;						///<����Դ����ģʽ 0-δ֪��1-������2-���٣�3-�Ƶ���4-TWS��5-TAS��6�Ժ�Ԥ��
	uchar		emtPlorMod;						///<����Դ������ʽ 0-δ֪��1-��Բ������2-��Բ������3-��ֱ������4-ˮƽ������5-б������6-������ѡ��7-�������룬8-�����ݱ䣬9-������Բ������10-������Բ������11�Ժ�Ԥ��
	uchar		sigFM;							///<�źŵ��Ʒ�ʽ 0-������1-���棬2-�����Ե�Ƶ��3-���Ե�Ƶ��4-������룬5-������룬6-Ƶ�ʱ��룬8�Ժ�Ԥ��
	uchar		nlfmTp;							///<�����Ե�Ƶ����,�����Ե�Ƶʱ�����ֶ������壬0-δ֪ 1-���ǵ�Ƶ 2-�Ժ�Ԥ��
	float		fmBw;							///<��Ƶ����
	uchar		pfskCodCnt;						///<���ࡢ���������Ԫ����
	uchar		pfskSeq[20];			///<���ࡢ������λ��������
	uchar		fskCnt;							///<�ź�Ƶ����
	float		fskSeq[20];						///<Ƶ�ʱ���ʱ��������ֵ�Ƶ���б��粻��20������0��ʾ��
	float		sigScanProd;					///<ɨ������
	float		beamDwlTm;						///<��λפ��ʱ��
	float		IntfDur;						///<��ɴ�����
	uchar		sigRFTyp;						///<�ź�Ƶ������ 0-������1-�̶���2-��䣬3-�ּ���4-���룬5-�ݱ䣬6-��Ƶ�β7-������Ƶ�ʵ��ƣ�8-������������ƣ�9-�������������ƣ�10-����Ƶ�ʱ��룬11�Ժ�Ԥ��
	uchar		sigRFCnt;						///<�ź�Ƶ����
	float		sigRFMed;						///<�ź�Ƶ����ֵ
	float		sigRFRng;						///<�ź�Ƶ�ʷ�Χ
	float		sigRFSeq[MAXSEQLEN];			///<�ź�Ƶ��Ƶ�����У��涨��ഫ8��Ƶ��
	uchar		sigPRITyp;						///<�ź�PRI���� 0-������1-�̶���2-���䣬3-������4-�ݱ䣬5-�β6-���룬7-���䣬8-��������9�Ժ�Ԥ��
	uchar		sigPRICnt;						///<�ź�PRI����
	float		sigPRIMed;						///<�ź�PRI��ֵ
	float		sigPRIRng;						///<�ź�PRI��Χ
	float		sigPRISeq[MAXSEQLEN];			///<�ź�PRI���ܵ����У��涨��ഫ8������
	uchar		sigPWTyp;						///<�ź�PW���� 0-������1-�̶���2-�仯��3�Ժ�Ԥ��
	uchar		sigPWCnt;						///<�ź�PW����
	float		sigPWMed;						///<�ź�PW��ֵ
	float		sigPWRng;						///<�ź�PW��Χ
	float		sigPWSeq[MAXSEQLEN];				///<�ź�PW��������У��涨��ഫ8������
}TPCSCNEMT;
//42.ϵͳ��ͣ�ϱ�	
struct TPC_SysHaltNotify
{
	int		subSysId;								///<Ŀ����ϵͳID
	char		haltDesc[512];							///<ϵͳ��ͣ˵���������豸����
};
//43.1 �豸�Լ��ԤλӦ�����
struct DevAckPara
{
	int		devId;								///<�豸Id ���豸��������Ψһ��ʶ��0xffffffffʱ��ʾ�豸ȫԤλ����ϵͳ�������׼��
	int		retResult;							///<�豸Ԥλִ�н�� 0-�ɹ���1-ʧ�ܣ�2�Ժ�Ԥ��
	char		errMsg[256];							///<�豸Ԥλ��������
};
//43.�Լ�ظ�	
struct TPC_SysBitReply
{
	int		subSysId;							///<Ŀ����ϵͳID
	int		bitResult;							///<��ϵͳ�Լ��� 0-�ɹ���1-ʧ�ܣ�3�Ժ�Ԥ���� ���в����豸���Լ���ȫ��ͨ���ɹ����в�ͨ����ʧ��
	int		sysBitCnt;							///<�豸�Լ�������N
	DevAckPara sysBitData[MAXDEVICECOUNT];			///<�豸�Լ���,��Ч��N
};
//44.���ػظ�	
struct TPC_ScnDldNotify
{
	int		subSysId;								///<Ŀ����ϵͳID
	int		retResult;								///<ִ�н�� 0-�ɹ���1-ʧ�ܣ�2�Ժ�Ԥ��
	char		errMsg[256];								///<�������� �����ϵͳִ�н������ʧ�ܣ���ͬʱ���ش��������ַ���
};
//45.Ԥλ�ϱ�	
struct TPC_SysRdyNotify
{
	int		subSysId;							///<Ŀ����ϵͳID
	int		retResult;							///<��ϵͳԤλ���
	int		sysRdyCnt;							///<�豸�Լ�������N,ÿ�����32���豸���������������һ��
	DevAckPara sysRdyData[MAXDEVICECOUNT];		///<�豸Ԥλִ�н��
};

//46.1 ���п��ƻظ�
struct  TPC_SysCtrlReply
{
	int		subSysId;								///<Ŀ����ϵͳID
	int		retResult;								///<��ϵͳ״̬��ѯ��� ���п����� 0��������1��������2��Ԥ��;��
};

//46.1 ��У������״̬�ظ�
struct  TPC_BXCControlStateReply
{
	int		subSysId;								///<Ŀ����ϵͳID
	int		retResult;								///<��ϵͳ״̬��ѯ��� ����Դ 0������; 1����������;��
};


//46.1 ״̬�ظ�����
struct  DevPara
{
	int		devId;							//�豸Id
	char	para[512];						//�����飬������ϵͳ�ṩ��xml���и�ʽ������
};
//46.״̬�ظ�	
struct TPC_SysStqReply
{
	int		subSysId;								///<Ŀ����ϵͳID
	int		retResult;								///<��ϵͳ״̬��ѯ��� 0 - ������1 - �쳣��2�Ժ�Ԥ����
	int		devCnt;									///<�豸����N
	DevPara devState[MAXDEVICECOUNT]; 				///<�豸״̬,������Ч����N
};
//47.����ջ��Լ� - Ƶ���ϱ�	
struct TPC_RadBitSPNotify
{
	int		subSysId;							///<Ŀ����ϵͳID
	int		sigFlat;								///<�źű�� 0 - δ�����1 - ���
	double	freqCent;							///<Ƶ����ֵ
	double	sigPow;								///<�źŹ���
	int		freqNum;								///<Ƶ������
	double	freqAmpl[1024];						///<Ƶ�㸳ֵ��dBm
};
//48.1 ָ������ϱ�
struct CmdParaDef
{
	char		paraName[32];						//��������
	double	val;									//����ֵ
	char		strUnit[32];							//������λ
};
//48.�豸����ָ���ϱ�	
struct TPC_DevInstNotify
{
	int			subSysId;							///<Ŀ����ϵͳID
	int			devId;								///<�豸Id
	char			cmdName[64];							///<ָ�������ַ���
	int			cmpParaCnt;							///<ָ���������N
	CmdParaDef	cmpPara[MAXDATACOUNT]; 				///<ָ�����,������Ч����N
};
//49.�㼣�ϱ�	
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
	double		begDstRange;						///<��ʼ�������
	double		endDstRange;						///<�����������
	double		begDrcRange;						///<��ʼ��λ����
	double		endDrcRange;						///<������λ����
	double		beamRange;						///<��������
	double		fanLev;							///<�����ȼ�
	int			pltQuality;						///<�㼣����
	int			pltFlat;							///<�㼣��־
};
//50.�����ϱ�	
struct TPC_RadTrkNotify
{
	int			radId;							///<�״�Id,ʵ�ʷ����״��豸��ʶ��0-38�״1-�׿��״2-23���״3֮��Ԥ��
	int			trkId;							///<�㼣Id
	int			trkRecTime[7];					///<�㼣ʱ��,��,�£��գ�ʱ���֣���,����
	double		calDst;							///<Ԥ�����
	double		calAzim;							///<Ԥ�ⷽλ
	int			IFFCode;							///<IFF����
	double		observeDst;						///<�۲����
	double		observeDrc;						///<�۲ⷽλ
	int			trkQuality;						///<��������
	int			mod1Ans;							///<�����״�ģʽ1Ӧ��
	int			mod2Ans;							///<�����״�ģʽ2Ӧ��
	int			mod3aAns;						///<�����״�ģʽ3 / AӦ��
	double		SSRAlt;							///<�����״�߶�
};

//��  ����
struct TPC_RadTrkNotify_n
{
	UINT32		objectID; 						//װ���������ƽ̨
	UINT32		equipID; 						//װ������ID
	UINT32		pltRecTime[5];					///<�㼣ʱ��,��,�£��գ�ʱ������0-3600000000
	UINT32 		uiPlotId; 						// �㼣���
	UINT16 		uiTrackId;  					// ������
	UINT16 		tgtNo; 							// ��Ŀ����
	UINT8 		subNo;  						// ��Ŀ����
	UINT8 		traceStatus; 					// ����״̬ 0:���� 1:�ָ� 2:����
	UINT8 		ucTrackQuality;  				// �������� 0:���� 1:���� 2:���� 3: ��������
	UINT8 		ucFollowCtrl;  					// ���ٿ��� 0:�������� 1:�������� 2:�մ� 3:���� 4:����
	UINT16 		waveForm;  						// ��ϲ��α��
	INT16 		SNR;  							// ����� 0.1dB����
	INT32		amp;  							// �ز����� dbw
	INT32 		GR;  							// Ŀ����� ��ؼ�����/1m��������ϵ��
	INT32 		GA;  							// Ŀ�귽λ ��ؼ�����/0.01�� -18000-18000
	INT32 		GE;  							// Ŀ�긩�� ��ؼ�����/0.01�� -9000-9000
	INT32 		distErr;  						// ������� ��ؼ�����/1m
	INT32 		azErr;  						// ��λ��� ��ؼ�����/0.01�� -18000-18000
	INT32 		elErr;  						// ������� ��ؼ�����/0.01�� -9000-9000
	INT32 		Vr;  							// �����ٶ� ��ؼ�����/1m/s
	INT32		Va;  							// ��λ�ٶ� ��ؼ�����/0.01��/s
	INT32 		Ve;  							// �����ٶ� ��ؼ�����/0.01��/s
	INT32 		X;  							// ����X/1m������������ϵ��
	INT32 		Y;  							// ����Y/1m
	INT32 		Z;  							// ����Z/1m
	INT32 		VX; 							// ����X�ٶ�/1m/s
	INT32 		VY;  							// ����Y�ٶ�/1m/s
	INT32 		VZ;  							// ����Z�ٶ�/1m/s
	INT32		lon;							///����   -180-180
	INT32		lat;							///γ��	  -90-90
	float		alt;							///�߶�
	INT16 		DopV;  							// �������ٶ�
	INT16 		remain;
};

//��  �㼣
struct TPC_RadPltNotify_n
{
	UINT32		objectID; 						//װ���������ƽ̨
	UINT32		equipID; 						//װ������ID
	UINT32		pltRecTime[5];					///<�㼣ʱ��,��,�£��գ�ʱ������ 0-3600000000
	UINT32		pltId;							///<�㼣Id
	UINT16		wfmId;							/// ���α��
	INT16		SNR;							///�����   0.1db
	INT32		amp; 							///�ز����� dbw
	INT32		R;							///<�㼣���� m
	INT32		Az;							///<�㼣��λ  0.01 -18000-18000
	INT32		El;						///�㼣���� 0.01  -9000-9000
	INT32		distErr; 						///������� m
	INT32		azErr; 						///��λ��� 0.01��	-18000-18000
	INT32		elErr; 						///�������0.01��	-9000-9000
	INT32		posX; 							///�㼣x
	INT32		posY;	 						///�㼣y
	INT32		posZ;	 						///�㼣z
	INT32		lon;							///����   -180-180
	INT32		lat;							///γ��	  -90-90
	float		alt;							///�߶�
	INT8		SFmark; 						///�������ٱ�־ 0--���� 1--����
	INT16		DopV;							///�������ٶ�
	INT8		back; 							///����
};

//51.1�״�������ο�	
struct RadPmWfm
{
	int			wfmId;							///<����Id������Id������Դ��ģ����Idһ��
	float		cpiTm;							///<��������ۻ�����ʱ�䣺��ǰ���γ���ʱ�䣬ms
};
//51.2�״������λ��	
struct RadPmBwl
{
	int			bdwId;							///<��λId����λId�벨λͼ���Ӧ��ϵ������ӳ�䲨��ʸ��
	float		dwlTm;							///<��λפ��ʱ�䣺��ǰ��λפ��ʱ�䣬ms
	int			wfmNum;							///<����������ָ��ǰ��λ�ڲ�������
	RadPmWfm		wfmLst[4];						///<�����б���ǰ��λ�ڲ����б��״ﲨ��Id����Դ��ģ����Idһ�£����ΰ��涨cpiʱ��˳�򲥷�
};
//51.3�״��������ģʽ��	
struct RadPmWkm
{
	int			wkmId;							///<����ģʽId������Ĺ���ģʽIdֻ��Ӧ�յ�ģʽ���ƣ������ɰ�����λ�Ͳ������ݾ���
	float		vldlTm;							///<����ģʽ����ʱ�䣺����һ����ģʽ/�ϱ���ʼ����������ģʽ����/�����ϱ���ʱ�䣬ms
	int			bdwNum;							///<��λ������ָ����һ���ϱ��������ϱ�
	RadPmBwl		bdwLst[32];						///<��λ�б���ǰ����ģʽ��Чʱ���ڵĲ�λ�б�
};
//51.�״�����ϱ�
// struct TPC_RadParmNotify
// {
// 	int			pltId;							///<װ������ƽ̨Id
// 	int			emtId;							///<װ��������Դ��Id
// 	float		ntfPrvTm;						///<�ϱ���ʼʱ�䣺����һ���ϱ���ʱ�䣬ms
// 	float		ntfSpnTm;						///<�ϱ�����ʱ�䣺�������ϱ���Ч����ʱ�䣬ms
// 	int			wkmNum;							///<��λ������ָ����һ���ϱ��������ϱ�
// 	RadPmWkm		wkmLst[4];						///<ģʽ�б������ϱ��ڵĹ���ģʽ�б�
// };
//52.��ѡ�ϱ�	
typedef struct TPC_SutChsNotify
{
	int			sutPlatId;						//SUT�ڳ����е����������ڶ��ػ�����
	int			recTime[7];						//��ѡ����ʱ��,��,�£��գ�ʱ���֣���,����
	int			tgtBatchNum;						//Ŀ������
	uchar		tgtForce;						//Ŀ��������� 0-δ���壬1-�ҷ���2-�з���3-�ѷ���4-������5�Ժ�Ԥ����
	uchar		tgtPlatCat;						//Ŀ��ƽ̨���� 0-δ֪��1-����̶���2-�����ƶ���3-ˮ�棬4-ˮ�£�5-������6-�̶���7-��ת��8-���˻���9-���ǣ�10-����ƽ̨��12-��Я��13�Ժ�Ԥ��
	uchar		tgtThreatGrade;					//Ŀ����в�ȼ�
	uchar		emtTyp;							//����Դ ����0-δ֪��1-�����״2-�Կվ����״3-�Ժ������״4-�Ϳվ����״5-�����״6-Ŀ��ָʾ�״7-����״8-Ԥ���״9-����Ԥ���״10-���������״11-�����״12-�����Ƶ��״13-���������״14-���׹����״15-�๦���״16-����ĩ�Ƶ��״17-��ը��׼�״18-����״19-ս������״20-��λ���У���״21-�Ŀ�����У���״22-���չ����״23-�����״24-���θ����״25-��½�����״26-�ۿڼ����״27-�����״28-�����״29-����ʶ������30-�����״31-�����״�
	float		tgtPos[3];						//Ŀ��λ��,���� γ�� �߶�
	float		tgtAzim;							//Ŀ�귽λ
	float		tgtElev;							//Ŀ�긩��
	float		tgtAzimVar;						//Ŀ�귽λ����
	float		tgtElevVar;						//Ŀ�긩������
	float		tgtSdist;						//Ŀ��б��
	float		tgtSdistVar;						//Ŀ��б�෽��
	float		tgtRadSpd;						//Ŀ�꾶���ٶ� ��Ϊ�ӽ�����ΪԶ��
	float		tgtTagSpd;						//Ŀ�������ٶ� ��Ϊ��ʱ�룬��Ϊ˳ʱ��
	uchar		emtCode;							//���������
	uchar		emtWkMod;						//����Դ����ģʽ 0-δ֪��1-������2-���٣�3-�Ƶ���4-TWS��5-TAS��6�Ժ�Ԥ��
	uchar		emtPlorMod;						//����Դ������ʽ 0-δ֪��1-��Բ������2-��Բ������3-��ֱ������4-ˮƽ������5-б������6-������ѡ��7-�������룬8-�����ݱ䣬9-������Բ������10-������Բ������11�Ժ�Ԥ��
	uchar		sigFM;							//�źŵ��Ʒ�ʽ 0-������1-���棬2-�����Ե�Ƶ��3-���Ե�Ƶ��4-������룬5-������룬6-Ƶ�ʱ��룬7-Ƶ�ʷּ���8�Ժ�Ԥ��
	float		sigScanProd;						//ɨ������
	float		beamDwlTm;						//��λפ��ʱ��
	float		IntfDur;							//��ɴ�����
	uchar		sigState;						//�źŻ״̬ 0-���źţ�1-��źţ�2-��ʱ��ʧ�źţ�3-��ʧ�����źţ�4-��ʧ�źţ�5�Ժ�Ԥ��
	uchar		sigIntfMark;						//�źŸ��ű�� 0-δ���ţ�1-��Դ���ţ�2-��Դ���ţ�3-��Դ���ż���Դ���ţ�4-HPECM��5�Ժ�Ԥ��
	uchar		sigFreqTyp;						//�ź�Ƶ������ 0-������1-�̶���2-��䣬3-�ּ���4-���룬5-�ݱ䣬6-��Ƶ�β7-������Ƶ�ʵ��ƣ�8-������������ƣ�9-�������������ƣ�10-����Ƶ�ʱ��룬11�Ժ�Ԥ��
	uchar		sigFPCnt;						//�ź�Ƶ����
	float		sigFreqMed;						//�ź�Ƶ����ֵ
	float		sigFreqRng;						//�ź�Ƶ�ʷ�Χ
	float		sigRFSeq[MAXSEQLEN];				//�ź�Ƶ���б�32��Ƶ��[(Ƶ�㲻��ʱҲ������)������Ƶ�ʶ���������Ӱ��
	uchar		sigPRITyp;						//�ź�PRI���� 0-������1-�̶���2-���䣬3-������4-�ݱ䣬5-�β6-���룬7-���䣬8-��������9�Ժ�Ԥ��
	uchar		sigPRICnt;						//�ź�PRI����
	float		sigPRIMed;						//�ź�PRI��ֵ
	float		sigPRISeq[MAXSEQLEN];			//�ź�PRI�б��ź�PRI���ܵ����У�32��PRI(PRI����ʱҲ������)
	float		sigPRIRng;						//�ź�PRI��Χ
	uchar		sigPWTyp;						//�ź�PW���� 0-������1-�̶���2-�仯��3�Ժ�Ԥ��
	uchar		sigPWCnt;						//�ź�PW����
	float		sigPWMed;						//�ź�PW��ֵ
	float		sigPWRng;						//�ź�PW��Χ
	float		sigPWSeq[MAXSEQLEN];				//�ź�PW��������У�32��PW(PRI����ʱҲ������)
}TPCSUTEPL;
//53.ECMƵ���ϱ�	
typedef struct TPC_ECMSPNotify
{
	int			subSysId;						///<Ŀ����ϵͳID
	int			freqNum;							///<Ƶ�׵���N
	double		freqStart;						///<��ʼƵ�㣬MHz
	double		freqStop;						///<��ֹƵ�㣬MHz
	double		freqAmpl[1024]; 					///<Ƶ����ȣ�������Ч����N
}ECMSP;
//81.SUT�¼�	
struct TPC_SimSutEvent
{
	//����
};
//82.�ⲿƽ̨��������	
struct TPC_ExtPlatUpdate
{
	int			simTime[7];						///<�ϱ�ʱ��,��,�£��գ�ʱ���֣���,����
	int			entCnt;							///<����Դƽ̨����N
	ScnPlat		emtPlat[MAXDATACOUNT];			///<����Դƽ̨���ݿ�,��Ч��N
};
//83.�ⲿ����Դ�¼�����	
struct TPC_ExtEmtEvetn
{
	int			simTime[7];						///<�ϱ�ʱ��,��,�£��գ�ʱ���֣���,����
	int			platId;						///<ƽ̨Id
	int			emtId;						///<����ԴId
	int			tgtMdl;						//Ŀ��ģʽId:�¼�Ϊģʽ�л�ʱ��Ч��Ŀ�깤��ģʽId
	float		antAzm;						///<������λ
	float		antElv;						///<��������
	int			beamNo;						///<��λ��
	float		scanDwlTm;					///<פ��ʱ��
	int			trkTgtCnt;					///<����Ŀ������N
	int			trkTgtIdLst[8];				///<����Ŀ��Id�б�
	char		csfNm[8];					///<�Զ��巽��ͼ�ļ�����
};
//84.1 ���߶���
struct AntDef
{
	int antId;			///<����Id
	float antAzm;		///<���߷�λ
	float antElv;		///<���߸���
	float antDwlTm;		///<פ��ʱ��

};
//84.�ⲿSUT����ɨ���¼�����
struct TPC_ExtSutAntScEvent
{
	int			simTime[7];					///<�ϱ�ʱ��,��,�£��գ�ʱ���֣���,����
	int			sutId;						///<SutΨһ��ʶ��ϵͳͳһ����
	int			antCnt;						///<��������N
	int			AntDef[8];					///<�����б�
};

//85.DRFSԤ��������ϱ�
struct TPC_DrfsPgrsNotify
{
	int			prePgrs;					///<���ȣ�0-100��%
};

//86.1 ����ʵ����̬
struct VehicleHPR
{
	int			vehclId;						///<����id
	double		vehclAlt;					///<�����߶�
	double		vehclPch;					///<��������
	double		vehclRol;					///<�������
};
//86 ����ʵ����̬����
struct TPC_VehicleHPRUpt
{
	int			vechlNum;					///<��������
	VehicleHPR	vechlData[MAXDATACOUNT];		///<��������
};


struct BEAM_INFO
{
	INT32 iBeamAz;// �������ķ�λ ����0.1deg [-1800-1800��]
	INT32 iBeamEl;// �������ĸ��� ����0.1deg [-900-900��]
	UINT32 iBeamWidthA;// ������ȷ�λ ����0.1deg [0-1800]
	UINT32 iBeamWidthE;// ������ȸ��� ����0.1deg [0-1800]
	UINT32 uiBeamCutTime;// ��λפ��ʱ�� 0-�������� 1-���ٲ��� 2-Ԥ��
	UINT8 ucWaveType;// ��������
	UINT8 ucAgilityType;//�ݱ�״̬ 0-�ݱ� 1-�ǽݱ� 2-Ԥ��
};
//
////�״﹤�������ϱ�
//struct TPC_RadParmNotify
//{
//	UINT32 objectID; //װ���������ƽ̨
//	UINT32 equipID; //װ������ID
//	float uptime;  //�״�����ϱ�ʱ��
//	UINT32 uiBeamCutEventNum; //��λ�л��¼���Ŀ
//	BEAM_INFO BeamINfoList[100];
//};


//51.1�״ﲨλ�л��ϱ�
typedef enum eRadBmWks
{
	beam_wks_search = 0,			//��������
	beam_wks_track = 1,			//���ٲ���
	beam_wks_slient = 2,			//��Ĭ
	beam_wks_reserve = 3,		//����
};
struct RadBdwNtfPm
{
	int			bmAzim;					///<��ǰ��λ������λ��deg��-180~180
	int			bmElev;					///<��ǰ��λ����������deg��-90~90
	int			tmSltNo;					///<ʱ϶��ţ������״��ϱ���ʱ϶���
	int			bmDwlTm;					///<��λפ��ʱ�䣺��s
	int			bmWks;					///<��λ����״̬������eRadBmWks����
};
//51.1�״ﲨ���л��ϱ�
typedef enum eRadWfmAgs
{
	wfm_agility_yes = 0,			//�ݱ�
	wfm_agility_no = 1,			//�ǽݱ�
	wfm_agility_reserve = 2,		//����
};
struct RadWfmNtfPm
{
	float		wfmFreq;;				///<����Ƶ�ʣ�MHz
	int			wfmAgs;					///<�ݱ�״̬����eRadWfmAgs����
};
//51.�״�����ϱ�
typedef enum eRadEvtCode
{
	sim_event_sw = 0,			//���ػ��¼�
	sim_event_wkm = 1,			//����ģʽ�л��¼����ݲ�ʹ��
	sim_event_bdw = 2,			//��λ�л��¼�
	sim_event_wfm = 3,			//�����л��¼�
	sim_event_atp = 4,			//����ͼ�л��¼����ݲ�ʹ��
	sim_event_ttk = 5,			//Ŀ������¼����ݲ�ʹ��
};
struct TPC_RadParmNotify
{
	int			platId;						///<����ƽ̨Id����ƽ̨�����е�Idһ��
	int			emtId;						///<װ��Id
	int			evtCode;						///<�¼��룺��eRadEvtCode����
	int			simEvtCnt;					///<����Դ�¼�����N
	int				seRadSw;					///<�״￪�ػ��¼���0-�ػ���1-���������ǿ�����Ƶ
	RadBdwNtfPm		seRadBdw[MAXDATACOUNT];	///<�״ﲨλ�л��ϱ�
	RadWfmNtfPm		seRadWfm;				///<�״ﲨ���л��ϱ�
};

#pragma pack(pop)
