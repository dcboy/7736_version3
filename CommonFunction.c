//#undef _DEBUG_TRACE
#define COMMONFUNCTION_C
#include "debug.h"
#include "device.h"
#include "global.h"
#include "common.h"
#include "CommonFunction.h"
#include "key.h"
#include "STRING.H"
#include "DataExChange.h"
#include "mainflow.h"
#include "timer.h"
#include "SstFlash.h"
#include "procotol.h"
#include "casher.h"
#include "scheduler.h"
#include "IOInput.h"
#include "communication.h"
#include "ITL.h"
#include "VMC_PC.h"
#include "lifterApi.h"


/*��ʱ��Ƭ�ø�Ӳ����ͨѶģ��*/

struct WayList xdata InputGoodsWayList[ GOODSWAYNUM ] ;

void CoreProcessCycle()
{
	SchedulerProcess();
#ifndef _DEBUG_NO_MOBILE
	if( SystemParameter.MobileON == 1 )
		DoCommunication();
#endif
}

//Flash��ʼ��
void FlashInit()
{
	//FlashƬѡ
	//ѡ�е�һƬ
	ZhkHardFlashSelect();
	//��Ƭ����
	SstFlashChipErase();
	ZhkHardSramSelect();
	//ѡ�еڶ�Ƭ
	ZhkHardFlash1Select();
	//��Ƭ����
	SstFlashChipErase();
	ZhkHardSramSelect();
}

/*�ó�ʱ��Ƭʵ�ֵȴ�,msec����Ϊָ���ȴ�ʱ��, DeviceIDΪ�豸ID���ָ��*/
u_char WaitForWork( unsigned long msec, struct DEVICE xdata* DeviceID )
{
	unsigned long loopSec = msec / 1000;
	unsigned short loopMSec = msec % 1000;
		
	TestDeviceCommOK( DeviceID );
	// ���뼶��ʱ
	LzjMSecTimer = loopMSec & 0x7F;
	loopMSec /= 128;
	do
	{
		while(LzjMSecTimer)
		{			
			if( DeviceID != NULL )
			{
				SchedulerProcess();
				if( TestDeviceCommOK(  DeviceID ) == 0 )
					return 0;
			}
			else
			{		
				if( SystemParameter.MobileON == 1 )
				{
					Mission();
					CoreProcessCycle();			
				}
				else
					SchedulerProcess();	
			}
		}
		LzjMSecTimer = 128;
	}while(loopMSec--);

	// �뼶��ʱ
	SgpSecTimer = loopSec & 0x7F;
	loopSec /= 128;
	do
	{
		while(SgpSecTimer)
		{
			if( DeviceID != NULL )
			{
				SchedulerProcess();
				if( TestDeviceCommOK(  DeviceID ) == 0 )
					return 0;
			}
			else
			{
				if( SystemParameter.MobileON == 1 )
				{
					Mission();
					CoreProcessCycle();			
				}
				else
					SchedulerProcess();	
			}
		}
		SgpSecTimer = 128;
	}while(loopSec--);

	if( DeviceID != NULL )	
		return 1;
	else
		return 0;
			
}

/*********************************************************************************************************
** Function name:     	CrcCheck
** Descriptions:	    CRCУ���
** input parameters:    msg��Ҫ���������;len���ݳ���
** output parameters:   ��
** Returned value:      CRC������
*********************************************************************************************************/
u_int CrcCheck(u_char *msg, u_int len) 
{
    u_int xdata i, j;
    u_int xdata crc = 0;
    u_int xdata current = 0;
    for(i=0;i<len;i++) 
    {
        current = msg[i] << 8;
        for(j=0;j<8;j++) 
        {
            if((int)(crc^current)<0)
                crc = (crc<<1)^0x1021;
            else 
                crc <<= 1; 
            current <<= 1; 
        }
    }
    return crc;
}


//�����ֵ	
void ClearKey()
{
    u_char xdata ch = 0;

    if( sysVPMission.VPMode == 1 )
    {
	    //1.
        if( DeviceStatus.Selection[0] == 0 )
		{
			ch = GetSelectionState( 1, &Selection1 );
		    if( ch == 0 )
			{
			    DeviceStatus.Selection[0] &= 0xfe;
			}
			else
			{
				DeviceStatus.Selection[0] |= 0x01;
			}
		}
		//2.
        if( DeviceStatus.Selection[1] == 0 )
		{
			ch = GetSelectionState( 2, &Selection2 );
		    if( ch == 0 )
			{
			    DeviceStatus.Selection[1] &= 0xfe;
			}
			else
			{
				DeviceStatus.Selection[1] |= 0x01;
			}
		}
		//3.
		if( DeviceStatus.Selection[2] == 0 )
		{
			ch = GetSelectionState( 3, &Selection3 );
		    if( ch == 0 )
			{
			    DeviceStatus.Selection[2] &= 0xfe;
			}
			else
			{
				DeviceStatus.Selection[2] |= 0x01;
			}
		}
    
    }
    else
    {
		KeyLock();
		KeyUnLock();
    }
}

/*��ʾ�ַ�,flag��־ָ�����Թ�굱ǰλ�û�����ָ��λ����ʾ�ַ���
	��flagΪ0���Ե�ǰλ��*/	
void  DisplayStr( u_char x, u_char y, bit flag, u_char *str, const u_char len )
{	
	u_char xdata timeflag = 1;
	u_char xdata clearstr[] = "                    ";
	u_char xdata tempstr[20];
	u_char xdata i = 0;
	u_char xdata j = 0;

	memset( tempstr, 0x20, sizeof( tempstr ) );
	if( flag == 0 )//�ڵ�ǰλ����ʾ				
		i = DisplayString( str, len );		
	else
	{				
		if( ( x + len ) < 20 )			
			memcpy( tempstr + x, str, len );		
		else
			memcpy( tempstr + x, str, 20 );
        //len = 20;		
		i = DisplayPosString( 0, y, tempstr, 20 );//������Ļ�ִ�
	}	
	if( i == 0 )
		return ;
	i = 0;
	j = 0;
	while( ! ( i || j ) )
	{
		WaitForWork( 50, NULL );
		i = TestDeviceTimeOut( &Lcd );
		j = TestDeviceCommOK( &Lcd );		
	}
    //WaitForWork( 3000, &Lcd );
}

//��������
u_char GetOneIDKey()
{
	u_char xdata k = KEY_NULL ;
	u_char xdata m_str[2];
//	u_char xdata line[2];	
	unsigned int xdata interval = 500;   //��ʱʱ��5��

	memset( m_str, 0, 2 );
	m_str[0] = '*';
	while( ( k == KEY_NULL ) && ( interval != 0 ) )
	{
		SchedulerProcess();
		WaitForWork( 50, NULL );
		k = GetKey();			
		interval --;
	}
	switch( k )
	{
		case KEY_0:
		case KEY_1:
		case KEY_2:
		case KEY_3:
		case KEY_4:
		case KEY_5:
		case KEY_6:
		case KEY_7:
		case KEY_8:
		case KEY_9:			
	//	case KEY_DOT:		
		//	NumberToString( k ,  m_str , 1  );				
		//	sprintf( m_str,"%bu", k );
			DisplayStr( 0, 0, 0, m_str, 1 );
		    break;			
	}	
	if(interval == 0)
		return KEY_NULL;	
	return k;	
}


