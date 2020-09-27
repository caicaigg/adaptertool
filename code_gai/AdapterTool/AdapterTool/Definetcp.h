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
// file:	报文传输格式定义
//
// summary:	阮道清
////////////////////////////////////////////////////////////////////////////////////////////////////

struct  SMessageFormat
{
	/// <summary> 代码开始标志，固定填写0x7e7e</summary>
	unsigned short _CodeStartSign;

	/// <summary> 数据长度，总长度含包头包尾，最大值为8192个字节</summary>
	unsigned short _DataLenth;

	/// <summary> 源地址，源地址为0或0xffff表示无意义</summary>
	unsigned short _SourceAddress;

	/// <summary> 目的地址，目的地址为0和0xffff表示无意义</summary>
	unsigned short _TargetAddress;

	/// <summary> 命令号，命令下发时顺序下发的流水号，当该数据属于主动上报时，命令号为0</summary>
	unsigned short _CommandNum;

	/// <summary> 命令码，0x01～0x7f为雷达接口代理软件下发给雷达与标校车的数据，0x81~0xff为雷达与标校车上报给雷达接口代理软件的数据</summary>
	unsigned short _CommandCode;

	/// <summary> 版本号，本课题版本号固定为1</summary>
	unsigned short _Version;

	/// <summary> 属性，本课题该字段固定为0</summary>
	unsigned char _Property;

	/// <summary> 报文序号，取值范围0～255，初始值为0，每次发送新报文顺序加1，超过255立即重新从1而非0开始编号；\
		/// 		  某报文上次发送失败后重发时，其报文序号不变；当接收方收到报文序号为0的报文时必须无条件接受该报文，\
	/// 		  若不为0则需要与上次报文的报文序号相比较，如果相同则认为该报文重复，将之舍弃，如果不同则作为新报文接受</summary>
	unsigned char _MessageOrder;

	/// <summary> 总包数，要分开传输的报文的个数，总分包数不大于65535。本字段只在“属性”接口项的D3=1的即已分包的通信数据格式中有效</summary>
	unsigned short _TotalNumOfMessage;

	/// <summary> 当前包号，本包数据的编号，从1开始顺序编号，最大为总包数。</summary>
	unsigned short _CurrentSerialNum;

	/// <summary> 数据包，</summary>
	//unsigned char _DataPackage;

	/// <summary> 校验码，本课题固定为0</summary>
	unsigned short _CheckCode;

	/// <summary> 终止码，固定填写为：0x0a0d</summary>
	unsigned short _CodeEndSign;

};
STRUCT_PTR_DECLARE(SMessageFormat);


////////////////////////////////////////////////////////////////////////////////////////////////////
// file:	报文类型定义
//
// summary:	阮道清
////////////////////////////////////////////////////////////////////////////////////////////////////

enum  SMessageType
{
	/// <summary> 下发报文.  </summary>
	Struct_DicpatchMessage = 0,

