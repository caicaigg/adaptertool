/***********************************************************************
  typedef.h: interface for the data type definition.
************************************************************************/
#ifndef _TYPEDEF_H_
#define _TYPEDEF_H_

#ifdef  OK
#undef  OK
#endif
#define	OK					0

#ifdef  ERROR
#undef  ERROR
#endif
#define ERROR				-1

#ifndef NULL
#define NULL        		((void*)0)
#endif

#ifndef FALSE
#define FALSE       		0
#endif

#ifndef TRUE
#define TRUE        		1
#endif

#define global
#define CONST       		const
#define STATIC      		static
#define EXTERN      		extern

#define _win32				1
#define _win64				2
#define _linux				3
#define _vxworks			4
#define _reworks			5
#define OS_ARCH			   _win32

#if(OS_ARCH == _vxworks)
#include <vxWorks.h>

typedef char				CHAR;
typedef short				SHORT;
typedef int  				INT;
typedef long				LONG;
typedef float				FLOAT;
typedef double  			DOUBLE;
typedef signed char   		SCHAR;
typedef unsigned char		BYTE;
typedef long long 			LDWORD;

#ifdef __edit
typedef	bool				BOOL;
#endif

#if(CPU != SIMNT)
typedef unsigned short		WORD;
typedef unsigned int		DWORD;
#endif

typedef DWORD				LOCK;

typedef BYTE*				PBYTE;
typedef WORD*				PWORD;
typedef DWORD*				PDWORD;
#endif

#if(OS_ARCH == _win32)
#ifdef __cplusplus
//#include <afxmt.h>
#include "stdafx.h"
#endif

#ifndef __cplusplus
typedef char				BOOL;
typedef char				CHAR;
typedef short				SHORT;
typedef int  				INT;
typedef long				LONG;
typedef float				FLOAT;
typedef double  			DOUBLE;
typedef signed char   		SCHAR;
typedef unsigned char		BYTE;
typedef unsigned short		WORD;
typedef unsigned long		DWORD;
#endif

#ifdef __cplusplus
typedef WORD				STATUS;
typedef DWORD 		  	   	(*FUNCPTR)(LPVOID pParam);
typedef UINT64				LDWORD;

// typedef CMutex				SEM;
// typedef	SEM*				SEM_ID;
// typedef CRITICAL_SECTION	LOCK;
#endif

#endif
#endif
