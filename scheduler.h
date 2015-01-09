#ifndef _SCHEDULER_
#define _SCHEDULER_

#ifndef SCHEDULER_C
	#define SchedulerSourse extern
#else
	#define SchedulerSourse
#endif
	#define CS_GB2312    	936
	#define CS_WIN1252  	1252
	SchedulerSourse uchar xdata ZhkSchedulerState;
	SchedulerSourse void ZhkChannelSwitch( uchar type );
	SchedulerSourse uchar ZhkSchedulerAddTask( struct COMMTASK xdata* NewTask );
	
	/** @name ͨ���豸��ѯ�������ִ��״̬���� 
	 *
	 */
	 //@{
	/** ������ȴ��ڿ���״̬ */
	#define TASK_NULL		0x00
	/** ��ǰ�����ھ���״̬ */
	#define TASK_REDAY		0x01
	/** ��ǰ������ִ�еȴ�״̬ */
	#define TASK_WAIT		0x02
	/** ��ǰ����������ִ�в��ȴ�״̬ */
	#define TASK_REWAIT		0x03
	/** ��ǰ������ȷִ�н��� */
	#define TASK_FINISH  		0x04
	/** ��ǰ������� */
	#define TASK_ERROR		0x05
	//@}
	/** @name ͨ���豸��ѯ�������ȼ�����
	 *  ��ֵԽС���ȼ�Խ��
	 */
	 //@{
	/** ������ȴ��ڿ���״̬ */
	// 
	// ��ֵԽС���ȼ�Խ��
	#define PRIORITY1  		0x41
	#define PRIORITY2  		0x42
	#define PRIORITY3  		0x43
	#define PRIORITY4  		0x44
	#define PRIORITY5  		0x45
	#define PRIORITY6  		0x46
	//@}
	/** ������ͨ��������ȼ�Ϊ�����ȼ� */
	#define PRIORITY_NORMAL  	PRIORITY2
	
	/** ͨ���������Ͷ��� */
	struct COMMTASK
	{
		uchar 		Priority;		// ���ȼ���0 Ϊ��߼�
		uchar 		Id;			// id��
		uchar 		Cmd;			// ָ��
		uchar 		Sn;			// 
		uchar 		State;			//
		uchar 		ParamLen;		//
		uchar 		Param[32];		//
	};
	extern struct COMMTASK xdata CurrentTask;
	/**���Զ�ִ����������Ͷ��塡*/
	struct AUTOTASK
	{
		uchar 		Id;
		uchar 		Cmd;
		uchar 		Cycle;
	};
	/** �豸���Ͷ��塡*/
	struct DEVICE					// �豸�������Ͷ���

	{
		uchar Id;			// �豸ID
		uchar Sn;			// �豸sn������
		uchar CommState;		// bit0 = Buzy , bit1 = TimeOut , bit2 = CommOK
		uchar State;			// �豸����״̬
		uchar ExtState[17];		// �豸��չ״̬
	};
	/** @name�豸ͨ��״̬����
	 *
	 */
	//@{
	/** æ��־,���ڣ���ʾ��ǰ�豸ͨ��״̬����æ״̬�����ڣ���ʾ��æ */
	#define COMM_BUZY    		1
	
	/** ��ʱ��־,
	 *  ���ڣ�ʱ��ʾ��ǰͨ��δ����Ԥ��ʱ���ڽ��յ�Ӧ���źţ�
	 *  ���ڣ���ʾ��ǰͨ�������Ѿ���Ԥ��ʱ���ڽ��յ�Ӧ���ź� 
	 */
	#define COMM_TIMEOUT 		2
	/** ͨ�����������־ 
	 *  ���ڣ���ʾ��ǰͨ�����������������ʱ�ʹ������
	 *�����ڣ���ʾ��ǰͨ��������δ������
	 */
	#define COMM_COMMOK 		4  		// bit2 = CommOK
	//@}
	
