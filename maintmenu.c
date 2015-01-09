#include "device.h"	
//#include <stdio.h>
//#include <stdlib.h>
#include <string.h>
#include "global.h"
#include "mainflow.h"
#include "maintmenu.h"
#include "scheduler.h"
#include "CommonFunction.h"
#include "SysParamSet.h"
#include "devicecheck.h"
#include "key.h"  
#include "IOInput.h"
#include "Clock.h"
#include "timer.h" 
#include "common.h"
#include "DataExchange.h"  
#include "debug.h"
#include "initialization.h"
#include "GoodsWaySet.h"
#include "countermaint.h"
#include "RackSet.h"
#include "VMC_PC.h"


//#include "Mobile.h"
//#include "communication.h"

#ifdef _CHINA_
	const struct StrAndLen  code MainMenuStr[] =    
	{	 
		/*
        { "1.������\xca\xfd", 10 },
        { "2.����״̬���ٲ�ѯ", 18 },
		{ "3.����ȫ������",   14 },
        { "4.��Ӳ�����",     12},
        { "5.ȫϵͳͬ��",     12 },
        { "6.������ܻ���",   14 },
        { "7.ȡֽ�����",     12},	        
		{ "8.�豸����",       12 },
		{ "9.ϵͳ��\xca\xfd", 12 },		
		{ "10. ��������", 12 },
        { "11. ����Ĭ������", 16 },
        { "12. �ӻ����", 12 },
        { "13. �������", 12 },
		{ "14. ���׼�¼", 12   },
		{ "15. �����ۼ�", 12   },//120521 by cq SellAccumulate
		{ "16. �������", 12   }
		*/
		{ "1.������ͳ��", 12   },
		{ "2.������\xca\xfd", 10 },
        { "3.����״̬�鿴", 14 },
		{ "4.����ȫ������",   14 },
        { "5.��Ӳ�����",     12},
        { "6.ȫϵͳͬ��",     12 },
        { "7.������ܻ���",   14 },
        { "8.ȡֽ�����",     12},	        
		{ "9.�豸����",       10 },
		{ "10. ϵͳ��\xca\xfd", 12 },		
		{ "11. ��������", 12 },
        { "12. ����Ĭ������", 16 },  
        { "13. ������������ͳ��", 20   },
		{ "14. ����ǩ��", 12   }
		
        
	};
#else
	const struct StrAndLen  code MainMenuStr[] =    
	{
	/*
		{ "1.Column", 8 },
		{ "2.Add full goods", 16 },
        { "3.Add layer goods", 17 },
        { "4.Add changes", 13 },
        { "5.Add Cash", 10 },
		{ "6.Goods-Column", 14 },
        { "7.Count 0.50$ coin", 18 },
		{ "8.Count 1.00$ coin", 18 },
		{ "9.Device", 8 },
		{ "10.Parameter", 11 },
		{ "11.Record inquiry", 16 },
		{ "12.Tray", 6 },
        { "13.Default setting", 18 },
        { "14.Add Slave Goods", 18 },
	*/
	    { "1.Column", 8 },
        { "2.goods status", 14}
		{ "3.Add full goods", 16 },
        { "4.Add coin", 10 },		
		{ "5.Goods-Column", 14 },
        { "6.Add layer goods", 17 },        
        { "7.Add Cash", 10 },
        /*		
        { "8.Count 0.50$ coin", 18 },
		{ "9.Count 1.00$ coin", 18 },
        */
		{ "8.Device", 8 },
		{ "9.Parameter", 11 },
		{ "10.Tray", 6 },
        { "11.Default setting", 18 },
        { "12.Add slave Goods", 18 },
		{ "13.Column test", 13 }
     
	};
#endif



