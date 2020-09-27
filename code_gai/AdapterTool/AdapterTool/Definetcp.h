#pragma once

#include <boost/shared_ptr.hpp>
#include <vector>
#include <WTypes.h>
//#include <basetsd.h>
//#include <wtypesbase.h>

#define STRUCT_PTR_DECLARE(Name) \
	typedef boost::shared_ptr<Name> Name##ptr;

#pragma pack(1)
////////////////////////////////////////////////////////////////////////////////////////////////////
// file:	���Ĵ����ʽ����
//
// summary:	�����
////////////////////////////////////////////////////////////////////////////////////////////////////

struct  SMessageFormat
{
	/// <summary> ���뿪ʼ��־���̶���д0x7e7e</summary>
	unsigned short _CodeStartSign;

	/// <summary> ���ݳ��ȣ��ܳ��Ⱥ���ͷ��β�����ֵΪ8192���ֽ�</summary>
	unsigned short _DataLenth;

	/// <summary> Դ��ַ��Դ��ַΪ0��0xffff��ʾ������</summary>
	unsigned short _SourceAddress;

	/// <summary> Ŀ�ĵ�ַ��Ŀ�ĵ�ַΪ0��0xffff��ʾ������</summary>
	unsigned short _TargetAddress;

	/// <summary> ����ţ������·�ʱ˳���·�����ˮ�ţ������������������ϱ�ʱ�������Ϊ0</summary>
	unsigned short _CommandNum;

	/// <summary> �����룬0x01��0x7fΪ�״�ӿڴ�������·����״����У�������ݣ�0x81~0xffΪ�״����У���ϱ����״�ӿڴ������������</summary>
	unsigned short _CommandCode;

	/// <summary> �汾�ţ�������汾�Ź̶�Ϊ1</summary>
	unsigned short _Version;

	/// <summary> ���ԣ���������ֶι̶�Ϊ0</summary>
	unsigned char _Property;

	/// <summary> ������ţ�ȡֵ��Χ0��255����ʼֵΪ0��ÿ�η����±���˳���1������255�������´�1����0��ʼ��ţ�\
		/// 		  ĳ�����ϴη���ʧ�ܺ��ط�ʱ���䱨����Ų��䣻�����շ��յ��������Ϊ0�ı���ʱ�������������ܸñ��ģ�\
	/// 		  ����Ϊ0����Ҫ���ϴα��ĵı��������Ƚϣ������ͬ����Ϊ�ñ����ظ�����֮�����������ͬ����Ϊ�±��Ľ���</summary>
	unsigned char _MessageOrder;

	/// <summary> �ܰ�����Ҫ�ֿ�����ı��ĵĸ������ְܷ���������65535�����ֶ�ֻ�ڡ����ԡ��ӿ����D3=1�ļ��ѷְ���ͨ�����ݸ�ʽ����Ч</summary>
	unsigned short _TotalNumOfMessage;

	/// <summary> ��ǰ���ţ��������ݵı�ţ���1��ʼ˳���ţ����Ϊ�ܰ�����</summary>
	unsigned short _CurrentSerialNum;

	/// <summary> ���ݰ���</summary>
	//unsigned char _DataPackage;

	/// <summary> У���룬������̶�Ϊ0</summary>
	unsigned short _CheckCode;

	/// <summary> ��ֹ�룬�̶���дΪ��0x0a0d</summary>
	unsigned short _CodeEndSign;

};
STRUCT_PTR_DECLARE(SMessageFormat);


////////////////////////////////////////////////////////////////////////////////////////////////////
// file:	�������Ͷ���
//
// summary:	�����
////////////////////////////////////////////////////////////////////////////////////////////////////

enum  SMessageType
{
	/// <summary> �·�����.  </summary>
	Struct_DicpatchMessage = 0,

