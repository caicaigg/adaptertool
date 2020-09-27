#pragma once


#include <WTypes.h>
// #include <basetsd.h>
// #include <wtypesbase.h>

enum DDSTypeEnum
{
	DDSTYPE_SysResetRequest = 0xFF01,	//ϵͳ��λ 1
	DDSTYPE_SysHaltRequest,				//ϵͳ��ֹ 2
	DDSTYPE_SysBitRequest,				//ϵͳ�Լ� 3				
	DDSTYPE_ScnDldRequest,				//ϵͳ���� 4
	DDSTYPE_SysRdyRequest,				//ϵͳԤλ 5
	DDSTYPE_SysModeSet,					//ģʽ���� 6
	DDSTYPE_SysCtrlRequest,				//���п��� 7
	DDSTYPE_SysStqRequest,				//״̬��ѯ 8
	DDSTYPE_ScnPlatUpdate,				//ƽ̨�˶����� 9
	DDSTYPE_ScnEventUpdate,				//�����¼����� A
	DDSTYPE_SysResetReply,				//ϵͳ��λ�ظ�
	DDSTYPE_SysHaltNotify,				//ϵͳ��ֹ�ظ�
	DDSTYPE_SysBitReply,				//ϵͳ�Լ�ظ�
	DDSTYPE_SysDldNotify,				//ϵͳ���ػظ�
	DDSTYPE_SysRdyNotify,				//ϵͳԤλ�ظ�
	DDSTYPE_SysModeReply,				//ģʽ���ûظ�
	DDSTYPE_SysCtrlReply,				//���п��ƻظ�,��У������״̬�ظ�
	DDSTYPE_SysStqReply,				//״̬�ظ�

	DDSTYPE_OwnInsUpdate,				//ƽ̨�ߵ�����
	DDSTYPE_ScnMixUpdate,				//�����ںϸ���
	DDSTYPE_RadEventReport,				//�״��¼��ϱ�
	DDSTYPE_RadPltReport,				//�״�㼣�ϱ�
	DDSTYPE_RadTrkReport,				//�״ﺽ���ϱ�
	DDSTYPE_EwEventReport,				//����ս�¼��ϱ�
	DDSTYPE_EwSortReport,				//����ս��ѡ�ϱ�
	DDSTYPE_EwSpecReport,				//����սƵ���ϱ�
	DDSTYPE_EwPDWReport,				//����սȫ�����ϱ� ""
	DDSTYPE_EwTgtLocReport,				//����սĿ�궨λ�ϱ�
	DDSTYPE_ReportSysStop,				//��ͣ�¼�

	DDSTYPE_RadParmNotify				//�״﹤�������ϱ�

};

#define DECLARE_DATATYPE_NOINIT(ClassName) \
	public:\
		ClassName(){} \
		virtual ~ClassName(){}

#define DECLARE_DATATYPE(ClassName,Type) \
	public:\
		ClassName(){ \
			DataType = Type; \
		} \
			virtual ~ClassName() {}

//DDS ������������
class DataTypeBase /*: public boost::enable_shared_from_this<CBase>*/
{
public:
	DataTypeBase()
	{}
	virtual ~DataTypeBase()
	{}
	UINT32 DataType;
};
typedef boost::shared_ptr<DataTypeBase> DataTypeBaseptr;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	ϵͳ��λ.  </summary>
///
/// <remarks>	�����, 2020/8/7. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////

class SysReset : public DataTypeBase
{
	DECLARE_DATATYPE(SysReset, DDSTYPE_SysResetRequest);

	UINT32 TargetSubSysID;			//Ŀ����ϵͳID
	UINT32 EquipmentNum;			//�豸����
	UINT32 EquipmentID[32];			//�豸ID
};
typedef boost::shared_ptr<SysReset> SysResetptr;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	ϵͳ��ֹ.  </summary>
///
/// <remarks>	�����, 2020/8/7. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////
class SysConclude : public DataTypeBase
{
	DECLARE_DATATYPE(SysConclude, DDSTYPE_SysHaltRequest);

};
typedef boost::shared_ptr<SysConclude> SysConcludeptr;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	ϵͳ�Լ�.  </summary>
///
/// <remarks>	�����, 2020/8/7. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////
class SysSelfCheck : public DataTypeBase
{
	DECLARE_DATATYPE(SysSelfCheck, DDSTYPE_SysBitRequest);
	UINT32 TargetSubSysID;			//Ŀ����ϵͳID
	UINT32 SelfCheckMode;			//�Լ췽ʽ
	UINT32 EquipmentNum;			//�豸����
	UINT32 EquipmentID[32];			//�豸ID
};
typedef boost::shared_ptr<SysSelfCheck> SysSelfCheckptr;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	ϵͳ����.  </summary>
///
/// <remarks>	�����, 2020/8/7. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////
class SysLoad : public DataTypeBase
{
	DECLARE_DATATYPE(SysLoad, DDSTYPE_ScnDldRequest);

	UINT32 TargetSubSysID;			//Ŀ����ϵͳID
	UINT32 ExpTestID;				//��������ID
	UINT32 Reserved[4];				//����
};
typedef boost::shared_ptr<SysLoad> SysLoadptr;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	ϵͳԤλ.  </summary>
///
/// <remarks>	�����, 2020/8/7. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////
class SysPrePosition : public DataTypeBase
{
	DECLARE_DATATYPE(SysPrePosition, DDSTYPE_SysRdyRequest);

	UINT32 TargetSubSysID;			//Ŀ����ϵͳID
};
typedef boost::shared_ptr<SysPrePosition> SysPrePositionptr;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	ģʽ����.  </summary>
///
/// <remarks>	�����, 2020/8/7. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////
class SysModeSet : public DataTypeBase
{
	DECLARE_DATATYPE(SysModeSet, DDSTYPE_SysModeSet);

	UINT32 SysWorkMode;				//ϵͳ����ģʽ
};
typedef boost::shared_ptr<SysModeSet> SysModeSetptr;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	���п���.  </summary>
///
/// <remarks>	�����, 2020/8/7. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////
class SysRunControl : public DataTypeBase
{
	DECLARE_DATATYPE(SysRunControl, DDSTYPE_SysCtrlRequest);

