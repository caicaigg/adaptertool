#include "stdafx.h"
#include "TcpConnectClient.h"
#include <DailyLog.h>
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include "DataManager.h"
#include "Define.h"

#define _LOG_AHead(s) _LOG( std::string("<").append(_ModeName).append(">").append( s ))

using boost::asio::ip::udp;

CTcpConnectClient::CTcpConnectClient()
	: m_buf(1024, 0)
	,_MessageOrderNumber(0)
	,_recvp(ip::udp::v4(), 6000)
	,_sockp(io_service_s)
	,_sockrecv(nullptr)
	,_ModeName("")
	,ofer_read_buf_len(0)
	,_ReConFlag(false)
{
	
}


CTcpConnectClient::~CTcpConnectClient()
{
}

void CTcpConnectClient::Init(std::string IP, int Port, int RecvPort, boost::function<void(buffer_type)> func, std::string ModeName)
{
	_ModeName = ModeName;

	if (func == nullptr)
	{
		_LOG_AHead("��ʼ������Ϊ�գ�");
		//return;
	}

	datafunc = func;

	ip::address add;
	//add = ip::address::from_string("192.168.1.30");
	add = ip::address::from_string(IP.c_str());
	assert(add.is_v4());

	m_ep = new ip::tcp::endpoint(add, Port);

	//��������
	start();
}

void CTcpConnectClient::run(io_service* io /*= nullptr*/)
{
	if (nullptr == io)
	{
		m_io.run();
		//m_io.reset();
		std::cout << " m_io run end" << std::endl;
	}
	else
	{
		io->run();
		std::cout << " io run end" << std::endl;
	}
}

void CTcpConnectClient::start()
{
	sock = boost::make_shared<ip::tcp::socket>(m_io);
	sock->async_connect(*m_ep, boost::bind(&CTcpConnectClient::conn_handler, this, boost::asio::placeholders::error, sock));
}


