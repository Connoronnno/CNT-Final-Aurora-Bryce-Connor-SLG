//LCD library source code
//Created by Aurora :)
//MUCH INSPIRATION taken from: https://blog.embeddedexpert.io/?p=488
#include "gpio.h"
#include "spi.h"
//Define GPIO commands (pull pins low/high)

//Reset control
#define LCD_RST_HIGH GPIOB->BSRR|=GPIO_BSRR_BS10
#define LCD_RST_LOW GPIOB->BSRR|=GPIO_BSRR_BR10
//Data command control
#define	LCD_DC_HIGH GPIOB->BSRR|=GPIO_BSRR_BS4 //DATA Mode
#define	LCD_DC_LOW GPIOB->BSRR|=GPIO_BSRR_BR4 //CMD Mode

//Prototypes for functions start here
void static LCD_Init(void);

void static LCD_Data(char data);

void static LCD_Cmd(char command);

//Data and Cmd both leverage this
void static LCD_Send(char sendme);