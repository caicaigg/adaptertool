
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
STATIC DOUBLE  g_real_theta;		//物理空间中目标连线与正北夹角

STATIC DOUBLE  g_scen_hScale;		//仿真空间中雷达所在位置的单位经度跨度
STATIC DOUBLE  g_scen_vScale;		//仿真空间中雷达所在位置的单位纬度跨度

STATIC DOUBLE  g_scen_gamma;		//仿真空间中目标连线与正北夹角
STATIC VEC_POS g_scen_radPos;		//仿真空间中雷达站址坐标



///////////////////////////////////////////////////////////
// 获取目标距离
///////////////////////////////////////////////////////////
DOUBLE GetTargetRange(PLT_ENTITY* own, PLT_ENTITY* tgt)
{
	DOUBLE hScale, vScale, range;
	DOUBLE deltaX, deltaY, deltaZ;

	//计算单位经纬度距离跨度
	hScale = EARTH_RADIUS * cos(own->latitude*PI / 180) * (2 * PI / 360.0);
	vScale = EARTH_RADIUS * (2 * PI / 360.0);

	//计算东北天坐标系距离分量
	deltaX = (tgt->longitude - own->longitude) * hScale;
	deltaY = (tgt->latitude - own->latitude) * vScale;
	deltaZ = (tgt->altitude - own->altitude);

	//计算矢量方向上的连线距离
	range = sqrt(deltaX*deltaX + deltaY*deltaY + deltaZ*deltaZ);
	return range;
}

///////////////////////////////////////////////////////////
// 获取目标方位
///////////////////////////////////////////////////////////
DOUBLE GetTargetAzimuth(PLT_ENTITY* own, PLT_ENTITY* tgt)
{
	DOUBLE hScale, vScale;
	DOUBLE deltaX, deltaY, theta;

	//计算单位经纬度距离跨度
	hScale = EARTH_RADIUS * cos(own->latitude*PI / 180) * (2 * PI / 360.0);
	vScale = EARTH_RADIUS * (2 * PI / 360.0);

	//计算东北天坐标系距离分量
	deltaX = (tgt->longitude - own->longitude) * hScale;
	deltaY = (tgt->latitude - own->latitude) * vScale;

	//计算目标到达角
	if ((deltaY == 0) && (deltaX > 0))//X轴正半轴
	{
		theta = 90;
	}
	else if ((deltaY == 0) && (deltaX < 0))//X轴负半轴
	{
		theta = 270;
	}
	else if ((deltaY > 0) && (deltaX >= 0))//第一象限
	{
		theta = atan(deltaX / deltaY) * 180 / PI;
	}
	else if ((deltaY < 0) && (deltaX >= 0))//第二象限
	{
		theta = atan(deltaX / deltaY) * 180 / PI + 180;
	}
	else if ((deltaY < 0) && (deltaX < 0))//第三象限
	{
		theta = atan(deltaX / deltaY) * 180 / PI + 180;
	}
	else if ((deltaY > 0) && (deltaX < 0))//第四象限
	{
		theta = atan(deltaX / deltaY) * 180 / PI + 360;
	}
	else//原点位置
	{
		theta = 0;
	}

	return theta;
}

///////////////////////////////////////////////////////////
// 获取目标俯仰
///////////////////////////////////////////////////////////
DOUBLE GetTargetElev(PLT_ENTITY* own, PLT_ENTITY* tgt)
{
	DOUBLE hScale, vScale, horzXY;
	DOUBLE deltaX, deltaY, deltaZ, theta;

	//计算单位经纬度距离跨度
	hScale = EARTH_RADIUS * cos(own->latitude*PI / 180) * (2 * PI / 360.0);
	vScale = EARTH_RADIUS * (2 * PI / 360.0);

	//计算东北天坐标系距离分量
	deltaX = (tgt->longitude - own->longitude) * hScale;
	deltaY = (tgt->latitude - own->latitude) * vScale;
	deltaZ = (tgt->altitude - own->altitude);

	//计算径向矢量的水平投影长度
	horzXY = sqrt(deltaX*deltaX + deltaY*deltaY);

	//计算目标俯仰角
	if ((horzXY == 0) && (deltaZ > 0))//Z轴正半轴
	{
		theta = 90;
	}
	else if ((horzXY == 0) && (deltaZ < 0))//Z轴负半轴
	{
		theta = -90;
	}
	else if ((horzXY == 0) && (deltaZ == 0))//原点位置
	{
		theta = 0;
	}
	else//其他
	{
		theta = atan(deltaZ / horzXY) * 180 / PI;
	}

	return theta;
}

