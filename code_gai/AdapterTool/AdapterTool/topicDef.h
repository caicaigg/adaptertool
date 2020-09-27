/*!
 * 文 件 名：topicDef.h
 * 命名空间：
 * 功    能：DDS传输公共数据定义文件，xml文件中Topic配置长度请按本文件定义长度定义
 *	注意：所有字符串数据采用utf-8编码
 * 作    者：MYS
 * 通    讯：
 * 生成日期：
 * 版 本 号：V1.0.0.0
 * 修改日志：
 *
 *
*/
#pragma once

//设备数量
#define MAXDEVICECOUNT	32	
//数据块个数
#define MAXDATACOUNT		32
//频点/重周点/脉宽点最大数量
#define MAXSEQLEN	32

#pragma pack(push, 1)

//Topic数据长度
// const unsigned int G_TDS_SysHaltRequest				= 1    ;					//1系统急停，无参数
// const unsigned int G_TDS_SysBitRequest				= 140  ;					//2系统/设备自检
// const unsigned int G_TDS_SysResetRequest				= 136  ;					//3系统/设备复位
// const unsigned int G_TDS_RadBitRFRequest2			= 102420;				//4射频发送
// const unsigned int G_TDS_RadBitRFRequest				= 48;					//4辐射闭环自检-射频
// const unsigned int G_TDS_RadBitSDRequest				= 32   ;					//5辐射闭环自检-频谱  			36
// const unsigned int G_TDS_ScnDldRequest				= 24   ;					//6场景启动加载
// const unsigned int G_TDS_SysRdyRequest				= 4    ;					//7系统预位
// const unsigned int G_TDS_SysCtrlRequest				= 36   ;					//8系统运行控制
// const unsigned int G_TDS_SysStqRequest				= 4    ;					//9系统/设备状态查询
// const unsigned int G_TDS_ScnPlatUpdate				= 2316 ;					//10场景平台数据更新
// const unsigned int G_TDS_ScnEmtEvent					= 2056 ;					//11场景辐射源事件
// const unsigned int G_TDS_ScnWpnEvent					= 520  ;					//12场景武器事件
// const unsigned int G_TDS_RPScnDldRequest				= 24   ;					//13回放-场景启动加载
// const unsigned int G_TDS_RPScnPlatUpdate				= 2316 ;					//14场景回放平台数据更新
// const unsigned int G_TDS_RPScnEmtEvent				= 2056 ;					//15场景回放辐射源事件
// const unsigned int G_TDS_RPScnWpnEvent				= 520  ;					//16场景回放武器事件
// const unsigned int G_TDS_OwnInsUpdate				= 148  ;					//17载机惯导数据更新	
// const unsigned int G_TDS_ScnSimEvent					= 7688 ;					//18场景仿真事件
// const unsigned int G_TDS_ScnDatMixNotify				= 615  ;					//场景辐射源融合数据上报     228
// const unsigned int G_TDS_SysHaltNotify				= 516  ;					//系统急停上报
// const unsigned int G_TDS_SysBitReply					= 8460 ;					//20系统/设备自检回复
// const unsigned int G_TDS_ScnDldNotify				= 264  ;					//场景启动加载回复
// const unsigned int G_TDS_SysRdyNotify				= 8460 ;					//系统预位上报			
// const unsigned int G_TDS_SysStqReply					= 16524;					//系统/设备状态查询回复
// const unsigned int G_TDS_RadBitSPNotify				= 8220 ;					//辐射闭环自检-频谱上报		
// const unsigned int G_TDS_DevInstNotify				= 2380 ;					//25设备控制指令上报			2384
// const unsigned int G_TDS_RadPltNotify				= 180  ;					//雷达点迹上报			184
// const unsigned int G_TDS_RadTrkNotify				= 96   ;					//雷达航迹上报			104
// const unsigned int G_TDS_RadParmNotify				= 5700 ;					//雷达工作参数上报
// const unsigned int G_TDS_SutChsNotify				= 515  ;					//SUT分选数据上报		452
// const unsigned int G_TDS_ECMSPNotify					= 8216 ;					//30ECM频谱上报
// const unsigned int G_TDS_SimSutEvent					= 1    ;					//SUT仿真事件（预留）
// const unsigned int G_TDS_VehicleHPRUpt				= 900  ;					//地面车辆的姿态数据更新
// const unsigned int G_TDS_ExtPlatUpdate				= 2080 ;					//外部平台更新驱动
// const unsigned int G_TDS_ExtEmtEvetn					= 100  ;					//外部辐射源事件驱动
// const unsigned int G_TDS_ExtSutAntScEvent			= 68   ;					//外部SUT天线扫描事件驱动

//																				 
//返回值常量定义
const enum { ACK_SUCCESS = 0, ACK_FAILE =1};
typedef unsigned char uchar;
typedef unsigned int uint;
//1.系统急停
struct TPC_SysHaltRequest
{
};
//2.系统自检
struct TPC_SysBitRequest
{
	int subSysId;					///<目标子系统ID
	int bitMdl;						///<自检方式 0-上电自检，1-维护自检
	int bitDevCnt;					///<自检设备数量N
	int devId[MAXDEVICECOUNT];		///<设备Id,有效数N
};
//3.系统复位
struct TPC_SysResetRequest
{
	int subSysId;					///<目标子系统ID
	int resetDevCnt;					///<复位设备数量N
	int devId[MAXDEVICECOUNT];		///<设备Id,有效数N
};

