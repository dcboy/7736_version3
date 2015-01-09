#ifndef __GLOBAL__
#define __GLOBAL__

#define MACHINE_SET_MDB
#define TIME_BILL_STACK     5//3-5
#define WATCHDOGTIMEOUT     120//240
#define _DEBUG_NO_MOBILE    //Added by andy on 2010.12.22
#define SELECTION_NUM       3
#define RACKNUM		        8
#define RACKCOLUMNNUM		8
#define GOODSWAYNUM		    64  

#define HOPPERNUM 		    3
#define VERFYMESSAGELEN 	50
#define ADDONPHONEMAX 		5
#define ONEWAYGOODSNUM 		10  //ÿ��������ʱ����Ʒ����
#define _CHINA_                 //��Ϊ���Ľ������棬�ر�ΪӢ�Ľ�������
#define _SHUPING_              //����Ϊ���� 
#define _SJJ_                  //����Ϊ������


typedef unsigned int  u_int;
typedef unsigned char u_char;
typedef unsigned int  uint_PARALUE;	// ������Ͷ��壬˫�ֽ�һλ����
typedef unsigned long u_long;

//#define _BAOLIAN_ //(COINTYPE)��Ӳ��������ָ��Ӳ�������ͣ��˿�Ϊ����
#define _GUANYU_ //(COINTYPE)��Ӳ��������ָ��Ӳ�������ͣ��˿�Ϊ����
//#define _COIN_INPUT_SERIAL  //�Դ��ڷ�ʽʹ��Ӳ����
#define _COIN_INPUT_PARALLEL  //�Բ��ڷ�ʽʹ�ù���Ӳ����

//#define _MOBILE_SMS_1;		//�ö��Ž���Զ�̹����汾��1.0��

//#define _MOBILE_GPRS;		//��GPRS����Զ�̹���

#define HUINT16(n)				(((n) >> 8) & 0xff)//16λ��ֵ��8λ
#define LUINT16(n)				((n) & 0xff)//16λ��ֵ��8λ	
#define H0UINT32(n)				(((n) >> 24) & 0xff)//32λ��ֵ��һ����8λ
#define H1UINT32(n)				(((n) >> 16) & 0xff)//32λ��ֵ�ڶ�����8λ
#define L0UINT32(n)				(((n) >> 8) & 0xff)//32λ��ֵ��һ����8λ
#define L1UINT32(n)				((n) & 0xff)//32λ��ֵ�ڶ�����8λ

#ifdef _CHINA_
	#define BILLMULTIPLE	1 //100  //ֽ�����ʣ���ֽ����ÿͨ����ʵ����ֵ����	
#else
	#define BILLMULTIPLE	1 //100  //ֽ�����ʣ���ֽ����ÿͨ����ʵ����ֵ����	
#endif

#define COINMULTIPLE 		1 //100   //Ӳ�����ʣ���Ӳ����ÿ�������ʵ����ֵ����,���ڴ��ڹ�����ʽ
#define MONEYMULTIPLE 		1 //100   //��ʾ���ʱ�ľ�ȷ��,1��ʾ��С����(����ԪΪ��λ),10��ʾС�����1λ(����10��Ϊ��λ)��100��ʾС�����2λ(���Է�Ϊ��λ)

#define MENU_COUNT(menu) (sizeof(menu) / sizeof( struct StrAndLen ))

#define MAX_SMS_LIST	10	//���Ŷ��еĳ���

#define MAX_SMS_LEN		160	//��Ϊ��7λ���뷢�ͣ�ÿ���ŵ���󳤶�,byte
//����˱�����Ϊ7λ���룬�ر���Ϊ16λ����
#define SMSENCODE_7_BIT

#define SYS_GOOS_SOLDOUT_CTR    //If need to manage the goods soldout status  
#define GOODSTYPEMAX2        18


