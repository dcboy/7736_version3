#define  GOODS_WAY_C
#include "device.h"
#include "global.h"
#include "scheduler.h"
#include "CommonFunction.h"
#include "STRING.h"
#include "GoodsWaySet.h"
#include "key.h"
#include "common.h"
#include "mainflow.h"
#include "CommonFunction.h"
//#include "AllMenuStr.h"
//#include "language.h"
#include "debug.h"
#include "VMC_PC.h"

#undef _DEBUG_TRACE
/***********************************/

#ifdef _CHINA_
	const struct StrAndLen code GoodsWaystr[] =
	{	
		{ "1.�������: ", 12 },
        { "2.��Ʒ����: ", 12 },
        { "3.��Ʒ���: ", 12 },
		{ "4.����: ", 8 },
		{ "5.����״̬: ", 12 },
	    
	};
#else
	const struct StrAndLen code GoodsWaystr[] =
	{	
		{ "1.Column code:", 14 },
        { "2.Goods remain:", 15 },
		{ "3.Price:", 8 },
		{ "4.Column status:", 16 },
	    { "5.Goods code:", 13},
	};
#endif

u_char xdata  m_SetArrayNo = 0;
u_char xdata  GoodsSetSave = 0;
u_char xdata  goodsTypeSave = 0;


