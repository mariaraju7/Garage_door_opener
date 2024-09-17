/*
 * ECE 153B
 *
 * Name(s):
 * Section:
 * Project
 */

#include "stm32l476xx.h"
#include "SysClock.h"
#include "SysTimer.h"
#include "UART.h"
#include "motor.h"
#include <stdio.h>
#include <string.h>


int main(void) {
	char ch;
	// Switch System Clock = 80 MHz
	System_Clock_Init(); 
	Motor_Init();
	SysTick_Init();
	UART2_GPIO_Init();
	UART2_Init();
	USART_Init(USART2);//TODO
	
	printf("Program Starts.\r\n");
	setDire(1);
	

	while(1) {
		char x[60];
		printf("print your line: ");
		scanf("%s", x); 
		

			if ((strcmp("y", x)==0 | (strcmp("Y", x))==0))
			{
				setDire(1);
				printf("CLOCKWISE \n");
			}
			else if ((strcmp("n", x)==0 | (strcmp("N", x))==0))
			{
				setDire(0);
				printf("COUNTERCLOCKWISE \n");
			}
			else if ((strcmp("s", x)==0 | (strcmp("S", x))==0)){
				//stop();
				setDire(2);
				printf("STOP \n");
			}
			else 
			{
				printf("try again with a valid command");
			}
	   
		
	}
}


