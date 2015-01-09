#ifndef _IOINPUT_
#define _IOINPUT_
//#include "global.h"

#ifndef IOINPUT_C
	#define IOInputSourse extern
#else
	#define IOInputSourse
#endif

	IOInputSourse struct COINAPCCEPTOR
	{
		unsigned char Enable;
		unsigned int  Line1;
		unsigned int  Line2;
		unsigned int  Line3;
		unsigned int  Line4;
		unsigned int  Line5;
		unsigned int  Line6;
		unsigned char check;
	};
	
	// �Ƿ�ģʽ���ش��ڹر�״̬
	IOInputSourse bit IsModeOff( void );

	// Ӳ����ʹ��
	IOInputSourse bit CoinerEnable( void );

	// Ӳ��������
	IOInputSourse bit CoinerDisable( void );

	// Ӳ�����Ƿ����
	IOInputSourse bit IsCoinerException( void );

    IOInputSourse unsigned char IfCoinHopperFull( void );

	// ��ȡ���յ���Ӳ�ҽ��
	IOInputSourse unsigned int GetCoin( void );

	// �Ƿ��ڵ���״̬
	IOInputSourse bit IsPowerOff( void );

	// ���쾯����
	IOInputSourse bit IfShakeAlarm( void );
	
	// ��һ��
	IOInputSourse void Beep( void );
	
/////////////////////////////////////////////////////////////////////////////////////	

	IOInputSourse void ZhkIOInit( void );

//#ifdef _COIN_INPUT_PARALLEL
//	IOInputSourse void ZyzChkCoinChnSta( void ) using 1
//#endif
    
    IOInputSourse bit IfGameKeyOn( void );
    IOInputSourse bit IfReturnKeyOn( void );

#endif 