#include "stdafx.h"
#include "UDPConnectClient.h"
#include <DailyLog.h>
#include "DataManager.h"
#include "Define.h"
#include <ScnParserLib.h>

#include <boost/thread.hpp>

#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <mmiscapi2.h>

//#define TRAGETNUMBER_1 1
//#define TRAGETNUMBER_2 1 | 1 << 3
//#define TRAGETNUMBER_3 1 | 1 << 3 | 1 << 6
#define TRAGETNUMBER_1 1
#define TRAGETNUMBER_2 1 | 1 << 6
#define TRAGETNUMBER_3 1 | 1 << 3 | 1 << 6

using boost::asio::ip::udp;

CUDPConnectClient::CUDPConnectClient()
	: m_buf(100, 0)
	, _MessageOrderNumber(0)
	, _recvp(ip::udp::v4(), 6000)
	, _sockp(io_service_s)
	, _sockrecv(nullptr)
	, _ModeName("")
{

}


CUDPConnectClient::~CUDPConnectClient()
{
}

void CALLBACK CheckTimeOutFunction(UINT uTimerID, UINT uMsg, DWORD_PTR dwUser, DWORD_PTR dw1, DWORD_PTR dw2)
{
	CUDPConnectClient * testclient = (CUDPConnectClient*)dwUser;
	// 	M->TPC_SysStqRequest_ddsfunc(nullptr);

	//假数据测试；
	//testclient->BXC_TestData_TMP(ToolConfig::Instance()->GetBXCUdpIPValue(),ToolConfig::Instance()->GetBXCUdpPortValue());

	testclient->SendTmp();
}

void CUDPConnectClient::Init(std::string IP, int Port, int RecvPort, boost::function<void(buffer_type)> func, std::string ModeName)
{
	_ModeName = ModeName;

	if (func == nullptr)
	{
		_LOG_AHead("初始化函数为空！");
		//return;
	}

	//Init_tmp2(IP,Port);
	//BXC_TestData_TMP(IP, Port);
	//boost::shared_ptr<boost::thread> thr = boost::make_shared<boost::thread>(&CUDPConnectClient::BXC_TestData_TMP,this); 
	//new boost::thread(&CUDPConnectClient::BXC_TestData_TMP, this,IP,Port);
	//new boost::thread(&CUDPConnectClient::SendTmp, this);
	//new boost::thread(&CUDPConnectClient::BXC_TestData_TMP, this, IP, Port);

	timeSetEvent(10, 1, CheckTimeOutFunction, (DWORD_PTR)this, TIME_PERIODIC);

 	udp::endpoint sendp(ip::address::from_string(IP), Port);
 	_sendp = sendp;
 	// 	ip::udp::socket sockp(io_service);
 	// 	_sockp = sockp;
 	_sockp.open(udp::v4());
 
// 	udp::endpoint recvp(ip::udp::v4(), RecvPort);
// 	_recvp = recvp;
// 
// 	_sockrecv = new ip::udp::socket(io_service_r, ip::udp::endpoint(ip::udp::v4(), RecvPort));

}

void CUDPConnectClient::send_p(char * buff, int length)
{
	std::string str(buff, length);
	//memcpy(str.data(),buff,length);
	boost::shared_ptr<std::string> msg(new std::string(str));

	_sockp.async_send_to(buffer(buff, length), _sendp, boost::bind(&CUDPConnectClient::handle_send, this, msg, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));

	_sockrecv->async_receive_from(buffer(read_buf_), _recvp, boost::bind(&CUDPConnectClient::handle_receive, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));

	//_sockrecv.async_receive_from(buffer(s_buf),_recvp,boost::bind(&CUDPConnectClient::handle_receive,this,boost::asio::placeholders::error,boost::asio::placeholders::bytes_transferred));

	//Sleep(10);
}


void CUDPConnectClient::handle_send(boost::shared_ptr<std::string> message, const boost::system::error_code& error, std::size_t bytes_transferred)
{
	std::cout << "send over!" << std::endl;
}

