/*
 * ECE 153B
 *
 * Name(s): Maria Raju, Janani Ganesh
 * Section: Wed 7PM
 * Project
 */

#include "stm32l476xx.h"
#include "SysClock.h"
#include "SysTimer.h"
#include "LED.h"
#include "DMA.h"
#include "UART.h"
#include "motor.h"
#include "SPI.h"
#include "I2C.h"
#include "accelerometer.h"
#include <stdio.h>
#include <string.h>

static char buffer[IO_SIZE];

#define CW_direction 1
#define CCW_direction 0
#define STOP 2

#define HIGH_threshold 0.95
#define LOW_threshold 0.09

uint8_t door_state = 0;//0 close 1 open
uint8_t next_door_state = 1;
uint8_t in_process = 0;
uint8_t override = 0;
int new_temp;
int old_temp = 100; //changed from 150
uint8_t SecondaryAddress;
uint8_t Data_Receive;
uint8_t Data_Send;


void UART_onInput(char* inputs, uint32_t size) {
	override = 1;
	if (!strncmp(inputs, "Y\n", 5)){
		setDire(0);
		sprintf(buffer, "garage door opening.\n");
		UART_print(buffer);
		next_door_state = 1;
		in_process = 1;
	}
	else if (!strncmp(inputs, "close\n", 6)){
		setDire(1);
		sprintf(buffer, "garage door closing.\n");
		UART_print(buffer);
		next_door_state = 0;
		in_process = 1;
	}
	else{
		setDire(2);
		sprintf(buffer, "try again with a valid command\n");
		UART_print(buffer);
		in_process = 0;
	}
}

void tempData(){

  // Determine Secondary Address
  // Note the "<< 1" must be present because bit 0 is treated as a don't care in 7-bit addressing mode
  SecondaryAddress = 0b1001000 << 1;

  // First, send a command to the sensor for reading the temperature
  // Next, get the measurement
  Data_Send = 0x00;
  I2C_SendData(I2C1, SecondaryAddress, &Data_Send, 1);
  I2C_ReceiveData(I2C1, SecondaryAddress, &Data_Receive, 1);
  
  new_temp = Data_Receive;

}


int main(void) {
// Switch System Clock = 80 MHz
System_Clock_Init();
Motor_Init();
SysTick_Init();
LED_Init();
USART_Init(USART2);
SPI1_GPIO_Init();
SPI1_Init();
initAcc();
I2C_GPIO_Init();
I2C_Initialization();
  
double x,y,z;
  
  while(1){
  //TODO
    LED_Toggle();
    tempData();
    readValues(&x, &y, &z);
    
    sprintf(buffer, "Acceleration: %.2f, %.2f, %.2f\rCurrent temperature: %d\n",x,y,z,Data_Receive);
		UART_print(buffer);
    
    //end states for the different thresholds
    if (z > HIGH_threshold && in_process == 1 && next_door_state == 1){
      setDire(STOP);
      in_process = 0;
      door_state = 1;
      next_door_state = 0;
      sprintf(buffer, "door opened!\r\n");
      UART_print(buffer);
    }
    else if(z < LOW_threshold && in_process == 1 && next_door_state == 0){
      setDire(STOP);
      in_process = 0;
      door_state = 0;
      next_door_state = 1;
      sprintf(buffer, "door closed!\r\n");
      UART_print(buffer);
    }
    
    //creates a 3 second delay for data to be printed
    if((override != 0) && (in_process == 0)){
			override++;
			if(override > 3){
				override = 0;
			}
		}
		else{
			if(new_temp < 25 && door_state ==1 && in_process == 0 && override == 0 && next_door_state == 0){
				sprintf(buffer, "temperature is too low, door is closing.\r\n");
				UART_print(buffer);
				setDire(1);
				in_process = 1;
				next_door_state = 0;
			}
      else if(new_temp >25 && door_state == 0 && in_process == 0 && override == 0 && next_door_state == 1){
        sprintf(buffer, "temperature is too high, door is opening.\r\n");
				UART_print(buffer);
				setDire(0);
				in_process = 1;
				next_door_state = 1;
      }
    }
    delay(1000);
    readValues(&x, &y, &z);
    
    if(z > HIGH_threshold && in_process == 1 && next_door_state == 1){
        
				setDire(2);
				in_process = 0;
        door_state = 1;
				next_door_state = 1;
        sprintf(buffer, "door is opened.\r\n");
				UART_print(buffer);
    }
    else if(z < LOW_threshold && in_process == 1 && next_door_state == 0){
        setDire(2);
				in_process = 0;
        door_state = 0;
				next_door_state = 1;
        sprintf(buffer, "door is closed.\r\n");
				UART_print(buffer);
    }
    
    if(z < LOW_threshold && in_process == 0){
      door_state = 0;
      next_door_state = 1;
    }
    else if(z > HIGH_threshold && in_process == 0){
      door_state = 1;
      next_door_state = 0;
    }
    delay(500);
  }
}
