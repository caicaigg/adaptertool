#pragma once
#include "Definedds.h"

class CSceneResolution
{
public:
	CSceneResolution();
	~CSceneResolution();

public:
	void CalcDistance(double &Distance);
	void CalcSpeed(double &Speed);
	void CalcRcs(double &Rcs);

	void AssignData(const SysMotionUpdate& data);
private:
	SysMotionUpdate _data;
};

