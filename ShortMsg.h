#ifndef _SHORTMSG_
#define _SHORTMSG_
#ifndef SMS_C
	#define ShortMsgSourse extern
#else
	#define ShortMsgSourse
#endif

	#define MAX_SMS_LEN 160
	struct SHORTMSG 
	{
		// �ֻ�����,�շ�ʱ��ΪBCD��ʽ,�ն�Ѷʱ,�˺����а������Ҵ���,
		uchar phone[16];		
		// ���ų���	
		uint len;			
		// �ն��źͷ�����ʱ��ASC���ʾ
		uchar msg[MAX_SMS_LEN];			
	};

	// �ж��Ƿ��ܵ�����
	// ����յ����ŷ��ط�0
	// ���δ�յ����ŷ���0
	//ShortMsgSourse bit IsShortMsgIn( void );	
	
	// ��ȡ�յ��Ķ���
	// Message �洢Ŀ��λ��
	ShortMsgSourse uchar GetShortMsg( struct SHORTMSG* Msg );	
	
	// ���Ͷ��ţ��Ƕ�ռ��ʽ�������ǵȴ�������ŷ��أ�	
	ShortMsgSourse uchar PutShortMsg( struct SHORTMSG* Msg );	
	
	ShortMsgSourse bit IsMessagerBuzy( void );

	ShortMsgSourse uchar SMSGetLastErr( void );

	// �������Ͷ���
	#define SMS_ERR_NULL 		0
	#define SMS_ERR_BLOCK 		1
	#define SMS_ERR_CONNECTBREAK	2
	#define SMS_ERR_TIMEOUT 	3	
	#define SMS_ERR_SENDFAIL 	4	//�����ֻ�ģ���ͨѶ����������
	#define SMS_ERR_READFAIL 	5	//�����ֻ�ģ���ͨѶ����������
	#define SMS_ERR_CONNECTING  6
	#define SMS_ERR_SEND_SUCCEED 7
	#define SMS_ERR_REND_SUCCEED 8

	ShortMsgSourse	uint 	SMSErrorCode;	//�ֻ�ģ�鷵�صĴ�����

	//�����ض����ط��Ĵ���,�������ջ��Ƿ�������3�μ���������Ϣ
	//��¼����Ϣ�Ĵ���	
	ShortMsgSourse uchar SMSSendTime;
	//��¼����Ϣ�Ĵ���
	ShortMsgSourse uchar SMSReceiveTime;
	//�ط�������ʱ�Ĵ���
	#define RETRYTIME  5
	//�ط�������ʱ�����ʱ�䣬����Ϊ��λ
	#define INTERVAL_TIME 30

	//��������Ϣ����ն���ʱ���ִ���ʱ���ԵĴ���,
	//bit0��bit2��bit3���ڼ�¼�ط��Ĵ���
	//�˱�����bit7��bit6��λ���ڼ�¼����״̬
	//���������bit7Ϊ0,bit6λΪ1,��ֵ������bit6��bit7λ������5ʱ������������,����bit7Ϊ1,bit6Ϊ0;
	//���bit7Ϊ1,bit6Ϊ1,��ֵ������bit6��bit7λ������5ʱ,��ʾ�����������ŵķ��Ͷ����ɹ���
	//��ʱֹͣ���ŷ���
	//����гɹ��յ�һ�����Ż��м�ɹ����͹�һ�ζ��ţ����ô˱���
	ShortMsgSourse	uchar ReTryTime;

	//���ͻ���ն�������ָ��������û�гɹ������ֻ�ģ���µ�����
	ShortMsgSourse	uchar DownMobilePowerFlag;	
#endif