	UINT32 TargetSubSysID;			//Ŀ����ϵͳID
	UINT32 CommondID;				//0-��ʼ��1-������2-��ͣ��3-�ָ���4-��ֹ
	UINT32 TYear;					//ԤԼִ��ʱ�䣺�ꣻȡֵ��Χ��2000-2099
	UINT32 TMouth;					//ԤԼִ��ʱ�䣺�£�ȡֵ��Χ��1-12
	UINT32 TDay;					//ԤԼִ��ʱ�䣺�գ�ȡֵ��Χ��1-31
	UINT32 THour;					//ԤԼִ��ʱ�䣺ʱ��ȡֵ��Χ��0-23
	UINT32 TMinute;					//ԤԼִ��ʱ�䣺�֣�ȡֵ��Χ��0-59
	UINT32 TSecond;					//ԤԼִ��ʱ�䣺�룻ȡֵ��Χ��0-59
	UINT32 ExpTestID;				//��������ID
};
typedef boost::shared_ptr<SysRunControl> SysRunControlptr;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	״̬��ѯ.  </summary>
///
/// <remarks>	�����, 2020/8/7. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////
class SysStateSeek : public DataTypeBase
{
	DECLARE_DATATYPE(SysStateSeek, DDSTYPE_SysStqRequest);

	UINT32 TargetSubSysID;			//Ŀ����ϵͳID
};
typedef boost::shared_ptr<SysStateSeek> SysStateSeekptr;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	ƽ̨�˶�����.  </summary>
///
/// <remarks>	�����, 2020/8/7. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////
class EntityMotionParam : public DataTypeBase
{
	DECLARE_DATATYPE_NOINIT(EntityMotionParam);

	UINT32 EntityID;				//����ʵ��ID
	float  EntityPosLon;			//ƽ̨λ�ã�����  ��Χ��-180~180����λ����
	float  EntityPosLat;			//ƽ̨λ�ã�γ��	 ��Χ��-90~90����λ����
	float  EntityPosHight;			//ƽ̨λ�ã��߶�	 ��Χ��-1000~30000����λ����
	float  EntityPosAzimuth;		//ƽ̨��̬��ƫ��	 ��Χ��-180~180����λ����
	float  EntityPosPitch;			//ƽ̨��̬������	 ��Χ��-90~90����λ����
	float  EntityPosRoll;			//ƽ̨��̬�����	 ��Χ��-180~180����λ����
	float  EntityVelEast;			//ƽ̨�ٶȣ�����	 ��Χ��-2000~2000����λ��m/s
	float  EntityVelNorth;			//ƽ̨�ٶȣ�����	 ��Χ��-2000~2000����λ��m/s
	float  EntityVelUnder;			//ƽ̨�ٶȣ�����	 ��Χ��-1000~1000����λ��m/s
	float  EntityAccEast;			//ƽ̨���ٶȣ�����	��λ��m/s^2
	float  EntityAccNorth;			//ƽ̨���ٶȣ�����	��λ��m/s^2
	float  EntityAccUnder;			//ƽ̨���ٶȣ�����	��λ��m/s^2
	float  EntityAngVelAzimuth;		//ƽ̨���ٶȣ�ƫ��	��λ��deg/s
	float  EntityAngVelPitch;		//ƽ̨���ٶȣ�����	��λ��deg/s
	float  EntityAngVelRoll;		//ƽ̨���ٶȣ����	��λ��deg/s
};
typedef boost::shared_ptr<EntityMotionParam> EntityMotionParamptr;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	ƽ̨�˶�����.  </summary>
///
/// <remarks>	�����, 2020/8/7. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////
class SysMotionUpdate : public DataTypeBase
{
	DECLARE_DATATYPE(SysMotionUpdate, DDSTYPE_ScnPlatUpdate);

	UINT32 SIMStepOrder;						//����������ţ���������֡��������ǰ��10ms��Ϊ�̶��ķ����������
	UINT32 ForceEntityNum;						//����ʵ������
	EntityMotionParam  EntityMotionInfo[32];	//ƽ̨�˶�����
};
typedef boost::shared_ptr<SysMotionUpdate> SysMotionUpdateptr;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	�����¼��������ࣨͬʱ�������¼�����Ϊ�ػ��򿪻�ʱ�����¼�����Ϊ��0-�ػ���1-����ʱ��.  </summary>
///
/// <remarks>	�����, 2020/8/7. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////
class SimEventParamBase : public DataTypeBase
{
	DECLARE_DATATYPE_NOINIT(SimEventParamBase);
};
typedef boost::shared_ptr<SimEventParamBase> SimEventParamBaseptr;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	�����¼�����-����ģʽ�л�ʱ���¼�����Ϊ��2-����ģʽ�л�ʱ��.  </summary>
///
/// <remarks>	�����, 2020/8/7. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////
class SimEventParam2 : public SimEventParamBase
{
	DECLARE_DATATYPE_NOINIT(SimEventParam2);

	UINT32 WorkModeID;						//Ŀ��ģʽID,�ο�װ������ģ���ļ��ж�ӦID�������Ĺ���ģʽ����
};
typedef boost::shared_ptr<SimEventParam2> SimEventParam2ptr;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	�����¼�����-פ����λ�л�ʱ���¼�����Ϊ��101-פ����λ�л����״�ר�ã�ʱ��.  </summary>
///
/// <remarks>	�����, 2020/8/7. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////
class SimEventParam101 : public SimEventParamBase
{
	DECLARE_DATATYPE_NOINIT(SimEventParam101);

	UINT32 TargetWaveNumb;						//Ŀ�Ĳ�λ���
	UINT32 SignalWavetotal;						//�źŲ�������
	UINT32 SignalWaveID1;						//�źŲ���ID1������װ������ģ���ļ��ж�ӦID���������źŲ��β���
	UINT32 SignalWaveID2;						//�źŲ���ID2������װ������ģ���ļ��ж�ӦID���������źŲ��β���
	UINT32 SignalWaveID3;						//�źŲ���ID3������װ������ģ���ļ��ж�ӦID���������źŲ��β���
	UINT32 SignalWaveID4;						//�źŲ���ID4������װ������ģ���ļ��ж�ӦID���������źŲ��β���	
};
typedef boost::shared_ptr<SimEventParam101> SimEventParam101ptr;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	�����¼�����-�źŲ����л�ʱ���¼�����Ϊ��102-�źŲ����л�ʱ���״�ר�ã�ʱ��.  </summary>
///
/// <remarks>	�����, 2020/8/7. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////
class SimEventParam102 : public SimEventParamBase
{
	DECLARE_DATATYPE_NOINIT(SimEventParam102);