///////////////////////////////////////////////////////////
// 获取目标径向速度
///////////////////////////////////////////////////////////
DOUBLE GetTargetRadialVel(PLT_ENTITY* own, PLT_ENTITY* tgt)
{
	DOUBLE unitX, unitY, unitZ;
	DOUBLE hScale, vScale, range;
	DOUBLE deltaX, deltaY, deltaZ;
	DOUBLE v1, v2, radVel;

	//计算单位经纬度距离跨度
	hScale = EARTH_RADIUS * cos(own->latitude*PI / 180) * (2 * PI / 360.0);
	vScale = EARTH_RADIUS * (2 * PI / 360.0);

	//计算东北天坐标系距离分量
	deltaX = (tgt->longitude - own->longitude) * hScale;
	deltaY = (tgt->latitude - own->latitude) * vScale;
	deltaZ = (tgt->altitude - own->altitude);

	//计算东北天坐标系单位径向矢量
	range = sqrt(deltaX*deltaX + deltaY*deltaY + deltaZ*deltaZ);
	unitX = deltaX / range;
	unitY = deltaY / range;
	unitZ = deltaZ / range;

	//计算速度矢量在径向矢量上的投影
	v1 = own->v_east*unitX + own->v_north*unitY + own->v_sky*unitZ;
	v2 = tgt->v_east*unitX + tgt->v_north*unitY + tgt->v_sky*unitZ;

	//计算径向合成速度
	radVel = v1 - v2;
	return radVel;
}

///////////////////////////////////////////////////////////
// 获取目标多普勒频移
///////////////////////////////////////////////////////////
DOUBLE GetTargetDopplerRF(PLT_ENTITY* own, PLT_ENTITY* tgt, DWORD rfc)
{
	DOUBLE radVel, deltaF;
	radVel = GetTargetRadialVel(own, tgt);

	//计算目标回波双程多普勒频移
	deltaF = (double)(rfc)/ C_LIGHT_VEL * radVel * 2;
	return deltaF;
}

///////////////////////////////////////////////////////////
// 获取目标回波衰减
///////////////////////////////////////////////////////////
DOUBLE GetTargetEchoAtten(PLT_ENTITY* own, PLT_ENTITY* tgt)
{
	/*以RCS=10dBsm，距离=10Km条件作为0dB衰减量基准*/
	DOUBLE rcs, range, atten;

	rcs = GetTargetRCS(own, tgt, RADIO_BAND_S);

	range = GetTargetRange(own, tgt);

	atten = 40 * log10(range / 10000) + (10 - rcs);

	return atten;
}

