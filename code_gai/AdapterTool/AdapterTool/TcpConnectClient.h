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
#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/shared_mutex.hpp>
#include "stdafx.h"


#define _LOG_AHead(s) _LOG( _ModeName + s)

using namespace boost::asio;
using boost::asio::ip::udp;

typedef boost::shared_ptr<ip::udp::socket> sock_udp_ptr;
typedef boost::shared_ptr<ip::tcp::socket> sock_ptr;
typedef std::vector<char> buffer_type;


class CTcpConnectClient/* :public boost::enable_shared_from_this<CTcpConnectClient>*/
{
public:
	CTcpConnectClient();
	virtual ~CTcpConnectClient();


public:

	/// <summary>	初始化ip 端口数据. </summary> wujl 
	void Init(std::string IP, int Port, int RecvPort, boost::function<void(buffer_type)> func, std::string ModeName);

	//TCP..............//
public:
	/// <summary>	启动io. </summary> wujl 
	virtual void run(io_service* io = nullptr);

	/// <summary>	异步连接. </summary> wujl 
	void start();

	void restart();

	/// <summary>	接收数据处理. </summary> wujl 
	void RecvDataFunction(buffer_type str);

	/// <summary>	连接的回调函数. </summary> wujl 
	void conn_handler(const boost::system::error_code&ec, sock_ptr sock);

	/// <summary>	重连函数. </summary> wujl 
	void reconn_handler(const boost::system::error_code&ec, sock_ptr sock);
	/// <summary>	重连函数. </summary> wujl 
	void reconn_handler();

	/// <summary>	读取数据的回调函数. </summary> wujl 
	//void read_handler(const boost::system::error_code&ec, sock_ptr sock);

	//void read_handler(const boost::system::error_code&ec, size_t len);
	void read_handler(const boost::system::error_code&ec, size_t bytes_transferred);
	void write(std::string info);
	void write(char * buff, int length);

	void write_handler(const boost::system::error_code&ec);

private:
	bool PreExcete(char * buf, int bytes_transferred);
	bool CommandOnceFunc(char * buf, int undeallen, int &CommandLen);
	void OfExcete(char * buf, int bytes_transferred);

public:
	int RunWaterNumber();
	int MessageOrderNumber();
	void SetDealbuff(char *Dealbuff, int *dealbuflen);
	void SetSemaphore(HANDLE *CheckSemaphore);

	std::string _ModeName;

private:
	
	io_service m_io;
	buffer_type m_buf;
	buffer_type s_buf;
	ip::tcp::endpoint *m_ep;

	boost::mutex _pharMutex;
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
	
	char read_buf_[2048];
	char ofer_read_buf_[2048];

	char pre_read_buf[2048 + 2048];
	int pre_undeallen;

	int ofer_read_buf_len;
	char *dealbuf;
	int *dealbuflen;
	sock_ptr sock;
	boost::function<void(buffer_type)> datafunc;
	std::string DealBuff;

	int preType;
	int preNoRecvNumber;
	bool _ReConFlag;
	HANDLE *_CheckSemaphore;
	boost::mutex _reconMutex;
	boost::shared_ptr<boost::thread> _iothr;
};

