/***********************************************************************
  utility.h: general function and macro definition.
************************************************************************/
#ifndef _UTILITY_H_
#define _UTILITY_H_

#include <stdio.h>
#include "typedef.h"
#include "ScnParserGlobal.h"

#if(OS_ARCH == _vxworks)
#define os_delay				taskDelay
#define showLog					printf
#endif

#if(OS_ARCH == _win32)
#define os_delay				Sleep
#ifdef __cplusplus
#define showLog					TRACE
#else
#define showLog					printf
#endif
#endif

#define MAX(a, b) 				(((a)>(b))? (a):(b))
#define MIN(a, b) 				(((a)<(b))? (a):(b))


SCNPARSERLIB_DECL BYTE	ctoi(CHAR ch);

SCNPARSERLIB_DECL BOOL 	IsLeapYear(WORD year);

SCNPARSERLIB_DECL DOUBLE	CheckLongitude(CHAR* str);

SCNPARSERLIB_DECL DOUBLE	CheckLatitude(CHAR* str);

SCNPARSERLIB_DECL DWORD	RFVal2RFBand(DWORD rf);



#endif