	/// <summary> �ϱ�����.  </summary>
	Struct_ReportMessage,
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	�·�����������.  </summary>
///
/// <remarks>	�����, 2020/8/5. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////

#define _LVC_DM_TXCX		 0X0001		//ͨ�Ų�ѯ:			�˹�������ϵͳ��������Զ�����߼���·״̬ʱ�·�
#define _LVC_DM_XTZJ		 0X0002		//ϵͳ�Լ�:			Ҫ���״���У�������Լ첢�ϱ��Լ���
#define _LVC_DM_LDCSHPZ      0X0003		//�״��ʼ������:	�·��״�ĳ�ʼ�����ò���
#define _LVC_DM_LDZBCX       0X0004		//�״������ѯ:		Ҫ���״��ϱ���ǰ���淨��ָ���״�/��У��վַ����
#define _LVC_DM_XYKZ	     0X0005		//���п���:			Ҫ���״���У���л�����״̬
#define _LVC_DM_BJCCSHPZ     0X0006		//��У����ʼ������:	�·���У����ʼ�����ò���
#define _LVC_DM_SSMBCS       0X0007		//ʵʱĿ�����:		�·��ز�ģ��Ŀ���ʵʱλ�á��ٶ���RCS����

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	�ϱ�����������. </summary>
///
/// <remarks>	�����, 2020/8/5. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////

#define _LVC_RM_MLXY		 0X0081		//������Ӧ:			���յ�ͨ�Ų�ѯ����������ϱ�
#define _LVC_RM_XTSB		 0X0082		//�����ϱ�:Ԥλ�ظ�	��ϵͳͨ�ſ���ʱ��ʱ����
#define _LVC_RM_LDZJSB		 0X0083		//�״��Լ��ϱ�:		�״��ϱ�ȫϵͳ���ϵͳ�Լ���
#define _LVC_RM_BJCZJSB      0X0084		//��У���Լ��ϱ�:	��У���ϱ�ȫϵͳ���ϵͳ�Լ���
#define _LVC_RM_LDZBSB       0X0085		//�״������ϱ�:		�յ����״������ѯ��������ϱ���ǰ���淨��ָ���״�/��У��վַ����
#define _LVC_RM_DJSJ         0X0086		//�㼣�����ϱ�:			���״�ϵͳ�ڲ������㼣���ݺ������ϱ�
#define _LVC_RM_HJSJ         0X0087		//���������ϱ�:			���״�ϵͳ�ڲ������������ݺ������ϱ�
#define _LVC_RM_LDGZCS       0X0088		//�״﹤�������ϱ�:		���״﹤�����������仯ʱ���������ϱ�
#define _LVC_RM_LDYXKZHF     0X0089		//�״����п��ƻظ�:
#define _LVC_RM_BJCKZZT      0X008a		//��˳�����״̬�ظ�����˳�Ŀ��ģ��������Դ�л�����У����ʼ�����ûظ�;
#define _LVC_RM_LDSCHJ       0X008b		//�״�ɾ������

#define _LVC_TPC_ScnDldNotify 0x00F1 //���ػظ�
#define _LVC_TPC_SysRdyNotify 0x00F2 //Ԥλ�ظ�

////////////////////////////////////////////////////////////////////////////////////////////////////
// file:	�·�������ͨ�Ų�ѯ _LVC_DM_TXCX
//
// summary:	�����
////////////////////////////////////////////////////////////////////////////////////////////////////

struct  DMCommunicationQueryPackage
{
	
};
STRUCT_PTR_DECLARE(DMCommunicationQueryPackage);

////////////////////////////////////////////////////////////////////////////////////////////////////
// file:	�·�������ϵͳ�Լ�
// summary:	�����
////////////////////////////////////////////////////////////////////////////////////////////////////

struct  DMSystemSelfCheckPackage
{
	
};
STRUCT_PTR_DECLARE(DMSystemSelfCheckPackage);

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	�·��������״��ʼ�����ð��п����Ŵ�ʩ.  </summary>
///
/// <remarks>	�����, 2020/8/5. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////

enum DMCQPAntiJammingMeasure
{
	/// <summary> �԰����.  </summary>
	DMCQKAJM_PBDX = 0,

	/// <summary> �԰�����.  </summary>
	DMCQKAJM_PBXY,

	/// <summary> ����ѹ�� .  </summary>
	DMCQKAJM_MCYS,

	/// <summary> Ƶ�ʽݱ�.  </summary>
	DMCQKAJM_PLJB,

	/// <summary> ���龯����.  </summary>
	DMCQKAJM_HXJCL,

	/// <summary> ����ǰ�ظ���.  </summary>
	DMCQKAJM_JLQYGZ,

	/// <summary> �ٶ�ǰ�ظ��� .  </summary>
	DMCQKAJM_SDQYGZ,

	/// <summary> �ٶȺ��ظ��� .  </summary>
	DMCQKAJM_SDHYGZ,

	/// <summary> ��������.  </summary>
	DMCQKAJM_BDGZ,

	/// <summary> ���ʹ���.  </summary>
	DMCQKAJM_GLGL,

	/// <summary> Ѱ���ݱ�Ƶ.  </summary>
	DMCQKAJM_XAJBP,

	/// <summary> ��������.  </summary>
	DMCQKAJM_GRZL,

	/// <summary> ��Ŀ����.  </summary>
	DMCQKAJM_DMBJC,

	/// <summary> ������Ĭ.  </summary>
	DMCQKAJM_SQJM,

	/// <summary> �ڻ�����.  </summary>
	DMCQKAJM_YHMC,

	/// <summary> ���첽����.  </summary>
	DMCQKAJM_KYBGR,

	/// <summary> �޿����Ŵ�ʩ.  </summary>
	DMCQKAJM_WKGRCS,
};

////////////////////////////////////////////////////////////////////////////////////////////////////
// file:	�·��������״��ʼ������
//
// summary:	�����
////////////////////////////////////////////////////////////////////////////////////////////////////

struct  DMRadarInitConfigPackage
{

