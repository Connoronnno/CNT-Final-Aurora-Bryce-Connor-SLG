/*********************************************************************

File    : main.c
Program : Template Project
Author  : Carlos Estay
Purpose : 
Date    : Sept-24-2024

Revision History:

*/

/********************************************************************
  Defines
********************************************************************/

/********************************************************************
  Default includes
********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "stm32g031xx.h"
#include "clock.h"
#include "gpio.h"
#include "uart.h"
/*********************************************************************
  Local Prototypes
*********************************************************************/
void HAL_Init(void);

/*********************************************************************
  Global variables 
*********************************************************************/

volatile uint16_t msCounter = 0;
volatile uint8_t beacon = 0;
/*********************************************************************
  Main entry
*********************************************************************/
int main(void) 
{
  /********************************************************************
    One-time Initializations
  ********************************************************************/  
  
  HAL_Init(); //this is needed when working at higher clock speeds (> 24MHz)
  //Clock_InitPll(PLL_40MHZ); //Enable Pll to 40MHz

  /********************************************************************
    Infinite Loop
  ********************************************************************/
  while(1)
  {
    if(beacon)
    {
      beacon = 0;
      UART_TxStr(USART2,"Hello Program...\n\r");
      printf("Hello Console...\n\r");
    }
  }
}

/********************************************************************
  Functions
********************************************************************/
void HAL_Init(void)
{
  //Enable power interface clock (RM 5.4.15)
  RCC->APBENR1 |= RCC_APBENR1_PWREN_Msk;
  

  /*Define HCLK clock ratio to the FLASH,
    slow down system to access flash (RM 3.7.1)*/

  FLASH->ACR |= FLASH_ACR_PRFTEN_Msk;     //Enable instruction prefetch  
  FLASH->ACR |= FLASH_ACR_LATENCY_Msk;    //One wait state is used to read a word in the NVM.

  /*Peripherals clock enable (RM 5.4.13)*/
  
  RCC->IOPENR |= RCC_IOPENR_GPIOAEN_Msk;  //Enable Port A
  RCC->IOPENR |= RCC_IOPENR_GPIOBEN_Msk;  //Enable Port B
  RCC->IOPENR |= RCC_IOPENR_GPIOCEN_Msk;  //Enable Port C

  RCC->APBENR1 |= RCC_APBENR1_USART2EN_Msk;     //Enable USART2
  RCC->APBENR2 |= RCC_APBENR2_SPI1EN_Msk;       //Enable SPI1 (Clock)
}


/*  This event Handler gets called every 1[ms] according to Systick Configuration
    This is technically not an ISR, therefore it requires no flag clearing
*/
void SysTick_Handler(void)
{
}