/***********************************/
//��\д�ڴ��еĻ������ò���,Num,ѡ�еĲ˵�����,len�ַ�������,OutInFlagΪ0ʱ�Ƕ�,Ϊ1ʱ��д
void ReadWriteGoodsParam( u_char Num,u_char xdata *OutStr,u_char xdata *InStr ,u_char xdata *len, bit OutInFlag )
{	
	u_char  xdata  Templen = 0;	
	u_char	xdata  i = 0;
	uint	xdata  temp = 0;	
    u_char  xdata  oldNum = 0;
	u_int   xdata  oldPrice = 0;

	switch( Num )
	{
		case 0:	//�������	
			if( OutInFlag == 0 )
			{
				//*len = 2;
				//*len = sprintf( OutStr, "%02bu", GoodsWaySetVal[m_SetArrayNo].WayNo );
				/*
				if( m_SetArrayNo == 0 )
				{
					*len = sprintf( OutStr, "%02bu", 11 );	
				}
				else
				{
                	*len = sprintf( OutStr, "%02bu", GoodsWaySetVal[m_SetArrayNo].WayNo );	
				}
				*/
				*len = sprintf( OutStr, "%02bu", InputGoodsWayList[m_SetArrayNo].GoodsWayNo );
				
			}			
		break;
        case 1://��Ʒ�ִ���				
			if(  OutInFlag == 0 )
			{					
				*len = sprintf( OutStr, "%3bu", GoodsWaySetVal[m_SetArrayNo].GoodsCurrentSum );												
			}			
			else//����
			{
				Templen = *len;
				if( Templen == 0 )
					break;
				if( Templen > 3 )
					Templen = 3;
	            oldNum = GoodsWaySetVal[m_SetArrayNo].GoodsCurrentSum;
				GoodsWaySetVal[m_SetArrayNo].GoodsCurrentSum = 0;	
				for( i = 0; i < Templen; i ++ )
				{					
					if( ( *( InStr + i ) >= 0 ) && ( *( InStr + i ) <= 9 ) )
						GoodsWaySetVal[m_SetArrayNo].GoodsCurrentSum = 
								GoodsWaySetVal[m_SetArrayNo].GoodsCurrentSum * 10 + *( InStr + i );					
				}
				GoodsWaySetVal[m_SetArrayNo].GoodsCurrentSum = (GoodsWaySetVal[m_SetArrayNo].GoodsCurrentSum>63)?63:(GoodsWaySetVal[m_SetArrayNo].GoodsCurrentSum);
				if( GoodsWaySetVal[m_SetArrayNo].GoodsCurrentSum == 0 )	Templen = 3;
				GoodsSetSave = 1;
				//------------------------------------------------------------------------------------------
                if( ( GoodsWaySetVal[m_SetArrayNo].GoodsCurrentSum != oldNum )&&(sysVPMission.offLineFlag == 0) )
				{
					VPAddSingleColGoods( m_SetArrayNo, GoodsWaySetVal[m_SetArrayNo].GoodsCurrentSum, oldNum, 1 );
				}
				//==========================================================================================
			}						
		break;
		//------------------------------------------------------------
		//Good code edit
		case 2:  				
			if(  OutInFlag == 0 )
			{					
				sprintf( OutStr, "%2bu", GoodsWaySetVal[m_SetArrayNo].GoodsType );	//3bu, 2, 			
				*len = 2;								
			}	
			/*
			else //����
			{
				Templen = *len;
				if( Templen == 0 )
					break;
				if( Templen > 2 )  //3,2
					Templen = 2;	
				GoodsWaySetVal[m_SetArrayNo].GoodsType = 0;	
				for( i = 0; i < Templen; i ++ )
				{					
					if( ( *( InStr + i ) >= 0 ) && ( *( InStr + i ) <= 9 ) )
						GoodsWaySetVal[m_SetArrayNo].GoodsType = 
								GoodsWaySetVal[m_SetArrayNo].GoodsType * 10 + *( InStr + i );					
				}
				if( GoodsWaySetVal[m_SetArrayNo].GoodsType == 0 )								
					Templen = 2;  //3,2
				GoodsSetSave = 1;
				goodsTypeSave = 1;
			}	
			*/					
		break;
		case 3://����
			////////////////////
			if( OutInFlag == 0 )
			{
				switch( SystemParameter.curUnit )
				{
					case 1:
						*len = sprintf( OutStr, "%u", GoodsWaySetVal[m_SetArrayNo].Price );
					break;				
					case 10:
						*len = sprintf( OutStr, "%u.%u", GoodsWaySetVal[m_SetArrayNo].Price/SystemParameter.curUnit, GoodsWaySetVal[m_SetArrayNo].Price%SystemParameter.curUnit );
					break;
					case 100:
						*len = sprintf( OutStr, "%u.%02u", GoodsWaySetVal[m_SetArrayNo].Price/SystemParameter.curUnit, GoodsWaySetVal[m_SetArrayNo].Price%SystemParameter.curUnit );
					break;					
				}
			}
			/*
			else
			{
				Templen = *len;
				if( Templen == 0 )
					break;
				if( Templen > 5 )
					Templen = 5;
				oldPrice = GoodsWaySetVal[m_SetArrayNo].Price;
				GoodsWaySetVal[m_SetArrayNo].Price = 0;
				for( i = 0; i < Templen; i ++ )
				{					
					if( ( *( InStr + i ) >= 0 ) && ( *( InStr + i ) <= 9 ) )
						GoodsWaySetVal[m_SetArrayNo].Price = GoodsWaySetVal[m_SetArrayNo].Price * 10 + *( InStr + i );					
				}	
				GoodsSetSave = 1;
			    //------------------------------------------------------------------------------------------
                if( GoodsWaySetVal[m_SetArrayNo].Price != oldPrice )
				{
					VPChangeColPrice( m_SetArrayNo, GoodsWaySetVal[m_SetArrayNo].Price, oldPrice );
				}
				//==========================================================================================
			}
			*/			
		break;		
		case 4:// ����״̬ �޸Ļ���״̬��ѯ;by gzz 20120323
			if(  OutInFlag == 0 )
			{				
				Templen = 1;
				/*
				if( GoodsWaySetVal[m_SetArrayNo].GoodsCurrentSum == 0 )
					Templen = 3;
				i = ( GoodsWaySetVal[m_SetArrayNo].WayState & 0x0f );				
				if( ( i & 0x01 ) != 0x01 )
					Templen = 0;				
				else if( ( i & 0x02 ) == 0x02 )
					Templen = 2;
				else if( ( i & 0x04 ) == 0x04 )
					Templen = 3;
				else if( ( i & 0x08 ) == 0x08 )
					Templen = 4;		
				*/
				if(( GoodsWaySetVal[m_SetArrayNo].WayState & 0x01 )!= 0x01)
				{
				    //δ
				    Templen = 0;
				}
				else if( GoodsWaySetVal[m_SetArrayNo].WayState & 0x0A )
				{
				    //��
				    Templen = 2;
				}
				else if( (GoodsWaySetVal[m_SetArrayNo].WayState & 0x04) || (GoodsWaySetVal[m_SetArrayNo].GoodsCurrentSum == 0) )
				{
				    //ȱ
				    Templen = 3;
				}
				else
				{
				    //��
				    Templen = 1;
				}
				sprintf( OutStr, "%bu", Templen );				
				*len = 1;				
			}			
			/*
			else//���������������;by gzz 20110926
			{
				Templen = *len;
				if( Templen == 0 )
					break;
				if( Templen > 1 )
					Templen = 1;	
				GoodsWaySetVal[m_SetArrayNo].WayState = 0x01;	
				if( *InStr == 0 )//�ֶ���Ϊ��ȷ��
				{
					GoodsWaySetVal[m_SetArrayNo].WayState = 0x00;
					GoodsWaySetVal[m_SetArrayNo].GoodsCurrentSum = 0;//by gzz 20110926
				}	
				else if( *InStr == 1 )//�ֶ���Ϊ����
					GoodsWaySetVal[m_SetArrayNo].WayState = 0x01; 
				else if( *InStr == 2 )//�ֶ���Ϊ����
				{
					GoodsWaySetVal[m_SetArrayNo].WayState = 0x03;
					GoodsWaySetVal[m_SetArrayNo].GoodsCurrentSum = 0;//by gzz 20110926
				}	
				else if( *InStr == 3 )//�ֶ���Ϊ�޻�
				{
					GoodsWaySetVal[m_SetArrayNo].WayState = 0x05;

					//�޸Ĵ������
					oldNum = GoodsWaySetVal[m_SetArrayNo].GoodsCurrentSum;
					GoodsWaySetVal[m_SetArrayNo].GoodsCurrentSum = 0;//by gzz 20110926
					if( GoodsWaySetVal[m_SetArrayNo].GoodsCurrentSum != oldNum )
					{
						VPAddSingleColGoods( m_SetArrayNo, GoodsWaySetVal[m_SetArrayNo].GoodsCurrentSum, oldNum, 1 );
					}
				}
				else if( *InStr == 4 )//�ֶ���Ϊ�廵
					GoodsWaySetVal[m_SetArrayNo].WayState = 0x09;
				else
					GoodsWaySetVal[m_SetArrayNo].WayState = *InStr;				
				GoodsSetSave = 1;
                //-------------------------
				VPMission_ColumnSta_RPT();//by gzz 20120223
				//=========================
			}	
			*/
		break;		
		default: break;			
	}
}

