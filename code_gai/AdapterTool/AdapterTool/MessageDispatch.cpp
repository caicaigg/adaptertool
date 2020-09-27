#include "stdafx.h"
#include "MessageDispatch.h"

#include <mmsystem.h>
#include <boost/timer.hpp>

#include <ScnParserLib.h>

#include "DataManager.h"
#include "RadarCore.h"
#include "BXCCore.h"
#include "SceneResolution.h"


//void CALLBACK CheckTimeOutFunction(UINT uTimerID, UINT uMsg, DWORD_PTR dwUser, DWORD_PTR dw1, DWORD_PTR dw2)
//{
//// 	MessageDispatch * M = (MessageDispatch*)dwUser;
//// 	M->TPC_SysStqRequest_ddsfunc(nullptr);
//}


MessageDispatch::MessageDispatch(const CRadarCore * Radar, const CBXCCore * Bxc, CSceneResolution* scenres)
	:_radar(Radar)
	,_bxc(Bxc)
	,_scenR(scenres)
{
	_DispatchThread = boost::make_shared<boost::thread>(&MessageDispatch::DDSDataFunction_Thread, this);
	
// 	timeSetEvent(5000,10,CheckTimeOutFunction,(DWORD_PTR)this,TIME_PERIODIC);
// 	timeSetEvent(5000,10,CheckTimeOutFunction,(DWORD_PTR)this,TIME_PERIODIC);
}

MessageDispatch::~MessageDispatch()
{
	//timeKillEvent(nid);
}


#define CASE_DDSTYPE(TypeValue,Data) \
	case TypeValue: \
		{ \
			if(base->data == NULL) std::cout << "base->data null!" <<std::endl;\
			Data Data##tmp; \
			memcpy(&Data##tmp, base->data, sizeof(Data)); \
			if (&Data##tmp) \
			{ \
				Data##_ddsfunc(Data##tmp); \
			} \
			else \
			{ \
				_LOG("ö���ͺţ����������Ͳ�ƥ�䣡"); \
			} \
		} \
		break;

#pragma region DDS�����·���Ϣ����ģ��

void MessageDispatch::DDSDataFunction_Thread()
{
	do
	{
		QueueData_DDS()->WaitCmd();

		if (BaseTypePtr  base = QueueData_DDS()->GetData())
		{
			
			switch (base->type)
			{
 				CASE_DDSTYPE(DDSTYPE_SysResetRequest, TPC_SysResetRequest);
 				CASE_DDSTYPE(DDSTYPE_SysHaltRequest, TPC_SysHaltRequest);
				CASE_DDSTYPE(DDSTYPE_SysBitRequest, TPC_SysBitRequest);
				CASE_DDSTYPE(DDSTYPE_ScnDldRequest, TPC_ScnDldRequest);
				CASE_DDSTYPE(DDSTYPE_SysRdyRequest, TPC_SysRdyRequest);
				//CASE_DDSTYPE(DDSTYPE_SysModeSet, SysModeSet);
				CASE_DDSTYPE(DDSTYPE_SysCtrlRequest, TPC_SysCtrlRequest);
				CASE_DDSTYPE(DDSTYPE_SysStqRequest, TPC_SysStqRequest);
				CASE_DDSTYPE(DDSTYPE_ScnPlatUpdate, TPC_ScnPlatUpdate);
// 				case DDSTYPE_ScnPlatUpdate: 
// 				{ 
// 					if (base->data == NULL) std::cout << "base->data null!" << std::endl;
// 					TPC_ScnPlatUpdate *DataTPC_ScnPlatUpdate = new TPC_ScnPlatUpdate;
// 					memset(DataTPC_ScnPlatUpdate, 0, sizeof(TPC_ScnPlatUpdate));
// 					memcpy(DataTPC_ScnPlatUpdate, base->data, sizeof(TPC_ScnPlatUpdate));
// 					if (DataTPC_ScnPlatUpdate)
// 					{
// 						TPC_ScnPlatUpdate_ddsfunc(*DataTPC_ScnPlatUpdate);
// 					}
// 					else
// 					{
// 						_LOG("ö���ͺţ����������Ͳ�ƥ�䣡"); \
// 					}
// 				} 
// 				break;
				CASE_DDSTYPE(DDSTYPE_RadEventReport, TPC_ScnEmtEvent);//����Դ�¼�
				CASE_DDSTYPE(DDSTYPE_RadPltReport, TPC_RadPltNotify);//�㼣
				CASE_DDSTYPE(DDSTYPE_RadTrkReport, TPC_RadTrkNotify);//����
//				CASE_DDSTYPE(DDSTYPE_ScnEventUpdate, TPC_ScnSimEvent);
// 				CASE_DDSTYPE(DDSTYPE_OwnInsUpdate, UpdateNavigationInfo);
// 				CASE_DDSTYPE(DDSTYPE_ScnMixUpdate, UpdateScenarioData);

			default:
				break;
			}

			//
			delete base->data;

		}

	} while (true);
}



void MessageDispatch::TPC_SysResetRequest_ddsfunc(TPC_SysResetRequest Reset)
{
// 	Reset = boost::make_shared<SysReset>();
// 	Reset->DataType = 0xFF01;

	//Q
}

void MessageDispatch::TPC_SysHaltRequest_ddsfunc(TPC_SysHaltRequest Halt)
{
	//�м�����ݴ���

	//Q
	std::cout << "���п��ƣ���ֹ" << std::endl;
	DMRunControlPackage package;
	package._WorkCodeID = 2;//��ֹ
	_radar->SendDMRunControlPackage(package);
}

void MessageDispatch::TPC_SysBitRequest_ddsfunc(TPC_SysBitRequest SelfCheck)
{
	//Q
	std::cout << "�����Լ�" << std::endl;
	DMSystemSelfCheckPackage package;

	_radar->SendDMSystemSelfCheckPackage(package);

	_bxc->SendDMSystemSelfCheckPackage(package);

	//Q �鹹һ���Լ�ظ�
	//virtualSendtoDDS(_LVC_RM_LDZJSB);
}

void MessageDispatch::TPC_ScnDldRequest_ddsfunc(TPC_ScnDldRequest Load)
{
	//��������˳�� վַ��ѯ->�ȴ��ظ�����->���ؽ�����xml�ļ�->�ظ����ݣ�����->dds�ظ��������

	//�������أ��ļ�
	CDataManager::DMFileLoadTransfer::Instance()->Initialize();
// 	const LVCScenarioFile& scn = CDataManager::DMFileLoadTransfer::Instance()->GetScenarioInfo();
// 	const RadarInfoVec& radar = CDataManager::DMFileLoadTransfer::Instance()->GetRadarsInfo();

	//�״�վַ��ѯ,��ʱ���ڼ�����
	DMRadarLocationQueryPackage package;
	_radar->SendDMRadarLocationQueryPackage(package);


	//Q, �鹹һ�Σ����Լ��ػظ�
	//std::cout << "���ͼ��ػظ�" << std::endl;
	//virtualSendtoDDS(_LVC_TPC_ScnDldNotify);


// 	SMessageFormat Head;
// 	Head._CodeStartSign = 0x1F1F; //�鹹
// 	Head._DataLenth = MSGHEADER;
// 	Head._DataLenth += MSGEND;
// 	Head._SourceAddress = 0;
// 	Head._TargetAddress = 0;
// 	Head._CommandNum = 0;
// 	Head._CommandCode = _LVC_TPC_ScnDldNotify; //Q
// 	Head._Version = VERSION_LVC29;
// 	Head._Property = PROPERTY_LVC29;
// 	Head._MessageOrder = 0;
// 	Head._TotalNumOfMessage = 1;
// 	Head._CurrentSerialNum = 1;
// 
// 	Head._CheckCode = CHECKCODE_LVC29;
// 	Head._CodeEndSign = ENDCODE_LVC29;
// 
// 	buffer_type tmpRecvBuff;
// 	for (int i = 0; i < sizeof(SMessageFormat); ++i)
// 	{
// 		tmpRecvBuff.push_back(*((char*)&Head + i));
// 	}
// 	
// 	QueueData_UDP()->SetData(tmpRecvBuff);

	//Sleep(10);
	//�����Լ�
	//std::cout << "�����Լ�" << std::endl;
	//TPC_SysBitRequest_ddsfunc(TPC_SysBitRequest());

	//Sleep(10);
	//����Ԥλ
	//std::cout << "����Ԥλ" << std::endl;
	//TPC_SysRdyRequest_ddsfunc(TPC_SysRdyRequest());


}

void MessageDispatch::TPC_SysRdyRequest_ddsfunc(TPC_SysRdyRequest PrePosition)
{
	//����ת��
	std::cout << "����Ԥλ" << std::endl;
	CENTER2RADAR_INIT radarinit;
	memset(&radarinit, 0, sizeof(CENTER2RADAR_INIT));

	memcpy(&radarinit, &InitConfig::Instance()->GetRadarInfo(), sizeof(CENTER2RADAR_INIT));

	radarinit.ucStart = 3;//����

	radarinit.usPscCtrl = SceneResolution()->GetAlphaValue()*10;//1194;//����0.1��
	//double tmpHead = 244.13;
	double tmpHead = ToolConfig::Instance()->GetTmpHeading();
	if (radarinit.usPscCtrl - tmpHead > 0)
	{
		radarinit.usPscCtrl -= tmpHead;
	}
	else
	{
		radarinit.usPscCtrl -= tmpHead;
		radarinit.usPscCtrl += 3600;
	}
	if (0 == radarinit.usPscCtrl)
	{
		std::cout << "�ŷ�ת���Ƕ�Ϊ0�ȣ�" << std::endl;
	}

	/*radarinit.disCmdDbf = 0;
	radarinit.disCmdDbfNum = 0;
	radarinit.disCmdShadow = 0;
	radarinit.auxShadowB = 0;
	radarinit.disCmdPower = 0;
	radarinit.disCmdMutiFake = 0;

	radarinit.ucMode = 0;
	radarinit.ucMainPulseFrq = 0;

	radarinit.ucFtCvrPulseFrq = 0;
	radarinit.ucBkCvrPulseFrq = 0;
	radarinit.usMainWaveCode = 0;
	radarinit.ucFtCvrCtrl = 0;
	radarinit.ucBkCvrCtrl = 0;
	radarinit.ucFtCvrDirCtrl = 0;
	radarinit.ucBkCvrDirCtrl = 0;
	radarinit.usFtCvrIntvl = 0;
	radarinit.usBkCvrIntvl = 0;
	radarinit.usFtCvrWaveCode = 0;
	radarinit.usBkCvrWaveCode = 0;
	radarinit.uiFtCvrA = 0;
	radarinit.iFtCvrE = 0;
	radarinit.uiBkCvrA = 0;
	radarinit.iBkCvrE = 0;

	radarinit.ucPassFollow = 0;

	radarinit.ucSectorEf[0] = 0;
	radarinit.ucSectorEf[1] = 0;
	radarinit.stSector[0].usStartA = 0;
	radarinit.stSector[0].usEndA = 0;
	radarinit.stSector[0].usStartE = 0;
	radarinit.stSector[0].usEndE = 0;

	radarinit.stSector[1].usStartA = 0;
	radarinit.stSector[1].usEndA = 0;
	radarinit.stSector[1].usStartE = 0;
	radarinit.stSector[1].usEndE = 0;

	radarinit.disCmdAsync = 0;

	radarinit.ucSearchArea1 = 1;
	radarinit.stSearchAreaData[0].usStartA = 600;
	radarinit.stSearchAreaData[0].usEndA = 900;
	radarinit.stSearchAreaData[0].usStartE = 300;
	radarinit.stSearchAreaData[0].usEndE = 600;*/

	//�״��ʼ������
	_radar->SendDMRadarInitConfigPackage(radarinit);

	//Ԥλ��ʱ�ȴ��̣߳�1000ms ��ʼ�жϳ�ʱ
	boost::thread* thr = new boost::thread(&MessageDispatch::waitRdyRequestback, this, 2000);
}

void MessageDispatch::SysModeSet_ddsfunc(SysModeSetptr ModeSet)
{
	//Q
}

void MessageDispatch::TPC_SysCtrlRequest_ddsfunc(TPC_SysCtrlRequest RunControl)
{
	std::cout << "�յ����п��ƣ�" << ((RunControl.cmdCode == 0) ? "��ʼ" : "����" )<< std::endl;

	if (0 == RunControl.cmdCode)
	{
		DMAalibrationMarkCarInitPackage statePackage;
		statePackage._ScenarioMode = 0;
		statePackage._TargetTotalNum = 0;
		_bxc->SendDMAalibrationMarkCarInitPackage(statePackage);
	}
	DMRunControlPackage package;
	package._WorkCodeID = RunControl.cmdCode;//���У�
	_radar->SendDMRunControlPackage(package);
}

void MessageDispatch::TPC_SysStqRequest_ddsfunc(TPC_SysStqRequest StateSeek)
{

	//ͨ�Ų�ѯ
	DMCommunicationQueryPackage package;

	_radar->SendDMCommunicationQueryPackage(package);

	_bxc->SendDMCommunicationQueryPackage(package);
}

void MessageDispatch::TPC_ScnPlatUpdate_ddsfunc(TPC_ScnPlatUpdate MotionUpdate)
{
//	std::cout << "in TPC_ScnPlatUpdate_ddsfunc()" << std::endl;
	
	for (int i = 0; i < MotionUpdate.sutPlatCnt; ++i)
	{
		double tlon = MotionUpdate.sutPlat[i].lon;
		double tlat = MotionUpdate.sutPlat[i].lat;
		MotionUpdate.sutPlat[i].lon = tlon / 1e7;
		MotionUpdate.sutPlat[i].lat = tlat / 1e7;
	}

	for (int i = 0; i < MotionUpdate.emtPlatCnt; ++i)
	{
		double tlon = MotionUpdate.emtPlat[i].lon;
		double tlat = MotionUpdate.emtPlat[i].lat;
		MotionUpdate.emtPlat[i].lon = tlon / 1e7;
		MotionUpdate.emtPlat[i].lat = tlat / 1e7;
	}

	SceneResolution()->SetData(MotionUpdate);

// 	std::cout << "�յ��������£�lon:" << MotionUpdate.sutPlat[0].lon <<
// 		"lat:" << MotionUpdate.sutPlat[0].lat << std::endl;
	//_scenR->AssignData(*MotionUpdate);
	double dis = 0;
	double rcs = 0;
	double speed = 0;
	_scenR->CalcDistance(dis);
	_scenR->CalcRcs(rcs);
	_scenR->CalcSpeed(speed);

	//DMTargetRealTimePackage RealTimePackage;
	//RealTimePackage._TargetTotalNum = 1;
	//DMAMCInitializeOfTarget info;
	//info._TargetDistance = 5;
	//info._TargetVelocity = 100;
	//info._TargetFrequencyShift = 200;
	//info._TargetWorkingFrequency = 40000;
	//info._TargetRCS = 10;
	//info._TargetRCSMode = 0;
	//info._TargetReceiveDecay = 200;
	//info._TargetSendDecayI = 200;
	//info._TargetSendDecayII = 200;
	//info._TargetSendDecayIII = 200;
	//RealTimePackage._TargretInformation.push_back(info);

	//_radar->SendDMTargetRealTimePackage(RealTimePackage);

	//Q ������룬˥����rcs

// 	PLT_RCS rcs_s;
// 
// 
//  	PLT_ENTITY entity;
// 	entity.nID = 1;
// 	entity.platType = 1;
// 	entity.enemyAttr = 1;
// 	memcpy(entity.strPrompt, "����" ,4);
// 	entity.longitude = 104.06;
// 	entity.latitude = 30.67;
// 	entity.altitude = 400;
// 	entity.course = 53;
// 	entity.pitch = 0;
// 	entity.across = 0;
// 	entity.v_east = 0;
// 	entity.v_north = 0;
// 	entity.v_sky = 0;
// 	//entity.rcsTable = 
//  	PLT_ENTITY target;
// 	GetTargetRange(&entity,&target);
// 
// 
// 	//��У�� ��Ϣ
// 	BGC2_TO_TS ts;
// 	ts.ucWorkState = 0;
// 	ts.ucTSWKfrq = 200;
// 	ts.ucTSRCSsevro = 0;
// 	ts.ucTSrecvAtt = 63;
// 	ts.ucTSemsnAtt[0] = 1;
// 	ts.ucTSemsnAtt[1] = 2;
// 	ts.ucTSemsnAtt[2] = 3;
// 	ts.ucTSdataEffect = 1;
// 	ts.ucTarSt = 1;
// 	for (int i = 0; i < 3; ++i)
// 	{
// 		ts.stTOTsInfo[i].R[0] = 10;
// 		ts.stTOTsInfo[i].R[1] = 20;
// 		ts.stTOTsInfo[i].R[2] = 30;
// 
// 		ts.stTOTsInfo[i].V[0] = 200;
// 		ts.stTOTsInfo[i].V[1] = 200;
// 		ts.stTOTsInfo[i].V[2] = 200;
// 
// 		ts.stTOTsInfo[i].Freq[0] = 10000;
// 		ts.stTOTsInfo[i].Freq[1] = 10000;
// 		ts.stTOTsInfo[i].Freq[2] = 10000;
// 
// 		ts.stTOTsInfo[i].IfFreMove = 0;
// 	}
// 	_bxc->SendBGC2_TO_TSPackage(ts);

}

void MessageDispatch::TPC_ScnEmtEvent_ddsfunc(TPC_ScnEmtEvent EmtEvent)
{

}

void MessageDispatch::TPC_RadPltNotify_ddsfunc(TPC_RadPltNotify Tarce)
{

}

void MessageDispatch::TPC_RadTrkNotify_ddsfunc(TPC_RadTrkNotify track)
{

}

void MessageDispatch::TPC_ScnSimEvent_ddsfunc(TPC_ScnSimEvent EventPub)
{
	//Q
}

void MessageDispatch::UpdateNavigationInfo_ddsfunc(UpdateNavigationInfoptr UpdateNavigation)
{
	//���͸�SUT���䵥Ԫ
}

void MessageDispatch::UpdateScenarioData_ddsfunc(UpdateScenarioDataptr UpdateScenario)
{
	//��
}


void MessageDispatch::waitRdyRequestback(int times)
{
	if (0 == times)
	{
		times = 2000;
	}
// 	boost::posix_time::ptime time = boost::posix_time::microsec_clock::local_time();
// 	bool rs = QueueData_DDS()->WaitRdyRequest(times);
// 	if (rs) //false: time out; true: posted;
// 	{
// 		return;
// 	}
	Sleep(times);
	
	if (!QueueData_DDS()->WaitRdyRequest(0))
	{
		//��ʱ 
		QueueData_DDS()->SetTPC_SysRdyNotify_tcpfunc_rs(1);
		std::cout << "Ԥλ�ظ���ʱ�� �Զ��ظ�Ԥλ" << std::endl;
		virtualSendtoDDS(_LVC_TPC_SysRdyNotify);
		// int TPC_SysRdyNotify_tcpfunc_rs;
	
	}
}

void MessageDispatch::virtualSendtoDDS(int type)
{
	SMessageFormat Head;
	Head._CodeStartSign = 0x1F1F; //�鹹
	Head._DataLenth = MSGHEADER;
	Head._DataLenth += MSGEND;
	Head._SourceAddress = 0;
	Head._TargetAddress = 0;
	Head._CommandNum = 0;
	Head._CommandCode = type; //Q
	Head._Version = VERSION_LVC29;
	Head._Property = PROPERTY_LVC29;
	Head._MessageOrder = 0;
	Head._TotalNumOfMessage = 1;
	Head._CurrentSerialNum = 1;

	Head._CheckCode = CHECKCODE_LVC29;
	Head._CodeEndSign = ENDCODE_LVC29;

	buffer_type tmpRecvBuff;
	for (int i = 0; i < sizeof(SMessageFormat); ++i)
	{
		tmpRecvBuff.push_back(*((char*)&Head + i));
	}

	QueueData_TCP()->SetData(tmpRecvBuff);
}

#pragma endregion DDS������Ϣ����ģ��
