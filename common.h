#ifndef _COMMON_
#define _COMMON_
#ifndef COMMON_C
	#define CommonSourse extern
#else
	#define CommonSourse
#endif
	#define BIT0 	0x01
	#define BIT1 	0x02
	#define BIT2 	0x04
	#define BIT3 	0x08
	#define BIT4 	0x10
	#define BIT5 	0x20
	#define BIT6 	0x40
	#define BIT7 	0x80
	
	//CommonSourse void DelayMs( unsigned char );
    CommonSourse void DelayMs( unsigned int );
	// ������ʱ
	CommonSourse void delay( unsigned char );
	// ����ʱ
	CommonSourse void NumberToString( unsigned long dat , uchar * str , unsigned char len  );
	// ����ת��ΪAsc��
	// ����:
	// dat		��ת������
	// str		ת���ַ���
	// len		����
	
	
#endif