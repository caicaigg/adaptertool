
/*************************************************************************/
/*                    Interface Control Agent Software                   */
/*                          Common Utility Lib                           */
/*                                                                       */
/* File    : ScnParserLib.c                                              */
/* Author  : Listen                                                      */
/* Date    : 2020.08.18                                                  */
/* Version : v1.0                                                        */
/* Descrip : Method implement for scenario parser library                */
/*************************************************************************/
#include "stdafx.h"
#include <math.h>
#include "utility.h"
#include "ScnParserLib.h"


#define  showLog(s) printf(s)

///////////////////////////////////////////////////////////
// Static Variables
///////////////////////////////////////////////////////////
STATIC DOUBLE  g_real_theta;		//����ռ���Ŀ�������������н�

STATIC DOUBLE  g_scen_hScale;		//����ռ����״�����λ�õĵ�λ���ȿ��
STATIC DOUBLE  g_scen_vScale;		//����ռ����״�����λ�õĵ�λγ�ȿ��

STATIC DOUBLE  g_scen_gamma;		//����ռ���Ŀ�������������н�
STATIC VEC_POS g_scen_radPos;		//����ռ����״�վַ����



///////////////////////////////////////////////////////////
// ��ȡĿ�����
///////////////////////////////////////////////////////////
DOUBLE GetTargetRange(PLT_ENTITY* own, PLT_ENTITY* tgt)
{
	DOUBLE hScale, vScale, range;
	DOUBLE deltaX, deltaY, deltaZ;

	//���㵥λ��γ�Ⱦ�����
	hScale = EARTH_RADIUS * cos(own->latitude*PI / 180) * (2 * PI / 360.0);
	vScale = EARTH_RADIUS * (2 * PI / 360.0);

	//���㶫��������ϵ�������
	deltaX = (tgt->longitude - own->longitude) * hScale;
	deltaY = (tgt->latitude - own->latitude) * vScale;
	deltaZ = (tgt->altitude - own->altitude);

	//����ʸ�������ϵ����߾���
	range = sqrt(deltaX*deltaX + deltaY*deltaY + deltaZ*deltaZ);
	return range;
}

///////////////////////////////////////////////////////////
// ��ȡĿ�귽λ
///////////////////////////////////////////////////////////
DOUBLE GetTargetAzimuth(PLT_ENTITY* own, PLT_ENTITY* tgt)
{
	DOUBLE hScale, vScale;
	DOUBLE deltaX, deltaY, theta;

	//���㵥λ��γ�Ⱦ�����
	hScale = EARTH_RADIUS * cos(own->latitude*PI / 180) * (2 * PI / 360.0);
	vScale = EARTH_RADIUS * (2 * PI / 360.0);

	//���㶫��������ϵ�������
	deltaX = (tgt->longitude - own->longitude) * hScale;
	deltaY = (tgt->latitude - own->latitude) * vScale;

	//����Ŀ�굽���
	if ((deltaY == 0) && (deltaX > 0))//X��������
	{
		theta = 90;
	}
	else if ((deltaY == 0) && (deltaX < 0))//X�Ḻ����
	{
		theta = 270;
	}
	else if ((deltaY > 0) && (deltaX >= 0))//��һ����
	{
		theta = atan(deltaX / deltaY) * 180 / PI;
	}
	else if ((deltaY < 0) && (deltaX >= 0))//�ڶ�����
	{
		theta = atan(deltaX / deltaY) * 180 / PI + 180;
	}
	else if ((deltaY < 0) && (deltaX < 0))//��������
	{
		theta = atan(deltaX / deltaY) * 180 / PI + 180;
	}
	else if ((deltaY > 0) && (deltaX < 0))//��������
	{
		theta = atan(deltaX / deltaY) * 180 / PI + 360;
	}
	else//ԭ��λ��
	{
		theta = 0;
	}

	return theta;
}

