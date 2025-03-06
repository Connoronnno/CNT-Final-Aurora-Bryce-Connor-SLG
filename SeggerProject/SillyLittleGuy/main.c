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
#include "spi.h"
#include "ADXL343.h"
#include "i2c.h"
/*********************************************************************
  Local Prototypes
*********************************************************************/
void HAL_Init(void);

/*********************************************************************
  Global variables 
*********************************************************************/

volatile uint16_t msCounter = 0;
volatile uint8_t beacon = 0;

char buffer[100];

unsigned char addr;

unsigned char accelX;
unsigned char accelY;
unsigned char accelZ;
unsigned char steps;
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
  Clock_EnableOutput(MCO_Sel_SYSCLK, MCO_Div4); //Enables clock output on PA8 and divides it by 1
  GPIO_InitOutput(GPIOC, 6);
  GPIO_InitOutput(GPIOB, 5);
  SysTick_Config(SystemCoreClock / 1000); //Make SysTick to Tick at 1[ms]

  //We need these GPIO settings to enable USAR2 PINs on PA2 and PA3 (Table 13 Datasheet, AF1)
  GPIO_InitAlternateF(GPIOA, 2, 1);
  GPIO_InitAlternateF(GPIOA, 3, 1);

  GPIO_InitAlternateF(GPIOA, 1, 0);
  GPIO_InitAlternateF(GPIOA, 7, 0);

  UART_Init(USART2,115200, 0); //Init USART2 (VCOM) at 115,200 BR


  _I2C1_Init(); // PB6:SCL , PB7:SDA; 
  _ADXL343_Init();


  ///*Init I2C Module*/
  //I2C_Init(I2C1, I2C_Standard);

 printf("1");

  ////Pedometer Setup
  _ADXL343_WriteReg8(0x19, 0x02);
  ////wait 
  printf("2");
  _ADXL343_WriteReg8(0x7C, 0x01);
  _ADXL343_WriteReg8(0x1A, 0x38);
  _ADXL343_WriteReg8(0x1B, 0x04);
  _ADXL343_WriteReg8(0x1F, 0x80);
  _ADXL343_WriteReg8(0x21, 0x80);



  //  //Step Counter
  _ADXL343_WriteReg8(0x18, 0x01); // enable walking mode
  _ADXL343_WriteReg8(0x20, 0x01); // enable step interrupt
  _ADXL343_WriteReg8(0x59, 0x01); // step ctr config

  printf("3");

  /********************************************************************
    Infinite Loop
  ********************************************************************/
  while(1)
  {
    if(beacon)
    {
      beacon = 0;
      //UART_TxStr(USART2,"Hello Program...\n\r");
      //printf("Hello Console...\n\r");

      _ADXL343_ReadReg8(0x04, &accelX);
      _ADXL343_ReadReg8(0x06, &accelY);
      _ADXL343_ReadReg8(0x08, &accelZ);

      sprintf(buffer, "X:%d - Y:%d - Z:%d \n", accelX, accelY, accelZ);
      printf(buffer);

      _ADXL343_ReadReg8(0x15, &steps);

      sprintf(buffer, "Steps: %d \n", steps);
      printf(buffer);

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
  
  GPIO_Toggle(GPIOB, 5);
  if(++msCounter > 99)
  {
    GPIO_Toggle(GPIOC, 6);
    msCounter = 0;
    beacon = 1;   
  }
}