//4.辐射闭环自检 - 信号辐射			
struct TPC_RadBitRFRequest
{
	int		subSysId;					///<目标子系统ID
	int		devId;						///<设备Id
	int		sigRFSw;						///<射频开关 1-开射频，0-关射频
	int		sigMod;						///<信号样式 0-连续波，1-脉冲
	double	plsFreq;						///<频率
	double	plsPrd;						///<重复周期
	double	plsPW;						///<脉宽
	double	sigAzim;						///<信号方位：°
};
//4.辐射闭环自检 - 信号辐射2,用于信号辐射时传递复杂信号
struct TPC_RadBitRFRequest2
{
	int		subSysId;					///<目标子系统ID
	int		devId;						///<设备Id
	int		sigRFSw;						///<射频开关 1-开射频，0-关射频
	double	sigAzim;						///<信号方位：°
	char    sig[102400];					///<信号参数dom
};
//5.辐射闭环自检 - 信号监测			
struct TPC_RadBitSDRequest
{
	int		subSysId;					///<目标子系统ID
	int		bStart;						///<频谱上报 1-开始，0-停止
	double	plsCntFreq;					///<中心频率	 400-18000
	double	montPlsBW;					///<监测带宽
	double	freqRes;					///<频率分辨率
};
//6.启动加载
struct TPC_ScnDldRequest
{
	int subSysId;						///<目标子系统ID
	int scnId;							///<场景ID
	int scnFileMD5[4];					///<xml文件MD5，用作文件完整性校验
};
//7.系统预位
struct TPC_SysRdyRequest
{
	int subSysId;						///<目标子系统ID
};
//8.运行控制
struct TPC_SysCtrlRequest
{
	int subSysId;						///<目标子系统ID
	int cmdCode;							///<命令码：0-开始，1-结束，2-暂停，3-恢复，4-开始回放，5-停止回放，6-暂停回放，7-恢复回放，8以后预留；暂停/恢复比较复杂，还需进一步讨论
	int excTime[6];						///<执行时间：年,月，日，时，分，秒
	int tskId;							///<试验任务Id
};
//9.状态查询
struct TPC_SysStqRequest
{
	int subSysId;						///<目标子系统ID
};
//10.1 平台数据
struct ScnPlat
{
	int	  plat_id;					///<平台Id
	INT32 lon;						///< 经度
	INT32 lat;						///< 纬度
	float alt;						///< 高度
	float hdg;						///< 偏航 站心直角（东北天）坐标系下，机体矢量与坐标系平面夹角
	float pch;						///< 俯仰
	float rol;						///< 横滚
	float spdEast;					///<速度东向 站心直角（东北天）坐标系，东向速度，东正西负
	float spdNorth;					///<速度北向
	float spdUp;						///<速度天向
	float accEast;					///<加速度东向
	float accorth;					///<加速度北向
	float accUp;						///<加速度天向
	float ROThdg;					///<角速度偏航
	float ROTpch;					///<角速度俯仰
	float ROTrol;					///<角速度横滚
};
//10.场景平台更新
struct TPC_ScnPlatUpdate
{
	int		simNo;					///<场景仿真节拍序号
	int		sutPlatCnt;				///<SUT平台数量M 1-16
	ScnPlat sutPlat[4];				///<SUT平台数据块,有效数M
	int		emtPlatCnt;				///<辐射源平台数量N 1-1024
	ScnPlat emtPlat[MAXDATACOUNT];	///<辐射源平台数据块,有效数N
};
//11.1辐射源事件
struct EmtEvtAttr
{
	int		platId;						//搭载平台Id，与平台更新中的Id一致
	int		emtId;						//辐射源Id
	int		tmOff;						//μs	0 - 10000	相对当前仿真节拍的时间偏移，用更细的时间粒度描述对象离散事件
	int		entCode;						//事件码,0:关机，2：模式切换，3：跟踪目标切换，4-目标发现（雷达角度），5-目标丢失，6-被干扰，7-天线方向图更新，8-以后预留；
	int		tgtMdl;						//目标模式Id:事件为模式切换时起效，目标工作模式Id
	int		trkTgtCnt;					//跟踪目标数量
	int		trkTgtIdLst[8];				//跟踪目标id列表
	char		csfNm[8];					//<自定义方向图文件名称
};
//11.辐射源事件	
struct TPC_ScnEmtEvent
{
	int			simNo;						///<场景仿真节拍序号
	int			emtEvtCnt;					///<辐射源事件数量N
	EmtEvtAttr	emtEvt[MAXDATACOUNT];		///<辐射源事件项,有效数N
};
//12.1武器事件事件项
struct WpnEvtAttr
{
	int		ownPlatId;					//搭载平台Id
	int		tgtPlatId;					//目标平台Id
	int		wpnId;						//武器Id
	int		evtId;						//事件Id 0-发射，1-爆炸，2以后预留；
};
//12.武器事件	
struct TPC_ScnWpnEvent
{
	int			simNo;						///<场景仿真节拍序号
	int			wpnEvtCnt;					///<武器事件数量N
	WpnEvtAttr	wpnEvt[MAXDATACOUNT];		///<武器事件,有效数N
};
//13.回放-场景启动加载	
struct TPC_RPScnDldRequest
{
	int subSysId;						///<目标子系统ID
	int scnId;							///<场景ID
	int scnFileMD5[4];					///<xml文件MD5，用作文件完整性校验
};
//14.回放 - 场景平台更新	
struct TPC_RPScnPlatUpdate
{		
	int			simNo;						///<场景仿真节拍序号
	int			sunPlatCnt;					///<SUT平台数量M 1-16
	ScnPlat		sutPlat[1];					///<SUT平台数据块,有效数M
	int			emtPlatCnt;					///<辐射源平台数量N 
	ScnPlat		emtPlat[MAXDATACOUNT];		///<辐射源平台数据块,有效数N
};
//15.回放 - 辐射源事件	
struct TPC_RPScnEmtEvent
{
	int			simNo;						///<场景仿真节拍序号
	int			emtEvtCnt;					///<辐射源事件数量N
	EmtEvtAttr	emtEvt[MAXDATACOUNT];		///<辐射源事件项,有效数N
};
//16.回放 - 武器事件	
struct TPC_RPScnWpnEvent
{
	int			simNo;						///<场景仿真节拍序号
	int			wpnEvtCnt;					///<武器事件数量N
	WpnEvtAttr	wpnEvt[MAXDATACOUNT];		///<武器事件,有效数N
};
//17.载机惯导数据更新	
typedef struct TPC_OwnInsUpdate
{
	int			simNo;						///<场景仿真节拍序号
	double		ownLon;						///<载机经度，°
	double		ownLat;						///<载机纬度，°
	double		altBaro;						///<气压高度，m
	double		altRad;						///<雷达高度，m
	double		ownPitch;					///<俯仰角，°
	double		ownRoll;						///<滚转角，°
	double		hdgTrue;						///<真航向，°
	double		hdgMag;						///<磁航向，°
	double		velEst;						///<东向速度，m/s
	double		velNth;						///<北向速度，m/s
	double		velUp;						///<天向速度，m/s
	double		ownTas;						///<真空速，m/s
	double		grdSpd;						///<地速，m/s
	double		ackAng;						///<攻角，°
	double		sldAng;						///<侧滑角，°
	double		aclEst;						///<东向加速度，m/s^2
	double		aclNst;						///<北向加速度，m/s^2
	double		aclUp;						///<天向加速度，m/s^2
}TPCOSINS;
//18.1雷达工作模式切换子事件	
struct SubEvt_RadWkm
{
	int			swFlg;					///<开关位：0-关机，1-开机，2-模式切换
	int			tgtWkm;					///<目标工作模式：开关为模式切换时起效，目标工作模式Id
};
//18.2雷达波位切换子事件
struct SubEvt_RadBdw
{
	int			tgtBdwId;				///<目标波位Id：波位Id从1开始，按统一方式定义波位编排规则，波位Id对应波位波束矢量方向
	int			wfmNum;					///<当前波位波形数量：1~4
	int			wfmLst[4];				///<波形Id列表：波形Id对应装备参数模型文件中波形参数描述对应Id
};
//18.3雷达波形切换子事件
struct SubEvt_RadWfm
{
	int			tgtWfmId;				///<目标波形Id：波形Id对应装备参数模型文件中波形参数描述对应Id
};
//18.4雷达跟踪目标切换子事件
struct SubEvt_RadTrk
{
	int			trkTgtCnt;					///<跟踪目标数量：1~32，当处于跟踪模式（STT、MTT、TAS等）起效，跟踪目标数量
	int			trkTgtIdLst[32];				///<跟踪目标Id列表
};
//18.5雷达波束赋形切换子事件
struct SubEvt_RadDbf
{
	double		bmPtnFreq;					///<波束方向图频点：0~100000，MHz
	double		bmPtnStep;					///<波束方向图步进：0~10，deg
	int			bmPtnType;					///<波束方向图类型：0-方位，1-俯仰
	int			bmPtnPtNum;					///<波束方向图有效点数：1-720
	//float		bmPtnPtSeq[720];				///<波束方向图点序列：-200~200，dB
};
//18.6导弹武器子事件
struct SubEvt_Msl
{
	int			ownPlatId;					///<导弹搭载平台Id
	int			tgtPlatId;					///<导弹目标平台Id
	int			wpnId;						///<导弹武器Id
	int			initGdWkmId;					///<初始制导模式Id
	int			evtCode;						///<导弹事件码：201-发射，202-爆炸，203-目标切换，204-制导模式切换
	int			hitFlag;						///<命中标识：0-脱靶，1-命中，事件为导弹爆炸时有效
	int			altTgtId;					///<切换目标平台Id：事件为目标切换时有效
	int			altGdWkmId;					///<切换制导模式Id：事件为制导模式切换时有效
};
//18.7仿真事件	
struct SimEvt
{
	int			platId;						///<搭载平台Id，与平台更新中的Id一致
	int			emtId;						///<装备Id
	int			tmOff;						///<时间偏移时间：0~10000，μs，	相对当前仿真节拍的时间偏移，用更细的时间粒度描述对象离散事件
	int			evtCode;						///<事件码：0-关机，1-开机，2-模式切换
											///<			101-雷达波位切换，102-雷达波形切换，103-雷达跟踪目标切换，104-雷达波束赋形切换
											///<			201-导弹发射，202-导弹爆炸，203-导弹目标切换，204-导弹制导模式切换
	SubEvt_RadWkm	seRadWkm;				///<雷达模式切换子事件块
	SubEvt_RadBdw	seRadBdw;				///<雷达波位切换子事件块
	SubEvt_RadWfm	seRadWfm;				///<雷达波形切换子事件块
	SubEvt_RadTrk	seRadTrk;				///<雷达跟踪切换子事件块
	SubEvt_RadDbf	seRadDbf;				///<雷达波束赋形切换子事件块
	SubEvt_Msl		seRadMsl;				///<导弹切换子事件块
};
//18.仿真事件下发	
struct TPC_ScnSimEvent
{
	int			simNo;						///<场景仿真节拍序号
	int			simEvtCnt;					///<辐射源事件数量N
	SimEvt		simEvtSeq[MAXDATACOUNT];		///<事件序列
};