///////////////////////////////////////////////////////////
// ��ȡĿ�긩��
///////////////////////////////////////////////////////////
DOUBLE GetTargetElev(PLT_ENTITY* own, PLT_ENTITY* tgt)
{
	DOUBLE hScale, vScale, horzXY;
	DOUBLE deltaX, deltaY, deltaZ, theta;

	//���㵥λ��γ�Ⱦ�����
	hScale = EARTH_RADIUS * cos(own->latitude*PI / 180) * (2 * PI / 360.0);
	vScale = EARTH_RADIUS * (2 * PI / 360.0);

	//���㶫��������ϵ�������
	deltaX = (tgt->longitude - own->longitude) * hScale;
	deltaY = (tgt->latitude - own->latitude) * vScale;
	deltaZ = (tgt->altitude - own->altitude);

	//���㾶��ʸ����ˮƽͶӰ����
	horzXY = sqrt(deltaX*deltaX + deltaY*deltaY);

	//����Ŀ�긩����
	if ((horzXY == 0) && (deltaZ > 0))//Z��������
	{
		theta = 90;
	}
	else if ((horzXY == 0) && (deltaZ < 0))//Z�Ḻ����
	{
		theta = -90;
	}
	else if ((horzXY == 0) && (deltaZ == 0))//ԭ��λ��
	{
		theta = 0;
	}
	else//����
	{
		theta = atan(deltaZ / horzXY) * 180 / PI;
	}

	return theta;
}

///////////////////////////////////////////////////////////
// ��ȡĿ�꾶���ٶ�
///////////////////////////////////////////////////////////
DOUBLE GetTargetRadialVel(PLT_ENTITY* own, PLT_ENTITY* tgt)
{
	DOUBLE unitX, unitY, unitZ;
	DOUBLE hScale, vScale, range;
	DOUBLE deltaX, deltaY, deltaZ;
	DOUBLE v1, v2, radVel;

	//���㵥λ��γ�Ⱦ�����
	hScale = EARTH_RADIUS * cos(own->latitude*PI / 180) * (2 * PI / 360.0);
	vScale = EARTH_RADIUS * (2 * PI / 360.0);

	//���㶫��������ϵ�������
	deltaX = (tgt->longitude - own->longitude) * hScale;
	deltaY = (tgt->latitude - own->latitude) * vScale;
	deltaZ = (tgt->altitude - own->altitude);

	//���㶫��������ϵ��λ����ʸ��
	range = sqrt(deltaX*deltaX + deltaY*deltaY + deltaZ*deltaZ);
	unitX = deltaX / range;
	unitY = deltaY / range;
	unitZ = deltaZ / range;

	//�����ٶ�ʸ���ھ���ʸ���ϵ�ͶӰ
	v1 = own->v_east*unitX + own->v_north*unitY + own->v_sky*unitZ;
	v2 = tgt->v_east*unitX + tgt->v_north*unitY + tgt->v_sky*unitZ;

	//���㾶��ϳ��ٶ�
	radVel = v1 - v2;
	return radVel;
}

///////////////////////////////////////////////////////////
// ��ȡĿ�������Ƶ��
///////////////////////////////////////////////////////////
DOUBLE GetTargetDopplerRF(PLT_ENTITY* own, PLT_ENTITY* tgt, DWORD rfc)
{
	DOUBLE radVel, deltaF;
	radVel = GetTargetRadialVel(own, tgt);

	//����Ŀ��ز�˫�̶�����Ƶ��
	deltaF = (double)(rfc)/ C_LIGHT_VEL * radVel * 2;
	return deltaF;
}

///////////////////////////////////////////////////////////
// ��ȡĿ��ز�˥��
///////////////////////////////////////////////////////////
DOUBLE GetTargetEchoAtten(PLT_ENTITY* own, PLT_ENTITY* tgt)
{
	/*��RCS=10dBsm������=10Km������Ϊ0dB˥������׼*/
	DOUBLE rcs, range, atten;

	rcs = GetTargetRCS(own, tgt, RADIO_BAND_S);

	range = GetTargetRange(own, tgt);

	atten = 40 * log10(range / 10000) + (10 - rcs);

	return atten;
}

