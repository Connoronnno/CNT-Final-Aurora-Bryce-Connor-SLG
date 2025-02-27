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
#include "timer.h"
#include "gpio.h"
#include "uart.h"
#include "spi.h"
#include "../inc/lcd.h"
/*********************************************************************
  Local Prototypes
*********************************************************************/
void HAL_Init(void);

/*********************************************************************
  Global variables 
*********************************************************************/

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
  Clock_EnableOutput(MCO_Sel_SYSCLK, MCO_Div4); //Enables clock output on PA8 and divides it by 1
  //SysTick_Config(SystemCoreClock / 1000); //Make SysTick to Tick at 1[ms]

  Timer_SetDelay_us(TIM17); //this is just to set the prescaler
  SPI_Init(SPI1, DIV_2);
  LCD_Init();
  /********************************************************************
    Infinite Loop
  ********************************************************************/
  while(1)
  {
    //does nothing
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
  
  //does nothing
}