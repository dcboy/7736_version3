#ifndef _DATAEXCHANGE_
#define _DATAEXCHANGE_
#include "device.h"
#ifndef DATAEXCHANGE_C
	#define DataExchangeSourse extern
#else
	#define DataExchangeSourse
#endif
	DataExchangeSourse bit MovDataFromFlash( ulong FlashAddr , uchar idata* RamAddr , uchar len ) small;
	// ��Flash���ƶ�һ�����ݵ�Ƭ��
	// ������
	// FlashAddr flash�ڲ���ַ��ȡֵ��Χ��Ӳ���ṹ���
	// RamAddr   Ƭ���ڴ��ַ
	// len	     ����
	
	//DataExchangeSourse bit MovDataToFlash( ulong FlashAddr , uchar idata* RamAddr , uchar len ) small;
	// ��Ƭ���ƶ�һ�����ݵ�Flash
	// ������
	// FlashAddr flash�ڲ���ַ��ȡֵ��Χ��Ӳ���ṹ���
	// RamAddr   Ƭ���ڴ��ַ
	// len	     ����

	DataExchangeSourse bit MovDataFromSram( uchar xdata* SramAddr , uchar idata* RamAddr , uchar len );
	// ��Ƭ���ڴ��ƶ�һ�����ݵ�Ƭ���ڴ�
	// SramAddr  Ƭ���ڲ���ַ��ȡֵ��Χ��Ӳ���ṹ���
	// RamAddr   Ƭ���ڴ��ַ
	// len	     ����
	
	DataExchangeSourse bit MovDataToSram( uchar xdata* SramAddr , uchar idata* RamAddr , uchar len );
	// ��Ƭ���ڴ��ƶ�һ�����ݵ�Ƭ���ڴ�
	// SramAddr  Ƭ���ڲ���ַ��ȡֵ��Χ��Ӳ���ṹ���
	// RamAddr   Ƭ���ڴ��ַ
	// len	     ����
	
	
	DataExchangeSourse bit MovSramToFlash( ulong FlashAddr , uchar xdata* SramAddr , uint len ) small;
	// ��Ƭ���ڴ��ƶ�һ���ַ�flash
	// FlashAddr flash�ڲ���ַ��ȡֵ��Χ��Ӳ���ṹ���
	// SramAddr  Ƭ���ڲ���ַ��ȡֵ��Χ��Ӳ���ṹ���
	// len	     ����

	DataExchangeSourse bit MovFlashToSram( ulong FlashAddr , uchar xdata* SramAddr , uint len ) small;
	// ��flash�ƶ�һ���ַ���Ƭ���ڴ�
	// FlashAddr flash�ڲ���ַ��ȡֵ��Χ��Ӳ���ṹ���
	// SramAddr  Ƭ���ڲ���ַ��ȡֵ��Χ��Ӳ���ṹ���
	// len	     ����

	DataExchangeSourse bit PogramFlash( ulong FlashAddr , uchar xdata* SramAddr , uint len ) small;
	// ��Ƭ���ڴ��е�һ���ַ�д�뵽flash��û�о�������flash
	// FlashAddr flash�ڲ���ַ��ȡֵ��Χ��Ӳ���ṹ���
	// SramAddr  Ƭ���ڲ���ַ��ȡֵ��Χ��Ӳ���ṹ���
	// len	     ����

	DataExchangeSourse bit MovSramToSram( uchar xdata* Sourse , uchar xdata* Object , uint len );
	// ������Ƭ���ڴ���ƶ��ַ���
	// Sourse    Դ��ַ
	// Object    Ŀ���ַ
	// len       �ַ����ĳ��� 
	
	DataExchangeSourse bit FlashDel( ulong FlashAddr , ulong len ) small;
	// ���flash�е�����
	// FlashAddr��ʾ���������׵�ַ
	// len ��ʾ������򳤶�
	
	DataExchangeSourse uchar idata Cache[ 64 ];
	// ���㻺����
	
#endif