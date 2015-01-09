#define RACK_SET_C
#include "device.h"
#include "global.h"
#include "scheduler.h"
#include "CommonFunction.h"
#include "STRING.h"
#include "RackSet.h"
#include "key.h"
#include "common.h"
#include "mainflow.h"
#include "CommonFunction.h"
//#include "AllMenuStr.h"
//#include "language.h"
#include "debug.h"

#undef _DEBUG_TRACE
/***********************************/
#ifdef _CHINA_
	const struct StrAndLen code RackParastr[] =
	{	
		{ "1.��ܱ��:", 11 },
		{ "2.�Ƿ�����:", 11 },
		{ "3.�������:", 13 },
		{ "4.��һ����:", 11 },
		{ "5.�ڶ�����:", 11 },
		{ "6.��\xc8\xfd����:", 11 },
		{ "7.���Ļ���:", 11 },
		{ "8.�������:", 11 },
		{ "9.��������:", 11 },
		{ "10. ���߻���:", 13 },
		{ "11. �ڰ˻���:", 13 },								
	};
#else
	const struct StrAndLen code RackParastr[] =
	{	
		{ "1.Tray code:", 12 },
		{ "2.Enabled:", 10 },
		{ "3.Goods Max.:", 13 },
		{ "4.Column 1:", 11 },
		{ "5.Column 2:", 11 },
		{ "6.Column 3:", 11 },
		{ "7.Column 4:", 11 },
		{ "8.Column 5:", 11 },
		{ "9.Column 6:", 11 },
		{ "10.Column 7:", 12 },
		{ "11.Column 8:", 12 },								
	};
#endif


#ifdef _CHINA_
	const struct StrAndLen code CSTR_Rack[] = 
	{	
		{ "����������:", 11 },
		{ "�������!", 9 }
	};
#else
	const struct StrAndLen code CSTR_Rack[] = 
	{	
		{ "Input password:", 15 },
		{ "Password error!", 15 }
	};
#endif


