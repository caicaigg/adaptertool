#pragma once


#include <WTypes.h>
// #include <basetsd.h>
// #include <wtypesbase.h>

enum DDSTypeEnum
{
	DDSTYPE_SysResetRequest = 0xFF01,	//系统复位 1
	DDSTYPE_SysHaltRequest,				//系统中止 2
	DDSTYPE_SysBitRequest,				//系统自检 3				
	DDSTYPE_ScnDldRequest,				//系统加载 4
	DDSTYPE_SysRdyRequest,				//系统预位 5
	DDSTYPE_SysModeSet,					//模式设置 6
	DDSTYPE_SysCtrlRequest,				//运行控制 7
	DDSTYPE_SysStqRequest,				//状态查询 8
	DDSTYPE_ScnPlatUpdate,				//平台运动更新 9
	DDSTYPE_ScnEventUpdate,				//仿真事件发布 A
	DDSTYPE_SysResetReply,				//系统复位回复
	DDSTYPE_SysHaltNotify,				//系统中止回复
	DDSTYPE_SysBitReply,				//系统自检回复
	DDSTYPE_SysDldNotify,				//系统加载回复
	DDSTYPE_SysRdyNotify,				//系统预位回复
	DDSTYPE_SysModeReply,				//模式设置回复
	DDSTYPE_SysCtrlReply,				//运行控制回复,标校车控制状态回复
	DDSTYPE_SysStqReply,				//状态回复

	DDSTYPE_OwnInsUpdate,				//平台惯导更新
	DDSTYPE_ScnMixUpdate,				//场景融合更新
	DDSTYPE_RadEventReport,				//雷达事件上报
	DDSTYPE_RadPltReport,				//雷达点迹上报
	DDSTYPE_RadTrkReport,				//雷达航迹上报
	DDSTYPE_EwEventReport,				//电子战事件上报
	DDSTYPE_EwSortReport,				//电子战分选上报
	DDSTYPE_EwSpecReport,				//电子战频谱上报
	DDSTYPE_EwPDWReport,				//电子战全脉冲上报 ""
	DDSTYPE_EwTgtLocReport,				//电子战目标定位上报
	DDSTYPE_ReportSysStop,				//急停事件

	DDSTYPE_RadParmNotify				//雷达工作参数上报

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

//DDS 总线数据类型
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
/// <summary>	系统复位.  </summary>
///
/// <remarks>	阮道清, 2020/8/7. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////

class SysReset : public DataTypeBase
{
	DECLARE_DATATYPE(SysReset, DDSTYPE_SysResetRequest);

	UINT32 TargetSubSysID;			//目标子系统ID
	UINT32 EquipmentNum;			//设备数量
	UINT32 EquipmentID[32];			//设备ID
};
typedef boost::shared_ptr<SysReset> SysResetptr;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	系统终止.  </summary>
///
/// <remarks>	阮道清, 2020/8/7. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////
class SysConclude : public DataTypeBase
{
	DECLARE_DATATYPE(SysConclude, DDSTYPE_SysHaltRequest);

};
typedef boost::shared_ptr<SysConclude> SysConcludeptr;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	系统自检.  </summary>
///
/// <remarks>	阮道清, 2020/8/7. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////
class SysSelfCheck : public DataTypeBase
{
	DECLARE_DATATYPE(SysSelfCheck, DDSTYPE_SysBitRequest);
	UINT32 TargetSubSysID;			//目标子系统ID
	UINT32 SelfCheckMode;			//自检方式
	UINT32 EquipmentNum;			//设备数量
	UINT32 EquipmentID[32];			//设备ID
};
typedef boost::shared_ptr<SysSelfCheck> SysSelfCheckptr;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	系统加载.  </summary>
///
/// <remarks>	阮道清, 2020/8/7. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////
class SysLoad : public DataTypeBase
{
	DECLARE_DATATYPE(SysLoad, DDSTYPE_ScnDldRequest);

	UINT32 TargetSubSysID;			//目标子系统ID
	UINT32 ExpTestID;				//试验任务ID
	UINT32 Reserved[4];				//保留
};
typedef boost::shared_ptr<SysLoad> SysLoadptr;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	系统预位.  </summary>
///
/// <remarks>	阮道清, 2020/8/7. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////
class SysPrePosition : public DataTypeBase
{
	DECLARE_DATATYPE(SysPrePosition, DDSTYPE_SysRdyRequest);

	UINT32 TargetSubSysID;			//目标子系统ID
};
typedef boost::shared_ptr<SysPrePosition> SysPrePositionptr;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	模式设置.  </summary>
///
/// <remarks>	阮道清, 2020/8/7. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////
class SysModeSet : public DataTypeBase
{
	DECLARE_DATATYPE(SysModeSet, DDSTYPE_SysModeSet);

	UINT32 SysWorkMode;				//系统工作模式
};
typedef boost::shared_ptr<SysModeSet> SysModeSetptr;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	运行控制.  </summary>
///
/// <remarks>	阮道清, 2020/8/7. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////
class SysRunControl : public DataTypeBase
{
	DECLARE_DATATYPE(SysRunControl, DDSTYPE_SysCtrlRequest);

