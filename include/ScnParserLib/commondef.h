/***********************************************************************
  commondef.h:  interface for the composite data structure definition.
************************************************************************/
#ifndef _COMMONDEF_H_
#define _COMMONDEF_H_

#include "typedef.h"

///////////////////////////////////////////////////////////
// Macro Definition
///////////////////////////////////////////////////////////

//���������
#define DEBUG_PACK_CODE    		0x1234

#define MAX_ANTENNA_NUM			8
#define MAX_RFBAND_NUM			8

///////////////////////////////////////////////////////////
// Structure Definition
///////////////////////////////////////////////////////////

//��ƵƵ�λ���
typedef enum
{
	RADIO_BAND_P				= 0,			//P���� : 230~1000MHz
	RADIO_BAND_L				= 1,			//L���� : 1GHz~2GHz
	RADIO_BAND_S				= 2,			//S���� : 2GHz~4GHz
	RADIO_BAND_C				= 3,			//C���� : 4GHz~8GHz
	RADIO_BAND_X				= 4,			//X���� : 8GHz~12GHz
	RADIO_BAND_KU				= 5,			//Ku����: 12GHz~18GHz
	RADIO_BAND_K				= 6,			//K���� : 18GHz~26.5GHz
	RADIO_BAND_KA				= 7,			//Ka����: 26.5GHz~40GHz
	RADIO_BAND_NUM				= 8,			//��������
};

//ƽ̨RCS������
typedef struct _PLT_RCS_
{
	FLOAT			rcs_head[RADIO_BAND_NUM];	//ǰ��RCS(����P/L/S/C/X/Ku/K/Ka���λ���)
	FLOAT			rcs_side[RADIO_BAND_NUM];	//����RCS
	FLOAT			rcs_rear[RADIO_BAND_NUM];	//����RCS
}PLT_RCS;

//�ռ�����ʸ��
typedef struct _VEC_POS_
{
	//��γ������ϵ
	DOUBLE			lon;						//���ȣ���λ: ��
	DOUBLE			lat;						//γ�ȣ���λ: ��
	DOUBLE			alt;						//�߶ȣ���λ: m

	//����������ϵ
	DOUBLE			east;						//�������
	DOUBLE			north;						//�������
	DOUBLE			sky;						//�������

	//��λ-����-��������ϵ
	DOUBLE			azim;						//��λ
	DOUBLE			pitch;						//����
	DOUBLE			range;						//����
	
}VEC_POS;

//�ռ���̬ʸ��(������)
typedef struct _VEC_DIR_
{
	DOUBLE			jaw;						//ƫ������λ: ��(������Ϊ���˳ʱ����ת)
	DOUBLE			pitch;						//��������λ: ��(����Ϊ�����¸�Ϊ��)
	DOUBLE			roll;						//�������λ: ��(��ˮƽ����Ϊ��ȣ�������)
	
}VEC_DIR;

//ƽ̨ʵ��
typedef struct _PLT_ENTITY_
{
	//ƽ̨����
	DWORD			nID;  				//ƽ̨ID
	DWORD			platType;			//ƽ̨����: 0-δ֪��1-����̶���2-���أ�3-��Я��4-��(��)�أ�5-����
										//       6-ֱ�����أ�7-���˻��أ�8-���أ�9-����
	DWORD			enemyAttr;			//��������: 0-δ֪��1-�з���2-�ҷ���3-����
	CHAR			strPrompt[256];		//ƽ̨����

	//ƽ̨λ��
	DOUBLE			longitude;			//���ȣ���λ: ��
	DOUBLE			latitude;			//γ�ȣ���λ: ��
	DOUBLE			altitude;			//�߶ȣ���λ: m

	//ƽ̨��̬
	DOUBLE			course;				//���򣬵�λ: ��(������Ϊ���˳ʱ����ת)
	DOUBLE			pitch;				//��������λ: ��(����Ϊ�����¸�Ϊ��)
	DOUBLE			across;				//�������λ: ��(��ˮƽ����Ϊ��ȣ�������)

	//ƽ̨�ٶ�
	DOUBLE			v_east;				//�����ٶȣ���λ: m/s
	DOUBLE			v_north;			//�����ٶȣ���λ: m/s
	DOUBLE			v_sky;				//�����ٶȣ���λ: m/s

	//ƽ̨RCS
	PLT_RCS			rcsTable;			//ƽ̨RCS������
}PLT_ENTITY;

