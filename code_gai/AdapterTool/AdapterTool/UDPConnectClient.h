#pragma once

#include <iostream>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>
#include <boost/asio/placeholders.hpp>
#include <boost/system/error_code.hpp>
#include <boost/bind/bind.hpp>
#include <boost/function.hpp>
#include <boost/thread/mutex.hpp>
#include "stdafx.h"

#include "Define.h"

#define _LOG_AHead(s) _LOG( _ModeName + s)

using namespace boost::asio;
using boost::asio::ip::udp;

typedef boost::shared_ptr<ip::udp::socket> sock_udp_ptr;
typedef boost::shared_ptr<ip::tcp::socket> sock_ptr;
typedef std::vector<char> buffer_type;

class CUDPConnectClient
{
public:
	CUDPConnectClient();
	~CUDPConnectClient();

public:

	/// <summary>	初始化ip 端口数据. </summary> wujl 
	void Init(std::string IP, int Port, int RecvPort, boost::function<void(buffer_type)> func, std::string ModeName);
	void BXC_TestData_TMP(std::string IP, int Port);
	//void BXC_TestData_TMP();

	void SendTmp();

	int TargetNumber(int no);

	bool CalcRadarPlat(ScnPlat &plat, const TPC_ScnPlatUpdate& scn);
	bool CalcTgtPlat(std::vector<ScnPlat> &plats, const TPC_ScnPlatUpdate& scn);

	virtual void run();
	//UDP...............//
public:
	void send_p(char * buff, int length);
	void handle_send(boost::shared_ptr<std::string> message, const boost::system::error_code& error, std::size_t bytes_transferred);
	void handle_receive(const boost::system::error_code& error, std::size_t bytes_transferred);

	void SetDealbuff(char *Dealbuff, int *dealbuflen);
	void SetSemaphore(HANDLE *CheckSemaphore);
public:
	int RunWaterNumber();
	int MessageOrderNumber();


	std::string _ModeName;

private:

	buffer_type m_buf;
	buffer_type s_buf;

	boost::mutex _rwMutex;
	boost::mutex _moMutex;
	static unsigned long _RunWaterNumber;
	unsigned char _MessageOrderNumber;

	boost::asio::io_service io_service_s;
	ip::udp::socket _sockp;
	udp::endpoint _sendp;

	udp::endpoint _recvp;
	boost::asio::io_service io_service_r;
	ip::udp::socket* _sockrecv;

	char read_buf_[1024];
	sock_ptr sock;
	boost::function<void(buffer_type)> datafunc;

};

