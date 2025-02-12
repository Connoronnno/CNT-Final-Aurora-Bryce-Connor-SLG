/*********************************************************************

File    : main.c
Program : Template Project
Author  : Carlos Estay
Purpose : PWM1 Demo. Variable Duty cycle on An7 (TIM17->CH1, CN4 PIN5)
          - Timer set to 1MHz-> 1[us] Ticks
          - Period set to 100 ticks -> 100[us]->10KHz PWM frequency
          - Duty variable between 1 and 99
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
volatile uint8_t beacon = 0, dutyUpdate = 0;
/*********************************************************************
  Main entry
*********************************************************************/
int main(void) 
{
  uint16_t duty = 25;
  /********************************************************************
    One-time Initializations
  ********************************************************************/  
  
  HAL_Init(); //this is needed when working at higher clock speeds (> 24MHz)
  Clock_InitPll(PLL_40MHZ); //Enable Pll to 40MHz
  printf("System Clock: %u Hz\n\r", SystemCoreClock); //print system clock result
  Clock_EnableOutput(MCO_Sel_SYSCLK, MCO_Div1); //Enables clock output on PA8 and divides it factor


  //Enable built in LED (PC6)
  GPIO_InitOutput(GPIOC, 6);
  SysTick_Config(SystemCoreClock / 1000); //Make SysTick to Tick at 1[ms] and call SysTick_Handler()

  //We need these GPIO settings to enable USAR2 PINs on PA2 and PA3 (Table 13 Datasheet, AF1)
  GPIO_InitAlternateF(GPIOA, 2, 1);
  GPIO_InitAlternateF(GPIOA, 3, 1);
  UART_Init(USART2,115200, 0); //Init USART2 (VCOM) at 115,200 BR


  /*
    PWM settings
    -PWM generation on TIM17->CH1
    -Have to setup alternate function: PA7->AF5 (CN4->PIN 5)
  */
  GPIO_InitAlternateF(GPIOA, 7, 5);

  //Timer setting - Run at 1MHz - Reload at 100 (100[us])
  Timer_Setup(TIM17, 40, 100);
  //PWM mode 1 on Timwe17, Channel 1
  Timer_SetupChannel(TIM17, TimCCR1, Pwm1);
  Timer_WriteCCR(TIM17, TimCCR1, duty);//Set duty
  Timer_SetEnable(TIM17, 1); //Start timer

  


  /********************************************************************
    Infinite Loop
  ********************************************************************/
  while(1)
  {
    if(dutyUpdate)
    {
      dutyUpdate = 0;
      //change duty cycle here
      if(++duty > 99)
      {
        duty = 1;
      }
      Timer_WriteCCR(TIM17, TimCCR1, duty);
    }
    if(beacon)
    {
      beacon = 0;
      UART_TxStr(USART2,"Hello Program...\n\r");
      printf("Hello Program...\n\r"); //Send same to debug console
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
  if(msCounter%25 == 0)
  {//update duty every 25[ms]
    dutyUpdate = 1;
  }
  if(++msCounter > 499)
  {
    GPIO_Toggle(GPIOC, 6);
    
    msCounter = 0;
    beacon = 1;   
  }
}
 
/****************Interrupt Service Routines (ISR's)***********************/

