#include "stdafx.h"
#include "MessageReport.h"


#include "DDSCore.h"
#include "RadarCore.h"

#include "DataManager.h"
#include <ScnParserLib.h>

#include <boost/lexical_cast.hpp>



MessageReport::MessageReport(const CDDSCore * DDS, CRadarCore *Radar)
	:_dds(DDS)
	,_radar(Radar)
{
	int s = 0;
	//int s = sizeof(TPC_RadParmNotify);
	//int s = sizeof(RMPantReportPackage);
	//s = sizeof(TPC_RadTrkNotify_n);
	//s = sizeof(TPC_RadPltNotify_n);
	_ReportThread = boost::make_shared<boost::thread>(&MessageReport::TCPDataFunction_Thread, this);
}

MessageReport::~MessageReport()
{
}


#define CASE_TCPTYPE(TypeValue,Data) \
	case TypeValue: { \
		Data data; \
		memset(&data,0,sizeof(Data));\
		/*std::cout << "fff:" << buffer.size() << ":" << sizeof(Data) << std::endl;*/ \
		if (buffer.size()-MSGHEADER >= sizeof(Data)) \
		{ \
			/*std::cout << "ggg" <<std::endl;*/ \
			memcpy(&data, &buffer[0 + MSGHEADER], sizeof(Data)); \
		} \
		Data##_tcpfunc(data); \
		}\
		break;

	/*	else \
		{ \
		_LOG("���������ݣ����ȳ���"); \
		_LOG(std::string("��������:").append(boost::lexical_cast<std::string>(TypeValue))); \
		_LOG(std::string("����buff����:").append(boost::lexical_cast<std::string>(buffer.size()))); \
		} \*/
#pragma region Tcp������Ϣ����ģ��

void MessageReport::TCPDataFunction_Thread()
{
	do
	{
		QueueData_TCP()->WaitCmd();

		buffer_type buffer = QueueData_TCP()->GetData();
		if (!buffer.empty())
		{
			//����ͷ
			SMessageFormat msghead;
			_radar->TransferHead(msghead, buffer);

			//�״�ӿڲ��ԣ�
			//������Ϣ��DDS����
			switch (msghead._CommandCode)
			{
				CASE_TCPTYPE(_LVC_RM_MLXY, RMCommandAnswerPackage);
				CASE_TCPTYPE(_LVC_RM_XTSB, RMPantReportPackage);
				CASE_TCPTYPE(_LVC_RM_LDZJSB, RMRadarSelfTestResult);
				CASE_TCPTYPE(_LVC_RM_BJCZJSB, RMCACSelfTestResult);
				CASE_TCPTYPE(_LVC_RM_LDZBSB, RMRadarCoordinateReport);	
				CASE_TCPTYPE(_LVC_RM_DJSJ, RMPointTraceReport);
				CASE_TCPTYPE(_LVC_RM_HJSJ, RMFlightTraceReport);
				CASE_TCPTYPE(_LVC_RM_LDGZCS, RMRadarWorkParamReport);
				CASE_TCPTYPE(_LVC_RM_LDYXKZHF, RMRadarRunControlReport);
				CASE_TCPTYPE(_LVC_RM_BJCKZZT, RMCACControlStateReport);

				CASE_TCPTYPE(_LVC_TPC_ScnDldNotify, TPC_ScnDldNotify);
				CASE_TCPTYPE(_LVC_TPC_SysRdyNotify, TPC_SysRdyNotify);
			default:
				std::cout << "DDS�ϱ����ʹ���" << msghead._CommandCode << std::endl;
				break;
			}
		}

	} while (true);
}


void MessageReport::RMCommandAnswerPackage_tcpfunc(RMCommandAnswerPackage& package)
{
	//Q


}

void MessageReport::RMPantReportPackage_tcpfunc(RMPantReportPackage& package)
{
	//Q �ݶ�ΪԤλ �ظ�
	TPC_SysRdyNotify_tcpfunc(TPC_SysRdyNotify());
	QueueData_DDS()->ReleaseRdyRequest();
}

void MessageReport::RMRadarSelfTestResult_tcpfunc(RMRadarSelfTestResult& package)
{

	TPC_SysBitReply screply;
	screply.bitResult = 0;

	_dds->SendDDS(DDSTYPE_SysBitReply, &screply);
}

