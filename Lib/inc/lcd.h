//LCD library source code
//Created by Aurora :)
//MUCH INSPIRATION taken from: https://blog.embeddedexpert.io/?p=488
#include "gpio.h"
#include "spi.h"
#include "timer.h"
#include "clock.h"

#include "timer.h"

//Prototypes for functions start here
void LCD_Init(void);

void LCD_Data(uint8_t data);

void LCD_Cmd(uint8_t command);