/*����һ���ַ�����strTipΪ��ʾ����lenΪstrTip�ĳ��ȣ�y Ϊ��ʾ�кţ�lineΪ���ص��ַ���,len1Ϊ������볤�ȼ�ʵ���������
1:�ɹ���0��ʧ��*/	  
u_char GetLine( u_char  *strTip, unsigned char len, u_char y, u_char * line, unsigned char *len1)
{
    u_char 	xdata key;
	u_char  xdata iCounter = 0;
	u_char  xdata len_loca;
	u_char xdata space_char = 0x20;
	u_char xdata Tempstr[20];

	memset( Tempstr, 0, sizeof( Tempstr ) );
	iCounter = 0;
	ClearKey();
	len_loca = *len1;		
	if( len + len_loca > 20 )
	{	
		DisplayStr( 0, 0, 1, strTip, len );		
		DisplayStr( 0, 1, 1, " ", 1 );	
		DisplayCursorState( 0, 1, 1, 1, 1 );	
	}
	else
	{
		DisplayStr( 0, y, 1, strTip, len );
		DisplayCursorState( len, y, 1, 1, 1 );		
	}
	SgwSecTimer= 30;
	while( SgwSecTimer )
	{
		WaitForWork( 20, NULL );			
		if(iCounter >= len_loca)	
		{
			*len1 = len_loca;
		//	WaitForWork( 800, NULL );		
			memcpy( line, Tempstr, len_loca );
			return 1;
		}
		key = GetOneKey();	
		if ( (key == KEY_UP) || (key == KEY_DOWN) || (key == KEY_DOT) || (key == KEY_NULL) )
		    continue;
		else if( key == KEY_SUBMIT) 
		{				
			*len1 = iCounter;			
			memcpy( line, Tempstr, iCounter );
			return 1;
		}			
		else if(key == KEY_CANCEL)
			return 0;
		else if( key == KEY_BACK)//clear��,������һ��
		{		
			if( iCounter >= 1 )
			{
				if( len + len_loca >= 20 )
				{										
					DisplayPosString( iCounter - 1, 1, &space_char, 1); /* ��Ļ���һ�������ַ� */	
					WaitForWork( 300, &Lcd );
					DisplaySetCursorPos( iCounter - 1 , 1 );//���ù��λ��				
					WaitForWork( 300, &Lcd );
				}
				else
				{										
					DisplayPosString( iCounter + len - 1, y, &space_char, 1); /* ��Ļ���һ�������ַ� */	
					WaitForWork( 300, &Lcd );
					DisplaySetCursorPos( iCounter + len - 1 , y );//���ù��λ��				
					WaitForWork( 300, &Lcd );
				}						
				*(line + iCounter) = 0;
				iCounter--;		
				SgwSecTimer = 30;
			}
			
		}
		else
		{						
			Tempstr[ iCounter ] = key;			
			iCounter++;
			SgwSecTimer = 30;			
		}			
	}
}

/*����һ���ַ�����strTipΪ��ʾ����lenΪstrTip�ĳ��ȣ�lineΪ���ص��ַ���,
lenΪline����󳤶�,PasswdlogΪ��������(1)����������(0) 1:�ɹ���0��ʧ��*/	  
u_char GetLine_1( u_char  *strTip, unsigned char len, u_char y, u_char * line, unsigned char *len1, bit Passwdlog)
{
    u_char 	xdata key;
	u_char  xdata iCounter = 0;
	u_char  xdata len_loca;
	u_char xdata space_char = 0x20;
	u_char xdata Tempstr[20];

	memset( Tempstr, 0, sizeof( Tempstr ) );
	iCounter = 0;
	ClearKey();
	len_loca = *len1;		
	if( len + len_loca >= 20 )
	{	
		DisplayStr( 0, 0, 1, strTip, len );		
		DisplayStr( 0, 1, 1, " ", 1 );	
		DisplayCursorState( 0, 1, 1, 1, 1 );	
	}
	else
	{
		DisplayStr( 0, y, 1, strTip, len );
		DisplayCursorState( len, y, 1, 1, 1 );		
	}

    //SgwSecTimer = 30;
	while( 1 )
	{
		WaitForWork( 50, NULL );			
		key = KEY_NULL;
		ClearKey();
		if(iCounter >= len_loca)	
		{
			*len1 = len_loca;		
			memcpy( line, Tempstr, len_loca );
			return 1;
		}
		if( Passwdlog == 1 )
			key = GetOneIDKey();	
		else
			key = GetOneKey();			
		if ( (key == KEY_UP) || (key == KEY_DOWN) /*|| (key == KEY_BACK)*/ || (key == KEY_NULL) )
		    continue;
		else if( key == KEY_SUBMIT) 
		{				
			*len1 = iCounter;			
			memcpy( line, Tempstr, iCounter );
			return 1;
		}			
		else if(key == KEY_CANCEL)
			return 0;
		else if( key == KEY_BACK)//clear��,������һ��
		{		
			if( iCounter >= 1 )
			{
				if( len + len_loca >= 20 )
				{										
					DisplayPosString( iCounter - 1, 1, &space_char, 1); /* ��Ļ���һ�������ַ� */	
					WaitForWork( 300, &Lcd );
					DisplaySetCursorPos( iCounter - 1 , 1 );//���ù��λ��				
					WaitForWork( 300, &Lcd );
				}
				else
				{										
					DisplayPosString( iCounter + len - 1, y, &space_char, 1); /* ��Ļ���һ�������ַ� */	
					WaitForWork( 300, &Lcd );
					DisplaySetCursorPos( iCounter + len - 1 , y );//���ù��λ��				
					WaitForWork( 300, &Lcd );
				}						
				*(line + iCounter) = 0;
				iCounter--;				
			}			
		}
		else
		{						
			Tempstr[ iCounter ] = key;			
			iCounter++;					
		}			
	}
	return 0;
}


/*��ȡ�����������*/
u_char GetOneMoneyKey()
{
	u_char xdata k = KEY_NULL ;
	u_char xdata m_str[2];
//	u_char xdata line[2];	
	unsigned int xdata interval = 500;   //��ʱʱ��5��
	
	memset( m_str, 0 , sizeof (m_str ) );
	while( ( k == KEY_NULL ) && ( interval != 0 ) )
	{
		SchedulerProcess();
		WaitForWork( 50, NULL );
		k = GetKey();			
		interval --;
	}
	switch( k )
	{
		case KEY_0:
		case KEY_1:
		case KEY_2:
		case KEY_3:
		case KEY_4:
		case KEY_5:
		case KEY_6:
		case KEY_7:
		case KEY_8:
		case KEY_9:			
			NumberToString( k ,  m_str , 1  );				
		//	sprintf( m_str,"%bu", k );
			DisplayStr( 0, 0, 0, m_str, 1 );
		    break;	
	}	
	if(interval == 0)
		return KEY_NULL;	
	return k;	
}