struct SYSTEMPARAMETER			// ����ϵͳ��������
{		
	u_char 		RefundPermission;		// �Ƿ�����δ���˱� 1 ��ʾ���� , 0 ��ʾ������		
	u_int 		HopperCoinPrice1;		// �������1��Ӳ����ֵ	
	u_int 		HopperCoinPrice2;		// �������1��Ӳ����ֵ	
	u_int 		HopperCoinPrice3;		// �������1��Ӳ����ֵ
	u_char 		BillNo;		            // �Ƿ���ֽ����
	u_char 		IsMuliVerd;		        // �Ƿ�����ι���
	u_int 		Min;		            //�ٴι������Ͷ�
	u_int 		BanknoteMax;	        //������յ�����Ǯ
	u_int  		DoubtCash;	            //���һ�������ʵ���ֽ�ҽ��
	u_int 		NotOutMax;	            //���һ��Ƿ��Ǯ
    u_char 		MuchOutFlag;            //���һ���Ƿ��ж���Ǯ
	u_char		VmID[5];			    //����ID����
	u_char		GSMNO[16];		       	//���������ֻ�����	
	u_char		MobileON;		        //�Ƿ����ֻ�ģ��
    //----------------------------------------------------
    //Added by Andy on 2010.8.17
    u_char      printerOn;            //open printer
	u_char      printerErrIfService;  //
	u_int       billValue[8];         //The bill value for each channel. If 0, disable the channel.
	u_int       coinValue[6]; 
    u_char      currencyRate;         //Change rate...
    u_char      printMode;            //0: reserved mode; 1:without overprint; 2:overprint;
    u_char      decimal;  
	u_int       curUnit;              //1: 1 dollar; 10: 0.1 dollar--10 cents; 100: 0.01 dollar-- 1 cent;
	u_char      SVC_NoChange;         //
    u_char      GOCOn;                //1: open the GOC device
    u_char      SVC_GOCErr;           //1: service when GOC error
	u_int       tradeTime;	
	u_char      coinOn;
	u_char      busCardOn;
	u_char      BCReadTime;
	//u_char      holdingMode;
    //u_char      holdNoteFive;   //by gzz 20110419
    //u_char      holdNoteTen;    //by gzz 20110419
	u_char      ACDCModule; 
	u_char      CompModule;
	u_char      selItem[GOODSTYPEMAX2];       //Selection item
    //====================================================
	u_char 		Checkbyte;	//У��λ
};


/*���豸״̬0����������λ��1�Ķ����˵��*/
struct DEVICESTATUS
{
	u_char BillAccepter;      //��ֽ����״̬��Bit 7 -- �޴�ģ�飻Bit 6~1 ������Bit 0 -- ���ϣ�
	u_char CoinAccepter;      //��Ӳ����״̬��Bit 7 -- �޴�ģ�飻Bit 6~1 ������Bit 0 -- ���ϣ�
	u_char ChangeUnit1;       //#1�˱�����Bit 7 -- �޴�ģ�飻Bit 6~2 ������Bit 1 -- ȱ�ң�Bit 0 -- ���ϣ�				
	u_char ChangeUnit2;       //#1�˱�����Bit 7 -- �޴�ģ�飻Bit 6~2 ������Bit 1 -- ȱ�ң�Bit 0 -- ���ϣ�				
	u_char ChangeUnit3;       //#1�˱�����Bit 7 -- �޴�ģ�飻Bit 6~2 ������Bit 1 -- ȱ�ң�Bit 0 -- ���ϣ�				
	u_char PickupLED;         //��Դ״̬��Bit 7 -- �޴�ģ�飻Bit 6~1 ������Bit 0 -- ��Դ�������	
	u_char KeyBoard;          //���̣�Bit 7 -- �޴�ģ�飻Bit 6~1 ������Bit 0 -- ���ϣ�
	u_char LCD;               //LCD��Bit 7 -- �޴�ģ�飻Bit 6~1 ������Bit 0 -- ���ϣ�				
	u_char MobileStates;              //�ֻ�ģ�飬Bit 7 -- �޴�ģ�飻Bit 6~1 ������Bit 0 -- ����;
	u_char GOCStatus;                 //
    u_char Selection[SELECTION_NUM];  //
	u_char BusCard;
    u_char ACDCModule;
    u_char Driver64;
};

