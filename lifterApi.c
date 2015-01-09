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
#include "IOInput.h"
#include "communication.h"

#include "Serial1.h"
#include "scheduler.h"

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "stdarg.h"



//VMC֪ͨGCC��λ��ʼ��
#define VMC_RESET_REQ				(0x80)
//VMC֪ͨGCC����GCC״̬
#define VMC_STATUS_REQ				(0x81)
//VMC֪ͨGCC����
#define VMC_VENDING_REQ				(0x82)
//VMC֪ͨGCC����������
#define VMC_VENDINGRESULT_REQ		(0x83)


//GCC֪ͨVMC��λ��ʼ��
#define GCC_RESET_ACK				(0x00)
//GCC֪ͨVMC����GCC״̬
#define GCC_STATUS_ACK				(0x01)
//GCC֪ͨVMC����
#define GCC_VENDING_ACK				(0x02)
//GCC֪ͨVMC����������
#define GCC_VENDINGRESULT_ACK		(0x03)
//GCC֪ͨVMC����
#define GCC_OPENDOOR_ACK			(0x04)
//GCC֪ͨVMC����
#define GCC_CLOSEDOOR_ACK			(0x05)
//GCC֪ͨVMC��������
#define GCC_OPENLIGHT_ACK			(0x06)
//GCC֪ͨVMC�ر�������
#define GCC_CLOSELIGHT_ACK			(0x07)
//GCC֪ͨVMC�������ò���
#define GCC_GETINFO_ACK				(0x08)




//��������
#define CHANNEL_OUTGOODS		(1)
//��������ǰ״̬			
#define CHANNEL_CHECKSTATE		(2)
//�������ϴεĳ������			
#define CHANNEL_CHECKOUTRESULT	(3)	
//���sn
#define CHANNEL_CLEARSN			(4)



static struct COMMTASK xdata lifterTask,ackTask;
uchar lifterSendMsg(unsigned char type,uchar binNo,uchar rowNo,uchar columNo);
uchar LifterVendoutTask(struct COMMTASK xdata*liftPtr);
uint LifterCheckStateTask(uchar binNo,uchar *errNo);
uchar LifterVendout(uchar binNum,uchar logicNo);













	


void lifterDelay(unsigned long timeout)
{
	lifterTimer = timeout / 10;
	while(lifterTimer);
}



/*****************************************************************************
** Function name:	ZhkLifterRxMsg	
** Descriptions:	      ���մ��ڻ�Ӧ��													 			
** parameters:		��
** Returned value:	0:�����ݽ��� 1:������� 2:���ݽ��մ���
*****************************************************************************/
u_char ZhkLifterRxMsg( void )
{
	
	uchar i,index = 0,rcx = 50;
	uint crc;
	memcpy( &ackTask, &CurrentTask, sizeof( struct COMMTASK ) );
	while(rcx)
	{
		if(ZhkSerial1IsRxBufNull())//������ ��Ҫ��ʱ�ȴ�һ��
		{
			for(i = 0;i < 10;i++)
			{
				i = i;
			}
			rcx--;
		}
		else
		{
			ackTask.Param[index] = ZhkSerial1GetCh();
			if(index == 0)
			{
				//�жϰ�ͷ
				if(ackTask.Param[0] != 0xC8)//head err
					continue;
			}
			else if(index == 1)
				ackTask.ParamLen = ackTask.Param[index];
			index++;
			if(index >= 7)
			{
				crc = CrcCheck(ackTask.Param,ackTask.ParamLen);
				return 1;
#if 0
				if(ackTask.Param[index - 2] == crc / 256 && ackTask.Param[index-1] == crc % 256)
					return 1;
				else
					return 2;
#endif
			}
			
		}
	}
	
	if(index)
		return 2;
	else
		return 0;
	
	
}




/*********************************************************************************************************
** Function name:     	ZhkLifterTxMsg
** Descriptions:	       ���������ʹ���
** input parameters:    
** output parameters:   ��
** Returned value:      CRC������
*********************************************************************************************************/
bit ZhkLifterTxMsg( struct COMMTASK xdata* NewTask )
{
	uchar i,len;
	uint  crc;
	len = NewTask->Param[1];
	crc	= CrcCheck(NewTask->Param,len);//��У��
	NewTask->Param[len] = (uchar)(crc >> 8);
	NewTask->Param[len + 1] = (uchar)(crc & 0xFF);
	for(i = 0;i < len + 2;i++)
	{	
		ZhkSerial1PutCh( NewTask->Param[i]);
	}
	
	return 1;	
}