/***********************************/
/*yΪ�к�,NumΪ�˵������,flagΪ�Ƿ���ʾֵ*/
void  DisplayGoodsMenuAndVal( u_char line, u_char Num, bit flag )
{
	u_char  xdata y_displaystr[22];	
	u_char  xdata  len ;
    u_char  xdata dispVal[10];
	u_char  xdata i=0;
    u_char  xdata j=0;

	len = 0;	
	memset( y_displaystr,0,sizeof( y_displaystr ) );
	if( Num != 3 )
	{				
		{
		 	memcpy( y_displaystr, GoodsWaystr[Num].str, GoodsWaystr[Num].len );
		}
		if( flag == 1 )
		{		
			
		    //ReadWriteGoodsParam( Num, y_displaystr + GoodsWaystr[Num].len  , 0, &len, 0 );//�õ��˵���Ӧ��ֵ
			
			//-----------------------------------------------			
		    //�õ��˵���Ӧ��ֵ;by gzz 20110505
			//ReadWriteGoodsParam( Num, dispVal, 0, &len, 0 );
			//strcat(y_displaystr,dispVal);

            //�õ��˵���Ӧ��ֵ;by gzz 20110611            
			ReadWriteGoodsParam( Num, dispVal, 0, &len, 0 );
			j = GoodsWaystr[Num].len;
			while(i<len)
		       y_displaystr[j++]=dispVal[i++];
		    y_displaystr[j]='\0';            
			//===============================================
        }	
        //y_displaystr[GoodsWaystr[Num].len + len ] = '\0';//20110611		
		DisplayStr( 0, line, 1, y_displaystr, GoodsWaystr[Num].len + len  );//��ʾ�˵�		
	}
	else
	{		
		//Trace( "\n GPRS MenuStr" );
		if( flag == 0 )//�༭����˵�
		{	
			DisplayStr( 0, 0, 1, GoodsWaystr[Num].str, GoodsWaystr[Num].len );//��ʾ�˵�			
		}
		else//��ʾ����˵�
		{
			memcpy( y_displaystr, GoodsWaystr[Num].str, GoodsWaystr[Num].len );//�˵���ת��Ϊunicode��	
			//ReadWriteGoodsParam( Num, y_displaystr + GoodsWaystr[Num].len, 0, &len, 0 );//�õ��˵���Ӧ��ֵ

			//----------------------------------------------------------------------------------------------	
			//�õ��˵���Ӧ��ֵ;by gzz 20110505
			//ReadWriteGoodsParam( Num, dispVal, 0, &len, 0 );            
			//strcat(y_displaystr,dispVal);

			//�õ��˵���Ӧ��ֵ;by gzz 20110611
            ReadWriteGoodsParam( Num, dispVal, 0, &len, 0 );
			j = GoodsWaystr[Num].len;
			while(i<len)
		       y_displaystr[j++]=dispVal[i++];
		    y_displaystr[j]='\0';           
			//==============================================================================================
            //y_displaystr[GoodsWaystr[Num].len + len ] = '\0';//20110611
			DisplayStr( 0, line, 1,  y_displaystr, GoodsWaystr[Num].len + len );//��ʾ�˵�						
		}
	}
    //Trace( "\n edit SysParamMenu Num= %bd", Num );
	//Trace( "display one SysParanMenu and val end\n" );
}	