	/// <summary> ��ʼ����Ƶ��Ϊ��Ƶ,ȡֵ��ΧΪ0~40000MHz</summary>
	UINT32 _WorkFrequency;

	/// <summary> ɨ�跶Χ-��λ����λ����</summary>
	INT32 _ScanningAzimuth;

	/// <summary> ɨ�跶Χ-��������λ����</summary>
	INT32 _ScanningPitch;

	/// <summary> �����Ŵ�ʩ�������������ο�DMCQPAntiJammingMeasureö�ٶ���</summary>
	UINT32 _AntiJammingMeasure;

	/// <summary> ����ָ��Ƕȣ��������淨�߷������״ﳵ��ƽ��ͶӰ���״ﳵͷ����֮��ļн�</summary>
	INT32 _AntennaArrayAngle;

};
STRUCT_PTR_DECLARE(DMRadarInitConfigPackage);

////////////////////////////////////////////////////////////////////////////////////////////////////
// file:	�·��������״������ѯ
//
// summary:	�����
////////////////////////////////////////////////////////////////////////////////////////////////////

struct  DMRadarLocationQueryPackage
{

};
STRUCT_PTR_DECLARE(DMRadarLocationQueryPackage);

////////////////////////////////////////////////////////////////////////////////////////////////////
// file:	�·����������п��Ƶ����п�����
//
// summary:	�����
////////////////////////////////////////////////////////////////////////////////////////////////////

enum  DMRunControlCode
{
	/// <summary> ����.  </summary>
	DMRunControl_Working = 0,

	/// <summary> ����.  </summary>
	DMRunControl_Standby,

	/// <summary> Ԥ��.  </summary>
	DMRunControl_Reserve,
};

////////////////////////////////////////////////////////////////////////////////////////////////////
// file:	�·����������п��ư����ݶ���
//
// summary:	�����
////////////////////////////////////////////////////////////////////////////////////////////////////

struct  DMRunControlPackage
{

	/// <summary> ���п����룬0~2</summary>
	UINT8 _WorkCodeID;

};
STRUCT_PTR_DECLARE(DMRunControlPackage);

////////////////////////////////////////////////////////////////////////////////////////////////////
// file:	�·������б�У������ģʽѡ��
//
// summary:	�����
////////////////////////////////////////////////////////////////////////////////////////////////////

enum  DMAMCScenarioModeSelect
{
	/// <summary> �ڲ����泡��.  </summary>
	DMAMCS_InternalScenario = 0,

	/// <summary> �����ⲿ���泡���������з���.  </summary>
	DMAMCS_ReceiveExternalData,

	/// <summary> Ԥ��.  </summary>
	DMAMCS_Reserve,
};


////////////////////////////////////////////////////////////////////////////////////////////////////
// file:	�·������б�У����ʼ��������Ŀ��RCS��ʼģʽ 
//
// summary:	�����
////////////////////////////////////////////////////////////////////////////////////////////////////

enum  DMAMCInintializeRCSMode
{
	/// <summary> �̶�ֵ.  </summary>
	DMAMCIRCSMode_FixedValue = 0,

	/// <summary> Swerling I.  </summary>
	DMAMCIRCSMode_SwerlingI,

	/// <summary> Swerling II.  </summary>
	DMAMCIRCSMode_SwerlingII,

	/// <summary> Swerling III.  </summary>
	DMAMCIRCSMode_SwerlingIII,

	/// <summary> Swerling IV.  </summary>
	DMAMCIRCSMode_SwerlingIV,

	/// <summary> Ԥ��.  </summary>
	DMAMCIRCSMode_Reserve,
};

////////////////////////////////////////////////////////////////////////////////////////////////////
// file:	��У�����ð���Ŀ����Ϣ��ʽ����
//
// summary:	�����
////////////////////////////////////////////////////////////////////////////////////////////////////

struct  DMAMCInitializeOfTarget
{

	/// <summary> Ŀ����룬ȡֵ��Χ5~3000����λ��0.1KM</summary>
	INT32 _TargetDistance;

	/// <summary> Ŀ���ٶȣ�ȡֵ��Χ-1100~1100����λ��m/s,˵����Ŀ������״�ľ����ٶȣ�����Ϊ����Զ��Ϊ��</summary>
	INT32 _TargetVelocity;

	/// <summary> Ŀ��Ƶ�ƣ�ȡֵ��Χ-2800~2800����λ:Hz</summary>
	INT32 _TargetFrequencyShift;

	/// <summary> Ŀ�깤��Ƶ�ʣ�ȡֵ��Χ0~40000����λ��MHz</summary>
	UINT32 _TargetWorkingFrequency;

	/// <summary> Ŀ��RCS��ȡֵ��Χ0~99999����λ:m2</summary>
	DOUBLE _TargetRCS;

	/// <summary> Ŀ��RCSģʽ��ȡֵ��Χ0~5</summary>
	UINT8 _TargetRCSMode;

