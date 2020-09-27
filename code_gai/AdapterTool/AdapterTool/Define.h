#pragma once
#include <string>
#include <boost/shared_ptr.hpp>

#include "Definedds.h"
#include "Definetcp.h"
#include "topicDef.h"

#define SIZE_UNCHAR sizeof(unsigned char)
#define SIZE_UNSHORT sizeof(unsigned short)
#define MSGHEADER (9*SIZE_UNSHORT+2*SIZE_UNCHAR)
#define MSGEND (2*SIZE_UNSHORT)




#define TOPIC_S_SysResetRequest "SysResetRequest1"
#define TOPIC_S_SysHaltRequest "SysHaltRequest"
#define TOPIC_S_SYSBITREQUEST "SysBitRequest"
#define TOPIC_S_ScnDldRequest "ScnDldRequest"
#define TOPIC_S_SysRdyRequest "SysRdyRequest"
#define TOPIC_S_SysModeSet "SysModeSet"
#define TOPIC_S_SysCtrlRequest "SysCtrlRequest"
#define TOPIC_S_SysStqRequest "SysStqRequest"
#define TOPIC_S_ScnPlatUpdate "ScnPlatUpdate"
#define TOPIC_S_ScnEventUpdate "ScnEventUpdate"
#define TOPIC_S_OwnInsUpdate "OwnInsUpdate"
#define TOPIC_S_ScnMixUpdate "ScnMixUpdate"

#define TOPIC_P_SysResetReply "SysResetReply"
#define TOPIC_P_SysHaltNotify "SysHaltNotify"
#define TOPIC_P_SysBitReply "SysBitReply"
#define TOPIC_P_SysDldNotify "ScnDldNotify"
#define TOPIC_P_SysRdyNotify "SysRdyNotify"
#define TOPIC_P_SysModeReply "SysModeReply"
#define TOPIC_P_SysCtrlReply "SysCtrlReply"
#define TOPIC_P_SysStqReply "SysStqReply"
#define TOPIC_P_RadEventReport "RadEventReport"
#define TOPIC_P_RadPltReport "RadPltReport"
#define TOPIC_P_RadTrkReport "RadTrkReport"
#define TOPIC_P_EwEventReport "EwEventReport"
#define TOPIC_P_EwSortReport "EwSortReport"
#define TOPIC_P_EwSpecReport "EwSpecReport"
#define TOPIC_P_EwPDWReport "EwPDWReport"
#define TOPIC_P_EwTgtLocReport "EwTgtLocReport"
#define TOPIC_P_ReportSysStop "ReportSysStop"
#define TOPIC_P_RadParmNotify "RadParmNotify"


typedef std::vector<char> buffer_type;

//DDS 接收队列，类型定义
struct BaseType
{
	int type;
	void *data;
};
typedef boost::shared_ptr<BaseType> BaseTypePtr;


//场景信息
struct LVCScenBaseInfo
{

};

struct InitStateInfo
{
	double lon;
	double lat;
	double alt;
	double Heading;
	double pitch;
	double roll;
	double speed;
};

struct EquipInfo
{
	int id;
};

//场景兵力
struct LVCEntityInfo
{
	int id;
	std::string name;
	InitStateInfo initState;
	std::vector<EquipInfo> equipList;
};

//场景文件解析 
struct LVCScenarioFile
{
	LVCScenBaseInfo _Sceninfo;
	std::vector<LVCEntityInfo> _Entitylist;
};

struct antennal
{
	int x;
	int y;
	int z;
	double heading;
	double pitch;
	double roll;
};

//天线安装参数
struct AtnAchParam
{
	int atnArrayID;
	std::vector <antennal> params;
};

//雷达信息
struct RadarInfo
{
	int id;
	std::string name;
	std::string desc;
	AtnAchParam AtnAchParamList;
};
typedef std::vector<RadarInfo> RadarInfoVec;

//映射设备
struct MapEquip
{
	int subid;
	int subtype;
	std::string subname;
	std::string desc;
};

//兵力映射关系
struct LVCEntityMapInfo
{
	int id;
	std::string name;
	std::vector<MapEquip> MapQuipList;
};
typedef std::vector<LVCEntityMapInfo> LVCEntityMapInfoVec;

//TCP 数据结构
//class DataTypeBase /*: public boost::enable_shared_from_this<CBase>*/
//{
//public:
//	DataTypeBase()
//	{}
//	virtual ~DataTypeBase()
//	{}
//	int DataType;
//};
//typedef boost::shared_ptr<DataTypeBase> DataTypeBaseptr;
//
//class SelfCheck : public DataTypeBase
//{
//public:
//	SelfCheck() {}
//	virtual ~SelfCheck() {}
//	
//	int i;
//};
//typedef boost::shared_ptr<SelfCheck> SelfCheckptr;
//
//class LaunchLoad : public DataTypeBase
//{
//public:
//	LaunchLoad()
//		:strtime("123359")
//	{}
//	virtual ~LaunchLoad()
//	{}
//	std::string strtime;
//};
//typedef boost::shared_ptr<LaunchLoad> LaunchLoadptr;

//// #define _LVC_DM_TXCX		 0X0001		//通信查询:			人工操作或系统控制软件自动检查逻辑链路状态时下发
//
//// struct SMessageFormat
//// {
//// 	int type;
//};
//
//struct DMCommunicationQueryPackage
//{
//
//};