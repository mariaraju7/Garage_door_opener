#include "UART.h"

void UART1_Init(void) {
	RCC->APB2ENR |= RCC_APB2ENR_USART1EN   ; //enable clck
	RCC->CCIPR &= ~ RCC_CCIPR_USART1SEL; //clear bits
	RCC->CCIPR |= RCC_CCIPR_USART1SEL_0; //01, : System clock (SYSCLK) selected as USART2 clock
}

void UART2_Init(void) {
	RCC->APB1ENR1 |= RCC_APB1ENR1_USART2EN; //enable clck
	RCC->CCIPR &= ~ RCC_CCIPR_USART2SEL; //clear bits
	RCC->CCIPR |= RCC_CCIPR_USART2SEL_0; //01, : System clock (SYSCLK) selected as USART2 clock
}

void UART1_GPIO_Init(void) {
	// PB6 and PB7 to operate as UART transmitters and receivers.
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN; //enable clock
	
	//Set PB6 to very high output speed
	GPIOB->OSPEEDR  &= ~(GPIO_OSPEEDER_OSPEEDR6);
	GPIOB->OSPEEDR  |= (GPIO_OSPEEDER_OSPEEDR6); // sets both bits high, for high speed
	
	GPIOB->OTYPER &= ~(GPIO_OTYPER_OT6); // sets to push/pull output type
	
	GPIOB->PUPDR &= ~(GPIO_PUPDR_PUPD6); // Resets to no pull-up/pull-down
  GPIOB->PUPDR |= GPIO_PUPDR_PUPD6_0; // 01, sets it to pull-up
	
		// Alternative Function
	GPIOB->MODER &= ~(GPIO_MODER_MODE6_0); //sets bit 2 to high
	
	// Selects the alternative function for PB7
	GPIOB->AFR[0] &= ~GPIO_AFRL_AFSEL6;
	GPIOB->AFR[0] |= (GPIO_AFRL_AFSEL6_2| GPIO_AFRL_AFSEL6_1|GPIO_AFRL_AFSEL6_0);
	
	
	// initializing PB7
	
	GPIOB->OSPEEDR  &= ~(GPIO_OSPEEDER_OSPEEDR7);
	GPIOB->OSPEEDR  |= (GPIO_OSPEEDER_OSPEEDR7); // sets both bits high, for high speed
	
	GPIOB->OTYPER &= ~(GPIO_OTYPER_OT7); // sets to push/pull output type
	
	GPIOB->PUPDR &= ~(GPIO_PUPDR_PUPD7); // Resets to no pull-up/pull-down
  GPIOB->PUPDR |= GPIO_PUPDR_PUPD7_0; // 01, sets it to pull-up
	
	// Alternative Function
	GPIOB->MODER &= ~ (GPIO_MODER_MODE7_0); //sets bit 2 to high
	
	// Selects the alternative function for PB7
	GPIOB->AFR[0] &= ~GPIO_AFRL_AFSEL7;
	GPIOB->AFR[0] |= (GPIO_AFRL_AFSEL7_2| GPIO_AFRL_AFSEL7_1 | GPIO_AFRL_AFSEL7_0);
}