	UINT32 TargetSignalWaveID;						//Ŀ���źŲ���ID
};
typedef boost::shared_ptr<SimEventParam102> SimEventParam102ptr;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	�����¼�����-����Ŀ���л�ʱ���¼�����Ϊ��103-����Ŀ���л�ʱ���״�ר�ã�ʱ��.  </summary>
///
/// <remarks>	�����, 2020/8/7. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////
class SimEventParam103 : public SimEventParamBase
{
	DECLARE_DATATYPE_NOINIT(SimEventParam103);

	UINT32 TrackTargetNum;						//����Ŀ������
	UINT32 TargetID[32];							//Ŀ��ʵ��ID
};
typedef boost::shared_ptr<SimEventParam103> SimEventParam103ptr;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	�����¼�����-���������л�ʱ���¼�����Ϊ��104-���������л�ʱ���״�ר�ã�ʱ��.  </summary>
///
/// <remarks>	�����, 2020/8/7. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////
class SimEventParam104 : public SimEventParamBase
{
	DECLARE_DATATYPE_NOINIT(SimEventParam104);

	DOUBLE BeamDiagramFrqPoint;						//��������ͼƵ�㣬��Χ��0~100000����λ��MHz
	DOUBLE BeamDiagramStep;						//��������ͼ��������Χ��0~10����λ����
	DOUBLE BeamDiagramType;						//��������ͼ���ͣ���Χ��0~1
	UINT32 BeamDiagramNum;						//��������ͼ����
												//float  BeamDiagram[����];					//����ͼ���飬��Χ��-200~200����λ��dB
	std::vector<float> BeamDiagramVar;
};
typedef boost::shared_ptr<SimEventParam104> SimEventParam104ptr;


////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	�����¼�����-��������ʱ���¼�����Ϊ��201-��������ʱ������ר�ã�ʱ��.  </summary>
///
/// <remarks>	�����, 2020/8/7. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////
class MissileSend201 : public SimEventParamBase
{
	DECLARE_DATATYPE_NOINIT(MissileSend201);

	UINT32 MissileBSEID;						//��������ƽ̨ID
	UINT32 MissileTargetID;						//��������Ŀ��ID
	UINT32 MissileID;							//��������ID������Ψһ��ʶ�������滮ʱ��̬����
};
typedef boost::shared_ptr<MissileSend201> MissileSend201ptr;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	�����¼�����-������ըʱ���¼�����Ϊ��202-������ըʱ������ר�ã�ʱ��.  </summary>
///
/// <remarks>	�����, 2020/8/7. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////
class MissileBomb202 : public SimEventParamBase
{
	DECLARE_DATATYPE_NOINIT(MissileBomb202);

	UINT32 MissileHitSign;						//�������б�ʶ��0-δ����Ŀ�꣬1-����Ŀ��
};
typedef boost::shared_ptr<MissileBomb202> MissileBomb202ptr;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	�����¼�����-����Ŀ���л�ʱ���¼�����Ϊ��203-����Ŀ���л�ʱ������ר�ã�ʱ��.  </summary>
///
/// <remarks>	�����, 2020/8/7. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////
class ShiftTarget203 : public SimEventParamBase
{
	DECLARE_DATATYPE_NOINIT(ShiftTarget203);

	UINT32 MissileTargetID;						//��������Ŀ��ID
};
typedef boost::shared_ptr<ShiftTarget203> ShiftTarget203ptr;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	�����¼�����-�Ƶ�ģʽ�л�ʱ���¼�����Ϊ��204-�Ƶ�ģʽ�л�ʱ������ר�ã�ʱ��.  </summary>
///
/// <remarks>	�����, 2020/8/7. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////
class ShiftGuide204 : public SimEventParamBase
{
	DECLARE_DATATYPE_NOINIT(ShiftGuide204);

	UINT32 TargetGuideID;						//Ŀ���Ƶ�ģʽID
};
typedef boost::shared_ptr<ShiftGuide204> ShiftGuide204ptr;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	�����¼�����.  </summary>
///
/// <remarks>	�����, 2020/8/7. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////
class SimEventDescribe : public DataTypeBase
{
	DECLARE_DATATYPE_NOINIT(SimEventDescribe);

	UINT32 EntityID;							//����ʵ��ID
	UINT32 EquipmentID;							//װ������ID
	UINT32 TimeDt;								//ʱ��ƫ�ƣ�ȡֵ��Χ��0~10000����λ��us
	UINT32 EventCodeID;							//�¼����룬0-�ػ���1-������2-����ģʽ�л��� \
																								101-פ����λ�л����״�ר�ã���102-�źŲ����л����״�ר�ã���103-����Ŀ���л����״�ר�ã���\
												  104-���������л����״�ר�ã���201-�������䣨����ר�ã���202-������ը������ר�ã���\
												  203-����Ŀ���л�������ר�ã���204-�Ƶ�ģʽ�л�������ר�ã�������Ԥ��
	SimEventParamBase SIMEventInfo[32];			//�����¼�����
};
typedef boost::shared_ptr<SimEventDescribe> SimEventDescribeptr;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	�����¼�����.  </summary>
///
/// <remarks>	�����, 2020/8/7. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////
class SysEventPub : public DataTypeBase
{
	DECLARE_DATATYPE(SysEventPub, DDSTYPE_ScnEventUpdate);

	UINT32 SIMStepOrder;						//��������������,��������֡��������ǰ��10ms��Ϊ�̶��ķ����������
	UINT32 SIMEventNum;							//�����¼�����
	SimEventDescribe SimEventInfo[32];			//�����¼�����
};
typedef boost::shared_ptr<SysEventPub> SysEventPubptr;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	ƽ̨�ߵ�����.  </summary>
///
/// <remarks>	�����, 2020/8/7. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////
class UpdateNavigationInfo : public DataTypeBase
{
	DECLARE_DATATYPE(UpdateNavigationInfo, DDSTYPE_OwnInsUpdate);

