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
  Use PB9 for testing ADC time
  */
  GPIO_InitOutput(GPIOB, 9);

  /*
  Uee PB4 to test timer manually toggling a PIN
  */
  GPIO_InitOutput(GPIOB, 4);

  //Enable built in LED (PC6)
  GPIO_InitOutput(GPIOC, 6);
  SysTick_Config(SystemCoreClock / 1000); //Make SysTick to Tick at 1[ms] and call SysTick_Handler()

  //We need these GPIO settings to enable USAR2 PINs on PA2 and PA3 (Table 13 Datasheet, AF1)
  GPIO_InitAlternateF(GPIOA, 2, 1);
  GPIO_InitAlternateF(GPIOA, 3, 1);
  UART_Init(USART2,115200, 0); //Init USART2 (VCOM) at 115,200 BR

  /*ADC settings*/
  ADC_Init(ADC1, ADC1_COMMON, ADC_Presc_10, ADC_Channel_0);


  //Timer setting - run at 1MHz - Reload at 100 (100[us])
  Timer_Setup(TIM17, 40, 100);
  //Enable counter overflow interrupt only (very simple approach)
  Timer_EnableInterrupt(TIM17, TIM17_IRQn, TimUIE);
  Timer_SetEnable(TIM17, 1); //Start timer

  /********************************************************************
    Infinite Loop
  ********************************************************************/
  while(1)
  {
    if(convTrigger)
    {
      convTrigger = 0;
      //No longer triggering the conversion here
    }
    if(beacon)
    {
      beacon = 0;
      UART_TxStr(USART2,"Hello Program...\n\r");
      printf("Hello Program...\n\r"); //Send same to debug console
      printf("AN0: %u\n\r", adcRead); //Send same to debug console
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

/*
  - This Handler includes all interrupts for TIM17
  - To handle a specific interrupt, mask the proper flag
  - NVIC_ClearPendingIRQ must be called always, aside 
    from clearing the flag bit, to service the interrupt completely
*/
void TIM17_IRQHandler(void)
{
  
  if(TIM17->SR & TIM_SR_UIF)
  {//Counter overflow flag called the ISR
    TIM17->SR &= ~TIM_SR_UIF; //clear overflow flag
    NVIC_ClearPendingIRQ(TIM17_IRQn);
    GPIO_Toggle(GPIOB,4);
    GPIO_Set(GPIOB, 9);//ADC conversion test PIN
    /*We have to be careful here as this ISR is being called every 100[us]*/
    ADC_TriggerConv(ADC1); //The conversion of 1 channel is taking around 5[us] with ADC @4MHz 
    adcRead = ADC_Read(ADC1);
    convTrigger = 0;
    GPIO_Clear(GPIOB, 9);//ADC conversion test PIN1`    
  }
}