	/// <summary> 上报报文.  </summary>
	Struct_ReportMessage,
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	下发报文命令码.  </summary>
///
/// <remarks>	阮道清, 2020/8/5. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////

#define _LVC_DM_TXCX		 0X0001		//通信查询:			人工操作或系统控制软件自动检查逻辑链路状态时下发
#define _LVC_DM_XTZJ		 0X0002		//系统自检:			要求雷达或标校车进行自检并上报自检结果
#define _LVC_DM_LDCSHPZ      0X0003		//雷达初始化配置:	下发雷达的初始化配置参数
#define _LVC_DM_LDZBCX       0X0004		//雷达坐标查询:		要求雷达上报当前阵面法向指向及雷达/标校车站址坐标
#define _LVC_DM_XYKZ	     0X0005		//运行控制:			要求雷达或标校车切换工作状态
#define _LVC_DM_BJCCSHPZ     0X0006		//标校车初始化配置:	下发标校车初始化配置参数
#define _LVC_DM_SSMBCS       0X0007		//实时目标参数:		下发回波模拟目标的实时位置、速度与RCS参数

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	上报报文命令码. </summary>
///
/// <remarks>	阮道清, 2020/8/5. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////

#define _LVC_RM_MLXY		 0X0081		//命令响应:			接收到通信查询命令后立即上报
#define _LVC_RM_XTSB		 0X0082		//心跳上报:预位回复	在系统通信空闲时定时发送
#define _LVC_RM_LDZJSB		 0X0083		//雷达自检上报:		雷达上报全系统与分系统自检结果
#define _LVC_RM_BJCZJSB      0X0084		//标校车自检上报:	标校车上报全系统与分系统自检结果
#define _LVC_RM_LDZBSB       0X0085		//雷达坐标上报:		收到“雷达坐标查询”命令后上报当前阵面法向指向及雷达/标校车站址坐标
#define _LVC_RM_DJSJ         0X0086		//点迹数据上报:			当雷达系统内部产生点迹数据后主动上报
#define _LVC_RM_HJSJ         0X0087		//航迹数据上报:			当雷达系统内部产生航迹数据后主动上报
#define _LVC_RM_LDGZCS       0X0088		//雷达工作参数上报:		当雷达工作参数发生变化时立即主动上报
#define _LVC_RM_LDYXKZHF     0X0089		//雷达运行控制回复:
#define _LVC_RM_BJCKZZT      0X008a		//标杆车控制状态回复，标杆车目标模拟器数据源切换，标校车初始化配置回复;
#define _LVC_RM_LDSCHJ       0X008b		//雷达删除航迹

#define _LVC_TPC_ScnDldNotify 0x00F1 //加载回复
#define _LVC_TPC_SysRdyNotify 0x00F2 //预位回复

////////////////////////////////////////////////////////////////////////////////////////////////////
// file:	下发报文中通信查询 _LVC_DM_TXCX
//
// summary:	阮道清
////////////////////////////////////////////////////////////////////////////////////////////////////

struct  DMCommunicationQueryPackage
{
	
};
STRUCT_PTR_DECLARE(DMCommunicationQueryPackage);

////////////////////////////////////////////////////////////////////////////////////////////////////
// file:	下发报文中系统自检
// summary:	阮道清
////////////////////////////////////////////////////////////////////////////////////////////////////

struct  DMSystemSelfCheckPackage
{
	
};
STRUCT_PTR_DECLARE(DMSystemSelfCheckPackage);

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	下发报文中雷达初始化配置包中抗干扰措施.  </summary>
///
/// <remarks>	阮道清, 2020/8/5. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////

enum DMCQPAntiJammingMeasure
{
	/// <summary> 旁瓣对消.  </summary>
	DMCQKAJM_PBDX = 0,

	/// <summary> 旁瓣消隐.  </summary>
	DMCQKAJM_PBXY,

	/// <summary> 脉冲压缩 .  </summary>
	DMCQKAJM_MCYS,

	/// <summary> 频率捷变.  </summary>
	DMCQKAJM_PLJB,

	/// <summary> 恒虚警处理.  </summary>
	DMCQKAJM_HXJCL,

	/// <summary> 距离前沿跟踪.  </summary>
	DMCQKAJM_JLQYGZ,

	/// <summary> 速度前沿跟踪 .  </summary>
	DMCQKAJM_SDQYGZ,

	/// <summary> 速度后沿跟踪 .  </summary>
	DMCQKAJM_SDHYGZ,

	/// <summary> 被动跟踪.  </summary>
	DMCQKAJM_BDGZ,

	/// <summary> 功率管理.  </summary>
	DMCQKAJM_GLGL,

	/// <summary> 寻凹捷变频.  </summary>
	DMCQKAJM_XAJBP,

	/// <summary> 干扰置零.  </summary>
	DMCQKAJM_GRZL,

	/// <summary> 动目标检测.  </summary>
	DMCQKAJM_DMBJC,

	/// <summary> 扇区静默.  </summary>
	DMCQKAJM_SQJM,

	/// <summary> 掩护脉冲.  </summary>
	DMCQKAJM_YHMC,

	/// <summary> 抗异步干扰.  </summary>
	DMCQKAJM_KYBGR,

	/// <summary> 无抗干扰措施.  </summary>
	DMCQKAJM_WKGRCS,
};

////////////////////////////////////////////////////////////////////////////////////////////////////
// file:	下发报文中雷达初始化配置
//
// summary:	阮道清
////////////////////////////////////////////////////////////////////////////////////////////////////

struct  DMRadarInitConfigPackage
{

	/// <summary> 初始工作频率为点频,取值范围为0~40000MHz</summary>
	UINT32 _WorkFrequency;

	/// <summary> 扫描范围-方位，单位：度</summary>
	INT32 _ScanningAzimuth;

	/// <summary> 扫描范围-俯仰，单位：度</summary>
	INT32 _ScanningPitch;