const code RackInputLen[] = { 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1 };
u_char xdata RackNo = 1;
u_char xdata IsModify = 0;
/***********************************/
//��\д�ڴ��еĲ�����ò���,Num,ѡ�еĲ˵�����,len�ַ�������,OutInFlagΪ0ʱ�Ƕ�,Ϊ1ʱ��д
void ReadWriteRactParam( u_char Num,u_char xdata *OutStr,u_char xdata *InStr ,u_char xdata *len, bit OutInFlag )
{	
	u_char  xdata Templen = 0;	
	u_char	xdata  i = 0;
	uint	xdata temp = 0;	

	switch( Num )
	{
		case 0:	//��ܱ��	
			if( OutInFlag == 0 )
			{				
				sprintf( OutStr, "%bu", iRackSet[RackNo - 1].RackNo );//GoodsWayNoList[m_SetArrayNo].GoodsWayNo)				
				*len = 2;
			}			
		break;
		case 1://���ñ�־
			////////////////////
			if( OutInFlag == 0 )
			{
				*len = sprintf( OutStr, "%bu", iRackSet[RackNo - 1].UseState );				
			}
			else
			{
				Templen = *len;
				if( Templen == 0 )
					break;
				if( Templen > 1 )
					Templen = 1;
				iRackSet[RackNo - 1].UseState = 0;
				for( i = 0; i < Templen; i ++ )
				{					
					if( ( *( InStr + i ) >= 0 ) && ( *( InStr + i ) <= 9 ) )
						iRackSet[RackNo - 1].UseState = *( InStr + i );					
				}					
			}			
		break;
		case 2://����Ʒ����				
			if(  OutInFlag == 0 )							
				*len = sprintf( OutStr, "%bu", iRackSet[RackNo - 1].GoodsMax );						
			else//����
			{
				Templen = *len;
				if( Templen == 0 )
					break;
				if( Templen > 2 )
					Templen = 2;	
				iRackSet[RackNo - 1].GoodsMax = 0;	
				for( i = 0; i < Templen; i ++ )
				{					
					if( ( *( InStr + i ) >= 0 ) && ( *( InStr + i ) <= 9 ) )
						iRackSet[RackNo - 1].GoodsMax = iRackSet[RackNo - 1].GoodsMax*10 + *( InStr + i );					
				}				
			}						
		break;	
		case 3:// ����1����״̬
			if(  OutInFlag == 0 )							
				*len = sprintf( OutStr, "%bu", iRackColumnSet[RackNo - 1][0].UseState );			
			else//����
			{
				Templen = *len;
				if( Templen == 0 )
					break;
				if( Templen > 1 )
					Templen = 1;	
				iRackColumnSet[RackNo - 1][0].UseState = 0;	
				for( i = 0; i < Templen; i ++ )
				{					
					if( ( *( InStr + i ) >= 0 ) && ( *( InStr + i ) <= 9 ) )
						iRackColumnSet[RackNo - 1][0].UseState = *( InStr + i );					
				}			
			}			
		break;	
		case 4:// ����2����״̬
			if(  OutInFlag == 0 )							
				*len = sprintf( OutStr, "%bu", iRackColumnSet[RackNo - 1][1].UseState );			
			else//����
			{
				Templen = *len;
				if( Templen == 0 )
					break;
				if( Templen > 1 )
					Templen = 1;	
				iRackColumnSet[RackNo - 1][1].UseState = 0;	
				for( i = 0; i < Templen; i ++ )
				{					
					if( ( *( InStr + i ) >= 0 ) && ( *( InStr + i ) <= 9 ) )
						iRackColumnSet[RackNo - 1][1].UseState = *( InStr + i );					
				}			
			}			
		break;	
		case 5:// ����3����״̬
			if(  OutInFlag == 0 )							
				*len = sprintf( OutStr, "%bu", iRackColumnSet[RackNo - 1][2].UseState );			
			else//����
			{
				Templen = *len;
				if( Templen == 0 )
					break;
				if( Templen > 1 )
					Templen = 1;	
				iRackColumnSet[RackNo - 1][2].UseState = 0;	
				for( i = 0; i < Templen; i ++ )
				{					
					if( ( *( InStr + i ) >= 0 ) && ( *( InStr + i ) <= 9 ) )
						iRackColumnSet[RackNo - 1][2].UseState = *( InStr + i );					
				}			
			}			
		break;
		case 6:// ����4����״̬
			if(  OutInFlag == 0 )							
				*len = sprintf( OutStr, "%bu", iRackColumnSet[RackNo - 1][3].UseState );			
			else//����
			{
				Templen = *len;
				if( Templen == 0 )
					break;
				if( Templen > 1 )
					Templen = 1;	
				iRackColumnSet[RackNo - 1][3].UseState = 0;	
				for( i = 0; i < Templen; i ++ )
				{					
					if( ( *( InStr + i ) >= 0 ) && ( *( InStr + i ) <= 9 ) )
						iRackColumnSet[RackNo - 1][3].UseState = *( InStr + i );					
				}			
			}			
		break;
		case 7:// ����5����״̬
			if(  OutInFlag == 0 )							
				*len = sprintf( OutStr, "%bu", iRackColumnSet[RackNo - 1][4].UseState );			
			else//����
			{
				Templen = *len;
				if( Templen == 0 )
					break;
				if( Templen > 1 )
					Templen = 1;	
				iRackColumnSet[RackNo - 1][4].UseState = 0;	
				for( i = 0; i < Templen; i ++ )
				{					
					if( ( *( InStr + i ) >= 0 ) && ( *( InStr + i ) <= 9 ) )
						iRackColumnSet[RackNo - 1][4].UseState = *( InStr + i );					
				}			
			}			
		break;
		case 8:// ����6����״̬
			if(  OutInFlag == 0 )							
				*len = sprintf( OutStr, "%bu", iRackColumnSet[RackNo - 1][5].UseState );			
			else//����
			{
				Templen = *len;
				if( Templen == 0 )
					break;
				if( Templen > 1 )
					Templen = 1;	
				iRackColumnSet[RackNo - 1][5].UseState = 0;	
				for( i = 0; i < Templen; i ++ )
				{					
					if( ( *( InStr + i ) >= 0 ) && ( *( InStr + i ) <= 9 ) )
						iRackColumnSet[RackNo - 1][5].UseState = *( InStr + i );					
				}			
			}			
		break;
		case 9:// ����7����״̬
			if(  OutInFlag == 0 )							
				*len = sprintf( OutStr, "%bu", iRackColumnSet[RackNo - 1][6].UseState );			
			else//����
			{
				Templen = *len;
				if( Templen == 0 )
					break;
				if( Templen > 1 )
					Templen = 1;	
				iRackColumnSet[RackNo - 1][6].UseState = 0;	
				for( i = 0; i < Templen; i ++ )
				{					
					if( ( *( InStr + i ) >= 0 ) && ( *( InStr + i ) <= 9 ) )
						iRackColumnSet[RackNo - 1][6].UseState = *( InStr + i );					
				}			
			}			
		break;
		case 10:// ����8����״̬
			if(  OutInFlag == 0 )							
				*len = sprintf( OutStr, "%bu", iRackColumnSet[RackNo - 1][7].UseState );			
			else//����
			{
				Templen = *len;
				if( Templen == 0 )
					break;
				if( Templen > 1 )
					Templen = 1;	
				iRackColumnSet[RackNo - 1][7].UseState = 0;	
				for( i = 0; i < Templen; i ++ )
				{					
					if( ( *( InStr + i ) >= 0 ) && ( *( InStr + i ) <= 9 ) )
						iRackColumnSet[RackNo - 1][7].UseState = *( InStr + i );					
				}			
			}			
		break;
	}
}