///////////////////////////////////////////////////////////
// ��ȡĿ��RCSֵ
///////////////////////////////////////////////////////////
DOUBLE GetTargetRCS(PLT_ENTITY* own, PLT_ENTITY* tgt, DWORD rfBand)
{
	FLOAT rcs = 0;
	DOUBLE theta, range;
	DOUBLE hScale, vScale;
	DOUBLE unitX, unitY, unitZ;
	DOUBLE deltaX, deltaY, deltaZ;
	DOUBLE velocX, velocY, velocZ;

	//��ƵƵ�κϷ��Լ��
	if (rfBand >= RADIO_BAND_NUM)
	{
		showLog("--WARNING: GetTargetRCS RF band is out range.\n");
		return (DOUBLE)rcs;
	}

	//���㵥λ��γ�Ⱦ�����
	hScale = EARTH_RADIUS * cos(own->latitude*PI / 180) * (2 * PI / 360.0);
	vScale = EARTH_RADIUS * (2 * PI / 360.0);

	//���㶫��������ϵ�������
	deltaX = (tgt->longitude - own->longitude) * hScale;
	deltaY = (tgt->latitude - own->latitude) * vScale;
	deltaZ = (tgt->altitude - own->altitude);

	//���㶫��������ϵ��λ����ʸ��
	range = sqrt(deltaX*deltaX + deltaY*deltaY + deltaZ*deltaZ);
	unitX = deltaX / range;
	unitY = deltaY / range;
	unitZ = deltaZ / range;

	//����Ŀ�꺽��λʸ��
	velocX = cos(tgt->pitch*PI / 180) * sin(tgt->course*PI / 180);
	velocY = cos(tgt->pitch*PI / 180) * cos(tgt->course*PI / 180);
	velocZ = sin(tgt->pitch*PI / 180);

	//�������ʸ���뺽��ʸ��֮��ļн�
	theta = acos((unitX*velocX + unitY*velocY) / sqrt(unitX*unitX + unitY*unitY) / sqrt(velocX*velocX + velocY*velocY));
	theta = theta * 360 / (2 * PI);

	//���ݾ���/����ʸ���н�ȷ��RCS�ֲ�����
	if ((theta >= 0) && (theta < 45))
	{
		rcs = tgt->rcsTable.rcs_rear[rfBand];//����
	}
	else if ((theta > 45) && (theta <= 135))
	{
		rcs = tgt->rcsTable.rcs_side[rfBand];//����
	}
	else
	{
		rcs = tgt->rcsTable.rcs_head[rfBand];//ǰ��
	}

	return (DOUBLE)rcs;
}

///////////////////////////////////////////////////////////
// ��ȡ�״����淽λ����ֵ
///////////////////////////////////////////////////////////
DOUBLE GetRadarAtnAzim(PLT_ENTITY* own, PLT_ENTITY* tgt, VEC_DIR* atn, VEC_POS* radPos, VEC_POS* bjcPos)
{
	DOUBLE realX, realY, realZ;
	DOUBLE theta, cross, gamma, alpha;
	DOUBLE hScale, vScale;
	DOUBLE deltaX, deltaY, deltaZ;
	DOUBLE antenX, antenY, antenZ;

	//���㵥λ��γ�Ⱦ�����
	hScale = EARTH_RADIUS * cos(own->latitude*PI / 180) * (2 * PI / 360.0);
	vScale = EARTH_RADIUS * (2 * PI / 360.0);

	//������泡�����״ﵽĿ��ľ���ʸ��(����������ϵ)
	deltaX = (tgt->longitude - own->longitude) * hScale;
	deltaY = (tgt->latitude - own->latitude) * vScale;
	deltaZ = (tgt->altitude - own->altitude);

	//������泡�����״����ߵķ���ʸ��(����������ϵ)
	antenX = cos((own->pitch + atn->pitch)*PI / 180) * sin((own->course + atn->jaw)*PI / 180);
	antenY = cos((own->pitch + atn->pitch)*PI / 180) * cos((own->course + atn->jaw)*PI / 180);
	antenZ = sin((own->pitch + atn->pitch)*PI / 180);

	//������泡���о���ʸ���뷽λʸ���ڷ�λ���ϵ�ͶӰ�н�
	theta = acos((deltaX*antenX + deltaY*antenY) / sqrt(deltaX*deltaX + deltaY*deltaY) / sqrt(antenX*antenX + antenY*antenY));
	cross = deltaX*antenY - deltaY*antenX;
	//theta = (cross<=0)? theta*(-1): theta;
	theta = (cross < 0) ? (2 * PI - theta) : theta;
	theta = theta * 360 / (2 * PI);

	//��������ռ����״ﵽ��У���ľ���ʸ��(����������ϵ)
	realX = (bjcPos->lon - radPos->lon) * hScale;
	realY = (bjcPos->lat - radPos->lat) * vScale;
	realZ = (bjcPos->alt - radPos->alt);

	//��������ռ��о���ʸ��������ʸ���ڷ�λ���ϵ�ͶӰ�н�
	gamma = acos(realY / sqrt(realX*realX + realY*realY));
	gamma = (realX < 0) ? (2 * PI - gamma) : gamma;
	gamma = gamma * 360 / (2 * PI);

	//������������Ԥλ�Ƕ�
	alpha = gamma - theta;
	alpha = (alpha < 0) ? (alpha + 360) : alpha;
	alpha = (alpha >= 360) ? (alpha - 360) : alpha;

	return alpha;
}


