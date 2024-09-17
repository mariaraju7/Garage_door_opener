/*
 * ECE 153B
 *
 * Name(s): Maria Raju, Janani Ganesh
 * Section: Wed 7PM
 * Project
 */
 
#include "DMA.h"
#include "SysTimer.h"


void DMA_Init_UARTx(DMA_Channel_TypeDef * tx, USART_TypeDef * uart) {
	
	RCC->AHB1ENR |= RCC_AHB1ENR_DMA1EN; //enable the clock for DMA
	for(int i =0; i<1000; i++){} //wait for 20us delay
	
	tx->CCR &= ~DMA_CCR_EN; //disable the channel
		
	tx->CCR &= ~DMA_CCR_MEM2MEM; //disable Memory-to-memory mode
	
	tx->CCR &= ~DMA_CCR_PL;
	tx->CCR |= DMA_CCR_PL_1; //Sset channel priority to high (10)
		
	tx->CCR &= ~DMA_CCR_PSIZE; //Set peripheral size to 8-bit (00)
	
	tx->CCR &= ~DMA_CCR_MSIZE;  //Set memory size to 8-bit (00)
	
	tx->CCR &= ~DMA_CCR_PINC; // Disable peripheral increment mode
	
	tx->CCR |= DMA_CCR_MINC; // Enable memory increment mode
	
	tx->CCR &= ~DMA_CCR_CIRC;// Disable circular mode
	
	tx->CCR |= DMA_CCR_DIR;// Set data transfer direction to Memory-to-Peripheral

	//tx->CPAR = (uint32_t)&(uart->TDR); //Set the data destination to the data register of the CRC block
	
	tx->CCR &= ~DMA_CCR_HTIE; //Disable half transfer interrupt
	tx->CCR &= ~DMA_CCR_TEIE; //Disable transfer error interrupt
	
	tx->CCR |= DMA_CCR_TCIE; //Enable transfer complete interrupt
	
	if(tx == DMA1_Channel4){
		DMA1_CSELR->CSELR |= 0b0010 << 12; //channel 4 maps to USART1_TX
		NVIC_SetPriority(DMA1_Channel4_IRQn,1); //Set interrupt priority to 1 in NVIC
		NVIC_EnableIRQ(DMA1_Channel4_IRQn); //Enable interrupt in NVIC
		NVIC_ClearPendingIRQ(DMA1_Channel4_IRQn);
	}
	else if(tx == DMA1_Channel7){
		DMA1_CSELR->CSELR |= 0b0010 << 24; //channel 7 maps to USART2_TX
		NVIC_SetPriority(DMA1_Channel7_IRQn,1); //Set interrupt priority to 1 in NVIC
		NVIC_EnableIRQ(DMA1_Channel7_IRQn); //Enable interrupt in NVIC
		NVIC_ClearPendingIRQ(DMA1_Channel7_IRQn);
	}

}



