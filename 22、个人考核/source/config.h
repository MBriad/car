#ifndef _CONFIG_H
#define _CONFIG_H
/****************************************************************
 ͨ��ͷ�ļ�
****************************************************************/
#include <reg52.h>
#include <intrins.h>

sfr T2MOD = 0xC9;  // Timer 2 mode control (STC89C52)

#define MAIN_Fosc		11059200UL	//�궨����ʱ��HZ
#define BAUD 9600 //UART ������

#define LeftMotorStop	 	IN1 = 0, IN2 = 0//����ֹͣ
#define RightMotorStop		IN3 = 0, IN4 = 0//�ҵ��ֹͣ
#define LeftMotorGo			IN1 = 0, IN2 = 1//��������
#define LeftMotorBack		IN1 = 1, IN2 = 0//������ת
#define RightMotorGo		IN3 = 1, IN4 = 0//�ҵ������
#define RightMotorBack		IN3 = 0, IN4 = 1//�ҵ����ת
#define Timer1On			TR1 = 1			//������ʱ��1
#define Timer1Off			TR1 = 0			//�رն�ʱ��1
#define EA_on				EA = 1			//��ʼ���ж�
#define EA_off				EA = 0			//�ر����ж�
#define BUZZER_on			BUZZER = 0		//����������
#define BUZZER_off			BUZZER = 1		//�رշ�����
#define Headlight_on		Headlight = 0	//����ǰ���
#define Headlight_off		Headlight = 1	//�ر�ǰ���
#define on	1  //�����궨��
#define off 0  //�أ��궨��

/****************************************************************
���������������¶���
****************************************************************/
typedef signed char int8;  //8λ�з�����
typedef signed int  int16; //16λ�з�����
typedef unsigned char uint8;  //8λ�޷�����
typedef unsigned char uchar;  //8λ�޷�����
typedef unsigned int  uint16; //16λ�޷�����
typedef unsigned int  uint; //16λ�޷�����
typedef unsigned long uint32; //32λ�޷�����
typedef unsigned char BYTE;	  //8λ�޷�����
typedef unsigned int WORD;	  //16λ�޷�����

/****************************************************************
 Ӳ���ӿڶ���
****************************************************************/
/*�������IO����*/
sbit IN1 = P1^2; //Ϊ1 ������ת
sbit IN2 = P1^3; //Ϊ1 ������ת
sbit IN3 = P1^6; //Ϊ1 �ҵ����ת
sbit IN4 = P1^7; //Ϊ1 �ҵ����ת
sbit LeftMotor_EN  = P1^4; //Ϊ1 ����ʹ��
sbit RightMotor_EN = P1^5; //Ϊ1 �ҵ��ʹ��
/*����ӿ�*/
sbit ServoPin = P2^7;
/*�������ӿ�*/
sbit EchoPin = P2^0; //������ģ��Echo	���ն�
sbit TrigPin = P2^1; //������ģ��Trig	���ƶ�
sbit My_EPin = P2^4; //�³�����ģ��Echo	���ն�
sbit My_TPin = P2^5; //�³�����ģ��Trig	���ն�
/*4λ������������*/
sbit KEY_S2 = P3^0;	//S2��������
sbit KEY_S3 = P3^1;	//S3��������
sbit KEY_S4 = P3^2;	//S4��������
sbit KEY_S5 = P3^3;	//S5��������
/*LCD1602Һ������*/
#define LCD1602_DB  P0      //data bus ��������
sbit LCD1602_RS = P3^5;		//LCD1602Һ������/����ѡ������
sbit LCD1602_RW = P3^6;		//LCD1602Һ����/дѡ������
sbit LCD1602_EN = P3^4;	 	//LCD1602Һ��ʹ������
/*5V��Դ����������*/
sbit BUZZER = P2^3;	//����������
/*�������ӿڶ���*/
sbit FollowSensorLeft 	=	P3^4;//����洫����
sbit FollowSensorRight	=	P3^5;//�Ҹ��洫����
sbit AvoidSensorLeft	=	P3^4;//����ϴ�����	
sbit AvoidSensorRight	=	P3^5;//�ұ��ϴ�����
//sbit TrackSensorLeft	=	P3^3;//��Ѱ��������
//sbit TrackSensorRight	=	P3^2;//��Ѱ��������
sbit UAvoidSensorLeft	=	P1^0;//����ϴ�����	
sbit UAvoidSensorRight	=	P1^1;//�ұ��ϴ�����
sbit LightSensorFront   =	P0^0;//ǰѰ�⴫����
sbit LightSensorLeft	=	P0^1;//��Ѱ�⴫����
sbit LightSensorRight	=	P0^2;//��Ѱ�⴫����
sbit AHA_Sensor			=	P0^3;//�Զ���ƴ�����Automatic Headlight Activation
sbit MIC				=	P0^4;//���ִ�����
sbit HI_Sensor			=	P3^7;//������⴫����

/*ǰ��ƽӿڶ���*/
sbit Headlight 	= 	P0^5;//ǰ���

#endif