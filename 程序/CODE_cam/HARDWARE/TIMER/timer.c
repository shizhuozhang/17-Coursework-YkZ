#include "H_define.h"

#if __SETITIM1
	void TIM1_Init(u16 arr,u16 psc)
	{
		RCC->APB2ENR|=1<<11;//定时器1初始化
		TIM1->ARR=arr;
		TIM1->PSC=psc;
		TIM1->DIER|=1<<0;//使能中断
		TIM1->CR1|=1<<7;//arpe使能
		TIM1->CR1|=1<<0;//使能计数器
		MY_NVIC_Init(3,2,TIM1_UP_IRQn,2);
	}
	
	void TIM1_UP_IRQHandler(void) //计数器中断
	{
		if(TIM1->SR&0x0001)
		{
			LED0=~LED0;
			LED1=~LED1;
		}
		TIM1->SR&=~(1<<0);//清除中断标志位 
	}		
#endif
	
#if __SETITIM2
	void TIM2_Init(u16 arr,u16 psc)
	{
		RCC->APB1ENR|=1<<0;//定时器2初始化
		TIM2->ARR=arr;
		TIM2->PSC=psc;
		TIM2->DIER|=1<<0;//使能中断
		TIM2->CR1|=1<<7;//arpe使能
		TIM2->CR1|=1<<0;//使能计数器
		MY_NVIC_Init(3,2,TIM2_IRQn,2);
	}
	
	void TIM2_IRQHandler(void) //计数器中断
	{
		if(TIM2->SR&0x0001)
		{
			LED0=~LED0;
			LED1=~LED1;
		}
		TIM2->SR&=~(1<<0);//清除中断标志位 
	}
#endif
	
#if __SETITIM3
	void TIM3_Init(u16 arr,u16 psc)
	{
		RCC->APB1ENR|=1<<1;//定时器3初始化
		TIM3->ARR=arr;
		TIM3->PSC=psc;
		TIM3->DIER|=1<<0;//使能中断
		TIM3->CR1|=1<<7;//arpe使能
//		TIM3->CR1|=1<<0;//使能计数器
		MY_NVIC_Init(1,1,TIM3_IRQn,2);
	}
u8 Led_num=0;
u8 Con_num=0;
u8 Tim_flag=0;	
	void TIM3_IRQHandler(void) //计数器中断
	{
		if(TIM3->SR&0x0001)
		{		
//			Prepare_Data();  //准备数据
//			IMU_Update();			//姿态更新频率为500Hz
//			
//			Angle_Now.Angle_X=Angle.X-Angle_Init[0];
//			Angle_Now.Angle_Y=Angle.Y-Angle_Init[1];
//			Angle_Now.Angle_Z=Angle.Z-Angle_Init[2];
					
			Con_num++;
			if(Con_num == 2)	 			//控制频率250Hz
			{ 
				Con_num = 0;							
				PID_Angle(Angle_Now,Angle_Exp);			
			}	
			
			Led_num++;
			if(Led_num>250)//2HZ
			{
				LED0=~LED0;
				Led_num=0;
				Tim_flag=1;
			}

		}
		TIM3->SR&=~(1<<0);//清除中断标志位 
	}
#endif
	
#if __SETITIM4
	void TIM4_Init(u16 arr,u16 psc)
	{
		RCC->APB1ENR|=1<<2;//定时器4初始化
		TIM4->ARR=arr;
		TIM4->PSC=psc;
		TIM4->DIER|=1<<0;//使能中断
		TIM4->CR1|=1<<7;//arpe使能
		TIM4->CR1|=1<<0;//使能计数器
		MY_NVIC_Init(3,2,TIM4_IRQn,2);
	}
	
	void TIM4_IRQHandler(void) //计数器中断
	{
		if(TIM4->SR&0x0001)
		{
			LED0=~LED0;
		}
		TIM4->SR&=~(1<<0);//清除中断标志位 
	}
#endif
	



	
	