//////////////////////////////////////////////////////////////////////////
//回复数据
//41.场景辐射源融合上报消息
typedef struct TPC_ScnDatMixNotify
{
	int			simTime[7];						///<仿真时间,年,月，日，时，分，秒,毫秒
	int			sutId;							///<融合上报对应的Sut搭载平台Id，Sut平台视角，预留用于未来多对多场景
	int			platId;							///<平台Id
	int			emtId;							///<辐射源Id
	uchar		platForce;						///<平台敌我属性 0-未定义，1-我方，2-敌方，3-友方，4-中立，5以后预留；
	uchar		platCat;						///<平台类型 0-未知，1-地面固定，2-地面移动，3-水面，4-水下，5-导弹，6-固定翼，7-旋转翼，8-无人机，9-卫星，10-升空平台，12-便携，13以后预留
	uchar		emtTyp;							///<辐射源 类型0-未知，1-警戒雷达，2-对空警戒雷达，3-对海警戒雷达，4-低空警戒雷达，5-引导雷达，6-目标指示雷达，7-测高雷达，8-预警雷达，9-导弹预警雷达，10-武器控制雷达，11-炮瞄雷达，12-导弹制导雷达，13-导弹攻击雷达，14-鱼雷攻击雷达，15-多功能雷达，16-导弹末制导雷达，17-轰炸瞄准雷达，18-侦察雷达，19-战场侦察雷达，20-炮位侦察校射雷达，21-活动目标侦察校射雷达，22-航空管制雷达，23-导航雷达，24-地形跟随雷达，25-着陆引导雷达，26-港口监视雷达，27-测量雷达，28-气象雷达，29-敌我识别器，30-机载雷达，31-成像雷达
	float		platPos[3];						///<平台位置,经度 纬度 高度
	float		platAzim;						///<平台方位
	float		platElev;						///<平台俯仰
	float		platSdist;						///<平台斜距
	float		tgtRadSpd;						///<目标径向速度 正为接近，负为远离
	float		tgtTagSpd;						///<目标切向速度 正为逆时针，负为顺时针
	float		sigPowCode;						///<信号功率值  dBm - 120 - 100
	uchar		emtWkMod;						///<辐射源工作模式 0-未知，1-搜索，2-跟踪，3-制导，4-TWS，5-TAS，6以后预留
	uchar		emtPlorMod;						///<辐射源极化方式 0-未知，1-左圆极化，2-右圆极化，3-垂直极化，4-水平极化，5-斜极化，6-极化可选择，7-极化编码，8-极化捷变，9-左旋椭圆极化，10-右旋椭圆极化，11以后预留
	uchar		sigFM;							///<信号调制方式 0-不明，1-常规，2-非线性调频，3-线性调频，4-二相编码，5-四相编码，6-频率编码，8以后预留
	uchar		nlfmTp;							///<非线性调频类型,非线性调频时，该字段有意义，0-未知 1-三角调频 2-以后预留
	float		fmBw;							///<调频带宽
	uchar		pfskCodCnt;						///<二相、四相编码码元个数
	uchar		pfskSeq[20];			///<二相、四相相位编码序列
	uchar		fskCnt;							///<信号频点数
	float		fskSeq[20];						///<频率编码时，代表出现的频率列表，如不足20个，用0表示；
	float		sigScanProd;					///<扫描周期
	float		beamDwlTm;						///<波位驻留时间
	float		IntfDur;						///<相干处理间隔
	uchar		sigRFTyp;						///<信号频率类型 0-不明，1-固定，2-组变，3-分集，4-编码，5-捷变，6-射频参差，7-连续波频率调制，8-连续波编码调制，9-连续波噪声调制，10-脉内频率编码，11以后预留
	uchar		sigRFCnt;						///<信号频点数
	float		sigRFMed;						///<信号频率中值
	float		sigRFRng;						///<信号频率范围
	float		sigRFSeq[MAXSEQLEN];			///<信号频率频点序列，规定最多传8个频点
	uchar		sigPRITyp;						///<信号PRI类型 0-不明，1-固定，2-跳变，3-抖动，4-捷变，5-参差，6-编码，7-滑变，8-连续波，9以后预留
	uchar		sigPRICnt;						///<信号PRI点数
	float		sigPRIMed;						///<信号PRI中值
	float		sigPRIRng;						///<信号PRI范围
	float		sigPRISeq[MAXSEQLEN];			///<信号PRI重周点序列，规定最多传8个重周
	uchar		sigPWTyp;						///<信号PW类型 0-不明，1-固定，2-变化，3以后预留
	uchar		sigPWCnt;						///<信号PW点数
	float		sigPWMed;						///<信号PW中值
	float		sigPWRng;						///<信号PW范围
	float		sigPWSeq[MAXSEQLEN];				///<信号PW脉宽点序列，规定最多传8个脉宽
}TPCSCNEMT;
//42.系统急停上报	
struct TPC_SysHaltNotify
{
	int		subSysId;								///<目标子系统ID
	char		haltDesc[512];							///<系统急停说明，风险设备描述
};
//43.1 设备自检和预位应答参数
struct DevAckPara
{
	int		devId;								///<设备Id 由设备管理分配的唯一标识；0xffffffff时表示设备全预位，子系统完成试验准备
	int		retResult;							///<设备预位执行结果 0-成功，1-失败，2以后预留
	char		errMsg[256];							///<设备预位错误描述
};
//43.自检回复	
struct TPC_SysBitReply
{
	int		subSysId;							///<目标子系统ID
	int		bitResult;							///<子系统自检结果 0-成功，1-失败，3以后预留； 所有参试设备的自检结果全部通过成功，有不通过的失败
	int		sysBitCnt;							///<设备自检结果数量N
	DevAckPara sysBitData[MAXDEVICECOUNT];			///<设备自检结果,有效数N
};
//44.加载回复	
struct TPC_ScnDldNotify
{
	int		subSysId;								///<目标子系统ID
	int		retResult;								///<执行结果 0-成功，1-失败，2以后预留
	char		errMsg[256];								///<错误描述 如果子系统执行结果返回失败，则同时返回错误描述字符串
};
//45.预位上报	
struct TPC_SysRdyNotify
{
	int		subSysId;							///<目标子系统ID
	int		retResult;							///<子系统预位结果
	int		sysRdyCnt;							///<设备自检结果数量N,每包最多32个设备，如果超出则另起一包
	DevAckPara sysRdyData[MAXDEVICECOUNT];		///<设备预位执行结果
};