	UINT32 TargetSubSysID;			//目标子系统ID
	UINT32 CommondID;				//0-开始，1-结束，2-暂停，3-恢复，4-终止
	UINT32 TYear;					//预约执行时间：年；取值范围：2000-2099
	UINT32 TMouth;					//预约执行时间：月；取值范围：1-12
	UINT32 TDay;					//预约执行时间：日；取值范围：1-31
	UINT32 THour;					//预约执行时间：时；取值范围：0-23
	UINT32 TMinute;					//预约执行时间：分；取值范围：0-59
	UINT32 TSecond;					//预约执行时间：秒；取值范围：0-59
	UINT32 ExpTestID;				//试验任务ID
};
typedef boost::shared_ptr<SysRunControl> SysRunControlptr;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	状态查询.  </summary>
///
/// <remarks>	阮道清, 2020/8/7. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////
class SysStateSeek : public DataTypeBase
{
	DECLARE_DATATYPE(SysStateSeek, DDSTYPE_SysStqRequest);

	UINT32 TargetSubSysID;			//目标子系统ID
};
typedef boost::shared_ptr<SysStateSeek> SysStateSeekptr;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	平台运动参数.  </summary>
///
/// <remarks>	阮道清, 2020/8/7. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////
class EntityMotionParam : public DataTypeBase
{
	DECLARE_DATATYPE_NOINIT(EntityMotionParam);

	UINT32 EntityID;				//兵力实体ID
	float  EntityPosLon;			//平台位置，经度  范围：-180~180，单位：度
	float  EntityPosLat;			//平台位置，纬度	 范围：-90~90，单位：度
	float  EntityPosHight;			//平台位置，高度	 范围：-1000~30000，单位：米
	float  EntityPosAzimuth;		//平台姿态，偏航	 范围：-180~180，单位：度
	float  EntityPosPitch;			//平台姿态，俯仰	 范围：-90~90，单位：度
	float  EntityPosRoll;			//平台姿态，横滚	 范围：-180~180，单位：度
	float  EntityVelEast;			//平台速度，东向	 范围：-2000~2000，单位：m/s
	float  EntityVelNorth;			//平台速度，北向	 范围：-2000~2000，单位：m/s
	float  EntityVelUnder;			//平台速度，天向	 范围：-1000~1000，单位：m/s
	float  EntityAccEast;			//平台加速度，东向	单位：m/s^2
	float  EntityAccNorth;			//平台加速度，北向	单位：m/s^2
	float  EntityAccUnder;			//平台加速度，天向	单位：m/s^2
	float  EntityAngVelAzimuth;		//平台角速度，偏航	单位：deg/s
	float  EntityAngVelPitch;		//平台角速度，俯仰	单位：deg/s
	float  EntityAngVelRoll;		//平台角速度，横滚	单位：deg/s
};
typedef boost::shared_ptr<EntityMotionParam> EntityMotionParamptr;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	平台运动更新.  </summary>
///
/// <remarks>	阮道清, 2020/8/7. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////
class SysMotionUpdate : public DataTypeBase
{
	DECLARE_DATATYPE(SysMotionUpdate, DDSTYPE_ScnPlatUpdate);

	UINT32 SIMStepOrder;						//场景节拍序号，场景仿真帧计数，当前以10ms作为固定的仿真节拍周期
	UINT32 ForceEntityNum;						//兵力实体数量
	EntityMotionParam  EntityMotionInfo[32];	//平台运动参数
};
typedef boost::shared_ptr<SysMotionUpdate> SysMotionUpdateptr;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	仿真事件参数基类（同时适用于事件编码为关机或开机时，即事件编码为：0-关机和1-开机时）.  </summary>
///
/// <remarks>	阮道清, 2020/8/7. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////
class SimEventParamBase : public DataTypeBase
{
	DECLARE_DATATYPE_NOINIT(SimEventParamBase);
};
typedef boost::shared_ptr<SimEventParamBase> SimEventParamBaseptr;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	仿真事件参数-工作模式切换时（事件编码为：2-工作模式切换时）.  </summary>
///
/// <remarks>	阮道清, 2020/8/7. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////
class SimEventParam2 : public SimEventParamBase
{
	DECLARE_DATATYPE_NOINIT(SimEventParam2);

	UINT32 WorkModeID;						//目的模式ID,参考装备参数模型文件中对应ID所描述的工作模式参数
};
typedef boost::shared_ptr<SimEventParam2> SimEventParam2ptr;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	仿真事件参数-驻留波位切换时（事件编码为：101-驻留波位切换（雷达专用）时）.  </summary>
///
/// <remarks>	阮道清, 2020/8/7. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////
class SimEventParam101 : public SimEventParamBase
{
	DECLARE_DATATYPE_NOINIT(SimEventParam101);

	UINT32 TargetWaveNumb;						//目的波位序号
	UINT32 SignalWavetotal;						//信号波形数量
	UINT32 SignalWaveID1;						//信号波形ID1：引用装备参数模型文件中对应ID所描述的信号波形参数
	UINT32 SignalWaveID2;						//信号波形ID2：引用装备参数模型文件中对应ID所描述的信号波形参数
	UINT32 SignalWaveID3;						//信号波形ID3：引用装备参数模型文件中对应ID所描述的信号波形参数
	UINT32 SignalWaveID4;						//信号波形ID4：引用装备参数模型文件中对应ID所描述的信号波形参数	
};
typedef boost::shared_ptr<SimEventParam101> SimEventParam101ptr;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	仿真事件参数-信号波形切换时（事件编码为：102-信号波形切换时（雷达专用）时）.  </summary>
///
/// <remarks>	阮道清, 2020/8/7. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////
class SimEventParam102 : public SimEventParamBase
{
	DECLARE_DATATYPE_NOINIT(SimEventParam102);

	UINT32 TargetSignalWaveID;						//目的信号波形ID
};
typedef boost::shared_ptr<SimEventParam102> SimEventParam102ptr;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	仿真事件参数-跟踪目标切换时（事件编码为：103-跟踪目标切换时（雷达专用）时）.  </summary>
///
/// <remarks>	阮道清, 2020/8/7. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////
class SimEventParam103 : public SimEventParamBase
{
	DECLARE_DATATYPE_NOINIT(SimEventParam103);