	/// <summary> Ŀ�����˥����ȡֵ��Χ0~630����λ:0.1dB</summary>
	UINT32 _TargetReceiveDecay;

	/// <summary> Ŀ�귢��˥��1��ȡֵ��Χ0~630����λ:0.1dB</summary>
	UINT32 _TargetSendDecayI;

	/// <summary> Ŀ�귢��˥��2��ȡֵ��Χ0~630����λ:0.1dB</summary>
	UINT32 _TargetSendDecayII;

	/// <summary> Ŀ�귢��˥��3��ȡֵ��Χ0~630����λ:0.1dB</summary>
	UINT32 _TargetSendDecayIII;
};
STRUCT_PTR_DECLARE(DMAMCInitializeOfTarget);


////////////////////////////////////////////////////////////////////////////////////////////////////
// file:	��У����ʼ�����ð����ݸ�ʽ����
//
// summary:	�����
////////////////////////////////////////////////////////////////////////////////////////////////////

struct  DMAalibrationMarkCarInitPackage
{

	/// <summary> ��������ģʽѡ��ȡֵ��Χ0~2��0���л�Ϊ�ɿ���״̬</summary>
	UINT8 _ScenarioMode;

	/// <summary> ģ��Ŀ������N��ȡֵ��Χ1~256</summary>
	UINT32 _TargetTotalNum;

	/// <summary> Ŀ����Ϣ</summary>
	//std::vector<DMAMCInitializeOfTarget> _TargretInformation;

};
STRUCT_PTR_DECLARE(DMAalibrationMarkCarInitPackage);


////////////////////////////////////////////////////////////////////////////////////////////////////
// file:	�·�������ʵʱĿ�������ʽ����
//
// summary:	�����
////////////////////////////////////////////////////////////////////////////////////////////////////

struct  DMTargetRealTimePackage
{

	/// <summary> ģ��Ŀ������N��ȡֵ��Χ1~256</summary>
	UINT32 _TargetTotalNum;

	/// <summary> Ŀ����Ϣ</summary>
	std::vector<DMAMCInitializeOfTarget> _TargretInformation;

};
STRUCT_PTR_DECLARE(DMTargetRealTimePackage);

////////////////////////////////////////////////////////////////////////////////////////////////////
// file:	�ϱ�������������Ӧ
//
// summary:	�����
////////////////////////////////////////////////////////////////////////////////////////////////////

struct  RMCommandAnswerPackage
{
};
STRUCT_PTR_DECLARE(RMCommandAnswerPackage);

////////////////////////////////////////////////////////////////////////////////////////////////////
// file:	�ϱ������������ϱ�
//
// summary:	�����
////////////////////////////////////////////////////////////////////////////////////////////////////

struct  RMPantReportPackage
{
};
STRUCT_PTR_DECLARE(RMPantReportPackage);


////////////////////////////////////////////////////////////////////////////////////////////////////
// file:	�ϱ�������ȫϵͳ�Լ���
//
// summary:	�����
////////////////////////////////////////////////////////////////////////////////////////////////////

enum  RMSystemSelfTestResult
{
	/// <summary> �ɹ�.  </summary>
	RMSSTR_Success = 0,

	/// <summary> ʧ��.  </summary>
	RMSSTR_Fail,

	/// <summary> Ԥ��.  </summary>
	RMSSTR_Reserve,
};

////////////////////////////////////////////////////////////////////////////////////////////////////
// file:	�ϱ��������״��Լ���
//
// summary:	�����
////////////////////////////////////////////////////////////////////////////////////////////////////

// struct  RMRadarSelfTestResult
// {
// 
// 	/// <summary> �״�ȫϵͳ�Լ�����ȡֵ��Χ0~2��˵����0���ɹ���1��ʧ�ܣ�2��Ԥ��</summary>
// 	UINT8 _RadarSystemTestResult;
// 
// 	/// <summary> �״��ϵͳ�Լ�����˵������ϵͳ�Լ�ɹ�����ӦbitΪ0����ϵͳ�Լ�ʧ�ܡ���ӦbitΪ1</summary>
// 	UINT16 _RadarSubSystemTestResult;
// 
// };


// �״��Լ��ϱ� 0x0084
struct RMRadarSelfTestResult
{
	UINT8 ucChkTotal; // ȫϵͳ�Լ��� 0~2 0���ɹ�; 1��ʧ��; 2��Ԥ��;
	UINT16 usLink;  // ��·�����Ϣ
					// D0: TR��� 0:���� 1:����
					// D1: DBF
					// D2: �źŴ���
					// D3: Ƶ��
					// D4: �������
					// D5: �ŷ�
					// D6: �Կ�


	UINT16 usSPSubIO;// �źŴ�����Ϣ
					 // D0-D3P��ϵͳ��� 0��ʾ��ϵͳ������7��ʾ��ϵͳ���ϣ�������ʾ��ϵͳ������
					 // D4 �ӿ����״̬ 0��ʾ�޹��ϣ�1��ʾ����
	UINT16 PluginState;// �ŷ������Ϣ D0~D7:�������״̬��0��ʾ�޹��ϣ�1��ʾ����
	UINT16 sc_moni;/*ϵͳ�����, ���е�λ���,0��ʾ���� 1��ʾ����
				   * D1-D3:����״̬�� D5:������(���Ź���) D7:���������(A14) D8:�Ǳ����(A11) D10:�ӵ���ư�(�ŷ��ӵ�������) ����:����
				   * D1D2D3: 000-���ų���(������) 001-��Դ���� 010-����Ƿѹ 011-����
				   * 100-���� 101-���� 110-��ѹ 111-���� */

				   /*�ŷ�ϵͳ״̬��*/
	UINT16 usSvState;   /*D0:�ѻ�����  0�ѻ�  1����*/
						/*D1:�������(��������)  0δ����  1����*/
						/*D2:��ѹ�ӵ��(���Ÿ�ѹ&��ѹ�ӵ�)  0δ�ӵ�� 1�ӵ��*/
						/*D3:�ŷ�����  0�ŷ�����  1�ŷ�����*/
						/*D4:����ͣ��  0ͣ��  1����*/
						/*D5:���氲ȫ  0δ��ȫ  1��ȫ*/
						/*D6:���ſ���(���Ź�)  0�ſ�  1�Ź�*/
						/*D7:�������(��λ������)  0��������  1�������*/
						/*D8:����ʹ�� 0δʹ�� 1ʹ��*/
						/*D9:����λ�� 0δ��λ 1��λ��*/

						// Ƶ�ۼ����Ϣ
	UINT16 usGeneralFault; // Ƶ������ܹ���
	UINT16 Group1Fault; // Ƶ�����1���� D0~D14:�ֱ��ʾ���1~15����״̬��0��ʾ�޹��ϣ�1��ʾ����
	UINT16 Group2Fault; // Ƶ�����2���� D0~D3:�ֱ��ʾ���1~4����״̬��0��ʾ�޹��ϣ�1��ʾ����

	UINT16 PluginFault; // DBF������ϼ�� D0~D8:�ֱ��ʾ���1~9����״̬��0��ʾ�޹��ϣ�1��ʾ����

	UINT16 usJamInfomation;     /*�����������Ϣ D8~D15:������
								D7:A15ģ�����״̬��
								D6:����
								D5:A14��A15ͨ��״̬��
								D4:A8�����ֹ���״̬��
								D3:A8��A14ͨ��״̬��
								D2:A8&&A9&&A11��Link����״̬��
								D1:A11AD����ʱ�ӣ�
								D0:���״̬&&A11оƬ���ȣ�
								���ϼ��λ��0��ʾ������1��ʾ����*/
};
STRUCT_PTR_DECLARE(RMRadarSelfTestResult);

////////////////////////////////////////////////////////////////////////////////////////////////////
// file:	�ϱ������б�У���Լ���
//
// summary:	�����
////////////////////////////////////////////////////////////////////////////////////////////////////

struct  RMCACSelfTestResult
{

	/// <summary> �״�ȫϵͳ�Լ�����ȡֵ��Χ0~2��˵����0���ɹ���1��ʧ�ܣ�2��Ԥ��</summary>
	UINT8 _CACSystemTestResult;

	/// <summary> �״��ϵͳ�Լ�����˵������ϵͳ�Լ�ɹ�����ӦbitΪ0����ϵͳ�Լ�ʧ�ܡ���ӦbitΪ1</summary>
	/*bit1 ~7Ŀ��ģ����
	bit1 ��׼���A4
	bit2 �������A6
	bit3�ϱ�Ƶ���1 A9
	bit4�ϱ�Ƶ���2 A13
	bit5�ϱ�Ƶ���3 A14
	bit6ģ��������A3
	bit7������ִ�Ƶ���A11
	bit8 ~12Ŀ��ģ����
	bit8 ��׼���A8
	bit9 �������A10
	bit10 �ϱ�Ƶ���A4
	bit11ģ��������A12
	bit12������ִ�Ƶ���A6
	*/
	UINT16 _CACSubSystemTestResult;

};
STRUCT_PTR_DECLARE(RMCACSelfTestResult);

////////////////////////////////////////////////////////////////////////////////////////////////////
// file:	�ϱ��������״������ѯ�ϱ� _LVC_RM_LDZBSB
// 
// summary:	�����
////////////////////////////////////////////////////////////////////////////////////////////////////

struct  RMRadarCoordinateReport
{

	/// <summary> ����ָ��Ƕȣ��������淨�߷������״ﳵ��ƽ��ͶӰ���״ﳵͷ����֮��ļнǣ���Χ��-180~180����λ��deg</summary>
	INT32 _AntennaArrayAngle;

	/// <summary> �״�վַ   \
		/// 		  ���ȷ�Χ��-180~180����λ��deg,˵�����������ϵ\
	/// 		  ���ȷ�Χ��-90~90����λ��deg,˵�����������ϵ\
	/// 		   ���ȷ�Χ��-1000~30000����λ��m,˵�����������ϵ </summary>

