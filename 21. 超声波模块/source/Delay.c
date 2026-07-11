#include "config.h"
#include "Delay.h"

/*====================================
函数名	：Delay1ms(INT16U ms)
参数	：ms，毫秒延时形参
返回值	：无
描述	：12T 51单片机自适应主时钟毫秒级延时函数
====================================*/
void Delay1ms(uint ms)
{
     uint i;
	 do{
	      i = MAIN_Fosc / 96000; 
		  while(--i);   //96T per loop
     }while(--ms);
}
/*超声波触发延时*/
void Delay15us()		//@11.0592MHz
{
	unsigned char i;

	i = 4;
	while (--i);
}


/*舵机方波延时朝向小车正前方*/
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
/*舵机方波延时向小车右方*/
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
/*舵机方波延时朝向小车左方*/
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