/***********************************/
/*yΪ�к�,NumΪ�˵������,flagΪ�Ƿ���ʾֵ*/
void  DisplayRackMenuAndVal( u_char line, u_char Num, bit flag )
{
	u_char  xdata y_displaystr[22];	
	u_char   xdata  len ;

    if( flag == 0 ) flag = 0;

	len = 0;	
	memset( y_displaystr,0,sizeof( y_displaystr ) );	
 	memcpy( y_displaystr, RackParastr[Num].str, RackParastr[Num].len );					
	ReadWriteRactParam( Num, y_displaystr + RackParastr[Num].len  , 0, &len, 0 );//�õ��˵���Ӧ��ֵ			
	DisplayStr( 0, line, 1, y_displaystr, RackParastr[Num].len + len  );//��ʾ�˵�			
}	

/***********************************/
/*�༭ѡ����,NumΪѡ�еĲ˵����,lineΪ�༭�к�*/
bit  EditRackParam( u_char Num, u_char line )
{
	u_char  xdata Inputstr[10];
	u_char  xdata  key;
	u_char  xdata  Inputlen;
	
	key = 0;	
	Inputlen = RackInputLen[Num];
	memset( Inputstr, 0, sizeof( Inputstr ) );	
	key = GetLine( RackParastr[Num].str, RackParastr[Num].len, line, Inputstr, &Inputlen );			
	ClearKey();		
	if( key == 1 )//Enter	
	{		
		DisplayCursorState( 0, 0, 0, 0, 1 );		
		//Trace( "selected Enter \n" );			
		ReadWriteRactParam( Num, 0, Inputstr ,&Inputlen, 1 );	
		IsModify = 1;	
		ClearKey();		
	}		
	//Trace( "edit one SysParanMenu end\n" );
	return 0;
}

/************************************/
/*����ڲ˵����ƶ���ѡ��,SelectedNum��ǰ������ڵĲ˵����,
	CursorLine����ǰ��������ǵ���,ֵΪ1��2,MoveRange,�˵������ķ�Χ
*/
void  Rack_MenuSelected( u_char xdata *SelectedNum, u_char xdata *CursorLine, u_char MoveRange )
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
					DisplayRackMenuAndVal( 1, MenuNum, 1 );					
					if( MenuNum == 0 )
						MenuNum = MoveRange;					
					else									    
						MenuNum--;					
					DisplayRackMenuAndVal( 0, MenuNum , 1 );																					
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
					DisplayRackMenuAndVal( 0, MenuNum, 1 );						
					if( MenuNum == MoveRange )
						MenuNum = 0;					
					else									    
						MenuNum++;					
					DisplayRackMenuAndVal( 1, MenuNum , 1 );																					
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
		}
		CoreProcessCycle();//�ó�ʱ��Ƭ
		DelayMs( 5 );
	}
	ClearKey();		
}