	/// <summary> 抗干扰措施，具体参数意义参考DMCQPAntiJammingMeasure枚举定义</summary>
	UINT32 _AntiJammingMeasure;

	/// <summary> 阵面指向角度，天线阵面法线方向在雷达车身平面投影与雷达车头方向之间的夹角</summary>
	INT32 _AntennaArrayAngle;

};
STRUCT_PTR_DECLARE(DMRadarInitConfigPackage);

////////////////////////////////////////////////////////////////////////////////////////////////////
// file:	下发报文中雷达坐标查询
//
// summary:	阮道清
////////////////////////////////////////////////////////////////////////////////////////////////////

struct  DMRadarLocationQueryPackage
{

};
STRUCT_PTR_DECLARE(DMRadarLocationQueryPackage);

////////////////////////////////////////////////////////////////////////////////////////////////////
// file:	下发报文中运行控制的运行控制码
//
// summary:	阮道清
////////////////////////////////////////////////////////////////////////////////////////////////////

enum  DMRunControlCode
{
	/// <summary> 工作.  </summary>
	DMRunControl_Working = 0,

	/// <summary> 待机.  </summary>
	DMRunControl_Standby,

	/// <summary> 预留.  </summary>
	DMRunControl_Reserve,
};

////////////////////////////////////////////////////////////////////////////////////////////////////
// file:	下发报文中运行控制包内容定义
//
// summary:	阮道清
////////////////////////////////////////////////////////////////////////////////////////////////////

struct  DMRunControlPackage
{

	/// <summary> 运行控制码，0~2</summary>
	UINT8 _WorkCodeID;

};
STRUCT_PTR_DECLARE(DMRunControlPackage);

////////////////////////////////////////////////////////////////////////////////////////////////////
// file:	下发报文中标校车场景模式选择
//
// summary:	阮道清
////////////////////////////////////////////////////////////////////////////////////////////////////

enum  DMAMCScenarioModeSelect
{
	/// <summary> 内部仿真场景.  </summary>
	DMAMCS_InternalScenario = 0,

	/// <summary> 接收外部仿真场景参数进行仿真.  </summary>
	DMAMCS_ReceiveExternalData,

	/// <summary> 预留.  </summary>
	DMAMCS_Reserve,
};


////////////////////////////////////////////////////////////////////////////////////////////////////
// file:	下发报文中标校车初始化配置中目标RCS初始模式 
//
// summary:	阮道清
////////////////////////////////////////////////////////////////////////////////////////////////////

enum  DMAMCInintializeRCSMode
{
	/// <summary> 固定值.  </summary>
	DMAMCIRCSMode_FixedValue = 0,

	/// <summary> Swerling I.  </summary>
	DMAMCIRCSMode_SwerlingI,

	/// <summary> Swerling II.  </summary>
	DMAMCIRCSMode_SwerlingII,

	/// <summary> Swerling III.  </summary>
	DMAMCIRCSMode_SwerlingIII,

	/// <summary> Swerling IV.  </summary>
	DMAMCIRCSMode_SwerlingIV,

	/// <summary> 预留.  </summary>
	DMAMCIRCSMode_Reserve,
};

////////////////////////////////////////////////////////////////////////////////////////////////////
// file:	标校车配置包中目标信息格式定义
//
// summary:	阮道清
////////////////////////////////////////////////////////////////////////////////////////////////////

struct  DMAMCInitializeOfTarget
{

	/// <summary> 目标距离，取值范围5~3000，单位：0.1KM</summary>
	INT32 _TargetDistance;

	/// <summary> 目标速度，取值范围-1100~1100，单位：m/s,说明：目标相对雷达的径向速度，靠近为正，远离为负</summary>
	INT32 _TargetVelocity;

	/// <summary> 目标频移，取值范围-2800~2800，单位:Hz</summary>
	INT32 _TargetFrequencyShift;

	/// <summary> 目标工作频率，取值范围0~40000，单位：MHz</summary>
	UINT32 _TargetWorkingFrequency;

	/// <summary> 目标RCS，取值范围0~99999，单位:m2</summary>
	DOUBLE _TargetRCS;

	/// <summary> 目标RCS模式，取值范围0~5</summary>
	UINT8 _TargetRCSMode;

	/// <summary> 目标接收衰减，取值范围0~630，单位:0.1dB</summary>
	UINT32 _TargetReceiveDecay;

	/// <summary> 目标发射衰减1，取值范围0~630，单位:0.1dB</summary>
	UINT32 _TargetSendDecayI;