void MessageReport::RMCACSelfTestResult_tcpfunc(RMCACSelfTestResult& package)
{
// 	package._CACSystemTestResult = RMSSTR_Success;
// 	package._CACSubSystemTestResult = 0;
	
	RMCACSelfTestResult a = package;


	//Q DDS������ô��
	TPC_SysBitReply screply;
	screply.bitResult = 0;
	//screply.DataType = DDSTYPE_SysBitReply;
	//int s = sizeof(SelfCheckReply);

	_dds->SendDDS(DDSTYPE_SysBitReply, (void*)&screply);
}

void MessageReport::RMRadarCoordinateReport_tcpfunc(RMRadarCoordinateReport& package)
{
	//Q վַ�ϱ�

	const LVCScenarioFile& scn = CDataManager::DMFileLoadTransfer::Instance()->GetScenarioInfo();
	const RadarInfo& radar = CDataManager::DMFileLoadTransfer::Instance()->GetRadarsInfo();

	

	PLT_ENTITY own;
	LVCEntityInfo RadarEtt;
	if (!FileTransfer()->GetRadarEntity(RadarEtt))
	{
		std::cout << "RadarEntity δ�������ļ��ҵ���" << std::endl;
	}

	own.longitude = RadarEtt.initState.lon;
	own.latitude = RadarEtt.initState.lat;
	own.altitude = RadarEtt.initState.alt;
	own.course = RadarEtt.initState.Heading;
	own.pitch = RadarEtt.initState.pitch;
	own.across = RadarEtt.initState.roll;

	PLT_ENTITY tgt;

	std::vector<LVCEntityInfo> ettVec;
	LVCEntityInfo tgtEtt;
	if (!FileTransfer()->GetTargetEntity(ettVec))
	{
		std::cout << "tgtEtt δ�������ļ��ҵ���" << std::endl;
	}
	//Q Ĭ��ȡ��һ��Ŀ��
	if (ettVec.size() > 0)
	{
		tgtEtt = ettVec[0];
	}
	tgt.longitude = tgtEtt.initState.lon;
	tgt.latitude = tgtEtt.initState.lat;
	tgt.altitude = tgtEtt.initState.alt;
	tgt.course = tgtEtt.initState.Heading;
	tgt.pitch = tgtEtt.initState.pitch;
	tgt.across = tgtEtt.initState.roll;


	VEC_DIR atn;
	assert(0 != radar.AtnAchParamList.params.size());
	atn.jaw = radar.AtnAchParamList.params[0].heading;
	atn.pitch = radar.AtnAchParamList.params[0].pitch;
	atn.roll = radar.AtnAchParamList.params[0].roll;

	VEC_POS radPos;
	radPos.lon = package._RadarLon /10e4;
	radPos.lat = package._RadarLat / 10e4;
	radPos.alt = package._RadarAlt / 10e4;

	VEC_POS bjcPos;
	bjcPos.lon = package._BxcLon / 10e4;
	bjcPos.lat = package._BxcLat / 10e4;
	bjcPos.alt = package._BxcAlt / 10e4;


	double alpha = GetRadarAtnAzim(&own, &tgt, &atn, &radPos, &bjcPos);

	// ��ʼ��Ŀ������ת������
	InitTargetConvert(&own, &tgt,  &radPos, &bjcPos);

	std::cout << "alpha::" << alpha << std::endl;

	if (alpha > 0.000001 )
	{
		SceneResolution()->SetAlphaValue(alpha);
	}

	//���ػظ�
	TPC_ScnDldNotify dld;
	TPC_ScnDldNotify_tcpfunc(dld);
}

void MessageReport::RMPointTraceReport_tcpfunc(RMPointTraceReport& package)
{
	//RMPointTraceReport a = package;

	//RMPointTraceReport trace;
	//_dds->SendDDS(DDSTYPE_RadPltReport,&trace);


	TPC_RadPltNotify_n plt;

	plt.objectID = 0;
	plt.equipID = 0;
	memcpy(plt.pltRecTime, &package.stPlotTime, sizeof(INTF_DC_TIME));
	plt.pltId = package.uiPlotId;
	plt.wfmId = package.waveForm;
	plt.SNR = package.SNR;
	plt.amp = package.amp;
	plt.R = package.R;
	plt.Az = package.Az;
	plt.El = package.El;
	plt.distErr = package.distErr;
	plt.azErr = package.azErr;
	plt.elErr = package.elErr;
	plt.posX = package.X;
	plt.posY = package.Y;
	plt.posZ = package.Z;

	VEC_POS scenpos;
	VEC_POS realpos;
	memset(&realpos, 0, sizeof(VEC_POS));
	memset(&scenpos, 0, sizeof(VEC_POS));

	realpos.east = package.X;
	realpos.north = package.Y;
	realpos.sky = package.Z;
	DoTargetConvert(&realpos, &scenpos);
	plt.lon = scenpos.lon*1e7;
	plt.lat = scenpos.lat*1e7;
	plt.alt = scenpos.alt;

	plt.SFmark = package.SFmark;
	plt.DopV = package.DopV;
	plt.back = package.remain;

	_dds->SendDDS(DDSTYPE_RadPltReport, &plt);
}

