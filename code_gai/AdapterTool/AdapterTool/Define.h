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

//DDS ���ն��У����Ͷ���
struct BaseType
{
	int type;
	void *data;
};
typedef boost::shared_ptr<BaseType> BaseTypePtr;


//������Ϣ
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

//��������
struct LVCEntityInfo
{
	int id;
	std::string name;
	InitStateInfo initState;
	std::vector<EquipInfo> equipList;
};

//�����ļ����� 
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

//���߰�װ����
struct AtnAchParam
{
	int atnArrayID;
	std::vector <antennal> params;
};

//�״���Ϣ
struct RadarInfo
{
	int id;
	std::string name;
	std::string desc;
	AtnAchParam AtnAchParamList;
};
typedef std::vector<RadarInfo> RadarInfoVec;

//ӳ���豸
struct MapEquip
{
	int subid;
	int subtype;
	std::string subname;
	std::string desc;
};

//����ӳ���ϵ
struct LVCEntityMapInfo
{
	int id;
	std::string name;
	std::vector<MapEquip> MapQuipList;
};
typedef std::vector<LVCEntityMapInfo> LVCEntityMapInfoVec;

//TCP ���ݽṹ
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

//// #define _LVC_DM_TXCX		 0X0001		//ͨ�Ų�ѯ:			�˹�������ϵͳ��������Զ�����߼���·״̬ʱ�·�
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