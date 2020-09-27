#include "stdafx.h"
#include "BXCCore.h"


CBXCCore::CBXCCore()
	:_BClient(new BXCClient())
{
}


CBXCCore::~CBXCCore()
{
}

bool CBXCCore::Initialize()
{
	bool rs = _BClient->Initialize();
	return rs;
}

void CBXCCore::SendBGC2_TO_TSPackage(const BGC2_TO_TS Data) const
{
	_BClient->sendBGC2_TO_TSPackage(Data);
}

void CBXCCore::SendDMCommunicationQueryPackage(const DMCommunicationQueryPackage CommunicationQuery) const
{
	_BClient->sendDMCommunicationQueryPackage(CommunicationQuery);
}

void CBXCCore::SendDMSystemSelfCheckPackage(const DMSystemSelfCheckPackage SelfCheck) const
{
	_BClient->sendDMSystemSelfCheckPackage(SelfCheck);
}

void CBXCCore::SendDMAalibrationMarkCarInitPackage(const DMAalibrationMarkCarInitPackage ControlState) const
{
	_BClient->sendDMAalibrationMarkCarInitPackage(ControlState);
}