	UINT32 TrackTargetNum;						//跟踪目标数量
	UINT32 TargetID[32];							//目标实体ID
};
typedef boost::shared_ptr<SimEventParam103> SimEventParam103ptr;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	仿真事件参数-波束赋形切换时（事件编码为：104-波束赋形切换时（雷达专用）时）.  </summary>
///
/// <remarks>	阮道清, 2020/8/7. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////
class SimEventParam104 : public SimEventParamBase
{
	DECLARE_DATATYPE_NOINIT(SimEventParam104);

	DOUBLE BeamDiagramFrqPoint;						//波束方向图频点，范围：0~100000，单位：MHz
	DOUBLE BeamDiagramStep;						//波束方向图步进，范围：0~10，单位：度
	DOUBLE BeamDiagramType;						//波束方向图类型，范围：0~1
	UINT32 BeamDiagramNum;						//波束方向图点数
												//float  BeamDiagram[？？];					//方向图数组，范围：-200~200，单位：dB
	std::vector<float> BeamDiagramVar;
};
typedef boost::shared_ptr<SimEventParam104> SimEventParam104ptr;


////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	仿真事件参数-导弹发射时（事件编码为：201-导弹发射时（导弹专用）时）.  </summary>
///
/// <remarks>	阮道清, 2020/8/7. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////
class MissileSend201 : public SimEventParamBase
{
	DECLARE_DATATYPE_NOINIT(MissileSend201);

	UINT32 MissileBSEID;						//导弹搭载平台ID
	UINT32 MissileTargetID;						//导弹攻击目标ID
	UINT32 MissileID;							//导弹对象ID，武器唯一标识，场景规划时动态分配
};
typedef boost::shared_ptr<MissileSend201> MissileSend201ptr;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	仿真事件参数-导弹爆炸时（事件编码为：202-导弹爆炸时（导弹专用）时）.  </summary>
///
/// <remarks>	阮道清, 2020/8/7. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////
class MissileBomb202 : public SimEventParamBase
{
	DECLARE_DATATYPE_NOINIT(MissileBomb202);

	UINT32 MissileHitSign;						//导弹命中标识，0-未命中目标，1-命中目标
};
typedef boost::shared_ptr<MissileBomb202> MissileBomb202ptr;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	仿真事件参数-攻击目标切换时（事件编码为：203-攻击目标切换时（导弹专用）时）.  </summary>
///
/// <remarks>	阮道清, 2020/8/7. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////
class ShiftTarget203 : public SimEventParamBase
{
	DECLARE_DATATYPE_NOINIT(ShiftTarget203);

	UINT32 MissileTargetID;						//导弹攻击目标ID
};
typedef boost::shared_ptr<ShiftTarget203> ShiftTarget203ptr;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	仿真事件参数-制导模式切换时（事件编码为：204-制导模式切换时（导弹专用）时）.  </summary>
///
/// <remarks>	阮道清, 2020/8/7. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////
class ShiftGuide204 : public SimEventParamBase
{
	DECLARE_DATATYPE_NOINIT(ShiftGuide204);

	UINT32 TargetGuideID;						//目的制导模式ID
};
typedef boost::shared_ptr<ShiftGuide204> ShiftGuide204ptr;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	仿真事件描述.  </summary>
///
/// <remarks>	阮道清, 2020/8/7. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////
class SimEventDescribe : public DataTypeBase
{
	DECLARE_DATATYPE_NOINIT(SimEventDescribe);

	UINT32 EntityID;							//兵力实体ID
	UINT32 EquipmentID;							//装备对象ID
	UINT32 TimeDt;								//时间偏移，取值范围：0~10000，单位：us
	UINT32 EventCodeID;							//事件编码，0-关机，1-开机，2-工作模式切换， \
																								101-驻留波位切换（雷达专用），102-信号波形切换（雷达专用），103-跟踪目标切换（雷达专用），\
												  104-波束赋形切换（雷达专用），201-导弹发射（导弹专用），202-导弹爆炸（导弹专用），\
												  203-攻击目标切换（导弹专用），204-制导模式切换（导弹专用），其余预留
	SimEventParamBase SIMEventInfo[32];			//仿真事件参数
};
typedef boost::shared_ptr<SimEventDescribe> SimEventDescribeptr;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	仿真事件发布.  </summary>
///
/// <remarks>	阮道清, 2020/8/7. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////
class SysEventPub : public DataTypeBase
{
	DECLARE_DATATYPE(SysEventPub, DDSTYPE_ScnEventUpdate);

	UINT32 SIMStepOrder;						//场景仿真节拍序号,场景仿真帧计数，当前以10ms作为固定的仿真节拍周期
	UINT32 SIMEventNum;							//仿真事件数量
	SimEventDescribe SimEventInfo[32];			//仿真事件描述
};
typedef boost::shared_ptr<SysEventPub> SysEventPubptr;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	平台惯导更新.  </summary>
///
/// <remarks>	阮道清, 2020/8/7. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////
class UpdateNavigationInfo : public DataTypeBase
{
	DECLARE_DATATYPE(UpdateNavigationInfo, DDSTYPE_OwnInsUpdate);

