#include "config.h"
#include "timer_ISR.h"
#include "LCD1602.h"
#include "ultrasonic.h"
#include "Delay.h"
#include "motor.h"
#include "Servo.h"
#include "app.h"
#include "main.h"
#include <reg52.h>

bit Timer1Overflow;	//������1�����־λ
bit Timer2Overflow; //������2�����־λ


uchar code ASCII[13] = "0123456789";
uchar disbuff[4]={0,0,0,0};//���ڷֱ��ž����ֵ�ף����ף�����

uint LeftDistance = 0, RightDistance = 0, FrontDistance = 0; //��̨�����뻺��
uint My_Distance,RearDistance; //�����������������ľ���

uint DistBuf[5] = {0};//distance data buffer

uchar code ASCII_2[13] = "0123456789";
uchar disbuff_2[4]={0,0,0,0};//���ڷֱ������������������ֵ�ף����ף�����
uint  DistBuf_2[5] = {0};//������������������Ļ���

/*====================================
������	��DispDistance(unsigned long Val)
����	������
����ֵ	����
����	��LCD1602��ʾ����
��ʾ���뵥λ������
====================================*/
void DispDistance(unsigned int Val)
{
	if((Val >= 5000) || (Timer1Overflow == 1))//����������Χ
	{
		Timer1Overflow = 0; //�����ʱ�������־λ
		LCD1602_Dis_Str(0, 0, "!!! Out of range"); //LCD1602��ʾ�ַ���	
	}
	else
	{
		/*��ʾ���뵥λ����*/
		disbuff[0]=Val/1000; //������ֵǧλ
		disbuff[1]=Val%1000/100;//������ֵ��λ
		disbuff[2]=Val%100/10;//������ֵʮλ
		disbuff[3]=Val%10; //������ֵ��λ
		LCD1602_Dis_Str(0, 0, "Distance:0000 MM"); //��ʾ��Distance:000.0cm
	    LCD1602_Dis_OneChar(9, 0,  ASCII[disbuff[0]]); //��ʾǧλ
	    LCD1602_Dis_OneChar(10, 0, ASCII[disbuff[1]]);	
	    LCD1602_Dis_OneChar(11, 0, ASCII[disbuff[2]]);	
	    LCD1602_Dis_OneChar(12, 0, ASCII[disbuff[3]]); 				
	}		
}
//ð������
void bubble(unsigned int *a,unsigned char n) /*�������������������׵�ַ�������С*/
{
	unsigned int i,j,temp;	
	for(i = 0;i < n-1; i++)	
	{	
		for(j = i + 1; j < n; j++) /*ע��ѭ����������*/
		{
			if(a[i] > a[j])
			{
				temp = a[i];		
				a[i] = a[j];		
				a[j] = temp;			
			}
		}
	}

}
/*====================================
������	��RefreshDistance
����	����
����ֵ	������ð�������ľ���
����	������5�β�࣬ȥ�����ֵ����Сֵ��ȡ�м�3��ƽ��ֵ
���뵥λ������
====================================*/
unsigned int RefreshDistance()
{
	uchar num;
	uint Dist;
	for(num=0; num<5; num++)
	{
		DistBuf[num] = GetDistance();
		Delay1ms(60);//������ڲ�����60����	
	}
	bubble(DistBuf, 5);//
	Dist = (DistBuf[1]+DistBuf[2]+DistBuf[3])/3; //ȥ��������Сȡ�м�ƽ��ֵ
	return(Dist);
}
/*�������*/
void IR_Avoid()
{
	if(UAvoidSensorLeft == 0)
	{
		SmartCarRight(LeftSpeed, RightSpeed);//��ת	
	}else if(UAvoidSensorRight == 0)
	{
		SmartCarLeft(LeftSpeed, RightSpeed);//��ת		
	}else
	{
		SmartCarForward(LeftSpeed, RightSpeed);//ǰ��	
	}
}
/*====================================
������	��PTZ_Avoid
����	��val���ñ��ϴ�������
����ֵ	����
����	������С�������̨����
���뵥λ������
====================================*/
void PTZ_Avoid(uint val)
{
	uint Dis;//�����ݴ����
	Dis = GetDistance();//��ȡ������������,��λ������
	if(Dis < val)
	{
		LCD1602_Dis_OneChar(0, 0, 'D');
		DispDistance(Dis);//LCD1602��ʾ������������	
		SmartCarStops();	//ͣ��
		Delay1ms(50);

		/*�����ת���*/
		ServoLeft();
		LeftDistance = RefreshDistance();
		LCD1602_Dis_OneChar(0, 0, 'L');
		DispDistance(LeftDistance);//LCD1602��ʾ������������
		Delay1ms(50);

		/*�����ת���*/
		ServoRight();
		RightDistance = RefreshDistance();
		LCD1602_Dis_OneChar(0, 0, 'R');
		DispDistance(RightDistance);//LCD1602��ʾ������������
		Delay1ms(50);

		/*�����ǰ�����*/
		ServoFront();
		FrontDistance = RefreshDistance();
		LCD1602_Dis_OneChar(0, 0, 'F');
		DispDistance(FrontDistance);//LCD1602��ʾ������������
		Delay1ms(50);



		if((FrontDistance<100) && (LeftDistance<100) && (RightDistance<100))
		{
			do{
				SmartCarLeftTurn(255, 255);//ԭ����ת
				Delay1ms(50);
				/*�����ǰ�����*/
				ServoFront();
				Dis = RefreshDistance();
				LCD1602_Dis_OneChar(0, 0, 'D');
				DispDistance(Dis);//LCD1602��ʾ������������
				Delay1ms(100);		
			}while(Dis < 200);
		}else if((FrontDistance>LeftDistance) && (FrontDistance>RightDistance))
		{
			LCD1602_Dis_OneChar(0, 0, 'F');
			DispDistance(FrontDistance);//LCD1602��ʾ������������
			Delay1ms(100);
			SmartCarForward(LeftSpeed, RightSpeed);//ǰ��
		}else if(LeftDistance > RightDistance)
		{
			LCD1602_Dis_OneChar(0, 0, 'L');
			DispDistance(LeftDistance);//LCD1602��ʾ������������
			Delay1ms(100);
			SmartCarLeftTurn(255, 255);//ԭ����ת
			Delay1ms(80);		
		}else if(RightDistance > LeftDistance)
		{
			LCD1602_Dis_OneChar(0, 0, 'R');
			DispDistance(RightDistance);//LCD1602��ʾ������������
			Delay1ms(100);
			SmartCarRightTurn(255, 255);//ԭ����ת
			Delay1ms(80);	
		}		
	}
	else
	{
		for(Dis=0; Dis<1800; Dis++)//������ڲ�����60ms �������Dis������ѭ��
		{
			IR_Avoid();//�������
		}
	}			
}