/*����һ���ַ�����strTipΪ��ʾ����lenΪstrTip�ĳ��ȣ�lineΪ���ص��ַ���,
lenΪline����󳤶�,PasswdlogΪ��������(1)����������(0) 1:�ɹ���0��ʧ��*/	  
u_char GetLineMoney( u_char  *strTip, unsigned char len, u_char y, u_char * line, unsigned char *len1 )
{
    u_char xdata key;
	u_char xdata iCounter = 0;
	u_char xdata len_loca;
	u_char xdata space_char = 0x20;
	u_char xdata Tempstr[20];

	memset( Tempstr, 0, sizeof( Tempstr ) );
	iCounter = 0;
	ClearKey();
	len_loca = *len1;		
	if( len + len_loca >= 20 )
	{	
		DisplayStr( 0, 0, 1, strTip, len );		
		DisplayStr( 0, 1, 1, " ", 1 );	
		DisplayCursorState( 0, 1, 1, 1, 1 );	
	}
	else
	{
		DisplayStr( 0, y, 1, strTip, len );
		DisplayCursorState( len, y, 1, 1, 1 );		
	}
	while( 1 )
	{
		WaitForWork( 50, NULL );			
		key = KEY_NULL;
		ClearKey();
		if(iCounter >= len_loca)	
		{
			*len1 = len_loca;		
			memcpy( line, Tempstr, len_loca );
			return 1;
		}
		key = GetOneMoneyKey();			
		if ( (key == KEY_UP) || (key == KEY_DOWN) || (key == KEY_DOT) || (key == KEY_NULL) )
		    continue;
		else if( key == KEY_SUBMIT) 
		{				
			*len1 = iCounter;			
			memcpy( line, Tempstr, iCounter );
			return 1;
		}			
		else if(key == KEY_CANCEL)
			return 0;
		else if( key == KEY_BACK)//clear��,������һ��
		{		
			if( iCounter >= 1 )
			{
				if( len + len_loca >= 20 )
				{										
					DisplayPosString( iCounter - 1, 1, &space_char, 1); /* ��Ļ���һ�������ַ� */	
					WaitForWork( 300, &Lcd );
					DisplaySetCursorPos( iCounter - 1 , 1 );//���ù��λ��				
					WaitForWork( 300, &Lcd );
				}
				else
				{										
					DisplayPosString( iCounter + len - 1, y, &space_char, 1); /* ��Ļ���һ�������ַ� */	
					WaitForWork( 300, &Lcd );
					DisplaySetCursorPos( iCounter + len - 1 , y );//���ù��λ��				
					WaitForWork( 300, &Lcd );
				}						
				*(line + iCounter) = 0;
				iCounter--;						
			}			
		}
		else
		{						
			Tempstr[ iCounter ] = key;			
			iCounter++;			
		}			
	}
	return 0;
}

void ClearDisplayLine( u_char Line )
{
	if( ( Line > 0 ) && ( Line < 3 ) )
	{
		DisplayStr( 0, Line - 1 , 1 , "                    " , 20 );
		WaitForWork( 20, NULL );	
	}
}


/*��ʾ���λ�ú�����,posflagȷ���Ƿ�����λ��,������0ʱx��y��Ч��stateflag������ͬ*/	
void  DisplayCursorState( u_char x, u_char y, bit posflag, u_char state, bit stateflag   )
{		
	u_char xdata i = 0;
	u_char xdata j = 0;

	if( posflag == 1 )	
		i = DisplaySetCursorPos( x, y );	
	if( stateflag == 1 )			
		i = DisplaySetCursorStyle( state );

	if( i == 0 )
		return ;
	i = 0;
	j = 0;
	while( ! ( i || j ) )
	{
		WaitForWork( 50, NULL );
		i = TestDeviceTimeOut( &Lcd );
		j = TestDeviceCommOK( &Lcd );		
	}
//	WaitForWork( 3000, &Lcd );
}

/*��ȡ��������*/
u_char GetOneKey()
{
	u_char xdata k = KEY_NULL ;
	u_char xdata m_str[2];
//	u_char xdata line[2];	
	unsigned int xdata interval = 500;   //��ʱʱ��5��
	
	memset( m_str, 0 , sizeof (m_str ) );
	while( ( k == KEY_NULL ) && ( interval != 0 ) )
	{
		CoreProcessCycle();
		WaitForWork( 50, NULL );
		k = GetKey();			
		interval --;
	}
	switch( k )
	{
		case KEY_0:
		case KEY_1:
		case KEY_2:
		case KEY_3:
		case KEY_4:
		case KEY_5:
		case KEY_6:
		case KEY_7:
		case KEY_8:
		case KEY_9:			
			NumberToString( k ,  m_str , 1  );				
		//	sprintf( m_str,"%bu", k );
			DisplayStr( 0, 0, 0, m_str, 1 );
		    break;
	//	case KEY_DOT:		
	//		m_str[0] = 0x2e;
    //      DisplayStr( 0, 0, 0, m_str, 1 );  
	//		break;
	}	
	if(interval == 0)
		return KEY_NULL;	
	return k;	
}

/*�����ֵĳ���*/
/*�����ֵĳ���*/
u_char LenOfNum( unsigned long num )
{
	if(num >= 1000000000 )
		return 10;
	if(num >= 100000000 )
		return 9;
	if(num >= 10000000 )
		return 8;
	if(num >= 1000000 )
		return 7;
	if(num >= 100000 )
		return 6;
	if(num >= 10000 )
		return 5;
	else if(num >= 1000 )
		return 4;
	else if(num >= 100 )
		return 3;
	else if(num >= 10 ) 
		return 2;
	else
		return 1;
} 

//����ģ���յ���᷵��ACKӦ���
u_char HopperOutCoin( u_int iCoinNum, u_char iHopperNo, struct DEVICE xdata* iDevice )
{	
	u_char xdata i = 0;
	u_char xdata j = 0;

	HopperOutput( iHopperNo , iCoinNum );
	WaitForWork( 100, NULL );
	i = 0;
	j = 0;
	while( ! ( i || j ) )
	{
		WaitForWork( 100, NULL );
		i = TestDeviceTimeOut( iDevice );
		j = TestDeviceCommOK( iDevice );		
	}		
	if ( i )	
	{
		return 1;//��ʱ
	}
//	if ( TestDeviceException( iDevice ) )
//	{
//		return 2;//����
//	}
	Trace("\n HopperOutCoin OK" );
	sysVPMission.hopperCoinNum = iCoinNum;
	return 0; // ��������
}
   

//�������,�����������������߼�����������������б�ţ�����ʧ�ܷ���100
u_char InputGoodsWayNo( u_char x )
{
	u_char xdata key = 0;
	u_char xdata m_InputCode;
	u_char xdata m_GoodsWayNo;
	u_char xdata Tempstr[8];
	u_char xdata len = 0;
	u_char xdata i = 0;
	
	ClearKey();
	while( 1 )
	{		
		ClearDisplayLine( 1 );
		ClearDisplayLine( 2 );		
		len = 2;
		memset( Tempstr,0, sizeof( Tempstr ) );	
	#ifdef _CHINA_
		key = GetLine( "��������: ", 12 , 0, Tempstr, &len );
	#else	
		key = GetLine( "Input column code:", 18 , 0, Tempstr, &len );
	#endif
		WaitForWork( 500, NULL );	
		m_GoodsWayNo = 100;
		m_InputCode = 0;
		ClearKey();				
		if( key == 1 )//Enter	
		{			
			DisplayCursorState( 0, 0, 0, 0, 1 );			
			for( i = 0; i < len; i ++ )
			{
	//			Trace( "\n GoodsNo1 = %bu", Tempstr[i] );		
				if( ( Tempstr[i] >= 0 ) && ( Tempstr[i] <= 9 ) )
					m_InputCode = m_InputCode * 10 + Tempstr[i];				
			}
			if( ( m_InputCode == 99 ) && ( x == 0 ) )
				return 99;					
			ClearKey();	
			if( m_InputCode != 0 )
			{
				for( i = 0; i < GOODSWAYNUM; i ++ )
				{
					if( InputGoodsWayList[i].GoodsWayNo == m_InputCode )
					{
						m_GoodsWayNo = i;					
						return i;
					}
				}		
			}
			else
				i = GOODSWAYNUM;
			if( i == GOODSWAYNUM )
	 	    {
			#ifdef _CHINA_
				DisplayStr( 0, 0, 1, "����������", 12 );
				DisplayStr( 0, 1, 1, "�������������", 14 );
			#else
				DisplayStr( 0, 0, 1, "Input code error", 16 );
				DisplayStr( 0, 1, 1, "Input other code", 16 );
			#endif
				m_GoodsWayNo = 100;			
				WaitForWork( 2000, NULL );
				continue;
			}			
	//		Trace( "\n m_SetArrayNo = %bu", m_GoodsWayNo );
	//		Trace( "\n return 0" );
			return m_GoodsWayNo;
		}
		else
			return m_GoodsWayNo;
	}
}