	UINT32 SIMStepOrder;								//场景仿真节拍序号,场景仿真帧计数，乘10ms节拍表示仿真时间
	DOUBLE  NavigationLon;								//经度,范围：-180~180，单位：度
	DOUBLE  NavigationLat;								//纬度,范围：-90~90，单位：度
	DOUBLE  NavigationHight;							//气压高度,范围：0~9999，单位：米
	DOUBLE  RadioAltitude;								//无线电高度,范围：0~9999，单位：米
	DOUBLE  NavigationRoll;								//横滚角,范围：-180~180，单位：度
	DOUBLE  NavigationPitch;							//俯仰角,范围：-90~90，单位：度
	DOUBLE  NavigationTrueAzimuth;						//真航向,范围：-180~180，单位：度
	DOUBLE  NavigationElecAzimuth;						//磁航向,范围：-180~180，单位：度
	DOUBLE  NavigationVelEast;							//东向速度，范围：-9999~9999，单位：m/s
	DOUBLE  NavigationVelNorth;							//北向速度，范围：-9999~9999，单位：m/s
	DOUBLE  NavigationVelUnder;							//天向速度，范围：-9999~9999，单位：m/s
	DOUBLE  VacuumVelcity;								//真空速，范围：0~9999，单位：m/s
	DOUBLE  EarthVelcity;								//地速，范围：0~9999，单位：m/s
};
typedef boost::shared_ptr<UpdateNavigationInfo> UpdateNavigationInfoptr;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	场景融合更新.  </summary>
///
/// <remarks>	阮道清, 2020/8/7. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////
class UpdateScenarioData : public DataTypeBase
{
	DECLARE_DATATYPE(UpdateScenarioData, DDSTYPE_ScnMixUpdate);

};
typedef boost::shared_ptr<UpdateScenarioData> UpdateScenarioDataptr;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	雷达事件上报.  </summary>
///
/// <remarks>	阮道清, 2020/8/7. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////
class ReportRadarEvent : public DataTypeBase
{
	DECLARE_DATATYPE(ReportRadarEvent, DDSTYPE_RadEventReport);

};
typedef boost::shared_ptr<ReportRadarEvent> ReportRadarEventptr;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	雷达点迹上报.  </summary>
///
/// <remarks>	阮道清, 2020/8/7. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////
class ReportRadarTrace : public DataTypeBase
{
	DECLARE_DATATYPE(ReportRadarTrace, DDSTYPE_RadPltReport);

};
typedef boost::shared_ptr<ReportRadarTrace> ReportRadarTraceptr;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	雷达航迹上报.  </summary>
///
/// <remarks>	阮道清, 2020/8/7. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////
class ReportRadarTrack : public DataTypeBase
{
	DECLARE_DATATYPE(ReportRadarTrack, DDSTYPE_RadTrkReport);
};
typedef boost::shared_ptr<ReportRadarTrack> ReportRadarTrackptr;



////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	系统急停上报.  </summary>
///
/// <remarks>	阮道清, 2020/8/7. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////
class ReportSysStop : public DataTypeBase
{
	DECLARE_DATATYPE_NOINIT(ReportSysStop);

	UINT32 SubSysID;				//子系统ID
	CHAR StopDetail[512];			//急停情况描述
};
typedef boost::shared_ptr<ReportRadarTrace> ReportRadarTraceptr;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	辐射源上报信息详情.  </summary>
///
/// <remarks>	阮道清, 2020/8/7. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////
class RadiationSocDetail : public DataTypeBase
{
	DECLARE_DATATYPE_NOINIT(RadiationSocDetail);

	UINT32 BSEID;					//平台ID
	UINT32 EquipID;					//辐射源ID
	UINT32 BSEIdentification;		//平台敌我属性，0-未定义，1-我方，2-敌方，3-友方，4-中立，5以后预留；
	UINT32 BSEType;					//平台类型，0-未知，1-地面固定，2-地面移动，3-水面，4-水下，5-导弹，6-固定翼，\
																											//7-旋转翼，8-无人机，9-卫星，10-升空平台，12-便携，13以后预留
	UINT32 EquipType;				//辐射源类型，0-未知，1-警戒雷达，2-对空警戒雷达，3-对海警戒雷达，4-低空警戒雷达，\
																											//5-引导雷达，6-目标指示雷达，7-测高雷达，8-预警雷达，9-导弹预警雷达，10-武器控制雷达，\
									//11-炮瞄雷达，12-导弹制导雷达，13-导弹攻击雷达，14-鱼雷攻击雷达，15-多功能雷达，16-导弹末制导雷达，\
									//17-轰炸瞄准雷达，18-侦察雷达，19-战场侦察雷达，20-炮位侦察校射雷达，21-活动目标侦察校射雷达，\
									//22-航空管制雷达，23-导航雷达，24-地形跟随雷达，25-着陆引导雷达，26-港口监视雷达，27-测量雷达，\
									//28-气象雷达，29-敌我识别器，30-机载雷达，31-成像雷达
	float  BSEPosLon;				//平台位置，经度 ：大地坐标系，东正西负 范围：-180~180，单位：度
	float  BSEPosLat;				//平台位置，纬度	：大地坐标系，北正南负 范围：-90~90，单位：度
	float  BSEPosHight;				//平台位置，高度：大地坐标系，上正下负，海拔高度	 范围：-1000~30000，单位：米
	float  BSEAzimuth;				//平台方位：载机机体坐标系，目标相对方位 范围：-180~180，单位：度
	float  BSEPitch;				//平台俯仰：载机机体坐标系，目标相对俯仰	 范围：-90~90，单位：度
	float  BSEDistance;				//平台斜距	 范围：0~999999，单位：米
	float  BSERadialVel;			//平台径向速度，正为接近，负为远离，单位：m/s
	float  BSETangentialVel;		//平台切向速度，正为逆时针，负为顺时针，单位：m/s
	UINT32 RadiSocWorkMode;			//辐射源工作模式，0-未知，1-搜索，2-跟踪，3-制导，4-TWS，5-TAS，6以后预留
	UINT32 RadiSocPolarMode;		//辐射源极化方式,0-未知，1-左圆极化，2-右圆极化，3-垂直极化，4-水平极化，5-斜极化，6-极化可选择，7-极化编码，\
																											//8-极化捷变，9-左旋椭圆极化，10-右旋椭圆极化，11以后预留

