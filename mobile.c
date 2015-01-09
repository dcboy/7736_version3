// �ֻ�ģ����������
// ����������m20�ֻ�ģ��
#define MOBILE_C
#define GPRS_C
#define SMS_C

#include "device.h"
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include "serial.h"
#include "mobile.h"
#include "timer.h"
#include "debug.h"
#include "global.h"

#define ZHKMOBILE_CONNECTTIMEOUT  	180
#define ZHKMOBILE_CMD_ACKTIMEOUT  	50
#define ZHKMOBILE_SMS_ACKTIMEOUT  	70
//�洢�յ��Ķ��ŵ������
#define SmsRxMaxNum	3

uchar ZhkAtCmd( uchar* AtCmd, uchar CmdFlag );
uchar ZhkAtCmdGetErr( void );
uchar xdata ZhkAtCmdBuffer[ 1024 ];
uint  xdata ZhkAtCmdBufWr;
uchar MobileInitProcess( void );
uchar ZhkMobileNullProcess( void );
void ZhkMobileSignalIn( void );	

//ATָ������ִ�еĽ��
#define ATCMD_ERR_NULL 		0
#define ATCMD_ERR_BLOCK  	1
#define ATCMD_ERR_TIMEOUT 	2
#define ATCMD_ERR_ERR 		3
uchar xdata ZhkAtCmdErr = ATCMD_ERR_NULL;

///��������в���������
#define ZHKTASKCLAIM_DIAL  	0x01		// �������� 
#define ZHKTASKCLAIM_HANG  	0x02		// �Ҷ����� 
#define ZHKTASKCLAIM_CONNECT  	0x04	// �������� 
#define ZHKTASKCLAIM_SHUT  	0x08		// �������� 
#define ZHKTASKCLAIM_TXSMSG  	0x10 	// ���Ͷ������� 
#define ZHKTASKCLAIM_RXTMSG  	0x40 	// ������Ϣ���� 
#define ZHKTASKCLAIM_QUERY  	0x80 	// ��ѯ״̬����,�ڶ���ģʽ�����ڲ�ѯ�ֻ�ģ��Ĺ���״̬
uchar xdata ZhkTaskClaim;			// �ֻ�ͨ����������

// ����״̬
////�ֻ�ģ�鵱ǰִ�е�����
#define MOBILE_NULL  		0x00  	// ����״̬
#define MOBILE_DIALUP 		0x01	// ������
#define MOBILE_HANGUP 		0x02	// �Ҷ���
#define MOBILE_TCP_CONNECT 	0x03	// ������
#define MOBILE_TXSHORTMSG	0x05	// ���Ͷ�����
#define MOBILE_RXSHORTMSG  	0x06 	// ���ն�����
#define MOBILE_TCP_SHUT 	0x04	// ������
#define MOBILE_TXTCPMSG  	0x07 	// ���ڷ���TCP��Ϣ
#define MOBILE_RXTCPMSG     0x08	// ���ڽ���TCP��Ϣ
#define MOBILE_INIT      	0x09	// ���ڳ�ʼ��
#define MOBILE_QUERY      	0x0A	//��ѯ
uchar xdata ZhkMobileCurrentTask = MOBILE_NULL;		// �ֻ�ģ��״̬

// �ֻ�ģ��ִ��ĳ������ʱ�Ľ��ȶ���	
#define MOBILE_BEGIN 	0x00
#define MOBILE_STEP1 	0x01
#define MOBILE_STEP2 	0x02
#define MOBILE_STEP3 	0x03
#define MOBILE_STEP4 	0x04
#define MOBILE_STEP5 	0x05
#define MOBILE_STEP6 	0x06
#define MOBILE_STEP7 	0x07
#define MOBILE_STEP8 	0x08
#define MOBILE_STEP9 	0x09
#define MOBILE_STEP10 	0x0a
#define MOBILE_FINISH	0x10
#define MOBILE_TIMEOUT 	0x11
#define MOBILE_ERROR 	0x12	

///�ֻ�ģ��������ͨѶ��·״̬
#define GPRS_STATUS_BREAK  		1	//��SMSģ�±�ʾ���ذ����ֻ�ģ��ͨѶ�Ͽ�
#define GPRS_STATUS_DIALUP  		2
#define GPRS_STATUS_CONNECTED  		3	//��SMSģ�±�ʾ���ذ����ֻ�ģ��ͨѶ����
#define GPRS_STATUS_CONNECTING  	4	//��SMSģ�±�ʾ���ذ����ֻ�ģ����������
#define GPRS_STATUS_HANGUP  		5
uchar xdata ZhkGprsStatus     	= GPRS_STATUS_BREAK;