///////////////////////////////////////////////////////////
// 获取目标RCS值
///////////////////////////////////////////////////////////
DOUBLE GetTargetRCS(PLT_ENTITY* own, PLT_ENTITY* tgt, DWORD rfBand)
{
	FLOAT rcs = 0;
	DOUBLE theta, range;
	DOUBLE hScale, vScale;
	DOUBLE unitX, unitY, unitZ;
	DOUBLE deltaX, deltaY, deltaZ;
	DOUBLE velocX, velocY, velocZ;

	//射频频段合法性检查
	if (rfBand >= RADIO_BAND_NUM)
	{
		showLog("--WARNING: GetTargetRCS RF band is out range.\n");
		return (DOUBLE)rcs;
	}

	//计算单位经纬度距离跨度
	hScale = EARTH_RADIUS * cos(own->latitude*PI / 180) * (2 * PI / 360.0);
	vScale = EARTH_RADIUS * (2 * PI / 360.0);

	//计算东北天坐标系距离分量
	deltaX = (tgt->longitude - own->longitude) * hScale;
	deltaY = (tgt->latitude - own->latitude) * vScale;
	deltaZ = (tgt->altitude - own->altitude);

	//计算东北天坐标系单位径向矢量
	range = sqrt(deltaX*deltaX + deltaY*deltaY + deltaZ*deltaZ);
	unitX = deltaX / range;
	unitY = deltaY / range;
	unitZ = deltaZ / range;

	//计算目标航向单位矢量
	velocX = cos(tgt->pitch*PI / 180) * sin(tgt->course*PI / 180);
	velocY = cos(tgt->pitch*PI / 180) * cos(tgt->course*PI / 180);
	velocZ = sin(tgt->pitch*PI / 180);

	//计算距离矢量与航向矢量之间的夹角
	theta = acos((unitX*velocX + unitY*velocY) / sqrt(unitX*unitX + unitY*unitY) / sqrt(velocX*velocX + velocY*velocY));
	theta = theta * 360 / (2 * PI);

	//根据距离/航向矢量夹角确定RCS分布象限
	if ((theta >= 0) && (theta < 45))
	{
		rcs = tgt->rcsTable.rcs_rear[rfBand];//后向
	}
	else if ((theta > 45) && (theta <= 135))
	{
		rcs = tgt->rcsTable.rcs_side[rfBand];//侧向
	}
	else
	{
		rcs = tgt->rcsTable.rcs_head[rfBand];//前向
	}

	return (DOUBLE)rcs;
}

///////////////////////////////////////////////////////////
// 获取雷达阵面方位设置值
///////////////////////////////////////////////////////////
DOUBLE GetRadarAtnAzim(PLT_ENTITY* own, PLT_ENTITY* tgt, VEC_DIR* atn, VEC_POS* radPos, VEC_POS* bjcPos)
{
	DOUBLE realX, realY, realZ;
	DOUBLE theta, cross, gamma, alpha;
	DOUBLE hScale, vScale;
	DOUBLE deltaX, deltaY, deltaZ;
	DOUBLE antenX, antenY, antenZ;

	//计算单位经纬度距离跨度
	hScale = EARTH_RADIUS * cos(own->latitude*PI / 180) * (2 * PI / 360.0);
	vScale = EARTH_RADIUS * (2 * PI / 360.0);

	//计算仿真场景中雷达到目标的距离矢量(东北天坐标系)
	deltaX = (tgt->longitude - own->longitude) * hScale;
	deltaY = (tgt->latitude - own->latitude) * vScale;
	deltaZ = (tgt->altitude - own->altitude);

	//计算仿真场景中雷达天线的方向矢量(东北天坐标系)
	antenX = cos((own->pitch + atn->pitch)*PI / 180) * sin((own->course + atn->jaw)*PI / 180);
	antenY = cos((own->pitch + atn->pitch)*PI / 180) * cos((own->course + atn->jaw)*PI / 180);
	antenZ = sin((own->pitch + atn->pitch)*PI / 180);

	//计算仿真场景中距离矢量与方位矢量在方位面上的投影夹角
	theta = acos((deltaX*antenX + deltaY*antenY) / sqrt(deltaX*deltaX + deltaY*deltaY) / sqrt(antenX*antenX + antenY*antenY));
	cross = deltaX*antenY - deltaY*antenX;
	//theta = (cross<=0)? theta*(-1): theta;
	theta = (cross < 0) ? (2 * PI - theta) : theta;
	theta = theta * 360 / (2 * PI);

	//计算物理空间中雷达到标校车的距离矢量(东北天坐标系)
	realX = (bjcPos->lon - radPos->lon) * hScale;
	realY = (bjcPos->lat - radPos->lat) * vScale;
	realZ = (bjcPos->alt - radPos->alt);

	//计算物理空间中距离矢量与正北矢量在方位面上的投影夹角
	gamma = acos(realY / sqrt(realX*realX + realY*realY));
	gamma = (realX < 0) ? (2 * PI - gamma) : gamma;
	gamma = gamma * 360 / (2 * PI);

	//计算天线阵面预位角度
	alpha = gamma - theta;
	alpha = (alpha < 0) ? (alpha + 360) : alpha;
	alpha = (alpha >= 360) ? (alpha - 360) : alpha;

	return alpha;
}