//�����������ú���
u_char FactorySetting( void )
{
    u_char xdata i = 0;
	u_char xdata j = 0;
	u_char xdata key = 0;
    u_char xdata flag = 0;
	u_char xdata ret = 0;
	//u_char xdata str[20];
	u_char xdata len = 0;
    
	u_char xdata fristNum ;
	u_char xdata columnNum = 0;   
    u_char xdata trayNum = 0;
   	

	//uchar LineNum;
    //1.
#ifdef _CHINA_
	DisplayStr( 0, 0, 1, "  ȷ������������?", 17 );   
	DisplayStr( 0, 1, 1, "ȷ��ENTER ȡ��CANCEL", 20 );	
#else		
	DisplayStr( 0, 0, 1, "   Are you sure?", 16 );  
	DisplayStr( 0, 1, 1, "   ENTER   CANCEL", 17 );	
#endif
    while( 1 )
	{
		key = GetKey();
		if( ( key == KEY_CANCEL ) || (key == KEY_SUBMIT) )
			break;
		WaitForWork( 100, NULL );	
		if(sysVPMission.msActTimer == 0)
		{
			sysVPMission.msActTimer = 100;
			VPMission_Act_RPT(VP_ACT_ADMIN,VP_ACT_ENTERADMIN);
		}
	}
	if( key == KEY_CANCEL ) return 0;

    //2.System parameter set
	memset( &SystemParameter, 0, sizeof( SystemParameter ) );
    SystemParameter.HopperCoinPrice1 = 50;
	SystemParameter.HopperCoinPrice2 = 100;
	SystemParameter.HopperCoinPrice3 = 0;
	SystemParameter.IsMuliVerd = 1;        //0,1
	SystemParameter.RefundPermission = 1;
	SystemParameter.BillNo = 1;
	SystemParameter.MobileON = 0;
	SystemParameter.Min = 100;
	SystemParameter.BanknoteMax = 2000;
	SystemParameter.DoubtCash = 0;
	//memset( SystemParameter.VmID, 0, sizeof( SystemParameter.VmID ) );
	//memset( SystemParameter.GSMNO, 0, sizeof( SystemParameter.GSMNO ) );
    memcpy( SystemParameter.GSMNO, "0", 1 );
	SystemParameter.NotOutMax = 0;
	SystemParameter.decimal = 2; 
	SystemParameter.curUnit = 100;
    SystemParameter.billValue[0] = 100;
    SystemParameter.billValue[1] = 500;
	SystemParameter.billValue[2] = 1000;
	SystemParameter.billValue[3] = 2000;
	SystemParameter.billValue[4] = 0;
	SystemParameter.billValue[5] = 0;
	SystemParameter.billValue[6] = 0;
	SystemParameter.billValue[7] = 0;
	SystemParameter.coinValue[0] = 50;
	SystemParameter.coinValue[1] = 100;
	SystemParameter.coinValue[2] = 0;
	SystemParameter.coinValue[3] = 0;
	SystemParameter.coinValue[4] = 0;
	SystemParameter.coinValue[5] = 0;
	SystemParameter.GOCOn = 0;
	SystemParameter.tradeTime = 5;
    SystemParameter.SVC_NoChange = 0;
	SystemParameter.coinOn = 1;
	SystemParameter.busCardOn = 0;     //1,0
	SystemParameter.BCReadTime = 2;
    //SystemParameter.holdingMode  = 1;  //open by default
    //SystemParameter.holdNoteFive = 0;  //add by gzz 20110429
    //SystemParameter.holdNoteTen  = 1;  //add by gzz 20110429
    SystemParameter.ACDCModule   = 1;  //open by default 
    SystemParameter.CompModule = 1;

    //дϵͳ����
	SaveGlobalParam();	
    //3.Column set
	for( i=0; i<RACKNUM; i++ )
	{
		iRackSet[i].RackNo = i+1;
		iRackSet[i].UseState = 0;
        iRackSet[i].GoodsMax = 0;
		for( j=0; j<RACKNUM; j++ )
		{
			iRackColumnSet[i][j].UseState = 0;
		}

	}
    for( i=0; i<6; i++ )
	{
    	//iRackSet[i].RackNo = i+1;
    	iRackSet[i].UseState = 1;
		iRackSet[i].GoodsMax = 10;
        for( j=0; j<RACKNUM; j++ )
		{
			iRackColumnSet[i][j].UseState = 1;
		}
    }

    //���������ɣ����úŵ�����
	columnNum = 0; //�ܵĿ���������
	trayNum = 0;  //��������
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
					InputGoodsWayList[ columnNum ].GoodsWayNo = ( trayNum + 1 ) * 10 + fristNum;//�߼�����  
					Trace("\n InputGoodsWayList[ %bu ].GoodsWayNo = %bu", LineNum, InputGoodsWayList[ LineNum ].GoodsWayNo);
				//	InputGoodsWayList[ LineNum ].SetArrayNo = i*RACKCOLUMNNUM + len + 1 ;//�������
					InputGoodsWayList[ columnNum ].SetArrayNo = 64 - i*RACKCOLUMNNUM - 8 + len + 1;//�������
					Trace("\n InputGoodsWayList[ %bu ].SetArrayNo = %bu", LineNum, InputGoodsWayList[ LineNum ].SetArrayNo);
					InputGoodsWayList[ columnNum ].UseState = 1;//����״̬
					Trace("\n InputGoodsWayList[ %bu ].UseState = %bu", LineNum, InputGoodsWayList[ LineNum ].UseState);
					InputGoodsWayList[ columnNum ].GoodsMax = key;//�������
					Trace("\n InputGoodsWayList[ %bu ].GoodsMax = %bu", columnNum, InputGoodsWayList[ LineNum ].GoodsMax);
					columnNum += 1;								
					fristNum += 1;
				}							
			}
			trayNum += 1;
		}
		else
		{
			iRackSet[i].GoodsMax = 0;
			memset( iRackColumnSet[i], 0, 16 );
		}
	}
	//memset( GoodsWaySetVal, 0, sizeof( struct WaySet ) * GOODSWAYNUM );
	memset( GoodsWaySetVal, 0, sizeof( GoodsWaySetVal ) );
	Trace("\n EnableNum = %bu", LineNum);
	for( i = 0; i < columnNum; i ++ )
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
	WaitForWork( 100, NULL );
    //4.
    //�ָ�Ĭ�ϲ��������׼�¼�������;by gzz 20110721
	//memset( &TradeCounter, 0, sizeof( struct TRADECOUNTER ) );			    
    //memset( DoubtTradeLog, 0, sizeof( DoubtTradeLog ) );
	/*
	memset( TradeLog, 0, sizeof( TradeLog ) );	
	for( key = 0; key < GOODSWAYNUM; key++ )
	{				
		TradeLog[key].WayNo = InputGoodsWayList[key].GoodsWayNo;
    }
	*/
    /*	
    memset( &Temptime, 0, sizeof( struct time ) );
	GetCurrentTime( &Temptime );
	TradeCounter.Date[0] = ( Temptime.year & 0xff00 ) >> 8;
	TradeCounter.Date[1] = ( Temptime.year & 0x00ff );
	TradeCounter.Date[2] = Temptime.mon;
	TradeCounter.Date[3] = Temptime.date;			
	SgwSecTimer = 0;
	*/
	SaveTradeParam();
	SaveTradeCounter();
	WaitForWork( 100, NULL );
	return 0;

}



