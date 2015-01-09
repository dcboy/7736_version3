#ifndef _DEVICE_
#define _DEVICE_
#ifndef DEVICE_C
	#define BasicSourse extern
#else
	#define BasicSourse
#endif

#include <reg669.h>
#include <ABSACC.h>
#include <intrins.h>
#include "board.h"
#ifdef __REG669_H__

    #define ES      	ES0
    
    #define SM0  	SM0_0
    #define FE  	FE_0
    #define SM1  	SM1_0
    #define SM2  	SM2_0
    #define REN  	REN_0
    #define TB8  	TB8_0
    #define RB8  	RB8_0
    #define TI  	TI_0
    #define RI  	RI_0
#endif
typedef unsigned char uchar;
typedef unsigned int  uint;
typedef unsigned long ulong;


#define OSCRATE 		11059200
#define MACHINECYCLE   		6			// ���������뾧�����ڵı�����ϵ

//#define DOWNMSGACKTIMEOUT   	30

// flash��ַ����

// ϵͳ����,�ӵ�����������ʼ,ռ�ö�������
#define ADDRF_SYSTEMPARAM 	0x80180

// ������������,���64�����,�ܹ�320bytes,ռ����������
//��ʼ��ַ:ADDRF_SYSTEMPARAM+0x00100
#define ADDRF_GOODSWAYS_SET  0x80280
//����һ��ҳ�治��0x80400-80480
//����ͳ�Ʋ������ܼ�22bytes,����һ�������Ŀռ䣬��128byte = 0x80
//��ʼ��ַ:ADDRF_GOODSWAYS_SET + 0x00180
//#define ADDRF_TRADECOUNTER  	0x80400 // +0x80
#define ADDRF_TRADECOUNTER  	0x80500
//������ҳ��
#define ADDRF_TRADECOUNTERCOPY 	0x80600

//��������ͳ�Ʋ���,ÿ�������׼�¼��5byte,
//���64����ƣ�����320byte,�������������Ŀռ䣬��384byte = 0x180
//��ʼ��ַ:ADDRF_TRADECOUNTER + 0x00080
//#define ADDRF_WAYSTARDE_LOG		0x80480 //+180

//������ò���,ÿ�㽻�׼�¼��3byte,
//���8����ƣ�����24byte,������������Ŀռ䣬��256byte = 0x100
//�м�������������
#define ADDRF_RACK_SET		0x80700 //+0x100

//���������������,ÿ�����������ó���2byte,
//���64����ƣ�����128byte,������������Ŀռ䣬��256byte = 0x100
#define ADDRF_RACK_COLUMN_SET	0x80800 //+100

//----------------------------------------------------------------------------------
#define ADDRF_GOODSPAR_SET      0x81000
//==================================================================================

////////////////////////////////////////////////////////////////////////////////////

#ifdef ZHK_INTERRUPT
// Ƭѡ�������ֳ����洦��
#define ZhkLoadChipSelect() _pop_( P1 )
// ֻ���ú꺯�� 
#define ZhkSaveChipSelect() _push_ ( P1 )
// ֻ���ú꺯�� 
#endif


#define ZhkHardNullSelect()     	P1   = 0x04
#define ZhkHardSramSelect()  		P1   = 0x08
#define ZhkHardFlashSelect()  		P1   = 0x09
#define ZhkHardFlash1Select()   	P1   = 0x0A
#define ZhkHardDs12887Select()  	P1   = 0x0B
#define ZhkHardKeyBoardLine1Select()  	P1   = 0x0E
#define ZhkHardKeyBoardLine2Select()  	P1   = 0x0F
#define ZhkHardIOInputSelect()  	P1   = 0x0D
#define ZhkHardIOOutputSelect()  	P1   = 0x14

#define ZhkHardSetRTS() 		PinRTS = 0
#define ZhkHardClrRTS()  		PinRTS = 1
#define ZhkHardIsCTS()     		~ PinCTS

extern void ZhkHardSerialSwitch( unsigned char Route );
extern void ZhkHardBuzzerOn( void );
extern void ZhkHardBuzzerOff( void );
extern void ZhkHardCoinerDisable( void );
extern void ZhkHardCoinerEnable( void );
extern void ZhkHardStatusOn( void );
//extern void ZhkHardStatusOff( void );
extern void ZhkHardPowerOn( void );
extern void ZhkHardPowerOff( void );
extern void WaterKeyEnable( void );
extern void WaterKeyDisable( void );
extern void GameLedOn( void );
extern void GameLedOff( void );
extern void WatchDogInit( void );
extern void WatchDogDisable( void );
extern void FeedWatchDog( void );

#endif