void CUDPConnectClient::handle_receive(const boost::system::error_code& error, std::size_t bytes_transferred)
{
	
}

void CUDPConnectClient::run()
{
	//_sockrecv->async_receive_from(buffer(read_buf_), _recvp, boost::bind(&CUDPConnectClient::handle_receive, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));

	//io_service_r.run();
}

static double tmp_i = 1;
void CUDPConnectClient::BXC_TestData_TMP(std::string IP, int Port)
{
	boost::asio::io_service io_service;
	//udp::resolver resolver(io_service);
	//udp::resolver::query query(udp::v4(),IP,"6000");
	//udp::endpoint receiver_endpoint = *resolver.resolve(query);
	udp::endpoint sendp(ip::address::from_string(IP), Port);
	ip::udp::socket sockp(io_service);
	sockp.open(udp::v4());
 
  	int lentmp = sizeof(BGC2_TO_TS);
  	// 	std::vector<char> buf;
  	// 	buf.push_back('t');
  	// 	buf.push_back('s');
  
  	double tmp_change_value = 0.5;
  	int tmp_change_db_send = 0;
  	int tmp_change_db_send_i = 0;
  
  	int tmp_speed = 0;
  
  	
  //	while (1)
  	{
  		BGC2_TO_TS ts;
  		memset(&ts, 0, sizeof(BGC2_TO_TS));
  		ts.ucWorkState = 0;
  		ts.ucTSWKfrq = 20;
  		ts.ucTSRCSsevro = 0;
  		ts.ucTSrecvAtt = 15;
  
  		int v = tmp_change_db_send + tmp_change_db_send_i;
  		tmp_change_db_send_i++;
  		if (v > 63)
  		{
			//tmp_change_db_send_i = 0;
  			v = 0;
  		}
  		ts.ucTSemsnAtt[0] = v;
  		ts.ucTSemsnAtt[1] = v;
  		ts.ucTSemsnAtt[2] = v;
  		ts.ucTSdataEffect = 1;
		ts.ucTarSt = 1;// TargetNumber(9);
  
		ts.stTOTsInfo[0].R[0] = abs(90 * 1000 - tmp_change_value*tmp_i);
  		ts.stTOTsInfo[0].R[1] = 0;
  		ts.stTOTsInfo[0].R[2] = 0;
  
  		//R 填值， V一直为0;
  		ts.stTOTsInfo[0].V[0] = 0;
  		ts.stTOTsInfo[0].V[1] = 0;
  		ts.stTOTsInfo[0].V[2] = 0;
  
		int freq = 0;
  		//频偏必须填一致
  		ts.stTOTsInfo[0].Freq[0] = freq;
  		ts.stTOTsInfo[0].Freq[1] = freq;
  		ts.stTOTsInfo[0].Freq[2] = freq;
  
  		ts.stTOTsInfo[0].IfFreMove = 1;
  
  		//for (int i = 0; i < 3; ++i)
  		// 		{
  		// 			ts.stTOTsInfo[0].R[0] = 90*1000 + tmp_change_value*tmp_i;
  		// 			ts.stTOTsInfo[0].R[1] = 95*1000 + tmp_change_value*tmp_i;
  		// 			ts.stTOTsInfo[0].R[2] = 100*1000 + tmp_change_value*tmp_i;
  		// 
  		// 			ts.stTOTsInfo[0].V[0] = tmp_speed;
  		// 			ts.stTOTsInfo[0].V[1] = tmp_speed;
  		// 			ts.stTOTsInfo[0].V[2] = tmp_speed;
  		// 
  		// 			ts.stTOTsInfo[0].Freq[0] = 10000;
  		// 			ts.stTOTsInfo[0].Freq[1] = 10000;
  		// 			ts.stTOTsInfo[0].Freq[2] = 10000;
  		// 
  		// 			ts.stTOTsInfo[0].IfFreMove = 1;
  		// 		}
  		// 
  		// 		ts.stTOTsInfo[1].R[0] = 105*1000 + tmp_change_value*tmp_i;
  		// 		ts.stTOTsInfo[1].R[1] = 110*1000 + tmp_change_value*tmp_i;
  		// 		ts.stTOTsInfo[1].R[2] = 115*1000 + tmp_change_value*tmp_i;
  		// 
  		// 		ts.stTOTsInfo[1].V[0] = tmp_speed;
  		// 		ts.stTOTsInfo[1].V[1] = tmp_speed;
  		// 		ts.stTOTsInfo[1].V[2] = tmp_speed;
  		// 
  		// 		ts.stTOTsInfo[1].Freq[0] = 10000;
  		// 		ts.stTOTsInfo[1].Freq[1] = 10000;
  		// 		ts.stTOTsInfo[1].Freq[2] = 10000;
  		// 		
  		// 		ts.stTOTsInfo[1].IfFreMove = 1;
  		// 
  		// 		//
  		// 		ts.stTOTsInfo[2].R[0] = 120*1000 + tmp_change_value*tmp_i;
  		// 		ts.stTOTsInfo[2].R[1] = 125*1000 + tmp_change_value*tmp_i;
  		// 		ts.stTOTsInfo[2].R[2] = 130*1000 + tmp_change_value*tmp_i;
  		// 
  		// 		ts.stTOTsInfo[2].V[0] = tmp_speed;
  		// 		ts.stTOTsInfo[2].V[1] = tmp_speed;
  		// 		ts.stTOTsInfo[2].V[2] = tmp_speed;
  		// 
  		// 		ts.stTOTsInfo[2].Freq[0] = 10000;
  		// 		ts.stTOTsInfo[2].Freq[1] = 10000;
  		// 		ts.stTOTsInfo[2].Freq[2] = 10000;
  
  		ts.stTOTsInfo[2].IfFreMove = 1;
  
  		char buf[512] = { "" };
  
  
  
  		memcpy(buf, &ts, sizeof(BGC2_TO_TS));
  		s_buf.clear();
  		for (int i = 0; i < sizeof(BGC2_TO_TS); ++i)
  		{
  			s_buf.push_back(buf[i]);
  		}
  
		sockp.send_to(buffer(s_buf), sendp);
  		//Sleep(10);
  
  		tmp_i++;
  	}
}