struct StrAndLen
{
	unsigned char *str;
	unsigned char len;
};

struct RackSet//��������
{
	u_char  RackNo; //��ܱ��
	u_char  UseState;//���ñ�־,0Ϊδ����,1Ϊ����
	u_char	GoodsMax;//����������л����������
};

struct RackColumnSet //ÿ�������������
{
	u_char	ColumnNo;//�������,1--8
	u_char  UseState;//����״̬,0Ϊδ����,1Ϊ����,	
};

////������ṹ�е����л����������õĻ���
struct WaySet //�������� 6byte
{
	u_char  	WayNo;				//�������
	//����״̬�ֽڵĶ���
	//bit0Ϊ0��ʾ������״̬��ȷ��,״̬��ȷ����ָ�����ú�,û�о�������,Ϊ1��ʾ�Ѳ��Թ�,ֻҪ�ǲ������Ҫ�ô�λΪ1;
	//bit1Ϊ0��ʾ����,bit1Ϊ1��ʾ����(2),bit2Ϊ1��ʾȱ��(4),bit3Ϊ1��ʾ������廵(8)
	//bit7��bit6��bit5���ϱ�������λ,����ӦλΪ1ʱ��ʾ��Ӧ�����ѷ��͹�,bit5Ϊ1��ʾȱ��,bit6Ϊ1��ʾ���ϣ�
	u_char 		WayState;	
	u_int		Price;				//����	
	u_char		GoodsCurrentSum;	//��Ʒ�ִ���
	u_char      GoodsType;          //2010.12.16 changed
	u_char      IsUsed;             //1�Ѿ�ʹ�ù�һ����
	
};

////������ṹ�е����л����������õĻ���
struct WayList //������Ŷ�Ӧ�б�ṹ
{
	u_char    GoodsWayNo;//�߼����
	u_char    SetArrayNo;//������
	u_char	  UseState;	 //����ʹ��״̬,0Ϊδʹ��,1Ϊ����
	u_char	  GoodsMax;	 //�����������
};


struct HopperSet //Hopper����ṹ
{
	u_int    price;
	u_char   HopperIndex;
	u_char   HopperState;//1Ϊ����,2Ϊ����
};

struct TRADECOUNTER					// �������в������� 22byte
{		
	//u_long  TrueCurrencySum;   //�������ܵ��ܽ�����, ��λ: ��	
	//u_long  CoinSum;           //�����Ӳ���ܶ�
	u_long  CashSum;	      //�����ֽ���ܶ�
    u_long  CashSumBack;
    u_long  CoinSum5j;
    u_long  CoinSum5jBack;
    u_long  CoinSum1y;
    u_long  CoinSum1yBack;
    u_long  Hopper1Sum;	
    u_long  Hopper1SumBack;
    u_long  Hopper2Sum;	
    u_long  Hopper2SumBack;
    //u_long  TotalSellNum;//120419 by cq TotalSell
    //u_long  TotalSellMoeny;//120419 by cq TotalSell

	//120521 by cq SellAccumulate
	u_long   vpSuccessNum;                    //ȫ����������
	u_long   vpSuccessMoney;                  //ȫ���������
	u_long   vpCashNum;                       //�ֽ��������
	u_long   vpCashMoney;                     //�ֽ�������
	u_long   vpGameNum;                       //��Ϸ�������� 
	u_long   vpCardNum;                       //ˢ����������
	u_long   vpOnlineNum;                     //���߳�������
	
	//------------------------------------------------
	//������������
	//u_char	 offLineFlag;                   //�Ƿ����ߴ��� 
	u_long   offLineNum;                    //���߳�������
	u_long   offLineMoney;                  //���߳������

	
    //============================================   

};

