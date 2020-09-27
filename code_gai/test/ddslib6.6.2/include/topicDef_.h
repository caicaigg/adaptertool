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

#pragma pack(push, 4)

//Topic数据长度
const unsigned int G_TDS_SysBitRequest = 140;			//系统/设备自检
const unsigned int G_TDS_SysResetRequest = 136;			//系统/设备复位
const unsigned int G_TDS_RadBitRFRequest = 40;			//辐射闭环自检-射频
const unsigned int G_TDS_RadBitSDRequest = 40;			//辐射闭环自检-频谱
const unsigned int G_TDS_ScnDldRequest = 24;			//场景启动加载
const unsigned int G_TDS_SysCtrlRequest = 36;			//系统运行控制
const unsigned int G_TDS_SysStqRequest = 4;				//系统/设备状态查询
const unsigned int G_TDS_ScnPlatUpdate = 3084;			//场景平台数据更新
const unsigned int G_TDS_ScnEmtEvent = 1672;			//场景辐射源事件
const unsigned int G_TDS_ScnWpnEvent = 520;				//场景武器事件
const unsigned int G_TDS_RPScnPlatUpdate = 3084;		//场景回放平台数据更新
const unsigned int G_TDS_RPScnEmtEvent = 1672;			//场景回放辐射源事件
const unsigned int G_TDS_RPScnWpnEvent = 520;			//场景回放武器事件
const unsigned int G_TDS_ScnDatMixNotify = 232;			//场景辐射源融合数据
const unsigned int G_TDS_SysBitReply = 16524;			//系统/设备自检回复
const unsigned int G_TDS_ScnDldNotify = 260;			//场景启动加载回复
const unsigned int G_TDS_SysRdyNotify = 268;			//系统预位上报
const unsigned int G_TDS_SysStqReply = 16524;			//系统/设备状态查询回复
const unsigned int G_TDS_RadBitSPNotify = 8200;			//辐射闭环自检-频谱上报
const unsigned int G_TDS_DevInstNotify = 2384;			//设备控制指令上报
const unsigned int G_TDS_RadPltNotify = 184;			//雷达点迹上报
const unsigned int G_TDS_RadTrkNotify = 104;			//雷达航迹上报
const unsigned int G_TDS_RadParmNotify = 56;			//雷达工作参数上报
const unsigned int G_TDS_SutChsNotify = 264;			//SUT分选数据上报
const unsigned int G_TDS_SimSutEvent = 1;				//SUT仿真事件（预留）

//1.系统自检
struct TPC_SysBitRequest
{
	int subSysId;					///<目标子系统ID
	int bitMdl;						///<自检方式 0-上电自检，1-维护自检
	int bitDevCnt;					///<自检设备数量N
	int devId[MAXDEVICECOUNT];		///<设备Id,有效数N
};
//2.系统复位
struct TPC_SysResetRequest
{
	int subSysId;					///<目标子系统ID
	int resetDevCnt;				///<复位设备数量N
	int devId[MAXDEVICECOUNT];		///<设备Id,有效数N
};