//////////////////////////////////////////////////////////
///��������1��ʾ
//////////////////////////////////////////////////////////
bit  ZhkLifterTask( struct COMMTASK xdata* TaskTemp )
{
	switch( ZhkSchedulerState )
	{
	case TASK_NULL:
		break;
	case TASK_REDAY:	//���ʹ�������
		ZhkChannelSwitch( EQUIP_CHANNEL );	
		if(TaskTemp->Cmd == VMC_VENDING_REQ)//��������һ������
		{
			Channel.State = LifterVendoutTask(TaskTemp);
			ZhkSchedulerState = TASK_FINISH;
		}
		else
		{
			ZhkLifterTxMsg( TaskTemp );
			ZhkSchedulerState = TASK_WAIT;
			ZhkDownMsgAckTimer  = 500;//15�� �ȴ�
			Channel.CommState = COMM_BUZY;
			Channel.ExtState[2] = 0;
		}
		
		break;	
	case TASK_WAIT:
		if(!ZhkSerial1IsRxBufNull())//������
		{
			ZhkSchedulerState = TASK_FINISH;
			Channel.State = ZhkLifterRxMsg();
			break;
		}
		
		if ( ZhkDownMsgAckTimer == 0 )//��ʱ
		{
			ZhkSchedulerState = TASK_ERROR;					
		}		
		break;			
	case TASK_FINISH:
		ZhkSchedulerState = TASK_NULL; 		
		Channel.CommState   = COMM_COMMOK;
		memset( &CurrentTask, 0, sizeof( struct COMMTASK ) );
		ZhkDownMsgAckTimer = 0;
		break;
	case TASK_ERROR:
		Channel.CommState = COMM_TIMEOUT;
		ZhkSchedulerState   = TASK_NULL; 
		memset( &CurrentTask, 0, sizeof( struct COMMTASK ) );
		break;
	default:
		ZhkSchedulerState = TASK_NULL;
		
	}
	return 1;
}

/*****************************************************************************
** Function name:	LifterSendVendout	
** Descriptions:	      	���ͳ�����ѯ�������													 			
** parameters:		binNo:���
** Returned value:	�Ͱ�λ  0:��ѯʧ�� 1:������� 2:���ڳ���
								0xFF:ͨ�Ź��� 
					

					�߰�λ ��"����ʧ�� �����ֶ���Ч"
					0:�����ɹ�
					1:���ݴ���
					2:�޻�				3:����
					4:ȡ����û����
					5:����δȡ�� 		6:������ű�����
					7:����������  	other:��������
*****************************************************************************/
uint LifterSendCheckRst(uchar binNo)
{
	uchar rst = 0;
	rst = lifterSendMsg(VMC_VENDINGRESULT_REQ,binNo,0,0);
	if(rst == 0)
		return 0xFF;
	if(ackTask.Param[4] == GCC_VENDINGRESULT_ACK)//�ɹ��յ�ACK
	{	
		if(ackTask.Param[5] == 0x01)//���ڳ���
			return 2;
		else
		{
			if(ackTask.Param[6] == 0x00)//�����ɹ�
				return 1;
			else
				return (((uint)ackTask.Param[7] << 8)| (0x01));
		}
	}
	return 0;
	
}