//46.1 运行控制回复
struct  TPC_SysCtrlReply
{
	int		subSysId;								///<目标子系统ID
	int		retResult;								///<子系统状态查询结果 运行控制码 0—工作；1—待机；2—预留;；
};

//46.1 标校车控制状态回复
struct  TPC_BXCControlStateReply
{
	int		subSysId;								///<目标子系统ID
	int		retResult;								///<子系统状态查询结果 数据源 0—本地; 1—控制中心;；
};


//46.1 状态回复参数
struct  DevPara
{
	int		devId;							//设备Id
	char	para[512];						//参数块，根据子系统提供的xml进行格式化解析
};
//46.状态回复	
struct TPC_SysStqReply
{
	int		subSysId;								///<目标子系统ID
	int		retResult;								///<子系统状态查询结果 0 - 正常，1 - 异常，2以后预留；
	int		devCnt;									///<设备数量N
	DevPara devState[MAXDEVICECOUNT]; 				///<设备状态,数组有效数量N
};
//47.辐射闭环自检 - 频谱上报	
struct TPC_RadBitSPNotify
{
	int		subSysId;							///<目标子系统ID
	int		sigFlat;								///<信号标记 0 - 未检出，1 - 检出
	double	freqCent;							///<频率中值
	double	sigPow;								///<信号功率
	int		freqNum;								///<频点数量
	double	freqAmpl[1024];						///<频点赋值，dBm
};
//48.1 指令参数上报
struct CmdParaDef
{
	char		paraName[32];						//参数名称
	double	val;									//参数值
	char		strUnit[32];							//参数单位
};
//48.设备控制指令上报	
struct TPC_DevInstNotify
{
	int			subSysId;							///<目标子系统ID
	int			devId;								///<设备Id
	char			cmdName[64];							///<指令名称字符串
	int			cmpParaCnt;							///<指令参数数量N
	CmdParaDef	cmpPara[MAXDATACOUNT]; 				///<指令参数,数组有效数量N
};
//49.点迹上报	
struct TPC_RadPltNotify
{
	int			radId;							///<雷达Id,实际仿真雷达设备标识，0-38雷达，1-雷科雷达，2-23所雷达，3之后预留
	int			pltId;							///<点迹Id
	int			pltRecTime[7];					///<点迹时间,年,月，日，时，分，秒,毫秒
	double		pltDst;							///<点迹距离
	double		pltDop;							///<点迹多普勒
	int			vertBeamNo;						///<垂直波束号
	int			horzBeamNo;						///<水平波束号
	int			FCCnt;							///<频道数
	int			FCFlag;							///<频道标识
	int			plsGrpFlag;						///<脉组标识
	int			ERCnt;							///<EP数
	double		begDst;							///<起始距离
	double		endDst;							///<结束距离
	double		begDrc;							///<起始方位
	double		endDrc;							///<结束方位
	double		orgAD;							///<原始AD
	double		bgAD;							///<背景AD
	double		begDstRange;						///<起始距离幅度
	double		endDstRange;						///<结束距离幅度
	double		begDrcRange;						///<起始方位幅度
	double		endDrcRange;						///<结束方位幅度
	double		beamRange;						///<波束幅度
	double		fanLev;							///<扇区等级
	int			pltQuality;						///<点迹质量
	int			pltFlat;							///<点迹标志
};
//50.航迹上报	
struct TPC_RadTrkNotify
{
	int			radId;							///<雷达Id,实际仿真雷达设备标识，0-38雷达，1-雷科雷达，2-23所雷达，3之后预留
	int			trkId;							///<点迹Id
	int			trkRecTime[7];					///<点迹时间,年,月，日，时，分，秒,毫秒
	double		calDst;							///<预测距离
	double		calAzim;							///<预测方位
	int			IFFCode;							///<IFF代码
	double		observeDst;						///<观测距离
	double		observeDrc;						///<观测方位
	int			trkQuality;						///<航迹质量
	int			mod1Ans;							///<二次雷达模式1应答
	int			mod2Ans;							///<二次雷达模式2应答
	int			mod3aAns;						///<二次雷达模式3 / A应答
	double		SSRAlt;							///<二次雷达高度
};

