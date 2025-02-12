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
  printf("System Clock: %u Hz\n\r", SystemCoreClock); //print system clock result
  Clock_EnableOutput(MCO_Sel_SYSCLK, MCO_Div1); //Enables clock output on PA8 and divides it factor


  /*
  Enable LEDS 
  RED->PB4(CN3_15), YELLOW->PB5(CN3_14), GREEN->PB9(CN3_13)
  */
  GPIO_InitOutput(GPIOB, 4);
  GPIO_InitOutput(GPIOB, 5);
  GPIO_InitOutput(GPIOB, 9);

  /*
  Enable switches
   CTR->PA0(12)
  */
  GPIO_InitInput(GPIOA, 0);

  //Enable built in LED (PC6)
  GPIO_InitOutput(GPIOC, 6);
  SysTick_Config(SystemCoreClock / 1000); //Make SysTick to Tick at 1[ms] and call SysTick_Handler()

  //We need these GPIO settings to enable USAR2 PINs on PA2 and PA3 (Table 13 Datasheet, AF1)
  GPIO_InitAlternateF(GPIOA, 2, 1);
  GPIO_InitAlternateF(GPIOA, 3, 1);
  UART_Init(USART2,115200, 0); //Init USART2 (VCOM) at 115,200 BR

  /********************************************************************
    Infinite Loop
  ********************************************************************/
  while(1)
  {
    if(beacon)
    {
      beacon = 0;
      UART_TxStr(USART2,"Hello Program...\n\r");
    }
    if(GPIO_Read(GPIOA, 0))
    {//If CTR is pressed
      GPIO_Set(GPIOB, 5); //Turn ON YELLOW LED
    }
    else
    {
      GPIO_Clear(GPIOB, 5); //Turn OFF YELLOW LED
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
}


/*  This event Handler gets called every 1[ms] according to Systick Configuration
    This is technically not an ISR, therefore it requires no flag clearing
*/
void SysTick_Handler(void)
{
  if(++msCounter > 499)
  {
    GPIO_Toggle(GPIOC, 6);
    //GPIO_Toggle(GPIOB, 5);//Toggle GREEN LED
    msCounter = 0;
    beacon = 1;   
  }
  if(msCounter % 125 == 0)
  {
    GPIO_Toggle(GPIOB, 4); //Toggle RED LED
  }
  if(msCounter % 250 == 0)
  {
    GPIO_Toggle(GPIOB, 9);//Toggle GREEN LED
  }
}
