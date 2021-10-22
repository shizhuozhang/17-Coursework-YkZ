#include "H_define.h"


#define Init_S1 4400
#define Init_S2 4500

volatile Angle_XYZ  Angle_Exp;///位置环输出的期望角度
Angle_XYZ Angle_err;

float Angle_Init[3]={0.0,0.0,0.0};
float Angle_Sum[3]={0.0};
u8 Time_Count=0;
s8   Yaw_Set[16]={10,20,30,0,0,0,0,0,10,20,30,0,-10,0,-30,0};
s8 Pitch_Set[16]={0,0,0,0,10,20,30,0,10,20,30,0,10,0,-30,0};

int main()
{
	u8 GYRO_Flag=1;
	u8 Num=0;//陀螺仪初始化
	
	Init1();
	Init2();
	
	TIM4->CCR1=Init_S1;  //roll，对应X，<4500,逆时针转，正角度
	TIM4->CCR2=Init_S2;	//偏航，对应Z，<4500,顺时针，正角度
	
	Angle_Exp.Angle_X=0;
	Angle_Exp.Angle_Z=0;	
	
    while(1)
	{			
/*串口使用函数*/		
		if(sign_usrt2)
		{	
			if(Num>100)
			{
				GYRO_Flag=0;
				Num=100;
				Angle_Init[0]=(float)(Angle_Sum[0]/100);
				Angle_Init[1]=(float)(Angle_Sum[1]/100);	
				Angle_Init[2]=(float)(Angle_Sum[2]/100);
				printf("%f  %f  %f \r\n",Angle_Init[0],Angle_Init[1],Angle_Init[2]);	
				printf("ok\r\n");
				
				TIM3->CR1|=1<<0;//使能计数器,开始PID控制
			}
			
			if(GYRO_Flag)
			{
				Num++;	
				Angle_Sum[0]+=Angle_Now.Angle_X;
				Angle_Sum[1]+=Angle_Now.Angle_Y;
				Angle_Sum[2]+=Angle_Now.Angle_Z;
			}	
			else			
				printf("%f  %f \r\n",Angle_Now.Angle_X,Angle_Now.Angle_Z);
			
			sign_usrt2=0;	
		}
		if(Tim_flag)
		{
//			Tim_flag=0;
//			Time_Count++;
//			if(Time_Count>=128)
//				Time_Count=0;//控制16个数
//			Angle_Exp.Angle_Y=Pitch_Set[(u8)(Time_Count/8)];
//			Angle_Exp.Angle_Z=Yaw_Set[(u8)(Time_Count/8)];	
			
		}
	}
}








