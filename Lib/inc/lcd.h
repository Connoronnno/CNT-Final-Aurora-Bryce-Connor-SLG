//LCD library source code
//Created by Aurora :)
//MUCH INSPIRATION taken from: https://blog.embeddedexpert.io/?p=488
#include "gpio.h"
//Define GPIO commands (pull pins low/high)

//Prototypes for functions start here
void static LCD_Init(void);

void static LCD_Write(char command);