/*****************************************************************************
** Function name:	LifterSendCheckState	
** Descriptions:	      	���Ͳ�ѯ״̬����													 			
** parameters:		binNo:���
** Returned value:	�Ͱ�λ0�������� 1����æ2��ѯʧ��0xFFͨ��ʧ��
					�߰�λ(��λ����1��ʾ�й���)
					bit0 ����״̬����
					bit1����������
					bit2ȡ���������
					bit3�û��綯�Ź���
					bit4���һ�������
					bit5����ģ�����
					bit6��������������
					bit7�������Ź���
*****************************************************************************/
uint LifterSendCheckState(uchar binNo)
{
	uchar rst = 0,state,errNo = 0,rcx = 2;
	while(rcx--)
	{
		rst = lifterSendMsg(VMC_STATUS_REQ,binNo,0,0);
		if(rst == 0)
			continue;		
		if(ackTask.Param[4] == GCC_STATUS_ACK)//�ɹ��յ�ACK
		{	
			state = (ackTask.Param[5] == 0x01) ? 1 : 0;//������־ 0���� 1æ
			errNo |= (ackTask.Param[6] & 0x01) << 0;//����״̬
			errNo |= (ackTask.Param[7] & 0x01) << 1;//������
			errNo |= (ackTask.Param[8] & 0x01) << 2;//ȡ�����
			errNo |= (ackTask.Param[9] & 0x01) << 3;//�û��綯��
			errNo |= (ackTask.Param[10] & 0x01) << 4;//���һ���
			errNo |= (ackTask.Param[11] & 0x01) << 5;//����ģ��
			errNo |= (ackTask.Param[12] & 0x01) << 6;//����������
			errNo |= (ackTask.Param[13] & 0x01) << 6;//��������	
			
			return (((uint)errNo << 8) | state);
			
		}
		return 2;
	}

	return 0xFF;
	
}



/*****************************************************************************
** Function name:	LifterSendVendout	
** Descriptions:	      	���ͳ�������													 			
** parameters:		binNo:���
					rowNo:���
					columnNo:����
** Returned value:	0:����ʧ��; 1:���ͳɹ�;0xFF ͨ��ʧ��
*****************************************************************************/
uchar LifterSendVendout(uchar binNo,uchar rowNo,uchar columnNo)
{
	uchar rst = 0,rcx = 2;
	while(rcx--)
	{
		rst = lifterSendMsg(VMC_VENDING_REQ,binNo,rowNo,columnNo);
		if(rst == 0)
			return 0xFF;
		if(ackTask.Param[4] == GCC_VENDING_ACK)//�ɹ��յ�ACK
		{
			return 1;
		}
		//���û���յ�ACK����Ҫ�ڷ���һ�β�ѯ����
		//ȷ����������ͳɹ������ظ����ͳ�������
		if(LifterSendCheckRst(binNo) == 2)//��ʾ������æ ͬ����ζ�ų�������ͳɹ�
			return 1;
	}
	return 0;
}


/*****************************************************************************
** Function name:	lifterSendMsg	
** Descriptions:													 			
** parameters:		type:��������
					binNo:�����
					rowNo:����
					columNo:������					
** Returned value:	0:ͨ��ʧ��; 1:ͨ�ųɹ�;
*****************************************************************************/
uchar lifterSendMsg(unsigned char type,uchar binNo,uchar rowNo,uchar columNo)
{
	uchar timeout = 0,comOK = 0,index = 0;
	uchar devType = 0x40;//��ͨ������ 
	binNo = binNo;
	memset( &lifterTask, 0, sizeof( struct COMMTASK ) );
	Channel.CommState   = COMM_BUZY;
	lifterTask.Id 		= ID_CHANNEL;
	lifterTask.Cmd 		= type;
	lifterTask.Priority = PRIORITY_NORMAL; 

	lifterTask.Param[index++] = 0xC7;
	lifterTask.Param[index++] = 0x05;//����
	lifterTask.Param[index++] = devType;
	lifterTask.Param[index++] = 0x00;//�汾�̶�0
	lifterTask.Param[index++] = type;
	if(rowNo != 0x00)
		lifterTask.Param[index++] = rowNo;
	if(columNo != 0x00)
		lifterTask.Param[index++] = columNo;

	lifterTask.ParamLen	= index;
	lifterTask.Param[1] = index;//�����ض�λ

	ZhkSchedulerAddTask( &lifterTask );
	while(! ( timeout || comOK ))
	{
		WaitForWork( 50, NULL );
		timeout = TestDeviceTimeOut( &Channel );
		comOK = TestDeviceCommOK( &Channel );	
	}

	if(timeout)
		return 0;
	if(comOK)
		return (Channel.State == 1);	
	return 0;


}



