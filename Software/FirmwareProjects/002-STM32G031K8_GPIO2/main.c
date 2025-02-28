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
#include "minmea.h"
#include "uart.h"

/*********************************************************************

  Local Prototypes

*********************************************************************/

void HAL_Init(void);
 
/*********************************************************************

  Global variables 

*********************************************************************/
 
volatile uint16_t msCounter = 0;
volatile uint16_t i = 0;
volatile uint8_t beacon = 0;
volatile uint16_t thi = 1000; 
struct minmea_sentence_rmc rmcStruct;
unsigned char buffer[128];
volatile float lat;
volatile float lon;

/*********************************************************************

  Main entry

*********************************************************************/

int main(void){

  /********************************************************************

    One-time Initializations

  ********************************************************************/  

  HAL_Init(); //this is needed when working at higher clock speeds (> 24MHz)

  Clock_InitPll(PLL_40MHZ); //Enable Pll to 40MHz

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

  GPIO_InitAlternateF(GPIOA, 9, 1);

  GPIO_InitAlternateF(GPIOA, 10, 1);

  UART_Init(USART2,115200, 0); //Init USART2 (VCOM) at 115,200 BR

  UART_Init(USART1, 9600, 0);
  buffer[0] = 'A';
  buffer[1] = 'B';

  /********************************************************************

    Infinite Loop

  ********************************************************************/

  while(1)

  {
    
    i=0;
    while(true){
    if(UART_RxByte(USART1, &buffer[i]))
    {
      if(buffer[i]=='\n') break;
      i++;
    }
    }
    printf(buffer);
   if(minmea_parse_rmc(&rmcStruct, buffer)){
    printf("FIX?:");
    lat = minmea_tocoord(&rmcStruct.latitude);
    lon = minmea_tocoord(&rmcStruct.longitude);
    sprintf(buffer, "lat:%d, %d", (int)(lat*100), (int)(lon*100));
    if(rmcStruct.valid!=0)
    {printf(buffer);
  }}
  buffer[0] = '\0';
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

  RCC->APBENR2 |= RCC_APBENR2_USART1EN_Msk;    //Enable USART1

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

 