/***********************************/
////////////////
bit RackParamManage()		
{
	u_char  xdata fristNum ;//һ���˵����
	u_char  xdata LineNum ;//ѡ����Ļ���к�	
	u_char  xdata key = 0;
	u_char xdata  i = 0;
	u_char xdata Tempstr[8];
	u_char xdata len = 0;	
	struct PassWordLog xdata TempPassWd;
	u_char  xdata password[9];
    u_char xdata ErrFlag = 0;

	ClearKey();		
	//����������
	RackNo = 0;
	IsModify = 0;

    //------------------------------------------------------------------------------------
	//Check the password firstly
	memset( &TempPassWd, 0, sizeof(struct PassWordLog) );
	{
    	TempPassWd.passwdlen = 8;
		TempPassWd.checkbyte = 0;
		TempPassWd.PassWordByte[0] = 8;
        TempPassWd.PassWordByte[1] = 3;
		TempPassWd.PassWordByte[2] = 7;
		TempPassWd.PassWordByte[3] = 1;
        TempPassWd.PassWordByte[4] = 8;
        TempPassWd.PassWordByte[5] = 5;
		TempPassWd.PassWordByte[6] = 5;
		TempPassWd.PassWordByte[7] = 7;
		for( i=0; i<8; i++ )
		{
			TempPassWd.checkbyte += TempPassWd.PassWordByte[i];
 	    }
    }
	DisplayStr( 0, 0, 1, "   ", 3 );
	DisplayStr( 0, 1, 1, " ", 1 );
	while( 1 )
	{		
		WaitForWork( 100, NULL );
		memset(password , 0 , sizeof(password));
		key = 8;
		ErrFlag = GetLine_1(CSTR_Rack[ 0 ].str , CSTR_Rack[ 0 ].len, 0, password , &key, 1 );		
		ClearKey();	
		if(ErrFlag == 0)       //��ʱ��cancel
		{
			DisplayCursorState( 0, 0, 0, 0, 1 );//�޹��				
			return 0;	
		}
		ErrFlag = 0;	
		if( key == TempPassWd.passwdlen )		
			ErrFlag = memcmp( TempPassWd.PassWordByte, password, TempPassWd.passwdlen );
		else
			ErrFlag = 1;
		
		//�������,�˳�
		if( ErrFlag != 0 )      
		{				
			DisplayCursorState( 0, 0, 0, 0, 1 );     //�޹��		
			DisplayStr( 0, 0, 1, CSTR_Rack[ 1 ].str, CSTR_Rack[ 1 ].len );
			DisplayStr( 0, 1, 1, "    ", 4 );				
			WaitForWork( 2000, NULL );				
		}
		else
			break;
	}
	//=====================================================================================

	while( 1 )
	{		
		ClearKey();	
		//����������
		RackNo = 0;
		//////////////////////////		
		while( 1 )
		{		
			ClearDisplayLine( 1 );
			ClearDisplayLine( 2 );		
			len = 1;
			memset( Tempstr,0, sizeof( Tempstr ) );	
		 #ifdef _CHINA_
		 	key = GetLine( "�����ܱ��:", 13 , 0, Tempstr, &len );
		 #else
			key = GetLine( "Input Tray code:", 16 , 0, Tempstr, &len );
		 #endif
			WaitForWork( 500, NULL );	
			ClearKey();				
			if( key == 1 )//Enter	
			{			
				DisplayCursorState( 0, 0, 0, 0, 1 );			
				for( i = 0; i < len; i ++ )
				{
					if( ( Tempstr[i] >= 0 ) && ( Tempstr[i] <= 9 ) )
					{
						RackNo = Tempstr[i];				
						break;
					}
				}				
				ClearKey();	
					
				if( ( RackNo <= 0 ) || ( RackNo > RACKNUM ))
		 	    {
					#ifdef _CHINA_
						DisplayStr( 0, 0, 1, "����������", 12 );
						DisplayStr( 0, 1, 1, "�������������", 14 );
					#else
						DisplayStr( 0, 0, 1, "Input code error", 16 );
						DisplayStr( 0, 1, 1, "Input other code", 16 );				
					#endif									
					WaitForWork( 2000, NULL );
					continue;
				}
				else
					break;
			}
			else
			{
				Trace( "\n IsModify = %bu", IsModify );
				if( IsModify == 0 )
					return 0;
				////���������ɣ����úŵ�����
				LineNum = 0;//�ܵĿ���������
				RackNo = 0;//��������
				//memset( InputGoodsWayList, 0, sizeof( InputGoodsWayList )*GOODSWAYNUM ); //Disabled by Andy 2011.3.2
                memset( InputGoodsWayList, 0, sizeof( InputGoodsWayList ) );
				for( i = 0; i < RACKNUM; i++ )//���ܲ���
				{
					if( iRackSet[ i ].UseState == 1 )//����˲㿪����
					{
						key = iRackSet[ i ].GoodsMax;//�˲��и������������
						fristNum = 1;//���߻�����ŵĸ�λ	
						for( len = 0; len < RACKCOLUMNNUM; len ++ )//����ÿ���п����Ļ�����
						{
							Trace("\n iRackColumnSet[ %bu ][ %bu ].UseState = %bu", i, len, iRackColumnSet[i][len].UseState  );
							if( iRackColumnSet[i][len].UseState == 1)
							{
								InputGoodsWayList[ LineNum ].GoodsWayNo = ( RackNo + 1 ) * 10 + fristNum;//�߼�����  
								Trace("\n InputGoodsWayList[ %bu ].GoodsWayNo = %bu", LineNum, InputGoodsWayList[ LineNum ].GoodsWayNo);
							//	InputGoodsWayList[ LineNum ].SetArrayNo = i*RACKCOLUMNNUM + len + 1 ;//�������
								InputGoodsWayList[ LineNum ].SetArrayNo = 64 - i*RACKCOLUMNNUM - 8 + len + 1;//�������
								Trace("\n InputGoodsWayList[ %bu ].SetArrayNo = %bu", LineNum, InputGoodsWayList[ LineNum ].SetArrayNo);
								InputGoodsWayList[ LineNum ].UseState = 1;//����״̬
								Trace("\n InputGoodsWayList[ %bu ].UseState = %bu", LineNum, InputGoodsWayList[ LineNum ].UseState);
								InputGoodsWayList[ LineNum ].GoodsMax = key;//�������
								Trace("\n InputGoodsWayList[ %bu ].GoodsMax = %bu", LineNum, InputGoodsWayList[ LineNum ].GoodsMax);
								LineNum += 1;								
								fristNum += 1;
							}							
						}
						RackNo += 1;
					}
					else
					{
						iRackSet[i].GoodsMax = 0;
						memset( iRackColumnSet[i], 0, 16 );
					}
				}
				memset( GoodsWaySetVal, 0, sizeof( struct WaySet ) * GOODSWAYNUM );
				Trace("\n EnableNum = %bu", LineNum);
				for( i = 0; i < LineNum; i ++ )
			    {
					GoodsWaySetVal[i].WayNo = InputGoodsWayList[ i ].GoodsWayNo;
					Trace("\n GoodsWaySetVal[ %bu ].WayNo = %bu", i, GoodsWaySetVal[ i ].WayNo);
					GoodsWaySetVal[i].WayState = 0;					
					GoodsWaySetVal[i].GoodsCurrentSum = 0;
                    //-----------------------------------------------
                    //GoodsWaySetVal[i].Price = 0;
                    GoodsWaySetVal[i].Price = SystemParameter.curUnit;
                    //===============================================
				}
				//����������úͻ�����������
				SaveGoodsSet();
				SaveRackSet();
				SaveRackColumnSet();
				return 0;
			}
		}
		//////////////////////////		
		DisplayRackMenuAndVal( 0, 0, 1 );	
		DisplayRackMenuAndVal( 1, 1, 1 );		
		DisplayCursorState( 0, 1, 1, 2, 1 );//���ù���ڵڶ�������Ϊ���й��״̬
		fristNum = 1;
		LineNum = 2;
		WaitForWork( 300, NULL );
		while( 1 )
		{		
			/*�жϰ��ºμ�*/			
			Rack_MenuSelected( &fristNum, &LineNum, MENU_COUNT( RackParastr ) - 1 );			
			//ѡ����ĳ��˵�				
			if( fristNum == 100 )//ѡ���˳�									
				break;		
			else if( fristNum == 0 )//û��ѡ���˳�
				continue;
			else
			{				
				ClearKey();	
				if( iRackSet[RackNo - 1].UseState == 1 )
					EditRackParam( fristNum, LineNum - 1 );	
				else if( fristNum == 1 ) 
					EditRackParam( fristNum, LineNum - 1 );			
				//������ʾ���������ֵ			
				if( LineNum == 2 )
				{			
					if( fristNum == 0 )
						DisplayRackMenuAndVal( 0, MENU_COUNT( RackParastr ) - 1, 1 );
					else						
						DisplayRackMenuAndVal( 0, fristNum-1, 1 );						
					DisplayRackMenuAndVal( 1, fristNum, 1 );	
				}
				else
				{									
					if( fristNum == ( MENU_COUNT( RackParastr ) - 1 ) )
						DisplayRackMenuAndVal( 1, 0, 1 );	
					else						
						DisplayRackMenuAndVal( 1, fristNum + 1, 1 );	
					DisplayRackMenuAndVal( 0, fristNum, 1 );
				}			
				DisplayCursorState( 0, LineNum - 1, 1, 2, 1 );//���ù��Ϊ����״̬			
			}					
		}
	}
	return 0;
}