/*****************************************************************************
** Function name:	LifTerProcess	
** Descriptions:														 			
** parameters:		��				
** Returned value:	01:�ɹ�
					11:���ݴ��� 
					12:�޻�
					13:����		  
					14:ȡ����û����
					15:����δȡ��
					16:������ű���
					17:������������
					21:��������
					22:����������
					23:ȡ���������
					24:�û��綯�Ź���
					25:���һ�������
					26:����ģ�����
					27:��������������
					28:�������Ź��
					51:״̬��ѯ��ʱ
					52:���������ʧ��
					53:���������ѯ��ʱ
					99:��������
					255(0xFF):ͨ��ʧ��
*******************************************************************************/
uchar LifTerProcess(uchar binNum,uchar logicNo)
{
	uchar Result[36]={0},res = 0,rcx = 5;
	uchar rowNo = 0,columnNo = 0,stateH,stateL;
	unsigned short takeTimeOut = 10,vendoutTimeout;
	uint liftState;
	if(logicNo == 0x00)
		return 0xff;
	rowNo = logicNo / 10 ;
	columnNo = logicNo % 10;
	
	//��ʼ���� //��ѯ״̬�Ƿ���������������
	rcx = 10;
	while(rcx--)
	{
		liftState = LifterSendCheckState(binNum); 
		stateL = liftState & 0xFF;
		stateH = (liftState >> 8) & 0xFF;
		if(stateL == 0)//����������
			break;
		else if(stateL == 0xFF)//ͨ��ʧ��
		{
			return 0xFF;
		}
		else 
		{
			if(stateH & 0xFF)//�й���
			{
				if(stateH & 0x01) return 21;
				if(stateH & 0x02) return 22;
				if(stateH & 0x04) return 23;
				if(stateH & 0x08) return 24;
				if(stateH & 0x10) return 25;
				if(stateH & 0x20) return 26;
				if(stateH & 0x40) return 27;
				if(stateH & 0x80) return 28;
				return 99;
					
			}
		}
		WaitForWork( 1000, NULL );
	}

	if(liftState != 0)//��ʱ��ѯ��Ȼ������
		return 51;
	
	while(1)
	{
		//���г�������
		res = LifterSendVendout(binNum,rowNo,columnNo);
		if(res == 0 || res == 0xFF)
			return 52;
		
		WaitForWork(50, NULL );
		//5000 * 10  = 50000 
		vendoutTimeout = 100 +(8 - rowNo) * 10;//�����������ʱ
		while(vendoutTimeout--)
		{	
			liftState = LifterSendCheckRst(binNum);//���������
			if((liftState & 0xFF) == 0x01)//�������
			{
				break;
			}
			WaitForWork( 1000, NULL );
		}
		
		if(vendoutTimeout)
		{
			if((liftState & 0xFF00))//����ʧ��
			{
				if((((liftState >> 8) & 0xFF) == 5) && takeTimeOut)//��δȡ��
				{
					WaitForWork( 2000, NULL );
					takeTimeOut--;
					continue;
				}
				stateH = (liftState >> 8) & 0xFF ;
				return ((stateH > 7) ? (stateH + 10) : 99);
			}	
			else//�����ɹ�
				return 1;
		}
		else										   	
			return 53;		
	}
//	return 0xFF;
}