/*����ֵ������
	0:��ȷִ�е�����
	1:��������ʧ��
	2:ִ�����ʱ
	3:�����޻�
	4:��������
	5:���޶���ʱ���ڵ�����ܵ�λ
    6:
    7: CMD ERR
    8: GOC check error 
*/
u_char ChannelTask( u_char ChannelNum, u_char TaskId )
{	
	u_char xdata i = 0;
	u_char xdata j = 0;
	u_char xdata z = 0;

	#ifdef   _SJJ_//������
		return 0;
	#endif
	
	while( z < 2 )
	{
		switch( TaskId )
		{
			case CHANNEL_EXEC://����			
				ZhkChannelExec( ChannelNum, z );			
				break;
			case CHANNEL_QUERY://��ѯ����ִ�����
				ZhkChannelQuery();
				break;
			case CHANNEL_TEST://��������
				ZhkChannelTest( ChannelNum );			
				break;
			case CHANNEL_CLEAR://ͬ��SN
				ZhkChannelClear();
				break;		
			default:
				return 0;
		}
		i = 0;
		j = 0;
		while( ! ( i || j ) )
		{
			WaitForWork( 50, NULL );
			i = TestDeviceTimeOut( &Channel );
			j = TestDeviceCommOK( &Channel );		
		}
	//	Trace("\n i = %bu, j = %bu", i, j );
		if( i ) //��ʱ����������	
		{
			if( ( TaskId == CHANNEL_EXEC ) || ( TaskId == CHANNEL_TEST ) )
			{
				if( Channel.ExtState[2] == 0 )	//û���յ�����ACK������һ��
				{
					z++;
					continue;
				}
				else if( Channel.ExtState[2] == 1 )//�յ�����ACK����û���յ���ϢACK�����ѯ����ִ�����
				{
					TaskId = CHANNEL_QUERY;
					z++;
			//		Trace("\n CHANNEL_QUERY" );
					continue;
				}
			}
			else
			{
		//		Trace("\n TimeOut" );
				return 2;
			}
		}
		else
			break;
	}
	if( i )
		return 2;
	/*״̬�ֽ��и�λ������
	  Bit 6: ���յ���������д���
	  Bit 5: ����û��ͨ����������
	  Bit 4: ���޶���ʱ���ڵ�����ܵ�λ
	  Bit 3: ���û��ת��
	  Bit 2: ��ת��ǰ���û�е�λ
	  Bit 1: ��Ʒ���գ�����
	  Bit 0: ����ʧ�� */
	switch( TaskId )
	{
	    
		case CHANNEL_EXEC:
		case CHANNEL_QUERY:	
		case CHANNEL_TEST:
			//----------------------------------------------------------------------
			//Added by Andy on 2010.10.21 for GOC device
             if( SystemParameter.GOCOn == 1 )
    		 {
					if( Channel.State & 0x80 )
					{
						DeviceStatus.GOCStatus |= 0x01;	
					}
                    else
                    {
                        DeviceStatus.GOCStatus &= 0xFE;
                    }
			 }
			//======================================================================
			if( Channel.State & 0x01 ) 
			{	
                /*
                2011.3.4 disabled!
				if( Channel.State & 0x04 )
					return 3;//��ת��ǰ���û�е�λ��û�г������˻����Ѳ��ܹ�����
                */
				if( Channel.State & 0x08 )
				{				    
					return 4;//���û��ת����û�г�������������һ��
				}
				//�г��ֻ���δת����δת��λʱ������Ǯ;by cq 20110909
				//if( Channel.State & 0x10 )
				//	return 5;//���޶���ʱ���ڵ�����ܵ�λ�������ѳ��ɹ���������Ӳ�����ϣ�
                if( Channel.State & 0x10 )					
				{

				    /*
	                if( SystemParameter.GOCOn == 1 )
	    			{
						if(!( Channel.State & 0x20 ))
						{						    
							return 5;
						}						
						return 4;
	                }
					*/					
					return 4;
				}

				if( Channel.State & 0x40 )
					return 7;//���յ���������д��󣬵���û�г�����������һ��
				//----------------------------------------------------------------------
				//Added by Andy on 2010.10.21 for GOC device
                if( SystemParameter.GOCOn == 1 )
    			{
					if( Channel.State & 0x20 )
					{
					    //if( ( DeviceStatus.GOCStatus == 0x00 ) )
                        /*
						if( SystemParameter.SVC_GOCErr == 0x00 )
						{
							return 8;
						}
						else
						{
						    return 0;	
						}
                        */						
                        return 8;
					}
				}
				//======================================================================
				return 1;//����ʧ��
			}
			break;		
		case CHANNEL_CLEAR:
            {
            	//----------------------------------------------------------------------
				//Added by Andy on 2010.10.21 for GOC device
	             if( SystemParameter.GOCOn == 1 )
	    		 {
						if( Channel.State & 0x80 )
						{
							DeviceStatus.GOCStatus |= 0x01;	
						}
	                    else
	                    {
	                        DeviceStatus.GOCStatus &= 0xFE;
	                    }
				 }
				//======================================================================
            }
			break;
	}		
	return 0;//�����ɹ�
}

/*
//������ѯ
u_char ChannelQuery( u_char ChannelNum )
{
	u_char xdata i = 0;
	u_char xdata j = 0;

//	if ( ChannelNum > GOODSWAYNUM || ChannelNum == 0 ) 	
//		return 4;//��������ȷ
//	Trace( "\n ChannelQuery" );
	ZhkChannelQuery( ChannelNum );
	i = 0;
	j = 0;
	while( ! ( i || j ) )
	{
		WaitForWork( 100, NULL );
		i = TestDeviceTimeOut( &Channel );
		j = TestDeviceCommOK( &Channel );		
	}
	if( i ) 
		return 3;//��ʱ����������
	else if( Channel.State & 0x01 )
		return 2;//����ʧ��
	return 0;//��������
}

//��������
u_char ChannelExec( u_char ChannelNum )
{
	u_char xdata i = 0;
	u_char xdata j = 0;

//	if ( ChannelNum > 64 || ChannelNum == 0 ) 	
//		return 1;//��������ȷ
	ZhkChannelExec( ChannelNum );
	i = 0;
	j = 0;
	while( ! ( i || j ) )
	{
		WaitForWork( 100, NULL );
		i = TestDeviceTimeOut( &Channel );
		j = TestDeviceCommOK( &Channel );		
	}	
	if ( i )	
		return 3;//��ʱ,�����������ͨѶ������,����Ϊ��������ͳ������
	if ( Channel.State & 0x01 ) 	
		return 2;//����ʧ��
	return 0;//�����ɹ�
	
}
*/

