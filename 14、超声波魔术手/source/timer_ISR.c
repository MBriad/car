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
/* Timer0 interrupt routine */
void tm1_isr() interrupt 3 using 1
{
	Timer1Overflow = 1;	//计数器1溢出标志位
	EchoPin = 0;		//超声波接收端	
}