	/// <summary> 目标发射衰减2，取值范围0~630，单位:0.1dB</summary>
	UINT32 _TargetSendDecayII;

	/// <summary> 目标发射衰减3，取值范围0~630，单位:0.1dB</summary>
	UINT32 _TargetSendDecayIII;
};
STRUCT_PTR_DECLARE(DMAMCInitializeOfTarget);


////////////////////////////////////////////////////////////////////////////////////////////////////
// file:	标校车初始化配置包内容格式定义
//
// summary:	阮道清
////////////////////////////////////////////////////////////////////////////////////////////////////

struct  DMAalibrationMarkCarInitPackage
{

	/// <summary> 场景仿真模式选择，取值范围0~2；0：切换为可控制状态</summary>
	UINT8 _ScenarioMode;

	/// <summary> 模拟目标数量N，取值范围1~256</summary>
	UINT32 _TargetTotalNum;

	/// <summary> 目标信息</summary>
	//std::vector<DMAMCInitializeOfTarget> _TargretInformation;

};
STRUCT_PTR_DECLARE(DMAalibrationMarkCarInitPackage);


////////////////////////////////////////////////////////////////////////////////////////////////////
// file:	下发报文中实时目标参数格式定义
//
// summary:	阮道清
////////////////////////////////////////////////////////////////////////////////////////////////////

struct  DMTargetRealTimePackage
{

	/// <summary> 模拟目标数量N，取值范围1~256</summary>
	UINT32 _TargetTotalNum;

	/// <summary> 目标信息</summary>
	std::vector<DMAMCInitializeOfTarget> _TargretInformation;

};
STRUCT_PTR_DECLARE(DMTargetRealTimePackage);

////////////////////////////////////////////////////////////////////////////////////////////////////
// file:	上报报文中命令响应
//
// summary:	阮道清
////////////////////////////////////////////////////////////////////////////////////////////////////

struct  RMCommandAnswerPackage
{
};
STRUCT_PTR_DECLARE(RMCommandAnswerPackage);

////////////////////////////////////////////////////////////////////////////////////////////////////
// file:	上报报文中心跳上报
//
// summary:	阮道清
////////////////////////////////////////////////////////////////////////////////////////////////////

struct  RMPantReportPackage
{
};
STRUCT_PTR_DECLARE(RMPantReportPackage);


////////////////////////////////////////////////////////////////////////////////////////////////////
// file:	上报报文中全系统自检结果
//
// summary:	阮道清
////////////////////////////////////////////////////////////////////////////////////////////////////

enum  RMSystemSelfTestResult
{
	/// <summary> 成功.  </summary>
	RMSSTR_Success = 0,

	/// <summary> 失败.  </summary>
	RMSSTR_Fail,

	/// <summary> 预留.  </summary>
	RMSSTR_Reserve,
};

////////////////////////////////////////////////////////////////////////////////////////////////////
// file:	上报报文中雷达自检结果
//
// summary:	阮道清
////////////////////////////////////////////////////////////////////////////////////////////////////

// struct  RMRadarSelfTestResult
// {
// 
// 	/// <summary> 雷达全系统自检结果，取值范围0~2，说明：0—成功；1—失败；2—预留</summary>
// 	UINT8 _RadarSystemTestResult;
// 
// 	/// <summary> 雷达分系统自检结果，说明：分系统自检成功—对应bit为0；分系统自检失败—对应bit为1</summary>
// 	UINT16 _RadarSubSystemTestResult;
// 
// };


// 雷达自检上报 0x0084
struct RMRadarSelfTestResult
{
	UINT8 ucChkTotal; // 全系统自检结果 0~2 0—成功; 1—失败; 2—预留;
	UINT16 usLink;  // 链路监测信息
					// D0: TR组件 0:正常 1:故障
					// D1: DBF
					// D2: 信号处理
					// D3: 频综
					// D4: 干扰侦查
					// D5: 伺服
					// D6: 显控


	UINT16 usSPSubIO;// 信号处理信息
					 // D0-D3P分系统监测 0表示分系统正常；7表示分系统故障；其他表示分系统降级；
					 // D4 接口组合状态 0表示无故障，1表示故障
	UINT16 PluginState;// 伺服监测信息 D0~D7:插件故障状态，0表示无故障，1表示故障
	UINT16 sc_moni;/*系统监测字, 所有的位监测,0表示故障 1表示正常
				   * D1-D3:功放状态码 D5:驱动器(功放故障) D7:输入输出板(A14) D8:角编码板(A11) D10:加电控制板(伺服加电控制组合) 其他:备份
				   * D1D2D3: 000-功放超速(属正常) 001-电源故障 010-功放欠压 011-过流
				   * 100-过热 101-过载 110-过压 111-正常 */