void UART2_GPIO_Init(void) {
	// PA2 and PA3 to operate as UART transmitters and receivers.
	
	//initializing PA2
	
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN; //enable clock
	
	//Set PA2 to very high output speed
	GPIOA->OSPEEDR  &= ~(GPIO_OSPEEDER_OSPEEDR2);
	GPIOA->OSPEEDR  |= (GPIO_OSPEEDER_OSPEEDR2); // sets both bits high, for high speed
	
	GPIOA->OTYPER &= ~(GPIO_OTYPER_OT2); // sets to push/pull output type
	
	GPIOA->PUPDR &= ~(GPIO_PUPDR_PUPD2); // Resets to no pull-up/pull-down
  GPIOA->PUPDR |= GPIO_PUPDR_PUPD2_0; // 01, sets it to pull-up
	
		// Alternative Function
	GPIOA->MODER &= ~(GPIO_MODER_MODE2_0); //sets bit 2 to high
	
	// Selects the alternative function for PA5
	GPIOA->AFR[0] &= ~GPIO_AFRL_AFSEL2;
	GPIOA->AFR[0] |= (GPIO_AFRL_AFSEL2_2| GPIO_AFRL_AFSEL2_1|GPIO_AFRL_AFSEL2_0);
	
	
	// initializing PA3
	
	GPIOA->OSPEEDR  &= ~(GPIO_OSPEEDER_OSPEEDR3);
	GPIOA->OSPEEDR  |= (GPIO_OSPEEDER_OSPEEDR3); // sets both bits high, for high speed
	
	GPIOA->OTYPER &= ~(GPIO_OTYPER_OT3); // sets to push/pull output type
	
	GPIOA->PUPDR &= ~(GPIO_PUPDR_PUPD3); // Resets to no pull-up/pull-down
  GPIOA->PUPDR |= GPIO_PUPDR_PUPD3_0; // 01, sets it to pull-up
	
	// Alternative Function
	GPIOA->MODER &= ~ (GPIO_MODER_MODE3_0); //sets bit 2 to high
	
	// Selects the alternative function for PA5
	GPIOA->AFR[0] &= ~GPIO_AFRL_AFSEL3;
	GPIOA->AFR[0] |= (GPIO_AFRL_AFSEL3_2| GPIO_AFRL_AFSEL3_1 | GPIO_AFRL_AFSEL3_0);
}

void USART_Init(USART_TypeDef* USARTx) {
	// Disable USART before configuring settings
	USARTx->CR1 &= ~USART_CR1_UE;
	
	// Set Communication Parameters
	USARTx->CR1 &= ~(USART_CR1_M);     // 00 -> 8 Data Bits
	USARTx->CR1 &= ~(USART_CR1_OVER8); // 0 -> Oversampling by 16
	USARTx->CR2 &= ~(USART_CR2_STOP);  // 00 -> 1 Stop Bit
	
	// Set Baud Rate
	// f_CLK = 80 MHz, Baud Rate = 9600 = 80 MHz / DIV -> DIV = 8333 = 0x208D
	USARTx->BRR = 0x208D;
	
	// Enable Transmitter/Receiver
	USARTx->CR1 |= USART_CR1_TE | USART_CR1_RE;
	
	// Enable USART
	USARTx->CR1 |= USART_CR1_UE;
}

uint8_t USART_Read (USART_TypeDef * USARTx) {
	// SR_RXNE (Read data register not empty) bit is set by hardware
	while (!(USARTx->ISR & USART_ISR_RXNE));  // Wait until RXNE (RX not empty) bit is set
	// USART resets the RXNE flag automatically after reading DR
	return ((uint8_t)(USARTx->RDR & 0xFF));
	// Reading USART_DR automatically clears the RXNE flag 
}

void USART_Write(USART_TypeDef * USARTx, uint8_t *buffer, uint32_t nBytes) {
	int i;
	// TXE is cleared by a write to the USART_DR register.
	// TXE is set by hardware when the content of the TDR 
	// register has been transferred into the shift register.
	for (i = 0; i < nBytes; i++) {
		while (!(USARTx->ISR & USART_ISR_TXE));   	// wait until TXE (TX empty) bit is set
		// Writing USART_DR automatically clears the TXE flag 	
		USARTx->TDR = buffer[i] & 0xFF;
		USART_Delay(300);
	}
	while (!(USARTx->ISR & USART_ISR_TC));   		  // wait until TC bit is set
	USARTx->ISR &= ~USART_ISR_TC;
}   

void USART_Delay(uint32_t us) {
	uint32_t time = 100*us/7;    
	while(--time);   
}