void CTcpConnectClient::conn_handler(const boost::system::error_code & ec, sock_ptr sock)
{
	if (ec)
	{
		std::cout << "���ӣ�������ʧ�ܣ�" << std::endl;
		std::cout << ec.message() << std::endl;
		std::string errstr(ec.message());
		_reconMutex.lock();
		_ReConFlag = false;
		_reconMutex.unlock();

		return;
	}
	std::cout << "���ӣ��������ɹ�" << std::endl;

	_reconMutex.lock();
	_ReConFlag = false;
	_reconMutex.unlock();

	std::cout << "Receive from " << sock->remote_endpoint().address() << ": " << std::endl;
	sock->async_read_some(buffer(read_buf_), boost::bind(&CTcpConnectClient::read_handler, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
}

void CTcpConnectClient::reconn_handler(const boost::system::error_code&ec, sock_ptr sock)
{
	do
	{
		_LOG_AHead("<---------------tcp����!--------------->");
		//sock->close();
		sock->close();
		restart();
		Sleep(1000);

	} while (0);
}

void CTcpConnectClient::restart()
{
	//boost::shared_ptr<io_service> io = boost::shared_ptr<io_service>(new io_service);
	io_service * io = new io_service;
	sock = boost::make_shared<ip::tcp::socket>(*io);
	boost::asio::io_service::work work(*io);
	if (_iothr && !_iothr->joinable())
	{
		std::cout << _iothr->get_id() << std::endl;
		std::cout << "iothr ���˳�" << std::endl;
	}
	
	sock->async_connect(*m_ep, boost::bind(&CTcpConnectClient::conn_handler, this, boost::asio::placeholders::error, sock));
	_iothr = boost::make_shared<boost::thread>(&CTcpConnectClient::run, this, io);
}

void CTcpConnectClient::reconn_handler()
{
	if (!_ReConFlag)
	{
		if (_reconMutex.try_lock())
		{
			//_reconMutex.lock();
			if (!_ReConFlag)
			{
				_ReConFlag = true;
				_reconMutex.unlock();
				reconn_handler(boost::system::error_code(), sock);
			}
			else
			{
				_reconMutex.unlock();
			}
		}
	}

}

//static int tmpiBeamWidthA = 0;
void CTcpConnectClient::read_handler(const boost::system::error_code&ec, size_t bytes_transferred)
{
	//_pharMutex.lock();
	//std::cout << bytes_transferred << std::endl;
	if (ec)
	{
		std::cout << ec.message() << std::endl;
		return;
	}

	//Ԥ����
	PreExcete(read_buf_, bytes_transferred);

#define Assign(unlen,dlen,siz) \
	if(unlen > 0) \
	{ \
		unlen -= siz;\
		dlen += siz; \
		if (unlen < 0) \
		{ \
			unlen = 0; \
		} \
	}  
	
	//�����ϴεĻ���
	char tmp_read_buf[2048+2048];
	if (ofer_read_buf_len > 0)
	{
		memcpy(tmp_read_buf, ofer_read_buf_, ofer_read_buf_len);
		memset(ofer_read_buf_, 0, 2048);
	}
	memcpy(tmp_read_buf+ ofer_read_buf_len, read_buf_, bytes_transferred);

	int undeallen = bytes_transferred+ ofer_read_buf_len;
	static int stmp = 0;
	stmp = ofer_read_buf_len;
	ofer_read_buf_len = 0;

	
	int tmp_pre_undeallen = undeallen;
	
	bool flagpre = false;
	int dlen = 0;
	while (undeallen)
	{

		bool flag = false;
		int tmpi = 0;

		//preNoRecvNumber > 0 ˵���ϴ�������û�н�����
		if (undeallen >= 24 /*|| preNoRecvNumber > 0*/)
		{
			for (;tmpi < undeallen-1;++tmpi)
			{
				unsigned short head = 0;
				memcpy(&head, &tmp_read_buf[dlen + tmpi], 2);
				if (0x7e7e == head )
				{
					flag = true;
					break;
				}
			}
			if (!flag)
			{
				std::cout << "δ�ҵ�����ͷ0x7e7e,ʣ��δ������:" << undeallen << std::endl;

				for (int i = 0; i < undeallen; ++i)
				{
					if (tmp_read_buf[dlen + i] == 0)
					{
						tmp_read_buf[dlen + i] = ' ';
					}
				}
				
				std::stringstream errorstream;
				errorstream << "\nδ�ҵ�����ͷ��";
				errorstream << tmp_read_buf[dlen];
				_LOG_AHead(errorstream.str());
				_LOG_FILE("δ�ҵ�����ͷ.txt",errorstream.str());

				
				//��������ֹ�룬�Ƿ���ǰ���Ľ�������ͻ��߱��ĳ���
				for (int i = 0; i < undeallen - 1; ++i)
				{
					unsigned short tail = 0;
					memcpy(&tail, &tmp_read_buf[dlen + i], 2);
					if (0x0a0d == tail)
					{
						std::cout << "index:" << i << ";��β;" << std::endl;
						//break;
					}
				}
				break;
			}
			if (tmpi != 0)
			{
				std::cout << "��������:" << tmpi << std::endl;
			}

			SMessageFormat msg;
			memcpy(&msg, tmp_read_buf + dlen + tmpi, MSGHEADER);
			//�����ͷ
			Assign(undeallen, dlen, MSGHEADER + tmpi);

			int tmpmmm = sizeof(TPC_RadParmNotify);
			int commandlen = 0;
			int tmplen = 0;

			//std::cout << "Э�飺" << msg._CommandCode << std::endl;

			switch (msg._CommandCode) {
			case _LVC_RM_MLXY:
				//_LOG_AHead("ͨ�Ų�ѯ����ظ�");
				//���յ��ظ����ͷ��źţ������´η���ͨ�Ų�ѯ����
				ReleaseSemaphore(*_CheckSemaphore, 1, NULL);
				commandlen += MSGHEADER;
				preType = _LVC_RM_MLXY;
				//���Ķ���Ϊ�գ�ֻ�����ͷ+��β
				break;
				//case _LVC_RM_XTSB:break;
			case _LVC_RM_XTSB:
				{
				_LOG_AHead("Ԥλ�ظ�������������");
				commandlen += MSGHEADER;
				//���Ķ���Ϊ�գ�ֻ�����ͷ+��β
				}
				break;
			case _LVC_RM_LDZJSB:
				_LOG_AHead("�״ﳵ�Լ�ظ���");
				{
					RMRadarSelfTestResult self;
					if (undeallen >= sizeof(RMRadarSelfTestResult))
					{
						tmplen = sizeof(RMRadarSelfTestResult);
						memcpy(&self, tmp_read_buf + dlen, tmplen);
						commandlen += MSGHEADER;
						commandlen += tmplen;
					}
				}
				break;
			case _LVC_RM_BJCZJSB:
				_LOG_AHead("��У���Լ�ظ���");
				{
					RMCACSelfTestResult self;
					if (undeallen >= sizeof(RMCACSelfTestResult))
					{
						tmplen = sizeof(RMCACSelfTestResult);
						memcpy(&self, tmp_read_buf + dlen, tmplen);
						commandlen += MSGHEADER;
						commandlen += tmplen;
					}
				}
				break;
			case _LVC_RM_LDZBSB:
				_LOG_AHead("վַ�ϱ��ظ���");
				{
					RMRadarCoordinateReport self;
					if (undeallen >= sizeof(RMRadarCoordinateReport))
					{
						tmplen = sizeof(RMRadarCoordinateReport);
						memcpy(&self, tmp_read_buf + dlen, tmplen);
						commandlen += MSGHEADER;
						commandlen += tmplen;
					}
				}
				break;
			case _LVC_RM_DJSJ:
				//_LOG_AHead("�㼣�ϱ���");
				{
					RMPointTraceReport self;
					if (undeallen >= sizeof(RMPointTraceReport))
					{
						tmplen = sizeof(RMPointTraceReport);
						memcpy(&self, tmp_read_buf + dlen, tmplen);
						
						commandlen += MSGHEADER;
						commandlen += tmplen;
					}
				
				}
				break;
			case _LVC_RM_HJSJ:
				//_LOG_AHead("�����ϱ���");
				{
					RMFlightTraceReport self;
					if (undeallen >= sizeof(RMFlightTraceReport))
					{
						tmplen = sizeof(RMFlightTraceReport);
						memcpy(&self, tmp_read_buf + dlen, tmplen);

						commandlen += MSGHEADER;
						commandlen += tmplen;
					}
				}
				break;
			case _LVC_RM_LDGZCS:
				_LOG_AHead("�״﹤�������ϱ�");
				{
					RMRadarWorkParamReport self;
					int mintmpRadarworkparamLen = sizeof(UINT32);
					if (undeallen >= mintmpRadarworkparamLen)
					{
						//��ȡ��λ�ܸ�������֤�յ������Ƿ��������в�λ��Ϣ
						tmplen = mintmpRadarworkparamLen;
						memcpy(&self, tmp_read_buf + dlen, tmplen);

						preType = _LVC_RM_LDGZCS;

						//�յ��ǲа���������-ֱ�ӻ��棬��������
						if (undeallen - mintmpRadarworkparamLen < self.uiBeamCutEventNum *sizeof(ST_BEAM_INFO))
						{
							_LOG_AHead("�״﹤�������ϱ�,�յ��ǲа�����λ�л��¼��������յ��Ĳ�λ��Ϣ�ܳ��Ȳ�һ�£��ȴ���һ�����!\n");
							//std::cout << "�״﹤�������ϱ�,�յ��ǲа�����λ�л��¼��������յ��Ĳ�λ��Ϣ�ܳ��Ȳ�һ�£��ȴ���һ�����!" << std::endl;
							//Assign(dlen, undeallen, MSGHEADER);//�ظ�������
							//memset(ofer_read_buf_, 0, 2048);
							//memcpy(ofer_read_buf_, tmp_read_buf + dlen, undeallen);
							//ofer_read_buf_len = undeallen;
							//undeallen = 0;
							break;
						}

						//preNoRecvNumber = self.uiBeamCutEventNum;
							
#pragma region �����״﹤����������
// 						std::stringstream stream;
// 						stream << std::endl;
// 						_LOG(stream.str());
#pragma endregion �����״﹤����������
						for (int tmpi = 0; tmpi < self.uiBeamCutEventNum; ++tmpi)
						{
							if (undeallen >= sizeof(ST_BEAM_INFO)*tmpi)
							{
								ST_BEAM_INFO info;
								memcpy(&info, tmp_read_buf + dlen + tmplen , sizeof(ST_BEAM_INFO));
								//std::cout << info.ucWaveType << std::endl;
								//preNoRecvNumber--;
								tmplen += sizeof(ST_BEAM_INFO);

#pragma region �����״﹤����������

								int ucWaveType = info.ucWaveType;
								int ucAgilityType = info.ucAgilityType;


								std::stringstream stream;
								
								stream << self.uiBeamCutEventNum << "\t";
								stream << tmpi << "\t";
								stream << info.iBeamAz << "\t";
								stream << info.iBeamEl << "\t";
								stream << info.iBeamWidthA << "\t";
								stream << info.iBeamWidthE << "\t";
								stream << info.uiBeamCutTime << "\t";
								stream << ucWaveType << "\t";
								stream << ucAgilityType << std::endl;
//
//								static int tmpmmm = 0;
//								if (tmpmmm == 0)
//								{
//									tmpmmm = 1;
//									tmpiBeamWidthA = info.iBeamWidthA - 1;
//								}
//								if (info.iBeamWidthA != tmpiBeamWidthA + 1)
//								{
//									tmpiBeamWidthA = info.iBeamWidthA;
//
//									//��ԭ���ϴΰ��� �˶δ�������ڵ��ԣ����а�ע��
//// 									memcpy(tmp_read_buf, pre_read_buf, 4096);
//// 									undeallen = pre_undeallen;
//// 									dlen = 0;
//// 									flagpre = true;
// 									std::cout << "�״﹤������ �Ѷ�������ˮ�Ų�������" << std::endl;
//// 									break;
//								}
//								else
//								{
//									tmpiBeamWidthA++;
//								}
//
								_LOG(stream.str());

#pragma endregion �����״﹤����������

							}
						}
						
						commandlen += MSGHEADER;
						commandlen += tmplen;
					}
				}
				break;
			case _LVC_RM_LDYXKZHF:
				_LOG_AHead("�״����п��ƻظ�");
				{
					RMRadarRunControlReport self;
					if (undeallen >= sizeof(RMRadarRunControlReport))
					{
						tmplen = sizeof(RMRadarRunControlReport);
						memcpy(&self, tmp_read_buf + dlen, tmplen);
						commandlen += MSGHEADER;
						commandlen += tmplen;
					}
				}
				break;
			case _LVC_RM_BJCKZZT:
				_LOG_AHead("��˳�����״̬�ظ�");
				{
					RMCACControlStateReport self;
					if (undeallen >= sizeof(RMCACControlStateReport))
					{
						tmplen = sizeof(RMCACControlStateReport);
						memcpy(&self, tmp_read_buf + dlen, tmplen);
						commandlen += MSGHEADER;
						commandlen += tmplen;
					}
				}
				break;
			case _LVC_RM_LDSCHJ:
				_LOG_AHead("�״�ɾ������");
				{
					RMRadarDeleteTrack self;
					if (undeallen >= sizeof(RMRadarDeleteTrack))
					{
						tmplen = sizeof(RMRadarDeleteTrack);
						memcpy(&self, tmp_read_buf + dlen, tmplen);
						commandlen += MSGHEADER;
						commandlen += tmplen;
					}
				}
				break;
			default:
				_LOG_AHead("û�е�ǰЭ�����ͣ����������������֣�");
				commandlen = -1;//���ʹ�����ʱʹ��commandlen ��ʾ��
				std::cout << "û�и�Э�����ͣ�" << msg._CommandCode << std::endl;
				break;
			}

#pragma region �����״﹤����������
// 			if (flagpre)
// 			{
// 				flagpre = false;
// 				continue;
// 			}
#pragma endregion �����״﹤����������

			//������ȷ,������ȷ
			if (commandlen > 0)
			{
				//���봦�����
				buffer_type tmpbuf;
// 				for (int i = 0; i < commandlen; ++i)
// 				{
// 					tmpbuf.push_back(tmp_read_buf[i+dlen-MSGHEADER]);
// 				}

				tmpbuf.resize(commandlen);
				memcpy(&tmpbuf[0], tmp_read_buf + dlen - MSGHEADER, commandlen);
				
				if (_LVC_RM_LDGZCS == preType)
				{
					tmpbuf.resize(sizeof(RMRadarWorkParamReport)+MSGHEADER);
					memset(&tmpbuf[0], 0, sizeof(RMRadarWorkParamReport) + MSGHEADER);
					memcpy(&tmpbuf[0], tmp_read_buf + dlen - MSGHEADER, commandlen);
				}

				QueueData_TCP()->SetData(tmpbuf);


				//��ֵ֮�󣬵������������ݳ���
				Assign(undeallen, dlen, tmplen);

				//��β����
				if (undeallen >= MSGEND)
				{
					Assign(undeallen, dlen, MSGEND);
				}
			}
			else if( 0 == commandlen )
			{
				Assign(dlen, undeallen, MSGHEADER);//�ظ������ͷ����
				memset(ofer_read_buf_, 0, 2048);
				memcpy(ofer_read_buf_, tmp_read_buf + dlen, undeallen);
				ofer_read_buf_len = undeallen;
				undeallen = 0;
				_LOG_AHead("ʣ�೤�� С�ڱ���Э�����ݣ������´ν�����");
				break;
			}

			if (undeallen < 0)
			{
				std::cout << "error" << undeallen << ":" << dlen << std::endl;
			}
		}
		else
		{
			memset(ofer_read_buf_, 0, 2048);
			memcpy(ofer_read_buf_, tmp_read_buf + dlen, undeallen);
			ofer_read_buf_len = undeallen;
			_LOG_AHead("ʣ�೤�� С�ڰ�ͷ��β�����棬����������");
			break;
		}

	}

	memset(read_buf_, 0, bytes_transferred);

	pre_undeallen = tmp_pre_undeallen;
	memcpy(pre_read_buf, tmp_read_buf, 2048 + 2048);
	memset(tmp_read_buf, 0, 2048+2048);
	sock->async_read_some(buffer(read_buf_), boost::bind(&CTcpConnectClient::read_handler, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));

	//_pharMutex.unlock();
}

bool CTcpConnectClient::PreExcete(char * buf, int bytes_transferred)
{
	//assert(bytes_transferred > 2048);
	if (bytes_transferred > 2048)
	{
		std::cout << "recv size > 2048;" << std::endl;
		return false;
	}

	if (0 == bytes_transferred)
	{
		std::cout << "recv size = 0;" << std::endl;
		_LOG_AHead("recv size = 0;");
		return false;
	}
	if (MSGHEADER+MSGEND > bytes_transferred)
	{
		_LOG_AHead("����������С����С����С��������");
		return false;
	}
	if (bytes_transferred > 84)
	{
		//std::cout << "recv size > 84;" << std::endl;
	}
	if (bytes_transferred != 84 || bytes_transferred != 116)
	{
		//std::cout << "ճ������С��" << bytes_transferred << std::endl;
	}
}

bool CTcpConnectClient::CommandOnceFunc(char * buf, int undeallen, int &CommandLen)
{
	

	return true;
}


void CTcpConnectClient::write(std::string info)
{
	for (int i = 0; i < info.size(); ++i)
	{
		s_buf.push_back(info[i]);
	}

	sock->async_write_some(buffer(s_buf), boost::bind(&CTcpConnectClient::write_handler, this, boost::asio::placeholders::error));
}

void CTcpConnectClient::write(char * buff, int length)
{
	if (!sock)
	{
		return;
	}
	sock->async_write_some(buffer(buff, length), boost::bind(&CTcpConnectClient::write_handler, this, boost::asio::placeholders::error));
}

void CTcpConnectClient::write_handler(const boost::system::error_code & ec)
{
	//std::cout << "send msg Client" << std::endl;
}

int CTcpConnectClient::RunWaterNumber()
{
	_rwMutex.lock();

	++_RunWaterNumber;

	_rwMutex.unlock();
	return _RunWaterNumber;
}

int CTcpConnectClient::MessageOrderNumber()
{
	_moMutex.lock();

	//_MessageOrderNumber++;

	_moMutex.unlock();
	return _MessageOrderNumber;
}

void CTcpConnectClient::SetSemaphore(HANDLE *CheckSemaphore)
{
	_CheckSemaphore = CheckSemaphore;
}

unsigned long CTcpConnectClient::_RunWaterNumber = 0;

//boost::asio::io_service CTcpConnectClient::io_service_r;
