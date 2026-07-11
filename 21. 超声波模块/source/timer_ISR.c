#include "config.h"
#include "timer_ISR.h"
#include "motor.h"
#include "app.h"

uchar PWM_T;//PWW周期
/*=================================================
*函数名称：IntRegInit
*函数功能：中断寄存器初始化
*调用：
*输入：
=================================================*/
void IntRegInit()
{
	ET0 = 1;//允许定时器0中断
	ET1 = 1;             //允许T1中断
	ET2 = 1;
	EA	= 1;//总中断允许	
}
/*定时器0初始化*/
void Timer0Init(void)		//100微秒@11.0592MHz
{
	TMOD |= 0x02;//定时器0，8位自动重装模块
	TH0 = 0xA4;
	TL0 = 0xA4;//100US中断一次
	TR0 = 1;//启动定时器0
}

/*定时器1初始化*/
void Timer1Init(void)		
{
	TMOD |= 0x10;	//定时器1工作模式1,16位定时模式。T1用测ECH0脉冲长度
	TH1 = 0;		   
  TL1 = 0;
}
/* Timer0 interrupt routine */
void tm0_isr() interrupt 1 using 1
{
	PWM_T++;
	if(PWM_T == 255)		//频率F=1000000/T0溢出时间*255
	{
		PWM_T = 0;
	}
	if(RightMotorSpeed >= PWM_T)
	{
		RightMotor_EN = 1;	//使能右马达
	}
	if(LeftMotorSpeed >= PWM_T)
	{
	 	LeftMotor_EN  = 1;  //使能左马达
	}		
	if(LeftMotorSpeed < PWM_T)
	{
	 	LeftMotor_EN  = 0;  //禁用左马达
	}		
	if(RightMotorSpeed < PWM_T)
	{
		RightMotor_EN = 0;	//禁用右马达
	}	
}
/*定时器1中断处理函数*/
void tm1_isr() interrupt 3 using 1
{
	Timer1Overflow = 1;	//计数器1溢出标志位
	EchoPin = 0;		//超声波接收端	
}

/**********************************/
/*定时器1初始化*/
void Timer2Init(void)//
{
	T2MOD = 0x00;
	T2CON = 0x00;
	TH2 = 0;
	TL2 = 0;
}
/*定时器2中断处理函数*/
void tm2_isr() interrupt 5 using 1
{
	Timer2Overflow = 1; //计数器2溢出标志位
	My_EPin = 0;//新超声波接收端	
}

/*
//这款单片机内部有3个定时计数器，
其中定时计数器0-T0  用于产生PWM用于控制车轮的转动速度
定时计数器T1 用于超声波距离的计数
定时计数器T2 用于新增超声波距离的计数
*/