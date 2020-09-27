#pragma once

#include <iostream>
#include <boost/shared_ptr.hpp>
#include <boost/asio.hpp>
#include <boost/asio/placeholders.hpp>
#include <boost/system/error_code.hpp>
#include <boost/bind/bind.hpp>
#include "stdafx.h"

using namespace boost::asio;
using namespace std;
typedef boost::shared_ptr<ip::tcp::socket> sock_ptr;
typedef std::vector<char> buffer_type;

class CASIOServer
{
private:
	io_service m_io;
	ip::tcp::acceptor m_acceptor;
	buffer_type m_buf;
public:
	CASIOServer()
		:m_acceptor(m_io, ip::tcp::endpoint(ip::tcp::v4(), 9998))
		, m_buf(1000, 0)
	{
		accept();
	}

	void run() { m_io.run(); }

	void accept()
	{
		sock_ptr sock(new ip::tcp::socket(m_io));
		m_acceptor.async_accept(*sock, boost::bind(&CASIOServer::accept_handler, this, boost::asio::placeholders::error, sock));
	}

	void read_handler(const boost::system::error_code & ec, sock_ptr sock)
	{
		if (ec)
		{
			return;
		}
		sock->async_read_some(buffer(m_buf), boost::bind(&CASIOServer::read_handler, this, boost::asio::placeholders::error, sock));
		std::cout << &m_buf[0] << std::endl;

		int a = 0;
		char buf[100] = { "" };
		std::cout << "(1):";
		std::cin >> buf;

		try
		{
			a = atoi(buf);
		}
		catch (...)
		{
		}

		switch (a)
		{
		case 1:
			sock->async_write_some(buffer("hello asio Manually check for alive _folders_ of pervious version of VA in extensions folders (paths are described)"), boost::bind(&CASIOServer::write_handler, this, boost::asio::placeholders::error));
			break;
		}

	}

	void accept_handler(const boost::system::error_code& ec, sock_ptr sock)
	{
		if (ec)
		{
			return;
		}
		cout << "Client:";
		cout << sock->remote_endpoint().address() << endl;
		sock->async_write_some(buffer("hello asio Manually check for alive _folders_ of pervious version of VA in extensions folders (paths are described)"), boost::bind(&CASIOServer::write_handler, this, boost::asio::placeholders::error));
		// 发送完毕后继续监听，否则io_service将认为没有事件处理而结束运行 
		sock->async_read_some(buffer(m_buf), boost::bind(&CASIOServer::read_handler, this, boost::asio::placeholders::error, sock));
		accept();
	}

	void write_handler(const boost::system::error_code&ec)
	{
		cout << "send msg Server" << endl;
	}
};
