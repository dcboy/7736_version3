#ifndef _TIMER_
#define _TIMER_
#ifndef TIMER_C
	#define TimerSourse extern
#else
	#define TimerSourse
#endif
#include "device.h"

TimerSourse void ZhkTimerInit( void );

//TimerSourse uchar data g_byCommHeartBeatMins;
// ���Ӷ�ʱ������ר��
//TimerSourse uchar data g_byCommTimeOutSeconds;
// �붨ʱ������ר��
TimerSourse uchar xdata LzjSecTimer;

TimerSourse uchar xdata SgwSecTimer;
// �붨ʱ�����ǽ�ר��
TimerSourse uchar xdata SgpSecTimer;
// �붨ʱ�����·�ר��
TimerSourse uchar xdata YgpSecTimer;
// �붨ʱ��Ҷ��ƽר��



TimerSourse uchar xdata LzjMSecTimer;
// ���붨ʱ�����ǽ�ר��
//TimerSourse uchar data MSecTimer2;
// ���붨ʱ��2

//�ٴβ�ѯֽ������ʱ�������뼶
TimerSourse uchar xdata QueryCashTimer;

//�����ż��ʱ��
TimerSourse uchar xdata SendSMSTimer;
//�ն������Լ��ʱ��
TimerSourse uchar xdata ReceiveSMSTimer;

//�ֻ�ģ��ָ���Ӧ��ʱʱ��
TimerSourse uchar xdata ZhkMobileSecTimer;
//���ű����ļ��ʱ��,���Ӽ�ʱ��
TimerSourse uchar  xdata AlarmSpacing;
//�ֻ�ģ�鼤��������ʱ��,���ֻ�ģ������ʱ���ڶ�ʱ�����ֻ�ģ�飬
//���ֻ�ģ����Ҫ��������ʱ���ڼ�¼����ʱ�����뼶
TimerSourse uint xdata GPRSModuleResetTimer; 

//�˿Ͳ�ѯ�ȴ�ʱ��,�뼶
TimerSourse uchar xdata QueryTimer;

////////////////////////////////////////////////////////////////////////////////////////

TimerSourse uchar xdata ZhkSchedulerClock;	
//TimerSourse uchar data ZhkDownMsgAckTimer;
TimerSourse uint xdata ZhkDownMsgAckTimer;
TimerSourse  char xdata ZhkBuzzerTimer;

extern  char xdata lifterTimer;
 

#endif