	UINT32 SignalModulation;		//信号调制方式，0-不明，1-常规，2-非线性调频，3-线性调频，4-二相编码，5-四相编码，6-频率编码，7-频率分集，8以后预留
	float  ScanPeriod;				//扫描周期,单位：ms
	float  waveStateTime;			//波位驻留时间,单位：ms
	float  CoherentInterval;		//相干处理间隔,单位：ms
	UINT32 SigFreqType;				//信号频率类型,0-不明，1-固定，2-组变，3-分集，4-原编码，5-捷变，6-射频参差，7-连续波频率调制，8-连续波编码调制，\
																											//9-连续波噪声调制， 10-脉内频率编码（去掉），11以后预留
	UINT32 SigFreqCount;			//信号频点数,取值范围：1~64
	float  MidFrequence;			//信号频率中值,取值范围：30~40000,单位：MHz
	float  RangeFrequence;			//信号频率范围,取值范围：30~40000,单位：MHz
	UINT32 FreqList;				//频点列表,取值范围：1~64,64个频点(频点不足时也按此算)不考虑频率抖动带来的影响
	UINT32 PRIType;					//信号PRI类型,0-不明，1-固定，2-以后保留，3-抖动，4-以后保留，5-参差，6-以后保留，7-滑变，8-以后保留，9以后预留
	UINT32 PRITotal;				//信号PRI点数,取值范围：1~64,不考虑PRI抖动新增的点数
	float  PRIMiddle;				//信号PRI中值,单位：us;取值范围：1~99999
	float  PRIRange;				//信号PRI范围,单位：us;反应抖动、不固定PRI的影响
	UINT32 PRIList;					//信号PRI列表,取值范围：1~64,64个PRI(PRI不足时也按此算)不考虑PRI抖动带来的影响
	UINT32 PWType;					//信号PW类型，0-不明，1-固定，2-跳变，3以后预留
	float  PWMiddle;				//信号PW中值,单位：us;取值范围：1~99999
	float  PWRange;					//信号PW范围,单位：us;取值范围：1~99999
	UINT32 PWList;					//信号PRI列表,取值范围：1~64,64个PW(PW不足时也按此算)不考虑PW抖动带来的影响
};
typedef boost::shared_ptr<RadiationSocDetail> RadiationSocDetailptr;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	场景辐射源融合上报.  </summary>
///
/// <remarks>	阮道清, 2020/8/7. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////
class ReportFusion : public DataTypeBase
{
	DECLARE_DATATYPE_NOINIT(ReportFusion);

	UINT32 SimTYear;							//场景仿真时间：年；取值范围：2000-2099
	UINT32 SimTMouth;							//场景仿真时间：月；取值范围：1-12
	UINT32 SimTDay;								//场景仿真时间：日；取值范围：1-31
	UINT32 SimTHour;							//场景仿真时间：时；取值范围：0-23
	UINT32 SimTMinute;							//场景仿真时间：分；取值范围：0-59
	UINT32 SimTSecond;							//场景仿真时间：秒；取值范围：0-59
	UINT32 SimTMicSecond;						//场景仿真时间：毫秒；取值范围：1~999
	UINT32 RadsourceTotal;						//辐射源数量，取值范围：1~2000
	RadiationSocDetail RadSourDetial[2000];		//辐射源信息详情
};
typedef boost::shared_ptr<ReportFusion> ReportFusionptr;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	自检回复内容格式定义.  </summary>
///
/// <remarks>	阮道清, 2020/8/7. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////
class SCRespondDetial : public DataTypeBase
{
	DECLARE_DATATYPE_NOINIT(SCRespondDetial);

	UINT32 EquiID;							//设备Id；
	UINT32 EquiSelfCheckResult;				//设备自检结果；0-成功，1-失败，3以后预留；
	char   ResultParam[256];				//设备自检结果参数块；根据子系统提供的设备自检结果xml进行格式化解析建议改为子系统上报解析后的参数值字符串，用[,]分隔
};
typedef boost::shared_ptr<SCRespondDetial> SCRespondDetialptr;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	自检回复.  </summary>
///
/// <remarks>	阮道清, 2020/8/7. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////
class SelfCheckReply : public DataTypeBase
{
	DECLARE_DATATYPE_NOINIT(SelfCheckReply);

	UINT32							SubSysID;						//设备子系统Id；
	UINT32							SubSelfCheckResult;				//子系统自检结果，0-成功，1-失败，3以后预留； 
	UINT32							SubSelfCheckTotal;				//设备自检结果数量N，要求子系统上报管理设备/仪器的自检结果，在后面附上设备自检结果参数块 \
																																																			//为确保传输效率，每包最多32个设备，如果超出则另起一包
	std::vector<SCRespondDetial>	SubSysDetial;					//子系统详情
};
typedef boost::shared_ptr<SelfCheckReply> SelfCheckReplyptr;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	加载回复.  </summary>
///
/// <remarks>	阮道清, 2020/8/7. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////
class LoadRespond : public DataTypeBase
{
	DECLARE_DATATYPE_NOINIT(LoadRespond);