///////////////////////////////////////////////////////////
// 初始化目标坐标转换功能
///////////////////////////////////////////////////////////
DWORD InitTargetConvert(PLT_ENTITY* own, PLT_ENTITY* tgt, VEC_POS* radPos, VEC_POS* bjcPos)
{
	DOUBLE hScale, vScale;
	DOUBLE realX, realY, realZ;
	DOUBLE deltaX, deltaY, deltaZ;

	//雷达/标校车站址坐标有效性判断
	if ((radPos->lon == 0) && (radPos->lat == 0) && (radPos->alt == 0))
	{
		return (DWORD)ERROR;
	}

	if ((bjcPos->lon == 0) && (bjcPos->lat == 0) && (bjcPos->alt == 0))
	{
		return (DWORD)ERROR;
	}

	//计算单位经纬度距离跨度
	hScale = EARTH_RADIUS * cos(own->latitude*PI / 180) * (2 * PI / 360.0);
	vScale = EARTH_RADIUS * (2 * PI / 360.0);

	//计算仿真空间中雷达到目标的距离矢量(东北天坐标系)
	deltaX = (tgt->longitude - own->longitude) * hScale;
	deltaY = (tgt->latitude - own->latitude) * vScale;
	deltaZ = (tgt->altitude - own->altitude);

	//计算仿真空间中雷达至目标连线与正北夹角
	g_scen_gamma = acos(deltaY / sqrt(deltaX*deltaX + deltaY*deltaY));
	g_scen_gamma = (deltaX < 0) ? (2 * PI - g_scen_gamma) : g_scen_gamma;
	g_scen_gamma = g_scen_gamma * 360 / (2 * PI);

	//计算物理空间中雷达到标校车的距离矢量(东北天坐标系)
	realX = (bjcPos->lon - radPos->lon) * hScale;
	realY = (bjcPos->lat - radPos->lat) * vScale;
	realZ = (bjcPos->alt - radPos->alt);

	//计算物理空间中雷达至标校车连线与正北夹角
	g_real_theta = acos(realY / sqrt(realX*realX + realY*realY));
	g_real_theta = (realX < 0) ? (2 * PI - g_real_theta) : g_real_theta;
	g_real_theta = g_real_theta * 360 / (2 * PI);

	//保存仿真空间中雷达站址坐标
	memset(&g_scen_radPos, 0, sizeof(VEC_POS));
	g_scen_radPos.lon = own->longitude;
	g_scen_radPos.lat = own->latitude;
	g_scen_radPos.alt = own->altitude;
	g_scen_hScale = hScale;
	g_scen_vScale = vScale;

	return (DWORD)OK;
}

///////////////////////////////////////////////////////////
// 目标坐标转换(物理空间->仿真空间)
///////////////////////////////////////////////////////////
DWORD DoTargetConvert(VEC_POS* realPos, VEC_POS* scenPos)
{
	DOUBLE theta, deltaX, deltaY, deltaZ;
	PLT_ENTITY p1, p2;

	//物理点迹坐标有效性判断
	if ((realPos->east == 0) || (realPos->north == 0))
	{
		return (DWORD)ERROR;
	}

	//物理点迹坐标在X-Y平面进行坐标旋转
	theta = (g_real_theta - g_scen_gamma)*PI / 180;
	deltaX = realPos->east*cos(theta) - realPos->north*sin(theta);
	deltaY = realPos->east*sin(theta) + realPos->north*cos(theta);
	deltaZ = realPos->sky;

	//回填转换结果(仿真空间东北天坐标)
	memset(scenPos, 0, sizeof(VEC_POS));
	scenPos->east = deltaX;
	scenPos->north = deltaY;
	scenPos->sky = deltaZ;

	//回填转换结果(仿真空间经纬高坐标)
	scenPos->lon = g_scen_radPos.lon + deltaX / g_scen_hScale;
	scenPos->lat = g_scen_radPos.lat + deltaY / g_scen_vScale;
	scenPos->alt = g_scen_radPos.alt + deltaZ;

	//回填转换结果(仿真空间球坐标)
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
