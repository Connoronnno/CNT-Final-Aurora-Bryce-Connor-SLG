//LCD library source code
//Created by Aurora :)
//MUCH INSPIRATION taken from: https://blog.embeddedexpert.io/?p=488
#include "lcd.h"

void LCD_Init(void)
{
//Slave select (CS) pin (PA4)
GPIO_InitAlternateF(GPIOA, 4, 0);

//Set PA5 as SPI_CLK
GPIO_InitAlternateF(GPIOA, 5, 0);

//Set PA7 as SPI_MOSI (output line)
GPIO_InitAlternateF(GPIOA, 7, 0);

//Set PA0 as output for LCD Reset
GPIO_InitOutput(GPIOA, 0);

//1 as data and command control
GPIO_InitOutput(GPIOA, 1);

//Reset=0
GPIO_Clear(GPIOA, 0);
Timer_Delay_us(TIM17, 10000); //delay 10 ms
//Reset=1
GPIO_Set(GPIOA, 0);
Timer_Delay_us(TIM17, 10000); //delay 10 ms

//CS=0
GPIO_Clear(GPIOA, 4);
//Start sending commands
LCD_Cmd(0x11);
Timer_Delay_us(TIM17, 10000); //delay 10 ms
LCD_Cmd(0x3A);
LCD_Data(0x05);
LCD_Cmd(0x36);
LCD_Data(0x14);
LCD_Cmd(0x29);
}

void LCD_Cmd(uint8_t command)
{
GPIO_Clear(GPIOA, 4);
GPIO_Clear(GPIOA, 1);
SPI_TxByte(SPI1, command);
Timer_Delay_us(TIM17, 2);
GPIO_Set(GPIOA, 4);
}

void LCD_Data(uint8_t data)
{
GPIO_Clear(GPIOA, 4);
GPIO_Set(GPIOA, 1);                     
SPI_TxByte(SPI1, data);
Timer_Delay_us(TIM17, 2);
GPIO_Set(GPIOA, 4);
}
