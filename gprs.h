// gprs ����ӿ�
// ���÷������첽ͨ�ŷ�ʽ
#ifndef _GPRS_
#define _GPRS_

#ifndef GPRS_C
#define GprsSourse extern
#else
#define GprsSourse
#endif

// ����
// ��������
GprsSourse void GprsDailUp( uchar* VPN );

// �Ҷ�
// ��������
GprsSourse void GprsHangUp( void );


// ��������
// ��������
GprsSourse void GprsConnect( uchar* IP , uint Port );

// �ж�����
// ��������
GprsSourse void GprsShut( void );

// ������Ϣ
// ����ֵ
// -1 ��ʾ����
// >=0 ��ʾʵ��д�뻺����������
GprsSourse int GprsSendMsg( uchar* GprsMsg , int len );

// ������Ϣ
// len ��ʾ������յ���Ϣ����
// ����ֵ��ʾ
// >=0 ʵ�ʽ��յ�����Ϣ����
// -1 ����
GprsSourse uchar GprsInit( void );
GprsSourse int GprsRecvMsg( uchar *GprsMsg , int len );

// ����豸״̬
// ����ֵΪ�豸״̬�������ʾ
GprsSourse uchar GprsSelect( void );

// �豸״̬����
#define GPRS_WRITEABLE 		1
#define GPRS_READABLE 		2
#define GPRS_ERROR 		4


// ȡǰһ�β����Ĵ�����Ϣ
// ����ֵ�������ͣ�
GprsSourse uchar GprsGetLastErr( void );

// �������Ͷ���
#define GPRS_ERR_NULL 		0
#define GPRS_ERR_BLOCK 		1
#define GPRS_ERR_HANGUP  	2
#define GPRS_ERR_CONNECTBREAK	3
#define GPRS_ERR_TIMEOUT 	4
#define GPRS_ERR_SENDFAIL 	5
#define GPRS_ERR_CONNECTING  	6

#endif 