unsigned char Led_Good( u_char ledMode )//�����Ʒ��Ӧ�ĵ��Ƿ���1��,0��
{
	u_char xdata i = 0;
	sysVPMission.sel1ReadyLed = 0x00;
    sysVPMission.sel1ErrLed   = 0x00;
    sysVPMission.sel2ReadyLed = 0x00;
    sysVPMission.sel2ErrLed   = 0x00;
    sysVPMission.sel3ReadyLed = 0x00;
    sysVPMission.sel3ErrLed   = 0x00;
	
	if(ledMode == 1)
	{
		for( i=0; i<KEYEXTRAVAL; i++ )
	    {
	    	if(GoodsWaySetVal[m_SetArrayNo].GoodsType == SystemParameter.selItem[i])
	    	{
	    		sysVPMission.sel1ReadyLed |= 1<<i;
	    	}
		}
		for( i=KEYEXTRAVAL; i<KEYEXTRAVAL*2; i++ )
	    {
			if(GoodsWaySetVal[m_SetArrayNo].GoodsType == SystemParameter.selItem[i])
	        {
	        	sysVPMission.sel2ReadyLed |= 1<<(i-KEYEXTRAVAL);
	        }	        
	    }
		for( i=KEYEXTRAVAL*2; i<KEYEXTRAVAL*3; i++ )
	    {
			if(GoodsWaySetVal[m_SetArrayNo].GoodsType == SystemParameter.selItem[i])
	        {
	        	sysVPMission.sel3ReadyLed |= 1<<(i-KEYEXTRAVAL*2);
	        }	        
	    }
	}
	GetKey_M2();
	return 0;
}


/***********************************/
/*�༭ѡ����,NumΪѡ�еĲ˵����,lineΪ�༭�к�*/
bit  EditGoodsParam( u_char Num, u_char line )
{
	u_char  xdata Inputstr[10];
	u_char  xdata  key;
	u_char  xdata  Inputlen;

	//Led_Good(1);
	key = 0;	
	Inputlen = 5;
	memset( Inputstr, 0, sizeof( Inputstr ) );
	if( Num == 2 )   //1,2(2010.12.30)
		key = GetLineMoney( GoodsWaystr[Num].str, GoodsWaystr[Num].len, line, Inputstr, &Inputlen );
	else
		key = GetLine( GoodsWaystr[Num].str, GoodsWaystr[Num].len, line, Inputstr, &Inputlen );			
	ClearKey();		
	if( key == 1 )//Enter	
	{		
		DisplayCursorState( 0, 0, 0, 0, 1 );		
		//Trace( "selected Enter \n" );			
		ReadWriteGoodsParam( Num, 0, Inputstr ,&Inputlen, 1 );		
		ClearKey();		
	}		
	//Trace( "edit one SysParanMenu end\n" );
	//Led_Good(0);
	return 0;
}