struct TRADELOG//����������ͳ�Ƽ�¼ 7byte
{
	u_char 	WayNo;		    //�������
	u_int   TraceSum;	    //��Ʒ�����ʳ������״�������, u_char-u_int(changed by Andy on 2010.8.19)		
	u_int   DoubtTraceSum;	//��Ʒ�����ʳ������״���������u_char-u_int(changed by Andy on 2010.8.19)		
	u_int  	MoneySum;	    //������ʱ����������ܶ�
	u_int 	TradeSum;       //������ʱ���ʽ��׵��ܽ�����, ��λ: ��	
};

struct SMSMessageList//�����Ķ��Ŷ���
{
	u_char 	SendTime;	//����ʱ��
	u_char  Flag;	//���ڼ�¼������Ҫ�ȼ�ʱ���ֻأ�1����Ҫ�ֻأ�0����Ҫ
	u_char  SMSLen;		//���ų���
	u_char  SMSMessage[MAX_SMS_LEN];	//��������
};

struct PassWordLog//���л�������ͳ�Ƽ�¼ 7byte
{
	u_char passwdlen;		//���볤��
	u_char checkbyte;	//��Ʒ�����ʳ������״���������		
	u_char PassWordByte[10];	//��Ʒ�����ʳ������״���������		
};

extern struct DEVICESTATUS xdata DeviceStatus;
extern struct SYSTEMPARAMETER xdata SystemParameter;

extern struct RackSet	xdata iRackSet[RACKNUM];//��������
extern struct RackColumnSet xdata iRackColumnSet[RACKNUM][RACKCOLUMNNUM]; //ÿ�������������
extern struct WayList xdata InputGoodsWayList[ GOODSWAYNUM ];
extern struct WaySet  xdata GoodsWaySetVal[GOODSWAYNUM];//������������

extern struct TRADECOUNTER xdata TradeCounter;
//extern struct TRADELOG xdata TradeLog[GOODSWAYNUM];//�������Ľ���ͳ��
extern bit data  SystemSave ;//ϵͳ�Ƿ񱣴�
extern unsigned char xdata  GoodsSetSave;//������������

//�����豸������֤�ֽڣ���bitΪ1��ʾ��Ӧ�Ĺ����ѱ���,���嶨��Ϊ��
//bit7��ֽ֤������bit6��֤Ӳ����
//bit0-bit1��֤hopper1,bit0��֤ȱ�ҡ�bit1��֤�豸����,��������
//bit2-bit3��֤hopper2
//bit4-bit5��֤hopper3
extern unsigned char xdata  MoneyDevAlarm;

//�������ϱ�����֤�ֽڣ���bitΪ1��ʾ��Ӧ�Ĺ����ѱ���,���嶨��Ϊ��
//bit0��֤��ͣ����,bit1��֤ϵͳ����У��,bit2��֤��������ʾ��ͨѶ
//bit3��֤���л����޻�,bit4��֤���л�������,
//bit5��֤���л�����������������,bit6��֤���������������ͨѶ����
//bit7����
extern unsigned char xdata  SystemErrorAlarm;//������������

extern struct SMSMessageList xdata SMSMessage[MAX_SMS_LIST];

//extern unsigned char xdata ListIndex;


//--------------------------------------------------------------
//20_140&40_140&60_140
#define SYS_WAIT_NEXT_PULSE 200   //
#define SYS_WAIT_CARD_IN    1500
#define MACHINE_SET_VMC_PC  
//#define VP_PRO_VER          2//1--2�汾����Ϊ2;by gzz 20110823
#define VP_MAC_SET_H        0
#define VP_MAC_SET_L        1