void MessageReport::RMFlightTraceReport_tcpfunc(RMFlightTraceReport& package)
{
	//RMFlightTraceReport a = package;

	//ReportRadarTrack track;
	//_dds->SendDDS(DDSTYPE_RadTrkReport,&track);

	TPC_RadTrkNotify_n trk;

	trk.objectID = 0;
	trk.equipID = 0;
	memcpy(trk.pltRecTime, &package.stTrackTime, sizeof(INTF_DC_TIME));
	trk.uiPlotId = package.uiPlotId;
	trk.uiTrackId = package.uiTrackId;
	trk.tgtNo = package.tgtNo;
	trk.subNo = package.subNo;
	trk.traceStatus = package.traceStatus;
	trk.ucTrackQuality = package.ucTrackQuality;
	trk.ucFollowCtrl = package.ucFollowCtrl;
	trk.waveForm = package.waveForm;
	trk.SNR = package.SNR;
	trk.amp = package.amp;
	trk.GR = package.GR;
	trk.GA = package.GA;
	trk.GE = package.GE;
	trk.distErr = package.distErr;
	trk.azErr = package.azErr;
	trk.elErr = package.elErr;
	trk.Vr = package.Vr;
	trk.Va = package.Va;
	trk.Ve = package.Ve;
	trk.X = package.X;
	trk.Y = package.Y;
	trk.Z = package.Z;
	trk.VX = package.VX;
	trk.VY = package.VY;
	trk.VZ = package.VZ;

	VEC_POS scenpos;
	VEC_POS realpos;
	memset(&realpos, 0, sizeof(VEC_POS));
	memset(&scenpos, 0, sizeof(VEC_POS));

	realpos.east = package.X;
	realpos.north = package.Y;
	realpos.sky = package.Z;
	DoTargetConvert(&realpos, &scenpos);
	trk.lon = scenpos.lon*1e7;
	trk.lat = scenpos.lat*1e7;
	trk.alt = scenpos.alt;

	trk.DopV = package.DopV;
	trk.remain = package.remain;

	_dds->SendDDS(DDSTYPE_RadTrkReport, &trk);
}