/************************************/
/*����ڲ˵����ƶ���ѡ��,SelectedNum��ǰ������ڵĲ˵����,
	CursorLine����ǰ��������ǵ���,ֵΪ1��2,MoveRange,�˵������ķ�Χ
*/
void  Goods_MenuSelected( u_char xdata *SelectedNum, u_char xdata *CursorLine, u_char MoveRange )
{
	u_char xdata  MenuNum = *SelectedNum;
	u_char xdata  Cursor = *CursorLine;
	bit	   data  flag = 1;
	u_char xdata  key = 0xff;
	u_char  xdata  len = 0;	

	while( flag )
	{
		key = GetKey();
		switch( key )		
		{
			case KEY_CANCEL:
				flag = 0;
				*SelectedNum = 100;				
				break;
			case KEY_UP://����  				
				if( Cursor == 2 )//ѡ�б������
				{			
					DisplayCursorState( 0, 0, 1, 2, 1 );//��һ�������					
					Cursor = 1;
					if( MenuNum == 0 )
						MenuNum = MoveRange;					
					else									    
						MenuNum--;					
				}
				else//�˵��Ϸ�
				{						
					DisplayGoodsMenuAndVal( 1, MenuNum, 1 );					
					if( MenuNum == 0 )
						MenuNum = MoveRange;					
					else									    
						MenuNum--;					
					DisplayGoodsMenuAndVal( 0, MenuNum , 1 );																					
					Cursor = 1;						
				}
				break;
			case KEY_DOWN://����						
				if( Cursor == 1 )//ѡ�б������
				{
					DisplayCursorState( 0, 1, 1, 2, 1 );//�ڶ��������
					if( MenuNum == MoveRange )
						MenuNum = 0;					
					else									    						
						MenuNum++;				     
					Cursor = 2;						
				}
				else//�˵��·�
				{					
					DisplayGoodsMenuAndVal( 0, MenuNum, 1 );						
					if( MenuNum == MoveRange )
						MenuNum = 0;					
					else									    
						MenuNum++;					
					DisplayGoodsMenuAndVal( 1, MenuNum , 1 );																					
					Cursor = 2;
				}
				break;
			case KEY_SUBMIT://Enter,ѡ����ĳ��˵�
				{			
					*SelectedNum = MenuNum;
					*CursorLine = Cursor;					
					flag = 0;	
				}
				break;	
			case KEY_4://��һ������	
				if(m_SetArrayNo==0)
				{
				    m_SetArrayNo = (GOODSWAYNUM-1);
				}
				else
				{
					m_SetArrayNo--;
				}
				while(InputGoodsWayList[m_SetArrayNo].UseState == 0)
				{
				    m_SetArrayNo--;
				}	
				
				if( Cursor == 1 )
				{
					DisplayGoodsMenuAndVal( 0, MenuNum, 1 );				
					if( MenuNum == MoveRange )
						DisplayGoodsMenuAndVal( 1, 0, 1 );					
					else										
						DisplayGoodsMenuAndVal( 1, MenuNum+1, 1 );	
				}
				else
				{						
					DisplayGoodsMenuAndVal( 1, MenuNum, 1 );					
					if( MenuNum == 0 )
						DisplayGoodsMenuAndVal( 0, MoveRange, 1 );
					else									    
						DisplayGoodsMenuAndVal( 0, MenuNum-1, 1 );					
				}
				break;
			case KEY_3://��һ������	
				do
				{
				    m_SetArrayNo++;
				}
				while( (InputGoodsWayList[m_SetArrayNo].UseState == 0)&&(m_SetArrayNo < GOODSWAYNUM) );
				if(m_SetArrayNo>=GOODSWAYNUM)
				{
				    m_SetArrayNo = 0;
				}
				if( Cursor == 1 )
				{
					DisplayGoodsMenuAndVal( 0, MenuNum, 1 );				
					if( MenuNum == MoveRange )
						DisplayGoodsMenuAndVal( 1, 0, 1 );					
					else										
						DisplayGoodsMenuAndVal( 1, MenuNum+1, 1 );	
				}
				else
				{						
					DisplayGoodsMenuAndVal( 1, MenuNum, 1 );					
					if( MenuNum == 0 )
						DisplayGoodsMenuAndVal( 0, MoveRange, 1 );
					else									    
						DisplayGoodsMenuAndVal( 0, MenuNum-1, 1 );					
				}	
				break;	
		}
		CoreProcessCycle();//�ó�ʱ��Ƭ
		DelayMs( 5 );
		if(sysVPMission.msActTimer == 0)
		{
			sysVPMission.msActTimer = 100;
			VPMission_Act_RPT(VP_ACT_ADMIN,VP_ACT_ENTERADMIN);
		}
	}
	ClearKey();		
}

