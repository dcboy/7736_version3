#define SYSPARAM_C
#include "device.h"
#include "global.h"
#include "scheduler.h"
#include "CommonFunction.h"
#include "STRING.h"
#include "SysParamSet.h"
#include "key.h"
#include "common.h"
#include "mainflow.h"
#include "debug.h"
#include "VMC_PC.h"


//#undef _DEBUG_TRACE
/***********************************/
#ifdef _CHINA_
	const struct StrAndLen code SysMenustr[] =
	{	
		/*
		{ "1.#1��������ֵ:", 15 },	
		{ "2.#2��������ֵ:", 15 },		
		//{ "3.#3��������ֵ:", 15 }, //111024 by cq ɾ��
		{ "3.�����ι���:", 15 },
		{ "4.������˱�:", 13 },
		{ "5.����ֽ����:", 13 },        
		//{ "7.�����ֻ�ģ��:", 15 },	 //111024 by cq ɾ��
        { "6.�������:", 11 },
        { "7.�ձ�����:", 11 },	
        //���һ��ֽ�������ʵ��ձҽ��
		//{ "10. ���ʽ��:", 13 },//111024 by cq ɾ��
		//{ "11. �������: ", 13 },//111024 by cq ɾ��
		//{ "12.GSM����:", 11 },//111024 by cq ɾ��
		//{ "1X. Ƿ��:", 9 },//111024 by cq ɾ��
		{ "8.Ƿ��:", 7 },//111024 by cq ɾ��
		//-----------------------------------------------------
        //{ "1X. С\xca\xfd��:", 11},//111024 by cq ɾ��
		{ "9.С\xca\xfd��:", 9 },//111024 by cq ɾ��
        { "10. #1ֽ��:", 11 },
        { "11. #2ֽ��:", 11 },
        { "12. #3ֽ��:", 11 },
        { "13. #4ֽ��:", 11 },
        { "14. #5ֽ��:", 11 },
        { "15. #6ֽ��:", 11 },
        { "16. #7ֽ��:", 11 },
        { "17. #8ֽ��:", 11 },
        { "18. #1Ӳ��:", 11 },
        { "19. #2Ӳ��:", 11 },
        { "20. #3Ӳ��:", 11 },
        { "21. #4Ӳ��:", 11 },
        { "22. #5Ӳ��:", 11 },
        { "23. #6Ӳ��:", 11 },
        { "24. ��������ȷ��:", 17 },
      //{ "30. �����޳���ȷ��:", 19 },
	    { "25. ����ʱ��:", 13 },
        { "26. ������ģʽ:", 15 },
        { "27. ����Ӳ����:", 15 },
        { "28. ����������:", 15 }, 
        { "29. ����ʱ��:",   13 },
        { "30. �ݴ�ֽ��ģʽ:",   17 },
        { "31. ��Ԫֽ���ݴ�:",   17 },
        { "32. ʮԪֽ���ݴ�:",   17 },
        { "33. ����ACDCģ��:",   17 },
        { "34. ��������:",   13 },
        */
        /*
        { "1.��������:",   11 },
        { "2.�Զ��˱�:", 11 }, 
        { "3.��������ȷ��:", 15 },
        { "4.Ƿ��:", 7 },//111024 by cq ɾ�� 
		{ "5.�����ι���:", 15 },
		{ "6.������˱�:", 13 },
        { "7.�������:", 11 },
        { "8.�ձ�����:", 11 },
		{ "9.����ֽ����:", 13 },
        { "10. ����Ӳ����:", 15 },        
		{ "11. ����ACDCģ��:",   17 },	
		//-----------------------------------------------------
        { "12. С\xca\xfd��:", 11 },//111024 by cq ɾ��
        { "13. #1������ֵ:", 15 },	
		{ "14. #2������ֵ:", 15 }, 
        { "15. #1ֽ��:", 11 },
        { "16. #2ֽ��:", 11 },
        { "17. #3ֽ��:", 11 },
        { "18. #4ֽ��:", 11 },
        { "19. #5ֽ��:", 11 },
        { "20. #6ֽ��:", 11 },
        { "21. #7ֽ��:", 11 },
        { "22. #8ֽ��:", 11 },
        { "23. #1Ӳ��:", 11 },
        { "24. #2Ӳ��:", 11 },
        { "25. #3Ӳ��:", 11 },
        { "26. #4Ӳ��:", 11 },
        { "27. #5Ӳ��:", 11 },
        { "28. #6Ӳ��:", 11 },
        //{ "29. ������ģʽ:", 15 },
        //{ "30. ����������:", 15 }, 
        //{ "31. ����ʱ��:",   13 }, 
        */
        { "1.��������:",   11 },
        { "2.�Զ��˱�:", 11 }, 
        { "3.��������ȷ��:", 15 },
        { "4.Ƿ��:", 7 },//111024 by cq ɾ�� 
		{ "5.�����ι���:", 15 },
		{ "6.������˱�:", 13 },
        { "7.�������:", 11 },
        { "8.����ֽ����:", 13 },
        { "9.����Ӳ����:", 13 },        
		{ "10. ����ACDCģ��:",   17 },	
		//-----------------------------------------------------
        //{ "11. #1������ֵ:", 15 },	
		//{ "12. #2������ֵ:", 15 }, 
        { "11. #1ֽ��:", 11 },
        { "12. #2ֽ��:", 11 },
        { "13. #3ֽ��:", 11 },
        { "14. #4ֽ��:", 11 },
        { "15. #5ֽ��:", 11 },
        { "16. #6ֽ��:", 11 },
        { "17. #1Ӳ��:", 11 },
        { "18. #2Ӳ��:", 11 },
        { "19. #3Ӳ��:", 11 },
        { "20. #4Ӳ��:", 11 },
        //=====================================================
	};
#else
	const struct StrAndLen code SysMenustr[] =
	{	        
		{ "1.#1 coin type:", 15 },	
		{ "2.#2 coin type:", 15 },		
		//{ "3.#3 coin type:", 15 },   //111024 by cq ɾ��     
		{ "3.Multi-verd:", 13 },//�Ƿ������ι���		
		{ "4.Refund:", 9 },//�Ƿ����������Ǯ	
		{ "5.Bill on:", 10 },
		//{ "7.Mobile on:", 12 },
		{ "7.Change value:", 15 },	
		{ "8.Banknote-max:", 15 },	
		//�����ʵĽ��
		//{ "10.Doubtful Amt:", 16 },//111024 by cq ɾ��
		//{ "11.VM ID:", 9 },//111024 by cq ɾ��
		//{ "12.GSM No.:", 11 },//111024 by cq ɾ��				
		{ "8.IOU:", 7 },
		//-----------------------------------------------------
		{ "9.Decimal num: ", 15 },
		
        { "10.#1 Note:", 11 },
        { "11.#2 Note:", 11 },
        { "12.#3 Note:", 11 },
        { "13.#4 Note:", 11 },
        { "14.#5 Note:", 11 },
        { "15.#6 Note:", 11 },
        { "16.#7 Note:", 11 },
        { "17.#8 Note:", 11 },
        { "18.#1 Coin:", 11 },
        { "19.#2 Coin:", 11 },
        { "20.#3 Coin:", 11 },
        { "21.#4 Coin:", 11 },
        { "22.#5 Coin:", 11 },
        { "23.#6 Coin:", 11 },
		{ "24.GOC_dev on:",  14 },
	  //{ "30.SVC/GOC ERR:", 15 },
        { "25.Trade time:", 14 },
        { "26.No change mode:", 18 },        
        //=====================================================
        
	};