void MessageReport::RMRadarWorkParamReport_tcpfunc(RMRadarWorkParamReport& package)
{
	TPC_RadParmNotify param;
	memset(&param, 0, sizeof(TPC_RadParmNotify));

	//��ȡ�״�ʵ��
	LVCEntityInfo RadarEtt;
	memset(&RadarEtt, 0, sizeof(LVCEntityInfo));
	if (!FileTransfer()->GetRadarEntity(RadarEtt))
	{
		std::cout << "RadarEntity δ�������ļ��ҵ���" << std::endl;
	}

	//Q ��ȡ�״��豸 �ֽ׶�ֻ��һ���״�
	EquipInfo radar;
	radar.id = -1;
	if (!RadarEtt.equipList.empty())
	{
		radar.id = RadarEtt.equipList[0].id;
	}
	else
	{
		std::cout << "�״��豸��ϢΪ�գ�" << std::endl;
	}

	param.platId = RadarEtt.id;
	param.emtId = radar.id;
	param.evtCode = sim_event_bdw;
	param.simEvtCnt = package.uiBeamCutEventNum;
	
	//Q ���������쳣����
	if (param.simEvtCnt < 0 || param.simEvtCnt > MAXDATACOUNT)
	{
		std::cout << "�״﹤�����������θ�������" << param.simEvtCnt << std::endl;
		param.simEvtCnt = MAXDATACOUNT;
	}

	

	bool wfmflag = false;
	int wfmindex = 0;
	int radarid = radar.id;
	int agstate = QueueData_TCP()->GetAgilityType(radarid);
	int beamvalue = QueueData_TCP()->GetBeamValue(radarid);

	for (int i = 0; i < param.simEvtCnt; ++i)
	{
		param.seRadBdw[i].bmAzim = package.BeamINfoList[i].iBeamAz;
		ReCliveBmazim(param.seRadBdw[i].bmAzim);

		param.seRadBdw[i].bmElev = package.BeamINfoList[i].iBeamEl;
		param.seRadBdw[i].tmSltNo = package.BeamINfoList[i].iBeamWidthA;
		param.seRadBdw[i].bmDwlTm = package.BeamINfoList[i].uiBeamCutTime;
		param.seRadBdw[i].bmWks = package.BeamINfoList[i].ucWaveType;


// 		if (wfmflag)
// 		{
// 			continue;
// 		}

		if (-1 == agstate)
		{
			agstate = package.BeamINfoList[i].ucAgilityType;
			if (0 != agstate && 1 != agstate)
			{
				std::cout << "�ݱ�״ֵ̬����ȷ,����߼�����" << agstate << std::endl;
				continue;
			}
			QueueData_TCP()->SetAgilityType(radarid, agstate);

		}
		if (-1 == beamvalue && package.BeamINfoList[i].ucAgilityType == wfm_agility_no)
		{
			beamvalue = package.BeamINfoList[i].iBeamWidthE;
			QueueData_TCP()->SetBeamValue(radarid, beamvalue);
		}

		//�ж��Ƿ����л�
		//�ǽݱ� ת �ݱ�
		if (wfm_agility_no == agstate)
		{
			if (package.BeamINfoList[i].ucAgilityType == 0
				&& package.BeamINfoList[i].ucWaveType == 0)
			{
				wfmindex = i;
				wfmflag = true;
				agstate = wfm_agility_yes;
			}

			//��Ƶ��
			if (-1 != beamvalue && package.BeamINfoList[i].iBeamWidthE != beamvalue)
			{
				beamvalue = package.BeamINfoList[i].iBeamWidthE;
				wfmindex = i;
				wfmflag = true;
				QueueData_TCP()->SetBeamValue(radarid, package.BeamINfoList[i].iBeamWidthE);
			}
		}


		//�ݱ� ת �ǽݱ�
		if (wfm_agility_yes == agstate)
		{
			if (package.BeamINfoList[i].ucAgilityType == 1
				&& package.BeamINfoList[i].ucWaveType == 0)
			{
				wfmindex = i;
				wfmflag = true;
				agstate = wfm_agility_no;
				beamvalue = package.BeamINfoList[i].iBeamWidthE;
				QueueData_TCP()->SetBeamValue(radarid, package.BeamINfoList[i].iBeamWidthE);
			}
		}
	}

	//�״��¼��ϱ�-��λ�л�
	//��䳤��
	memset(_buffRadarParam, 0, 657);
	int tmplen = sizeof(int) * 4;
	memcpy(_buffRadarParam, &param, tmplen);
	//memcpy(_buffRadarParam + tmplen, (char *)&param + tmplen, sizeof(int));
	memcpy(_buffRadarParam + tmplen, param.seRadBdw, sizeof(RadBdwNtfPm)*param.simEvtCnt);
	//memcpy(_buffRadarParam + tmplen, (char *)&param + tmplen, sizeof(RadWfmNtfPm));

	_dds->SendDDS(DDSTYPE_RadParmNotify, _buffRadarParam);


	//�״��¼��ϱ�-�����л�
	if (wfmflag)
	{
		QueueData_TCP()->SetAgilityType(radarid, agstate);

		TPC_RadParmNotify wfmparam;
		memset(&wfmparam, 0, sizeof(TPC_RadParmNotify));

		wfmparam.platId = RadarEtt.id;
		wfmparam.emtId = radar.id;
		wfmparam.evtCode = sim_event_wfm;
		wfmparam.simEvtCnt = 1;
		wfmparam.seRadWfm.wfmFreq = package.BeamINfoList[wfmindex].iBeamWidthE * 10 + 3100;//Ƶ��תƵ��
		wfmparam.seRadWfm.wfmAgs = agstate;

		memset(_buffRadarParam, 0, 657);
		int tmplen = sizeof(int) * 4;
		memcpy(_buffRadarParam, &wfmparam, tmplen);
		memcpy(_buffRadarParam + tmplen, &wfmparam.seRadWfm, sizeof(RadWfmNtfPm));

		_dds->SendDDS(DDSTYPE_RadParmNotify, _buffRadarParam);
		std::cout << "�״��¼��ϱ�-���θı�:" << (agstate ? "�ǽݱ�;" : "�ݱ�;") << package.BeamINfoList[wfmindex].iBeamWidthE << std::endl;
	}

}