/***********************************/
////////////////
bit GoodsParamManage()		
{
	u_char  xdata fristNum ;//һ���˵����
	u_char  xdata LineNum ;//ѡ����Ļ���к�	
	u_char  xdata key = 0;
	u_char xdata  i = 0;
	
	ClearKey();	
	//GoodsSetSave = 0;   //Disabled by Andy on 2011.6.8
	//����������
	m_SetArrayNo = 0;
    //m_SetArrayNo = InputGoodsWayNo( );
	/////////////////////////////////////////
	while( 1 )
	{		
		ClearKey();	
		//����������
		m_SetArrayNo = 0;
		m_SetArrayNo = InputGoodsWayNo( 1 );
		if( ( m_SetArrayNo == 100 ) || ( m_SetArrayNo == 99 ) )
			return 0;	
		Trace("\n input m_SetArrayNo = %bu", m_SetArrayNo );	
		DisplayGoodsMenuAndVal( 0, 0, 1 );	
		DisplayGoodsMenuAndVal( 1, 1, 1 );		
		DisplayCursorState( 0, 1, 1, 2, 1 );//���ù���ڵڶ�������Ϊ���й��״̬
		fristNum = 1;
		LineNum = 2;
		Led_Good(1);
		WaitForWork( 300, NULL );
		while( 1 )
		{		
			/*�жϰ��ºμ�*/			
			Goods_MenuSelected( &fristNum, &LineNum, MENU_COUNT( GoodsWaystr ) - 1 );			
			//ѡ����ĳ��˵�				
			if( fristNum == 100 )//ѡ���˳�									
				break;		
			else if( fristNum != 1 )//û��ѡ���˳�
				continue;
			else
			{				
				ClearKey();									
				EditGoodsParam( fristNum, LineNum - 1 );			
				//������ʾ���������ֵ			
				if( LineNum == 2 )
				{			
					if( fristNum == 0 )
						DisplayGoodsMenuAndVal( 0, MENU_COUNT( GoodsWaystr ) - 1, 1 );
					else						
						DisplayGoodsMenuAndVal( 0, fristNum-1, 1 );						
					DisplayGoodsMenuAndVal( 1, fristNum, 1 );	
				}
				else
				{									
					if( fristNum == ( MENU_COUNT( GoodsWaystr ) - 1 ) )
						DisplayGoodsMenuAndVal( 1, 0, 1 );	
					else						
						DisplayGoodsMenuAndVal( 1, fristNum + 1, 1 );	
					DisplayGoodsMenuAndVal( 0, fristNum, 1 );
				}			
				DisplayCursorState( 0, LineNum - 1, 1, 2, 1 );//���ù��Ϊ����״̬			
			}					
		}
		Led_Good(0);		
	}	
	return 0;
}
/////////////////

/*bit AddSalveGoods()
{
	u_char  xdata  i = 0;
    u_char  xdata  y_displaystr[22];	
    u_char  xdata  key;
    u_char  xdata  Inputstr[10];
    u_char  xdata  Inputlen = 2;
	u_char  xdata  CurrentSum;
	
		
	/////////////////////////////////////////
	while( 1 )
	{		
		ClearKey();	
		//����������
		m_SetArrayNo = 0;
		m_SetArrayNo = InputGoodsWayNo( 1 );
		if( ( m_SetArrayNo == 100 ) || ( m_SetArrayNo == 99 ) )
			return 0;	
		//Trace("\n input m_SetArrayNo = %bu", m_SetArrayNo );	
		
		ClearDisplayLine( 1 );
		ClearDisplayLine( 2 );
        Inputlen = 2;	
	    //sprintf(y_displaystr,"����%02bu������", GoodsWaySetVal[m_SetArrayNo].WayNo);
        sprintf(y_displaystr,"����%02bu������", InputGoodsWayList[m_SetArrayNo].GoodsWayNo);
        key = GetLine( y_displaystr, 12, 0, Inputstr, &Inputlen );
        WaitForWork( 500, NULL );
        ClearKey();	
        if( key == 1 )//Enter.
        {	
	    	DisplayCursorState( 0, 0, 0, 0, 1 );		
            CurrentSum = 0;
            for( i = 0; i < Inputlen; i ++ )
			{					
				if( ( *( Inputstr + i ) >= 0 ) && ( *( Inputstr + i ) <= 9 ) )
					CurrentSum = CurrentSum * 10 + *( Inputstr + i );					
			}			
			//------------------------------------------------------------------------------------------
            if( CurrentSum != 0 )
			{
				VPAddSingleColGoods( m_SetArrayNo, CurrentSum, 0, 2 );
                //sprintf(y_displaystr,"����������%02bu", CurrentSum);
                //DisplayStr( 0, 0, 1, y_displaystr, 14 );
				//WaitForWork( 2000, NULL );
			} 			
        }
	}
	return 0;	
}
*/
