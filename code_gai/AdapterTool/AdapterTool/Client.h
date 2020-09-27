#pragma once
#include "TcpConnectClient.h"

#include <boost/thread.hpp>

#include "Define.h"

#define VERSION_LVC29 1
#define PROPERTY_LVC29 0
#define CHECKCODE_LVC29 0
#define ENDCODE_LVC29 0x0a0d


////////////////////////////////////////////////////
/// <summary> 雷达TCP通信封装接口   </summary>
///  
/// <remarks>   吴俊霖  </remarks>
////////////////////////////////////////////////////


class RadarClient :
	public CTcpConnectClient
{
public:
	RadarClient();
	~RadarClient();

public:
		
	/// <summary>	初始化ip port，接收线程. </summary> wujl
	bool Initialize();

	/// <summary>	解析包头. </summary> wujl 
	void TransferHead(SMessageFormat& Head, const buffer_type & buffer);

	/// <summary>	打包. </summary> wujl 
	void Pack(SMessageFormat& Head, char * PackInfo);

	
public:

	/// <summary>	发送通信查询. </summary> wujl
	void sendDMCommunicationQueryPackage(const DMCommunicationQueryPackage CommunicationQuery);

	/// <summary>	发送系统自检. </summary> wujl
	void sendDMSystemSelfCheckPackage(const DMSystemSelfCheckPackage SelfCheck);

	/// <summary>	发送雷达初始化配置. </summary> wujl
	void sendDMRadarInitConfigPackage(const CENTER2RADAR_INIT RadarInit);

	/// <summary>	发送雷达坐标查询. </summary> wujl
	void sendDMRadarLocationQueryPackage(const DMRadarLocationQueryPackage LocationQuery);

	/// <summary>	发送运行控制. </summary> wujl
	void sendDMRunControlPackage(const DMRunControlPackage RunControl);

	/// <summary>	发送标校车初始化配置. </summary> wujl
	//void sendDMAalibrationMarkCarInitPackage(const DMAalibrationMarkCarInitPackage AMCInit);

	/// <summary>	发送实时目标参数. </summary> wujl
	void sendDMTargetRealTimePackage(const DMTargetRealTimePackage Targets);


private:
	bool tryTransferHead(const buffer_type & buffer);

protected:

	/// <summary>	接收数据处理. </summary> wujl 
	void TcpRecvDataFunction(const buffer_type& str);

	/// <summary>	周期通信查询线程. </summary> wujl
	void CheckFunction_Thread();

	/// <summary>	周期数据处理线程. </summary> wujl
	void DataFunction_Thread();
private:
	void ReportEvent(int EventCommand);

private:
	virtual void run();

private:
	boost::thread * _Recvthread;
	char _deal_buf[1024];
	int _deal_buflen;

	boost::shared_ptr<boost::thread> _CheckThread;
	HANDLE _CheckComSemaphore;

	boost::shared_ptr<boost::thread> _DataThread;
	HANDLE _DataSemaphore;
};


#include "UDPConnectClient.h"
////////////////////////////////////////////////////
/// <summary>  //标校车tcp通信接口  </summary>
///  
/// <remarks>   吴俊霖  </remarks>
////////////////////////////////////////////////////

class BXCClient :
	virtual public CTcpConnectClient
	,virtual public CUDPConnectClient
{
public:
	BXCClient();
	~BXCClient();

public:
	bool Initialize();

	/// <summary>	接收数据处理. </summary> wujl 
	void RecvDataFunction(const buffer_type& Buffer);

	void UdpSendFunction();

public:
	void sendBGC2_TO_TSPackage(const BGC2_TO_TS& Data) ;

	/// <summary>	发送通信查询. </summary> wujl
	void sendDMCommunicationQueryPackage(const DMCommunicationQueryPackage CommunicationQuery);

	/// <summary>	发送系统自检. </summary> wujl
	void sendDMSystemSelfCheckPackage(const DMSystemSelfCheckPackage SelfCheck);

	/// <summary>	发送控制状态查询. </summary> wujl
	void sendDMAalibrationMarkCarInitPackage(const DMAalibrationMarkCarInitPackage ControlState);

protected:
	/// <summary>	周期通信查询线程. </summary> wujl
	void CheckFunction_Thread();
private:
	boost::thread * _TcpRecvthread;
	boost::thread * _UdpRecvthread;
	char _deal_buf[1024];
	int _deal_buflen;
	

	boost::shared_ptr<boost::thread> _CheckThread;
	HANDLE _CheckComSemaphore;

	boost::shared_ptr<boost::thread> _DataThread;
	HANDLE _DataSemaphore;
};