//新  航迹
struct TPC_RadTrkNotify_n
{
	UINT32		objectID; 						//装备对象搭载平台
	UINT32		equipID; 						//装备对象ID
	UINT32		pltRecTime[5];					///<点迹时间,年,月，日，时，毫秒0-3600000000
	UINT32 		uiPlotId; 						// 点迹编号
	UINT16 		uiTrackId;  					// 航迹号
	UINT16 		tgtNo; 							// 团目标编号
	UINT8 		subNo;  						// 子目标编号
	UINT8 		traceStatus; 					// 跟踪状态 0:监视 1:粗跟 2:精跟
	UINT8 		ucTrackQuality;  				// 跟踪质量 0:外推 1:搜索 2:跟踪 3: 被动跟踪
	UINT8 		ucFollowCtrl;  					// 跟踪控制 0:正常跟踪 1:被动跟踪 2:烧穿 3:测速 4:成像
	UINT16 		waveForm;  						// 组合波形编号
	INT16 		SNR;  							// 信噪比 0.1dB量化
	INT32		amp;  							// 回波幅度 dbw
	INT32 		GR;  							// 目标距离 大地极坐标/1m（球坐标系）
	INT32 		GA;  							// 目标方位 大地极坐标/0.01度 -18000-18000
	INT32 		GE;  							// 目标俯仰 大地极坐标/0.01度 -9000-9000
	INT32 		distErr;  						// 距离误差 大地极坐标/1m
	INT32 		azErr;  						// 方位误差 大地极坐标/0.01度 -18000-18000
	INT32 		elErr;  						// 俯仰误差 大地极坐标/0.01度 -9000-9000
	INT32 		Vr;  							// 径向速度 大地极坐标/1m/s
	INT32		Va;  							// 方位速度 大地极坐标/0.01度/s
	INT32 		Ve;  							// 俯仰速度 大地极坐标/0.01度/s
	INT32 		X;  							// 航迹X/1m（东北天坐标系）
	INT32 		Y;  							// 航迹Y/1m
	INT32 		Z;  							// 航迹Z/1m
	INT32 		VX; 							// 航迹X速度/1m/s
	INT32 		VY;  							// 航迹Y速度/1m/s
	INT32 		VZ;  							// 航迹Z速度/1m/s
	INT32		lon;							///经度   -180-180
	INT32		lat;							///纬度	  -90-90
	float		alt;							///高度
	INT16 		DopV;  							// 多普勒速度
	INT16 		remain;
};

//新  点迹
struct TPC_RadPltNotify_n
{
	UINT32		objectID; 						//装备对象搭载平台
	UINT32		equipID; 						//装备对象ID
	UINT32		pltRecTime[5];					///<点迹时间,年,月，日，时，毫秒 0-3600000000
	UINT32		pltId;							///<点迹Id
	UINT16		wfmId;							/// 波形编号
	INT16		SNR;							///信噪比   0.1db
	INT32		amp; 							///回波幅度 dbw
	INT32		R;							///<点迹距离 m
	INT32		Az;							///<点迹方位  0.01 -18000-18000
	INT32		El;						///点迹俯仰 0.01  -9000-9000
	INT32		distErr; 						///距离误差 m
	INT32		azErr; 						///方位误差 0.01°	-18000-18000
	INT32		elErr; 						///俯仰误差0.01°	-9000-9000
	INT32		posX; 							///点迹x
	INT32		posY;	 						///点迹y
	INT32		posZ;	 						///点迹z
	INT32		lon;							///经度   -180-180
	INT32		lat;							///纬度	  -90-90
	float		alt;							///高度
	INT8		SFmark; 						///搜索跟踪标志 0--搜索 1--跟踪
	INT16		DopV;							///多普勒速度
	INT8		back; 							///保留
};