	UINT32	TargetSysID;						//目标子系统Id；
	UINT32	TargetSelfExcResult;				//执行结果，0-成功，1-失败，2以后预留
	char	ErrorDetil[256];					//如果子系统执行结果返回失败，则同时返回错误描述字符串
};
typedef boost::shared_ptr<LoadRespond> LoadRespondptr;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	预位上报详情.  </summary>
///
/// <remarks>	阮道清, 2020/8/7. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////
class PrePosReportDetial : public DataTypeBase
{
	DECLARE_DATATYPE_NOINIT(PrePosReportDetial);

	UINT32	EquipID;								//设备Id；
	UINT32	EquipPrePosResult;						//设备预位结果；0-成功，1-失败，3以后预留；
	char	EquipPrePosDetial[256];					//设备预位错误描述；

};
typedef boost::shared_ptr<PrePosReportDetial> PrePosReportDetialptr;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	预位上报.  </summary>
///
/// <remarks>	阮道清, 2020/8/7. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////
class PrePosReport : public DataTypeBase
{
	DECLARE_DATATYPE_NOINIT(PrePosReport);

	UINT32	SubSysID;											//子系统Id；
	UINT32	SubSysPrePosResult;									//子系统预位结果；0-成功，1-失败，3以后预留；
	UINT32	EquipPrePosTotal;									//设备预位结果数量:要求子系统上报管理设备/仪器的预位结果，在后面附上设备预位结果参数块\
																																																//为确保传输效率，每包最多32个设备，如果超出则另起一包
	std::vector<PrePosReportDetial> EquipPrePos;				//如果子系统执行结果返回失败，则同时返回错误描述字符串
};
typedef boost::shared_ptr<PrePosReport> PrePosReportptr;


////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	状态回复详情.  </summary>
///
/// <remarks>	阮道清, 2020/8/7. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////
class ResponseStateDetial : public DataTypeBase
{
	DECLARE_DATATYPE_NOINIT(ResponseStateDetial);

	UINT32	EquipID;								//设备Id；
	char	EquipStateCheck[256];					//设备状态查询参数块，根据子系统提供的设备状态查询xml进行格式化解析建议改为子系统上报解析后的参数值字符串，用[,]分隔
};
typedef boost::shared_ptr<ResponseStateDetial> ResponseStateDetialptr;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	状态回复.  </summary>
///
/// <remarks>	阮道清, 2020/8/7. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////
class ResponseState : public DataTypeBase
{
	DECLARE_DATATYPE_NOINIT(ResponseState);

	UINT32	SubSysID;											//子系统Id；
	UINT32	SubSysStateCheck;									//子系统状态查询结果；0-正常，1-异常，2以后预留；
	UINT32	EquipPrePosTotal;									//设备预位结果数量:要求子系统上报管理设备/仪器的预位结果，在后面附上设备预位结果参数块\
																																	//为确保传输效率，每包最多32个设备，如果超出则另起一包
	std::vector<ResponseStateDetial> EquipStateCheck;			//如果子系查询结果
};
typedef boost::shared_ptr<ResponseState> ResponseStateptr;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	辐射闭环自检--频谱上报.  </summary>
///
/// <remarks>	阮道清, 2020/8/7. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////
class RadSelfCheck : public DataTypeBase
{
	DECLARE_DATATYPE_NOINIT(RadSelfCheck);

	UINT32	SubSysID;											//子系统Id；
	UINT32	SignMark;											//信号标记；0-未检到信号，1-检到信号；
	DOUBLE  SignFreq;	 										//信号频率，信号监测软件检到的辐射信号频率
	DOUBLE  SignPower;	 										//信号功率，信号监测软件检到的辐射信号功率
	UINT32  FreqTotal;	 										//频谱点数，1~1024
	std::vector<DOUBLE> FreqRange;								//频点幅度，范围：-80~20，单位：dBm
};
typedef boost::shared_ptr<RadSelfCheck> RadSelfCheckptr;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	设备控制指令上报详情.  </summary>
///
/// <remarks>	阮道清, 2020/8/7. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////
class EquipCommandDetial : public DataTypeBase
{
	DECLARE_DATATYPE_NOINIT(EquipCommandDetial);

	char    ParamName[32];								//参数名称；
	DOUBLE  ParamValue;									//参数值；
	char	ParamUnit[32];								//参数单位；
};
typedef boost::shared_ptr<EquipCommandDetial> EquipCommandDetialptr;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	设备控制指令上报.  </summary>
///
/// <remarks>	阮道清, 2020/8/7. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////
class EquipCommand : public DataTypeBase
{
	DECLARE_DATATYPE_NOINIT(EquipCommand);

	UINT32	SubSysID;											//子系统Id；
	UINT32	EquipID;											//设备Id；
	CHAR    CommandName[64];									//指令名称；
	UINT32	ParamTotal;											//参数数量:有上报子系统自行选择重点参数上报;为确保传输效率，每包最多32个设备，如果超出则另起一包
	std::vector<EquipCommandDetial> ParamDetial;				//上报详情
};
typedef boost::shared_ptr<EquipCommand> EquipCommandptr;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	点迹上报.  </summary>
///
/// <remarks>	阮道清, 2020/8/7. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////
class ReportTrace : public DataTypeBase
{
	DECLARE_DATATYPE_NOINIT(ReportTrace);

