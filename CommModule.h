#ifndef __COMM_MODULE_H__
#define __COMM_MODULE_H__

//
//Ŀǰֻ��Ӧ�ò��лش������ͨѶģ�鷢�͵��������״̬���ͣ��Ļش������������⴦��������ͨ��WaitAnswer���ƣ�
//

#include <string.h>

#include "global.h"
#include "mobile.h"
#include "crc.h"
#include "clock.h"
#include "timer.h"
#include "gprs.h"

#include "communication.h"

/////����ִ�в��趨��

#define STA_COMM_MODULE_INIT 0
//���ͨѶ״̬�Լ�ȫ��ͨѶ�����;ֲ�ͨѶ����(�緢���仯������ȫ��ͨѶ�������ֲ�)
#define STA_CHECK_COMM_STATUS 1

///��ѯ���ŷ��ͽ��
#define STA_CHECK_SMS_SEND_RESULT 17

///���Ͷ��ſղ���,����ղ���ʹ����ת���ж��ǲ��ж�����Ҫ����
#define STA_SMS_NULL 18

extern unsigned char data g_byCommRunningStatus;

//��Χ�����õ���ͨѶ��·������״̬
#define COMM_STATUS_HANGUP 0
#define COMM_STATUS_DIALING 1
#define COMM_STATUS_BROKEN 2		//dial ok, but tcp broken
#define COMM_STATUS_CONNECTING 3
#define COMM_STATUS_OK 4
#define COMM_STATUS_BROKEING 5
#define COMM_STATUS_HANGING 6
#define COMM_STATUS_INITING 7		//���ڳ�ʼ��
#define COMM_STATUS_SMS_SENDING 8		//���ڷ��Ͷ���


////ͨ�ú���
//Init	
unsigned char staCommModuleInit();	
//���ͨѶ״̬�Լ�ȫ��ͨѶ�����;ֲ�ͨѶ����(�緢���仯������ȫ��ͨѶ�������ֲ�)	
unsigned char staCheckCommStatus();


#define VMID_LEN 5

#ifdef _MOBILE_SMS_1		//�ö��Ž��д���

	#define MAX_BUFFERED_SMS_COUNT 10
	struct SMSBuffer
	{
		unsigned char m_bySMSs[ MAX_BUFFERED_SMS_COUNT ][ MAX_SMS_LEN ];
		unsigned char m_byLens[ MAX_BUFFERED_SMS_COUNT ];		
		unsigned char m_byBeginIndex;
		unsigned char m_byCount;
	};
	struct SMSModuleInfo
	{		
		struct SMSBuffer m_SMSBuffer;
		unsigned char m_byAlarm;
		unsigned char m_byCommStatus;
	};
	extern struct SMSModuleInfo xdata g_SMSCommModuleInfo;
	//��鷢�ͱ�������
	#define STA_CHECK_ALARM 6
	unsigned char staCheckAlarm();
	//��SMS��������ȡSMS������������
	void commDoSendSMS();
	//��SMS���뷢�ͻ���
	//pSMS�����Ѿ��Ǿ����и����֤���Ȳ�����MAX_SMS_LEN��ʹ��PDUģʽ�µ�8λ���뷽ʽ�������140���ַ���
	void commAdd2SMSSendBuffer( unsigned char* pSMS, unsigned char byLen );
	//�����ŷ��ͽ��
	unsigned char staCheckSMSSendResult();
#endif
#endif //__COMM_MODULE_H__