				   /*伺服系统状态字*/
	UINT16 usSvState;   /*D0:脱机联机  0脱机  1联机*/
						/*D1:电机运行(功放运行)  0未运行  1运行*/
						/*D2:高压加电好(功放高压&高压加电)  0未加电好 1加电好*/
						/*D3:伺服解锁  0伺服锁定  1伺服解锁*/
						/*D4:紧急停机  0停机  1正常*/
						/*D5:阵面安全  0未安全  1安全*/
						/*D6:车门开关(舱门关)  0门开  1门关*/
						/*D7:车厢解锁(方位解锁好)  0车厢锁定  1车厢解锁*/
						/*D8:功放使能 0未使能 1使能*/
						/*D9:车复位好 0未复位 1复位好*/

						// 频综监测信息
	UINT16 usGeneralFault; // 频综组合总故障
	UINT16 Group1Fault; // 频综组合1故障 D0~D14:分别表示插件1~15故障状态，0表示无故障，1表示故障
	UINT16 Group2Fault; // 频综组合2故障 D0~D3:分别表示插件1~4故障状态，0表示无故障，1表示故障

	UINT16 PluginFault; // DBF插件故障监测 D0~D8:分别表示插件1~9故障状态，0表示无故障，1表示故障

	UINT16 usJamInfomation;     /*干扰侦察监测信息 D8~D15:保留；
								D7:A15模拟组件状态；
								D6:保留
								D5:A14与A15通信状态；
								D4:A8控制字光纤状态；
								D3:A8与A14通信状态；
								D2:A8&&A9&&A11的Link传输状态；
								D1:A11AD采样时钟；
								D0:风机状态&&A11芯片过热；
								以上监测位，0表示正常，1表示故障*/
};
STRUCT_PTR_DECLARE(RMRadarSelfTestResult);

////////////////////////////////////////////////////////////////////////////////////////////////////
// file:	上报报文中标校车自检结果
//
// summary:	阮道清
////////////////////////////////////////////////////////////////////////////////////////////////////

struct  RMCACSelfTestResult
{

	/// <summary> 雷达全系统自检结果，取值范围0~2，说明：0—成功；1—失败；2—预留</summary>
	UINT8 _CACSystemTestResult;

	/// <summary> 雷达分系统自检结果，说明：分系统自检成功—对应bit为0；分系统自检失败—对应bit为1</summary>
	/*bit1 ~7目标模拟器
	bit1 基准组件A4
	bit2 本振组件A6
	bit3上变频组件1 A9
	bit4上变频组件2 A13
	bit5上变频组件3 A14
	bit6模拟接收组件A3
	bit7宽带数字储频组件A11
	bit8 ~12目标模拟器
	bit8 基准组件A8
	bit9 本振组件A10
	bit10 上变频组件A4
	bit11模拟接收组件A12
	bit12宽带数字储频组件A6
	*/
	UINT16 _CACSubSystemTestResult;

};
STRUCT_PTR_DECLARE(RMCACSelfTestResult);

////////////////////////////////////////////////////////////////////////////////////////////////////
// file:	上报报文中雷达坐标查询上报 _LVC_RM_LDZBSB
// 
// summary:	阮道清
////////////////////////////////////////////////////////////////////////////////////////////////////

struct  RMRadarCoordinateReport
{

	/// <summary> 阵面指向角度，天线阵面法线方向在雷达车身平面投影与雷达车头方向之间的夹角，范围：-180~180，单位：deg</summary>
	INT32 _AntennaArrayAngle;

	/// <summary> 雷达站址   \
		/// 		  经度范围：-180~180，单位：deg,说明：大地坐标系\
	/// 		  经度范围：-90~90，单位：deg,说明：大地坐标系\
	/// 		   经度范围：-1000~30000，单位：m,说明：大地坐标系 </summary>

	INT32 _RadarLon;
	INT32 _RadarLat;
	INT32 _RadarAlt;
	/// <summary> 标校车站址   \
		/// 		  经度范围：-180~180，单位：deg,说明：大地坐标系\
	/// 		  经度范围：-90~90，单位：deg,说明：大地坐标系\
	/// 		   经度范围：-1000~30000，单位：m,说明：大地坐标系 </summary>

