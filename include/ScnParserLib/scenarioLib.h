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
#define	PI								3.14159265	//Բ���ʳ���
#define C_LIGHT_VEL						300000000	//��չ���(m/s)
#define	EARTH_RADIUS					6371000		//�������ʰ뾶

///////////////////////////////////////////////////////////
// Function Prototype
///////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C"{
#endif

////////////////////////////////////////////////////////////
// ��ȡĿ�����
DOUBLE GetTargetRange(PLT_ENTITY* own, PLT_ENTITY* tgt);

////////////////////////////////////////////////////////////
// ��ȡĿ�귽λ
DOUBLE GetTargetAzim(PLT_ENTITY* own, PLT_ENTITY* tgt);

////////////////////////////////////////////////////////////
// ��ȡĿ�긩��
DOUBLE GetTargetElev(PLT_ENTITY* own, PLT_ENTITY* tgt);

////////////////////////////////////////////////////////////
// ��ȡĿ�꾶���ٶ�
DOUBLE GetTargetRadialVel(PLT_ENTITY* own, PLT_ENTITY* tgt);

////////////////////////////////////////////////////////////
// ��ȡĿ�������Ƶ��
DOUBLE GetTargetDopplerRF(PLT_ENTITY* own, PLT_ENTITY* tgt, DWORD rfc);

////////////////////////////////////////////////////////////
// ��ȡĿ��RCSֵ
DOUBLE GetTargetRCS(PLT_ENTITY* own, PLT_ENTITY* tgt, DWORD rfc);

////////////////////////////////////////////////////////////
// ��ȡ�״����淽λ����ֵ
DOUBLE GetRadarAtnAzim(PLT_ENTITY* own, PLT_ENTITY* tgt, VEC_DIR* atn, VEC_POS* radPos, VEC_POS* bjcPos);


#ifdef __cplusplus
}
#endif

#endif
