/*********************************************************************

File    : main.c
Program : Template Project
Author  : Carlos Estay
Purpose : ADC demo. ADC is configured to 12-bit by default. Triggered by Timer ISR
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
#include "adc.h"
#include "timer.h"


/*********************************************************************
  Local Prototypes
*********************************************************************/
void HAL_Init(void);

/*********************************************************************
  Global variables 
*********************************************************************/

volatile uint16_t msCounter = 0;
volatile uint8_t beacon = 0, convTrigger = 0;
volatile uint16_t adcRead;
/*********************************************************************
  Main entry
*********************************************************************/
int main(void) 
{

  /********************************************************************
    One-time Initializations
  ********************************************************************/  
  
  HAL_Init(); //this is needed when working at higher clock speeds (> 24MHz)
  Clock_InitPll(PLL_40MHZ); //Enable Pll to 40MHz
  printf("System Clock: %u Hz\n\r", SystemCoreClock); //print system clock result
  Clock_EnableOutput(MCO_Sel_SYSCLK, MCO_Div1); //Enables clock output on PA8 and divides it factor


  /*
  Use PB9 for testing 
  */
  GPIO_InitOutput(GPIOB, 9);


  Timer_SetDelay_us(TIM17); //this is just to set the rpescaler


  /********************************************************************
    Infinite Loop
  ********************************************************************/
  while(1)
  {
    /*Test us delay*/
    Timer_Delay_us(TIM17, 80); //Delay for ~80[us]
    GPIO_Toggle(GPIOB, 9);
    if(convTrigger)
    {
      convTrigger = 0;
      //No longer triggering the conversion here
    }
    if(beacon)
    {
      beacon = 0;
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

  RCC->APBENR2 |= RCC_APBENR2_ADCEN;  //Enable ADC1 clock

  RCC->APBENR2 |= RCC_APBENR2_TIM17EN;//Enable TIM17 clock

}


/*  This event Handler gets called every 1[ms] according to Systick Configuration
    This is technically not an ISR (it's an exception), therefore 
    it requires no flag clearing.
*/
void SysTick_Handler(void)
{
  convTrigger = 1;
  if(++msCounter > 499)
  {
    GPIO_Toggle(GPIOC, 6);
    
    msCounter = 0;
    beacon = 1;   
  }
}
 
/****************Interrupt Service Routines (ISR's)***********************/