//51.1雷达参数波形块	
struct RadPmWfm
{
	int			wfmId;							///<波形Id：波形Id与与资源建模波形Id一致
	float		cpiTm;							///<波形相干累积处理时间：当前波形持续时间，ms
};
//51.2雷达参数波位块	
struct RadPmBwl
{
	int			bdwId;							///<波位Id：波位Id与波位图表对应关系待定，映射波束矢量
	float		dwlTm;							///<波位驻留时间：当前波位驻留时间，ms
	int			wfmNum;							///<波形数量：指当前波位内波形数量
	RadPmWfm		wfmLst[4];						///<波形列表：当前波位内波形列表，雷达波形Id与资源建模波形Id一致，波形按规定cpi时间顺序播放
};
//51.3雷达参数工作模式块	
struct RadPmWkm
{
	int			wkmId;							///<工作模式Id：这里的工作模式Id只对应空的模式名称，参数由包含波位和波形数据决定
	float		vldlTm;							///<工作模式持续时间：从上一工作模式/上报开始，到本工作模式结束/本次上报的时间，ms
	int			bdwNum;							///<波位数量：指从上一次上报到本次上报
	RadPmBwl		bdwLst[32];						///<波位列表：当前工作模式有效时间内的波位列表
};
//51.雷达参数上报
// struct TPC_RadParmNotify
// {
// 	int			pltId;							///<装备搭载平台Id
// 	int			emtId;							///<装备（辐射源）Id
// 	float		ntfPrvTm;						///<上报开始时间：即上一次上报的时间，ms
// 	float		ntfSpnTm;						///<上报区间时间：及本次上报有效持续时间，ms
// 	int			wkmNum;							///<波位数量：指从上一次上报到本次上报
// 	RadPmWkm		wkmLst[4];						///<模式列表：本次上报内的工作模式列表
// };
//52.分选上报	
typedef struct TPC_SutChsNotify
{
	int			sutPlatId;						//SUT在场景中的索引，用于多载机场景
	int			recTime[7];						//分选接收时间,年,月，日，时，分，秒,毫秒
	int			tgtBatchNum;						//目标批号
	uchar		tgtForce;						//目标敌我属性 0-未定义，1-我方，2-敌方，3-友方，4-中立，5以后预留；
	uchar		tgtPlatCat;						//目标平台类型 0-未知，1-地面固定，2-地面移动，3-水面，4-水下，5-导弹，6-固定翼，7-旋转翼，8-无人机，9-卫星，10-升空平台，12-便携，13以后预留
	uchar		tgtThreatGrade;					//目标威胁等级
	uchar		emtTyp;							//辐射源 类型0-未知，1-警戒雷达，2-对空警戒雷达，3-对海警戒雷达，4-低空警戒雷达，5-引导雷达，6-目标指示雷达，7-测高雷达，8-预警雷达，9-导弹预警雷达，10-武器控制雷达，11-炮瞄雷达，12-导弹制导雷达，13-导弹攻击雷达，14-鱼雷攻击雷达，15-多功能雷达，16-导弹末制导雷达，17-轰炸瞄准雷达，18-侦察雷达，19-战场侦察雷达，20-炮位侦察校射雷达，21-活动目标侦察校射雷达，22-航空管制雷达，23-导航雷达，24-地形跟随雷达，25-着陆引导雷达，26-港口监视雷达，27-测量雷达，28-气象雷达，29-敌我识别器，30-机载雷达，31-成像雷达
	float		tgtPos[3];						//目标位置,经度 纬度 高度
	float		tgtAzim;							//目标方位
	float		tgtElev;							//目标俯仰
	float		tgtAzimVar;						//目标方位方差
	float		tgtElevVar;						//目标俯仰方差
	float		tgtSdist;						//目标斜距
	float		tgtSdistVar;						//目标斜距方差
	float		tgtRadSpd;						//目标径向速度 正为接近，负为远离
	float		tgtTagSpd;						//目标切向速度 正为逆时针，负为顺时针
	uchar		emtCode;							//辐射幅度码
	uchar		emtWkMod;						//辐射源工作模式 0-未知，1-搜索，2-跟踪，3-制导，4-TWS，5-TAS，6以后预留
	uchar		emtPlorMod;						//辐射源极化方式 0-未知，1-左圆极化，2-右圆极化，3-垂直极化，4-水平极化，5-斜极化，6-极化可选择，7-极化编码，8-极化捷变，9-左旋椭圆极化，10-右旋椭圆极化，11以后预留
	uchar		sigFM;							//信号调制方式 0-不明，1-常规，2-非线性调频，3-线性调频，4-二相编码，5-四相编码，6-频率编码，7-频率分集，8以后预留
	float		sigScanProd;						//扫描周期
	float		beamDwlTm;						//波位驻留时间
	float		IntfDur;							//相干处理间隔
	uchar		sigState;						//信号活动状态 0-新信号，1-活动信号，2-暂时消失信号，3-消失重现信号，4-消失信号，5以后预留
	uchar		sigIntfMark;						//信号干扰标记 0-未干扰，1-有源干扰，2-无源干扰，3-有源干扰加无源干扰，4-HPECM，5以后预留
	uchar		sigFreqTyp;						//信号频率类型 0-不明，1-固定，2-组变，3-分集，4-编码，5-捷变，6-射频参差，7-连续波频率调制，8-连续波编码调制，9-连续波噪声调制，10-脉内频率编码，11以后预留
	uchar		sigFPCnt;						//信号频点数
	float		sigFreqMed;						//信号频率中值
	float		sigFreqRng;						//信号频率范围
	float		sigRFSeq[MAXSEQLEN];				//信号频点列表32个频点[(频点不足时也按此算)不考虑频率抖动带来的影响
	uchar		sigPRITyp;						//信号PRI类型 0-不明，1-固定，2-跳变，3-抖动，4-捷变，5-参差，6-编码，7-滑变，8-连续波，9以后预留
	uchar		sigPRICnt;						//信号PRI点数
	float		sigPRIMed;						//信号PRI中值
	float		sigPRISeq[MAXSEQLEN];			//信号PRI列表信号PRI重周点序列，32个PRI(PRI不足时也按此算)
	float		sigPRIRng;						//信号PRI范围
	uchar		sigPWTyp;						//信号PW类型 0-不明，1-固定，2-变化，3以后预留
	uchar		sigPWCnt;						//信号PW点数
	float		sigPWMed;						//信号PW中值
	float		sigPWRng;						//信号PW范围
	float		sigPWSeq[MAXSEQLEN];				//信号PW脉宽点序列，32个PW(PRI不足时也按此算)
}TPCSUTEPL;
//53.ECM频谱上报	
typedef struct TPC_ECMSPNotify
{
	int			subSysId;						///<目标子系统ID
	int			freqNum;							///<频谱点数N
	double		freqStart;						///<起始频点，MHz
	double		freqStop;						///<终止频点，MHz
	double		freqAmpl[1024]; 					///<频点幅度，数组有效数量N
}ECMSP;
//81.SUT事件	
struct TPC_SimSutEvent
{
	//待定
};
//82.外部平台更新驱动	
struct TPC_ExtPlatUpdate
{
	int			simTime[7];						///<上报时间,年,月，日，时，分，秒,毫秒
	int			entCnt;							///<辐射源平台数量N
	ScnPlat		emtPlat[MAXDATACOUNT];			///<辐射源平台数据块,有效数N
};
//83.外部辐射源事件驱动	
struct TPC_ExtEmtEvetn
{
	int			simTime[7];						///<上报时间,年,月，日，时，分，秒,毫秒
	int			platId;						///<平台Id
	int			emtId;						///<辐射源Id
	int			tgtMdl;						//目标模式Id:事件为模式切换时起效，目标工作模式Id
	float		antAzm;						///<波束方位
	float		antElv;						///<波束俯仰
	int			beamNo;						///<波位号
	float		scanDwlTm;					///<驻留时间
	int			trkTgtCnt;					///<跟踪目标数量N
	int			trkTgtIdLst[8];				///<跟踪目标Id列表
	char		csfNm[8];					///<自定义方向图文件名称
};
//84.1 天线定义
struct AntDef
{
	int antId;			///<天线Id
	float antAzm;		///<天线方位
	float antElv;		///<天线俯仰
	float antDwlTm;		///<驻留时间

};
//84.外部SUT天线扫描事件驱动
struct TPC_ExtSutAntScEvent
{
	int			simTime[7];					///<上报时间,年,月，日，时，分，秒,毫秒
	int			sutId;						///<Sut唯一标识，系统统一分配
	int			antCnt;						///<天线数量N
	int			AntDef[8];					///<天线列表
};

