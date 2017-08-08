#include "stepper.h"

/***************************************
* 函数名称：stepper_speed_set(u8 speed, u8 mode)
* 函数说明：speed设置步进电机速度，mode选择高速低速模式，
           高速共10个档+停止
		   低速共 3个档+停止
***************************************/

u8 steps_flag=0;

void stepper_speed_set(u8 speed, u8 mode)
{
	u16 arr,psc;
	
	if(mode==STEPPER_SPEED_HIGH)
	{
		switch(speed)
		{
			case 0:	//stop stepper
				HAL_TIM_Base_Stop_IT(&TIM3_Handler);
			break;
			case 1:	//1ms
				arr=90-1;
				psc=1100-1;
				TIM3_Init(arr,psc);
			break;
			case 2:
				arr=9-1;
				psc=1000-1;
				TIM3_Init(arr,psc);
			break;
			case 3:
				arr=9-1;
				psc=900-1;
				TIM3_Init(arr,psc);
			break;
			case 4:
				arr=9-1;
				psc=800-1;
				TIM3_Init(arr,psc);
			break;
			case 5:
				arr=9-1;
				psc=700-1;
				TIM3_Init(arr,psc);
			
			break;
			case 6:
				arr=9-1;
				psc=600-1;
				TIM3_Init(arr,psc);
			break;
			case 7:
				arr=9-1;
				psc=500-1;
				TIM3_Init(arr,psc);
			break;
			case 8:
				arr=9-1;
				psc=400-1;
				TIM3_Init(arr,psc);
			break;
			case 9:
				arr=9-1;
				psc=300-1;
				TIM3_Init(arr,psc);
			break;
			case 10:
				arr=9-1;
				psc=200-1;
				TIM3_Init(arr,psc);
			break;
			default:
				HAL_TIM_Base_Stop_IT(&TIM3_Handler);
			break;
		}		
	}
	else if(mode==STEPPER_SPEED_LOW)
	{
		switch(speed)
		{
			case 0:	//stop stepper
				HAL_TIM_Base_Stop_IT(&TIM3_Handler);
			break;
			case 1:	//1ms
				arr=90-1;
				psc=2000-1;
				TIM3_Init(arr,psc);
			break;
			case 2:
				arr=90-1;
				psc=1000-1;
				TIM3_Init(arr,psc);
			break;
			case 3:
				arr=60-1;
				psc=1000-1;
				TIM3_Init(arr,psc);
			break;
			default:
				HAL_TIM_Base_Stop_IT(&TIM3_Handler);
			break;
		}
	}
	else 
	{
		HAL_TIM_Base_Stop_IT(&TIM3_Handler);
	}
}

void stepper_direction_set(u8 direction)
{
	if(direction==STEPPER_CLOCKWISE)
	{
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,GPIO_PIN_SET);	//PB0置0
	}
	else if(direction==STEPPER_ANTI_CLOCKWISE)
	{
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,GPIO_PIN_RESET);	//PB0置1 
	}
	else 
	{
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,GPIO_PIN_RESET);
	}

}

void stepper_steps_set(u32 steps)
{
	if(steps_flag==STEPS_FLAG_OFF)
	{
		stepper_steps=steps*2;
		steps_flag=STEPS_FLAG_CNT;
	}
}

u32 angle2steps(float angle)
{
	return angle/0.9*16.0;
}
