#ifndef __ITL_H__
#define __ITL_H__

#define ITL_ERR_NULL     0
#define ITL_ERR_PAR      1   //mission parameter error
#define ITL_ERR_COM      2   //communication error

#define ITL_MSG_STX     0x7F
#define ITL_MSG_SEQ_0   0x00
#define ITL_MSG_SEQ_1   0x80

#define ITL_TIME_POLL     20     //30, 15,  10,  20(2011.4.13), 10, 20
#define ITL_TIME_OUT      100    //50, 100, 150, 1000, 100   
#define ITL_TIME_OUT_NUM  3      //1,3 
#define ITL_TIME_CMD_INTEVEL     100   //800-100
#define ITL_TIME_CMD_INTEVEL_1   20    //200-20
#define ITL_TIME_STACK    15     //3, 8(2011.4.26: wait more time for NV9), 15
#define ITL_TIME_REJECT   3
#define ITL_COM_RETRY     0      //0,1
#define ITL_COM_DELAY     1      //10,1
#define ITL_TIME_RESTART  30    //30 seconds or more time


/*
#define ITL_ACK_OK            0xf0    //+0
#define ITL_ACK_READ          0xef    //+Chn, 
#define ITL_ACK_STACKING      0xcc    //+0
#define ITL_ACK_CREDIT        0xee    //+Chn, valid sign
#define ITL_ACK_STACKED       0xeb    //+0
#define ITL_ACK_REJECTING     0xed    //+0
#define ITL_ACK_REJECTED      0xec    //+0
#define ITL_ACK_SJAM          0xea    //+0
#define ITL_ACK_UJAM          0xe9    //+0
*/

#define ITL_BILL_NULL         0x00
#define ITL_BILL_READ         0x01    //EF+chn(0 or valid chn)
#define ITL_BILL_STACKING     0x02    //CC+NULL
#define ITL_BILL_CREDIT       0x04    //EE+chn...
#define ITL_BILL_STACKED      0x08    //EB+NULL
#define ITL_BILL_REJECTING    0x10    //ED+NULL
#define ITL_BILL_REJECTED     0x20    //EC+NULL
#define ITL_BILL_SJAM         0x40    //
#define ITL_BILL_UJAM         0x80

//sysITLMission.billSta
//ITL_BILL_READ
//ITL_BILL_CREDIT
#define ITL_BILL_VEDNING      0x80

#define ITL_BILL_E_NCFFAR     0x01
#define ITL_BILL_E_NCICBAR    0x02
#define TIL_BILL_E_FATTN      0x04
#define ITL_BILL_E_CBREM      0x08
#define ITL_BILL_E_CBREP      0x10
#define ITL_BILL_E_STAFULL    0x20
#define ITL_BILL_E_DISABLED   0x40
#define ITL_BILL_E_FAIL       0x80

#define ITL_DEV_NULL          0x00
#define ITL_DEV_RESET         0x01
#define ITL_DEV_DISABLED      0x02
//
#define ITL_DEV_NCFFAR        0x04
#define ITL_DEV_NCICBAR       0x08
#define ITL_DEV_CBREM         0x04
#define ITL_DEV_CBREP         0x08
//
#define ITL_DEV_STAFULL       0x10
#define ITL_DEV_FATTN         0x20
#define ITL_DEV_FAIL          0x40


#define ITL_CMD_RESET         0x01
#define ITL_CMD_SETINHIBITS   0x02
#define ITL_CMD_DSPON         0x03
#define ITL_CMD_DSPOFF        0x04
#define ITL_CMD_SETUP         0x05
#define ITL_CMD_HOSTVERSION   0x06
#define ITL_CMD_POLL          0x07
#define ITL_CMD_REJECT        0x08
#define ITL_CMD_DISABLE       0x09
#define ITL_CMD_ENABLE        0x0a
#define ITL_CMD_PROGRAM       0x0b
#define ITL_CMD_GETSN         0x0c
#define ITL_CMD_SLAVEVERSION  0x0d
#define ITL_CMD_CHNVALUE      0x0e
#define ITL_CMD_CHNSEQURITY   0x0f
#define ITL_CMD_CHNRETEACH    0x10
#define ITL_CMD_SYN           0x11
#define ITL_CMD_COINROUTE     0x12
#define ITL_CMD_REJECTCODE    0x17
#define ITL_CMD_HOLD          0x18
#define ITL_CMD_VERSIONEVENT  0x19
//...
#define ITL_CMD_MANUFACTURES  0x30

#define ITL_CMD_MIN  ITL_CMD_RESET
#define ITL_CMD_MAX  ITL_CMD_MANUFACTURES

#define ITL_ACK_STACKING      0xcc    //+0
#define ITL_ACK_BCTA          0xd1
#define ITL_ACK_NCFFAR        0xe1
#define ITL_ACK_NCICBAR       0xe2
#define ITL_ACK_CBREM         0xe3
#define ITL_ACK_CBREP         0xe4
#define ITL_ACK_BCTV          0xe5
#define ITL_ACK_FATTN         0xe6
#define ITL_ACK_STAFULL       0xe7    //+0
#define ITL_ACK_DISABLED      0xe8    //+0

