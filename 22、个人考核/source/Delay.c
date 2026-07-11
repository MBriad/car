#include "config.h"
#include "Delay.h"

/*====================================
������	��Delay1ms(INT16U ms)
����	��ms��������ʱ�β�
����ֵ	����
����	��12T 51��Ƭ������Ӧ��ʱ�Ӻ��뼶��ʱ����
====================================*/
void Delay1ms(uint ms)
{
     uint i;
	 do{
	      i = MAIN_Fosc / 96000; 
		  while(--i);   //96T per loop
     }while(--ms);
}
/*������������ʱ*/
void Delay15us()		//@11.0592MHz
{
	unsigned char i;

	i = 4;
	while (--i);
}


/*���������ʱ����С����ǰ��*/
void Delay1550us()		//@11.0592MHz
{
	unsigned char i, j;

	i = 3;
	j = 196;
	do
	{
		while (--j);
	} while (--i);
}

void Delay18450us()		//@11.0592MHz
{
	unsigned char i, j;

	_nop_();
	i = 34;
	j = 16;
	do
	{
		while (--j);
	} while (--i);
}
/*���������ʱ��С���ҷ�*/
void Delay600us()		//@11.0592MHz
{
	unsigned char i, j;

	_nop_();
	i = 2;
	j = 15;
	do
	{
		while (--j);
	} while (--i);
}
void Delay19400us()		//@11.0592MHz
{
	unsigned char i, j;

	_nop_();
	i = 35;
	j = 197;
	do
	{
		while (--j);
	} while (--i);
}
/*���������ʱ����С����*/
void Delay17500us()		//@11.0592MHz
{
	unsigned char i, j;

	i = 32;
	j = 93;
	do
	{
		while (--j);
	} while (--i);
}
void Delay2500us()		//@11.0592MHz
{
	unsigned char i, j;

	i = 5;
	j = 120;
	do
	{
		while (--j);
	} while (--i);
}

/* ServoRight45 high pulse, -45 deg */
void Delay1000us()		//@11.0592MHz
{
	unsigned char i, j;

	i = 2;
	j = 25;
	do
	{
		while (--j);
	} while (--i);
}

/* ServoRight45 low pause, 20ms - 1.0ms */
void Delay19000us()		//@11.0592MHz
{
	unsigned char i, j;

	_nop_();
	i = 35;
	j = 193;
	do
	{
		while (--j);
	} while (--i);
}

/* ServoLeft45 high pulse, +45 deg */
void Delay2000us()		//@11.0592MHz
{
	unsigned char i, j;

	i = 4;
	j = 120;
	do
	{
		while (--j);
	} while (--i);
}

/* ServoLeft45 low pause, 20ms - 2.0ms */
void Delay18000us()		//@11.0592MHz
{
	unsigned char i, j;

	i = 33;
	j = 93;
	do
	{
		while (--j);
	} while (--i);
}
