#ifndef _FUNCTION_
#define _FUNCTION_
#ifndef COMMONFUNCTION_C
	#define FunctionSourse extern
#else
	#define FunctionSourse
#endif	

//#include "timer.h"
#include "Clock.h"
#include "scheduler.h"
#include "global.h"

//FunctionSourse struct WayList xdata InputGoodsWayList[ GOODSWAYNUM ];

//FunctionSourse unsigned char xdata InputGoodsNum[ GOODSWAYNUM ];
/*��ʱ��Ƭ�ø�Ӳ����ͨѶģ��*/
FunctionSourse void CoreProcessCycle();

/*�ó�ʱ��Ƭʵ�ֵȴ�,msec����Ϊָ��������,DeviceIDΪ�豸��ID���ָ��
	����ֵ��1Ϊ�豸æ��0Ϊ�豸��æ*/
FunctionSourse unsigned char WaitForWork( unsigned long msec, struct DEVICE xdata* DeviceID  );


FunctionSourse u_int CrcCheck(u_char *msg, u_int len); 
//�����ֵ	
FunctionSourse void ClearKey();

/*����һ���ַ�����strTipΪ��ʾ����lenΪstrTip�ĳ��ȣ�lineΪ���ص��ַ���,lenΪline����󳤶�
1:�ɹ���0��ʧ��*/
FunctionSourse unsigned char GetLine( unsigned char * strTip,unsigned char len, unsigned char y, unsigned char * line, unsigned char *len1);
FunctionSourse unsigned char GetLine_1( u_char  *strTip, unsigned char len, u_char y, u_char * line, unsigned char *len1, bit Passwdlog);

u_char GetLineMoney( u_char  *strTip, unsigned char len, u_char y, u_char * line, unsigned char *len1 );

/*��ʾ�ַ�,flag��־ָ�����Թ�굱ǰλ�û�����ָ��λ����ʾ�ַ���
	��flagΪ0���Ե�ǰλ��*/	
FunctionSourse void  DisplayStr( unsigned char x, unsigned char y, bit flag, unsigned char *str, const unsigned char len );

/*��ʾ���λ�ú�����,posflagȷ���Ƿ�����λ��,������0ʱx��y��Ч��stateflag������ͬ*/	
FunctionSourse void  DisplayCursorState( unsigned char x, unsigned char y, bit posflag, unsigned char state, bit stateflag );

/*��ȡ��������*/
FunctionSourse unsigned char GetOneKey();
FunctionSourse unsigned char GetOneIDKey();
FunctionSourse unsigned char GetOneMoneyKey();

FunctionSourse unsigned char LenOfNum( unsigned long num);

/*���������ң�iCoinNum��������,iHopperNo���������*/
//FunctionSourse unsigned char HopperOutCoin( unsigned char iCoinNum, unsigned char iHopperNo, struct DEVICE xdata* iDevice );
  FunctionSourse unsigned char HopperOutCoin( unsigned int iCoinNum, unsigned char iHopperNo, struct DEVICE xdata* iDevice );

//FunctionSourse unsigned char ChannelQuery(unsigned char ChannelNum );
//��������
//FunctionSourse unsigned char ChannelExec( unsigned char ChannelNum );
FunctionSourse unsigned char ChannelTask( u_char ChannelNum, u_char TaskId );
FunctionSourse u_char ChannelLifterTask( u_char ChannelNum, u_char TaskId );

//����������
FunctionSourse unsigned char InputGoodsWayNo( u_char i );

//ֽ��������
//FunctionSourse unsigned char HykCasherTask( unsigned char TaskId );

FunctionSourse unsigned char BaoLianCoinerTask( u_char TaskId );

/*�õ��豸״̬,iHopperNo������,ָ���豸,iDevice�豸�ṹָ��*/
FunctionSourse unsigned char GetHardWareDeviceState( unsigned char iHopperNo, struct DEVICE xdata* iDevice );
FunctionSourse unsigned char GetSelectionState( unsigned char id, struct DEVICE xdata* iDevice );
FunctionSourse unsigned char ACDCMission( void );

FunctionSourse unsigned char DisplayInfo( unsigned char line , unsigned char offset , unsigned char * buffer );

FunctionSourse void ClearDisplayLine( unsigned char Line );

//FunctionSourse void  PhoneTBCD( u_char *OutBuffer );

/*��Flash��װ������*/
FunctionSourse void  LoadGlobalParam();

/*������д��Flash��*/
FunctionSourse void  SaveGlobalParam();

/*�����������*/
FunctionSourse void SaveGoodsSet();

FunctionSourse void  SaveTradeParam();

//д����LOG
FunctionSourse void SaveTradeCounter();

/*��Flashȫ������ˢһ��*/
FunctionSourse void  FlashInit();

//��������
FunctionSourse void SaveRackSet();

//��������
FunctionSourse void SaveRackColumnSet();

//
FunctionSourse void SaveGoodsParSet( void );
FunctionSourse void ReadGoodsParSet( void );

#endif
