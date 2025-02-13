//LCD library source code
//Created by Aurora :)
//MUCH INSPIRATION taken from: https://blog.embeddedexpert.io/?p=488
#include "lcd.h"

void static LCD_Init(void)
{
//Set PB3 as SPI_CLK
GPIO_InitAlternateF(GPIOB, 3, 0);
//Set PB5 as SPI_MOSI (data control)
GPIO_InitAlternateF(GPIOB, 5, 0);
//Set PB10 as output for LCD Reset
GPIO_InitOutput(GPIOB, 10);
}