	UINT32 SIMStepOrder;								//��������������,��������֡��������10ms���ı�ʾ����ʱ��
	DOUBLE  NavigationLon;								//����,��Χ��-180~180����λ����
	DOUBLE  NavigationLat;								//γ��,��Χ��-90~90����λ����
	DOUBLE  NavigationHight;							//��ѹ�߶�,��Χ��0~9999����λ����
	DOUBLE  RadioAltitude;								//���ߵ�߶�,��Χ��0~9999����λ����
	DOUBLE  NavigationRoll;								//�����,��Χ��-180~180����λ����
	DOUBLE  NavigationPitch;							//������,��Χ��-90~90����λ����
	DOUBLE  NavigationTrueAzimuth;						//�溽��,��Χ��-180~180����λ����
	DOUBLE  NavigationElecAzimuth;						//�ź���,��Χ��-180~180����λ����
	DOUBLE  NavigationVelEast;							//�����ٶȣ���Χ��-9999~9999����λ��m/s
	DOUBLE  NavigationVelNorth;							//�����ٶȣ���Χ��-9999~9999����λ��m/s
	DOUBLE  NavigationVelUnder;							//�����ٶȣ���Χ��-9999~9999����λ��m/s
	DOUBLE  VacuumVelcity;								//����٣���Χ��0~9999����λ��m/s
	DOUBLE  EarthVelcity;								//���٣���Χ��0~9999����λ��m/s
};
typedef boost::shared_ptr<UpdateNavigationInfo> UpdateNavigationInfoptr;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	�����ںϸ���.  </summary>
///
/// <remarks>	�����, 2020/8/7. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////
class UpdateScenarioData : public DataTypeBase
{
	DECLARE_DATATYPE(UpdateScenarioData, DDSTYPE_ScnMixUpdate);

};
typedef boost::shared_ptr<UpdateScenarioData> UpdateScenarioDataptr;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	�״��¼��ϱ�.  </summary>
///
/// <remarks>	�����, 2020/8/7. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////
class ReportRadarEvent : public DataTypeBase
{
	DECLARE_DATATYPE(ReportRadarEvent, DDSTYPE_RadEventReport);

};
typedef boost::shared_ptr<ReportRadarEvent> ReportRadarEventptr;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	�״�㼣�ϱ�.  </summary>
///
/// <remarks>	�����, 2020/8/7. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////
class ReportRadarTrace : public DataTypeBase
{
	DECLARE_DATATYPE(ReportRadarTrace, DDSTYPE_RadPltReport);

};
typedef boost::shared_ptr<ReportRadarTrace> ReportRadarTraceptr;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	�״ﺽ���ϱ�.  </summary>
///
/// <remarks>	�����, 2020/8/7. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////
class ReportRadarTrack : public DataTypeBase
{
	DECLARE_DATATYPE(ReportRadarTrack, DDSTYPE_RadTrkReport);
};
typedef boost::shared_ptr<ReportRadarTrack> ReportRadarTrackptr;



////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	ϵͳ��ͣ�ϱ�.  </summary>
///
/// <remarks>	�����, 2020/8/7. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////
class ReportSysStop : public DataTypeBase
{
	DECLARE_DATATYPE_NOINIT(ReportSysStop);

	UINT32 SubSysID;				//��ϵͳID
	CHAR StopDetail[512];			//��ͣ�������
};
typedef boost::shared_ptr<ReportRadarTrace> ReportRadarTraceptr;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	����Դ�ϱ���Ϣ����.  </summary>
///
/// <remarks>	�����, 2020/8/7. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////
class RadiationSocDetail : public DataTypeBase
{
	DECLARE_DATATYPE_NOINIT(RadiationSocDetail);

	UINT32 BSEID;					//ƽ̨ID
	UINT32 EquipID;					//����ԴID
	UINT32 BSEIdentification;		//ƽ̨�������ԣ�0-δ���壬1-�ҷ���2-�з���3-�ѷ���4-������5�Ժ�Ԥ����
	UINT32 BSEType;					//ƽ̨���ͣ�0-δ֪��1-����̶���2-�����ƶ���3-ˮ�棬4-ˮ�£�5-������6-�̶���\
																											//7-��ת��8-���˻���9-���ǣ�10-����ƽ̨��12-��Я��13�Ժ�Ԥ��
	UINT32 EquipType;				//����Դ���ͣ�0-δ֪��1-�����״2-�Կվ����״3-�Ժ������״4-�Ϳվ����״\
																											//5-�����״6-Ŀ��ָʾ�״7-����״8-Ԥ���״9-����Ԥ���״10-���������״\
									//11-�����״12-�����Ƶ��״13-���������״14-���׹����״15-�๦���״16-����ĩ�Ƶ��״\
									//17-��ը��׼�״18-����״19-ս������״20-��λ���У���״21-�Ŀ�����У���״\
									//22-���չ����״23-�����״24-���θ����״25-��½�����״26-�ۿڼ����״27-�����״\
									//28-�����״29-����ʶ������30-�����״31-�����״�
	float  BSEPosLon;				//ƽ̨λ�ã����� ���������ϵ���������� ��Χ��-180~180����λ����
	float  BSEPosLat;				//ƽ̨λ�ã�γ��	���������ϵ�������ϸ� ��Χ��-90~90����λ����
	float  BSEPosHight;				//ƽ̨λ�ã��߶ȣ��������ϵ�������¸������θ߶�	 ��Χ��-1000~30000����λ����
	float  BSEAzimuth;				//ƽ̨��λ���ػ���������ϵ��Ŀ����Է�λ ��Χ��-180~180����λ����
	float  BSEPitch;				//ƽ̨�������ػ���������ϵ��Ŀ����Ը���	 ��Χ��-90~90����λ����
	float  BSEDistance;				//ƽ̨б��	 ��Χ��0~999999����λ����
	float  BSERadialVel;			//ƽ̨�����ٶȣ���Ϊ�ӽ�����ΪԶ�룬��λ��m/s
	float  BSETangentialVel;		//ƽ̨�����ٶȣ���Ϊ��ʱ�룬��Ϊ˳ʱ�룬��λ��m/s
	UINT32 RadiSocWorkMode;			//����Դ����ģʽ��0-δ֪��1-������2-���٣�3-�Ƶ���4-TWS��5-TAS��6�Ժ�Ԥ��
	UINT32 RadiSocPolarMode;		//����Դ������ʽ,0-δ֪��1-��Բ������2-��Բ������3-��ֱ������4-ˮƽ������5-б������6-������ѡ��7-�������룬\
																											//8-�����ݱ䣬9-������Բ������10-������Բ������11�Ժ�Ԥ��

	UINT32 SignalModulation;		//�źŵ��Ʒ�ʽ��0-������1-���棬2-�����Ե�Ƶ��3-���Ե�Ƶ��4-������룬5-������룬6-Ƶ�ʱ��룬7-Ƶ�ʷּ���8�Ժ�Ԥ��
	float  ScanPeriod;				//ɨ������,��λ��ms
	float  waveStateTime;			//��λפ��ʱ��,��λ��ms
	float  CoherentInterval;		//��ɴ�����,��λ��ms
	UINT32 SigFreqType;				//�ź�Ƶ������,0-������1-�̶���2-��䣬3-�ּ���4-ԭ���룬5-�ݱ䣬6-��Ƶ�β7-������Ƶ�ʵ��ƣ�8-������������ƣ�\
																											//9-�������������ƣ� 10-����Ƶ�ʱ��루ȥ������11�Ժ�Ԥ��
	UINT32 SigFreqCount;			//�ź�Ƶ����,ȡֵ��Χ��1~64
	float  MidFrequence;			//�ź�Ƶ����ֵ,ȡֵ��Χ��30~40000,��λ��MHz
	float  RangeFrequence;			//�ź�Ƶ�ʷ�Χ,ȡֵ��Χ��30~40000,��λ��MHz
	UINT32 FreqList;				//Ƶ���б�,ȡֵ��Χ��1~64,64��Ƶ��(Ƶ�㲻��ʱҲ������)������Ƶ�ʶ���������Ӱ��
	UINT32 PRIType;					//�ź�PRI����,0-������1-�̶���2-�Ժ�����3-������4-�Ժ�����5-�β6-�Ժ�����7-���䣬8-�Ժ�����9�Ժ�Ԥ��
	UINT32 PRITotal;				//�ź�PRI����,ȡֵ��Χ��1~64,������PRI���������ĵ���
	float  PRIMiddle;				//�ź�PRI��ֵ,��λ��us;ȡֵ��Χ��1~99999
	float  PRIRange;				//�ź�PRI��Χ,��λ��us;��Ӧ���������̶�PRI��Ӱ��
	UINT32 PRIList;					//�ź�PRI�б�,ȡֵ��Χ��1~64,64��PRI(PRI����ʱҲ������)������PRI����������Ӱ��
	UINT32 PWType;					//�ź�PW���ͣ�0-������1-�̶���2-���䣬3�Ժ�Ԥ��
	float  PWMiddle;				//�ź�PW��ֵ,��λ��us;ȡֵ��Χ��1~99999
	float  PWRange;					//�ź�PW��Χ,��λ��us;ȡֵ��Χ��1~99999
	UINT32 PWList;					//�ź�PRI�б�,ȡֵ��Χ��1~64,64��PW(PW����ʱҲ������)������PW����������Ӱ��
};
typedef boost::shared_ptr<RadiationSocDetail> RadiationSocDetailptr;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	��������Դ�ں��ϱ�.  </summary>
///
/// <remarks>	�����, 2020/8/7. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////
class ReportFusion : public DataTypeBase
{
	DECLARE_DATATYPE_NOINIT(ReportFusion);

	UINT32 SimTYear;							//��������ʱ�䣺�ꣻȡֵ��Χ��2000-2099
	UINT32 SimTMouth;							//��������ʱ�䣺�£�ȡֵ��Χ��1-12
	UINT32 SimTDay;								//��������ʱ�䣺�գ�ȡֵ��Χ��1-31
	UINT32 SimTHour;							//��������ʱ�䣺ʱ��ȡֵ��Χ��0-23
	UINT32 SimTMinute;							//��������ʱ�䣺�֣�ȡֵ��Χ��0-59
	UINT32 SimTSecond;							//��������ʱ�䣺�룻ȡֵ��Χ��0-59
	UINT32 SimTMicSecond;						//��������ʱ�䣺���룻ȡֵ��Χ��1~999
	UINT32 RadsourceTotal;						//����Դ������ȡֵ��Χ��1~2000
	RadiationSocDetail RadSourDetial[2000];		//����Դ��Ϣ����
};
typedef boost::shared_ptr<ReportFusion> ReportFusionptr;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	�Լ�ظ����ݸ�ʽ����.  </summary>
///
/// <remarks>	�����, 2020/8/7. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////
class SCRespondDetial : public DataTypeBase
{
	DECLARE_DATATYPE_NOINIT(SCRespondDetial);

	UINT32 EquiID;							//�豸Id��
	UINT32 EquiSelfCheckResult;				//�豸�Լ�����0-�ɹ���1-ʧ�ܣ�3�Ժ�Ԥ����
	char   ResultParam[256];				//�豸�Լ��������飻������ϵͳ�ṩ���豸�Լ���xml���и�ʽ�����������Ϊ��ϵͳ�ϱ�������Ĳ���ֵ�ַ�������[,]�ָ�
};
typedef boost::shared_ptr<SCRespondDetial> SCRespondDetialptr;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	�Լ�ظ�.  </summary>
///
/// <remarks>	�����, 2020/8/7. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////
class SelfCheckReply : public DataTypeBase
{
	DECLARE_DATATYPE_NOINIT(SelfCheckReply);

	UINT32							SubSysID;						//�豸��ϵͳId��
	UINT32							SubSelfCheckResult;				//��ϵͳ�Լ�����0-�ɹ���1-ʧ�ܣ�3�Ժ�Ԥ���� 
	UINT32							SubSelfCheckTotal;				//�豸�Լ�������N��Ҫ����ϵͳ�ϱ������豸/�������Լ������ں��渽���豸�Լ��������� \
																																																			//Ϊȷ������Ч�ʣ�ÿ�����32���豸���������������һ��
	std::vector<SCRespondDetial>	SubSysDetial;					//��ϵͳ����
};
typedef boost::shared_ptr<SelfCheckReply> SelfCheckReplyptr;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	���ػظ�.  </summary>
///
/// <remarks>	�����, 2020/8/7. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////
class LoadRespond : public DataTypeBase
{
	DECLARE_DATATYPE_NOINIT(LoadRespond);