#define KEYEXTRAVAL         0x06
#define GOODSTYPEMAX        18
#define EACHGOODSCOLUMNMAX  48
/*
#ifdef   _SJJ_//������
	#define COLUMN_NUM_SET      56		
#else         //��ͨ����
	#define COLUMN_NUM_SET      48
#endif
*/
extern u_char xdata COLUMN_NUM_SET;

#define GOODSMATRIXMODE
#define GOODS_MATRIX_NONE   0xff
#define SELECTION_VAL_MIN   0
#define SELECTION_VAL_MAX   17
#define DSP_WELCOME_UPDATE  8

#define VP_DSP_INTERVERL    250                 //200-250
#define VP_DSP_TIME1        VP_DSP_INTERVERL
#define VP_DSP_TIME2        VP_DSP_INTERVERL*2


//#define SELECTION_NUM     3
/*
#define INPUTGOODSSUM_2     2
#define INPUTGOODSSUM_3     3
#define INPUTGOODSSUM       INPUTGOODSSUM_3
*/
//The system goods matrix_33 bytes
/*
struct GoodsMatrix
{
	u_char   GoodsType;    //��Ʒ���
	u_int    Price;        //��Ʒ����
	u_char   Status;       //00-ok, !=0 error,
	//u_char   Led;          //
	u_char   ColumnNum;
	//u_char   ColumnMatrix[EACHGOODSCOLUMNMAX];   //Just the GoodsWaySetVal's address.                
	//u_char   NextColumn;                         //FF is none good column left.
};
extern struct GoodsMatrix xdata sysGoodsMatrix[124];
*/

#define VPM_LEN_MAX   250
struct VMC_PC_MSG
{
    u_char   sf;                //fixed with 0xe7
	u_char   len;               //5~250, msg+5
    u_char   datLen;            //
	u_char   verFlag;           //0x01( none response ); 0x81( need response )
    u_char   sn;                //0~255
	u_char   msgType;           //
	u_char   msg[VPM_LEN_MAX];  //0~250
	u_int    chk;
};

#define VPM_COM_TIMEOUT   1500   //1.5s
#define VPM_STA_PWRON     0x00
#define VPM_STA_FIRSTCOM  0x01
#define VPM_STA_GOODSPAR  0x02
#define VPM_STA_COLUMNPAR 0x04
#define VPM_STA_INITOK    0x08
#define VPM_STA_PCPAROK   0x80

#define VPM_DEVUPDATE_BUSCARD   300
#define VPM_DEVUPDATE_CHANGER1  240  //120-240
#define VPM_DEVUPDATE_CHANGER2  240
#define VPM_DEVUPDATE_CHANGER3  240
#define VPM_DEVUPDATE_GOC       180//20-180   
#define VPM_DEVUPDATE_HOPPEREMP 180
#define VPM_DEVUPDATE_TUBEREMOVE 3//30-3;by gzz 20111017 