/**************************************/
 //�³�����ģ��ľ�����ʾ��������ʾ��LCD�ĵڶ��У���һ����ʾ��ԭ���������ľ���
void My_DispDistance(unsigned int Val)	
{
	if((Val >= 2500) || (Timer2Overflow == 1))//����������Χ
	{
		Timer2Overflow = 0; //�����ʱ�������־λ
		LCD1602_Dis_Str(0, 1, "!!! Out of range"); //LCD1602��ʾ�ַ���	
	}
	else
	{
		/*��ʾ���뵥λ����*/
		disbuff_2[0]=Val/1000; //������ֵǧλ
		disbuff_2[1]=Val%1000/100;//������ֵ��λ
		disbuff_2[2]=Val%100/10;//������ֵʮλ
		disbuff_2[3]=Val%10; //������ֵ��λ
		LCD1602_Dis_Str(0, 1, "Distance:0000 MM"); //��ʾ��Distance:000.0cm
	    LCD1602_Dis_OneChar(9, 1,  ASCII_2[disbuff_2[0]]); //��ʾǧλ
	    LCD1602_Dis_OneChar(10, 1, ASCII_2[disbuff_2[1]]);	
	    LCD1602_Dis_OneChar(11, 1, ASCII_2[disbuff_2[2]]);	
	    LCD1602_Dis_OneChar(12, 1, ASCII_2[disbuff_2[3]]); 				
	}		
}
//�³�����ģ��ľ���ˢ�º���
unsigned int My_RefreshDistance() //
{
	uchar num;
	uint Dist;
	for(num=0; num<5; num++)
	{
		DistBuf_2[num] = My_GetDistance();
		Delay1ms(60);//������ڲ�����60����	
	}
	bubble(DistBuf_2, 5);//
	Dist = (DistBuf_2[1]+DistBuf_2[2]+DistBuf_2[3])/3; //ȥ��������Сȡ�м�ƽ��ֵ
	return(Dist);
}


void My_TEST(void)
{
//		RearDistance = My_RefreshDistance();
//		LCD1602_Dis_Str(0, 0, "Distance");
		My_DispDistance(100);//LCD1602��ʾ������������
		Delay1ms(50);
}

void My_TEST_2(void)
{
		My_Distance = RefreshDistance();
		DispDistance(My_Distance);
		Delay1ms(50);
}