	UINT32	TargetSysID;						//Ŀ����ϵͳId��
	UINT32	TargetSelfExcResult;				//ִ�н����0-�ɹ���1-ʧ�ܣ�2�Ժ�Ԥ��
	char	ErrorDetil[256];					//�����ϵͳִ�н������ʧ�ܣ���ͬʱ���ش��������ַ���
};
typedef boost::shared_ptr<LoadRespond> LoadRespondptr;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Ԥλ�ϱ�����.  </summary>
///
/// <remarks>	�����, 2020/8/7. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////
class PrePosReportDetial : public DataTypeBase
{
	DECLARE_DATATYPE_NOINIT(PrePosReportDetial);

	UINT32	EquipID;								//�豸Id��
	UINT32	EquipPrePosResult;						//�豸Ԥλ�����0-�ɹ���1-ʧ�ܣ�3�Ժ�Ԥ����
	char	EquipPrePosDetial[256];					//�豸Ԥλ����������

};
typedef boost::shared_ptr<PrePosReportDetial> PrePosReportDetialptr;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Ԥλ�ϱ�.  </summary>
///
/// <remarks>	�����, 2020/8/7. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////
class PrePosReport : public DataTypeBase
{
	DECLARE_DATATYPE_NOINIT(PrePosReport);

	UINT32	SubSysID;											//��ϵͳId��
	UINT32	SubSysPrePosResult;									//��ϵͳԤλ�����0-�ɹ���1-ʧ�ܣ�3�Ժ�Ԥ����
	UINT32	EquipPrePosTotal;									//�豸Ԥλ�������:Ҫ����ϵͳ�ϱ������豸/������Ԥλ������ں��渽���豸Ԥλ���������\
																																																//Ϊȷ������Ч�ʣ�ÿ�����32���豸���������������һ��
	std::vector<PrePosReportDetial> EquipPrePos;				//�����ϵͳִ�н������ʧ�ܣ���ͬʱ���ش��������ַ���
};
typedef boost::shared_ptr<PrePosReport> PrePosReportptr;


////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	״̬�ظ�����.  </summary>
///
/// <remarks>	�����, 2020/8/7. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////
class ResponseStateDetial : public DataTypeBase
{
	DECLARE_DATATYPE_NOINIT(ResponseStateDetial);

	UINT32	EquipID;								//�豸Id��
	char	EquipStateCheck[256];					//�豸״̬��ѯ�����飬������ϵͳ�ṩ���豸״̬��ѯxml���и�ʽ�����������Ϊ��ϵͳ�ϱ�������Ĳ���ֵ�ַ�������[,]�ָ�
};
typedef boost::shared_ptr<ResponseStateDetial> ResponseStateDetialptr;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	״̬�ظ�.  </summary>
///
/// <remarks>	�����, 2020/8/7. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////
class ResponseState : public DataTypeBase
{
	DECLARE_DATATYPE_NOINIT(ResponseState);

	UINT32	SubSysID;											//��ϵͳId��
	UINT32	SubSysStateCheck;									//��ϵͳ״̬��ѯ�����0-������1-�쳣��2�Ժ�Ԥ����
	UINT32	EquipPrePosTotal;									//�豸Ԥλ�������:Ҫ����ϵͳ�ϱ������豸/������Ԥλ������ں��渽���豸Ԥλ���������\
																																	//Ϊȷ������Ч�ʣ�ÿ�����32���豸���������������һ��
	std::vector<ResponseStateDetial> EquipStateCheck;			//�����ϵ��ѯ���
};
typedef boost::shared_ptr<ResponseState> ResponseStateptr;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	����ջ��Լ�--Ƶ���ϱ�.  </summary>
///
/// <remarks>	�����, 2020/8/7. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////
class RadSelfCheck : public DataTypeBase
{
	DECLARE_DATATYPE_NOINIT(RadSelfCheck);

	UINT32	SubSysID;											//��ϵͳId��
	UINT32	SignMark;											//�źű�ǣ�0-δ�쵽�źţ�1-�쵽�źţ�
	DOUBLE  SignFreq;	 										//�ź�Ƶ�ʣ��źż������쵽�ķ����ź�Ƶ��
	DOUBLE  SignPower;	 										//�źŹ��ʣ��źż������쵽�ķ����źŹ���
	UINT32  FreqTotal;	 										//Ƶ�׵�����1~1024
	std::vector<DOUBLE> FreqRange;								//Ƶ����ȣ���Χ��-80~20����λ��dBm
};
typedef boost::shared_ptr<RadSelfCheck> RadSelfCheckptr;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	�豸����ָ���ϱ�����.  </summary>
///
/// <remarks>	�����, 2020/8/7. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////
class EquipCommandDetial : public DataTypeBase
{
	DECLARE_DATATYPE_NOINIT(EquipCommandDetial);

	char    ParamName[32];								//�������ƣ�
	DOUBLE  ParamValue;									//����ֵ��
	char	ParamUnit[32];								//������λ��
};
typedef boost::shared_ptr<EquipCommandDetial> EquipCommandDetialptr;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	�豸����ָ���ϱ�.  </summary>
///
/// <remarks>	�����, 2020/8/7. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////
class EquipCommand : public DataTypeBase
{
	DECLARE_DATATYPE_NOINIT(EquipCommand);

	UINT32	SubSysID;											//��ϵͳId��
	UINT32	EquipID;											//�豸Id��
	CHAR    CommandName[64];									//ָ�����ƣ�
	UINT32	ParamTotal;											//��������:���ϱ���ϵͳ����ѡ���ص�����ϱ�;Ϊȷ������Ч�ʣ�ÿ�����32���豸���������������һ��
	std::vector<EquipCommandDetial> ParamDetial;				//�ϱ�����
};
typedef boost::shared_ptr<EquipCommand> EquipCommandptr;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	�㼣�ϱ�.  </summary>
///
/// <remarks>	�����, 2020/8/7. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////
class ReportTrace : public DataTypeBase
{
	DECLARE_DATATYPE_NOINIT(ReportTrace);