	INT32 _BxcLon;
	INT32 _BxcLat;
	INT32 _BxcAlt;
};
STRUCT_PTR_DECLARE(RMRadarCoordinateReport);


////////////////////////////////////////////////////////////////////////////////////////////////////
// file:	上报报文中点迹数据上报 _LVC_RM_DJSJ
// 
// summary:	w
////////////////////////////////////////////////////////////////////////////////////////////////////

// struct  RMPointTraceReport
// {
// 
// };
// STRUCT_PTR_DECLARE(RMPointTraceReport);

////////////////////////////////////////////////////////////////////////////////////////////////////
// file:	上报报文中航迹数据上报 _LVC_RM_HJSJ
// 
// summary:	w
////////////////////////////////////////////////////////////////////////////////////////////////////

// struct  RMFlightTraceReport
// {
// 
// };
// STRUCT_PTR_DECLARE(RMFlightTraceReport);

////////////////////////////////////////////////////////////////////////////////////////////////////
// file:	上报报文中雷达工作参数上报 _LVC_RM_LDGZCS
// 
// summary:	w
////////////////////////////////////////////////////////////////////////////////////////////////////

struct ST_BEAM_INFO
{
	INT32 iBeamAz;// 波束中心方位 量化0.1deg [-180 ~ 180°]
	INT32 iBeamEl;// 波束中心俯仰 量化0.1deg [-180 ~ 180°]
	UINT32 iBeamWidthA;// 辐射状态  0辐射1不辐射，波束宽度方位 量化0.1deg [0 ~ 180]
	UINT32 iBeamWidthE;// 工作频率  非捷变时有效，波束宽度俯仰 量化0.1deg [0 ~ 180]
	UINT32 uiBeamCutTime;// 波位驻留时间 0-搜索波形 1-跟踪波形 2-预留
	UINT8 ucWaveType;// 工作波形  0-搜索波形  1-跟踪波形  2预留
	UINT8 ucAgilityType;//捷变状态 0-捷变 1-非捷变 2-预留
};

struct  RMRadarWorkParamReport
{
	UINT32 uiBeamCutEventNum; // 波位切换事件数N 0~100 50ms内波位切换次数
							  //    ST_BEAM_INFO stBeamInfo; 后接 uiBeamCutEventNum个 ST_BEAM_INFO
	//std::vector<ST_BEAM_INFO> BeamINfoList; //
	ST_BEAM_INFO BeamINfoList[100];
};
STRUCT_PTR_DECLARE(RMRadarWorkParamReport);




// 雷达工作状态回报，雷达运行控制回复 0x0089
struct RMRadarRunControlReport
{
	UINT8 ucWorkStateReturn;// 运行控制码 0—工作；1—待机；2—预留;
} ;
STRUCT_PTR_DECLARE(RMRadarRunControlReport);

// 标杆车控制状态回复，目标模拟器数据源切换,标校车初始化配置回复  0x008A
struct RMCACControlStateReport
{
	UINT8 ucDataSrc; // 数据源 0—本地; 1—控制中心;
} ;
STRUCT_PTR_DECLARE(RMCACControlStateReport);

/// 雷达删除航迹  0x008B
struct RMRadarDeleteTrack
{
	UINT8 ucTrackTotalNum; // 删除航迹数量
	UINT8 bak[3]; // 保留
	UINT16 usTrackId[50]; // 删除航迹号
};
STRUCT_PTR_DECLARE(RMRadarDeleteTrack);

// 时间结构
struct INTF_DC_TIME
{
	UINT32 year : 12;  /*年:0~4095*/
	UINT32 mon : 4;    /*月:1~12*/
	UINT32 day : 8;    /*日:1~31*/
	UINT32 hour : 8;   /*时:0~23*/
	UINT32 us;      /*发送方发送时刻的分钟、秒、毫秒、微秒 以微秒为计时单位0~3600000000*/
};

//航迹
struct RMFlightTraceReport
{
	INTF_DC_TIME stTrackTime; // 时间
	UINT32 uiPlotId; // 点迹编号
	UINT16 uiTrackId; // 航迹号
	UINT16 tgtNo; // 团目标编号
	UINT8 subNo; // 子目标编号
	UINT8 traceStatus; // 跟踪状态 0:监视 1:粗跟 2:精跟
	UINT8 ucTrackQuality; // 跟踪质量 0:外推 1:搜索 2:跟踪 3: 被动跟踪
	UINT8 ucFollowCtrl; // 跟踪控制 0:正常跟踪 1:被动跟踪 2:烧穿 3:测速 4:成像
	UINT16 waveForm; // 组合波形编号
	INT16 SNR; // 信噪比 0.1dB量化
	INT32 amp; // 回波幅度
	INT32 GR; // 目标距离 大地极坐标/1m（球坐标系）
	INT32 GA; // 目标方位 大地极坐标/0.01度
	INT32 GE; // 目标俯仰 大地极坐标/0.01度
	INT32 distErr; // 距离误差 大地极坐标/1m
	INT32 azErr; // 方位误差 大地极坐标/0.01度
	INT32 elErr; // 俯仰误差 大地极坐标/0.01度
	INT32 Vr; // 径向速度 大地极坐标/1m/s
	INT32 Va; // 方位速度 大地极坐标/0.01度/s
	INT32 Ve; // 俯仰速度 大地极坐标/0.01度/s
	INT32 X; // 航迹X/1m（东北天坐标系）
	INT32 Y; // 航迹Y/1m
	INT32 Z; // 航迹Z/1m
	INT32 VX; // 航迹X速度/1m/s
	INT32 VY; // 航迹Y速度/1m/s
	INT32 VZ; // 航迹Z速度/1m/s
	INT16 DopV; // 多普勒速度
	INT16 remain;
};

//点迹
struct RMPointTraceReport
{
	INTF_DC_TIME stPlotTime; // 点迹时间
	UINT32 uiPlotId; // 点迹编号
	UINT16 waveForm; // 波形编号
	INT16 SNR; // 信噪比 0.1dB量化
	INT32 amp; // 回波幅度
	INT32 R; // 点迹距离 大地极坐标/1m
	INT32 Az; // 点迹方位 大地极坐标/0.01度
	INT32 El; // 点迹俯仰 大地极坐标/0.01度
	INT32 distErr; // 距离误差 大地极坐标/1m
	INT32 azErr; // 方位误差 大地极坐标/0.01度
	INT32 elErr; // 俯仰误差 大地极坐标/0.01度
	INT32 X; // 点迹X/1m
	INT32 Y; // 点迹Y/1m
	INT32 Z; // 点迹Z/1m
	INT8 SFmark; // 搜索跟踪标志
	INT8 remain;
	INT16 DopV; // 多普勒速度
};

//静默扇区
struct SECTOR
{
	UINT16  usStartA;   // 起始方位 0~360度/0.1度
	UINT16  usEndA;     // 终止方位 0~360度/0.1度
	INT16   usStartE;   // 起始俯仰 -90~90度/0.1度
	INT16   usEndE;     // 终止俯仰 -90~90度/0.1度
};

//搜索区域
struct SEARCH_AREA_DATA
{
	UINT16  usStartA; // 起始方位 0~360度/0.1度
	UINT16 usEndA; // 终止方位 0~360度/0.1度
	INT16 usStartE; // 起始俯仰 -90~90度/0.1度
	INT16 usEndE; // 终止俯仰 -90~90度/0.1度 ,终止俯仰必须比起始俯仰大！
};

// 雷达初始化配置 0x0003
struct CENTER2RADAR_INIT
{
	UINT8 ucStart;         // 0停止 3启动，表示伺服方位，俯仰不动
	UINT32 usPscCtrl;      // 位置控制 量化: 0.1 范围: 0~360