uchar LifterVendoutReturn(uchar res,uchar flag)
{
	uchar val = 0;
	switch(res)
	{
		case 1:
#ifdef _CHINA_
			if(flag == 1)
			DisplayStr( 0, 1, 1, "�����ɹ�", sizeof("�����ɹ�") );
#endif
			val = 0;
			break;
		case 11:
#ifdef _CHINA_
			if(flag == 1)
			DisplayStr( 0, 1, 1, "���ݴ���", sizeof("���ݴ���") );
#endif
			//DisplayStr( 0, 1, 1, "Err data", sizeof("Err data") );
			
			val = 11;
			break;
		case 12:
#ifdef _CHINA_	
			if(flag == 1)
			DisplayStr( 0, 1, 1, "�����޻�", sizeof("�����޻�") );
			//DisplayStr( 0, 1, 1, "No goods", sizeof("No goods") );
#endif
			val = 3;
			break;
		case 13:
			#ifdef _CHINA_
			if(flag == 1)
			DisplayStr( 0, 1, 1, "��������", sizeof("��������") );
			//DisplayStr( 0, 1, 1, "Ka Huo", sizeof("Ka Huo") );
			#endif
			val = 13;
			break;
		case 14:
			#ifdef _CHINA_
			if(flag == 1)
			DisplayStr( 0, 1, 1, "ȡ����û����", sizeof("ȡ����û����") );
			//DisplayStr( 0, 1, 1, "Ka Huo", sizeof("Ka Huo") );
			#endif
			val = 14;
			break;
		case 15:
			#ifdef _CHINA_
			if(flag == 1)
			DisplayStr( 0, 1, 1, "����δȡ��", sizeof("����δȡ��") );
			//DisplayStr( 0, 1, 1, "Mei Qu zou", sizeof("Mei Qu zou") );
			#endif
			val = 15;
			break;
		case 16:
			#ifdef _CHINA_
			if(flag == 1)
			DisplayStr( 0, 1, 1, "������ű���", sizeof("������ű���") );
			#endif
			val = 16;
			break;
		case 17:
			#ifdef _CHINA_
			if(flag == 1)
			DisplayStr( 0, 1, 1, "������������", sizeof("������������") );
			//DisplayStr( 0, 1, 1, "Err Lift", sizeof("Err Lift") );
			#endif
			val = 17;
			break;
		case 21:
			#ifdef _CHINA_
			if(flag == 1)
			DisplayStr( 0, 1, 1, "��������", sizeof("��������") );
			#endif
			val = 21;
			break;
		case 22:
			#ifdef _CHINA_
			if(flag == 1)
			DisplayStr( 0, 1, 1, "����������", sizeof("����������") );
			#endif
			val = 22;
			break;
		case 23:
			#ifdef _CHINA_
			if(flag == 1)
			DisplayStr( 0, 1, 1, "ȡ���������", sizeof("ȡ���������") );
			#endif
			val = 23;
			break;
		case 24:
			#ifdef _CHINA_
			if(flag == 1)
			DisplayStr( 0, 1, 1, "�û��綯�Ź���", sizeof("�û��綯�Ź���") );
			#endif
			val = 24;
			break;
		case 25:
			#ifdef _CHINA_
			if(flag == 1)
			DisplayStr( 0, 1, 1, "���һ�������", sizeof("���һ�������") );
			#endif
			val = 25;
			break;
		case 26:
			#ifdef _CHINA_
			if(flag == 1)
			DisplayStr( 0, 1, 1, "����ģ�����", sizeof("����ģ�����") );
			#endif
			val = 26;
			break;
		case 27:
			#ifdef _CHINA_
			if(flag == 1)
			DisplayStr( 0, 1, 1, "��������������", sizeof("��������������") );
			#endif
			val = 27;
			break;
		case 28:
			#ifdef _CHINA_
			if(flag == 1)
			DisplayStr( 0, 1, 1, "�������Ź���", sizeof("�������Ź���") );
			#endif
			val = 28;
			break;
		case 51:
			#ifdef _CHINA_
			if(flag == 1)
			DisplayStr( 0, 1, 1, "״̬��ѯ��ʱ", sizeof("״̬��ѯ��ʱ") );
			#endif
			//DisplayStr( 0, 1, 1, "Err State Check", sizeof("Err State Check") );
			val = 2;
			break;
		case 52:
			#ifdef _CHINA_
			if(flag == 1)
			DisplayStr( 0, 1, 1, "���������ʧ��", sizeof("���������ʧ��") );
			#endif
			val = 2;
			//DisplayStr( 0, 1, 1, "Err Send Vendout", sizeof("Err Send Vendout") );
			break;
		case 53:
			#ifdef _CHINA_
			if(flag == 1)
			DisplayStr( 0, 1, 1, "���������ѯ��ʱ", sizeof("���������ѯ��ʱ") );
			#endif
			//DisplayStr( 0, 1, 1, "Err Vendout Check", sizeof("Err Vendout Check") );
			val = 1;
			break;
		case 99:
#ifdef _CHINA_
			if(flag == 1)
			DisplayStr( 0, 1, 1, "��������", sizeof("��������") );
#endif
			///DisplayStr( 0, 1, 1, "Err Other", sizeof("Err Other") );
			val = 99;
			break;
		case 0xFF:
#ifdef _CHINA_
			if(flag == 1)
			DisplayStr( 0, 1, 1, "ͨ�Ź���", sizeof("ͨ�Ź���") );
#endif
			//DisplayStr( 0, 1, 1, "Err Com", sizeof("Err Com") );
			val = 0xFF;
			break;
		default:
#ifdef _CHINA_
			if(flag == 1)
			DisplayStr( 0, 1, 1, "��������", sizeof("��������") );
#endif
			val = 99;
			break;
	}

	WaitForWork( 2000, NULL );
	return val;
}