//id=4, ACDCModule
u_char GetSelectionState( u_char id, struct DEVICE xdata* iDevice )
{
	u_char xdata i = 0;
	u_char xdata j = 0;
	u_char xdata timeBuf = 0;
 
	if( ( id == 1 ) || ( id == 2 ) || ( id == 3 ) || ( id == 4 ) )
	{
		timeBuf = 3;  //10-3
    }
	for( YgpSecTimer=timeBuf; YgpSecTimer; )
	{  		
	    SelectionQuery( id );
		while( 1 )
		{
			i = TestDeviceCommOK( iDevice );
			j = TestDeviceTimeOut( iDevice );
			if( !( j || i ) )					
			{
				WaitForWork( 100, NULL );
				i = 0;
			}
			else
            {
				break;
            }	
		}
		if( i == 4 )
        {
			break;
		}
		WaitForWork( 100, NULL );
	}
	if( ( YgpSecTimer == 0 ) || ( j ) )
	{		
		Trace("\n Time Out" );
		return 1;      //��ʱ
	}
    /*	
	if ( TestDeviceException( iDevice ) )
	{
		return 2;   //����
	}
    */
	return 0;   //��������
	
}


u_char ACDCMission( void )
{
    u_char xdata flag = 0;

	if( SystemParameter.ACDCModule == 0 )
	{
		return 1;
	}

	if( DeviceStatus.ACDCModule == 0 )
	{
		flag = GetSelectionState( 4, &ACDCModule );
	    if( flag == 0 )
		{
		    DeviceStatus.ACDCModule &= 0xfe;
            //DeviceStatus.ACDCModule = 0;
			return 0;
		}
		else
		{
			DeviceStatus.ACDCModule |= 0x01;
			return 1;
		}
	}
	//return 0;
}

u_char GetHardWareDeviceState( u_char iHopperNo, struct DEVICE xdata* iDevice )
{
	u_char xdata i = 0;
	u_char xdata j = 0;
	u_int xdata timeBuf = 0;
    u_char xdata result = 0;

    //----------------------------------------------------------------------------------
    //Changed by Andy on 2010.11.2
    if( ( iHopperNo == 1 ) || ( iHopperNo == 2 ) || ( iHopperNo == 3 ) )
    {
    	//timeBuf = 5000;  //255-120-255(2011.6.16),5000(20110616)
		//ʱ������Ҫ���ҵ�������ȷ����20S����ʱʱ��;by gzz 20110616
		timeBuf = sysVPMission.hopperCoinNum/4 + 20;		
    }
    else
    {
    	timeBuf = 10;
    }        
    //==================================================================================
    
	//for( YgpSecTimer = timeBuf; YgpSecTimer ; )
    //for( YgpSecTimer=timeBuf; YgpSecTimer>0; )//by gzz 20110616
	for( sysVPMission.hopperOutTimer=timeBuf; sysVPMission.hopperOutTimer>0; )
	{			
		if( ( iHopperNo == 1 ) || ( iHopperNo == 2 ) || ( iHopperNo == 3 ) )  //������״̬
        {
			HopperQuery( iHopperNo );
        }
		else if( iHopperNo == 4 )   //ֽ����״̬
		{
            if( sysITLMission.ITLSet == 1 )
            {
                i = ITLMission_Poll();
            }
            else
            {
				i = CasherQuery( );	
			    WaitForWork( 100, NULL );
            }
		}
        sysVPMission.hopperTimer = timeBuf;
		while( sysVPMission.hopperTimer )
		{
            
            //--------------------------------------------------------------------------
            if( (iHopperNo>=1)&&(iHopperNo<=3) )
            {
            	WaitForWork( 100, NULL );
                //sysVPMission.msGameTimer1 = 200;
				//while( sysVPMission.msGameTimer1 )
				{
					//----------------------------------------------------
			        //Send the game key and poll pc in speciall time
		    		if( IfGameKeyOn() )
					{
						VPMission_Button_RPT( VP_BUT_GAME, VP_BUT_NUMBER );
		        		//Beep();
					}
			        result = VPMission_Poll();
			        //===============================
				} 
            }
            //============================================================================

			i = TestDeviceCommOK( iDevice );
			j = TestDeviceTimeOut( iDevice );
			if( !( j || i ) )					
			{
				WaitForWork( 100, NULL );
				i = 0;
			}
			else
				break;	
		}
		if( iHopperNo == 4 )
			break;
		if( i == 4 )
			break;		
		WaitForWork( 100, NULL );
	}

	//if( ( YgpSecTimer == 0 ) || ( j ) )//by gzz 20110616
	if( ( sysVPMission.hopperOutTimer == 0 ) || ( j ) )
	{		
		Trace("\n Time Out" );
		return 1;//��ʱ
	}	
	if ( TestDeviceException( iDevice ) )
	{
        //Trace("\n Exception" );
		return 2;//����
	}
	return 0; //��������	
}


/*
void   PhoneTBCD( u_char *OutBuffer )
{
	u_char xdata i = 0;
	for( i = 0; i < 16; i +=2 )		
	{
		if( SystemParameter.GSMNO[i] != 0xff )
		{
			if( SystemParameter.GSMNO[i + 1] != 0xff )
				OutBuffer[i/2]  = SystemParameter.GSMNO[i] * 16 + SystemParameter.GSMNO[i+1];
			else
			{
				if( ( i % 2 ) == 0 )
				{
					OutBuffer[i/2] = SystemParameter.GSMNO[i] * 16 + 15;
					OutBuffer[i/2+1 ] = 0xff;
					break;
				}
				else
				{						
					OutBuffer[i/2 + 1 ] = 0xff;
					break;
				}
			}
		}
		else
			OutBuffer[i/2 ] = 0xff;
	}	
	return;	
}
*/
u_char DisplayInfo( u_char line , u_char offset , u_char * buffer )
{
	u_char xdata length;

	length = strlen( buffer );
	DisplayStr( offset , line , 1 , buffer , length );
	return( 0 );
}

