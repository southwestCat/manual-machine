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
		if(USART_RX_STA&0x8000)					//	接受串口发送的控制字，可以自己编写数据协议
		{
			USART_RX_BUF[USART_RX_STA&0x3FFF]=0;
			if  ((USART_RX_BUF[0]=='F')&&(USART_RX_BUF[1]=='F'))		//定义通信以'F','F'开始,如"FF000000"分别对方向、速度模式（高低 速）
			{															//本来这里速度模式可以不要，开始写的时候需要步进电机特别低的转速，因此在原有基础上增加低速
				stepper_direction=(USART_RX_BUF[2]-'0')*10+(USART_RX_BUF[3]-'0');
				stepper_speed_mode=(USART_RX_BUF[4]-'0')*10+(USART_RX_BUF[5]-'0');
				stepper_speed=(USART_RX_BUF[6]-'0')*10+(USART_RX_BUF[7]-'0');
				
			}
			USART_RX_STA=0;
			state=0;
		}
		switch(state)		//测试程序，功能设定转向、速度、步进数（通过函数进行角度和步进数转化，可以参考步进电机的参数设置）
		{
			case 0:			//这里步进电机在未到达设定转角之前不能执行其他下一步动作。具体可以参见timer,c中有关步进电机标志位的说明
				stepper_direction_set(stepper_direction);
				stepper_speed_set(stepper_speed, stepper_speed_mode);
				stepper_steps_set(angle2steps(360));
				state=1;
			break;
			case 1:
				
			break;
			default:
				
			break;
		}
	}
}