uchar xdata	ZhkGprsLastErr       	= GPRS_ERR_BLOCK;
//�ֻ�ģ����������
#define GPRSMDeadJValue  3        //��Ӧ�����
#define GPRSMResetValue  90      //����ʱ�� 
bit data GPRSModuleDeadFlag = 0;	//�Ƿ�������־
bit data LoadPowerDeleAllSMS = 0;	//ϵͳ�ϵ��Ϻ��Ƿ�ɾ����������ǰ�Ķ���
uchar xdata GPRSDeadTimer = 0;	  	//�޻�Ӧ����


#ifdef _MOBILE_SMS_1	
	
	#define SMS_MOBILE_STATUS_OK 1
	#define SMS_MOBILE_STATUS_BROKEN 2

	uchar xdata	SMSLastErr       	= SMS_ERR_BLOCK;	
//	uchar xdata SMSMobileStatus = SMS_MOBILE_STATUS_BROKEN;
	// ���Ž��ջ�����
	struct SHORTMSG xdata ZhkSmsRxBuf[SmsRxMaxNum];
	uchar xdata ZhkSmsRxNum = 0;
	char xdata NewCommingSmsSit[16];
	// ���ŷ��ͻ�����
	struct SHORTMSG xdata ZhkSmsTxBuf;
	uchar xdata ZhkSmsTxNum = 0;
	

	uchar ZhkMobileSmsRxProcess( void );
	uchar ZhkMobileSmsTxProcess( void );
	uchar ZhkMobileSmsGetTxMsg( struct SHORTMSG* Msg );
	uint ZhkMobileSmsUnpack( struct SHORTMSG xdata* Msg, uchar xdata* DataBuf , uint DataLen );
	uint ZhkMobileSmsPack( struct SHORTMSG xdata* Msg, uchar xdata* DataBuf );
	uint ZhkGSMToAsc( uchar xdata* GSMCode , uchar xdata* AscCode , uint len );
//	uchar ZhkAscToGSM( uchar xdata* GSMCode , uchar xdata* AscCode , uchar len );	
#endif

//��������
/////������ʱ������������е�����
uchar ZhkMobileNullProcess( void )
{
	
	return 0;
}

//��������
////��ʼ���ֻ�ģ��
uchar MobileInitProcess( void )
{
    return 0;
}

//��������
///ѭ������ֻ�ģ��
uchar ZhkMobileProcess( void )
{	
	
	return 0;
}

uchar GprsInit( void )
{

	return 0;
}
//��������
///���ڵ��źŽ��У�Ȼ���ж���ʲô�ź�
void ZhkMobileSignalIn( void )
{
	#define SMSHEAD  "+CMTI:"			
	#define GPRSHEAD "+IPD"
	#define GPRSCLOSE "CLOSED"
	
}

//����ģ������ʼ��
uchar ZhkMobileInit( void )
{	
	
	return 0;
}

uchar SendATcommandToMobile()
{
    return 0;
}

