/*
 * ECE 153B
 *
 * Name(s): Janani Ganesh, Maria Raju
 * Section: Wed 7PM
 * Project
 */

#include "stm32l476xx.h"
#include "motor.h"

static const uint32_t MASK = 0x00000360U;//TODO
static const uint32_t HalfStep[8] = {0x00000140U, 0x00000040U, 0x00000240U, 0x00000200U, 0x00000220U, 0x00000020U, 0x00000120U, 0x00000100U};
static volatile int8_t dire = 0;
static volatile uint8_t step = 0;

void Motor_Init(void) {	

	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN; //Enable clock for Port C
	
	GPIOC->MODER &= ~(GPIO_MODER_MODE5_1); // Clear and sets bits for Pin 5
	GPIOC->OSPEEDR |= (GPIO_OSPEEDR_OSPEED5_1); //Sets Pin5 to fast
  GPIOC->OTYPER &= ~(GPIO_OTYPER_OT5); // Set as push-pull output
	GPIOC->PUPDR &= ~(GPIO_PUPDR_PUPD5); // Resets to no pull-up/pull-down
	
	GPIOC->MODER &= ~(GPIO_MODER_MODE6_1); // Clear and sets bits for Pin 6
	GPIOC->OSPEEDR |= (GPIO_OSPEEDR_OSPEED6_1); //Sets Pin6 to fast
  GPIOC->OTYPER &= ~(GPIO_OTYPER_OT6); // Set as push-pull output
	GPIOC->PUPDR &= ~(GPIO_PUPDR_PUPD6); // Resets to no pull-up/pull-down
	
	GPIOC->MODER &= ~(GPIO_MODER_MODE8_1); // Clear and sets bits for Pin 8
	GPIOC->OSPEEDR |= (GPIO_OSPEEDR_OSPEED8_1); //Sets Pin8 to fast
  GPIOC->OTYPER &= ~(GPIO_OTYPER_OT8); // Set as push-pull output
	GPIOC->PUPDR &= ~(GPIO_PUPDR_PUPDR8); // Resets to no pull-up/pull-down
	
	GPIOC->MODER &= ~(GPIO_MODER_MODE9_1); // Clear and sets bits for Pin 9
	GPIOC->OSPEEDR |= (GPIO_OSPEEDR_OSPEED9_1); //Sets Pin9 to fast
  GPIOC->OTYPER &= ~(GPIO_OTYPER_OT9); // Set as push-pull output
	GPIOC->PUPDR &= ~(GPIO_PUPDR_PUPD9); // Resets to no pull-up/pull-down
	
	step=0;
}


void rotate(void) {
	
	
	GPIOC->ODR &= ~MASK;
	GPIOC->ODR |= HalfStep[step];
	
	if(dire==0){ //counterclockwise
		step++;
		if(step>=8){ //reaches end then changes
			step=0;
		}
	}
	else if (dire==1){ //clockwise
		if(step==0){
			step = 7;
		}
		else{
			step--;
		}
	}
	else if (dire==2){ //stops
		while(1){
				break;
		}
	}
}
void setDire(int8_t direction) {
	dire=direction;
}

	







