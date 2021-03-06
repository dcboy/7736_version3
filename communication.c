#include "communication.h"
#include "commmodule.h"

#ifdef _MOBILE_SMS_1
	//发送状态报警（为设备模块报警，不包含非法入侵）
	void SendStatusWarnning()
	{
		g_SMSCommModuleInfo.m_byAlarm = 1;
	}
	
	void ClearAllSMSInSMSBuffer()
	{
		memset( &g_SMSCommModuleInfo.m_SMSBuffer, 0, sizeof(g_SMSCommModuleInfo.m_SMSBuffer) );
	}
	//获取通讯状态,是否可以发送短信
	//1 - OK	0 - Not OK
	bit SMSCommStatus()
	{	
		///待发的短信已装满待发区，不能再加入了
		if( g_SMSCommModuleInfo.m_SMSBuffer.m_byCount >= MAX_BUFFERED_SMS_COUNT )
			return 0;	
		if( g_SMSCommModuleInfo.m_byCommStatus != COMM_STATUS_OK )
			return 0;
		return 1;	
	}
	//将SMS放入发送缓冲
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
