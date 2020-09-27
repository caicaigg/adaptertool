#include "stdafx.h"
#include "SceneResolution.h"


CSceneResolution::CSceneResolution()
{
}


CSceneResolution::~CSceneResolution()
{
}

void CSceneResolution::CalcDistance(double & Distance)
{
	Distance = 10000;
}

void CSceneResolution::CalcSpeed(double & Speed)
{
	Speed = 20;
}

void CSceneResolution::CalcRcs(double & Rcs)
{
	
	Rcs = 0.1;
}

void CSceneResolution::AssignData(const SysMotionUpdate& data)
{
	_data = data;
}