void CUDPConnectClient::SendTmp()
{
// 	boost::asio::io_service io_service;
// 	udp::endpoint sendp(ip::address::from_string("192.168.2.192"), 6000);
// 	ip::udp::socket sockp(io_service);
// 	sockp.open(udp::v4());

	TPC_ScnPlatUpdate scnplat;
	memset(&scnplat, 0, sizeof(TPC_ScnPlatUpdate));
	if (SceneResolution()->tryGetData())
	{
		scnplat = SceneResolution()->GetData();
	}
	else
	{
		return;
	}

	//得到雷达和目标信息
	ScnPlat radar;
	memset(&radar, 0, sizeof(ScnPlat));
	std::vector<ScnPlat> tgtList;
	CalcTgtPlat(tgtList, scnplat);
	CalcRadarPlat(radar, scnplat);

	//
	BGC2_TO_TS ts;
	memset(&ts, 0, sizeof(BGC2_TO_TS));

	int  tmpi = 0;

	for (int no = 0; no < tgtList.size(); ++no,++tmpi)
	{
		//临时
		if (tmpi == 1)
		{
			tmpi = 2;
		}

		if (no > 2)
		{
			//std::cout << "超过两个目标" << ";不发送" << std::endl;
			break;
		}

		//计算
		PLT_ENTITY own;
		memset(&own, 0,sizeof(PLT_ENTITY));
		own.nID = radar.plat_id;
		own.longitude = radar.lon;
		own.latitude = radar.lat;
		own.altitude = radar.alt;
		own.course = radar.hdg;
		own.pitch = radar.pch;
		own.across = radar.rol;
		own.v_east = radar.spdEast;
		own.v_north = radar.spdNorth;
		own.v_sky = radar.spdUp;
// 			std::cout << "lon:" << radar.lon << std::endl
// 				<< ";lat:" << radar.lat << std::endl
// 				<< ";atl:" << radar.alt << std::endl
// 				<< ";course:" << radar.hdg << std::endl
// 				<< ";pch:" << radar.pch << std::endl
// 				<< ";ro" << radar.rol << std::endl
// 				<< ";ve" << radar.spdEast << std::endl
// 				<< ";vno" << radar.spdNorth << std::endl
// 				<< ";vs" << radar.spdUp << std::endl;
		memset(own.rcsTable.rcs_head, 0, sizeof(FLOAT)*RADIO_BAND_NUM);
		memset(own.rcsTable.rcs_side, 0, sizeof(FLOAT)*RADIO_BAND_NUM);
		memset(own.rcsTable.rcs_rear, 0, sizeof(FLOAT)*RADIO_BAND_NUM);

		PLT_ENTITY tgt;
		memset(&tgt, 0, sizeof(PLT_ENTITY));
		tgt.nID = tgtList[no].plat_id;
		tgt.longitude = tgtList[no].lon;
		tgt.latitude = tgtList[no].lat;
		tgt.altitude = tgtList[no].alt;
		tgt.course = tgtList[no].hdg;
		tgt.pitch = tgtList[no].pch;
		tgt.across = tgtList[no].rol;
		tgt.v_east = tgtList[no].spdEast;
		tgt.v_north = tgtList[no].spdNorth;
		tgt.v_sky = tgtList[no].spdUp;
		memset(&tgt.rcsTable, 0, sizeof(PLT_RCS));

		double rfc = 3300e6;

		double Range = GetTargetRange(&own, &tgt);
		double Azimuth = GetTargetAzimuth(&own, &tgt);
		double Elev = GetTargetElev(&own, &tgt);
		double RadialVel = GetTargetRadialVel(&own, &tgt);
		double DopplerRF = GetTargetDopplerRF(&own, &tgt, rfc);
		double RCS = GetTargetRCS(&own, &tgt, RADIO_BAND_S);
		double Atten = GetTargetEchoAtten(&own, &tgt);

		ts.ucWorkState = 0;
		ts.ucTSWKfrq = 20;
		ts.ucTSRCSsevro = 0;
		ts.ucTSrecvAtt = 15;

// 			int v = tmp_change_db_send + tmp_change_db_send_i;
// 			tmp_change_db_send_i++;
// 			if (v > 63)
// 			{
// 				v = 0;
// 			}

		Atten = 0;
		ts.ucTSemsnAtt[0] = Atten;
		ts.ucTSemsnAtt[1] = Atten;
		ts.ucTSemsnAtt[2] = Atten;
		ts.ucTSdataEffect = 1;

		ts.stTOTsInfo[tmpi].R[0] = Range;
		//ts.stTOTsInfo[0].R[1] = 0;
		//ts.stTOTsInfo[0].R[2] = 0;

		//R 填值， V一直为0;
		ts.stTOTsInfo[tmpi].V[0] = 0;
		ts.stTOTsInfo[tmpi].V[1] = 0;
		ts.stTOTsInfo[tmpi].V[2] = 0;

		//频偏必须填一致
		ts.stTOTsInfo[tmpi].Freq[0] = DopplerRF;
		ts.stTOTsInfo[tmpi].Freq[1] = DopplerRF;
		ts.stTOTsInfo[tmpi].Freq[2] = DopplerRF;

		ts.stTOTsInfo[tmpi].IfFreMove = 1;

	}

	ts.stTOTsInfo[0].IfFreMove = 1;
	ts.stTOTsInfo[1].IfFreMove = 1;
	ts.stTOTsInfo[2].IfFreMove = 1;

	switch (tgtList.size())
	{
	case 0:
		ts.ucTarSt = 0;
		break;
	case 1:
		ts.ucTarSt = TRAGETNUMBER_1;
		break;
	case 2:
		ts.ucTarSt = TRAGETNUMBER_2;
		break;
	case 3:
		ts.ucTarSt = TRAGETNUMBER_3;
		break;
	default:
		ts.ucTarSt = 0;
		break;
	}

	char buf[512] = { "" };

	memcpy(buf, &ts, sizeof(BGC2_TO_TS));
	s_buf.clear();
// 	for (int i = 0; i < sizeof(BGC2_TO_TS); ++i)
// 	{
// 		s_buf.push_back(buf[i]);
// 	}
	s_buf.resize(sizeof(BGC2_TO_TS));
	memcpy(&s_buf[0], &ts, sizeof(BGC2_TO_TS));

	_sockp.send_to(buffer(s_buf), _sendp);
	//sockp.send_to(buffer(s_buf), sendp);
}

