#ifndef _SCNPARSER_LIB_H_
#define _SCNPARSER_LIB_H_

#include "ScnParserGlobal.h"
#include "commondef.h"


///////////////////////////////////////////////////////////
// Macro Definition
///////////////////////////////////////////////////////////
#define	PI								3.1415926	//Բ���ʳ���
#define C_LIGHT_VEL						300000000	//��չ���(m/s)
#define	EARTH_RADIUS					6371000		//�������ʰ뾶


// ��ȡĿ�����
DOUBLE SCNPARSERLIB_DECL GetTargetRange(PLT_ENTITY* own, PLT_ENTITY* tgt);

// ��ȡĿ�귽λ
DOUBLE SCNPARSERLIB_DECL GetTargetAzimuth(PLT_ENTITY* own, PLT_ENTITY* tgt);

// ��ȡĿ�긩��
DOUBLE SCNPARSERLIB_DECL GetTargetElev(PLT_ENTITY* own, PLT_ENTITY* tgt);

// ��ȡĿ�꾶���ٶ�
DOUBLE SCNPARSERLIB_DECL GetTargetRadialVel(PLT_ENTITY* own, PLT_ENTITY* tgt);

// ��ȡĿ�������Ƶ��
DOUBLE SCNPARSERLIB_DECL GetTargetDopplerRF(PLT_ENTITY* own, PLT_ENTITY* tgt, DWORD rfc);

// ��ȡĿ��RCSֵ
DOUBLE SCNPARSERLIB_DECL GetTargetRCS(PLT_ENTITY* own, PLT_ENTITY* tgt, DWORD rfBand);

// ��ȡĿ��ز�˥��
DOUBLE SCNPARSERLIB_DECL GetTargetEchoAtten(PLT_ENTITY* own, PLT_ENTITY* tgt);

////////////////////////////////////////////////////////////
// ��ȡ�״����淽λ����ֵ
//
// own: xml��ȡ�����״�λ��
// tgt: xml��ȡĿ��λ��
// atn: xml��ȡ�״��豸����
// radpos: վַ���Ĳ�ѯ radarλ��
// bjcpos: վַ���Ĳ�ѯ bjcλ��
DOUBLE SCNPARSERLIB_DECL GetRadarAtnAzim(PLT_ENTITY* own, PLT_ENTITY* tgt, VEC_DIR* atn, VEC_POS* radPos, VEC_POS* bjcPos);


// ��ʼ��Ŀ������ת������
DWORD  SCNPARSERLIB_DECL InitTargetConvert(PLT_ENTITY* own, PLT_ENTITY* tgt, VEC_POS* radPos, VEC_POS* bjcPos);

// Ŀ������ת��(����ռ�->����ռ�)
DWORD  SCNPARSERLIB_DECL DoTargetConvert(VEC_POS* realPos, VEC_POS* scenPos);

#endif