	UINT8 disCmdDbf;/*旁瓣对消使能(DBF)，0:不使能  1:使能*/
	UINT8 disCmdDbfNum;/*旁瓣对消个数(DBF)，0:不对消  n:对消最多5个*/
	UINT8 disCmdShadow;/*旁瓣匿影使能，0:不使能  1:使能*/
	UINT16 auxShadowB;/*副瓣匿影B值(信号处理将该值乘以64作为B值)，数值0～10000，缺省256*/
	UINT8 disCmdPower;/*强脉冲剔除使能，0:不使能  1:使能*/
	UINT8 disCmdMutiFake;/*多假目标剔除使能，0:不使能  1:使能*/

	UINT8 ucMode;           // 主脉冲频率控制模式 0:固定 1:捷变 2:寻凹
	UINT16 ucMainPulseFrq;  // 主脉冲频率数 频率控制模式为固定时有效，0~40表示频点F0~F40,0xFFFF表示取消设置
	UINT16 ucFtCvrPulseFrq; // 前掩护脉冲频点, 0~40, 0xFFFF表示取消设置
	UINT16 ucBkCvrPulseFrq; // 后掩护脉冲频点, 0~40, 0xFFFF表示取消设置

	UINT16 usMainWaveCode;  // 主脉冲波形编号 0~67
	UINT8 ucFtCvrCtrl;      // 前掩护控制 0:无; 1:固定; 2:捷变
	UINT8 ucBkCvrCtrl;      // 后掩护控制 0:无; 1:固定; 2:捷变
	UINT8 ucFtCvrDirCtrl;   // 前掩护指向控制 0:自动 1:人工
	UINT8 ucBkCvrDirCtrl;   // 后掩护指向控制 0:自动 1:人工
	UINT16 usFtCvrIntvl;    // 前掩护间隔 0~100
	UINT16 usBkCvrIntvl;    // 后掩护间隔 0~100
	UINT16 usFtCvrWaveCode; // 前掩护脉冲波形编号 0~7
	UINT16 usBkCvrWaveCode; // 后掩护脉冲波形编号 0~7
	UINT32 uiFtCvrA;        // 前掩护方位 0~360度/0.000001度
	INT32 iFtCvrE;          // 前掩护俯仰 -90~90度/0.000001度
	UINT32 uiBkCvrA;        // 后掩护方位 0~360度/0.000001度
	INT32 iBkCvrE;          // 后掩护俯仰 -90~90度/0.000001度