/*****************************************************************************
** Function name:	ChannelLifterTask	
** Descriptions:		������+���ʹ���������												 			
** parameters:		��				
** Returned value:	0:��ȷִ�е�����1:��������ʧ��
**					2:ִ�����ʱ     3:�����޻�
**					4:��������   		  5:���޶���ʱ���ڵ�����ܵ�λ

**					 6:						7: CMD ERR  8: GOC check error 
*******************************************************************************/
u_char ChannelLifterTask( u_char ChannelNum, u_char TaskId )
{
	u_char xdata res = 0;
	uint temp = 0;
	switch(TaskId)
	{
		case CHANNEL_EXEC:
		case CHANNEL_TEST:
			//res = LifTerProcess(1,ChannelNum);
			res = LifterVendout(1,ChannelNum);
			res = LifterVendoutReturn(res,TaskId == CHANNEL_TEST);
			break;
		case CHANNEL_CLEAR: 
		case CHANNEL_QUERY:
			temp = LifterSendCheckState(1);
			if((temp & 0x00FF) == 2)
				res = 2;
			else
				res = 0;
			break;
		default:
			res = 7;
			break;
	}		
	return res;

	
}



/*****************************************************************************
**�������������
*******************************************************************************/

/*****************************************************************************
** Function name:	LifterRecv	
** Descriptions:	      ���մ��ڻ�Ӧ��													 			
** parameters:		��
** Returned value:	0:�����ݽ��� 1:������� 2:���ݽ��մ���
*****************************************************************************/
uchar LifterRecv(uint timeout)
{
	uchar index = 0;
	uint crc;
	timeout = timeout;
	memset( &ackTask, 0, sizeof( struct COMMTASK ) );
	ZhkDownMsgAckTimer = 1500;
	while(ZhkDownMsgAckTimer)
	{
		if(!ZhkSerial1IsRxBufNull())
		{
			ackTask.Param[index++] = ZhkSerial1GetCh();
			if(index == 1)//first byte 
			{
				if(ackTask.Param[0] != 0xC8)//head err
					continue;
			}
			else if(index == 2) //2th byte
				ackTask.ParamLen = ackTask.Param[1];
			else if(index >= (ackTask.ParamLen + 2)) //recv over
			{
				crc = CrcCheck(ackTask.Param,ackTask.ParamLen);
				return 1;
#if 0
				if(ackTask.Param[index - 2] == crc / 256 && ackTask.Param[index-1] == crc % 256)
					return 1;
				else
					return 2;
#endif
			}
			
		}
	}
	
	if(index)
		return 2;
	else
		return 0;
}

/*****************************************************************************
** Function name:	LifterSend	
** Descriptions:	      ���շ��Ͳ�����													 			
** parameters:		��
** Returned value:	0:�����ݽ��� 1:������� 2:���ݽ��մ���
*****************************************************************************/

uchar LifterSend(unsigned char type,uchar binNo,uchar rowNo,uchar columNo)
{
	uchar timeout = 0,comOK = 0,index = 0,i,buf[12] = {0};
	uint crc;
	binNo = binNo;
	Channel.CommState	= COMM_BUZY;
	buf[index++] = 0xC7;
	buf[index++] = 0x05;//����
	buf[index++] = 0x40;
	buf[index++] = 0x00;//�汾�̶�0
	buf[index++] = type;
	if(rowNo != 0x00)
		buf[index++] = rowNo;
	if(columNo != 0x00)
		buf[index++] = columNo;
	
	buf[1] = index;//�����ض�λ
	crc	= CrcCheck(buf,index);//��У��
	buf[index++] = (uchar)(crc >> 8);
	buf[index++] = (uchar)(crc & 0xFF);
	for(i = 0;i < index;i++)
	{	
		ZhkSerial1PutCh( buf[i]);
	}
	
	return LifterRecv(500);


}
	