#define ITL_ACK_UJAM          0xe9    //+0
#define ITL_ACK_SJAM          0xea    //+0
#define ITL_ACK_STACKED       0xeb    //+0
#define ITL_ACK_REJECTED      0xec    //+0
#define ITL_ACK_REJECTING     0xed    //+0
#define ITL_ACK_CREDIT        0xee    //+Chn, valid sign
#define ITL_ACK_READ          0xef    //+Chn, 
#define ITL_ACK_OK            0xf0    //+0
#define ITL_ACK_RESET         0xf1
#define ITL_ACK_CMDERR        0xf2
#define ITL_ACK_PARERR        0xf3
#define ITL_ACK_CMDAPL        0xf5
#define ITL_ACK_SOFERR        0xf6
#define ITL_ACK_CHKERR        0xf7
#define ITL_ACK_FAIL          0xf8
#define ITL_ACK_KEYERR        0xfa

#define ITL_ACK_MIN   ITL_ACK_STACKING
#define ITL_ACK_MAX   ITL_ACK_KEYERR 

extern void ITLUpdateCrc( const unsigned char num );
extern void ITLResetCrc( void );
extern void ITLChnCtr();
extern void ITLSerialInit( void );
extern unsigned char ITLBusUnpack( void );
extern unsigned char ITLBusTxMsg( void );
extern unsigned char ITLMsgPackSend( unsigned char msgType, unsigned char flag );


extern unsigned char ITLMission_Syn( void );
extern unsigned char ITLMission_Setup( void );
extern unsigned char ITLMission_SetInhibit( void );
extern unsigned char ITLMission_Reset( void );
extern unsigned char ITLMission_Dspon( void );
extern unsigned char ITLMission_Dspoff( void );
extern unsigned char ITLMission_Hold( void );
extern unsigned char ITLMission_Enable( void );
extern unsigned char ITLMission_Disable( void );
extern unsigned char ITLMission_Reject( void );
extern unsigned char ITLMission_Poll( void );
extern unsigned char ITLMission_Init_1( void );
extern unsigned char ITLMission_Init( void );
extern unsigned char ITLMission_HB_Stack( void );
extern unsigned char ITLMission_HB_Reject( void );

//---------------------------------------------------------------------------------------------
//---------------------MDB interface-----------------------------------------------------------
extern void MDBSerialInit( void );
extern unsigned char Session(unsigned char add,unsigned char const dat[ ],unsigned char count);

//ֽ�һ�����
extern unsigned char MDBMission_Bill_Init( void );
//Ϊֽ�������Ե��õ�ֽ�һ�����
//extern unsigned char MDBMission_Bill_InitForTest( void );
//ֽ�һ�ʹ��
extern unsigned char MDBMission_Bill_Enable( void );
//ֽ�һ�����
extern unsigned char MDBMission_Bill_Disable( void );

//Ӳ�һ�����
extern unsigned char MDBMission_Coin_Init( void );
//Ӳ����ʹ��
extern unsigned char MDBMission_Coin_Enable(void);
//Ӳ��������
extern unsigned char MDBMission_Coin_Disable(void);  
extern unsigned char MDB_Coin_Poll_API( void );
extern unsigned char MDB_Bill_Poll_API( void );
//------------------------------------------------------------------------------

//-------------------------------------
//-------------------------------------
//ֽ�һ���λ��
//0x80: comms error
//0x00: ok
//Reset ����
extern unsigned char MDB_Bill_Reset( void );  

//-------------------------------------
//------------------------------------
//Setup ����
extern unsigned char MDB_Bill_Setup( unsigned char *buf, unsigned char *len );

//0x80 = com error
//0x00 = ok
//��ѯ
extern unsigned char MDB_Bill_Poll(unsigned char *buf, unsigned char *len);
  
//0x80 = com error
//0x00 = not, 0x01=stacked,0x02=����״̬��
//�Ƿ���ѹ��
extern unsigned char MDB_Bill_IfStacked( unsigned char *buf, unsigned char *len );
 
//0x80 = com error
//0x00 = not, 0x01=secrow,0x02=����״̬��
//�Ƿ��ݴ�ֽ��
extern unsigned char MDB_Bill_IfSecrow( unsigned char *buf, unsigned char *len, unsigned char *billType );  

//------------------------------------
//0x80 = com error
//0x00 = not, 0x01=returned,0x02=����״̬��
//�Ƿ����˱�
extern unsigned char MDB_Bill_IfReturned( unsigned char *buf, unsigned char *len, unsigned char *billType );  

//------------------------------------
//0x80 = com error
//0x00 = not, 0x01=DBReject,0x02=����״̬��
//�Ƿ��˳�������ֽ��
extern unsigned char MDB_Bill_IfDBReject( unsigned char *buf, unsigned char *len, unsigned char *billType );
  