void MessageReport::RMRadarRunControlReport_tcpfunc(RMRadarRunControlReport & package)
{
// 	if (0 != package.ucWorkStateReturn 
// 		&& 1 != package.ucWorkStateReturn)
// 	{
// 	}
	TPC_SysCtrlReply reply;
	reply.subSysId = 0x00F1;//�״�
	reply.retResult = package.ucWorkStateReturn; 
	_dds->SendDDS(DDSTYPE_SysCtrlReply, &reply);


	//��ȡ�״�ʵ��
	LVCEntityInfo RadarEtt;
	memset(&RadarEtt, 0, sizeof(LVCEntityInfo));
	if (!FileTransfer()->GetRadarEntity(RadarEtt))
	{
		std::cout << "RadarEntity δ�������ļ��ҵ���" << std::endl;
	}

	//Q ��ȡ�״��豸 �ֽ׶�ֻ��һ���״�
	EquipInfo radar;
	radar.id = -1;
	if (!RadarEtt.equipList.empty())
	{
		radar.id = RadarEtt.equipList[0].id;
	}
	else
	{
		std::cout << "�״��豸��ϢΪ�գ�" << std::endl;
	}

	//�״��¼��ϱ�-���ػ�
	
	TPC_RadParmNotify param;
	memset(&param, 0, sizeof(TPC_RadParmNotify));

	param.platId = RadarEtt.id;
	param.emtId = radar.id;
	param.evtCode = sim_event_sw;
	param.simEvtCnt = 1;
	param.seRadSw = package.ucWorkStateReturn;

	if (1 == param.seRadSw)
	{
		param.seRadSw = 0;
	}
	else if (0 == param.seRadSw)
	{
		param.seRadSw = 1;
	}

	//��䳤��
	memset(_buffRadarParam, 0, 657);
	int tmplen = sizeof(int) * 4;
	memcpy(_buffRadarParam, &param, tmplen);
	memcpy(_buffRadarParam + tmplen, &param.seRadSw, sizeof(int));

	_dds->SendDDS(DDSTYPE_RadParmNotify, _buffRadarParam);
	std::cout << "�״��¼��ϱ�-���ػ���" << (param.seRadSw ==0 ? "�ػ�" : "����" )<< std::endl;

}

void MessageReport::RMCACControlStateReport_tcpfunc(RMCACControlStateReport & package)
{
	TPC_BXCControlStateReply reply;
	reply.subSysId = 0x00F2;//��У��
	reply.retResult = package.ucDataSrc;
	_dds->SendDDS(DDSTYPE_SysCtrlReply, &reply);
}

void MessageReport::TPC_ScnDldNotify_tcpfunc(TPC_ScnDldNotify & package)
{
	//Q
	TPC_ScnDldNotify a;
	a.retResult = 0;

	_dds->SendDDS(DDSTYPE_SysDldNotify, &a);
}


void MessageReport::TPC_SysRdyNotify_tcpfunc(TPC_SysRdyNotify & package)
{
	TPC_SysRdyNotify a;
	a.retResult = 0;//QueueData_DDS()->GetTPC_SysRdyNotify_tcpfunc_rs();

	_dds->SendDDS(DDSTYPE_SysRdyNotify, &a);
}

void MessageReport::ReCliveBmazim(int& bmazim)
{
	if (!SceneResolution()->tryGetData())
	{
		//std::cout << "û�г���������Ϣ" << std::endl;
		return;
	}

	TPC_ScnPlatUpdate scnplat = SceneResolution()->GetData_forLook();
	
	ScnPlat radar;
	memset(&radar, 0, sizeof(ScnPlat));
	
	LVCEntityInfo entity;
	FileTransfer()->GetRadarEntity(entity);

	bool findflag = false;
	for (int i = 0; i < scnplat.emtPlatCnt; ++i)
	{
		if (scnplat.emtPlat[i].plat_id == entity.id)
		{
			radar = scnplat.emtPlat[i];
			findflag = true;
			break;
		}
	}

	if (!findflag)
	{
		std::cout << "δ�ҵ�����������Ϣ�е��״�ʵ����Ϣ" << std::endl;
	}


	bmazim -= ToolConfig::Instance()->GetTmpHeading();
	bmazim += radar.hdg*10;

	if (bmazim < -1800)
	{
		bmazim += 3600;
	}
	if (bmazim > 1800)
	{
		bmazim -= 3600;
	}

}

#pragma endregion Tcp������Ϣ����ģ��

