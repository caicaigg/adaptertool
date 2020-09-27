#include "stdafx.h"
#include "RadarCore.h"
#include "DataManager.h"
#include "Define.h"

#include <boost/function.hpp>



CRadarCore::CRadarCore()
	:_RClient(new RadarClient())
{

}


CRadarCore::~CRadarCore()
{
}

#define ClientFunc(TypeValue,Data) \
	case TypeValue: \
		if (Data##ptr Data##tmp = boost::dynamic_pointer_cast<Data>(base)) \
		{ \
			Data##_tcpfunc();\
		} \
		break;

bool CRadarCore::Initialize()
{
	bool rs = _RClient->Initialize();
	//_RClient->addTcpType();


	return rs;
}


void CRadarCore::TransferHead(SMessageFormat& Head, const buffer_type & buffer)
{
	_RClient->TransferHead(Head, buffer);
}

void CRadarCore::SendDMCommunicationQueryPackage(const DMCommunicationQueryPackage CommunicationQuery) const
{
	_RClient->sendDMCommunicationQueryPackage(CommunicationQuery);
}

void CRadarCore::SendDMSystemSelfCheckPackage(const DMSystemSelfCheckPackage SelfCheck) const
{
	_RClient->sendDMSystemSelfCheckPackage(SelfCheck);
}

void CRadarCore::SendDMRadarInitConfigPackage(const CENTER2RADAR_INIT RadarInit) const
{
	_RClient->sendDMRadarInitConfigPackage(RadarInit);
}

void CRadarCore::SendDMRadarLocationQueryPackage(const DMRadarLocationQueryPackage LocationQuery) const
{
	_RClient->sendDMRadarLocationQueryPackage(LocationQuery);
}

void CRadarCore::SendDMRunControlPackage(const DMRunControlPackage RunControl) const
{
	_RClient->sendDMRunControlPackage(RunControl);
}

// void CRadarCore::SendDMAalibrationMarkCarInitPackage(const DMAalibrationMarkCarInitPackage AMCInit) const
// {
// 	_RClient->sendDMAalibrationMarkCarInitPackage(AMCInit);
// }

void CRadarCore::SendDMTargetRealTimePackage(const DMTargetRealTimePackage Targets) const
{
	_RClient->sendDMTargetRealTimePackage(Targets);
}