//3.辐射闭环自检 - 信号辐射			
struct TPC_RadBitRFRequest
{
	int		subSysId;					///<目标子系统ID
	int		devId;						///<设备Id
	int		sigRFSw;					///<射频开关 1-开射频，0-关射频
	int		sigMod;						///<信号样式 0-连续波，1-脉冲
	double	plsFreq;					///<频率
	double	plsPrd;						///<重复周期
	double	plsPW;						///<脉宽
};
//4.辐射闭环自检 - 信号监测			
struct TPC_RadBitSDRequest
{
	int		subSysId;					///<目标子系统ID
	int		bStart;						///<频谱上报 1-开始，0-停止
	int		sigMod;						///<信号样式  0-连续波，1-脉冲
	double	plsCntFreq;					///<中心频率	 400-18000
	double	montPlsBW;					///<监测带宽
	double	freqRes;					///<频率分辨率
};
//5.启动加载
struct TPC_ScnDldRequest
{
	int subSysId;						///<目标子系统ID
	int scnId;							///<场景ID
	int scnFileMD5[4];					///<xml文件MD5，用作文件完整性校验
};
//6.运行控制
struct TPC_SysCtrlRequest
{
	int subSysId;						///<目标子系统ID
	int cmdCode;						///<命令码：0-开始，1-结束，2-暂停，3-恢复，4以后预留；暂停/恢复比较复杂，还需进一步讨论
	int excTime[6];						///<执行时间：年,月，日，时，分，秒
	int tskId;							///<试验任务Id
};
//7.状态查询
struct TPC_SysStqRequest
{
	int subSysId;						///<目标子系统ID
};
//8.1 平台数据
struct ScnPlat
{
	int	  plat_id;					///<平台Id
	float lon;						///< 经度
	float lat;						///< 纬度
	float alt;						///< 高度
	float hdg;						///< 偏航 站心直角（东北天）坐标系下，机体矢量与坐标系平面夹角
	float pch;						///< 俯仰
	float rol;						///< 横滚
	float spdEast;					///<速度东向 站心直角（东北天）坐标系，东向速度，东正西负
	float spdNorth;					///<速度北向
	float spdUp;					///<速度天向
	float accEast;					///<加速度东向
	float accorth;					///<加速度北向
	float accUp;					///<加速度天向
	float ROThdg;					///<角速度偏航
	float ROTpch;					///<角速度俯仰
	float ROTrol;					///<角速度横滚
};
//8.场景平台更新
struct TPC_ScnPlatUpdate
{
	int		simNo;					///<场景仿真节拍序号
	int		sunPlatCnt;				///<SUT平台数量M 1-16
	ScnPlat sutPlat[16];			///<SUT平台数据块,有效数M
	int		emtPlatCnt;				///<辐射源平台数量N 1-1024
	ScnPlat emtPlat[MAXDATACOUNT];	///<辐射源平台数据块,有效数N
};
//9.1辐射源事件
struct EmtEvtAttr
{
	int platId;						//搭载平台Id，与平台更新中的Id一致
	int	emtId;						//辐射源Id
	int entCode;					//事件码,0:关机，2：模式切换，3：跟踪目标切换，4：预留
	int tgtMdl;						//目标模式Id:事件为模式切换时起效，目标工作模式Id
	int trkTgtCnt;					//跟踪目标数量
	int trkTgtIdLst[8];				//跟踪目标id列表
};
//9.辐射源事件	
struct TPC_ScnEmtEvent
{
	int			simNo;						///<场景仿真节拍序号
	int			emtEvtCnt;					///<辐射源事件数量N
	EmtEvtAttr	emtEvt[MAXDATACOUNT];		///<辐射源事件项,有效数N
};
//10.1武器事件事件项
struct WpnEvtAttr
{
	int	ownPlatId;					//搭载平台Id
	int tgtPlatId;					//目标平台Id
	int wpnId;						//武器Id
	int evtId;						//事件Id 0-发射，1-爆炸，2以后预留；
};
//10.武器事件	
struct TPC_ScnWpnEvent
{
	int			simNo;				///<场景仿真节拍序号
	int			wpnEvtCnt;				///<武器事件数量N
	WpnEvtAttr	wpnEvt[MAXDATACOUNT];		///<武器事件,有效数N
};
//11.回放 - 场景平台更新	
struct TPC_RPScnPlatUpdate
{
	int		simNo;					///<场景仿真节拍序号
	int		sunPlatCnt;				///<SUT平台数量M 1-16
	ScnPlat sutPlat[16];			///<SUT平台数据块,有效数M
	int		emtPlatCnt;				///<辐射源平台数量N 
	ScnPlat emtPlat[MAXDATACOUNT];			///<辐射源平台数据块,有效数N
};
//12.回放 - 辐射源事件	
struct TPC_RPScnEmtEvent
{
	int			simNo;				///<场景仿真节拍序号
	int			emtEvtCnt;			///<辐射源事件数量N
	EmtEvtAttr	emtEvt[MAXDATACOUNT];		///<辐射源事件项,有效数N
};
//13.回放 - 武器事件	
struct TPC_RPScnWpnEvent
{
	int			simNo;				///<场景仿真节拍序号
	int			wpnEvtCnt;				///<武器事件数量N
	WpnEvtAttr	wpnEvt[MAXDATACOUNT];		///<武器事件,有效数N
};
//////////////////////////////////////////////////////////////////////////
//回复数据
//14.场景辐射源融合上报消息
typedef struct TPC_ScnDatMixNotify
{
	//int			simNo;							///<场景仿真节拍序号
	int			simTime[7];						///<仿真时间,年,月，日，时，分，秒,毫秒
	int			platId;							///<平台Id
	int			emtId;							///<辐射源Id
	int			platForce;						///<平台敌我属性 0-未定义，1-我方，2-敌方，3-友方，4-中立，5以后预留；
	int			platCat;						///<平台类型 0-未知，1-地面固定，2-地面移动，3-水面，4-水下，5-导弹，6-固定翼，7-旋转翼，8-无人机，9-卫星，10-升空平台，12-便携，13以后预留
	int			emtTyp;							///<辐射源 类型0-未知，1-警戒雷达，2-对空警戒雷达，3-对海警戒雷达，4-低空警戒雷达，5-引导雷达，6-目标指示雷达，7-测高雷达，8-预警雷达，9-导弹预警雷达，10-武器控制雷达，11-炮瞄雷达，12-导弹制导雷达，13-导弹攻击雷达，14-鱼雷攻击雷达，15-多功能雷达，16-导弹末制导雷达，17-轰炸瞄准雷达，18-侦察雷达，19-战场侦察雷达，20-炮位侦察校射雷达，21-活动目标侦察校射雷达，22-航空管制雷达，23-导航雷达，24-地形跟随雷达，25-着陆引导雷达，26-港口监视雷达，27-测量雷达，28-气象雷达，29-敌我识别器，30-机载雷达，31-成像雷达
	double		platPos[3];						///<平台位置,经度 纬度 高度
	double		platAzim;						///<平台方位
	double		platElev;						///<平台俯仰
	double		platSdist;						///<平台斜距
	double		tgtRadSpd;						///<目标径向速度 正为接近，负为远离
	double		tgtTagSpd;						///<目标切向速度 正为逆时针，负为顺时针
	double		sigPowCode;						///<信号功率码  dBm - 120 - 100
	int			emtWkMod;						///<辐射源工作模式 0-未知，1-搜索，2-跟踪，3-制导，4-TWS，5-TAS，6以后预留
	int			emtPlorMod;						///<辐射源极化方式 0-未知，1-左圆极化，2-右圆极化，3-垂直极化，4-水平极化，5-斜极化，6-极化可选择，7-极化编码，8-极化捷变，9-左旋椭圆极化，10-右旋椭圆极化，11以后预留
	int			sigFM;							///<信号调制方式 0-不明，1-常规，2-非线性调频，3-线性调频，4-二相编码，5-四相编码，6-频率编码，7-频率分集，8以后预留
	double		sigScanProd;					///<扫描周期
	double		beamDwlTm;						///<波位驻留时间
	double		IntfDur;						///<相干处理间隔
	int			sigRFTyp;						///<信号频率类型 0-不明，1-固定，2-组变，3-分集，4-编码，5-捷变，6-射频参差，7-连续波频率调制，8-连续波编码调制，9-连续波噪声调制，10-脉内频率编码，11以后预留
	int			sigRFCnt;						///<信号频点数
	double		sigRFMed;						///<信号频率中值
	double		sigRFRng;						///<信号频率范围
	int			sigPRITyp;						///<信号PRI类型 0-不明，1-固定，2-跳变，3-抖动，4-捷变，5-参差，6-编码，7-滑变，8-连续波，9以后预留
	int			sigPRICnt;						///<信号PRI点数
	double		sigPRIMed;						///<信号PRI中值
	double		sigPRIRng;						///<信号PRI范围
	int			sigPWTyp;						///<信号PW类型 0-不明，1-固定，2-变化，3以后预留
	int			sigPWCnt;						///<信号PW点数
	double		sigPWMed;						///<信号PW中值
	double		sigPWRng;						///<信号PW范围
}TPCSCNEMT;
//15.1 设备参数
struct  DevPara
{
	int  devId;							//设备Id
	int	 bitResult;						///<设备自检/运行状态结果 0-成功，1-失败，3以后预留； 
	char para[512];						//参数块，根据子系统提供的xml进行格式化解析
};
//15.自检回复	
struct TPC_SysBitReply
{
	int		subSysId;							///<目标子系统ID
	int		sysBitCnt;							///<设备自检结果数量N
	DevPara sysBitData[MAXDEVICECOUNT];			///<设备自检结果,有效数N
};
//16.加载回复	
struct TPC_ScnDldNotify
{
	int subSysId;								///<目标子系统ID
	int retResult;								///<执行结果 0-成功，1-失败，2以后预留
	char errMsg[256];							///<错误描述 如果子系统执行结果返回失败，则同时返回错误描述字符串
};
//17.预位上报	
struct TPC_SysRdyNotify
{
	int subSysId;								///<目标子系统ID
	int devId;									///<设备Id 由设备管理分配的唯一标识；0xffffffff时表示设备全预位，子系统完成试验准备
	int retResult;								///<执行结果 0-成功，1-失败，2以后预留
	char errMsg[256];							///<错误描述 如果子系统执行结果返回失败，则同时返回错误描述字符串
};
//18.状态回复	
struct TPC_SysStqReply
{
	int subSysId;								///<目标子系统ID
	int retResult;								///<子系统状态查询结果 0 - 正常，1 - 异常，2以后预留；
	int	devCnt;									///<设备数量N
	DevPara devState[MAXDEVICECOUNT]; 			///<设备状态,数组有效数量N
};
//19.辐射闭环自检 - 频谱上报	
struct TPC_RadBitSPNotify
{
	int subSysId;								///<目标子系统ID
	int	devCnt;									///<频谱点数N
	double FreqRange[1024]; 					///<频点幅度,数组有效数量N
};
//20.1 指令参数
struct CmdParaDef
{
	char	paraName[32];						//参数名称
	double	val;								//参数值
	char	strUnit[32];						//参数单位
};
//20.设备控制指令上报	
struct TPC_DevInstNotify
{
	int			subSysId;							///<目标子系统ID
	int			devId;								///<设备Id
	char		cmdName[64];						///<指令名称字符串
	int			cmpParaCnt;							///<指令参数数量N
	CmdParaDef	cmpPara[MAXDATACOUNT]; 				///<指令参数,数组有效数量N
};
//21.点迹上报	
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
	double		begDstRange;					///<起始距离幅度
	double		endDstRange;					///<结束距离幅度
	double		begDrcRange;					///<起始方位幅度
	double		endDrcRange;					///<结束方位幅度
	double		beamRange;						///<波束幅度
	double		fanLev;							///<扇区等级
	int			pltQuality;						///<点迹质量
	int			pltFlat;						///<点迹标志
};
//22.航迹上报	
struct TPC_RadTrkNotify
{
	int			radId;							///<雷达Id,实际仿真雷达设备标识，0-38雷达，1-雷科雷达，2-23所雷达，3之后预留
	int			trkId;							///<点迹Id
	int			trkRecTime[7];					///<点迹时间,年,月，日，时，分，秒,毫秒
	double		calDst;							///<预测距离
	double		calAzim;						///<预测方位
	int			IFFCode;						///<IFF代码
	double		observeDst;						///<观测距离
	double		observeDrc;						///<观测方位
	int			trkQuality;						///<航迹质量
	int			mod1Ans;						///<二次雷达模式1应答
	int			mod2Ans;						///<二次雷达模式2应答
	int			mod3aAns;						///<二次雷达模式3 / A应答
	double		SSRAlt;							///<二次雷达高度
};
//23.雷达参数上报	
struct TPC_RadParmNotify
{
	int			radId;							///<雷达Id,实际仿真雷达设备标识，0-38雷达，1-雷科雷达，2-23所雷达，3之后预留
	int			trkId;							///<点迹Id
	int			recTime[7];						///<点迹时间,年,月，日，时，分，秒,毫秒
	int			OpModId;						///<工作模式Id
	int			freqCode;						///<频率码
	int			syncPulse;						///<同步脉冲
	double		ISR;							///<干信比

};
//24.分选上报	
typedef struct TPC_SutChsNotify
{
	int			sutPlatId;						///<SUT在场景中的索引，用于多载机场景
	int			recTime[7];						///<分选接收时间,年,月，日，时，分，秒,毫秒
	int			tgtBatchNum;					///<目标批号
	int			tgtForce;						///<目标敌我属性 0-未定义，1-我方，2-敌方，3-友方，4-中立，5以后预留；
	int			tgtPlatCat;						///<目标平台类型 0-未知，1-地面固定，2-地面移动，3-水面，4-水下，5-导弹，6-固定翼，7-旋转翼，8-无人机，9-卫星，10-升空平台，12-便携，13以后预留
	int			tgtThreatGrade;					///<目标威胁等级
	int			emtTyp;							///<辐射源 类型0-未知，1-警戒雷达，2-对空警戒雷达，3-对海警戒雷达，4-低空警戒雷达，5-引导雷达，6-目标指示雷达，7-测高雷达，8-预警雷达，9-导弹预警雷达，10-武器控制雷达，11-炮瞄雷达，12-导弹制导雷达，13-导弹攻击雷达，14-鱼雷攻击雷达，15-多功能雷达，16-导弹末制导雷达，17-轰炸瞄准雷达，18-侦察雷达，19-战场侦察雷达，20-炮位侦察校射雷达，21-活动目标侦察校射雷达，22-航空管制雷达，23-导航雷达，24-地形跟随雷达，25-着陆引导雷达，26-港口监视雷达，27-测量雷达，28-气象雷达，29-敌我识别器，30-机载雷达，31-成像雷达
	double		tgtPos[3];						///<目标位置,经度 纬度 高度
	double		tgtAzim;						///<目标方位
	double		tgtElev;						///<目标俯仰
	double		tgtAzimVar;						///<目标方位方差
	double		tgtElevVar;						///<目标俯仰方差
	double		tgtSdist;						///<目标斜距
	double		tgtSdistVar;					///<目标斜距方差
	double		tgtRadSpd;						///<目标径向速度 正为接近，负为远离
	double		tgtTagSpd;						///<目标切向速度 正为逆时针，负为顺时针
	int			emtCode;						///<辐射幅度码
	int			emtWkMod;						///<辐射源工作模式 0-未知，1-搜索，2-跟踪，3-制导，4-TWS，5-TAS，6以后预留
	int			emtPlorMod;						///<辐射源极化方式 0-未知，1-左圆极化，2-右圆极化，3-垂直极化，4-水平极化，5-斜极化，6-极化可选择，7-极化编码，8-极化捷变，9-左旋椭圆极化，10-右旋椭圆极化，11以后预留
	int			sigFM;							///<信号调制方式 0-不明，1-常规，2-非线性调频，3-线性调频，4-二相编码，5-四相编码，6-频率编码，7-频率分集，8以后预留
	double		sigScanProd;					///<扫描周期
	double		beamDwlTm;						///<波位驻留时间
	double		IntfDur;						///<相干处理间隔
	int			sigState;						///<信号活动状态 0-新信号，1-活动信号，2-暂时消失信号，3-消失重现信号，4-消失信号，5以后预留
	int			sigIntfMark;					///<信号干扰标记 0-未干扰，1-有源干扰，2-无源干扰，3-有源干扰加无源干扰，4-HPECM，5以后预留
	int			sigFreqTyp;						///<信号频率类型 0-不明，1-固定，2-组变，3-分集，4-编码，5-捷变，6-射频参差，7-连续波频率调制，8-连续波编码调制，9-连续波噪声调制，10-脉内频率编码，11以后预留
	int			sigFPCnt;						///<信号频点数
	double		sigFreqMed;						///<信号频率中值
	double		sigFreqRng;						///<信号频率范围
	int			sigPRITyp;						///<信号PRI类型 0-不明，1-固定，2-跳变，3-抖动，4-捷变，5-参差，6-编码，7-滑变，8-连续波，9以后预留
	int			sigPRICnt;						///<信号PRI点数
	double		sigPRIMed;						///<信号PRI中值
	double		sigPRIRng;						///<信号PRI范围
	int			sigPWTyp;						///<信号PW类型 0-不明，1-固定，2-变化，3以后预留
	int			sigPWCnt;						///<信号PW点数
	double		sigPWMed;						///<信号PW中值
	double		sigPWRng;						///<信号PW范围
}TPCSUTEPL;
//25.SUT事件	
struct TPC_SimSutEvent
{
	//待定
};

#pragma pack(pop)