	UINT32	RadarID;											//�״�Id��
	UINT32	TraceID;											//�㼣Id��
	UINT32  TraceTYear;											//�㼣ʱ�䣺�ꣻȡֵ��Χ��2000-2099
	UINT32  TraceTMouth;										//�㼣ʱ�䣺�£�ȡֵ��Χ��1-12
	UINT32  TraceTDay;											//�㼣ʱ�䣺�գ�ȡֵ��Χ��1-31
	UINT32  TraceTHour;											//�㼣ʱ�䣺ʱ��ȡֵ��Χ��0-23
	UINT32  TraceTMinute;										//�㼣ʱ�䣺�֣�ȡֵ��Χ��0-59
	UINT32  TraceTSecond;										//�㼣ʱ�䣺�룻ȡֵ��Χ��0-59
	UINT32  TraceTMicSecond;									//�㼣ʱ�䣺���룻ȡֵ��Χ��1~999
	DOUBLE	TraceDistance;										//�㼣����
	DOUBLE	TraceDoppler;										//�㼣������
	UINT32	HorizBeamNum;										//ˮƽ������
	UINT32	VertiBeamNum;										//��ֱ������
	UINT32	ChannelNum;											//Ƶ����
	UINT32	ChannelMark;										//Ƶ����ʶ
	UINT32	PulseMark;											//�����ʶ
	UINT32	EPNum;												//EP��
	DOUBLE	StartDistance;										//��ʼ����
	DOUBLE	EndDistance;										//��������
	DOUBLE	StartDirection;										//��ʼ��λ
	DOUBLE	EndDirection;										//������λ
	DOUBLE	StartAD;											//��ʼAD
	DOUBLE	EndAD;												//����AD
	DOUBLE	StartDistanceRange;									//��ʼ�������	
	DOUBLE	EndDistanceRange;									//�����������
	DOUBLE	StartDirectionRange;								//��ʼ��λ����	
	DOUBLE	EndDirectionRange;									//������λ����
	DOUBLE	BeamRange;											//��������
	DOUBLE	SectionLevel;										//�����ȼ�
	UINT32  TraceQuality;										//�㼣����
	UINT32  TraceMark;											//�㼣��־
};
typedef boost::shared_ptr<ReportTrace> ReportTraceptr;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	�����ϱ�.  </summary>
///
/// <remarks>	�����, 2020/8/7. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////
class ReportTrack : public DataTypeBase
{
	DECLARE_DATATYPE_NOINIT(ReportTrack);

	UINT32	RadarID;											//�״�Id��
	UINT32	TrackID;											//����Id��
	UINT32  TrackTYear;											//����ʱ�䣺�ꣻȡֵ��Χ��2000-2099
	UINT32  TrackTMouth;										//����ʱ�䣺�£�ȡֵ��Χ��1-12
	UINT32  TrackTDay;											//����ʱ�䣺�գ�ȡֵ��Χ��1-31
	UINT32  TrackTHour;											//����ʱ�䣺ʱ��ȡֵ��Χ��0-23
	UINT32  TrackTMinute;										//����ʱ�䣺�֣�ȡֵ��Χ��0-59
	UINT32  TrackTSecond;										//����ʱ�䣺�룻ȡֵ��Χ��0-59
	UINT32  TrackTMicSecond;									//����ʱ�䣺���룻ȡֵ��Χ��1~999
	DOUBLE	CalDistance;										//Ԥ�����
	DOUBLE	CalDirection;										//Ԥ�ⷽλ
	UINT32	IFFCode;											//IFF����	
	DOUBLE	ObserveDistance;									//�۲����
	DOUBLE	ObserveDirection;									//�۲ⷽλ
	UINT32  TrackQuality;										//��������
	UINT32  ATCRBSModeI;										//�����״�ģʽ1Ӧ��
	UINT32  ATCRBSModeII;										//�����״�ģʽ2Ӧ��
	UINT32  ATCRBSModeIII;										//�����״�ģʽ3/AӦ��
	DOUBLE  ATCRBSHight;										//�����״�߶�
};
typedef boost::shared_ptr<ReportTrack> ReportTrackptr;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	�״�����ϱ�.  </summary>
///
/// <remarks>	�����, 2020/8/7. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////
class ReportRadarParam : public DataTypeBase
{
	DECLARE_DATATYPE_NOINIT(ReportRadarParam);

	UINT32	RadarID;											//�״�Id��
	UINT32	TrackID;											//����Id��
	UINT32  TraceTYear;											//�㼣ʱ�䣺�ꣻȡֵ��Χ��2000-2099
	UINT32  TraceTMouth;										//�㼣ʱ�䣺�£�ȡֵ��Χ��1-12
	UINT32  TraceTDay;											//�㼣ʱ�䣺�գ�ȡֵ��Χ��1-31
	UINT32  TraceTHour;											//�㼣ʱ�䣺ʱ��ȡֵ��Χ��0-23
	UINT32  TraceTMinute;										//�㼣ʱ�䣺�֣�ȡֵ��Χ��0-59
	UINT32  TraceTSecond;										//�㼣ʱ�䣺�룻ȡֵ��Χ��0-59
	UINT32  TraceTMicSecond;									//�㼣ʱ�䣺���룻ȡֵ��Χ��1~999
	UINT32	WorkModeID;											//����ģʽId	:��Ӧ�״�ģ�������й���ģʽId,��Χ��0~255
	INT32   FreqCode;											//Ƶ����
	INT32   CynPlus;											//ͬ������
	DOUBLE  SNR;												//���ű�
};
typedef boost::shared_ptr<ReportRadarParam> ReportRadarParamptr;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	��ѡ�ϱ�.  </summary>
///
/// <remarks>	�����, 2020/8/7. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////
class ReportSorting : public DataTypeBase
{
	DECLARE_DATATYPE_NOINIT(ReportSorting);