	UINT8 ucPassFollow;	//被动跟踪

	UINT8 ucSectorEf[2];    // 区域有效标志 1有效
	SECTOR stSector[2];     // 静默扇区

	UINT8 disCmdAsync;      /*异步干扰使能，0:不使能  1:使能*/

	UINT8 ucSearchArea1; // 搜索区域1有效标志 0无效 1有效
	UINT8 ucSearchArea2; // 搜索区域2有效标志 0无效 1有效

	SEARCH_AREA_DATA stSearchAreaData[2]; // 搜索区域
};


//标校车接口


// typedef struct
// {
// 	TS_MetaType(TS_INFORMATION_SEND);
// 	unsigned int R[3]; //目标1-9距离，量化单位：Km
// 	short V[3]; //目标1-9速度 量化单位：m/s
// 	short Freq[3]; //目标1-9频率偏移，量化单位：Hz
// 	unsigned char IfFreMove; // 频移标志 0 频移无效 1 频移有效
// }/*_attribute_((packed))*/TS_INFORMATION_SEND;

struct TS_INFORMATION_SEND
{
	unsigned int R[3]; //目标1-9距离，量化单位：Km
	short V[3]; //目标1-9速度 量化单位：m/s
	short Freq[3]; //目标1-9频率偏移，量化单位：Hz
	unsigned char IfFreMove; // 频移标志 0 频移无效 1 频移有效
};

// typedef struct 
// {
// 	TS_MetaType(BGC2_TO_TS);
// 	UINT8 ucWorkState; //远控状态切换
// 	UINT8 ucTSWKfrq; //工作频率
// 	UINT8 ucTSRCSsevro; //目标RCS随动（赋值为0不随动）
// 	UINT8 ucTSrecvAtt; //接收衰减0-63
// 	UINT8 ucTSemsnAtt[3]; //发射衰减0-63，（对应发射衰减1、发射衰减2、发射衰减3）
// 	UINT8 ucTSdataEffect; //模拟器辐射开关键，1辐射；0关闭辐射
// 	UINT16 ucTarSt; //9个目标的选中情况，前9位，1选中；0未选中
// 	TS_INFORMATION_SEND stTOTsInfo[3]; //目标数据
// }BGC2_TO_TS;

//显控给模拟器的数据
struct BGC2_TO_TS
{
	UINT8 ucWorkState; //远控状态切换
	UINT8 ucTSWKfrq; //工作频率
	UINT8 ucTSRCSsevro; //目标RCS随动（赋值为0不随动）
	UINT8 ucTSrecvAtt; //接收衰减0-63
	UINT8 ucTSemsnAtt[3]; //发射衰减0-63，（对应发射衰减1、发射衰减2、发射衰减3）
	UINT8 ucTSdataEffect; //模拟器辐射开关键，1辐射；0关闭辐射
	UINT16 ucTarSt; //9个目标的选中情况，前9位，1选中；0未选中
	TS_INFORMATION_SEND stTOTsInfo[3]; //目标数据
};


#pragma pack()