	INT32 _RadarLon;
	INT32 _RadarLat;
	INT32 _RadarAlt;
	/// <summary> ��У��վַ   \
		/// 		  ���ȷ�Χ��-180~180����λ��deg,˵�����������ϵ\
	/// 		  ���ȷ�Χ��-90~90����λ��deg,˵�����������ϵ\
	/// 		   ���ȷ�Χ��-1000~30000����λ��m,˵�����������ϵ </summary>

	INT32 _BxcLon;
	INT32 _BxcLat;
	INT32 _BxcAlt;
};
STRUCT_PTR_DECLARE(RMRadarCoordinateReport);


////////////////////////////////////////////////////////////////////////////////////////////////////
// file:	�ϱ������е㼣�����ϱ� _LVC_RM_DJSJ
// 
// summary:	w
////////////////////////////////////////////////////////////////////////////////////////////////////

// struct  RMPointTraceReport
// {
// 
// };
// STRUCT_PTR_DECLARE(RMPointTraceReport);

////////////////////////////////////////////////////////////////////////////////////////////////////
// file:	�ϱ������к��������ϱ� _LVC_RM_HJSJ
// 
// summary:	w
////////////////////////////////////////////////////////////////////////////////////////////////////

// struct  RMFlightTraceReport
// {
// 
// };
// STRUCT_PTR_DECLARE(RMFlightTraceReport);

////////////////////////////////////////////////////////////////////////////////////////////////////
// file:	�ϱ��������״﹤�������ϱ� _LVC_RM_LDGZCS
// 
// summary:	w
////////////////////////////////////////////////////////////////////////////////////////////////////

struct ST_BEAM_INFO
{
	INT32 iBeamAz;// �������ķ�λ ����0.1deg [-180 ~ 180��]
	INT32 iBeamEl;// �������ĸ��� ����0.1deg [-180 ~ 180��]
	UINT32 iBeamWidthA;// ����״̬  0����1�����䣬������ȷ�λ ����0.1deg [0 ~ 180]
	UINT32 iBeamWidthE;// ����Ƶ��  �ǽݱ�ʱ��Ч��������ȸ��� ����0.1deg [0 ~ 180]
	UINT32 uiBeamCutTime;// ��λפ��ʱ�� 0-�������� 1-���ٲ��� 2-Ԥ��
	UINT8 ucWaveType;// ��������  0-��������  1-���ٲ���  2Ԥ��
	UINT8 ucAgilityType;//�ݱ�״̬ 0-�ݱ� 1-�ǽݱ� 2-Ԥ��
};

struct  RMRadarWorkParamReport
{
	UINT32 uiBeamCutEventNum; // ��λ�л��¼���N 0~100 50ms�ڲ�λ�л�����
							  //    ST_BEAM_INFO stBeamInfo; ��� uiBeamCutEventNum�� ST_BEAM_INFO
	//std::vector<ST_BEAM_INFO> BeamINfoList; //
	ST_BEAM_INFO BeamINfoList[100];
};
STRUCT_PTR_DECLARE(RMRadarWorkParamReport);




// �״﹤��״̬�ر����״����п��ƻظ� 0x0089
struct RMRadarRunControlReport
{
	UINT8 ucWorkStateReturn;// ���п����� 0��������1��������2��Ԥ��;
} ;
STRUCT_PTR_DECLARE(RMRadarRunControlReport);

// ��˳�����״̬�ظ���Ŀ��ģ��������Դ�л�,��У����ʼ�����ûظ�  0x008A
struct RMCACControlStateReport
{
	UINT8 ucDataSrc; // ����Դ 0������; 1����������;
} ;
STRUCT_PTR_DECLARE(RMCACControlStateReport);

/// �״�ɾ������  0x008B
struct RMRadarDeleteTrack
{
	UINT8 ucTrackTotalNum; // ɾ����������
	UINT8 bak[3]; // ����
	UINT16 usTrackId[50]; // ɾ��������
};
STRUCT_PTR_DECLARE(RMRadarDeleteTrack);

// ʱ��ṹ
struct INTF_DC_TIME
{
	UINT32 year : 12;  /*��:0~4095*/
	UINT32 mon : 4;    /*��:1~12*/
	UINT32 day : 8;    /*��:1~31*/
	UINT32 hour : 8;   /*ʱ:0~23*/
	UINT32 us;      /*���ͷ�����ʱ�̵ķ��ӡ��롢���롢΢�� ��΢��Ϊ��ʱ��λ0~3600000000*/
};

//����
struct RMFlightTraceReport
{
	INTF_DC_TIME stTrackTime; // ʱ��
	UINT32 uiPlotId; // �㼣���
	UINT16 uiTrackId; // ������
	UINT16 tgtNo; // ��Ŀ����
	UINT8 subNo; // ��Ŀ����
	UINT8 traceStatus; // ����״̬ 0:���� 1:�ָ� 2:����
	UINT8 ucTrackQuality; // �������� 0:���� 1:���� 2:���� 3: ��������
	UINT8 ucFollowCtrl; // ���ٿ��� 0:�������� 1:�������� 2:�մ� 3:���� 4:����
	UINT16 waveForm; // ��ϲ��α��
	INT16 SNR; // ����� 0.1dB����
	INT32 amp; // �ز�����
	INT32 GR; // Ŀ����� ��ؼ�����/1m��������ϵ��
	INT32 GA; // Ŀ�귽λ ��ؼ�����/0.01��
	INT32 GE; // Ŀ�긩�� ��ؼ�����/0.01��
	INT32 distErr; // ������� ��ؼ�����/1m
	INT32 azErr; // ��λ��� ��ؼ�����/0.01��
	INT32 elErr; // ������� ��ؼ�����/0.01��
	INT32 Vr; // �����ٶ� ��ؼ�����/1m/s
	INT32 Va; // ��λ�ٶ� ��ؼ�����/0.01��/s
	INT32 Ve; // �����ٶ� ��ؼ�����/0.01��/s
	INT32 X; // ����X/1m������������ϵ��
	INT32 Y; // ����Y/1m
	INT32 Z; // ����Z/1m
	INT32 VX; // ����X�ٶ�/1m/s
	INT32 VY; // ����Y�ٶ�/1m/s
	INT32 VZ; // ����Z�ٶ�/1m/s
	INT16 DopV; // �������ٶ�
	INT16 remain;
};

//�㼣
struct RMPointTraceReport
{
	INTF_DC_TIME stPlotTime; // �㼣ʱ��
	UINT32 uiPlotId; // �㼣���
	UINT16 waveForm; // ���α��
	INT16 SNR; // ����� 0.1dB����
	INT32 amp; // �ز�����
	INT32 R; // �㼣���� ��ؼ�����/1m
	INT32 Az; // �㼣��λ ��ؼ�����/0.01��
	INT32 El; // �㼣���� ��ؼ�����/0.01��
	INT32 distErr; // ������� ��ؼ�����/1m
	INT32 azErr; // ��λ��� ��ؼ�����/0.01��
	INT32 elErr; // ������� ��ؼ�����/0.01��
	INT32 X; // �㼣X/1m
	INT32 Y; // �㼣Y/1m
	INT32 Z; // �㼣Z/1m
	INT8 SFmark; // �������ٱ�־
	INT8 remain;
	INT16 DopV; // �������ٶ�
};

//��Ĭ����
struct SECTOR
{
	UINT16  usStartA;   // ��ʼ��λ 0~360��/0.1��
	UINT16  usEndA;     // ��ֹ��λ 0~360��/0.1��
	INT16   usStartE;   // ��ʼ���� -90~90��/0.1��
	INT16   usEndE;     // ��ֹ���� -90~90��/0.1��
};

//��������
struct SEARCH_AREA_DATA
{
	UINT16  usStartA; // ��ʼ��λ 0~360��/0.1��
	UINT16 usEndA; // ��ֹ��λ 0~360��/0.1��
	INT16 usStartE; // ��ʼ���� -90~90��/0.1��
	INT16 usEndE; // ��ֹ���� -90~90��/0.1�� ,��ֹ�����������ʼ������
};

// �״��ʼ������ 0x0003
struct CENTER2RADAR_INIT
{
	UINT8 ucStart;         // 0ֹͣ 3��������ʾ�ŷ���λ����������
	UINT32 usPscCtrl;      // λ�ÿ��� ����: 0.1 ��Χ: 0~360