#ifdef _MOBILE_SMS_1
	
	bit IsShortMsgIn( void )
	{
	//	Trace("\n IsShortMsgIn");
		return ! ( ZhkSmsRxNum == 0 );
	}
	bit IsMessagerBuzy( void )
	{
		return ZhkSmsTxNum;
	}
	
	bit	SMSMobileStatus()
	{
		if( SMSMobileStatus == SMS_MOBILE_STATUS_OK )
			return 1;
		else
			return 0;
	}

	uchar GetShortMsg( struct SHORTMSG* Msg )
	{
		if( Msg == 0);	
		return 0;	
	}
	
	uchar PutShortMsg( struct SHORTMSG* Msg )
	{
	    if( Msg == 0);
		ZhkTaskClaim |= ZHKTASKCLAIM_TXSMSG;
		return ZhkSmsTxBuf.len;
	}

	uchar SMSGetLastErr( void )
	{
		return SMSLastErr;
	}	
	
	uchar ZhkMobileSmsTxProcess( void )
	{
		// AT+CMGS=<length><cr><lf>
		// waitfor '>'
		// SendMsg
		// <^Z><cr><lf>
		// waitfor OK
		return 0;
	    //return MsgTxStatus;
	}

	uchar ASCToInt( uchar val )
	{
		if ((val >= '0') && (val <= '9'))
        	return  val - '0';
        return 0;
	}

	uchar ZhkMobileSmsRxProcess( void )
	{
		// AT+CMGR=n
		// getline index "+cgml" and ���n
		// getline unpack
		// waitfor ok
		// AT+CMGD=n
		// waitfor ok
		return 	0;
	}

	// ����ֵ����0��ʾ�����ɹ��ӷ��ͻ�����ȡ������
	// ����ֵ�����ʾ����ʧ��
	uchar ZhkMobileSmsGetTxMsg( struct SHORTMSG* Msg )
	{
		if ( ZhkSmsTxNum == 0) 
			return 1;
		memcpy( Msg , &ZhkSmsTxBuf, sizeof( struct SHORTMSG ) );
	//	ZhkSmsTxNum --;
		return 0;
	}
	
	//////////////////////////
	/////��������Ķ�����7λ���룬��Ҫ�ô˺���ת��Ϊ8λ����
	// GSM�ַ���(ÿ���ַ�7λ)ת��ΪAsc�ַ���(ÿ���ַ�8λ)
	// GSMCode��GSM�ַ���(ÿ���ַ�7λ)��
	// AscCode��Asc�ַ���(ÿ���ַ�8λ)
	// len: �ַ������ȣ����ַ�����Ϊ
	uint ZhkGSMToAsc( uchar xdata* GSMCode , uchar xdata* AscCode , uint len )
	{
	   GSMCode = 0;
	   AscCode = 0;
       len = 0;
	   return 0;
	}
		
	// GSMCode��GSM�ַ���(ÿ���ַ�8λ)��
	// MessageCode����Ϣ�ַ���(ÿ���ַ�8λ)
	// len: �ַ������ȣ����ַ�����
	// ����ת������ĳ���
	//�˺����ǰѶ������ݱ�Ϊ7λ��ĺ���
	uint ZhkMessageToGSM( uchar xdata* GSMCode , uchar xdata* MessageCode , uint len )
	{
	    GSMCode = 0;
        MessageCode = 0;
        len = 0;
		return 0;
	}

	// �ֻ����ű���
	// ���ر����ȥ���������ĺ���ʣ�²��ֵ��ַ�����
	uint ZhkMobileSmsPack( struct SHORTMSG xdata* Msg, uchar xdata* DataBuf )
	{
	    Msg = 0;
		DataBuf = 0;
	    return 0;
	}

	// ����ֵ
	// ���ŵ���Ϣ����
	uint ZhkMobileSmsUnpack( struct SHORTMSG xdata* Msg, uchar xdata* DataBuf, uint DataLen ) 
	{
	    Msg = 0;
		DataBuf = 0;
		DataLen = 0;
		return 0;
	}	
#endif

