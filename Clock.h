#ifndef _CLOCK_
#define _CLOCK_
#ifndef CLOCK_C
	#define ClockSourse extern
#else
	#define ClockSourse 
#endif
/*	struct time 					// ʱ���������Ͷ��壬�����ֶξ�ΪBCD���ʾ
	{
		unsigned char year;			// ��
		unsigned char mon;			// ��
		unsigned char date;			// ��
		unsigned char hour;			// ʱ
		unsigned char min;			// ��
		unsigned char sec;			// ��
	};
*/	
	ClockSourse bit ClockInit( void ) small;
	// ʱ�ӳ�ʼ��
//	ClockSourse bit GetCurrentTime( struct time xdata* CurrentTime ) small;
	// ��ȡ��ǰʱ��
//	ClockSourse bit SetCurrentTime( struct time xdata* CurrentTime ) small;
	// ���õ�ǰʱ��
	
#endif