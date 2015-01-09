#include "communication.h"
#include "commmodule.h"

#ifdef _MOBILE_SMS_1
	//����״̬������Ϊ�豸ģ�鱨�����������Ƿ����֣�
	void SendStatusWarnning()
	{
		g_SMSCommModuleInfo.m_byAlarm = 1;
	}
	
	void ClearAllSMSInSMSBuffer()
	{
		memset( &g_SMSCommModuleInfo.m_SMSBuffer, 0, sizeof(g_SMSCommModuleInfo.m_SMSBuffer) );
	}
	//��ȡͨѶ״̬,�Ƿ���Է��Ͷ���
	//1 - OK	0 - Not OK
	bit SMSCommStatus()
	{	
		///�����Ķ�����װ���������������ټ�����
		if( g_SMSCommModuleInfo.m_SMSBuffer.m_byCount >= MAX_BUFFERED_SMS_COUNT )
			return 0;	
		if( g_SMSCommModuleInfo.m_byCommStatus != COMM_STATUS_OK )
			return 0;
		return 1;	
	}
	//��SMS���뷢�ͻ���
	void SendSMS( unsigned char* pSMS, unsigned char byLen )
	{
		while( byLen > MAX_SMS_LEN )
		{
			commAdd2SMSSendBuffer( pSMS, MAX_SMS_LEN );
			pSMS += MAX_SMS_LEN;
			byLen -= MAX_SMS_LEN;
		}
		if( byLen )
		{
			commAdd2SMSSendBuffer( pSMS, byLen );
		}
	}
#endif