///////////////////////////////////////////////////////////////////////////////////////	
///////////////////////////////////////////////////////////////////////////////////////
	
	/** ͨ���豸��ѯ������ȳ�ʼ�� */
	SchedulerSourse uchar SchedulerInit( void );
	/** �豸������ں��� */
	SchedulerSourse uchar SchedulerProcess( void );


///////////////////////////////////////////////////////////////////////////////////////
//
//       
//
///////////////////////////////////////////////////////////////////////////////////////
	/** ����豸�Ƿ�æ 
	 *  @param
	 */
	SchedulerSourse uchar TestDeviceBuzy( struct DEVICE xdata* Device );
	// ����豸�Ƿ�æ 
	// ����ֵ��
	// 	1 ��ʾæ��0��ʾ����

	SchedulerSourse uchar TestDeviceTimeOut( struct DEVICE xdata* Device );
	// ����豸�Ƿ�ʱ
	// ����ֵ��
	// 	1 ��ʾ��ʱ��0��ʾ����

	SchedulerSourse uchar TestDeviceCommOK( struct DEVICE xdata* Device );
	// ����豸�Ƿ�ͨ�����
	// ����ֵ��
	// 	1 ��ʾͨ����ɣ�0��ʾδ���

	SchedulerSourse uchar TestDeviceException( struct DEVICE xdata* Device );
	// ����豸�Ƿ����
	// ����ֵ��
	// 	1 ��ʾ���ϣ�0��ʾ����


	
///////////////////////////////////////////////////////////////////////////////////////
//
//      �豸״̬��ѯʹ�ܿ���
//
///////////////////////////////////////////////////////////////////////////////////////	
//	SchedulerSourse bit Hopper1QueryEnable( void );
	// �ұ�ģ��1״̬��ѯʹ��
	SchedulerSourse bit Hopper1QueryDisable( void );
	// �ұ�ģ��1״̬��ѯ����
	SchedulerSourse bit CasherQueryEnable( void );
	// ֽ����״̬��ѯʹ��
	SchedulerSourse bit CasherQueryDisable( void );
	// ֽ����״̬��ѯ����

///////////////////////////////////////////////////////////////////////////////////////
//
//      hubģ����ؽӿں�������
//	
///////////////////////////////////////////////////////////////////////////////////////	
//	SchedulerSourse bit DenoteLedLightOn( void );
	// ��������ָʾ��
//	SchedulerSourse bit DenoteLedLightOff( void );
	// Ϩ�����ָʾ��	
	
	//��������
//	SchedulerSourse bit SetAlertOn( void );
	//��������
//	SchedulerSourse bit SetAlertOff( void );

///////////////////////////////////////////////////////////////////////////////////////	
//
//      ���һ����ӿں��� 
//	
///////////////////////////////////////////////////////////////////////////////////////	
	SchedulerSourse bit HopperOutput( uchar HopperNum , uint CoinAmount );
	// ����ģ����ҿ���
	// ������
	// HopperNum	����ģ���ţ�ȡֵ��Χ1-2
	// CoinAmount  	��������(��λ��ö)

	SchedulerSourse bit HopperQuery( uchar HopperNum );
	// ����ģ��״̬����
	// ������
	// HopperNum	����ģ���ţ�ȡֵ��Χ1-2
	// ���ܣ����µ�ǰHopper״̬,
	// ����ֵ����
	
	SchedulerSourse uint HopperGetCoinOut( uchar HopperNum );
	// ����ģ���ѳ�������
	// ������
	// HopperNum	����ģ���ţ�ȡֵ��Χ1-2
	// ����ֵ��
	// �ѳ�������

	SchedulerSourse bit SelectionQuery( uchar itemNum );
    SchedulerSourse bit ACDCModuleQuery( void );
    SchedulerSourse bit HopperClearSn( uchar HopperNum );