struct VP_Mission
{
    struct  VMC_PC_MSG  send;
	struct  VMC_PC_MSG  receive;
    u_char  comLock;
	u_int   msTimer1;
	u_int   msTimer2;
    u_int   msTimer3;          //for VP_GameKeyPoll
    u_int   msActTimer;
	u_int   msGameTimer1;
    u_int   sTimer1;
	u_int   sTimer2;
    u_int   billSTimer;
	u_char  sTimerHeart;
	u_char  sTimerOffLine;//����poll
	//u_char  sWeihuTimer;//�˳�ά��ҳ��
    //bit0 - bus card reader
    //bit1 - changer 1
    //bit2 - changer 2
    //bit3 - changer 3
	//bit4 - GOC
	//bit5 -
	//bit6 -
	//bit7 - poll pc first
    u_char  VPDevCtr;     //
	u_int   sTimerBC;
	u_int   sTimerChanger1;
    u_int   sTimerChanger2;
    u_int   sTimerChanger3;
	u_int   sTimerGOC;
	//-----------------------------
	u_char  GoodsRev; //��Ʒ�����´�����Ʒ�������
	//------------------------------------------------------
	u_int   dspTimer1;
	u_char  dspUpdateFlag;
	u_char  coinFull;
    u_char  changeFlag;
    //bit0 - update balance display, after wrong selection
    //bit1 - update balance display and enable the cash devices
    u_char  dspCtr;
	//=======================================================
    u_int   systemErr;
	u_char  sysStatus;                  //
	u_char  PCStatus;
	u_char  VPMode;
	u_char  VPInit;
    u_char  VPMode_Key;
    u_int   comTimer;
	u_char  comErrNum;
    u_char  returnKey;                   //Yes or no
	u_char  gameKey;                     //Yes or no
	u_char  returnKeyLock;               //
	u_char  gameKeyLock;                 //
	u_char  gameLed;                     //On or off
	u_char  key;                         //Selection key
    //u_char  selItem[GOODSTYPEMAX];       //Selection item
    u_int   selPrice[124];      //Selection price
    u_char  columnNum[64];   //Column's storage 
	u_char  columnItem[64];  //Column's item
    u_int   readyLed;                    //
	u_int   redLed;                      //
	u_char  sel1ReadyLed;               //
	u_char  sel1ErrLed;                 //
	u_char  sel2ReadyLed;               //
	u_char  sel2ErrLed;                 //
	u_char  sel3ReadyLed;               //
	u_char  sel3ErrLed;                 //
    //------------------------------------
    u_char  ACDCLedCtr;
    u_char  ACDCCompressorCtr;
    //------------------------------------
	//u_char  proVer;
	u_char  columnNumSet;
	u_char  selectionNumSet;
	u_char  scalFactor;
	u_char  decimalPlaces;//������λ1��,2��,0Ԫ
	//------------------------------------
	u_char  payInDev;
	u_int   payInMoney;
	u_char  payOutDev;
	u_int   payOutMoney1;
	u_int   payOutMoney2;
	u_int   payOutMoney3;
	u_char  payInCoinFlag;
	u_char  payInBillFlag;
	u_int   payInCoinMoney;
	u_int   payInBillMoney;
	u_char  escrowInFlag;
	u_char  escrowOutFlag;
	u_int   escrowMoney;
	u_int   inBillMoney;//Ͷ��ֽ�ҽ��;
	u_int   tubeCoinMoney;//��������;
    //------------------------------------
    u_char  changeCmd;
    u_char  changeDev;
    u_int   changeMoney;
	u_char  changeType;
    //------------------------------------
    //���տ�Ǯ����;by gzz 20110822
    u_char  costCmd;
    u_char  costDev;
    u_int   costMoney;
	u_char  costType;
    //------------------------------------
    //�ϴ�Ƿ������;by gzz 20110825
    u_char  debtType;
    u_char  debtDev;
    u_int   debtMoney;
	//------------------------------------
	u_char  vendGoods;
	u_char  vendSta;
	u_char  vendColumn;
	u_char  vendType;
	u_int   vendCost;
	u_char  vendcolumnLeft;
    u_char  vendCmd;
	u_char  goodsType;
	u_char  goodsType2;
    //------------------------------------
	u_char  request;
	u_char  requestFlag;
	//------------------------------------
	u_char  ADM_Type;
	u_char  ADM_Dat[3];
    //------------------------------------
	u_char  ACT_Type;	
	u_char  ACT_Value;
	//-------------------------------------
	u_char  BUT_Type;
	u_char  BUT_Value;
	//-------------------------------------
	u_char  Action_Type;
	u_char  Action_Value;
	//-------------------------------------
	u_char  STA_CoinA;
	u_int   STA_ChangeNum1;
    u_int   STA_ChangeNum2;
	u_char  STA_BillA;
    u_char  STA_Changer1;
	u_char  STA_Changer2;
	u_char  STA_VMC;
	u_char  STA_Tep1;
	u_char  STA_Tep2;
	u_char  STA_Tep3;
	u_char  STA_Bus;		
	u_char  STA_ICCard;
    u_char  E_Tem1;      //For ACDC module 0xfd������,0xff����,0xfe������
    u_char  E_Tem2;      //For c
    u_char  ESTA_Tem1;
	u_char  ESTA_Tem2;
    //u_int   STA_BillCount;//ֻ���������ϴ�������5��ʱ�����ϱ�;by gzz 20110905
    u_int   STA_ICCardCount;//ֻ���������ϴ�������5��ʱ�����ϱ�;by gzz 20111012
    u_char  Payout_Time;
    //-------------------------------------
    u_char  resetDev;
    u_char  resetCmd;
	//-------------------------------------
	u_char  ctrType;
	u_char  ctrValue;
	u_char  billCoinEnable; 
    //u_char  sTimerHopperEmp;//by gzz 20110502
    //-------------------------------------
	u_char  menuTimer;
	u_char  menuFlag;
	u_char  menuKeyNum;
    u_char  menuKey[5];
    //-------------------------------------
    u_char  hopperComErr[3];
	u_int   hopperTimer;
    u_int   hopperCoinNum;
	u_int   hopperOutTimer;
    //-------------------------------------
    u_int   watchDogTimer;
	u_char  watchDogCtr;
	u_char  watchDogIng;
    //-------------------------------------
    u_char  boughtFlag; 
    //-------------------------------------
    u_char  SystemState;//1�Ƿ��ֽ���״̬
    u_char  hardWareErrShow;//����Ӳ������ֵ��������ʾ
    u_char GOCTestFlag;//���������
	u_int   sTimertubeRemoved;//���ҹ��Ƿ�����;by gzz 20110827
	u_char sTimerTubeUpdate;//���������
	
