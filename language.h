#ifndef __LANGUAGE_H__
#define __LANGUAGE_H__

#include "global.h"

#define STR_WELCOME 0
#define STR_COIN_NOT_ENOUGH 1//Ӳ�Ҳ���
#define STR_INPUT_CODE_TIMEOUT 2//ѡ����ʱ
#define STR_DOMAIN_ERROR 3     /*��ֵ����*/
#define STR_INPUT_GOODS 4 /*����������*/
#define STR_OK_NOT 5 /* ѡ��ȷ��*/
#define STR_GET_COIN 6 /*ȡ��Ӳ��*/
#define	STR_CANCEL 7 /*�ͻ�ȡ�� */
#define STR_INVAILD_CHOICE 8 /* ��Чѡ�� */
#define	STR_CONFIRM 9 /*�ͻ�ȡ�� */
#define STR_INSERT_BILL_COIN 10 /*����ֽ�Һ�Ӳ�� */
#define STR_CUSTOM_PAYED 11 /* �û��Ѿ������Ľ��ͳ�� */
#define STR_CHOICE_CHEAPERONE  12 /*ѡ������˵�ͬ�࿨ */
#define STR_HARDWARE_ERR 13 /* Ӳ������ */
#define STR_GOODS_SOLDOUT 14 /*�����ۿ� */
#define STR_THX_YOU_WITHOUT_COIN 15 /* ллʹ�ã���ȡ��Ӳ����ͷ */
#define STR_OUT_OF_SERVICE 16 /*��ͣ���� */
#define STR_HOPPER1_ERR 17 /*Ӳ��ģ�飱���� */
#define STR_PLEASE_WAIT 18 /*���Ժ�*/
#define STR_NOT_ENOUGH_NOTE 19 /*Ǯ����*/
#define STR_TRANCE_ING	20//���ڲ���
#define STR_OUTING_COIN	21//������Ǯ
#define STR_CHANGECOIN_ERRCFG 22//���ʧ��
#define	STR_PRESS_ANYKEY 23 //���������ʼ
#define STR_RE_INPUT_GOODS 24 /*��ѡ������*/
#define STR_INPUT_WAY_NO 25 /*��������*/
#define STR_TAKE_GOODS 26 /*ȡ�߻���*/ 
#define STR_TAKE_COIN 27 /*ȡ��Ӳ��*/
#define STR_GOODS_WAY_ERR1 28 /* �������� */
#define STR_GOODS_WAY_ERR2 29 /* ��Ʒ�ۼ� */
#define STR_OPERATION_TIMEOUT 30 /*������ʱ*/
#define STR_REFUND_MONEY 31 /*�˿�*/
#define STR_DUO_MONEY 32 /*Ƿ��*/
#define STR_INSERT_COIN 33 /*����Ӳ�� */
#define STR_INSERT_BILL 34/*����ֽ��*/
#define STR_INSERT_MONEY 35/*�����ʵ���Ǯ*/
#define STR_TYPE_VER        36   /*���ͺͰ汾��*/
#define STR_RE_BUY          37   /*�ٴι�����Ʒ*/
#define STR_SHORT_CHANGE    38   /*��������Ӳ�Ҳ���*/
#define STR_PRICE           39   /*��ӭ����*/
#define STR_COLUMN          40   /*����*/
#define STR_GOODS_OUT       41  /*�޻�*/
#define STR_COLUMN_ERROR    42  /*����*/
#define STR_CHANGE          43  /*����*/
#define STR_BALANCE         44  /*���*/
//-------------------------------------------------------
#define STR_BC_SCAN_CARD     45  //SCAN the card
#define STR_VP_M_S_G         46  //Money-Selection-Goods
#define STR_VP_S_C_G         47  //Selection-Card-Goods
#define STR_VP_CARD_MONEYLOW 48
#define STR_VP_CARD_READERR  49
#define STR_VP_CARD_BALANCE  50
#define STR_VP_BALANCE_LOW   51
#define STR_VP_CASH_TRADE     52
#define STR_VP_CASHLESS_TRADE 53
#define STR_VP_SELECTGOODS    54
//=======================================================
#define STR_OUT_OF_CASHSERVICE 55 /*��ͣ�ֽ��� */
#define STR_COLUMNNO          56   /*����*/
#define STR_GOODS_WAY_ERR3    57 /* �û�����ͣ���� */
#define STR_GOODS_WAY_NOSALE  58 /* ���ֽ�������Ʒ */
#define STR_COIN_UNPAY        59
#define STR_INPUT_GOODSNO     60 /*����������*/
#ifdef _CHINA_
	const struct StrAndLen code DispInformationTable[] =
	{
		{"      ��ӭ����", 14 },
        {"      ��Ǯ����", 14 }, //16			
        //{"    ������Ǯ", 12 },
		{"    ѡ����Ʒ��ʱ    ", 20 },	//2		
		{"  ������С���ֽ��", 20 },
		//{"������Ʒ���: ", 14 },      //4
        {"  ��ѡ�������Ͷ��!", 19  },  //4	
		{"ȷ��ENTER ȡ��CANCEL", 20 },	//5
		{"    ��ȡ��Ǯ", 12 },	        //6	
		{"ȡ��CANCEL", 10 },            //7
		{"    �������", 12 },          //8			
		{"ȷ��ENTER", 9 },              //9
		{"  ��Ͷ��ֽ�һ�Ӳ��", 18 },    //10	
		{"�ͻ����:", 9 },//11
		{"ѡ��������Ʒ��? ", 16  },//12	
		{"    ��������", 12 },//13
		{"  ��Ʒ������", 12 },//14	
		//{"      л  л", 12 },//15
		{"      лл!", 11    }, //15
		{"      ��ͣ����", 14 }, //16		
		{"    ����������", 14 }, //17	
		{"  ���Ժ�...", 12    },  //18	
		{"����, ��Ǯ��? ", 18 },
		{"  \xd5\xfd�ڳ���...", 13    }, //20
		{"  \xd5\xfd������...", 13    }, //21
		{"    ����ʧ��", 12 },//22
		{"    How are you!", 16 },     //23
		{"������������Ʒ���", 18 },   //24
		//{"������������Ʒ���", 18 },   //25
        {"  ��ѡ��������Ʒ", 16 },       //25
		{"  ��ȡ��...", 11 },            //26
		{"  ��ȡ���˱�...", 15   },      //27
		{"  ��Ʒ��������", 14    },      //28
		{"  ѡ��������Ʒ��?", 17 },    //29	
		{"      ������ʱ", 14 },       //30		
		{"    \xd5\xfd���˿�", 12 },   //31		
		{"Ƿ��:", 5 },                 //32
		{"    ��Ͷ��Ӳ��", 14 },       //33	
		{"    �����ֽ��", 14 },       //34		
		{"(2014-09-22)", 12 },   //35
		{"Junpeng-zonghe-1.0", 18 },    //36_V1.0-		
		{"  ��Ҫ������Ʒ��?",17},      //37
		//Added by Andy on Oct 9,2008
	    //{"    ������Ǯ", 12 },       
		{"      �����", 12 },         //38 
		{"  ��Ʒ�۸�:",  11 },         //39
	  //--------------------------------------------------
      //{"  ��Ʒ", 6 },
        {"  ��ѡ��Ʒ��ʱ", 14 },       //40
 	  //{"  ��ѡ��Ʒ", 10 },
	  //{"  ��ѡ��Ʒ��ʱȱ��", 18},    //41	
      //{"  ��Ʒȱ��", 10 },           //41
	    {"ȱ��", 4   },                //41
		{"  ����", 8 },                //42	
		{"  �˱ҽ��:", 11 },          //43
		//{"    ���: ",10 },          //44
        {"  ��ǰ���:", 11 },          //44
        //---------------------------------------------------
        {"  ��ˢ��...", 11 },          //45
        {"  Ͷ��->ѡ��->ȡ��  ", 20 }, //46
      //{"  ѡ��->����->ȡ��  ", 20 }, //47
        {"  ����->ѡ��->ȡ��  ", 20 }, //47
        {"  ������...",    15   }, //48
		{"  ����ʧ��...",      13   }, //49
		{"  �����:",          9    }, //50
		{"  ����...",      13   }, //51
        {"      �ֽ�����",     14   }, //52
		{"      ˢ������",     14   }, //53
		{"  ��ѡ��!",          9    }, //54
        //===================================================
        {"  ������ͣ�ֽ���", 18 }, //55
        {"����: ", 6 },              //56
        {"  �û�����ͣ����", 16    },      //57
        {"  ���ֽ�����", 12    },      //58
        {"��Ҳ��㣬�޷�����", 20   },      //59
        {"������Ʒ���: ", 14 },     //56
	};