//85.DRFS预处理进度上报
struct TPC_DrfsPgrsNotify
{
	int			prePgrs;					///<进度，0-100，%
};

//86.1 地面实体姿态
struct VehicleHPR
{
	int			vehclId;						///<车辆id
	double		vehclAlt;					///<车辆高度
	double		vehclPch;					///<车辆俯仰
	double		vehclRol;					///<车辆横滚
};
//86 地面实体姿态更新
struct TPC_VehicleHPRUpt
{
	int			vechlNum;					///<车辆数量
	VehicleHPR	vechlData[MAXDATACOUNT];		///<车辆数据
};


struct BEAM_INFO
{
	INT32 iBeamAz;// 波束中心方位 量化0.1deg [-1800-1800°]
	INT32 iBeamEl;// 波束中心俯仰 量化0.1deg [-900-900°]
	UINT32 iBeamWidthA;// 波束宽度方位 量化0.1deg [0-1800]
	UINT32 iBeamWidthE;// 波束宽度俯仰 量化0.1deg [0-1800]
	UINT32 uiBeamCutTime;// 波位驻留时刻 0-搜索波形 1-跟踪波形 2-预留
	UINT8 ucWaveType;// 工作波形
	UINT8 ucAgilityType;//捷变状态 0-捷变 1-非捷变 2-预留
};
//
////雷达工作参数上报
//struct TPC_RadParmNotify
//{
//	UINT32 objectID; //装备对象搭载平台
//	UINT32 equipID; //装备对象ID
//	float uptime;  //雷达参数上报时间
//	UINT32 uiBeamCutEventNum; //波位切换事件数目
//	BEAM_INFO BeamINfoList[100];
//};


//51.1雷达波位切换上报
typedef enum eRadBmWks
{
	beam_wks_search = 0,			//搜索波形
	beam_wks_track = 1,			//跟踪波形
	beam_wks_slient = 2,			//静默
	beam_wks_reserve = 3,		//保留
};
struct RadBdwNtfPm
{
	int			bmAzim;					///<当前波位波束方位：deg，-180~180
	int			bmElev;					///<当前波位波束俯仰：deg，-90~90
	int			tmSltNo;					///<时隙编号：采用雷达上报的时隙编号
	int			bmDwlTm;					///<波位驻留时间：μs
	int			bmWks;					///<波位工作状态：采用eRadBmWks定义
};
//51.1雷达波形切换上报
typedef enum eRadWfmAgs
{
	wfm_agility_yes = 0,			//捷变
	wfm_agility_no = 1,			//非捷变
	wfm_agility_reserve = 2,		//保留
};
struct RadWfmNtfPm
{
	float		wfmFreq;;				///<波形频率：MHz
	int			wfmAgs;					///<捷变状态：按eRadWfmAgs定义
};
//51.雷达参数上报
typedef enum eRadEvtCode
{
	sim_event_sw = 0,			//开关机事件
	sim_event_wkm = 1,			//工作模式切换事件：暂不使用
	sim_event_bdw = 2,			//波位切换事件
	sim_event_wfm = 3,			//波形切换事件
	sim_event_atp = 4,			//方向图切换事件，暂不使用
	sim_event_ttk = 5,			//目标跟踪事件，暂不使用
};
struct TPC_RadParmNotify
{
	int			platId;						///<搭载平台Id，与平台更新中的Id一致
	int			emtId;						///<装备Id
	int			evtCode;						///<事件码：按eRadEvtCode定义
	int			simEvtCnt;					///<辐射源事件数量N
	int				seRadSw;					///<雷达开关机事件：0-关机，1-开机；仅是开关射频
	RadBdwNtfPm		seRadBdw[MAXDATACOUNT];	///<雷达波位切换上报
	RadWfmNtfPm		seRadWfm;				///<雷达波形切换上报
};

#pragma pack(pop)
