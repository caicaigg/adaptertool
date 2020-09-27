/***********************************************************************
  utility.h: general function and macro definition.
************************************************************************/
#include "stdafx.h"

#include <math.h>
#include <stdio.h>
#include <string.h>

#include "commondef.h"


/********************************************************************
 *
 *  �� �� ����BYTE ctoi(CHAR ch)
 *
 *  ��    �ܣ���ʮ�����Ʒ���ת��Ϊ��Ӧ��ʮ��������
 *
 *  ��    ����	ch               --[in]	��ת����ʮ�����Ʒ���
 *
 *  ȫ�ֱ�����  
 *
 *  �� �� ֵ��ʮ��������   
 *
 *******************************************************************/
BYTE ctoi(CHAR ch)
{
	BYTE ret;

	if((ch>='0') && (ch<='9'))
	{
		ret = ch-'0';
	}
	else if((ch>='a') && (ch<='f'))
	{
		ret = ch-'a'+10;
	}
	else if((ch>='A') && (ch<='F'))
	{
		ret = ch-'A'+10;
	}
	else
	{
		ret = 0;
	}

	return ret;
}

///////////////////////////////////////////////////////////
// �������Ƿ�������
///////////////////////////////////////////////////////////
BOOL IsLeapYear(WORD year)
{
	BOOL ret = FALSE;

	if(year%4 == 0)
	{
		if(year%100 != 0)
		{
			ret = TRUE;
		}
		else if(year%400 == 0)
		{
			ret = TRUE;
		}
	}

	return ret;
}

///////////////////////////////////////////////////////////
// ��鲢���������ַ�����ʽ��ȷ��
///////////////////////////////////////////////////////////
DOUBLE CheckLongitude(CHAR* str)
{
	WORD  flag = 1;
	DOUBLE val = fabs(atof(str));

	if(strchr(str, 'W') != NULL)
	{
		flag = 0;
	}

	if(strchr(str, '-') != NULL)
	{
		flag ^= 0x1;
	}

	if(val > 180)
	{
		val = 180;
	}
	
	sprintf(str, "%.2f%s", val, (flag==1)? "E":"W");
	
	val = (flag==1)? val: val*(-1);
	return val;
}

///////////////////////////////////////////////////////////
// ��鲢����γ���ַ�����ʽ��ȷ��
///////////////////////////////////////////////////////////
DOUBLE CheckLatitude(CHAR* str)
{
	WORD  flag = 1;
	DOUBLE val = fabs(atof(str));

	if(strchr(str, 'S') != NULL)
	{
		flag = 0;
	}

	if(strchr(str, '-') != NULL)
	{
		flag ^= 0x1;
	}

	if(val > 90)
	{
		val = 90;
	}

	sprintf(str, "%.2f%s", val, (flag==1)? "N":"S");

	val = (flag==1)? val: val*(-1);
	return val;	
}

///////////////////////////////////////////////////////////
// ��ƵƵ��ת������ƵƵ��(Ƶ�ʵ�λ: kHz)
///////////////////////////////////////////////////////////
DWORD RFVal2RFBand(DWORD rf)
{
	DWORD bandNo = (DWORD)ERROR;

	//P���� : 230~1000MHz
	if((rf>=230e3) && (rf<=1e6))
	{
		bandNo = RADIO_BAND_P;
	}
	//L���� : 1GHz~2GHz
	else if((rf>1e6) && (rf<=2e6))
	{
		bandNo = RADIO_BAND_L;
	}
	//S���� : 2GHz~4GHz
	else if((rf>2e6) && (rf<=4e6))
	{
		bandNo = RADIO_BAND_S;
	}
	//C���� : 4GHz~8GHz
	else if((rf>4e6) && (rf<=8e6))
	{
		bandNo = RADIO_BAND_C;
	}
	//X���� : 8GHz~12GHz
	else if((rf>8e6) && (rf<=12e6))
	{
		bandNo = RADIO_BAND_X;
	}
	//Ku����: 12GHz~18GHz
	else if((rf>12e6) && (rf<=18e6))
	{
		bandNo = RADIO_BAND_KU;
	}
	//K���� : 18GHz~26.5GHz
	else if((rf>18e6) && (rf<=26.5e6))
	{
		bandNo = RADIO_BAND_K;
	}
	//Ka����: 26.5GHz~40GHz
	else if((rf>26.5e6) && (rf<=40e6))
	{
		bandNo = RADIO_BAND_KA;
	}

	return bandNo;
}

