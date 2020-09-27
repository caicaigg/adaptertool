/*************************************************************************/
/*                    Interface Control Agent Software                   */
/*                          Common Utility Lib                           */
/*                                                                       */
/* File    : scenarioLib.h                                              */
/* Author  : Listen                                                      */
/* Date    : 2020.08.18                                                  */
/* Version : v1.0                                                        */
/* Descrip : Header file for scenario parser library                     */
/*************************************************************************/
#ifndef _SCNPARSER_LIB_H_
#define _SCNPARSER_LIB_H_

#include ".\include\commondef.h"

///////////////////////////////////////////////////////////
// Macro Definition
///////////////////////////////////////////////////////////
#define	PI								3.14159265	//圆周率常数
#define C_LIGHT_VEL						300000000	//真空光速(m/s)
#define	EARTH_RADIUS					6371000		//地球曲率半径

///////////////////////////////////////////////////////////
// Function Prototype
///////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C"{
#endif

////////////////////////////////////////////////////////////
// 获取目标距离
DOUBLE GetTargetRange(PLT_ENTITY* own, PLT_ENTITY* tgt);

////////////////////////////////////////////////////////////
// 获取目标方位
DOUBLE GetTargetAzim(PLT_ENTITY* own, PLT_ENTITY* tgt);

////////////////////////////////////////////////////////////
// 获取目标俯仰
DOUBLE GetTargetElev(PLT_ENTITY* own, PLT_ENTITY* tgt);

////////////////////////////////////////////////////////////
// 获取目标径向速度
DOUBLE GetTargetRadialVel(PLT_ENTITY* own, PLT_ENTITY* tgt);

////////////////////////////////////////////////////////////
// 获取目标多普勒频移
DOUBLE GetTargetDopplerRF(PLT_ENTITY* own, PLT_ENTITY* tgt, DWORD rfc);

////////////////////////////////////////////////////////////
// 获取目标RCS值
DOUBLE GetTargetRCS(PLT_ENTITY* own, PLT_ENTITY* tgt, DWORD rfc);

////////////////////////////////////////////////////////////
// 获取雷达阵面方位设置值
DOUBLE GetRadarAtnAzim(PLT_ENTITY* own, PLT_ENTITY* tgt, VEC_DIR* atn, VEC_POS* radPos, VEC_POS* bjcPos);


#ifdef __cplusplus
}
#endif

#endif