	UINT32	RadarID;											//雷达Id；
	UINT32	TraceID;											//点迹Id；
	UINT32  TraceTYear;											//点迹时间：年；取值范围：2000-2099
	UINT32  TraceTMouth;										//点迹时间：月；取值范围：1-12
	UINT32  TraceTDay;											//点迹时间：日；取值范围：1-31
	UINT32  TraceTHour;											//点迹时间：时；取值范围：0-23
	UINT32  TraceTMinute;										//点迹时间：分；取值范围：0-59
	UINT32  TraceTSecond;										//点迹时间：秒；取值范围：0-59
	UINT32  TraceTMicSecond;									//点迹时间：毫秒；取值范围：1~999
	DOUBLE	TraceDistance;										//点迹距离
	DOUBLE	TraceDoppler;										//点迹多普勒
	UINT32	HorizBeamNum;										//水平波束号
	UINT32	VertiBeamNum;										//垂直波束号
	UINT32	ChannelNum;											//频道数
	UINT32	ChannelMark;										//频道标识
	UINT32	PulseMark;											//脉组标识
	UINT32	EPNum;												//EP数
	DOUBLE	StartDistance;										//起始距离
	DOUBLE	EndDistance;										//结束距离
	DOUBLE	StartDirection;										//起始方位
	DOUBLE	EndDirection;										//结束方位
	DOUBLE	StartAD;											//起始AD
	DOUBLE	EndAD;												//结束AD
	DOUBLE	StartDistanceRange;									//起始距离幅度	
	DOUBLE	EndDistanceRange;									//结束距离幅度
	DOUBLE	StartDirectionRange;								//起始方位幅度	
	DOUBLE	EndDirectionRange;									//结束方位幅度
	DOUBLE	BeamRange;											//波束幅度
	DOUBLE	SectionLevel;										//扇区等级
	UINT32  TraceQuality;										//点迹质量
	UINT32  TraceMark;											//点迹标志
};
typedef boost::shared_ptr<ReportTrace> ReportTraceptr;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	航迹上报.  </summary>
///
/// <remarks>	阮道清, 2020/8/7. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////
class ReportTrack : public DataTypeBase
{
	DECLARE_DATATYPE_NOINIT(ReportTrack);

	UINT32	RadarID;											//雷达Id；
	UINT32	TrackID;											//航迹Id；
	UINT32  TrackTYear;											//航迹时间：年；取值范围：2000-2099
	UINT32  TrackTMouth;										//航迹时间：月；取值范围：1-12
	UINT32  TrackTDay;											//航迹时间：日；取值范围：1-31
	UINT32  TrackTHour;											//航迹时间：时；取值范围：0-23
	UINT32  TrackTMinute;										//航迹时间：分；取值范围：0-59
	UINT32  TrackTSecond;										//航迹时间：秒；取值范围：0-59
	UINT32  TrackTMicSecond;									//航迹时间：毫秒；取值范围：1~999
	DOUBLE	CalDistance;										//预测距离
	DOUBLE	CalDirection;										//预测方位
	UINT32	IFFCode;											//IFF代码	
	DOUBLE	ObserveDistance;									//观测距离
	DOUBLE	ObserveDirection;									//观测方位
	UINT32  TrackQuality;										//航迹质量
	UINT32  ATCRBSModeI;										//二次雷达模式1应答
	UINT32  ATCRBSModeII;										//二次雷达模式2应答
	UINT32  ATCRBSModeIII;										//二次雷达模式3/A应答
	DOUBLE  ATCRBSHight;										//二次雷达高度
};
typedef boost::shared_ptr<ReportTrack> ReportTrackptr;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	雷达参数上报.  </summary>
///
/// <remarks>	阮道清, 2020/8/7. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////
class ReportRadarParam : public DataTypeBase
{
	DECLARE_DATATYPE_NOINIT(ReportRadarParam);

	UINT32	RadarID;											//雷达Id；
	UINT32	TrackID;											//航迹Id；
	UINT32  TraceTYear;											//点迹时间：年；取值范围：2000-2099
	UINT32  TraceTMouth;										//点迹时间：月；取值范围：1-12
	UINT32  TraceTDay;											//点迹时间：日；取值范围：1-31
	UINT32  TraceTHour;											//点迹时间：时；取值范围：0-23
	UINT32  TraceTMinute;										//点迹时间：分；取值范围：0-59
	UINT32  TraceTSecond;										//点迹时间：秒；取值范围：0-59
	UINT32  TraceTMicSecond;									//点迹时间：毫秒；取值范围：1~999
	UINT32	WorkModeID;											//工作模式Id	:对应雷达模型设置中工作模式Id,范围：0~255
	INT32   FreqCode;											//频率码
	INT32   CynPlus;											//同步脉冲
	DOUBLE  SNR;												//干信比
};
typedef boost::shared_ptr<ReportRadarParam> ReportRadarParamptr;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	分选上报.  </summary>
///
/// <remarks>	阮道清, 2020/8/7. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////
class ReportSorting : public DataTypeBase
{
	DECLARE_DATATYPE_NOINIT(ReportSorting);