///////////////////////////////////////////////////////////
// ��ʼ��Ŀ������ת������
///////////////////////////////////////////////////////////
DWORD InitTargetConvert(PLT_ENTITY* own, PLT_ENTITY* tgt, VEC_POS* radPos, VEC_POS* bjcPos)
{
	DOUBLE hScale, vScale;
	DOUBLE realX, realY, realZ;
	DOUBLE deltaX, deltaY, deltaZ;

	//�״�/��У��վַ������Ч���ж�
	if ((radPos->lon == 0) && (radPos->lat == 0) && (radPos->alt == 0))
	{
		return (DWORD)ERROR;
	}

	if ((bjcPos->lon == 0) && (bjcPos->lat == 0) && (bjcPos->alt == 0))
	{
		return (DWORD)ERROR;
	}

	//���㵥λ��γ�Ⱦ�����
	hScale = EARTH_RADIUS * cos(own->latitude*PI / 180) * (2 * PI / 360.0);
	vScale = EARTH_RADIUS * (2 * PI / 360.0);

	//�������ռ����״ﵽĿ��ľ���ʸ��(����������ϵ)
	deltaX = (tgt->longitude - own->longitude) * hScale;
	deltaY = (tgt->latitude - own->latitude) * vScale;
	deltaZ = (tgt->altitude - own->altitude);

	//�������ռ����״���Ŀ�������������н�
	g_scen_gamma = acos(deltaY / sqrt(deltaX*deltaX + deltaY*deltaY));
	g_scen_gamma = (deltaX < 0) ? (2 * PI - g_scen_gamma) : g_scen_gamma;
	g_scen_gamma = g_scen_gamma * 360 / (2 * PI);

	//��������ռ����״ﵽ��У���ľ���ʸ��(����������ϵ)
	realX = (bjcPos->lon - radPos->lon) * hScale;
	realY = (bjcPos->lat - radPos->lat) * vScale;
	realZ = (bjcPos->alt - radPos->alt);

	//��������ռ����״�����У�������������н�
	g_real_theta = acos(realY / sqrt(realX*realX + realY*realY));
	g_real_theta = (realX < 0) ? (2 * PI - g_real_theta) : g_real_theta;
	g_real_theta = g_real_theta * 360 / (2 * PI);

	//�������ռ����״�վַ����
	memset(&g_scen_radPos, 0, sizeof(VEC_POS));
	g_scen_radPos.lon = own->longitude;
	g_scen_radPos.lat = own->latitude;
	g_scen_radPos.alt = own->altitude;
	g_scen_hScale = hScale;
	g_scen_vScale = vScale;

	return (DWORD)OK;
}

///////////////////////////////////////////////////////////
// Ŀ������ת��(����ռ�->����ռ�)
///////////////////////////////////////////////////////////
DWORD DoTargetConvert(VEC_POS* realPos, VEC_POS* scenPos)
{
	DOUBLE theta, deltaX, deltaY, deltaZ;
	PLT_ENTITY p1, p2;

	//����㼣������Ч���ж�
	if ((realPos->east == 0) || (realPos->north == 0))
	{
		return (DWORD)ERROR;
	}

	//����㼣������X-Yƽ�����������ת
	theta = (g_real_theta - g_scen_gamma)*PI / 180;
	deltaX = realPos->east*cos(theta) - realPos->north*sin(theta);
	deltaY = realPos->east*sin(theta) + realPos->north*cos(theta);
	deltaZ = realPos->sky;

	//����ת�����(����ռ䶫��������)
	memset(scenPos, 0, sizeof(VEC_POS));
	scenPos->east = deltaX;
	scenPos->north = deltaY;
	scenPos->sky = deltaZ;

	//����ת�����(����ռ侭γ������)
	scenPos->lon = g_scen_radPos.lon + deltaX / g_scen_hScale;
	scenPos->lat = g_scen_radPos.lat + deltaY / g_scen_vScale;
	scenPos->alt = g_scen_radPos.alt + deltaZ;

	//����ת�����(����ռ�������)
	memset(&p1, 0, sizeof(PLT_ENTITY));
	p1.longitude = g_scen_radPos.lon;
	p1.latitude = g_scen_radPos.lat;
	p1.altitude = g_scen_radPos.alt;

	memset(&p2, 0, sizeof(PLT_ENTITY));
	p2.longitude = scenPos->lon;
	p2.latitude = scenPos->lat;
	p2.altitude = scenPos->alt;

	scenPos->azim = GetTargetAzimuth(&p1, &p2);
	scenPos->pitch = GetTargetElev(&p1, &p2);
	scenPos->range = GetTargetRange(&p1, &p2);

	return (DWORD)OK;
}