int CUDPConnectClient::TargetNumber(int no)
{
	int tmpnumber = 0;
	for (int i = 0; i < no;++i)
	{
		tmpnumber |= 1 << i;
	}

	return tmpnumber;
}

bool CUDPConnectClient::CalcRadarPlat(ScnPlat &plat, const TPC_ScnPlatUpdate& scn)
{
	LVCEntityInfo entity;
	FileTransfer()->GetRadarEntity(entity);
	for (int i = 0; i < scn.emtPlatCnt; ++i)
	{
		if (scn.emtPlat[i].plat_id == entity.id)
		{
			plat = scn.emtPlat[i];
			return true;
		}
// 		if (scn.sutPlat[i].plat_id == entity.id)
// 		{
// 			plat = scn.sutPlat[i];
// 			return true;
// 		}
	}

	return false;
}

bool CUDPConnectClient::CalcTgtPlat(std::vector<ScnPlat> &plats, const TPC_ScnPlatUpdate& scn)
{
	std::vector<LVCEntityInfo> ettlist;
	FileTransfer()->GetTargetEntity(ettlist);
	//for (int i = 0; i < scn.sutPlatCnt; ++i)
	//{
	//	for (int m = 0; m < ettlist.size(); ++m)
	//	{
	//		//if (scn.emtPlat[i].plat_id == ettlist[m].id &&
	//		//	scn.emtPlat[i].lon != 0 )
	//		//{
	//		//	plats.push_back(scn.emtPlat[i]);
	//		//}
	//		if (scn.sutPlat[i].plat_id == ettlist[m].id &&
	//			scn.sutPlat[i].lon != 0)
	//		{
	//			plats.push_back(scn.sutPlat[i]);
	//		}
	//	}
	//}

	for (int m = 0; m < ettlist.size(); ++m)
	{
		for (int i = 0; i < scn.emtPlatCnt; ++i)
		{
			if (scn.emtPlat[i].plat_id == ettlist[m].id &&
				scn.emtPlat[i].lon != 0)
			{
				plats.push_back(scn.emtPlat[i]);
				break;
			}
		}
		for (int i = 0; i < scn.sutPlatCnt; ++i)
		{
			if (scn.sutPlat[i].plat_id == ettlist[m].id &&
				scn.sutPlat[i].lon != 0)
			{
				plats.push_back(scn.sutPlat[i]);
				break;
			}
		}
	}

	if (!plats.empty())
	{
		return true;
	}

	return false;
}

int CUDPConnectClient::RunWaterNumber()
{
	_rwMutex.lock();

	++_RunWaterNumber;

	_rwMutex.unlock();
	return _RunWaterNumber;
}

int CUDPConnectClient::MessageOrderNumber()
{
	_moMutex.lock();

	//_MessageOrderNumber++;

	_moMutex.unlock();
	return _MessageOrderNumber;
}

void CUDPConnectClient::SetSemaphore(HANDLE *CheckSemaphore)
{
}

unsigned long CUDPConnectClient::_RunWaterNumber = 0;

//boost::asio::io_service CUDPConnectClient::io_service_r;