///////////////////////////////////////////////////////////////////////////////////////	
//
//      Һ����ʾ�ӿں��� 
//	
///////////////////////////////////////////////////////////////////////////////////////	
	SchedulerSourse bit DisplaycharacterSet( uint CharSetCode );
	// ѡ���ַ���
	SchedulerSourse bit DisplayClear( void );
	// ����
	SchedulerSourse bit DisplayString( uchar * Str , const uchar len );
	// �Ե�ǰ���λ��Ϊ�����ʾһ���ַ�������ַ���������Ļ��Ƚ��Զ�����
	// �������ͣ�������һ����ʾ���ַ�����һ��λ��
	SchedulerSourse bit DisplayPosString( const uchar PosX , const uchar PosY , uchar * Str , const uchar len );
	// ��λ��ʾһ���ַ�������ַ�������Ļ��ȣ��������ֲ���ʾ
	// �������ͣ�������һ����ʾ���ַ�����һ��λ�ã�����г�����Ļ��ȣ����ͣ���ڵ�ǰ�е�ĩβ
	// ����
	// PosX ��ʼ��ĺ�����
	// PosY ��ʼ���������
	// Str  �ַ����׵�ַ
	// len  �ַ�������

//ygp close	
/*	SchedulerSourse bit DisplayScroll( uchar Direct );
	// ��Ļ����
	// ������
	// Direct ��Ļ�����ķ���ȡֵ��Χ0-3
	// 	0��ʾ���¹���
	// 	1��ʾ���Ϲ���
	// 	2��ʾ�������
	// 	3��ʾ���ҹ���
*/
	
	SchedulerSourse bit DisplaySetCursorStyle( uchar style );
	// ���ù������
	// ������
	// style �����ʾ����
	// 	0��ʾ���޹�꣬
	// 	1��ʾ�ֽڹ�꣬
	// 	2��ʾ���й�ꡣ

	SchedulerSourse bit DisplaySetCursorPos( uchar PosX , uchar PosY );
	// ���ù��λ��
	// ������
	// PosX ������
	// PosY ������
	SchedulerSourse bit DisplayBkLightOn( void );
	// ����Һ������
	SchedulerSourse bit DisplayBkLightOff( void );
	// Ϩ��Һ������

	SchedulerSourse uchar IsBackLightOn( void );
	// Һ�������Ƿ��ڵ���״̬

	SchedulerSourse uchar GetDisplayState();
///////////////////////////////////////////////////////////////////////////////////////	
//
//      ֽ�����ӿں��� 
//	
///////////////////////////////////////////////////////////////////////////////////////	

	SchedulerSourse bit CasherQuery( void );

	SchedulerSourse bit CasherAccept( void );
	// ����ֽ��
	SchedulerSourse bit CasherReject( void );
	// ����ֽ��
	SchedulerSourse uchar CasherIsCashIn( void );
	// �Ƿ���ֽ�ҽ���ȴ�����
	SchedulerSourse uchar CasherIsAcceptOK( void );
	// �Ƿ�ֽ�ҽ��ܳɹ�
	SchedulerSourse uint GetCash( void );
	// ��ȡ�ѽ��յ�ֽ�����
	SchedulerSourse uint GetComingCash( void );
	// ��ȡ�Ѽ�⵽��ֽ�����
	SchedulerSourse bit CasherEnable( void );
	SchedulerSourse bit CasherDisable( void );
	SchedulerSourse bit CasherReset( void );
	SchedulerSourse bit ZhkCasherQuery( void );
	//�����Ĺ���״̬����ֽ������ҵ����
	SchedulerSourse void CasherGetMachineState( uchar state );
	//���ⷢ��ֽ������ʵʱ״̬,0��ʾ������1��ʾ����
	SchedulerSourse uchar CasherRealTimeState( );
	//�˱��Ƿ�ɹ�
	SchedulerSourse uchar CasherIsRejectOK( void );
	//���ó�ʱ����
	SchedulerSourse void CasherResetOuttime( void );
	///////////////////////////////////////////////////////////////////////////////////////	
	//
	//      Ӳ�����ӿں��� 
	//	
	///////////////////////////////////////////////////////////////////////////////////////	
	//�ر�Ӳ������Դ