void  LoadTradeParam()
{
	//uint8_t *tp2;
	//uint16_t crc;
	u_char xdata RdBuf[128]={0};
	u_int xdata num=0;
	u_int xdata len = 0;
	u_int xdata crc=0;
	//u_char xdata str[20];
	/*
	tp2 = (uint8_t *) &SystemPara;//�������ݼ�¼		
	AT45DBReadPage(4090,tp2);
	

	crc = CrcCheck(tp2,124);
	Trace("\r\n defaultsys=%d,%x,%x",124,crc/256,crc%256);
	if( (crc/256 == SystemPara.CrcCheck[0])&&(crc%256 == SystemPara.CrcCheck[1]) )
	{
		return 1;
	}
	else
	{
		return 0;
	}*/
	//���׼�¼
	//MovFlashToSram( ADDRF_TRADECOUNTER , ( unsigned char xdata * )&TradeCounter , sizeof(struct TRADECOUNTER) );
	//1.�����ݵ�������
	MovFlashToSram( ADDRF_TRADECOUNTER , RdBuf , 128 );	
	len = sizeof(struct TRADECOUNTER);
	//2.���ݵ��뵽�ṹ����
	memcpy(( unsigned char xdata * )&TradeCounter ,RdBuf, len);
    //3.������CRCУ��
	crc = CrcCheck(RdBuf,len);
	//Trace("\r\n defaultsys=%d,%x,%x",num,crc/256,crc%256);
	//4.�ṹ���д��ԭ�ȶ����У��ֵ
	//TradeCounter.CrcCheck[0] = RdBuf[126];
	//TradeCounter.CrcCheck[1] = RdBuf[127]; 
	//���Ƚ�
	if( (HUINT16(crc) == RdBuf[len])&&(LUINT16(crc) == RdBuf[len+1]) )
	{
		//len = sprintf( str, "deng=%x,%x-%x,%x", HUINT16(crc),LUINT16(crc),RdBuf[len],RdBuf[len+1] );
		//DisplayStr( 0, 0, 1, str, len );
		//WaitForWork( 2000, NULL );		
	}	
	else
	{
		//len = sprintf( str, "budeng=%x,%x-%x,%x", HUINT16(crc),LUINT16(crc),RdBuf[len],RdBuf[len+1] );
		//DisplayStr( 0, 0, 1, str, len );
		//WaitForWork( 2000, NULL );
		//������������ҳ
		//1.�����ݵ�������
		MovFlashToSram( ADDRF_TRADECOUNTERCOPY , RdBuf , 128 );	
		len = sizeof(struct TRADECOUNTER);
		//2.���ݵ��뵽�ṹ����
		memcpy(( unsigned char xdata * )&TradeCounter ,RdBuf, len);
	    //3.������CRCУ��
		crc = CrcCheck(RdBuf,len);
		//Trace("\r\n defaultsys=%d,%x,%x",num,crc/256,crc%256);
		//4.�ṹ���д��ԭ�ȶ����У��ֵ
		RdBuf[len] = HUINT16(crc);
		RdBuf[len+1] = LUINT16(crc);

		//����������ҳ����������ҳ
		MovSramToFlash( ADDRF_TRADECOUNTER , RdBuf , 128 ); 
	}
	
	/*	
	TradeCounter.TrueCurrencySum 	= (RdBuf[num++]<<24)|(RdBuf[num++]<<16)|(RdBuf[num++]<<8)|(RdBuf[num++]);
	TradeCounter.CoinSum = (RdBuf[num++]<<24)|(RdBuf[num++]<<16)|(RdBuf[num++]<<8)|(RdBuf[num++]);
	TradeCounter.CashSum = (RdBuf[num++]<<24)|(RdBuf[num++]<<16)|(RdBuf[num++]<<8)|(RdBuf[num++]);
	TradeCounter.CashSumBack = (RdBuf[num++]<<24)|(RdBuf[num++]<<16)|(RdBuf[num++]<<8)|(RdBuf[num++]);
	TradeCounter.CoinSum5j = (RdBuf[num++]<<24)|(RdBuf[num++]<<16)|(RdBuf[num++]<<8)|(RdBuf[num++]);
	TradeCounter.CoinSum5jBack = (RdBuf[num++]<<24)|(RdBuf[num++]<<16)|(RdBuf[num++]<<8)|(RdBuf[num++]);
	TradeCounter.CoinSum1y = (RdBuf[num++]<<24)|(RdBuf[num++]<<16)|(RdBuf[num++]<<8)|(RdBuf[num++]);
	TradeCounter.CoinSum1yBack = (RdBuf[num++]<<24)|(RdBuf[num++]<<16)|(RdBuf[num++]<<8)|(RdBuf[num++]);
	TradeCounter.Hopper1Sum = (RdBuf[num++]<<24)|(RdBuf[num++]<<16)|(RdBuf[num++]<<8)|(RdBuf[num++]);
	TradeCounter.Hopper1SumBack = (RdBuf[num++]<<24)|(RdBuf[num++]<<16)|(RdBuf[num++]<<8)|(RdBuf[num++]);
	TradeCounter.Hopper2Sum = (RdBuf[num++]<<24)|(RdBuf[num++]<<16)|(RdBuf[num++]<<8)|(RdBuf[num++]);
	TradeCounter.Hopper2SumBack = (RdBuf[num++]<<24)|(RdBuf[num++]<<16)|(RdBuf[num++]<<8)|(RdBuf[num++]);
	TradeCounter.TotalSellNum = (RdBuf[num++]<<24)|(RdBuf[num++]<<16)|(RdBuf[num++]<<8)|(RdBuf[num++]);
	TradeCounter.TotalSellMoeny = (RdBuf[num++]<<24)|(RdBuf[num++]<<16)|(RdBuf[num++]<<8)|(RdBuf[num++]);
	TradeCounter.vpSuccessNum = (RdBuf[num++]<<24)|(RdBuf[num++]<<16)|(RdBuf[num++]<<8)|(RdBuf[num++]);
	TradeCounter.vpSuccessMoney = (RdBuf[num++]<<24)|(RdBuf[num++]<<16)|(RdBuf[num++]<<8)|(RdBuf[num++]);
	TradeCounter.vpCashNum = (RdBuf[num++]<<24)|(RdBuf[num++]<<16)|(RdBuf[num++]<<8)|(RdBuf[num++]);
	TradeCounter.vpCashMoney = (RdBuf[num++]<<24)|(RdBuf[num++]<<16)|(RdBuf[num++]<<8)|(RdBuf[num++]);
	TradeCounter.vpGameNum = (RdBuf[num++]<<24)|(RdBuf[num++]<<16)|(RdBuf[num++]<<8)|(RdBuf[num++]);
	TradeCounter.vpCardNum = (RdBuf[num++]<<24)|(RdBuf[num++]<<16)|(RdBuf[num++]<<8)|(RdBuf[num++]);
	TradeCounter.vpOnlineNum = (RdBuf[num++]<<24)|(RdBuf[num++]<<16)|(RdBuf[num++]<<8)|(RdBuf[num++]);
	*/
}


/*��Flash��װ������*/
void   LoadGlobalParam()
{
	u_char xdata i = 0;		
	
	memset( &SystemParameter, 0, sizeof( SystemParameter ) );
	memset( GoodsWaySetVal, 0, sizeof( GoodsWaySetVal ) );
	memset( &TradeCounter, 0, sizeof(struct TRADECOUNTER) ); 
	//memset( TradeLog, 0, sizeof(struct TRADELOG) * GOODSWAYNUM ); 	
	memset( iRackSet, 0, sizeof(struct RackSet) * RACKNUM ); 	
	memset( iRackColumnSet, 0, sizeof(struct RackColumnSet) * RACKNUM * RACKCOLUMNNUM );
    //memset( &sysGoodsMatrix, 0, sizeof( sysGoodsMatrix ) );

	//����ϵͳ����
	MovFlashToSram( ADDRF_SYSTEMPARAM , ( unsigned char xdata * )&SystemParameter , sizeof(struct SYSTEMPARAMETER) );	
	MovFlashToSram( ADDRF_GOODSWAYS_SET , ( unsigned char xdata * )GoodsWaySetVal , sizeof( GoodsWaySetVal ) );	
	//���׼�¼
	//MovFlashToSram( ADDRF_TRADECOUNTER , ( unsigned char xdata * )&TradeCounter , sizeof(struct TRADECOUNTER) );		
    LoadTradeParam();
	//��������LOG����
	//MovFlashToSram( ADDRF_WAYSTARDE_LOG , ( unsigned char xdata * )TradeLog , sizeof(struct TRADELOG) * GOODSWAYNUM );	
	//��������
	MovFlashToSram( ADDRF_RACK_SET , ( unsigned char xdata * )iRackSet , sizeof(struct RackSet) * RACKNUM );		
	//��������
	MovFlashToSram( ADDRF_RACK_COLUMN_SET , ( unsigned char xdata * )iRackColumnSet , sizeof(struct RackColumnSet) * RACKNUM * RACKCOLUMNNUM );	
    //Goods parameter
    ReadGoodsParSet();	

}