#else
	const struct StrAndLen code DispInformationTable[] =
	{
		{"       Welcome", 14 },
		{"Not enough coins", 16 },
		{"Choose goods timeout", 20 },	//2		
		{"Insert a smaller one", 20 },
	//	{"Input goods code:", 17 },//4	
		//{"Make Selection:", 15 },//4
	    {"Make Selection!", 15 },
		{"  ENTER   CANCEL", 16 },	//5
		{"Collect coins", 13 },	//6	
		{"CANCEL", 6 }, //7
		{"Invalid choice", 14 },//8			
		{"ENTER", 5 },//9
		{"  Insert bill/coin", 18 },//10	
	//	{"Price paid:\x24", 12 },//11
		{"Price paid:", 11 },//11
		{"Choose other goods?", 19  },//12	
		{"Hardware error", 14 },//13
		{"      Sellout", 13 },//14	
		{"     Thank you", 14 },//15
		{"Out of service", 14 },//16		
		{"Hopper is wrong", 15 },//17	
		{"Please wait...", 14 },//18	
	//	{"Fund shortage,add?", 18 },
		{"Insufficient fund?", 18 },
		{"Taking the goods", 16 },//20
		{"  Changing", 14 },//21
		{"   Change failed", 16 },//22
		{"    How are you!", 16 },//23
		{"Input other code", 16 },//24
		{"  Input other code", 18 },//25
		{"Take away goods", 15 },//26
		{"  Take away changes", 19 },//27
		{"   Column error", 15 },//28
		{"Select another one?", 19 },//29	
		{"Operation timeout", 17 },//30		
		{"    Refund of fare", 18 },//31		
		{"IOU:", 4 },//32
		{"    Insert coin", 15 },//33	
		{"    Insert bill", 15 },//34		
//		{"NoChange-ExactAmount", 20 }, //35		
		{"Exact change require", 20 }, //35		
		{"EV7736-UB MDB V1.72", 20 },    //36_V1.0-
		{" Buy another one?",17},      //37
		{"Insufficient change",19},    //38//��������
		{"  Price:", 8 },              //39
        {"Column", 6 },                //40
		{"Out", 9 },                   //41
		{"Error", 5 },                 //42
		{"  Change :", 10 },           //43 
		{"  Balance:", 10 },         //44
        //-------------------------------------------
        {"Pls scan the card!", 18 },   //45 
        {"Money->Sel->Goods",  17 },   //46
        {"Sel->Card->Goods",   16 },   //47
		{"Card's balance low", 18 },   //48
		{"Read card fail!",    14 },   //49
		{"  Balance:",         10 },   //50
		{"More money require", 18 },   //51
		{"  Cash trade",       12 },   //52
		{"  Cashless trade",   16 },   //53
		{"  Select the goods", 18 },   //54
		{"Stop trade", 17 },//4	   //55
		{"Input goods code:", 17 },//4	   //56  
		{"   Column error", 15 },//57
        {"   Column unSale", 16 },//58
        {"   Column unSale", 16 },//59
        {"Input goods code:", 17 },//4	   //56  
        //===========================================
	};
#endif

#endif