	UINT32	IndexSUT;							//SUT索引,SUT在场景中的索引，用于多载机场景；
	UINT32  TraceTYear;							//点迹时间：年；取值范围：2000-2099
	UINT32  TraceTMouth;						//点迹时间：月；取值范围：1-12
	UINT32  TraceTDay;							//点迹时间：日；取值范围：1-31
	UINT32  TraceTHour;							//点迹时间：时；取值范围：0-23
	UINT32  TraceTMinute;						//点迹时间：分；取值范围：0-59
	UINT32  TraceTSecond;						//点迹时间：秒；取值范围：0-59
	UINT32  TraceTMicSecond;					//点迹时间：毫秒；取值范围：1~999
	UINT32	TargetBatchNum;						//目标批号
	UINT32	TargetIdentification;				//目标敌我属性
	UINT32	TargetType;							//目标平台类型
	UINT32	TargetLevel;						//目标威胁等级
	UINT32	RadType;							//辐射源类型:0-未知，1-警戒雷达，2-对空警戒雷达，3-对海警戒雷达，4-低空警戒雷达，5-引导雷达，\
																																				//6-目标指示雷达，7-测高雷达，8-预警雷达，9-导弹预警雷达，10-武器控制雷达，11-炮瞄雷达，\
												//12-导弹制导雷达，13-导弹攻击雷达，14-鱼雷攻击雷达，15-多功能雷达，16-导弹末制导雷达，\
												// 17-轰炸瞄准雷达，18-侦察雷达，19-战场侦察雷达，20-炮位侦察校射雷达，21-活动目标侦察校射雷达，\
												// 22-航空管制雷达，23-导航雷达，24-地形跟随雷达，25-着陆引导雷达，26-港口监视雷达，27-测量雷达，\
												// 28-气象雷达，29-敌我识别器，30-机载雷达，31-成像雷达
	DOUBLE  TargetPosLon;						//目标位置，经度  范围：-180~180，单位：度
	DOUBLE  TargetPosLat;						//目标位置，纬度	 范围：-90~90，单位：度
	DOUBLE  TargetPosHight;						//目标位置，高度	 范围：-1000~30000，单位：米
	DOUBLE  TargetPosAzimuth;					//目标方位	 范围：-180~180，单位：度
	DOUBLE  TargetPosPitch;						//目标俯仰	 范围：-90~90，单位：度
	DOUBLE  TargAzimuthVari;					//目标方位方差	
	DOUBLE  TargPitchVari;						//目标俯仰方差	
	DOUBLE	TargetDistance;						//目标斜距	 范围：0~999999，单位：米
	DOUBLE	TargDisVari;						//目标斜距方差	 
	DOUBLE	TargetRadialVel;					//目标径向速度，正为接近，负为远离，单位：m/s
	DOUBLE	TargetTangentialVel;				//目标切向速度，正为逆时针，负为顺时针，单位：m/s
	DOUBLE	TargetRadiRangCode;					//辐射源辐射幅度码
	DOUBLE	RadiSocWorkMode;					//辐射源工作模式，0-未知，1-搜索，2-跟踪，3-制导，4-TWS，5-TAS，6以后预留
	DOUBLE	RadiSocPolarMode;					//辐射源极化方式,0-未知，1-左圆极化，2-右圆极化，3-垂直极化，4-水平极化，5-斜极化，\
																																				//6-极化可选择，7-极化编码，8-极化捷变，9-左旋椭圆极化，10-右旋椭圆极化，11以后预留
	DOUBLE	SignalModulation;					//信号调制方式，0-不明，1-常规，2-非线性调频，3-线性调频，4-二相编码，5-四相编码，6-频率编码，7-频率分集，8以后预留
	DOUBLE	ScanPeriod;							//扫描周期,单位：ms
	DOUBLE	waveStateTime;						//波位驻留时间,单位：ms
	DOUBLE	CoherentInterval;					//相干处理间隔,单位：ms
	UINT32	SigActState;						//信号活动状态
	UINT32	SigJamMark;							//信号干扰标记
	UINT32	SigFreqType;						//信号频率类型,0-不明，1-固定，2-组变，3-分集，4-原编码，5-捷变，6-射频参差，7-连续波频率调制，\
																																				//8-连续波编码调制，9-连续波噪声调制， 10-脉内频率编码（去掉），11以后预留
	UINT32	SigFreqCount;						//信号频点数,取值范围：1~64
	DOUBLE	MidFrequence;						//信号频率中值,取值范围：30~40000,单位：MHz
	DOUBLE	RangeFrequence;						//信号频率范围,取值范围：30~40000,单位：MHz
	UINT32	SigPRIType;							//信号PRI类型,0-不明，1-固定，2-跳变，3-抖动，4-捷变，5-参差，6-编码，7-滑变，8-连续波，9以后预留
	UINT32	SigPRITotal;						//信号PRI点数
	DOUBLE	SigPRIMiddle;						//信号PRI中值,单位：us;取值范围：1~99999
	DOUBLE	SigPRIRange;						//信号PRI范围,单位：us;反应抖动、不固定PRI的影响
	UINT32	PWType;								//信号PW类型，0-不明，1-固定，2-跳变，3以后预留
	UINT32	PWMiddle;							//信号PW中值,单位：us;取值范围：1~99999
	DOUBLE	PWRange;							//信号PW范围,单位：us;取值范围：1~99999
	DOUBLE	PWList;								//信号PRI列表,取值范围：1~64,64个PW(PW不足时也按此算)不考虑PW抖动带来的影响
};
typedef boost::shared_ptr<ReportSorting> ReportSortingptr;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	ECM频谱上报.  </summary>
///
/// <remarks>	阮道清, 2020/8/7. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////
class ReportECW : public DataTypeBase
{
	DECLARE_DATATYPE_NOINIT(ReportECW);

	UINT32				 SubSysID;				//子系统Id；
	UINT32				 FreqTotal;				//频谱点数,范围：1~1024；
	std::vector<DOUBLE>  Range;					//频点幅度；

};
typedef boost::shared_ptr<ReportECW> ReportECWptr;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	SUT事件.  </summary>
///
/// <remarks>	阮道清, 2020/8/7. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////
class EventSUT : public DataTypeBase
{
	DECLARE_DATATYPE_NOINIT(EventSUT);

};
typedef boost::shared_ptr<EventSUT> EventSUTptr;