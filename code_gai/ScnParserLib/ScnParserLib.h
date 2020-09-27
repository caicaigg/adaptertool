#ifndef _SCNPARSER_LIB_H_
#define _SCNPARSER_LIB_H_

#include "ScnParserGlobal.h"
#include "commondef.h"


///////////////////////////////////////////////////////////
// Macro Definition
///////////////////////////////////////////////////////////
#define	PI								3.1415926	//圆周率常数
#define C_LIGHT_VEL						300000000	//真空光速(m/s)
#define	EARTH_RADIUS					6371000		//地球曲率半径


// 获取目标距离
DOUBLE SCNPARSERLIB_DECL GetTargetRange(PLT_ENTITY* own, PLT_ENTITY* tgt);

// 获取目标方位
DOUBLE SCNPARSERLIB_DECL GetTargetAzimuth(PLT_ENTITY* own, PLT_ENTITY* tgt);

// 获取目标俯仰
DOUBLE SCNPARSERLIB_DECL GetTargetElev(PLT_ENTITY* own, PLT_ENTITY* tgt);

// 获取目标径向速度
DOUBLE SCNPARSERLIB_DECL GetTargetRadialVel(PLT_ENTITY* own, PLT_ENTITY* tgt);

// 获取目标多普勒频移
DOUBLE SCNPARSERLIB_DECL GetTargetDopplerRF(PLT_ENTITY* own, PLT_ENTITY* tgt, DWORD rfc);

// 获取目标RCS值
DOUBLE SCNPARSERLIB_DECL GetTargetRCS(PLT_ENTITY* own, PLT_ENTITY* tgt, DWORD rfBand);

// 获取目标回波衰减
DOUBLE SCNPARSERLIB_DECL GetTargetEchoAtten(PLT_ENTITY* own, PLT_ENTITY* tgt);

////////////////////////////////////////////////////////////
// 获取雷达阵面方位设置值
//
// own: xml读取自身雷达位置
// tgt: xml读取目标位置
// atn: xml读取雷达设备天线
// radpos: 站址报文查询 radar位置
// bjcpos: 站址报文查询 bjc位置
DOUBLE SCNPARSERLIB_DECL GetRadarAtnAzim(PLT_ENTITY* own, PLT_ENTITY* tgt, VEC_DIR* atn, VEC_POS* radPos, VEC_POS* bjcPos);


// 初始化目标坐标转换功能
DWORD  SCNPARSERLIB_DECL InitTargetConvert(PLT_ENTITY* own, PLT_ENTITY* tgt, VEC_POS* radPos, VEC_POS* bjcPos);

// 目标坐标转换(物理空间->仿真空间)
DWORD  SCNPARSERLIB_DECL DoTargetConvert(VEC_POS* realPos, VEC_POS* scenPos);

#endif