#endif
//const code SysInputLen[] = { 5, 5, 5, 1, 1, 1, 1, 5, 5, 5, 5, 16, 1, 1, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 1, 5, 1, 1, 1, 2, 1, 1, 1, 1 /*, 1*/ };
//							  1,,,2,,,,,,,,,,,,,3,,,4,,,5,,,,,,,,,,,,,,6,,,7,,,,,,,,,,,,,,,,,,,,,,,,8,,,9,,10,11,12,13,14,15,16,17,18,19,20,21,,22,,23,24,25,26,27,28,29,,30,31,32,33
const code SysInputLen[] = { 5, 5,/*5,*/ 1, 1, 1, /*1,*/ 5, 5,/* 5, 5, 16,*/ 5, 1, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 1, 5, 1, 1, 1, 2, 1, 1, 1, 1 /*, 1*/ };//111024 by cq ɾ��
bit  data  SystemSave = 0;//ϵͳ�Ƿ񱣴�
u_char  xdata y_displaystr[44];	//����ʾ��
//u_char  xdata y_displaystr_1[22];	//������ʾ��
//��\дȡ�ڴ��е�ϵͳ����,Num,ѡ�еĲ˵�����,len�ַ�������,OutInFlagΪ0ʱ�Ƕ�,Ϊ1ʱ��д
void ReadWriteSysParam( u_char Num,u_char xdata *OutStr,u_char xdata *InStr ,u_char xdata *len, bit OutInFlag )
{	
	u_char  xdata j = 0;	
	u_char	xdata  i;
	uint	xdata temp = 0;		
	uint	xdata tempMoney = 0;	//111129 by cq ��������	

	i = 0;
	switch( Num )
	{

		case 0:  //If open compressor module 
			if( OutInFlag == 0 )
			{				
				*len = sprintf( OutStr, "%bu", SystemParameter.CompModule );			
			}
			else
			{
				j = *len;
				if( j == 0 )
					break;
				if( j > 1 )
					j = 1;
                //SystemParameter.ACDCModule = 0;
				for( i = 0; i < j; i ++ )
				{
					//111024 by cq ɾ��
					//if( ( *( InStr + i ) >= 0 ) && ( *( InStr + i ) <= 9 ) )
					if( ( *( InStr + i ) >= 0 ) && ( *( InStr + i ) <= 1 ) )
					{
						SystemParameter.CompModule = *( InStr + i );
						break;
					}
				}
				//111024 by cq ɾ��
				//if( SystemParameter.ACDCModule != 1 )
					//SystemParameter.ACDCModule = 0;	
				SystemSave = 1;
			}
		break;
		case 1:   //Trade time
			if( OutInFlag == 0 )
			{	
			    *len = sprintf( OutStr, "%u", SystemParameter.tradeTime );
			}
			else
			{
				j = *len;
				if( j==0 ) break;
				if( j>5 )  j = 5;
				SystemParameter.tradeTime = 0;
				for( i = 0; i < j; i ++ )
				{
					if( ( *( InStr + i ) >= 0 ) && ( *( InStr + i ) <= 9 ) )					
						SystemParameter.tradeTime = SystemParameter.tradeTime*10 + *( InStr + i );					
				}
				if(SystemParameter.tradeTime >= 255)
				{
					SystemParameter.tradeTime = 255;					
				}				
				SystemSave = 1;
			}			
		break;
		case 2:  //GOC device on
			if( OutInFlag == 0 )
			{				
				sprintf( OutStr, "%bu", SystemParameter.GOCOn );			
				*len = 1;
			}
			else
			{
				j = *len;
				if( j == 0 )
					break;
				if( j > 1 )
					j = 1;
				for( i = 0; i < j; i ++ )
				{
					//111024 by cq ɾ��
					//if( ( *( InStr + i ) >= 0 ) && ( *( InStr + i ) <= 9 ) )
					if( ( *( InStr + i ) >= 0 ) && ( *( InStr + i ) <= 1 ) )
					{
						SystemParameter.GOCOn = *( InStr + i );
						break;
					}
				}
				
				//if( SystemParameter.GOCOn != 1 )
					//SystemParameter.GOCOn = 0;	
				SystemSave = 1;
			}
		break;
		case 3://Ƿ�ͻ���Ǯ
			if( OutInFlag == 0 )
			{				
				//����������ж������������ʾ������������;
                //�����Ƿ���ʾǷ����;by gzz 20110810	
                if(SystemParameter.MuchOutFlag==1)
                {
                 	switch( SystemParameter.curUnit )
					{
						case 1:
							*len = sprintf( OutStr, "-%u", SystemParameter.NotOutMax );
						break;				
						case 10:
							*len = sprintf( OutStr, "-%u.%u", SystemParameter.NotOutMax/SystemParameter.curUnit,SystemParameter.NotOutMax%SystemParameter.curUnit);
						break;
						case 100:
							*len = sprintf( OutStr, "-%u.%02u", SystemParameter.NotOutMax/SystemParameter.curUnit,SystemParameter.NotOutMax%SystemParameter.curUnit);
						break;					
					}
                }	
                else if(SystemParameter.MuchOutFlag==0)
                {
					switch( SystemParameter.curUnit )
					{
						case 1:
							*len = sprintf( OutStr, "%u", SystemParameter.NotOutMax );
						break;				
						case 10:
							*len = sprintf( OutStr, "%u.%u", SystemParameter.NotOutMax/SystemParameter.curUnit,SystemParameter.NotOutMax%SystemParameter.curUnit);
						break;
						case 100:
							*len = sprintf( OutStr, "%u.%02u", SystemParameter.NotOutMax/SystemParameter.curUnit,SystemParameter.NotOutMax%SystemParameter.curUnit);
						break;					
					}
                }
			}
			else
			{
				j = *len;
				if( j == 0 )
					break;
				if( j > 1 )
					j = 1;			
				if( *( InStr ) == 0 ) 					
					SystemParameter.NotOutMax = 0;				
				SystemSave = 1;
			}			
		break;
		case 4://�����ι���	
			if( OutInFlag == 0 )
			{				
				sprintf( OutStr, "%bu", SystemParameter.IsMuliVerd );			
				*len = 1;
			}
			else
			{
				j = *len;
				if( j == 0 )
					break;
				if( j > 1 )
					j = 1;
				for( i = 0; i < j; i ++ )
				{
					//111024 by cq ɾ��
					//if( ( *( InStr + i ) >= 0 ) && ( *( InStr + i ) <= 9 ) )
					if( ( *( InStr + i ) >= 0 ) && ( *( InStr + i ) <= 1 ) )
					{
						SystemParameter.IsMuliVerd = *( InStr + i );
						break;
					}
				}
				//111024 by cq ɾ��
				//if( SystemParameter.IsMuliVerd != 1 )
					//SystemParameter.IsMuliVerd = 0;	
				SystemSave = 1;
			}
		break;
		case 5: //�����˱�	
			if( OutInFlag == 0 )
			{				
				sprintf( OutStr, "%bu", SystemParameter.RefundPermission );			
				*len = 1;
			}
			else
			{
				j = *len;
				if( j == 0 )
					break;
				if( j > 1 )
					j = 1;
				for( i = 0; i < j; i ++ )
				{
					//111024 by cq ɾ��
					//if( ( *( InStr + i ) >= 0 ) && ( *( InStr + i ) <= 9 ) )
					if( ( *( InStr + i ) >= 0 ) && ( *( InStr + i ) <= 1 ) )
					{
						SystemParameter.RefundPermission = *( InStr + i );
						break;
					}
				}		
				//111024 by cq ɾ��
				//if( SystemParameter.RefundPermission != 1 )
					//SystemParameter.RefundPermission = 0;	
				SystemSave = 1;
			}
		break;
		case 6://�ٽ��׵��޶�
			if( OutInFlag == 0 )
			{				
				switch( SystemParameter.curUnit )
				{
					case 1:
						*len = sprintf( OutStr, "%u", SystemParameter.Min );
					break;				
					case 10:
						*len = sprintf( OutStr, "%u.%u", SystemParameter.Min/SystemParameter.curUnit,SystemParameter.Min%SystemParameter.curUnit);
					break;
					case 100:
						*len = sprintf( OutStr, "%u.%02u", SystemParameter.Min/SystemParameter.curUnit,SystemParameter.Min%SystemParameter.curUnit);
					break;					
				}
			}
			else
			{				
				//Trace( "\n set IP val \n");
				j = *len;											
				if( j == 0 )
					break;
				SystemParameter.Min = 0;	
				for( i = 0; i < j; i ++ )
				{
					if( ( *( InStr + i ) >= 0 ) && ( *( InStr + i ) <= 9 ) )					
						SystemParameter.Min = SystemParameter.Min*10 + *( InStr + i );						
				}			
				SystemSave = 1;
			}	
		break;			
		case 7://�Ƿ�������ֽ����	
			if( OutInFlag == 0 )
			{				
				sprintf( OutStr, "%bu", SystemParameter.BillNo );			
				*len = 1;
			}			
			else
			{
				j = *len;
				if( j == 0 )
					break;
				if( j > 1 )
					j = 1;
				for( i = 0; i < j; i ++ )
				{
					//111024 by cq ɾ��
					//if( ( *( InStr + i ) >= 0 ) && ( *( InStr + i ) <= 9 ) )
					if( ( *( InStr + i ) >= 0 ) && ( *( InStr + i ) <= 1 ) )
					{
						SystemParameter.BillNo = *( InStr + i );
						break;
					}
				}

				if( SystemParameter.BillNo == 0 )
					DeviceStatus.BillAccepter = 128;	
				else
					DeviceStatus.BillAccepter &= 0x7f;	
				
				//111024 by cq ɾ��
				//if(SystemParameter.BillNo != 1)					
					//SystemParameter.BillNo = 0;
				SystemSave = 1;
			}			
		break;
		case 8:  //Coin acceptor on
			if( OutInFlag == 0 )
			{				
				sprintf( OutStr, "%bu", SystemParameter.coinOn );			
				*len = 1;
			}
			/*
			else
			{  
				j = *len;
				if( j == 0 )
					break;
				if( j > 1 )
					j = 1;
				for( i = 0; i < j; i ++ )
				{
					//111024 by cq ɾ��
					//if( ( *( InStr + i ) >= 0 ) && ( *( InStr + i ) <= 9 ) )
					if( ( *( InStr + i ) >= 0 ) && ( *( InStr + i ) <= 1 ) )
					{
						SystemParameter.coinOn = *( InStr + i );
						break;
					}
				}

				if( SystemParameter.coinOn == 0 )
					DeviceStatus.CoinAccepter = 128;  
				else
					DeviceStatus.CoinAccepter &= 0x7f;
					
				//if( SystemParameter.coinOn != 1 )
					//SystemParameter.coinOn = 0;	
				SystemSave = 1;                
			}
			*/
		break;
		case 9:  //If open ACDC module 
			if( OutInFlag == 0 )
			{				
				*len = sprintf( OutStr, "%bu", SystemParameter.ACDCModule );			
			}
			/*
			else
			{
				j = *len;
				if( j == 0 )
					break;
				if( j > 1 )
					j = 1;
                //SystemParameter.ACDCModule = 0;
				for( i = 0; i < j; i ++ )
				{
					//111024 by cq ɾ��
					//if( ( *( InStr + i ) >= 0 ) && ( *( InStr + i ) <= 9 ) )
					if( ( *( InStr + i ) >= 0 ) && ( *( InStr + i ) <= 1 ) )
					{
						SystemParameter.ACDCModule = *( InStr + i );
						break;
					}
				}
				//111024 by cq ɾ��
				//if( SystemParameter.ACDCModule != 1 )
					//SystemParameter.ACDCModule = 0;	
				SystemSave = 1;
			}
			*/
		break;		
		/*
		//111024 by cq ɾ��  			
		case 10://#1������ֵ			
			if( OutInFlag == 0 )
			{				
				switch( SystemParameter.curUnit )
				{
					case 1:
						*len = sprintf( OutStr, "%u", SystemParameter.HopperCoinPrice1 );
					break;				
					case 10:
						*len = sprintf( OutStr, "%u.%u", SystemParameter.HopperCoinPrice1/SystemParameter.curUnit,SystemParameter.HopperCoinPrice1%SystemParameter.curUnit );
					break;
					case 100:
						*len = sprintf( OutStr, "%u.%02u", SystemParameter.HopperCoinPrice1/SystemParameter.curUnit,SystemParameter.HopperCoinPrice1%SystemParameter.curUnit );
					break;					
				}				
			}
			else
			{	
                break;
                /*			
				//Trace( "\n set IP val \n");
				j = *len;											
				if( j == 0 )
					break;
				SystemParameter.HopperCoinPrice1 = 0;	
				for( i = 0; i < j; i ++ )
				{
					if( ( *( InStr + i ) >= 0 ) && ( *( InStr + i ) <= 9 ) )					
						SystemParameter.HopperCoinPrice1 = SystemParameter.HopperCoinPrice1*10 + *( InStr + i );						
				}			
				SystemSave = 1;
                * /
			}			
		break;
        		
		case 11://#2������ֵ			
			if( OutInFlag == 0 )
			{					
				switch( SystemParameter.curUnit )
				{
					case 1:
						*len = sprintf( OutStr, "%u", SystemParameter.HopperCoinPrice2 );
					break;				
					case 10:
						*len = sprintf( OutStr, "%u.%u", SystemParameter.HopperCoinPrice2/SystemParameter.curUnit,SystemParameter.HopperCoinPrice2%SystemParameter.curUnit );
					break;
					case 100:
						*len = sprintf( OutStr, "%u.%02u", SystemParameter.HopperCoinPrice2/SystemParameter.curUnit,SystemParameter.HopperCoinPrice2%SystemParameter.curUnit );
					break;					
				}				
			}
			else
			{
                break;
                /* 				
				//Trace( "\n set IP val \n");
				j = *len;											
				if( j == 0 )
					break;
				SystemParameter.HopperCoinPrice2 = 0;	
				for( i = 0; i < j; i ++ )
				{
					if( ( *( InStr + i ) >= 0 ) && ( *( InStr + i ) <= 9 ) )					
						SystemParameter.HopperCoinPrice2 = SystemParameter.HopperCoinPrice2*10 + *( InStr + i );						
				}			
				SystemSave = 1;
                * /
			}			
		break;
        */
        
		case 10://# 1 note
		case 11://# 2 note
		case 12://# 3 note
		case 13: //# 4 note
		case 14: //# 5 note
		case 15: //# 6 note
		case 16: //# 1 coin
		case 17: //# 2 coin
		case 18: //# 3 coin
		case 19: //# 4 coin
			if( OutInFlag == 0 )
			{
				
				switch(Num)
					{	
					case 10: //# 1 note
						tempMoney = SystemParameter.billValue[0];	
						break;
					case 11: //# 2 note
						tempMoney = SystemParameter.billValue[1];	
						break;
					case 12: //# 3 note
						tempMoney = SystemParameter.billValue[2];	
						break;
					case 13: //# 4 note
						tempMoney = SystemParameter.billValue[3];	
						break;
					case 14: //# 5 note
						tempMoney = SystemParameter.billValue[4];	
						break;
					case 15: //# 6 note
						tempMoney = SystemParameter.billValue[5];	
						break;
						
					case 16: //# 1 coin
						tempMoney = SystemParameter.coinValue[0];	
						break;
					case 17: //# 2 coin
						tempMoney = SystemParameter.coinValue[1];	
						break;
					case 18: //# 3 coin
						tempMoney = SystemParameter.coinValue[2];	
						break;
					case 19: //# 4 coin
						tempMoney = SystemParameter.coinValue[3];	
						break;													
					default:
						break;
					}

				
				switch( SystemParameter.curUnit )
				{
					case 1:
						*len = sprintf( OutStr, "%u", tempMoney/100 );
					break;				
					case 10:
						*len = sprintf( OutStr, "%u.%u", tempMoney/10/SystemParameter.curUnit,tempMoney/10%SystemParameter.curUnit );
					break;
					case 100:
						*len = sprintf( OutStr, "%u.%02u", tempMoney/SystemParameter.curUnit,tempMoney%SystemParameter.curUnit );
					break;					
				}		
				
			}
			/*
			else
			{				
				//Trace( "\n set IP val \n");
				j = *len;											
				if( j == 0 )
					break;				
				if( j > 5 )
					j = 5;

				tempMoney = 0;
				//SystemParameter.HopperCoinPrice4 = 0;	
				
				for( i = 0; i < j; i ++ )
				{
					if( ( *( InStr + i ) >= 0 ) && ( *( InStr + i ) <= 9 ) )							
						tempMoney = tempMoney*10 + *( InStr + i );
						//SystemParameter.HopperCoinPrice4 = SystemParameter.HopperCoinPrice4*10 + *( InStr + i );						
				}	

				switch(Num)
					{					
					case 10: //# 1 note
						SystemParameter.billValue[0] = tempMoney;	
						break;
					case 11: //# 2 note
						SystemParameter.billValue[1] = tempMoney;	
						break;
					case 12: //# 3 note
						SystemParameter.billValue[2] = tempMoney;	
						break;
					case 13: //# 4 note
						SystemParameter.billValue[3] = tempMoney;	
						break;
					case 14: //# 5 note
						SystemParameter.billValue[4] = tempMoney;	
						break;
					case 15: //# 6 note
						SystemParameter.billValue[5] = tempMoney;	
						break;							
						
					case 16: //# 1 coin
						SystemParameter.coinValue[0] = tempMoney;	
						break;
					case 17: //# 2 coin
						SystemParameter.coinValue[1] = tempMoney;	
						break;
					case 18: //# 3 coin
						SystemParameter.coinValue[2] = tempMoney;	
						break;
					case 19: //# 4 coin
						SystemParameter.coinValue[3] = tempMoney;	
						break;															
					default:
						break;
					}				
				SystemSave = 1;
			}			
			break;	
			*/
			/*
		case 28:  //SVC no change
			
			if( OutInFlag == 0 )
			{				
				sprintf( OutStr, "%bu", SystemParameter.SVC_NoChange );			
				*len = 1;
			}
			else
			{
				j = *len;
				if( j == 0 )
					break;
				if( j > 1 )
					j = 1;
				for( i = 0; i < j; i ++ )
				{
					//111024 by cq ɾ��
					//if( ( *( InStr + i ) >= 0 ) && ( *( InStr + i ) <= 9 ) )
					if( ( *( InStr + i ) >= 0 ) && ( *( InStr + i ) <= 1 ) )
					{
						SystemParameter.SVC_NoChange = *( InStr + i );
						break;
					}
				}
				//if( SystemParameter.SVC_NoChange != 1 )
					//SystemParameter.SVC_NoChange = 0;	
				SystemSave = 1;
			}
		break;
		*/
        /*
        case 29:  //Bus card on
        	
			if( OutInFlag == 0 )
			{				
				sprintf( OutStr, "%bu", SystemParameter.busCardOn );			
				*len = 1;
			}
			else
			{
				j = *len;
				if( j == 0 )
					break;
				if( j > 1 )
					j = 1;
				for( i = 0; i < j; i ++ )
				{
					//111024 by cq ɾ��
					//if( ( *( InStr + i ) >= 0 ) && ( *( InStr + i ) <= 9 ) )
					if( ( *( InStr + i ) >= 0 ) && ( *( InStr + i ) <= 1 ) )
					{
						SystemParameter.busCardOn = *( InStr + i );
						break;
					}
				}
				//if( SystemParameter.busCardOn != 1 )
					//SystemParameter.busCardOn = 0;	
				SystemSave = 1;
			}
		break;
		*/
			/*
        case 30:  //bus card read time 
        	
			if( OutInFlag == 0 )
			{				
				*len = sprintf( OutStr, "%bu", SystemParameter.BCReadTime );			
			}
			else
			{
				j = *len;
				if( j == 0 )
					break;
				if( j > 2 )
					j = 2;
                SystemParameter.BCReadTime = 0;
				for( i = 0; i < j; i ++ )
				{
					if( ( *( InStr + i ) >= 0 ) && ( *( InStr + i ) <= 9 ) )
					{
						SystemParameter.BCReadTime = SystemParameter.BCReadTime*10 + *( InStr + i );
						break;
					}
				}
				SystemSave = 1;
			}
		break;
		*/

		 /*		
		case 2://#3Ӳ����ֵ			
			if( OutInFlag == 0 )
			{													
				switch( SystemParameter.curUnit )
				{
					case 1:
						*len = sprintf( OutStr, "%u", SystemParameter.HopperCoinPrice3 );
					break;				
					case 10:
						*len = sprintf( OutStr, "%u.%u", SystemParameter.HopperCoinPrice3/SystemParameter.curUnit,SystemParameter.HopperCoinPrice3%SystemParameter.curUnit );
					break;
					case 100:
						*len = sprintf( OutStr, "%u.%02u", SystemParameter.HopperCoinPrice3/SystemParameter.curUnit,SystemParameter.HopperCoinPrice3%SystemParameter.curUnit );
					break;					
				}
			}
			else
			{				
				//Trace( "\n set IP val \n");
				j = *len;											
				if( j == 0 )
					break;
				SystemParameter.HopperCoinPrice3 = 0;	
				for( i = 0; i < j; i ++ )
				{
					if( ( *( InStr + i ) >= 0 ) && ( *( InStr + i ) <= 9 ) )					
						SystemParameter.HopperCoinPrice3 = SystemParameter.HopperCoinPrice3*10 + *( InStr + i );						
				}										
				SystemSave = 1;
			}			
		break;	
		*/
		
		
		
//111024 by cq ɾ��	
/*
		case 6://�Ƿ����ֻ�ģ��	
			if( OutInFlag == 0 )
			{				
				sprintf( OutStr, "%bu", SystemParameter.MobileON );			
				*len = 1;
			}
			else
			{
				j = *len;
				if( j == 0 )
					break;
				if( j > 1 )
					j = 1;				
				SystemParameter.MobileON = *( InStr + i );				
				SystemSave = 1;
			}
		break;
*/		
		
		//111024 by cq ɾ��
		/*
		case 9://���ʽ��
			if( OutInFlag == 0 )
			{				
				switch( SystemParameter.curUnit )
				{
					case 1:
						*len = sprintf( OutStr, "%u", SystemParameter.DoubtCash );
					break;				
					case 10:
						*len = sprintf( OutStr, "%u.%u", SystemParameter.DoubtCash/SystemParameter.curUnit,SystemParameter.DoubtCash%SystemParameter.curUnit);
					break;
					case 100:
						*len = sprintf( OutStr, "%u.%02u", SystemParameter.DoubtCash/SystemParameter.curUnit,SystemParameter.DoubtCash%SystemParameter.curUnit);
					break;					
				}
			}
			else
			{
				j = *len;
				if( j == 0 )
					break;
				if( j > 1 )
					j = 1;			
				if( *( InStr ) == 0 ) 					
					SystemParameter.DoubtCash = 0;				
				SystemSave = 1;
			}			
		break;
		case 10://ȡ����ID����				
			if(  OutInFlag == 0 )
			{
				for( i = 0; i < 5; i++ )
					*len += sprintf( OutStr + i, "%bu", SystemParameter.VmID[i] );
			}			
			else//����
			{		
				j = *len;
				memset( SystemParameter.VmID, 0, sizeof( SystemParameter.VmID ) );				
				for( i = 0; i < j; i ++ )
				{
					if( ( *( InStr + i ) >= 0 ) && ( *( InStr + i ) <= 9 ) )					
						SystemParameter.VmID[i] = *( InStr + i );					
				}
				SystemSave = 1;
			}						
		break;
		case 11://GSMģ�����
			if( OutInFlag == 0 )
			{
				for( i = 0; i < 15; i++ )
				{
					if( SystemParameter.GSMNO[i] != 0xff )
					{
						if( SystemParameter.GSMNO[i] >= 0x10 )
							*len += sprintf( OutStr + 2*i, "%2bx", SystemParameter.GSMNO[i] );	
						else
							*len += sprintf( OutStr + 2*i, "%02bx", SystemParameter.GSMNO[i] );	
						if( ( SystemParameter.GSMNO[i] & 0x0f ) == 0x0f )
						{
							(*len)--;
							break;
						}
					}
					else
						break;				
				}
				OutStr[(*len)] = 0x00;
			}
			else
			{
				j = *len;
				memset( SystemParameter.GSMNO, 0, sizeof( SystemParameter.GSMNO ) );				
				for( i = 0; i < j/2; i ++ )									
					SystemParameter.GSMNO[i] = *( InStr + 2*i ) * 16 + *( InStr + 2*i + 1 );				
				if( ( j%2 ) == 1 )//����������		
					SystemParameter.GSMNO[i] = *( InStr + 2*i )*16 + 0x0f;
				i++;
				SystemParameter.GSMNO[i] = 0xff;
				SystemSave = 1;
			}
		break;
		*/
		
		//----------------------------------------------------------------------------------------------------
		/*	
        case 9: //# 1 note
        if( OutInFlag == 0 )
			{			
				switch( SystemParameter.curUnit )
				{
					case 1:
						*len = sprintf( OutStr, "%u", SystemParameter.billValue[0] );
					break;				
					case 10:
						*len = sprintf( OutStr, "%u.%u", SystemParameter.billValue[0]/SystemParameter.curUnit,SystemParameter.billValue[0]%SystemParameter.curUnit );
					break;
					case 100:
						*len = sprintf( OutStr, "%u.%02u", SystemParameter.billValue[0]/SystemParameter.curUnit,SystemParameter.billValue[0]%SystemParameter.curUnit );
					break;					
				}				
			}
			else
			{				
				//Trace( "\n set IP val \n");
				j = *len;											
				if( j == 0 )
					break;
				if( j > 5 )
					j = 5;
				SystemParameter.billValue[0] = 0;	
				for( i = 0; i < j; i ++ )
				{
					if( ( *( InStr + i ) >= 0 ) && ( *( InStr + i ) <= 9 ) )					
						SystemParameter.billValue[0] = SystemParameter.billValue[0]*10 + *( InStr + i );						
				}	
				SystemSave = 1;
			}			
		break;
		case 10: //# 2 note
        if( OutInFlag == 0 )
			{			
				switch( SystemParameter.curUnit )
				{
					case 1:
						*len = sprintf( OutStr, "%u", SystemParameter.billValue[1] );
					break;				
					case 10:
						*len = sprintf( OutStr, "%u.%u", SystemParameter.billValue[1]/SystemParameter.curUnit,SystemParameter.billValue[1]%SystemParameter.curUnit );
					break;
					case 100:
						*len = sprintf( OutStr, "%u.%02u", SystemParameter.billValue[1]/SystemParameter.curUnit,SystemParameter.billValue[1]%SystemParameter.curUnit );
					break;					
				}				
			}
			else
			{				
				//Trace( "\n set IP val \n");
				j = *len;											
				if( j == 0 )
					break;
				if( j > 5 )
					j = 5;
				SystemParameter.billValue[1] = 0;	
				for( i = 0; i < j; i ++ )
				{
					if( ( *( InStr + i ) >= 0 ) && ( *( InStr + i ) <= 9 ) )					
						SystemParameter.billValue[1] = SystemParameter.billValue[1]*10 + *( InStr + i );						
				}	
				SystemSave = 1;
			}			
		break;
        case 11: //# 3 note
        if( OutInFlag == 0 )
			{			
				switch( SystemParameter.curUnit )
				{
					case 1:
						*len = sprintf( OutStr, "%u", SystemParameter.billValue[2] );
					break;				
					case 10:
						*len = sprintf( OutStr, "%u.%u", SystemParameter.billValue[2]/SystemParameter.curUnit,SystemParameter.billValue[2]%SystemParameter.curUnit );
					break;
					case 100:
						*len = sprintf( OutStr, "%u.%02u", SystemParameter.billValue[2]/SystemParameter.curUnit,SystemParameter.billValue[2]%SystemParameter.curUnit );
					break;					
				}				
			}
			else
			{				
				//Trace( "\n set IP val \n");
				j = *len;											
				if( j == 0 )
					break;
				if( j > 5 )
					j = 5;
				SystemParameter.billValue[2] = 0;	
				for( i = 0; i < j; i ++ )
				{
					if( ( *( InStr + i ) >= 0 ) && ( *( InStr + i ) <= 9 ) )					
						SystemParameter.billValue[2] = SystemParameter.billValue[2]*10 + *( InStr + i );						
				}	
				SystemSave = 1;
			}			
		break;
		case 12: //# 4 note
        if( OutInFlag == 0 )
			{			
				switch( SystemParameter.curUnit )
				{
					case 1:
						*len = sprintf( OutStr, "%u", SystemParameter.billValue[3] );
					break;				
					case 10:
						*len = sprintf( OutStr, "%u.%u", SystemParameter.billValue[3]/SystemParameter.curUnit,SystemParameter.billValue[3]%SystemParameter.curUnit );
					break;
					case 100:
						*len = sprintf( OutStr, "%u.%02u", SystemParameter.billValue[3]/SystemParameter.curUnit,SystemParameter.billValue[3]%SystemParameter.curUnit );
					break;					
				}				
			}
			else
			{				
				//Trace( "\n set IP val \n");
				j = *len;											
				if( j == 0 )
					break;
				if( j > 5 )
					j = 5;
				SystemParameter.billValue[3] = 0;	
				for( i = 0; i < j; i ++ )
				{
					if( ( *( InStr + i ) >= 0 ) && ( *( InStr + i ) <= 9 ) )					
						SystemParameter.billValue[3] = SystemParameter.billValue[3]*10 + *( InStr + i );						
				}	
				SystemSave = 1;
			}			
		break;
        case 13: //# 5 note
        if( OutInFlag == 0 )
			{			
				switch( SystemParameter.curUnit )
				{
					case 1:
						*len = sprintf( OutStr, "%u", SystemParameter.billValue[4] );
					break;				
					case 10:
						*len = sprintf( OutStr, "%u.%u", SystemParameter.billValue[4]/SystemParameter.curUnit,SystemParameter.billValue[4]%SystemParameter.curUnit );
					break;
					case 100:
						*len = sprintf( OutStr, "%u.%02u", SystemParameter.billValue[4]/SystemParameter.curUnit,SystemParameter.billValue[4]%SystemParameter.curUnit );
					break;					
				}				
			}
			else
			{				
				//Trace( "\n set IP val \n");
				j = *len;											
				if( j == 0 )
					break;
				if( j > 5 )
					j = 5;
				SystemParameter.billValue[4] = 0;	
				for( i = 0; i < j; i ++ )
				{
					if( ( *( InStr + i ) >= 0 ) && ( *( InStr + i ) <= 9 ) )					
						SystemParameter.billValue[4] = SystemParameter.billValue[4]*10 + *( InStr + i );						
				}	
				SystemSave = 1;
			}			
		break;
        case 14: //# 6 note
        if( OutInFlag == 0 )
			{			
				switch( SystemParameter.curUnit )
				{
					case 1:
						*len = sprintf( OutStr, "%u", SystemParameter.billValue[5] );
					break;				
					case 10:
						*len = sprintf( OutStr, "%u.%u", SystemParameter.billValue[5]/SystemParameter.curUnit,SystemParameter.billValue[5]%SystemParameter.curUnit );
					break;
					case 100:
						*len = sprintf( OutStr, "%u.%02u", SystemParameter.billValue[5]/SystemParameter.curUnit,SystemParameter.billValue[5]%SystemParameter.curUnit );
					break;					
				}				
			}
			else
			{				
				//Trace( "\n set IP val \n");
				j = *len;											
				if( j == 0 )
					break;
				if( j > 5 )
					j = 5;
				SystemParameter.billValue[5] = 0;	
				for( i = 0; i < j; i ++ )
				{
					if( ( *( InStr + i ) >= 0 ) && ( *( InStr + i ) <= 9 ) )					
						SystemParameter.billValue[5] = SystemParameter.billValue[5]*10 + *( InStr + i );						
				}	
				SystemSave = 1;
			}			
		break;
        case 15: //# 7 note
        if( OutInFlag == 0 )
			{			
				switch( SystemParameter.curUnit )
				{
					case 1:
						*len = sprintf( OutStr, "%u", SystemParameter.billValue[6] );
					break;				
					case 10:
						*len = sprintf( OutStr, "%u.%u", SystemParameter.billValue[6]/SystemParameter.curUnit,SystemParameter.billValue[6]%SystemParameter.curUnit );
					break;
					case 100:
						*len = sprintf( OutStr, "%u.%02u", SystemParameter.billValue[6]/SystemParameter.curUnit,SystemParameter.billValue[6]%SystemParameter.curUnit );
					break;					
				}				
			}
			else
			{				
				//Trace( "\n set IP val \n");
				j = *len;											
				if( j == 0 )
					break;
				if( j > 5 )
					j = 5;
				SystemParameter.billValue[6] = 0;	
				for( i = 0; i < j; i ++ )
				{
					if( ( *( InStr + i ) >= 0 ) && ( *( InStr + i ) <= 9 ) )					
						SystemParameter.billValue[6] = SystemParameter.billValue[6]*10 + *( InStr + i );						
				}	
				SystemSave = 1;
			}			
		break;
        case 16: //# 8 note
        if( OutInFlag == 0 )
			{			
				switch( SystemParameter.curUnit )
				{
					case 1:
						*len = sprintf( OutStr, "%u", SystemParameter.billValue[7] );
					break;				
					case 10:
						*len = sprintf( OutStr, "%u.%u", SystemParameter.billValue[7]/SystemParameter.curUnit,SystemParameter.billValue[7]%SystemParameter.curUnit );
					break;
					case 100:
						*len = sprintf( OutStr, "%u.%02u", SystemParameter.billValue[7]/SystemParameter.curUnit,SystemParameter.billValue[7]%SystemParameter.curUnit );
					break;					
				}				
			}
			else
			{				
				//Trace( "\n set IP val \n");
				j = *len;											
				if( j == 0 )
					break;
				if( j > 5 )
					j = 5;
				SystemParameter.billValue[7] = 0;	
				for( i = 0; i < j; i ++ )
				{
					if( ( *( InStr + i ) >= 0 ) && ( *( InStr + i ) <= 9 ) )					
						SystemParameter.billValue[7] = SystemParameter.billValue[7]*10 + *( InStr + i );						
				}	
				SystemSave = 1;
			}			
		break;
        // Coin value begin with 22
        case 17: //# 1 coin
        if( OutInFlag == 0 )
			{			
				switch( SystemParameter.curUnit )
				{
					case 1:
						*len = sprintf( OutStr, "%u", SystemParameter.coinValue[0] );
					break;				
					case 10:
						*len = sprintf( OutStr, "%u.%u", SystemParameter.coinValue[0]/SystemParameter.curUnit,SystemParameter.coinValue[0]%SystemParameter.curUnit );
					break;
					case 100:
						*len = sprintf( OutStr, "%u.%02u", SystemParameter.coinValue[0]/SystemParameter.curUnit,SystemParameter.coinValue[0]%SystemParameter.curUnit );
					break;					
				}				
			}
			else
			{				
				//Trace( "\n set IP val \n");
				j = *len;											
				if( j == 0 )
					break;
				if( j > 5 )
					j = 5;
				SystemParameter.coinValue[0] = 0;	
				for( i = 0; i < j; i ++ )
				{
					if( ( *( InStr + i ) >= 0 ) && ( *( InStr + i ) <= 9 ) )					
						SystemParameter.coinValue[0] = SystemParameter.coinValue[0]*10 + *( InStr + i );						
				}	
				SystemSave = 1;
			}			
		break;
		case 18: //# 2 coin
        if( OutInFlag == 0 )
			{			
				switch( SystemParameter.curUnit )
				{
					case 1:
						*len = sprintf( OutStr, "%u", SystemParameter.coinValue[1] );
					break;				
					case 10:
						*len = sprintf( OutStr, "%u.%u", SystemParameter.coinValue[1]/SystemParameter.curUnit,SystemParameter.coinValue[1]%SystemParameter.curUnit );
					break;
					case 100:
						*len = sprintf( OutStr, "%u.%02u", SystemParameter.coinValue[1]/SystemParameter.curUnit,SystemParameter.coinValue[1]%SystemParameter.curUnit );
					break;					
				}				
			}
			else
			{				
				//Trace( "\n set IP val \n");
				j = *len;											
				if( j == 0 )
					break;
				if( j > 5 )
					j = 5;
				SystemParameter.coinValue[1] = 0;	
				for( i = 0; i < j; i ++ )
				{
					if( ( *( InStr + i ) >= 0 ) && ( *( InStr + i ) <= 9 ) )					
						SystemParameter.coinValue[1] = SystemParameter.coinValue[1]*10 + *( InStr + i );						
				}	
				SystemSave = 1;
			}			
		break;
        case 19: //# 3 coin
        if( OutInFlag == 0 )
			{			
				switch( SystemParameter.curUnit )
				{
					case 1:
						*len = sprintf( OutStr, "%u", SystemParameter.coinValue[2] );
					break;				
					case 10:
						*len = sprintf( OutStr, "%u.%u", SystemParameter.coinValue[2]/SystemParameter.curUnit,SystemParameter.coinValue[2]%SystemParameter.curUnit );
					break;
					case 100:
						*len = sprintf( OutStr, "%u.%02u", SystemParameter.coinValue[2]/SystemParameter.curUnit,SystemParameter.coinValue[2]%SystemParameter.curUnit );
					break;					
				}				
			}
			else
			{				
				//Trace( "\n set IP val \n");
				j = *len;											
				if( j == 0 )
					break;
				if( j > 5 )
					j = 5;
				SystemParameter.coinValue[2] = 0;	
				for( i = 0; i < j; i ++ )
				{
					if( ( *( InStr + i ) >= 0 ) && ( *( InStr + i ) <= 9 ) )					
						SystemParameter.coinValue[2] = SystemParameter.coinValue[2]*10 + *( InStr + i );						
				}	
				SystemSave = 1;
			}			
		break;
		case 20: //# 4 coin
        if( OutInFlag == 0 )
			{			
				switch( SystemParameter.curUnit )
				{
					case 1:
						*len = sprintf( OutStr, "%u", SystemParameter.coinValue[3] );
					break;				
					case 10:
						*len = sprintf( OutStr, "%u.%u", SystemParameter.coinValue[3]/SystemParameter.curUnit,SystemParameter.coinValue[3]%SystemParameter.curUnit );
					break;
					case 100:
						*len = sprintf( OutStr, "%u.%02u", SystemParameter.coinValue[3]/SystemParameter.curUnit,SystemParameter.coinValue[3]%SystemParameter.curUnit );
					break;					
				}				
			}
			else
			{				
				//Trace( "\n set IP val \n");
				j = *len;											
				if( j == 0 )
					break;
				if( j > 5 )
					j = 5;
				SystemParameter.coinValue[3] = 0;	
				for( i = 0; i < j; i ++ )
				{
					if( ( *( InStr + i ) >= 0 ) && ( *( InStr + i ) <= 9 ) )					
						SystemParameter.coinValue[3] = SystemParameter.coinValue[3]*10 + *( InStr + i );						
				}	
				SystemSave = 1;
			}			
		break;
        case 21: //# 5 coin
        if( OutInFlag == 0 )
			{			
				switch( SystemParameter.curUnit )
				{
					case 1:
						*len = sprintf( OutStr, "%u", SystemParameter.coinValue[4] );
					break;				
					case 10:
						*len = sprintf( OutStr, "%u.%u", SystemParameter.coinValue[4]/SystemParameter.curUnit,SystemParameter.coinValue[4]%SystemParameter.curUnit );
					break;
					case 100:
						*len = sprintf( OutStr, "%u.%02u", SystemParameter.coinValue[4]/SystemParameter.curUnit,SystemParameter.coinValue[4]%SystemParameter.curUnit );
					break;					
				}				
			}
			else
			{				
				//Trace( "\n set IP val \n");
				j = *len;											
				if( j == 0 )
					break;
				if( j > 5 )
					j = 5;
				SystemParameter.coinValue[4] = 0;	
				for( i = 0; i < j; i ++ )
				{
					if( ( *( InStr + i ) >= 0 ) && ( *( InStr + i ) <= 9 ) )					
						SystemParameter.coinValue[4] = SystemParameter.coinValue[4]*10 + *( InStr + i );						
				}	
				SystemSave = 1;
			}			
		break;
        case 22: //# 6 coin
        if( OutInFlag == 0 )
			{			
				switch( SystemParameter.curUnit )
				{
					case 1:
						*len = sprintf( OutStr, "%u", SystemParameter.coinValue[5] );
					break;				
					case 10:
						*len = sprintf( OutStr, "%u.%u", SystemParameter.coinValue[5]/SystemParameter.curUnit,SystemParameter.coinValue[5]%SystemParameter.curUnit );
					break;
					case 100:
						*len = sprintf( OutStr, "%u.%02u", SystemParameter.coinValue[5]/SystemParameter.curUnit,SystemParameter.coinValue[5]%SystemParameter.curUnit );
					break;					
				}				
			}
			else
			{				
				//Trace( "\n set IP val \n");
				j = *len;											
				if( j == 0 )
					break;
				if( j > 5 )
					j = 5;
				SystemParameter.coinValue[5] = 0;	
				for( i = 0; i < j; i ++ )
				{
					if( ( *( InStr + i ) >= 0 ) && ( *( InStr + i ) <= 9 ) )					
						SystemParameter.coinValue[5] = SystemParameter.coinValue[5]*10 + *( InStr + i );						
				}	
				SystemSave = 1;
			}			
		break;
		*/
		
		/*
		case 29:  //If service, when GOC error
			if( OutInFlag == 0 )
			{				
				sprintf( OutStr, "%bu", SystemParameter.SVC_GOCErr );			
				*len = 1;
			}
			else
			{
				j = *len;
				if( j == 0 )
					break;
				if( j > 1 )
					j = 1;
				for( i = 0; i < j; i ++ )
				{
					if( ( *( InStr + i ) >= 0 ) && ( *( InStr + i ) <= 9 ) )
					{
						SystemParameter.SVC_GOCErr = *( InStr + i );
						break;
					}
				}
				if( SystemParameter.SVC_GOCErr != 1 )
					SystemParameter.SVC_GOCErr = 0;	
				SystemSave = 1;
			}
		break;
		*/		
        
               
		
		//====================================================================================================
		default:
			break;
	}
}

