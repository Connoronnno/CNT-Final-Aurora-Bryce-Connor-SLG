//LCD library source code
//Created by Aurora :)
//MUCH INSPIRATION taken from: https://blog.embeddedexpert.io/?p=488
#include "gpio.h"
#include "spi.h"
#include "timer.h"
#include "clock.h"

#include "timer.h"

//Define GPIO commands (pull pins low/high)
#define LCD_CS_HIGH GPIOA->BSRR|=GPIO_BSRR_BS4
#define LCD_CS_LOW GPIOA->BSRR|=GPIO_BSRR_BR4
//Reset control
#define LCD_RST_HIGH GPIOA->BSRR|=GPIO_BSRR_BS0
#define LCD_RST_LOW GPIOA->BSRR|=GPIO_BSRR_BR0
//Data command control
#define	LCD_DC_HIGH GPIOA->BSRR|=GPIO_BSRR_BS1 //DATA Mode
#define	LCD_DC_LOW GPIOA->BSRR|=GPIO_BSRR_BR1 //CMD Mode

//Prototypes for functions start here
void LCD_Init(void);

void LCD_Data(uint8_t data);

void LCD_Cmd(uint8_t command);

//Data and Cmd both leverage this
void LCD_Send(uint8_t sendme);