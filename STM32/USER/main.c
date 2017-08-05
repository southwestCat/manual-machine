#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "stepper.h"

u8 stepper_direction;
u8 stepper_speed;
u8 stepper_speed_mode;
u32 stepper_steps;

int main(void)
{
	int i;
	int state;
	
	HAL_Init();                     //初始化HAL库    
	Stm32_Clock_Init(360,25,2,8);   //设置时钟,180Mhz
	delay_init(180);
	uart_init(115200);
	GPIO_init();
	
	stepper_direction=STEPPER_CLOCKWISE;
	stepper_speed=SPEED_LEVEL_0;
	stepper_speed_mode=STEPPER_SPEED_LOW;
	stepper_direction_set(stepper_direction);
	stepper_speed_set(stepper_speed, stepper_speed_mode);
	while(1)
	{
		if(USART_RX_STA&0x8000)
		{
			USART_RX_BUF[USART_RX_STA&0x3FFF]=0;
			if  ((USART_RX_BUF[0]=='F')&&(USART_RX_BUF[1]=='F'))
			{
				stepper_direction=(USART_RX_BUF[2]-'0')*10+(USART_RX_BUF[3]-'0');
				stepper_speed_mode=(USART_RX_BUF[4]-'0')*10+(USART_RX_BUF[5]-'0');
				stepper_speed=(USART_RX_BUF[6]-'0')*10+(USART_RX_BUF[7]-'0');
				
			}
			USART_RX_STA=0;
			state=0;
		}
		switch(state)
		{
			case 0:
				stepper_direction_set(stepper_direction);
				stepper_speed_set(stepper_speed, stepper_speed_mode);
				state=1;
			break;
			case 1:
			
			break;
			default:
				
			break;
		}
	}
}
