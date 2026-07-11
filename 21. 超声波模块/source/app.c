#include "config.h"
#include "timer_ISR.h"
#include "LCD1602.h"
#include "ultrasonic.h"
#include "Delay.h"
#include "motor.h"
#include "Servo.h"
#include "app.h"
#include "main.h"

bit Timer1Overflow;	//计数器1溢出标志位
bit Timer2Overflow; //计数器2溢出标志位


uchar code ASCII[13] = "0123456789";
uchar disbuff[4]={0,0,0,0};//用于分别存放距离的值米，厘米，毫米

uint LeftDistance = 0, RightDistance = 0, FrontDistance = 0; //云台测距距离缓存
uint My_Distance,RearDistance; //定义新增超声波测距的距离

uint DistBuf[5] = {0};//distance data buffer

uchar code ASCII_2[13] = "0123456789";
uchar disbuff_2[4]={0,0,0,0};//用于分别存放新增超声波距离的值米，厘米，毫米
uint  DistBuf_2[5] = {0};//定义新增超声波距离的缓存

/*====================================
函数名	：DispDistance(unsigned long Val)
参数	：距离
返回值	：无
描述	：LCD1602显示距离
显示距离单位：毫米
====================================*/
void DispDistance(unsigned int Val)
{
	if((Val >= 5000) || (Timer1Overflow == 1))//超出测量范围
	{
		Timer1Overflow = 0; //清除定时器溢出标志位
		LCD1602_Dis_Str(0, 0, "!!! Out of range"); //LCD1602显示字符串	
	}
	else
	{
		/*显示距离单位毫米*/
		disbuff[0]=Val/1000; //距离数值千位
		disbuff[1]=Val%1000/100;//距离数值百位
		disbuff[2]=Val%100/10;//距离数值十位
		disbuff[3]=Val%10; //距离数值个位
		LCD1602_Dis_Str(0, 0, "Distance:0000 MM"); //显示：Distance:000.0cm
	    LCD1602_Dis_OneChar(9, 0,  ASCII[disbuff[0]]); //显示千位
	    LCD1602_Dis_OneChar(10, 0, ASCII[disbuff[1]]);	
	    LCD1602_Dis_OneChar(11, 0, ASCII[disbuff[2]]);	
	    LCD1602_Dis_OneChar(12, 0, ASCII[disbuff[3]]); 				
	}		
}
//冒泡排序
void bubble(unsigned int *a,unsigned char n) /*定义两个参数：数组首地址与数组大小*/
{
	unsigned int i,j,temp;	
	for(i = 0;i < n-1; i++)	
	{	
		for(j = i + 1; j < n; j++) /*注意循环的上下限*/
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
函数名	：RefreshDistance
参数	：无
返回值	：经过冒泡排序后的距离
描述	：经过5次测距，去除最大值和最小值，取中间3次平均值
距离单位：毫米
====================================*/
unsigned int RefreshDistance()
{
	uchar num;
	uint Dist;
	for(num=0; num<5; num++)
	{
		DistBuf[num] = GetDistance();
		Delay1ms(60);//测距周期不低于60毫秒	
	}
	bubble(DistBuf, 5);//
	Dist = (DistBuf[1]+DistBuf[2]+DistBuf[3])/3; //去掉最大和最小取中间平均值
	return(Dist);
}
/*红外避障*/
void IR_Avoid()
{
	if(UAvoidSensorLeft == 0)
	{
		SmartCarRight(LeftSpeed, RightSpeed);//右转	
	}else if(UAvoidSensorRight == 0)
	{
		SmartCarLeft(LeftSpeed, RightSpeed);//左转		
	}else
	{
		SmartCarForward(LeftSpeed, RightSpeed);//前进	
	}
}
/*====================================
函数名	：PTZ_Avoid
参数	：val设置避障触发距离
返回值	：无
描述	：智能小车舵机云台避障
距离单位：毫米
====================================*/
void PTZ_Avoid(uint val)
{
	uint Dis;//距离暂存变量
	Dis = GetDistance();//获取超声波测距距离,单位：毫米
	if(Dis < val)
	{
		LCD1602_Dis_OneChar(0, 0, 'D');
		DispDistance(Dis);//LCD1602显示超声波测距距离	
		SmartCarStops();	//停车
		Delay1ms(50);

		/*舵机左转测距*/
		ServoLeft();
		LeftDistance = RefreshDistance();
		LCD1602_Dis_OneChar(0, 0, 'L');
		DispDistance(LeftDistance);//LCD1602显示超声波测距距离
		Delay1ms(50);

		/*舵机右转测距*/
		ServoRight();
		RightDistance = RefreshDistance();
		LCD1602_Dis_OneChar(0, 0, 'R');
		DispDistance(RightDistance);//LCD1602显示超声波测距距离
		Delay1ms(50);

		/*舵机正前方测距*/
		ServoFront();
		FrontDistance = RefreshDistance();
		LCD1602_Dis_OneChar(0, 0, 'F');
		DispDistance(FrontDistance);//LCD1602显示超声波测距距离
		Delay1ms(50);



		if((FrontDistance<100) && (LeftDistance<100) && (RightDistance<100))
		{
			do{
				SmartCarLeftTurn(255, 255);//原地左转
				Delay1ms(50);
				/*舵机正前方测距*/
				ServoFront();
				Dis = RefreshDistance();
				LCD1602_Dis_OneChar(0, 0, 'D');
				DispDistance(Dis);//LCD1602显示超声波测距距离
				Delay1ms(100);		
			}while(Dis < 200);
		}else if((FrontDistance>LeftDistance) && (FrontDistance>RightDistance))
		{
			LCD1602_Dis_OneChar(0, 0, 'F');
			DispDistance(FrontDistance);//LCD1602显示超声波测距距离
			Delay1ms(100);
			SmartCarForward(LeftSpeed, RightSpeed);//前进
		}else if(LeftDistance > RightDistance)
		{
			LCD1602_Dis_OneChar(0, 0, 'L');
			DispDistance(LeftDistance);//LCD1602显示超声波测距距离
			Delay1ms(100);
			SmartCarLeftTurn(255, 255);//原地左转
			Delay1ms(80);		
		}else if(RightDistance > LeftDistance)
		{
			LCD1602_Dis_OneChar(0, 0, 'R');
			DispDistance(RightDistance);//LCD1602显示超声波测距距离
			Delay1ms(100);
			SmartCarRightTurn(255, 255);//原地右转
			Delay1ms(80);	
		}		
	}
	else
	{
		for(Dis=0; Dis<1800; Dis++)//测距周期不低于60ms 这里借用Dis变量做循环
		{
			IR_Avoid();//红外避障
		}
	}			
}

/**************************************/
 //新超声波模块的距离显示函数，显示在LCD的第二行，第一行显示了原来超声波的距离
void My_DispDistance(unsigned int Val)	
{
	if((Val >= 2500) || (Timer2Overflow == 1))//超出测量范围
	{
		Timer2Overflow = 0; //清除定时器溢出标志位
		LCD1602_Dis_Str(0, 1, "!!! Out of range"); //LCD1602显示字符串	
	}
	else
	{
		/*显示距离单位毫米*/
		disbuff_2[0]=Val/1000; //距离数值千位
		disbuff_2[1]=Val%1000/100;//距离数值百位
		disbuff_2[2]=Val%100/10;//距离数值十位
		disbuff_2[3]=Val%10; //距离数值个位
		LCD1602_Dis_Str(0, 1, "Distance:0000 MM"); //显示：Distance:000.0cm
	    LCD1602_Dis_OneChar(9, 1,  ASCII_2[disbuff_2[0]]); //显示千位
	    LCD1602_Dis_OneChar(10, 1, ASCII_2[disbuff_2[1]]);	
	    LCD1602_Dis_OneChar(11, 1, ASCII_2[disbuff_2[2]]);	
	    LCD1602_Dis_OneChar(12, 1, ASCII_2[disbuff_2[3]]); 				
	}		
}
//新超声波模块的距离刷新函数
unsigned int My_RefreshDistance() //
{
	uchar num;
	uint Dist;
	for(num=0; num<5; num++)
	{
		DistBuf_2[num] = My_GetDistance();
		Delay1ms(60);//测距周期不低于60毫秒	
	}
	bubble(DistBuf_2, 5);//
	Dist = (DistBuf_2[1]+DistBuf_2[2]+DistBuf_2[3])/3; //去掉最大和最小取中间平均值
	return(Dist);
}


void My_TEST(void)
{
		RearDistance = My_RefreshDistance();
//		LCD1602_Dis_Str(0, 0, "Distance");
		My_DispDistance(RearDistance);//LCD1602显示超声波测距距离
		Delay1ms(50);
}

void My_TEST_2(void)
{
		My_Distance = RefreshDistance();
		DispDistance(My_Distance);
		Delay1ms(50);
}