	//-----------------------------
	u_char infoType;
	u_char  infoErr;//�ϱ��ۻ�������;by gzz 20121226
	//------------------------------
	u_char  ErrFlag;//��һ�ι���ʱ,��Ҫ�ϱ���¼
	u_char  ErrFlag2;//��һ�ι���ʱ,���е�һЩ����
	u_char  DevErrFlag;//�豸����ʱ������Ҫ����ά��ģʽ��������Ҫ�ϱ�һ��
	u_char  adminType;//�Ƿ����ά��ģʽ
	u_char	offLineFlag; //�Ƿ����ߴ��� 
	u_char  returnCmd;  //���㷴Ӧ
	u_char  GoodsWayNum[64];       //Selection item
};
extern struct VP_Mission xdata sysVPMission;
//==============================================================

//--------------------------------------------------------------
#define ITL_TIME_DISABLED_INIT   35    //
#define ITL_TIME_JAMED_DISABLE   30    //

struct ITL_MSG
{
	u_char stx;
	u_char seq;
	u_char len;
	u_char msg[255];
	u_char crcL;
	u_char crcH;
};

struct ITL_Mission
{
    struct ITL_MSG send;
	struct ITL_MSG receive;
	u_char ITLSet;
	u_char crcL;
	u_char crcH;
    u_int  msPoll;
    u_int  msTimer2;
	u_int  sTimer1;
    u_int  sTimer2;     //holding -- credit
	u_char comErrNum;
	u_char status;
	u_char chnCtr1;
	u_char chnCtr2;
    u_char billSta;
    u_char billESta;
    u_char billChn;
	u_int  billValue;
    u_char enableFlag;
    u_char billStaCtr;        //Added 2011.4.13 Andy.
	u_int  billHoldingValue;  //Added 2011.4.13 Andy.
	u_char billHoldingFlag;   //Added 2011.4.13 Andy.
	//
	u_char reEnableFlag;
	u_int  reEnableTime;
    //
    u_char billJamedFlag;
    u_int  billJamedTime;
    //
    u_int  restartTime;
};

extern struct ITL_Mission xdata sysITLMission;
//==============================================================