//	SchedulerSourse bit CoinPowerOff( void );
	//��Ӳ������Դ
//	SchedulerSourse bit CoinPowerOn( void );

	/*
	// Ӳ����״̬��ѯ
	SchedulerSourse bit CoinerQuery( void );	
	// �Ƿ���Ӳ�ҽ���
	SchedulerSourse uchar CoinerIsCoinIn( void );	
	// ��ȡ�ѽ��յ�ֽ�����	
	SchedulerSourse uint GetCoin( void );	
	// Ӳ����ʹ��
	SchedulerSourse bit CoinerEnable( void );
	// Ӳ��������
	SchedulerSourse bit CoinerDisable( void );
	// Ӳ������λ
	SchedulerSourse bit CoinerReset( void );
	//Ӳ������ѯʹ��
	SchedulerSourse bit CoinerQueryEnable( void );
	//Ӳ������ѯ����
	SchedulerSourse bit CoinerQueryDisable( void );
*/
	//////////////////////////////////////////////
	//			�����ӿ�				//////////
	//////////////////////////////////////////////
	//����״̬��ѯ
	SchedulerSourse bit ZhkChannelQuery();
	// ��������ģ���ѯָ��
	// ChannelNum ������ 1-64
	// ����ѯ�ɹ���
	// ״̬�洢��Channel.State
	//ChannelNum ��1��ʼ

	//��������
	SchedulerSourse bit ZhkChannelExec(  unsigned char ChannelNum,  unsigned char ReSendFlag );
	// ��������ģ�����ָ��
	// ChannelNum ������ 1-64
	//ChannelNum ��1��ʼ
	
	//��������
	SchedulerSourse bit ZhkChannelTest(  unsigned char ChannelNum );
	
	//��������SN����
	SchedulerSourse bit ZhkChannelClear();

	///�����ֻ�ģ�������״̬
	//����0��OK,1��ʧ��,3���ֻ�ģ��æ
	SchedulerSourse uchar TestATcommand();


//	SchedulerSourse bit ZhkLedScrset( uchar LEDWIDE , uint CharSum , void* ScrMsg );
	// ���¹������ʾ����
	// LEDWIDE ��Ļ��ȣ�8�ı���
	// CharSum ��ʾ���ݵ��ֽڳ���
	// ScrMsg ��ʾ���ݵ��׵�ַ

	// �豸����
	SchedulerSourse struct DEVICE xdata Hopper1;	
	SchedulerSourse struct DEVICE xdata Hopper2;
	SchedulerSourse struct DEVICE xdata Hopper3;

    SchedulerSourse struct DEVICE xdata Selection1;
    SchedulerSourse struct DEVICE xdata Selection2;
    SchedulerSourse struct DEVICE xdata Selection3;
    SchedulerSourse struct DEVICE xdata ACDCModule;

	//��չ״̬�е�ExtState[13]��¼ֽ������ʵʱ״̬,0Ϊ������1Ϊ����
	//��չ״̬�е�ExtState[14]��¼ֽ����������Ӧ��ʱ����,
	//��չ״̬�е�ExtState[15]��¼�����ĵ�ǰ״̬:����(0)�����״̬(1)
	SchedulerSourse struct DEVICE xdata Casher;
	SchedulerSourse struct DEVICE xdata Lcd;
	SchedulerSourse struct DEVICE xdata Channel;
//	SchedulerSourse struct DEVICE xdata Hub;
//	SchedulerSourse struct DEVICE xdata Coiner;	
	SchedulerSourse uchar xdata MaintFlag;	
	
	
////////////////////////////////////////////////////////////////////////////////////////



#endif
