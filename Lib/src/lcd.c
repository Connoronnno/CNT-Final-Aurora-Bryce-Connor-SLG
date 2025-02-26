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

LCD_RST_LOW;
Timer_Delay_us(TIM17, 10000); //delay 10 ms
LCD_RST_HIGH;
Timer_Delay_us(TIM17, 10000); //delay 10 ms
LCD_CS_LOW;
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
LCD_CS_LOW;
LCD_DC_HIGH;
LCD_Send(command);
LCD_CS_HIGH;
}

void LCD_Data(uint8_t data)
{
LCD_CS_LOW;
LCD_DC_LOW;
LCD_Send(data);
LCD_CS_HIGH;
}

void LCD_Send(uint8_t sendme)
{
SPI_TxByte(SPI1, sendme);
}