//--------------------------------------------------------------
#define MDB_MAX_BLOCK_SIZF    36         //���ݿ���󳤶�
//#define MDB_ERR_TIME_OUT    0x81       //��ʱ
//#define MDB_ERR_NO_MODE_BIT 0x82       //δ�յ�����ֽ�
//#define MDB_ERR_CHECKSUM    0x83       //У��ʹ�
#define MDB_ERR_TIME_OUT      0x80       //��ʱ
#define MDB_ERR_NO_MODE_BIT   0x80       //δ�յ�����ֽ�
#define MDB_ERR_CHECKSUM      0x80       //У��ʹ�
#define MDB_ACK 0x00
#define MDB_RET 0xaa
#define MDB_NAK 0xff

struct MDB_Mission
{
    u_char port0_counter;                //����0�յ��ֽڼ���
    u_int  MDBMSTimer;
	u_char modeBit;
    u_char buff[MDB_MAX_BLOCK_SIZF];     //����0�յ��ֽڻ���
	u_char billBuf[MDB_MAX_BLOCK_SIZF];
    u_char coinBuf[MDB_MAX_BLOCK_SIZF];
	u_char Pc_billBuf[MDB_MAX_BLOCK_SIZF];
    u_char Pc_coinBuf[MDB_MAX_BLOCK_SIZF];
	u_char billIDENTITYBuf[MDB_MAX_BLOCK_SIZF];
    u_char coinIDENTITYBuf[MDB_MAX_BLOCK_SIZF];
    u_char billBufLen;
    u_char coinBufLen;
	u_char billType;
	u_char coinType;
	u_char coinStock;   //
	u_char billStock;
    u_char billDeviceStatus;
    u_char coinDeviceStatus;    //bit0(com error)
    u_char billIsEnable;
    u_char coinIsEnable;    //bit0=1����Ŀǰ��ʹ�ܵ�;by gzz 20110920
    u_int  coin5jNum;
    u_int  coin1yNum;
    u_int  coin5jValue;
    u_int  coin1yValue;
    u_int  coinAllValue;
	u_int  payout5jNum;
	u_int  payout1yNum;
    u_char returnKeyFlag;    //return key pressed
    u_char returnCmdFlag;    //return key pressed
    u_char returnBilFlag;    //return bill
    u_char tubeRemoved;      //�ҹ��Ƿ�û������;by gzz 20110827
    u_char billIsFull;      //�ж�ֽ�����Ƿ�������;by gzz 20111017 
    u_char billCashBuf;     //�����Ƴ�������;by gzz 20121224
    u_char billOthErr;     //ֽ������������bit0:motor,bit1:sensor,bit2:chksum,bit3:jammed,bit4:disabled,bit5:cashErr
    u_char coinOthErr;     //Ӳ������������bit0:sensor,bit1:tubejam,bit2:romchk,bit3:routing,bit4:jam,bit5:removeTube
   
};
extern struct MDB_Mission xdata sysMDBMission;

//==============================================================

//--------------------------------------------------------------
struct  BC_MSG
{
	u_char stx;
	u_char len;
	u_char msg[255];
	u_int  crc;
	u_char etx;
};

struct BC_Mission
{
    struct BC_MSG  send;
	struct BC_MSG  receive;
	//-----------------------
    u_int  msPoll;
    u_int  msTimer2;
	u_char comErrNum;
	//------------------------
	u_char recACK;
	u_char recDatLen;
    u_long balance;
    //------------------------
    u_char msgLen;
    u_char msgBuf[255];

};
extern struct BC_Mission xdata sysBCMission;

////������ṹ�б������л�������ѭ��������ù��ϴ���
struct COLUMNTEST 
{
    u_int   testNum;  
	u_char  WayNo[GOODSWAYNUM];				//�������		
	u_int	BreakCount[GOODSWAYNUM]; 		//���ϴ���			
};
extern struct COLUMNTEST xdata WayCheck;
//==============================================================

#endif