	UINT8 disCmdDbf;/*�԰����ʹ��(DBF)��0:��ʹ��  1:ʹ��*/
	UINT8 disCmdDbfNum;/*�԰��������(DBF)��0:������  n:�������5��*/
	UINT8 disCmdShadow;/*�԰���Ӱʹ�ܣ�0:��ʹ��  1:ʹ��*/
	UINT16 auxShadowB;/*������ӰBֵ(�źŴ�����ֵ����64��ΪBֵ)����ֵ0��10000��ȱʡ256*/
	UINT8 disCmdPower;/*ǿ�����޳�ʹ�ܣ�0:��ʹ��  1:ʹ��*/
	UINT8 disCmdMutiFake;/*���Ŀ���޳�ʹ�ܣ�0:��ʹ��  1:ʹ��*/

	UINT8 ucMode;           // ������Ƶ�ʿ���ģʽ 0:�̶� 1:�ݱ� 2:Ѱ��
	UINT16 ucMainPulseFrq;  // ������Ƶ���� Ƶ�ʿ���ģʽΪ�̶�ʱ��Ч��0~40��ʾƵ��F0~F40,0xFFFF��ʾȡ������
	UINT16 ucFtCvrPulseFrq; // ǰ�ڻ�����Ƶ��, 0~40, 0xFFFF��ʾȡ������
	UINT16 ucBkCvrPulseFrq; // ���ڻ�����Ƶ��, 0~40, 0xFFFF��ʾȡ������

	UINT16 usMainWaveCode;  // �����岨�α�� 0~67
	UINT8 ucFtCvrCtrl;      // ǰ�ڻ����� 0:��; 1:�̶�; 2:�ݱ�
	UINT8 ucBkCvrCtrl;      // ���ڻ����� 0:��; 1:�̶�; 2:�ݱ�
	UINT8 ucFtCvrDirCtrl;   // ǰ�ڻ�ָ����� 0:�Զ� 1:�˹�
	UINT8 ucBkCvrDirCtrl;   // ���ڻ�ָ����� 0:�Զ� 1:�˹�
	UINT16 usFtCvrIntvl;    // ǰ�ڻ���� 0~100
	UINT16 usBkCvrIntvl;    // ���ڻ���� 0~100
	UINT16 usFtCvrWaveCode; // ǰ�ڻ����岨�α�� 0~7
	UINT16 usBkCvrWaveCode; // ���ڻ����岨�α�� 0~7
	UINT32 uiFtCvrA;        // ǰ�ڻ���λ 0~360��/0.000001��
	INT32 iFtCvrE;          // ǰ�ڻ����� -90~90��/0.000001��
	UINT32 uiBkCvrA;        // ���ڻ���λ 0~360��/0.000001��
	INT32 iBkCvrE;          // ���ڻ����� -90~90��/0.000001��

	UINT8 ucPassFollow;	//��������

	UINT8 ucSectorEf[2];    // ������Ч��־ 1��Ч
	SECTOR stSector[2];     // ��Ĭ����

	UINT8 disCmdAsync;      /*�첽����ʹ�ܣ�0:��ʹ��  1:ʹ��*/

	UINT8 ucSearchArea1; // ��������1��Ч��־ 0��Ч 1��Ч
	UINT8 ucSearchArea2; // ��������2��Ч��־ 0��Ч 1��Ч

	SEARCH_AREA_DATA stSearchAreaData[2]; // ��������
};


//��У���ӿ�


// typedef struct
// {
// 	TS_MetaType(TS_INFORMATION_SEND);
// 	unsigned int R[3]; //Ŀ��1-9���룬������λ��Km
// 	short V[3]; //Ŀ��1-9�ٶ� ������λ��m/s
// 	short Freq[3]; //Ŀ��1-9Ƶ��ƫ�ƣ�������λ��Hz
// 	unsigned char IfFreMove; // Ƶ�Ʊ�־ 0 Ƶ����Ч 1 Ƶ����Ч
// }/*_attribute_((packed))*/TS_INFORMATION_SEND;

struct TS_INFORMATION_SEND
{
	unsigned int R[3]; //Ŀ��1-9���룬������λ��Km
	short V[3]; //Ŀ��1-9�ٶ� ������λ��m/s
	short Freq[3]; //Ŀ��1-9Ƶ��ƫ�ƣ�������λ��Hz
	unsigned char IfFreMove; // Ƶ�Ʊ�־ 0 Ƶ����Ч 1 Ƶ����Ч
};

// typedef struct 
// {
// 	TS_MetaType(BGC2_TO_TS);
// 	UINT8 ucWorkState; //Զ��״̬�л�
// 	UINT8 ucTSWKfrq; //����Ƶ��
// 	UINT8 ucTSRCSsevro; //Ŀ��RCS�涯����ֵΪ0���涯��
// 	UINT8 ucTSrecvAtt; //����˥��0-63
// 	UINT8 ucTSemsnAtt[3]; //����˥��0-63������Ӧ����˥��1������˥��2������˥��3��
// 	UINT8 ucTSdataEffect; //ģ�������俪�ؼ���1���䣻0�رշ���
// 	UINT16 ucTarSt; //9��Ŀ���ѡ�������ǰ9λ��1ѡ�У�0δѡ��
// 	TS_INFORMATION_SEND stTOTsInfo[3]; //Ŀ������
// }BGC2_TO_TS;

//�Կظ�ģ����������
struct BGC2_TO_TS
{
	UINT8 ucWorkState; //Զ��״̬�л�
	UINT8 ucTSWKfrq; //����Ƶ��
	UINT8 ucTSRCSsevro; //Ŀ��RCS�涯����ֵΪ0���涯��
	UINT8 ucTSrecvAtt; //����˥��0-63
	UINT8 ucTSemsnAtt[3]; //����˥��0-63������Ӧ����˥��1������˥��2������˥��3��
	UINT8 ucTSdataEffect; //ģ�������俪�ؼ���1���䣻0�رշ���
	UINT16 ucTarSt; //9��Ŀ���ѡ�������ǰ9λ��1ѡ�У�0δѡ��
	TS_INFORMATION_SEND stTOTsInfo[3]; //Ŀ������
};


#pragma pack()