#ifdef _MOBILE_GPRS		
	uchar ZhkMobileGprsConnectProcess( void )
	{
		// AT+CIPSTART="TCP","IP","PORT"
		// waitfor ok
		// waitfor connect ok
		static uchar xdata ConnectStatus = MOBILE_BEGIN;
		uchar xdata CmdStr[ 128 ];
		uchar  data len;
		uchar  data temp;
		switch( ConnectStatus )
		{
		case MOBILE_BEGIN:	
			len = sprintf( CmdStr , "AT+CIPSTART=\"TCP\",\"%d.%d.%d.%d\",\"%ld\"\0" ,  
				( int )ZhkGprsIP[ 0 ] , ( int )ZhkGprsIP[ 1 ] , 
				( int )ZhkGprsIP[ 2 ] , ( int )ZhkGprsIP[ 3 ] , (long)ZhkGprsPort );
			ZhkAtCmd( CmdStr, 0 );
			ConnectStatus     = MOBILE_STEP1;
			break;
		case MOBILE_STEP1:			// waitfor OK
			temp = ZhkAtCmdGetErr();
			switch( temp )
			{
			case ATCMD_ERR_NULL:
				// �ֻ�ģ����ȷ����ָ�
				ZhkMobileSecTimer = ZHKMOBILE_CONNECTTIMEOUT;
				ConnectStatus     = MOBILE_STEP2;
				break;
			case ATCMD_ERR_BLOCK:
				// ����״ֱ̬�ӷ���
				break;						
			case ATCMD_ERR_TIMEOUT:
				// �ֻ�ģ�����ָ�ʱ��
				ConnectStatus     = MOBILE_BEGIN;
				ZhkGprsStatus     = GPRS_STATUS_CONNECTING;
				ZhkGprsLastErr    = GPRS_ERR_CONNECTING;
				return MOBILE_TIMEOUT;
			case ATCMD_ERR_ERR:
				// �ֻ�ģ�����ָ�����
				ConnectStatus     = MOBILE_BEGIN;
				ZhkGprsStatus     = GPRS_STATUS_CONNECTING;
				ZhkGprsLastErr    = GPRS_ERR_CONNECTING;
				return MOBILE_ERROR;
			}
			break;	
		case MOBILE_STEP2:  			// wait for connectok
			// ����״ֱ̬�ӷ���
			if ( ZhkAtCmdBufWr == 0 )
			{
				if ( ZhkMobileSecTimer == 0 )
				{
					ConnectStatus     = MOBILE_BEGIN;
					ZhkGprsStatus     = GPRS_STATUS_CONNECTING;
					ZhkGprsLastErr    = GPRS_ERR_CONNECTING;
					return MOBILE_TIMEOUT;
				}
				 break;	
			}
			ZhkAtCmdBufWr = 0;
			// ���ӳɹ�
			if ( strcmp( ZhkAtCmdBuffer , "CONNECT OK" ) == 0 )
			{
				ConnectStatus     = MOBILE_BEGIN;
				ZhkGprsStatus     = GPRS_STATUS_CONNECTED;
				ZhkGprsLastErr    = GPRS_ERR_NULL;
				return MOBILE_FINISH;
			}
			if ( strcmp( ZhkAtCmdBuffer , "CONNECT FAIL" ) == 0 )
			{
				ConnectStatus     = MOBILE_BEGIN;
				ZhkGprsStatus     = GPRS_STATUS_CONNECTING;
				ZhkGprsLastErr    = GPRS_ERR_CONNECTING;
				return MOBILE_ERROR;
			}
			break;
		default:
			ConnectStatus = MOBILE_BEGIN;
			return MOBILE_ERROR;
		}
		return ConnectStatus;
	}
	
	uchar ZhkMobileGprsShutProcess( void )
	{
		// AT+CIPSHUT
		// waitfor shut ok or error
		static uchar xdata ShutStatus = MOBILE_BEGIN;
		uchar  data temp;
		
		switch( ShutStatus )
		{
		case MOBILE_BEGIN:	
			ZhkAtCmd( "AT+CIPSHUT", 0 );
			ShutStatus        = MOBILE_STEP1;
			break;
		case MOBILE_STEP1:			// waitfor OK
			temp = ZhkAtCmdGetErr();
			ZhkGprsMsgRxBufWr = 0;
			switch( temp )
			{
			case ATCMD_ERR_NULL:
				// �����ɹ��ı�־
				ShutStatus        = MOBILE_BEGIN;
				ZhkGprsStatus     = GPRS_STATUS_DIALUP;
				ZhkGprsLastErr    = GPRS_ERR_NULL;
				return MOBILE_FINISH;
			case ATCMD_ERR_BLOCK:
				// ����״ֱ̬�ӷ���
				break;						
			case ATCMD_ERR_TIMEOUT:
				// �Ҷϳ�ʱ����
				// ��ʱ����
				ShutStatus        = MOBILE_BEGIN;
				ZhkGprsLastErr    = GPRS_ERR_TIMEOUT;
				return MOBILE_TIMEOUT;
			case ATCMD_ERR_ERR:
				// �����ɹ��ı�־
				ShutStatus        = MOBILE_BEGIN;
				ZhkGprsStatus     = GPRS_STATUS_DIALUP;
				ZhkGprsLastErr    = GPRS_ERR_NULL;
				return MOBILE_FINISH;
			}
			break;
		default:
			ShutStatus        = MOBILE_BEGIN;
			return MOBILE_ERROR;
		}
		return ShutStatus;
	}

	uchar ZhkMobileGprsTxProcess( void )
	{
	
		return 0;
	}
	
	uchar ZhkMobileGprsRxProcess( void )
	{
		return 0;
	}

#endif

uchar ZhkAtCmd( uchar* AtCmd, uchar CmdFlag )
{
	if( *AtCmd == CmdFlag )  CmdFlag = 0;
	return 0;
}
uchar ZhkAtCmdGetErr( void )
{

	return ATCMD_ERR_BLOCK;
}

