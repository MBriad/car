#include "config.h"
#include "Delay.h"
#include "Servo.h"
/*=================================================
*�������ƣ�ServoFront
*�������ܣ���̨��ǰת��
*���ã�
*���룺
=================================================*/
void ServoFront()
{
	char i;
	EA_off;	//�ر��жϷ����Ӱ����ת��
	for(i=0;i<10;i++)
	{	
		ServoPin = 1;
		Delay1550us();
		ServoPin = 0;
		Delay18450us();
	}
	EA_on;	//���ж�
	Delay1ms(100);
}
/*=================================================
*�������ƣ�ServoLeft
*�������ܣ���̨����ת��
*���ã�
*���룺
=================================================*/
void ServoLeft()
{
	char i;
	EA_off;	//�ر��жϷ����Ӱ����ת��
	for(i=0;i<10;i++)
	{	
		ServoPin = 1;
		Delay2500us();
		ServoPin = 0;
		Delay17500us();
	}
	EA_on;	//���ж�
	Delay1ms(100);
}
/*=================================================
*�������ƣ�ServoFront
*�������ܣ���̨����ת��
*���ã�
*���룺
=================================================*/
void ServoRight()
{
	char i;
	EA_off;	//�ر��жϷ����Ӱ����ת��
	for(i=0;i<10;i++)
	{
		ServoPin = 1;
		Delay600us();
		ServoPin = 0;
		Delay19400us();
	}
	EA_on;	//���ж�
	Delay1ms(100);
}

void ServoLeft45()
{
	char i;
	EA_off;
	for(i=0;i<10;i++)
	{
		ServoPin = 1;
		Delay2000us();
		ServoPin = 0;
		Delay18000us();
	}
	EA_on;
	Delay1ms(100);
}

void ServoRight45()
{
	char i;
	EA_off;
	for(i=0;i<10;i++)
	{
		ServoPin = 1;
		Delay1000us();
		ServoPin = 0;
		Delay19000us();
	}
	EA_on;
	Delay1ms(100);
}