//д���������
void SaveGoodsSet()
{	
	MovSramToFlash( ADDRF_GOODSWAYS_SET , ( unsigned char xdata * )GoodsWaySetVal , sizeof(GoodsWaySetVal) );	
}

/*������д��Flash��*/
void   SaveGlobalParam()
{
	//����ϵͳ����	
	u_char xdata i = 0;
	u_char xdata j = 0;
	u_char xdata z = 0;
	//����ϵͳ����	
	//����ϵͳ������У��λ	
	i = sizeof( struct SYSTEMPARAMETER ) - 1;
	j = 0;
	for( z = 0; z < i; z++ )			
		j ^= (( u_char* )&SystemParameter)[z];			
	SystemParameter.Checkbyte = j;

	MovSramToFlash( ADDRF_SYSTEMPARAM , ( unsigned char xdata * )&SystemParameter , sizeof(struct SYSTEMPARAMETER) );	
}

void  SaveTradeParam()
{
	//uint8_t *tp2;
	u_char xdata Wrbuf[128]={0},RdBuf[128]={0};
	u_int xdata num=0,i=0;
	//u_char xdata str[20];
	u_int xdata len = 0;
	u_int xdata crc=0;
	/*
	tp2 = (uint8_t *) &SystemPara;//�������ݼ�¼	
	//crc = CrcCheck(tp2,sizeof(SystemPara)-2); 
	crc = CrcCheck(tp2,124);	
	SystemPara.CrcCheck[0] = crc/256;
	SystemPara.CrcCheck[1] = crc%256;
	Trace("\r\n defaultsys=%d,%x,%x",sizeof(SystemPara)-2,SystemPara.CrcCheck[0],SystemPara.CrcCheck[1]);	
	AT45DBWritePage(4090,tp2);
	*/
	//�������в���
	//MovSramToFlash( ADDRF_TRADECOUNTER , ( unsigned char xdata * )&TradeCounter , sizeof(struct TRADECOUNTER) );
	/*
	Wrbuf[num++] = (TradeCounter.TrueCurrencySum>>24)&0xff;
	Wrbuf[num++] = (TradeCounter.TrueCurrencySum>>16)&0xff;
	Wrbuf[num++] = (TradeCounter.TrueCurrencySum>>8)&0xff;
	Wrbuf[num++] = (TradeCounter.TrueCurrencySum)&0xff;
	Wrbuf[num++] = (TradeCounter.CoinSum>>24)&0xff;
	Wrbuf[num++] = (TradeCounter.CoinSum>>16)&0xff;
	Wrbuf[num++] = (TradeCounter.CoinSum>>8)&0xff;
	Wrbuf[num++] = (TradeCounter.CoinSum)&0xff;
	Wrbuf[num++] = (TradeCounter.CashSum>>24)&0xff;
	Wrbuf[num++] = (TradeCounter.CashSum>>16)&0xff;
	Wrbuf[num++] = (TradeCounter.CashSum>>8)&0xff;
	Wrbuf[num++] = (TradeCounter.CashSum)&0xff;
	Wrbuf[num++] = (TradeCounter.CashSumBack>>24)&0xff;
	Wrbuf[num++] = (TradeCounter.CashSumBack>>16)&0xff;
	Wrbuf[num++] = (TradeCounter.CashSumBack>>8)&0xff;
	Wrbuf[num++] = (TradeCounter.CashSumBack)&0xff;
	Wrbuf[num++] = (TradeCounter.CoinSum5j>>24)&0xff;
	Wrbuf[num++] = (TradeCounter.CoinSum5j>>16)&0xff;
	Wrbuf[num++] = (TradeCounter.CoinSum5j>>8)&0xff;
	Wrbuf[num++] = (TradeCounter.CoinSum5j)&0xff;
	Wrbuf[num++] = (TradeCounter.CoinSum5jBack>>24)&0xff;
	Wrbuf[num++] = (TradeCounter.CoinSum5jBack>>16)&0xff;
	Wrbuf[num++] = (TradeCounter.CoinSum5jBack>>8)&0xff;
	Wrbuf[num++] = (TradeCounter.CoinSum5jBack)&0xff;
	Wrbuf[num++] = (TradeCounter.CoinSum1y>>24)&0xff;
	Wrbuf[num++] = (TradeCounter.CoinSum1y>>16)&0xff;
	Wrbuf[num++] = (TradeCounter.CoinSum1y>>8)&0xff;
	Wrbuf[num++] = (TradeCounter.CoinSum1y)&0xff;
	Wrbuf[num++] = (TradeCounter.CoinSum1yBack>>24)&0xff;
	Wrbuf[num++] = (TradeCounter.CoinSum1yBack>>16)&0xff;
	Wrbuf[num++] = (TradeCounter.CoinSum1yBack>>8)&0xff;
	Wrbuf[num++] = (TradeCounter.CoinSum1yBack)&0xff;
	Wrbuf[num++] = (TradeCounter.Hopper1Sum>>24)&0xff;
	Wrbuf[num++] = (TradeCounter.Hopper1Sum>>16)&0xff;
	Wrbuf[num++] = (TradeCounter.Hopper1Sum>>8)&0xff;
	Wrbuf[num++] = (TradeCounter.Hopper1Sum)&0xff;
	Wrbuf[num++] = (TradeCounter.Hopper1SumBack>>24)&0xff;
	Wrbuf[num++] = (TradeCounter.Hopper1SumBack>>16)&0xff;
	Wrbuf[num++] = (TradeCounter.Hopper1SumBack>>8)&0xff;
	Wrbuf[num++] = (TradeCounter.Hopper1SumBack)&0xff;
	Wrbuf[num++] = (TradeCounter.Hopper2Sum>>24)&0xff;
	Wrbuf[num++] = (TradeCounter.Hopper2Sum>>16)&0xff;
	Wrbuf[num++] = (TradeCounter.Hopper2Sum>>8)&0xff;
	Wrbuf[num++] = (TradeCounter.Hopper2Sum)&0xff;
	Wrbuf[num++] = (TradeCounter.Hopper2SumBack>>24)&0xff;
	Wrbuf[num++] = (TradeCounter.Hopper2SumBack>>16)&0xff;
	Wrbuf[num++] = (TradeCounter.Hopper2SumBack>>8)&0xff;
	Wrbuf[num++] = (TradeCounter.Hopper2SumBack)&0xff;
	Wrbuf[num++] = (TradeCounter.TotalSellNum>>24)&0xff;
	Wrbuf[num++] = (TradeCounter.TotalSellNum>>16)&0xff;
	Wrbuf[num++] = (TradeCounter.TotalSellNum>>8)&0xff;
	Wrbuf[num++] = (TradeCounter.TotalSellNum)&0xff;
	Wrbuf[num++] = (TradeCounter.TotalSellMoeny>>24)&0xff;
	Wrbuf[num++] = (TradeCounter.TotalSellMoeny>>16)&0xff;
	Wrbuf[num++] = (TradeCounter.TotalSellMoeny>>8)&0xff;
	Wrbuf[num++] = (TradeCounter.TotalSellMoeny)&0xff;
	Wrbuf[num++] = (TradeCounter.vpSuccessNum>>24)&0xff;
	Wrbuf[num++] = (TradeCounter.vpSuccessNum>>16)&0xff;
	Wrbuf[num++] = (TradeCounter.vpSuccessNum>>8)&0xff;
	Wrbuf[num++] = (TradeCounter.vpSuccessNum)&0xff;
	Wrbuf[num++] = (TradeCounter.vpSuccessMoney>>24)&0xff;
	Wrbuf[num++] = (TradeCounter.vpSuccessMoney>>16)&0xff;
	Wrbuf[num++] = (TradeCounter.vpSuccessMoney>>8)&0xff;
	Wrbuf[num++] = (TradeCounter.vpSuccessMoney)&0xff;
	Wrbuf[num++] = (TradeCounter.vpCashNum>>24)&0xff;
	Wrbuf[num++] = (TradeCounter.vpCashNum>>16)&0xff;
	Wrbuf[num++] = (TradeCounter.vpCashNum>>8)&0xff;
	Wrbuf[num++] = (TradeCounter.vpCashNum)&0xff;	
	Wrbuf[num++] = (TradeCounter.vpCashMoney>>24)&0xff;
	Wrbuf[num++] = (TradeCounter.vpCashMoney>>16)&0xff;
	Wrbuf[num++] = (TradeCounter.vpCashMoney>>8)&0xff;
	Wrbuf[num++] = (TradeCounter.vpCashMoney)&0xff;
	Wrbuf[num++] = (TradeCounter.vpGameNum>>24)&0xff;
	Wrbuf[num++] = (TradeCounter.vpGameNum>>16)&0xff;
	Wrbuf[num++] = (TradeCounter.vpGameNum>>8)&0xff;
	Wrbuf[num++] = (TradeCounter.vpGameNum)&0xff;
	Wrbuf[num++] = (TradeCounter.vpCardNum>>24)&0xff;
	Wrbuf[num++] = (TradeCounter.vpCardNum>>16)&0xff;
	Wrbuf[num++] = (TradeCounter.vpCardNum>>8)&0xff;
	Wrbuf[num++] = (TradeCounter.vpCardNum)&0xff;	
	Wrbuf[num++] = (TradeCounter.vpOnlineNum>>24)&0xff;
	Wrbuf[num++] = (TradeCounter.vpOnlineNum>>16)&0xff;
	Wrbuf[num++] = (TradeCounter.vpOnlineNum>>8)&0xff;
	Wrbuf[num++] = (TradeCounter.vpOnlineNum)&0xff;
	*/
	for(i=0;i<5;i++)
	{
		len = sizeof(struct TRADECOUNTER);
	    //1.��ŵ�������
		memcpy(Wrbuf,( unsigned char xdata * )&TradeCounter , len);
		//2.��CRCУ��
		crc = CrcCheck(Wrbuf,len);	
		Wrbuf[len] = HUINT16(crc);
		Wrbuf[len+1] = LUINT16(crc);
		//len = sprintf( str, "%x,%x", Wrbuf[len],Wrbuf[len+1]);
		//DisplayStr( 0, 0, 1, str, len );
		//len = sprintf( str, "%u,%u,%u,%u,%u,%u,%u,%u-%u,%u", Wrbuf[8],Wrbuf[9],Wrbuf[10],Wrbuf[11],Wrbuf[12],Wrbuf[13],Wrbuf[14],Wrbuf[15],Wrbuf[126],Wrbuf[127]);
		//DisplayStr( 0, 1, 1, str, len );
		//WaitForWork( 5000, NULL );
		//3.���浽��ҳ��
		MovSramToFlash( ADDRF_TRADECOUNTER , Wrbuf , 128 ); 
		//4.���浽����ҳ��
		MovSramToFlash( ADDRF_TRADECOUNTERCOPY , Wrbuf , 128 ); 
		DelayMs(5);
		//5.��������,Ȼ�������ж�,���д��ɹ������˳��������ظ�д5��
		MovFlashToSram( ADDRF_TRADECOUNTER , RdBuf , 128 );	
		
		//len = sprintf( str, "%x,%x", RdBuf[len],RdBuf[len+1]);
		//DisplayStr( 0, 1, 1, str, len );
		//len = sprintf( str, "%u,%u,%u,%u,%u,%u,%u,%u-%u,%u", RdBuf[8],RdBuf[9],RdBuf[10],RdBuf[11],RdBuf[12],RdBuf[13],RdBuf[14],RdBuf[15],RdBuf[126],RdBuf[127]);
		//DisplayStr( 0, 1, 1, str, len );
		//WaitForWork( 5000, NULL );
		if(memcmp(Wrbuf,RdBuf,128)==0)//���
		{
			//len = sprintf( str, "deng=%u,%x,%x-%x,%x", i,Wrbuf[len],Wrbuf[len+1],RdBuf[len],RdBuf[len+1] );
			//DisplayStr( 0, 0, 1, str, len );
			//WaitForWork( 2000, NULL );
			break;
		}
		else
		{
			//len = sprintf( str, "budeng=%u,%x,%x-%x,%x", i,Wrbuf[len],Wrbuf[len+1],RdBuf[len],RdBuf[len+1] );
			//DisplayStr( 0, 0, 1, str, len );
			//WaitForWork( 2000, NULL );
		}
		
	}	
}


//д����LOG
void SaveTradeCounter()
{
	//��������LOG����
	//MovSramToFlash( ADDRF_WAYSTARDE_LOG , ( unsigned char xdata * )TradeLog , sizeof(struct TRADELOG) * GOODSWAYNUM );		
}

//��������
void SaveRackSet()
{
	//��������
	MovSramToFlash( ADDRF_RACK_SET , ( unsigned char xdata * )iRackSet , sizeof(struct RackSet) * RACKNUM );		
}

//��������
void SaveRackColumnSet()
{
	//��������
	MovSramToFlash( ADDRF_RACK_COLUMN_SET , ( unsigned char xdata * )iRackColumnSet , sizeof(struct RackColumnSet) * RACKNUM * RACKCOLUMNNUM );		
}

//Save the goods parameter
void SaveGoodsParSet( void )
{
	//MovSramToFlash( ADDRF_GOODSPAR_SET, ( unsigned char xdata * )&sysGoodsMatrix, sizeof( sysGoodsMatrix ) );	
}

void ReadGoodsParSet( void )
{
    // MovFlashToSram( ADDRF_GOODSPAR_SET, ( unsigned char xdata * )&sysGoodsMatrix, sizeof( sysGoodsMatrix ) );
}