#pragma pack(push, 4)

//�û��ļ�
typedef struct _USR_FILE_
{
	DWORD			usrFileID;			//�ļ�ID
	CHAR			usrFilePath[256];	//�ļ�·������
	DWORD			usrFileMD5;			//�ļ�У����
	
}USR_FILE;

//���ΰ�װ����
typedef struct _ATN_INST_
{
	DOUBLE			pos_x;				//���߰�װλ��X���ң���ƽ̨��������ϵ��������㣩
	DOUBLE			pos_y;				//���߰�װλ��Y��ǰ����ƽ̨��������ϵ��������㣩
	DOUBLE			pos_z;				//���߰�װλ��Z���ϣ���ƽ̨��������ϵ��������㣩

	DOUBLE			alpha;				//���߰�װ��λ�ǣ�ƽ̨��������ϵ
	DOUBLE			theta;				//���߰�װ�����ǣ�ƽ̨��������ϵ
	DOUBLE			gamma;				//���߰�װ��ת�ǣ�ƽ̨��������ϵ
	
}ATN_INST;

//����Ƶ�β���
typedef struct _RF_BAND_
{
	DOUBLE			rfStart;			//��ʼƵ�ʣ���λ: MHz
	DOUBLE			rfStop;				//����Ƶ�ʣ���λ: MHz
	
}RF_BAND;

//���߰�װ����
typedef struct _ATN_ARR_PARAM_
{
	DWORD			atnArrayID;			//������ID
	DWORD			atnArrayNum;		//���ߵ�Ԫ����
	ATN_INST		antenna[MAX_ANTENNA_NUM];
		
}ATN_ARR_PARAM;

//�շ�ͨ������
typedef struct _TR_CHAN_PARAM_
{
	DWORD			chanID;				//ͨ��ID
	DOUBLE			emtPwr;				//�������ֵ����
	DOUBLE			rcvNF;				//���ջ�����ϵ��

	DWORD			enAPM;				//����Ӧ���ʹܿ�ʹ�ܱ�־
	DOUBLE			rangeAMP;			//����Ӧ���ʵ�����Χ

	DWORD			nBand;				//����Ƶ������
	RF_BAND			rfBand[MAX_RFBAND_NUM];
	
}TR_CHAN_PARAM;

//�״﹤��ģʽ
typedef struct _RDS_WORK_MODE_
{
	DWORD			modeID;				//����ģʽID
	DWORD			modeType;			//����ģʽ����: 0-δ֪��1-������2-���٣�3-�Ƶ���4-TWS��5-TAS��6�Ժ�Ԥ��

}RDS_WORK_MODE;

//�״����ģ��
typedef struct _RDS_OBJ_
{
	DWORD			radarID;			//�״����ID
	CHAR			radarName[64];		//�״��������
	CHAR			radarDesc[256];		//�״��������

	DWORD			type;				//�������
	DWORD			platform;			//����ƽ̨
	DWORD			prio;				//�������ȼ�
	
	DWORD			initWorkModeID;		//��ʼ����ģʽID
	DWORD			startRunTime;		//����ʱ��
	USR_FILE 		devConfigFile;		//�豸�����ļ�
	DOUBLE			powerRange;			//�״�������Χ

	ATN_ARR_PARAM	atnArrayParam;		//���߰�װ����
	TR_CHAN_PARAM	trChanParam;		//�շ�ͨ������

	DWORD			nWorkMode;			//����ģʽ����
	RDS_WORK_MODE*	pWorkMode;			//�״﹤��ģʽ����
		
}RDS_OBJ;

#pragma pack(pop)

#endif