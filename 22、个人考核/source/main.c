/*
* ����дʱ�䡿�� 2019��8��6��
* ����    �ߡ��� �������:01
* ����    ������ 1.7 �Ż���������̨�����߼�
* ����    վ���� http://www.qxmcu.com/ 
* ���Ա����̡��� http://qxmcu.taobao.com/ 
* ��ʵ��ƽ̨���� QX-MCS51 ��Ƭ�������� & QX-A51����С��
* ���ⲿ���񡿣� 11.0592mhz	
* ������оƬ���� STC89C52
* �����뻷������ Keil ��Visio4
* �������ܡ��� ��̨���ϣ���������̨�������ϣ�1602Һ����ʾ����
* ��ʹ��˵������ 1���������1602Һ����ʾ��
				 2���뽫�������ذ��С���װ��ϵ�P32-P35��4P�Ű��߰ε�
				 3����װ�������Ű��ߣ��ֱ��С��������P34�ӵ����ذ��P10�ϣ�P35�ӵ����ذ��P11��

				 Һ����һ����ʾ��̨��෽�򣬷ֱ�ΪD��Fǰ����L����,R����
				 �ڶ�������ʾ�ľ��룬��λ����
				 ����ͨ�������ʾ��Ϣ����������С�������߼��������ϲ�ͬʵ�黷��
				 �¶���Ҫ���Բ��ܴﵽ����Ч����
				 ִ���߼�app.c�ļ�����PTZ_Avoid����
* ��ע������� ��̨����ײ
*/

#define  _MAIN_C
#include "config.h"
#include "motor.h"
#include "Delay.h"
#include "timer_ISR.h"
#include "LCD1602.h"
#include "ultrasonic.h"
#include "app.h"
#include "Servo.h"
#include "main.h"

uchar LeftSpeed, RightSpeed;//�����������ٶ�
void keyscan()
{
	for(;;)	//��ѭ��
	{
		if(KEY_S2 == 0)// ʵʱ���S2�����Ƿ񱻰���
		{
			Delay1ms(5); //��������
			if(KEY_S2 == 0)//�ټ��S2�Ƿ񱻰���
			{
				while(!KEY_S2);//���ּ��
				BUZZER_on;	//����������
				Delay1ms(200);//200������ʱ
				BUZZER_off;	//�رշ�����
				break;		//�˳�FOR��ѭ��
			}
		}
	}	
}
void main()
{
//	LeftSpeed	= 150;//���������ٶ�
//	RightSpeed	= 150;//���������ٶ�
	IntRegInit();//中断寄存器初始化
	Timer0Init();//PWM调速初始化
	Timer1Init();//初始化定时器
	Init_LCD1602(); //LCD1602��ʼ��
	ServoFront(); //��ʼ���������
	LCD1602_Dis_Str(0, 0, "Please press the"); //LCD1602д�ַ���
	LCD1602_Dis_Str(0, 1, "S2 to start"); //LCD1602д�ַ����밴��S2����С��
	keyscan();//��S2��������
	LCD1602_Clear_Screen();//LCD1602����	
	while(1)
	{
		AssessmentRun();
		SmartCarStops();
		while(1);
	}
}