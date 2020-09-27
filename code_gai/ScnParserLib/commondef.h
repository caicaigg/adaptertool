/***********************************************************************
  commondef.h:  interface for the composite data structure definition.
************************************************************************/
#ifndef _COMMONDEF_H_
#define _COMMONDEF_H_

#include "typedef.h"

///////////////////////////////////////////////////////////
// Macro Definition
///////////////////////////////////////////////////////////

//测试命令报文
#define DEBUG_PACK_CODE    		0x1234

#define MAX_ANTENNA_NUM			8
#define MAX_RFBAND_NUM			8

///////////////////////////////////////////////////////////
// Structure Definition
///////////////////////////////////////////////////////////

//射频频段划分
typedef enum
{
	RADIO_BAND_P				= 0,			//P波段 : 230~1000MHz
	RADIO_BAND_L				= 1,			//L波段 : 1GHz~2GHz
	RADIO_BAND_S				= 2,			//S波段 : 2GHz~4GHz
	RADIO_BAND_C				= 3,			//C波段 : 4GHz~8GHz
	RADIO_BAND_X				= 4,			//X波段 : 8GHz~12GHz
	RADIO_BAND_KU				= 5,			//Ku波段: 12GHz~18GHz
	RADIO_BAND_K				= 6,			//K波段 : 18GHz~26.5GHz
	RADIO_BAND_KA				= 7,			//Ka波段: 26.5GHz~40GHz
	RADIO_BAND_NUM				= 8,			//波段数量
};

//平台RCS参数表
typedef struct _PLT_RCS_
{
	FLOAT			rcs_head[RADIO_BAND_NUM];	//前向RCS(按照P/L/S/C/X/Ku/K/Ka波段划分)
	FLOAT			rcs_side[RADIO_BAND_NUM];	//侧向RCS
	FLOAT			rcs_rear[RADIO_BAND_NUM];	//后向RCS
}PLT_RCS;

//空间坐标矢量
typedef struct _VEC_POS_
{
	//经纬高坐标系
	DOUBLE			lon;						//经度，单位: °
	DOUBLE			lat;						//纬度，单位: °
	DOUBLE			alt;						//高度，单位: m

	//东北天坐标系
	DOUBLE			east;						//东向距离
	DOUBLE			north;						//北向距离
	DOUBLE			sky;						//天向距离

	//方位-俯仰-距离坐标系
	DOUBLE			azim;						//方位
	DOUBLE			pitch;						//俯仰
	DOUBLE			range;						//距离
	
}VEC_POS;

//空间姿态矢量(球坐标)
typedef struct _VEC_DIR_
{
	DOUBLE			jaw;						//偏航，单位: °(以正北为起点顺时针旋转)
	DOUBLE			pitch;						//俯仰，单位: °(上仰为正，下俯为负)
	DOUBLE			roll;						//横滚，单位: °(以水平航向为零度，左负右正)
	
}VEC_DIR;

//平台实体
typedef struct _PLT_ENTITY_
{
	//平台属性
	DWORD			nID;  				//平台ID
	DWORD			platType;			//平台类型: 0-未知，1-地面固定，2-车载，3-便携，4-舰(船)载，5-机载
										//       6-直升机载，7-无人机载，8-弹载，9-星载
	DWORD			enemyAttr;			//敌我属性: 0-未知，1-敌方，2-我方，3-中立
	CHAR			strPrompt[256];		//平台描述

	//平台位置
	DOUBLE			longitude;			//经度，单位: °
	DOUBLE			latitude;			//纬度，单位: °
	DOUBLE			altitude;			//高度，单位: m

	//平台姿态
	DOUBLE			course;				//航向，单位: °(以正北为起点顺时针旋转)
	DOUBLE			pitch;				//俯仰，单位: °(上仰为正，下俯为负)
	DOUBLE			across;				//横滚，单位: °(以水平航向为零度，左负右正)

	//平台速度
	DOUBLE			v_east;				//东向速度，单位: m/s
	DOUBLE			v_north;			//北向速度，单位: m/s
	DOUBLE			v_sky;				//天向速度，单位: m/s

	//平台RCS
	PLT_RCS			rcsTable;			//平台RCS参数表
}PLT_ENTITY;

#pragma pack(push, 4)

//用户文件
typedef struct _USR_FILE_
{
	DWORD			usrFileID;			//文件ID
	CHAR			usrFilePath[256];	//文件路径名称
	DWORD			usrFileMD5;			//文件校验码
	
}USR_FILE;

//几何安装参数
typedef struct _ATN_INST_
{
	DOUBLE			pos_x;				//天线安装位置X（右），平台机体坐标系（质心零点）
	DOUBLE			pos_y;				//天线安装位置Y（前），平台机体坐标系（质心零点）
	DOUBLE			pos_z;				//天线安装位置Z（上），平台机体坐标系（质心零点）

	DOUBLE			alpha;				//天线安装方位角，平台机体坐标系
	DOUBLE			theta;				//天线安装俯仰角，平台机体坐标系
	DOUBLE			gamma;				//天线安装旋转角，平台机体坐标系
	
}ATN_INST;

//工作频段参数
typedef struct _RF_BAND_
{
	DOUBLE			rfStart;			//起始频率，单位: MHz
	DOUBLE			rfStop;				//结束频率，单位: MHz
	
}RF_BAND;

//天线安装参数
typedef struct _ATN_ARR_PARAM_
{
	DWORD			atnArrayID;			//天线阵ID
	DWORD			atnArrayNum;		//天线单元数量
	ATN_INST		antenna[MAX_ANTENNA_NUM];
		
}ATN_ARR_PARAM;

//收发通道参数
typedef struct _TR_CHAN_PARAM_
{
	DWORD			chanID;				//通道ID
	DOUBLE			emtPwr;				//发射机峰值功率
	DOUBLE			rcvNF;				//接收机噪声系数

	DWORD			enAPM;				//自适应功率管控使能标志
	DOUBLE			rangeAMP;			//自适应功率调整范围

	DWORD			nBand;				//工作频段数量
	RF_BAND			rfBand[MAX_RFBAND_NUM];
	
}TR_CHAN_PARAM;

//雷达工作模式
typedef struct _RDS_WORK_MODE_
{
	DWORD			modeID;				//工作模式ID
	DWORD			modeType;			//工作模式类型: 0-未知，1-搜索，2-跟踪，3-制导，4-TWS，5-TAS，6以后预留

}RDS_WORK_MODE;

//雷达对象模型
typedef struct _RDS_OBJ_
{
	DWORD			radarID;			//雷达对象ID
	CHAR			radarName[64];		//雷达对象名称
	CHAR			radarDesc[256];		//雷达对象描述

	DWORD			type;				//对象类别
	DWORD			platform;			//搭载平台
	DWORD			prio;				//对象优先级
	
	DWORD			initWorkModeID;		//初始工作模式ID
	DWORD			startRunTime;		//开机时间
	USR_FILE 		devConfigFile;		//设备配置文件
	DOUBLE			powerRange;			//雷达威力范围

	ATN_ARR_PARAM	atnArrayParam;		//天线安装参数
	TR_CHAN_PARAM	trChanParam;		//收发通道参数

	DWORD			nWorkMode;			//工作模式数量
	RDS_WORK_MODE*	pWorkMode;			//雷达工作模式参数
		
}RDS_OBJ;

#pragma pack(pop)

#endif