/*****************************************************************************
** Function name:	LifterCheckRstTask	
** Descriptions:	      	���ͳ�����ѯ�������													 			
** parameters:		binNo:���
** Outputparameters: errNo   ��������ɺ�һ���ֶ���Ч
					0:�����ɹ�
					1:���ݴ���
					2:�޻�				3:����
					4:ȡ����û����
					5:����δȡ�� 		6:������ű�����
					7:����������  	other:��������
** Returned value:	 0:��ѯʧ�� 1:������� 
					 2:���ڳ���0xFF:ͨ�Ź��� 
*****************************************************************************/
uint LifterCheckRstTask(uchar binNo,uchar *errNo)
{
	uchar rst = 0;
	rst = LifterSend(VMC_VENDINGRESULT_REQ,binNo,0,0);
	if(rst == 0)
		return 0xFF;
	if(rst == 2)
		return 0;
	if(ackTask.Param[4] == GCC_VENDINGRESULT_ACK)//�ɹ��յ�ACK
	{	
		if(ackTask.Param[5] == 0x01)//���ڳ���
			return 2;
		else
		{
			if(ackTask.Param[6] == 0x00)//�����ɹ�
			{
				*errNo = 0;
				return 1;
			}
			else
			{
				*errNo = ackTask.Param[7];
				return 1;
			}
				
		}
	}
	return 0;
	
}



/*****************************************************************************
** Function name:	LifterSendCheckState	
** Descriptions:	      	���Ͳ�ѯ״̬����													 			
** parameters:		binNo:���
** outparameters:      0:�޹���
					1:����״̬����
					2:����������
					3:ȡ���������
					4:�û��綯�Ź���
					5:���һ�������
					6:����ģ�����
					7:��������������
					8:�������Ź���
** Returned value:	0�������� 1����æ2��ѯʧ��0xFFͨ��ʧ��
*****************************************************************************/
uint LifterCheckStateTask(uchar binNo,uchar *errNo)
{
	uchar rst = 0;
	rst = LifterSend(VMC_STATUS_REQ,binNo,0,0);
	if(rst == 0)
		return 0xFF;
	if(rst == 2)
		return 2;
	
	if(ackTask.Param[4] == GCC_STATUS_ACK)//�ɹ��յ�ACK
	{	
		if(ackTask.Param[5] == 0)//������־ 0���� 1æ
		{
			*errNo = 0;
			return 0;
		}
		else
		{
			*errNo = 1;
			if(ackTask.Param[6] & 0x01) *errNo = 1;//����״̬
			if(ackTask.Param[7] & 0x01) *errNo = 2;//������
			if(ackTask.Param[8] & 0x01) *errNo = 3;//ȡ�����
			if(ackTask.Param[9] & 0x01) *errNo = 4;//�û��綯��
			if(ackTask.Param[10] & 0x01) *errNo = 5;//���һ���
			if(ackTask.Param[11] & 0x01) *errNo = 6;//����ģ��
			if(ackTask.Param[12] & 0x01) *errNo = 7;//����������
			if(ackTask.Param[13] & 0x01) *errNo = 8;//��������	
			return 1;
		}
		
	}
	return 2;
	
}

/*****************************************************************************
** Function name:	LifterSendVendout	
** Descriptions:	      	���ͳ�������													 			
** parameters:		binNo:���
					rowNo:���
					columnNo:����
** Returned value:	0:����ʧ��; 1:���ͳɹ�;0xFF ͨ��ʧ��
*****************************************************************************/
uchar LifterSendVendoutTask(uchar binNo,uchar rowNo,uchar columnNo)
{
	uchar rst = 0,rcx = 2,errNo;
	while(rcx--)
	{
		rst = LifterSend(VMC_VENDING_REQ,binNo,rowNo,columnNo);
		if(rst == 0 || rst == 2)
			return 0xFF;
		if(ackTask.Param[4] == GCC_VENDING_ACK)//�ɹ��յ�ACK
		{
			return 1;
		}
		
		//���û���յ�ACK����Ҫ�ڷ���һ�β�ѯ����
		//ȷ����������ͳɹ������ظ����ͳ�������
		rst = LifterCheckRstTask(binNo,&errNo);
		if(rst == 2 || rst == 1)//��ʾ������æ ͬ����ζ�ų�������ͳɹ�
			return 1;
	}
	return 0;
}



