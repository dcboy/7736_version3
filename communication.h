#ifndef __COMMUNICATION_H__
#define __COMMUNICATION_H__

//#define PRINT_DEBUG

unsigned int ZhkSerial1Printf( unsigned char *format , ... );

//
//-----------------------------------ע��----------------------------
//
//Ŀǰ���Ŵ��������unsigned char������unicode
//
//Ŀǰ���Ͱ����ܴ���4096��������ͷ��CRC�ĳ��ȣ�
//
//����ȴ��ش����ʱ��ǿ�ҽ���ر���·��������ܷ���Ӧ��׼�����͵ڶ�������ʱ���յ���һ�����Ļش�
//Ӧ�ú�ͨѶģ��ͬʱʹ��ȫ�ֻ��������������ޣ�Ӧ�õķ��ͺͽ��ջ�����Ϊͬһ���������»���
//
//����VMID��ͨѶģ�����ģ�����Ҫ��֤ϵͳ����ȫ�ֱ����е�VMID��ȷ��������INIT��ʱ����ʵΪ9999+��װ�룩
//-------------------------------------------------------------------
//

//����
//2005-03-07
//	���ӻ�������СCOMM_PACKET_BUFFER_SIZE�ĺ궨��
//
//2005-03-05
//	����SendSMS����������SMS���͡���Ϊ���ڷ��Ͷ���Ϊ�Ƕ�ռʽ�������ڷ��͵�ʱ���޷��ٷ�����һ��������ͨѶģ������˻��崦��
//	ResponsePacketArrived��������һ�����������ڷ����յ��Ļش�������峤��

//2005-03-01
//	���ĵ�����Ϣ����궨��

//2005-02-28
//	���ӹ������������˵����
//		ע�⣬�Ƿ��й�������ĺ����������й�������󣬸�������������Ϣ�ͱ�־Ϊ��֪ͨӦ�ã����ٱ�����
//	DLCardParamCommandExist��������һ������
//////////////////////////////////////////////////////


//#define PRINT_DEBUG
#define __INT_LINE__ ((unsigned int)__LINE__)
#include <stdio.h>
#include "global.h"


//
//ͨѶ��̨����ִ�к���
//�ú������᳤ʱ��ռ��CPU��Ӧ��Ӧ�л�����������
//
void DoCommunication();
//������Ż������ڵ����ж���Ϣ
//void ClearAllSMSInSMSBuffer();

unsigned char TestSMSSend( struct SHORTMSG* Msg );
///ȡ���ŷ��ͽ��
//0��OK,1��fail,2-continue
unsigned char  GetTestSMSSendResult();

///ȡATָ�������
unsigned int  GetATCMDResult();

#ifdef _MOBILE_SMS_1
	//��SMS���뷢�ͻ���
	void SendSMS( unsigned char* pSMS, unsigned char byLen );
	//����״̬������Ϊ�豸ģ�鱨�����������Ƿ����֣�
	void SendStatusWarnning();
	//��ȡͨѶ�Ͷ��Ż���״̬,�Ƿ���Է��Ͷ���
	//1 - OK	0 - Not OK
	bit SMSCommStatus();	
#endif

#endif //__COMMUNICATION_H__