void mainmenu()
{
	u_char  xdata firstNum ;//һ���˵����
	u_char  xdata LineNum ;//ѡ����Ļ���к�	
	u_char  xdata i = 0;
	bit	data Notout = 1;
	u_char xdata ErrFlag = 0;
	u_char xdata key = 0;
	struct WaySet  xdata TempGoodsWaySetVal[GOODSWAYNUM];
	struct SYSTEMPARAMETER xdata TempSystemParameter;	
	//u_char xdata str[20];
    //struct SHORTMSG xdata message;

	ErrFlag = 0;
	while( ErrFlag == 0 )
	{
		ErrFlag = 0;
		Notout = 1;
		//sysVPMission.sWeihuTimer=20;
		ClearKey();	
		/*��ʾ���в˵�����ֵ*/
		DisplayStr( 0, 0, 1, MainMenuStr[0].str, MainMenuStr[0].len );//��ʾ�˵�	
		DisplayStr( 0, 1, 1, MainMenuStr[1].str, MainMenuStr[1].len );//��ʾ�˵�				
		DisplayCursorState( 0, 1, 1, 2, 1 );//���ù���ڵڶ�������Ϊ���й��״̬
		firstNum = 1;
		LineNum = 2;	
		while( Notout )    //��ʱ��ͻ��˳�
		{				
			key = GetKey();
			switch( key )		
			{
				case KEY_UP://����  	
					 //sysVPMission.sWeihuTimer=20;
				     if( LineNum == 2 )//ѡ�б������
				     {			     
				     	DisplayCursorState( 0, 0, 1, 2, 1 );//��һ�������
				     	LineNum = 1;			   
						if( firstNum == 0 )
							firstNum = MENU_COUNT(MainMenuStr)-1;					
						else
							firstNum--;
				     }
				     else//�˵��Ϸ�
				     {
				      	/*��firstNum<=1�����Ϸ���*/			      		
					//	DispDeviceMenu( firstNum, 1);									    
						DisplayStr( 0, 1, 1, MainMenuStr[firstNum].str, MainMenuStr[firstNum].len );
						if( firstNum == 0 )
							firstNum = MENU_COUNT(MainMenuStr)-1;					
						else
							firstNum--;
					//	DispDeviceMenu( firstNum, 0);						
						DisplayStr( 0, 0, 1, MainMenuStr[firstNum].str, MainMenuStr[firstNum].len );
						LineNum = 1;					
				     }
					 break;
				case KEY_DOWN://����	
					//sysVPMission.sWeihuTimer=20; 
					if( LineNum == 1 )//ѡ�б������
					{				 
					     DisplayCursorState( 0, 1, 1, 2, 1 );//�ڶ��������				   
						if( firstNum == MENU_COUNT(MainMenuStr)-1 )
							firstNum = 0;					
						else
							firstNum++;
					     LineNum = 2;				     
					 }
					 else//�˵��·�
					 {
					    /*��firstNum<=2�����Ϸ���*/				    				
						DisplayStr( 0, 0, 1, MainMenuStr[firstNum].str, MainMenuStr[firstNum].len );
				      	if( firstNum == MENU_COUNT(MainMenuStr)-1 )
							firstNum = 0;					
						else
							firstNum++;
						DisplayStr( 0, 1, 1, MainMenuStr[firstNum].str, MainMenuStr[firstNum].len );
						LineNum = 2;					
					}
					break;
				case KEY_CANCEL:
					Notout = 0;
					break;			
				case KEY_SUBMIT://Enter,ѡ����ĳ��˵�	
					//sysVPMission.sWeihuTimer=20;
					DisplayCursorState( 0, 0, 0, 0, 1 );//�ڶ��������
					ClearKey();				
					switch(firstNum)
					{	
                        case 0:
                            //���׼�¼	
                            //VPMission_ColumnSta_RPT();	
                            CounterMainMenu_1();	//Trade record
                            //sysVPMission.sWeihuTimer=20;
							break;							
						case 1:							
                            //��������
                            GoodsParamManage();	
							//sysVPMission.sWeihuTimer=20;
							break;
						case 2:
                            //���ϻ���
                            DispFaultGoodsWays();	
							//sysVPMission.sWeihuTimer=20;
							break;
						case 3:						    
						    //���ȫ������
						    VPAddAllColGoods();
							//sysVPMission.sWeihuTimer=20;
							break;
						case 4:
						    //��Ӳ��
						    VPAddChanges(1);     //Add coin
						    //sysVPMission.sWeihuTimer=20;
						    break;
                        case 5:						    
                            //ȫϵͳͬ��
                            VPSynGoodsCol();    //Add goods
                            //sysVPMission.sWeihuTimer=20;
							break;                        						
                        case 6:
						    //�����ܻ��� 
						    VPAddLayerColGoods();
							//sysVPMission.sWeihuTimer=20;
							break;						
                        //--------------------------------------------
                        /*
						case 7:
						    //VPCountCoin(1);     //Count the 0.5$ coin
						    break;                         
						case 8:
						    //VPCountCoin(2);     //Count the 1$ coin
						    break;
                        */
						//============================================
						case 7:
							//ȡֽ��
							VPAddChanges(2);     //Get cash;by gzz 20110506
							//sysVPMission.sWeihuTimer=20;
							break;					
						case 8:	
							//�豸����
							DeviceCheck();      //Device check
							//sysVPMission.sWeihuTimer=20;
							break;
                        case 9:
							//ϵͳ����
							SysParamManage();   //System parameter
							//sysVPMission.sWeihuTimer=20;
							break;	
                        case 10:
                            //�������
                            RackParamManage(); 	//Tray set
                            //sysVPMission.sWeihuTimer=20;
                            break;
                        case 11:
							//��������
							FactorySetting();
							//sysVPMission.sWeihuTimer=20;
							break;
						case 12:
							InitAllCounter_1();	//Trade record		
							//sysVPMission.sWeihuTimer=20;
							break;		
                        case 13:
							//�������
		                    VPBuhuoCol();	//Trade record
		                    //sysVPMission.sWeihuTimer=20;
							break;						
						/*case 14://120521 by cq SellAccumulate
							//CounterMainMenu_1();	//Trade record
							break;
						case 15://120521 by cq SellAccumulate
							VPBuhuoCol();	//Trade record
							break;	
							*/
                        default:
						    break;
					}
					if(LineNum ==2)
					{	
						if( firstNum == 0 )											
							DisplayStr( 0, 0, 1, MainMenuStr[MENU_COUNT(MainMenuStr)-1].str, MainMenuStr[MENU_COUNT(MainMenuStr)-1].len );
						else						
							DisplayStr( 0, 0, 1, MainMenuStr[firstNum - 1].str, MainMenuStr[firstNum - 1].len );
						DisplayStr( 0, 1, 1, MainMenuStr[firstNum].str, MainMenuStr[firstNum].len );
					}
					else
					{												
						if( firstNum == ( MENU_COUNT(MainMenuStr)-1 ) )				
							DisplayStr( 0, 1, 1, MainMenuStr[0].str, MainMenuStr[0].len );
						else						
							DisplayStr( 0, 1, 1, MainMenuStr[firstNum + 1].str, MainMenuStr[firstNum + 1].len );
						DisplayStr( 0, 0, 1, MainMenuStr[firstNum].str, MainMenuStr[firstNum].len );
					}				
					DisplayCursorState( 0, LineNum - 1, 1, 2, 1 );//�ڶ��������
					ClearKey();	
					break;
			}
			CoreProcessCycle();//�ó�ʱ��Ƭ
			DelayMs( 10 );
			if(sysVPMission.msActTimer == 0)
			{
				sysVPMission.msActTimer = 100;
				VPMission_Act_RPT(VP_ACT_ADMIN,VP_ACT_ENTERADMIN);
			}
			//�˳�ά��ҳ��
			//if(sysVPMission.sWeihuTimer==0)
			//{
			//	Notout = 0;
			//}
		}	
		WaitForWork( 300, &Lcd );
		DisplayClear();//��������		
		DisplayCursorState( 0, 0, 1, 0, 1 );//�޹��
		DisplayCursorState( 1, 0, 1, 0, 1 );//�޹��
		//////////////////
        //Trace("\n GoodsSetSave3 = %bu", GoodsSetSave );
		if( ( GoodsSetSave ) || ( SystemSave ) )
		{
		#ifdef _CHINA_
			DisplayStr( 0, 0, 1, "  \xd5\xfd�ڱ���", 10 );	
		#else
			DisplayStr( 0, 0, 1, "  Saving...", 11 );	
		#endif
			DisplayStr( 0, 1, 1, " ", 1 );
			WaitForWork( 2500, &Lcd );
		}	
		///////////
	    //Trace("\n GoodsSetSave4 = %bu", GoodsSetSave );
		if( GoodsSetSave )
		{
	        //Trace("\n GoodsSetSave5 = %bu", GoodsSetSave );
			//д��������
			SaveGoodsParSet();        //Added by Andy 2010.12.29!
			WaitForWork( 100, NULL );
			SaveGoodsSet();	
			WaitForWork( 100, NULL );
			memset( TempGoodsWaySetVal, 0, sizeof( TempGoodsWaySetVal ) );
			MovFlashToSram( ADDRF_GOODSWAYS_SET , ( unsigned char xdata * )TempGoodsWaySetVal , sizeof( TempGoodsWaySetVal ) );
		    //TempGoodsWaySetVal[2].GoodsCurrentSum = 324;
			for( i = 0; i < GOODSWAYNUM; i ++ )
			{
		        //Trace("\n GoodsWaySetVal[%bu].WayState = %bu", i ,GoodsWaySetVal[i].WayState );
		        //Trace("\n TempGoodsWaySetVal[%bu].WayState = %bu",i, TempGoodsWaySetVal[i].WayState );
				if( ( GoodsWaySetVal[i].GoodsCurrentSum != TempGoodsWaySetVal[i].GoodsCurrentSum ) || \
					( GoodsWaySetVal[i].WayState != TempGoodsWaySetVal[i].WayState ) || \
					( GoodsWaySetVal[i].Price != TempGoodsWaySetVal[i].Price ) )
					break;
			}
			if( i != GOODSWAYNUM )//����ͬ
			{
				Trace("\n GoodsWaySetVal error" );
				ErrFlag = 1;	
			}
			GoodsSetSave = 0;
		}

		if( SystemSave )
		{
			//дϵͳ����
			SaveGlobalParam();	
			WaitForWork( 100, NULL );	
			//��ⶨ��flash�е�����
			memset( &TempSystemParameter, 0, sizeof( TempSystemParameter ) );		
			//����ϵͳ����
			MovFlashToSram( ADDRF_SYSTEMPARAM , ( unsigned char xdata * )&TempSystemParameter , sizeof(struct SYSTEMPARAMETER) );	
					
			if( ( SystemParameter.RefundPermission != TempSystemParameter.RefundPermission ) || \
				( SystemParameter.HopperCoinPrice1 != TempSystemParameter.HopperCoinPrice1 ) || \
				( SystemParameter.HopperCoinPrice2 != TempSystemParameter.HopperCoinPrice2 ) || \
				( SystemParameter.HopperCoinPrice3 != TempSystemParameter.HopperCoinPrice3 ) || \
				( SystemParameter.BillNo != TempSystemParameter.BillNo ) || \
				( SystemParameter.IsMuliVerd != TempSystemParameter.IsMuliVerd ) || \
				( SystemParameter.Min != TempSystemParameter.Min ) || \
				( SystemParameter.BanknoteMax != TempSystemParameter.BanknoteMax ) || \
				( SystemParameter.NotOutMax != TempSystemParameter.NotOutMax ) || \
				( SystemParameter.Checkbyte != TempSystemParameter.Checkbyte ) )
			{
				Trace("\n SystemParameter error" );
				ErrFlag = 1;
			}
			SystemSave = 0;
		}
		if( ErrFlag )
		{
			ClearKey();	
		 #ifdef _CHINA_
			DisplayStr( 0, 0, 1, "����ʧ�ܣ���������?", 19 );	
		 #else
		 	DisplayStr( 0, 0, 1, "Save failed,reenter?", 20 );	
		 #endif			
			DisplayStr( 0, 1, 1, "  ENTER   CANCEL", 16 );
			LzjSecTimer= 15;
			i = 0;
			while( LzjSecTimer )
			{
				SchedulerProcess();
				key = GetKey();
				if ( key == KEY_NULL ) 
					continue;
				switch ( key )
			 	{			
					case KEY_SUBMIT:			
						ErrFlag = 0;
						i = 1;
						break;
					case KEY_CANCEL:				
						ErrFlag = 1 ;					
						i = 1;
						break;
					default:
						continue;
				}	
				if( i == 1 )
					break;
			}
			if( LzjSecTimer == 0 )
				ErrFlag = 0;
		}
		else
			ErrFlag = 1;
	}
	ClearKey();		
}