/***********************************/
/*yΪ�к�,NumΪ�˵������,flagΪ�Ƿ���ʾֵ*/
u_char  DisplayMenuAndVal( u_char y, u_char Num, bit flag )
{	
	u_char   xdata  len ;

	len = 0;	
	memset( y_displaystr,0,sizeof( y_displaystr ) );				
	if( flag == 0 )//�༭����˵�
	{	
		DisplayStr( 0, 0, 1, SysMenustr[Num].str, SysMenustr[Num].len );//��ʾ�˵�			
		return 0;
	}
	else//��ʾ����˵�
	{
		memcpy( y_displaystr, SysMenustr[Num].str, SysMenustr[Num].len );//�˵���ת��Ϊunicode��				
		ReadWriteSysParam( Num, y_displaystr + SysMenustr[Num].len, 0, &len, 0 );//�õ��˵���Ӧ��ֵ				
		DisplayStr( 0, y, 1,  y_displaystr, SysMenustr[Num].len + len );//��ʾ�˵�
		y_displaystr[SysMenustr[Num].len + len ] = '\0';
		if( SysMenustr[Num].len + len > 20 )
			return ( SysMenustr[Num].len + len - 20) ;		
		else
			return 0;
	}
}	

/***********************************/
/*�༭ѡ����,CardStyle,Ϊѡ�еĿ�������,NumΪѡ�еĲ˵����,flag��־λ,ȷ����ϵͳ����(0,��ʱCardStyle��Ч),
���ǿ�����(1)*/
bit  EditParam( u_char Num, u_char y )
{
	u_char  xdata Inputstr[30];
	u_char  xdata  key;
	u_char  xdata  Inputlen;	
	bit	data  ret;
	
	key = 0;
	Inputlen = 0;
	ret = 0;
	//Trace( "edit one SysParanMenu begin\n" );
	
	Inputlen = SysInputLen[Num];
	if( ( Num == 0 ) ||( Num == 1 ) ||( Num == 2 ) || ( Num == 7 )|| ( Num == 8 )|| ( Num == 9 ) )
		key = GetLineMoney( SysMenustr[Num].str, SysMenustr[Num].len, y, Inputstr, &Inputlen );		
	else
		key = GetLine( SysMenustr[Num].str, SysMenustr[Num].len, y, Inputstr, &Inputlen );	
	ClearKey();	
	//Trace( "input END RET (0x) = %bx\n", key );		
	if( key == 1 )//Enter	
	{
		//Trace( "display select \n" );
		DisplayCursorState( 0, 0, 0, 0, 1 );			
		ReadWriteSysParam( Num, 0, Inputstr ,&Inputlen, 1 );
		ClearKey();		
	}		
	//Trace( "edit one SysParanMenu end\n" );
	return ret;
}

