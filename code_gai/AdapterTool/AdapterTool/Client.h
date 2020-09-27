#pragma once
#include "TcpConnectClient.h"

#include <boost/thread.hpp>

#include "Define.h"

#define VERSION_LVC29 1
#define PROPERTY_LVC29 0
#define CHECKCODE_LVC29 0
#define ENDCODE_LVC29 0x0a0d


////////////////////////////////////////////////////
/// <summary> �״�TCPͨ�ŷ�װ�ӿ�   </summary>
///  
/// <remarks>   �⿡��  </remarks>
////////////////////////////////////////////////////


class RadarClient :
	public CTcpConnectClient
{
public:
	RadarClient();
	~RadarClient();

public:
		
	/// <summary>	��ʼ��ip port�������߳�. </summary> wujl
	bool Initialize();

	/// <summary>	������ͷ. </summary> wujl 
	void TransferHead(SMessageFormat& Head, const buffer_type & buffer);

	/// <summary>	���. </summary> wujl 
	void Pack(SMessageFormat& Head, char * PackInfo);

	
public:

	/// <summary>	����ͨ�Ų�ѯ. </summary> wujl
	void sendDMCommunicationQueryPackage(const DMCommunicationQueryPackage CommunicationQuery);

	/// <summary>	����ϵͳ�Լ�. </summary> wujl
	void sendDMSystemSelfCheckPackage(const DMSystemSelfCheckPackage SelfCheck);

	/// <summary>	�����״��ʼ������. </summary> wujl
	void sendDMRadarInitConfigPackage(const CENTER2RADAR_INIT RadarInit);

	/// <summary>	�����״������ѯ. </summary> wujl
	void sendDMRadarLocationQueryPackage(const DMRadarLocationQueryPackage LocationQuery);

	/// <summary>	�������п���. </summary> wujl
	void sendDMRunControlPackage(const DMRunControlPackage RunControl);

	/// <summary>	���ͱ�У����ʼ������. </summary> wujl
	//void sendDMAalibrationMarkCarInitPackage(const DMAalibrationMarkCarInitPackage AMCInit);

	/// <summary>	����ʵʱĿ�����. </summary> wujl
	void sendDMTargetRealTimePackage(const DMTargetRealTimePackage Targets);


private:
	bool tryTransferHead(const buffer_type & buffer);

protected:

	/// <summary>	�������ݴ���. </summary> wujl 
	void TcpRecvDataFunction(const buffer_type& str);

	/// <summary>	����ͨ�Ų�ѯ�߳�. </summary> wujl
	void CheckFunction_Thread();

	/// <summary>	�������ݴ����߳�. </summary> wujl
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
/// <summary>  //��У��tcpͨ�Žӿ�  </summary>
///  
/// <remarks>   �⿡��  </remarks>
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

	/// <summary>	�������ݴ���. </summary> wujl 
	void RecvDataFunction(const buffer_type& Buffer);

	void UdpSendFunction();

public:
	void sendBGC2_TO_TSPackage(const BGC2_TO_TS& Data) ;

	/// <summary>	����ͨ�Ų�ѯ. </summary> wujl
	void sendDMCommunicationQueryPackage(const DMCommunicationQueryPackage CommunicationQuery);

	/// <summary>	����ϵͳ�Լ�. </summary> wujl
	void sendDMSystemSelfCheckPackage(const DMSystemSelfCheckPackage SelfCheck);

	/// <summary>	���Ϳ���״̬��ѯ. </summary> wujl
	void sendDMAalibrationMarkCarInitPackage(const DMAalibrationMarkCarInitPackage ControlState);

protected:
	/// <summary>	����ͨ�Ų�ѯ�߳�. </summary> wujl
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