/*****************************************************************************
** Function name:	LifterVendoutTask	
** Descriptions:														 			
** parameters:		��				
** Returned value:	01:�ɹ�
					11:���ݴ��� 
					12:�޻�
					13:����		  
					14:ȡ����û����
					15:����δȡ��
					16:������ű���
					17:������������
					21:��������
					22:����������
					23:ȡ���������
					24:�û��綯�Ź���
					25:���һ�������
					26:����ģ�����
					27:��������������
					28:�������Ź��
					51:״̬��ѯ��ʱ
					52:���������ʧ��
					53:���������ѯ��ʱ
					99:��������
					255(0xFF):ͨ��ʧ��
*******************************************************************************/

uchar LifterVendoutTask(struct COMMTASK xdata*liftPtr)
{
	uchar res = 0,rcx = 5;
	uchar rowNo = 0,columnNo = 0,binNum,errNo,state;
	unsigned short takeTimeOut = 10,vendoutTimeout;
	binNum = liftPtr->Param[0];
	rowNo = liftPtr->Param[1] / 10 ;
	columnNo = liftPtr->Param[1] % 10;
	
	//��ʼ���� //��ѯ״̬�Ƿ���������������
	rcx = 10;
	while(rcx--)
	{
		state = LifterCheckStateTask(binNum,&errNo); 	
		if(state == 0)//����������
			break;
		else if(state == 1)//����æ
		{
			if(errNo & 0xFF)//�й���
			{
				if(errNo == 1) return 21;
				if(errNo == 2) return 22;
				if(errNo == 3) return 23;
				if(errNo == 4) return 24;
				if(errNo == 5) return 25;
				if(errNo == 6) return 26;
				if(errNo == 7) return 27;
				if(errNo == 8) return 28;
				return 99;
					
			}
		}
		else if(state == 0xFF)
		{
			rcx = 1;
		}
		lifterDelay(2000);
	}

	if(state != 0)//��ʱ��ѯ��������Ȼ������
	{
		if(state == 0xFF)
			return 0xFF;
		else
			return 51;
	}
		
	while(1)
	{
		//���г�������
		res = LifterSendVendoutTask(binNum,rowNo,columnNo);
		if(res == 0 || res == 0xFF)
			return 52;
		
		lifterDelay(500);
		//5000 * 10  = 50000 
		vendoutTimeout = 100 +(8 - rowNo) * 10;//�����������ʱ
		while(vendoutTimeout--)
		{	
			state = LifterCheckRstTask(binNum,&errNo);//���������
			if(state == 0x01)//�������
			{
				break;
			}
			lifterDelay(1000);
		}
		
		if(vendoutTimeout)
		{
			if(errNo != 0)//����ʧ��
			{
				if((errNo == 5) && takeTimeOut)//��δȡ��
				{
					lifterDelay(2000);
					takeTimeOut--;
					continue;
				}
				//return ((stateH > 7) ? (stateH + 10) : 99);
				return (errNo + 10);
			}	
			else//�����ɹ�
				return 1;
		}
		else										   	
			return 53;		
	}

}

uchar LifterVendout(uchar binNum,uchar logicNo)
{
	uchar timeout = 0,comOK = 0,index = 0;

	memset( &lifterTask, 0, sizeof( struct COMMTASK ) );
	Channel.CommState	= COMM_BUZY;
	lifterTask.Id		= ID_CHANNEL;
	lifterTask.Cmd		= VMC_VENDING_REQ;
	lifterTask.Priority = PRIORITY_NORMAL;
	lifterTask.Param[0] = binNum;
	lifterTask.Param[1] = logicNo;
	ZhkSchedulerAddTask( &lifterTask );
	
	while(! ( timeout || comOK ))
	{
		WaitForWork( 100, NULL );
		timeout = TestDeviceTimeOut( &Channel );
		comOK = TestDeviceCommOK( &Channel );	
	}

	if(timeout)
		return 0xFF;
	if(comOK)
		return Channel.State;	
	return 0xFF;
}