/************************************/
/*����ڲ˵����ƶ���ѡ��,SelectedNum��ǰ������ڵĲ˵����,
	CursorLine����ǰ��������ǵ���,ֵΪ1��2,MoveRange,�˵������ķ�Χ
	SysNum,ָ��ʾ����˵�,1Ϊϵͳ�˵�,2ΪƷ�Ʋ˵�,3Ϊ����˵�,
	ChangeLineflagָ���ƶ�����Ƿ��ƶ��˵���*/
void  SP_MenuSelected( u_char xdata *SelectedNum, u_char xdata *CursorLine, u_char MoveRange, u_char ChangeLineflag )
{
	u_char xdata  MenuNum = *SelectedNum;
	//����Ϊ1��ʾ����ڵ�һ��,Ϊ����ʾ����ڵڶ���
	u_char xdata  Cursor = *CursorLine;
	bit	   data   flag = 1;	
	u_char xdata  ReDisplen = 0;
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
	//			Trace("\n Cursor1 = %bu ", Cursor );				
	//			Trace("\n MenuNum1 = %bu ", MenuNum );
				if( Cursor == 2 )//ѡ�б������
				{			
					DisplayCursorState( 0, 0, 1, 2, 1 );//��һ�������					
					Cursor = 1;
					if( ( ChangeLineflag & 0x01 ) == 0x01 )					
						ChangeLineflag |= 0x02;
					else
					{
						if( MenuNum == 0 )
							MenuNum = MoveRange;					
						else									    
							MenuNum--;					
					}						
	//				Trace("\n Cursor2 = %bu ", Cursor );				
	//				Trace("\n MenuNum2 = %bu ", MenuNum );
				}
				else//�˵��Ϸ�
				{	
	//				Trace("\n Cursor3 = %bu ", Cursor );				
	//				Trace("\n MenuNum3 = %bu ", MenuNum );					
				//	DisplayMenuAndVal( 1, MenuNum, 1 );					
					if( MenuNum == 0 )
						MenuNum = MoveRange;					
					else									    
						MenuNum--;					
					ReDisplen = DisplayMenuAndVal( 0, MenuNum , 1 );
					if( ReDisplen != 0 )
					{
						DisplayStr( 0, 1, 1,  y_displaystr + 20, ReDisplen );//��ʾ�˵�						
						ReDisplen = 0;
						DisplayCursorState( 0, Cursor - 1, 1, 2, 1 );//��һ�������
						if( Cursor == 1 )
						{
							//���Ŀǰ�ڵ�һ�У������ƹ�겻�ı�˵�ѡ��
							ChangeLineflag |= 0x02;
						}
						else
						{
							//���Ŀǰ�ڵڶ��У������ƹ�겻�ı�˵�ѡ��
							ChangeLineflag |= 0x01;
						}
					}
					else
					{
						if(	MenuNum == MoveRange )
							ReDisplen = DisplayMenuAndVal( 1, 0 , 1 );
						else
							ReDisplen = DisplayMenuAndVal( 1, MenuNum + 1 , 1 );
						DisplayCursorState( 0, Cursor - 1, 1, 2, 1 );//��һ�������
						ChangeLineflag = 0;
					 //  Cursor = 1;
					}	
	//				Trace("\n Cursor4 = %bu ", Cursor );				
	//				Trace("\n MenuNum4 = %bu ", MenuNum );										
				}
				break;
			case KEY_DOWN://����	
	//			Trace("\n Cursor5 = %bu ", Cursor );				
	//			Trace("\n MenuNum5 = %bu ", MenuNum );					
				if( Cursor == 1 )//ѡ�б������
				{
					DisplayCursorState( 0, 1, 1, 2, 1 );//�ڶ��������
					if( ( ChangeLineflag & 0x02 ) == 0x02 )					
						ChangeLineflag |= 0x01;
					else
					{
						if( MenuNum == MoveRange )
							MenuNum = 0;					
						else									    						
							MenuNum++;				     
					}
					Cursor = 2;	
	//				Trace("\n Cursor7 = %bu ", Cursor );				
	//				Trace("\n MenuNum7 = %bu ", MenuNum );					
				}
				else//�˵��·�
				{	
					if( ChangeLineflag != 0x00 )
					{
						ChangeLineflag = 0;
						if( MenuNum == MoveRange )
							MenuNum = 0;					
						else			
							MenuNum++;	
			//		   DisplayCursorState( 0, 0, 1, 2, 1 );//�ڶ��������
			//		   Cursor = 1;
					}
	//				Trace("\n Cursor8 = %bu ", Cursor );				
	//				Trace("\n MenuNum8 = %bu ", MenuNum );	
					ReDisplen = DisplayMenuAndVal( 0, MenuNum, 1 );															
					if( ReDisplen != 0 )
					{
						DisplayStr( 0, 1, 1,  y_displaystr + 20, ReDisplen );//��ʾ�˵�						
						ReDisplen = 0;
						if( Cursor == 1 )
						{
							//���Ŀǰ�ڵ�һ�У������ƹ�겻�ı�˵�ѡ��
							ChangeLineflag |= 0x02;
						}
						else
						{
							//���Ŀǰ�ڵڶ��У������ƹ�겻�ı�˵�ѡ��
							ChangeLineflag |= 0x01;
						}
					}
					else
					{						
						if( MenuNum == MoveRange )
							MenuNum = 0;					
						else									    
							MenuNum++;	
						ReDisplen = DisplayMenuAndVal( 1, MenuNum , 1 );																					
					//	Cursor = 2;
					}
	//				Trace("\n Cursor9 = %bu ", Cursor );				
	//				Trace("\n MenuNum9 = %bu ", MenuNum );
				}
				break;
			case KEY_SUBMIT://Enter,ѡ����ĳ��˵�
				{			
					*SelectedNum = MenuNum;
				//	if( ChangeLineflag != 0 )
				//	{
				//		*CursorLine = 1;
				//		DisplayStr( 0, 1, 1,  " ", 20 );//��ʾ�˵�
				//	}
				//	else
					*CursorLine = Cursor;					
					flag = 0;	
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

/*���غ���*/
bit SysParamManage()		
{
	u_char  xdata fristNum ;//һ���˵����
	u_char  xdata LineNum ;//ѡ����Ļ���к�	
	u_char xdata  ReDisplen = 0;
	//bit0Ϊ���ƹⲻ�ı�˵���,bit1Ϊ���ƹ�겻�ı�˵���
	u_char xdata  ChangeLineflag = 0;	

	ClearKey();
	
	/*��ʾ���в˵�����ֵ*/				
	DisplayMenuAndVal( 0, 0, 1 );	
	DisplayMenuAndVal( 1, 1, 1 );		
	DisplayCursorState( 0, 1, 1, 2, 1 );//���ù���ڵڶ�������Ϊ���й��״̬
	fristNum = 1;
	LineNum = 2;	
	while( 1 )
	{		
		/*�жϰ��ºμ�*/			
		SP_MenuSelected( &fristNum, &LineNum, MENU_COUNT( SysMenustr ) - 1, ChangeLineflag );			
		//ѡ����ĳ��˵�				
		if( fristNum == 100 )//ѡ���˳�									
			break;		
		else//û��ѡ���˳�
		{				
			ClearKey();									
			EditParam( fristNum, LineNum - 1 );	
			//������ʾ���������ֵ			
			if( LineNum == 2 )
			{			
				if( fristNum == 0 )
					ReDisplen = DisplayMenuAndVal( 0, MENU_COUNT( SysMenustr ) - 1, 1 );
				else						
					ReDisplen = DisplayMenuAndVal( 0, fristNum-1, 1 );						
				if( ReDisplen > 0 )
				{
					DisplayStr( 0, 1, 1,  y_displaystr + 20, ReDisplen );//��ʾ�˵�					
					ReDisplen = 0;
					ChangeLineflag |=0x01;
				}
				else
				{
					ReDisplen = DisplayMenuAndVal( 1, fristNum, 1 );
					if( ReDisplen > 0 )
						ChangeLineflag = 0;
				}
			}
			else
			{	
				ReDisplen = DisplayMenuAndVal( 0, fristNum, 1 );				
				if( ReDisplen > 0 )
				{
					DisplayStr( 0, 1, 1,  y_displaystr + 20, ReDisplen );//��ʾ�˵�					
					ReDisplen = 0;
					ChangeLineflag |=0x02;
				}
				else
				{
					if( fristNum == ( MENU_COUNT( SysMenustr ) - 1 ) )
						DisplayMenuAndVal( 1, 0, 1 );	
					else						
						DisplayMenuAndVal( 1, fristNum + 1, 1 );	
				}
			//	DisplayMenuAndVal( 0, fristNum, 1 );
			}			
			DisplayCursorState( 0, LineNum - 1, 1, 2, 1 );//���ù��Ϊ����״̬			
		}		
	}		
	return 0;
}

