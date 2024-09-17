/*
 * ECE 153B
 *
 * Name(s):
 * Section:
 * Project
 */

#include "LED.h"

void LED_Init(void){
	// Enable GPIO Clocks
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;
	
	// Initialize Green LED
  GPIOA->MODER &= ~(GPIO_MODER_MODE5_1); // Clear and sets bits 10 and 11 for Pin 5/((uint32_t)0x00000C00U)
  GPIOA->OTYPER &= ~(GPIO_OTYPER_OT5); // Set as push-pull output
	GPIOA->PUPDR &= ~(GPIO_PUPDR_PUPD5); // Resets to no pull-up/pull-down
}

void LED_On(void){
	GPIOA->ODR |= 1UL << 5; // Set output value of GPIO pin 5 to 1
}

void LED_Off(void){
	GPIOA->ODR &= ~(1UL << 5); // Set output value of GPIO pin 5 to 0
}

void LED_Toggle(void){
	GPIOA->ODR ^= 1UL << 5; // Tpggles output value of GPIO pin 5
}