	UINT32	IndexSUT;							//SUT����,SUT�ڳ����е����������ڶ��ػ�������
	UINT32  TraceTYear;							//�㼣ʱ�䣺�ꣻȡֵ��Χ��2000-2099
	UINT32  TraceTMouth;						//�㼣ʱ�䣺�£�ȡֵ��Χ��1-12
	UINT32  TraceTDay;							//�㼣ʱ�䣺�գ�ȡֵ��Χ��1-31
	UINT32  TraceTHour;							//�㼣ʱ�䣺ʱ��ȡֵ��Χ��0-23
	UINT32  TraceTMinute;						//�㼣ʱ�䣺�֣�ȡֵ��Χ��0-59
	UINT32  TraceTSecond;						//�㼣ʱ�䣺�룻ȡֵ��Χ��0-59
	UINT32  TraceTMicSecond;					//�㼣ʱ�䣺���룻ȡֵ��Χ��1~999
	UINT32	TargetBatchNum;						//Ŀ������
	UINT32	TargetIdentification;				//Ŀ���������
	UINT32	TargetType;							//Ŀ��ƽ̨����
	UINT32	TargetLevel;						//Ŀ����в�ȼ�
	UINT32	RadType;							//����Դ����:0-δ֪��1-�����״2-�Կվ����״3-�Ժ������״4-�Ϳվ����״5-�����״\
																																				//6-Ŀ��ָʾ�״7-����״8-Ԥ���״9-����Ԥ���״10-���������״11-�����״\
												//12-�����Ƶ��״13-���������״14-���׹����״15-�๦���״16-����ĩ�Ƶ��״\
												// 17-��ը��׼�״18-����״19-ս������״20-��λ���У���״21-�Ŀ�����У���״\
												// 22-���չ����״23-�����״24-���θ����״25-��½�����״26-�ۿڼ����״27-�����״\
												// 28-�����״29-����ʶ������30-�����״31-�����״�
	DOUBLE  TargetPosLon;						//Ŀ��λ�ã�����  ��Χ��-180~180����λ����
	DOUBLE  TargetPosLat;						//Ŀ��λ�ã�γ��	 ��Χ��-90~90����λ����
	DOUBLE  TargetPosHight;						//Ŀ��λ�ã��߶�	 ��Χ��-1000~30000����λ����
	DOUBLE  TargetPosAzimuth;					//Ŀ�귽λ	 ��Χ��-180~180����λ����
	DOUBLE  TargetPosPitch;						//Ŀ�긩��	 ��Χ��-90~90����λ����
	DOUBLE  TargAzimuthVari;					//Ŀ�귽λ����	
	DOUBLE  TargPitchVari;						//Ŀ�긩������	
	DOUBLE	TargetDistance;						//Ŀ��б��	 ��Χ��0~999999����λ����
	DOUBLE	TargDisVari;						//Ŀ��б�෽��	 
	DOUBLE	TargetRadialVel;					//Ŀ�꾶���ٶȣ���Ϊ�ӽ�����ΪԶ�룬��λ��m/s
	DOUBLE	TargetTangentialVel;				//Ŀ�������ٶȣ���Ϊ��ʱ�룬��Ϊ˳ʱ�룬��λ��m/s
	DOUBLE	TargetRadiRangCode;					//����Դ���������
	DOUBLE	RadiSocWorkMode;					//����Դ����ģʽ��0-δ֪��1-������2-���٣�3-�Ƶ���4-TWS��5-TAS��6�Ժ�Ԥ��
	DOUBLE	RadiSocPolarMode;					//����Դ������ʽ,0-δ֪��1-��Բ������2-��Բ������3-��ֱ������4-ˮƽ������5-б������\
																																				//6-������ѡ��7-�������룬8-�����ݱ䣬9-������Բ������10-������Բ������11�Ժ�Ԥ��
	DOUBLE	SignalModulation;					//�źŵ��Ʒ�ʽ��0-������1-���棬2-�����Ե�Ƶ��3-���Ե�Ƶ��4-������룬5-������룬6-Ƶ�ʱ��룬7-Ƶ�ʷּ���8�Ժ�Ԥ��
	DOUBLE	ScanPeriod;							//ɨ������,��λ��ms
	DOUBLE	waveStateTime;						//��λפ��ʱ��,��λ��ms
	DOUBLE	CoherentInterval;					//��ɴ�����,��λ��ms
	UINT32	SigActState;						//�źŻ״̬
	UINT32	SigJamMark;							//�źŸ��ű��
	UINT32	SigFreqType;						//�ź�Ƶ������,0-������1-�̶���2-��䣬3-�ּ���4-ԭ���룬5-�ݱ䣬6-��Ƶ�β7-������Ƶ�ʵ��ƣ�\
																																				//8-������������ƣ�9-�������������ƣ� 10-����Ƶ�ʱ��루ȥ������11�Ժ�Ԥ��
	UINT32	SigFreqCount;						//�ź�Ƶ����,ȡֵ��Χ��1~64
	DOUBLE	MidFrequence;						//�ź�Ƶ����ֵ,ȡֵ��Χ��30~40000,��λ��MHz
	DOUBLE	RangeFrequence;						//�ź�Ƶ�ʷ�Χ,ȡֵ��Χ��30~40000,��λ��MHz
	UINT32	SigPRIType;							//�ź�PRI����,0-������1-�̶���2-���䣬3-������4-�ݱ䣬5-�β6-���룬7-���䣬8-��������9�Ժ�Ԥ��
	UINT32	SigPRITotal;						//�ź�PRI����
	DOUBLE	SigPRIMiddle;						//�ź�PRI��ֵ,��λ��us;ȡֵ��Χ��1~99999
	DOUBLE	SigPRIRange;						//�ź�PRI��Χ,��λ��us;��Ӧ���������̶�PRI��Ӱ��
	UINT32	PWType;								//�ź�PW���ͣ�0-������1-�̶���2-���䣬3�Ժ�Ԥ��
	UINT32	PWMiddle;							//�ź�PW��ֵ,��λ��us;ȡֵ��Χ��1~99999
	DOUBLE	PWRange;							//�ź�PW��Χ,��λ��us;ȡֵ��Χ��1~99999
	DOUBLE	PWList;								//�ź�PRI�б�,ȡֵ��Χ��1~64,64��PW(PW����ʱҲ������)������PW����������Ӱ��
};
typedef boost::shared_ptr<ReportSorting> ReportSortingptr;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	ECMƵ���ϱ�.  </summary>
///
/// <remarks>	�����, 2020/8/7. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////
class ReportECW : public DataTypeBase
{
	DECLARE_DATATYPE_NOINIT(ReportECW);

	UINT32				 SubSysID;				//��ϵͳId��
	UINT32				 FreqTotal;				//Ƶ�׵���,��Χ��1~1024��
	std::vector<DOUBLE>  Range;					//Ƶ����ȣ�

};
typedef boost::shared_ptr<ReportECW> ReportECWptr;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	SUT�¼�.  </summary>
///
/// <remarks>	�����, 2020/8/7. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////
class EventSUT : public DataTypeBase
{
	DECLARE_DATATYPE_NOINIT(EventSUT);

};
typedef boost::shared_ptr<EventSUT> EventSUTptr;