//-------------------------------------
//------------------------------------
//ѹ�����˳�����
//0x80: comms error
//0x00: ok
extern unsigned char MDB_Bill_EscrowCtr( unsigned char control );
  
//ֽ�����Ϳ��ƣ�����ֽ��ʹ�����ݴ湦��
//0x80: comms error
//0x00: ok
extern unsigned char MDB_Bill_Type( unsigned char enable1, unsigned char enable2, unsigned char escrow1, unsigned char escrow2 );  
//-------------------------------------
//����״̬��ѯ�����䱻ȡ�������豸�ϵ縴λ��ֽ�������ᱻ���� ��
//0x80: comms error
//0x00: ok
//(Fxxxxxxx)  (xxxxxxxx) 
//F = 1 if stacker is full, 0 if not.
//xxxxxxxxxxxxxxx  =  The number of bills in the stacker.
extern unsigned char MDB_Bill_Stacker( unsigned char * dat1, unsigned char *dat2 );
//------------------------------------------------------------------------------

extern unsigned char MDB_Bill_EXP_Identification(unsigned char *buf, unsigned char *len);


//Ӳ��������
//extern unsigned char MDB_Coin_Disable(void);  
//------------------------------------------------------------------------------
//Reset ����
//0x80 = com error
//0x00 = ok
extern unsigned char MDB_Coin_Reset(void);
//------------------------------------------------------------------------------
//Setup ����
//0x80 = com error
//0x00 = ok
extern unsigned char MDB_Coin_Setup(unsigned char *buf,unsigned char *len);
//------------------------------------------------------------------------------
//��ѯ�������ұҶ��ĵ�ǰ״̬
//After reset more 500 ms, 
//0x80: comms error
//0x00: ok
extern unsigned char MDB_Coin_TubeSta(unsigned char *buf,unsigned char *len);
//------------------------------------------------------------------------------
//��ѯ
//0x80 = com error
//0x00 = ok
extern unsigned char MDB_Coin_Poll(unsigned char *buf,unsigned char *len);
//------------------------------------------------------------------------------
//�Ƿ��˱�
//0x80 = com error
//0x00 = not, 0x01=dispensed, 0x02=����״̬��
extern unsigned char MDB_Coin_IfDispensed(unsigned char *buf,unsigned char *len,unsigned char *coinType,unsigned char *coinDispensedNum,unsigned char *coinStock);
//------------------------------------------------------------------------------
//�Ƿ���յ�Ӳ��
//0x80 = com error
//0x00 = not, 0x01=escrow, 0x02=����״̬��
extern unsigned char MDB_Coin_IfDeposited(unsigned char *buf,unsigned char *len,unsigned char *coinType,unsigned char *coinStock ); 
//------------------------------------------------------------------------------
//Ӳ�����Ϳ��ƣ���ͨ��Ӳ���ձ����˱�������
//0x80: comms error
//0x00: ok
extern unsigned char MDB_Coin_Type(unsigned char typeCtr1,unsigned char typeCtr2,unsigned char dispenseCtr1,unsigned char dispenseCtr2);
//------------------------------------------------------------------------------
//�ֶ��ұ�
//0x80: comms error
//0x00: ok
//Ӳ����,ֽ��������,���������˱���
extern unsigned char MDB_Coin_HopperEnable(void);
//------------------------------------------------------------------------------
//�ֶ��ұ�
//0x80: comms error
//0x00: ok
extern unsigned char MDB_Coin_Dispense( unsigned char type, unsigned char num );

extern unsigned char MDB_Coin_EXP_Identification(unsigned char *buf, unsigned char *len);

//------------------------------------------------------------------------------
//0x80: comms error
//0x00: ok
//z1-z33
extern unsigned char MDB_Coin_EXP_Identification(unsigned char *buf, unsigned char *len);
//------------------------------------------------------------------------------
//0x80: comms error
//0x00: ok
//none
extern unsigned char MDB_Coin_EXP_FeatureEnable(unsigned char dat1,unsigned char dat2,unsigned char dat3,unsigned char dat4);
//------------------------------------------------------------------------------
//0x80: comms error
//0x00: ok
//none
extern unsigned char MDB_Coin_EXP_Payout(unsigned char dat);
//------------------------------------------------------------------------------
//0x80: comms error
//0x00: busy, none coin payouted
//0x01: There is/are coin(s) payouted
extern unsigned char MDB_Coin_EXP_PayoutStatus(unsigned char *buf,unsigned char *len);
//------------------------------------------------------------------------------
//0x80: comms error
//0x00: ACK(Payout finished)
//0x01: There is/are coin(s) payouted  
extern unsigned char MDB_Coin_EXP_PayoutValuePoll(unsigned char *dat);

//------------------------------------------------------------------------------
//0x80: comms error
//0x00: ACK
//0x01: Get status finished
//���ұҹ��Ƿ�û������;by gzz 20110825
extern unsigned char MDB_Coin_EXP_TubeRemoved(void);


extern unsigned char MDB_Coin_TubeSta_API( void );
 
//=============================================================================================

#endif   //__ITL_H__
