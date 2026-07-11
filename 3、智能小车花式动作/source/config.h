#ifndef _CONFIG_H
#define _CONFIG_H
/****************************************************************
 通用头文件
****************************************************************/
#include <reg52.h>
#include <intrins.h>

#define MAIN_Fosc		11059200UL	//宏定义主时钟HZ
#define BAUD 9600 //UART 波特率

#define LeftMotorStop	 	IN1 = 0, IN2 = 0//左电机停止
#define RightMotorStop		IN3 = 0, IN4 = 0//右电机停止
#define LeftMotorGo			IN1 = 0, IN2 = 1//左电机正传
#define LeftMotorBack		IN1 = 1, IN2 = 0//左电机反转
#define RightMotorGo		IN3 = 1, IN4 = 0//右电机正传
#define RightMotorBack		IN3 = 0, IN4 = 1//右电机反转
#define Timer1On			TR1 = 1			//启动定时器1
#define Timer1Off			TR1 = 0			//关闭定时器1
#define EA_on				EA = 1			//开始总中断
#define EA_off				EA = 0			//关闭总中断
#define BUZZER_on			BUZZER = 0		//开启蜂鸣器
#define BUZZER_off			BUZZER = 1		//关闭蜂鸣器

/****************************************************************
已有数据类型重新定义
****************************************************************/
typedef signed char int8;  //8位有符号型
typedef signed int  int16; //16位有符号型
typedef unsigned char uint8;  //8位无符号型
typedef unsigned char uchar;  //8位无符号型
typedef unsigned int  uint16; //16位无符号型
typedef unsigned int  uint; //16位无符号型
typedef unsigned long uint32; //32位无符号型
typedef unsigned char BYTE;	  //8位无符号型
typedef unsigned int WORD;	  //16位无符号型

/****************************************************************
 硬件接口定义
****************************************************************/
/*电机驱动IO定义*/
sbit IN1 = P1^2; //为1 左电机反转
sbit IN2 = P1^3; //为1 左电机正转
sbit IN3 = P1^6; //为1 右电机正转
sbit IN4 = P1^7; //为1 右电机反转
sbit LeftMotor_EN  = P1^4; //为1 左电机使能
sbit RightMotor_EN = P1^5; //为1 右电机使能
/*舵机接口*/
sbit ServoPin = P2^7;
/*超声波接口*/
sbit EchoPin = P2^0; //超声波模块Echo	接收端
sbit TrigPin = P2^1; //超声波模块Trig	控制端
/*4位独立按键引脚*/
sbit KEY_S2 = P3^0;	//S2独立按键
sbit KEY_S3 = P3^1;	//S3独立按键
sbit KEY_S4 = P3^2;	//S4独立按键
sbit KEY_S5 = P3^3;	//S5独立按键
/*LCD1602液晶引脚*/
#define LCD1602_DB  P0      //data bus 数据总线
sbit LCD1602_RS = P3^5;		//LCD1602液晶命令/数据选择引脚
sbit LCD1602_RW = P3^6;		//LCD1602液晶读/写选择引脚
sbit LCD1602_EN = P3^4;	 	//LCD1602液晶使能引脚
/*5V有源蜂鸣器引脚*/
sbit BUZZER = P2^3;	//蜂鸣器引脚
/*传感器接口定义*/
sbit FollowSensorLeft 	=	P3^4;//左跟随传感器
sbit FollowSensorRight	=	P3^5;//右跟随传感器
sbit AvoidSensorLeft	=	P3^4;//左避障传感器	
sbit AvoidSensorRight	=	P3^5;//右避障传感器
sbit TrackSensorLeft	=	P3^3;//左寻迹传感器
sbit TrackSensorRight	=	P3^2;//右寻迹传感器

sbit UAvoidSensorLeft	=	P1^0;//左避障传感器	
sbit UAvoidSensorRight	=	P1^1;//右避障传感器

#endif