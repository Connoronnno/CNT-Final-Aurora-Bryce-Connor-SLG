//******************
//I2C Library
//
// CREATED: 01/28/2025, by Carlos Estay
//
// FILE: i2c.c
//

#include "i2c.h"

void I2C_Init(I2C_TypeDef* i2c, I2C_Speed speed)
{//Defaulted to 7-bit address
  i2c->CR1 &=  ~I2C_CR1_PE;             //Disable peripheral, to configure it
  i2c->TIMINGR = speed;                //Set speed mode
  i2c->OAR1 &= ~I2C_OAR1_OA1EN; 
  //Must diable own address before any setting can be added, add settings here
  i2c->OAR1 |= I2C_OAR1_OA1EN;          //Receiver address is ACKed, Addr 0
  i2c->CR2 &= ~I2C_CR2_ADD10;           //7-bit address
  i2c->CR2 |= I2C_CR2_AUTOEND | I2C_CR2_NACK; //Autoend mode (STOP condition), enable NACK(disable in salve mode)
  i2c->CR1 |= I2C_CR1_PE;               //Enable I2C
}
//---------------------------------------------------------------
void I2C_Reset(I2C_TypeDef* i2c)
{
  i2c->CR1 &=  ~I2C_CR1_PE;
}
//---------------------------------------------------------------
int I2C_Transmit(I2C_TypeDef* i2c, uint16_t addr, uint8_t* pData, uint8_t size)
{
  while(I2C_IsBusy(i2c));   //Wait until I2C is not busy

  /*Device address*/
  addr &= 0x7F;                     //Mask address to 7-bit
  addr <<=1;                        //Shift addr by 1
  i2c->CR2 &= ~I2C_CR2_SADD_Msk;   //Clear address
  i2c->CR2 |= addr;               //Write address

  /*Number of bytes to write*/  

  i2c->CR2 &= ~I2C_CR2_NBYTES_Msk;          //Clear NBytes
  i2c->CR2 |= size << I2C_CR2_NBYTES_Pos;  //Set number of bytes to write

  i2c->CR2 |= /*I2C_CR2_STOP |*/ I2C_CR2_AUTOEND;

  /*Send start condition*/
  i2c->CR2 |= I2C_CR2_START;  

  for (int i = 0; i < size; i++)
  {
    i2c->TXDR = *pData++;
    while(!(i2c->ISR & I2C_ISR_TXIS))  //Wait for TXDR to be empty
    {
      if(i2c->ISR & I2C_ISR_NACKF)
      {
        i2c->ICR |= I2C_ICR_NACKCF;
        return 0;
      }
    }
    /*Insert timeout later writing a 1 to TXE bit to flush*/
    //i2c->ISR |= I2C_ISR_TXE;
  }  
  return 1;
}
int I2C_IsBusy(I2C_TypeDef* i2c)
{
  return (i2c->ISR & I2C_ISR_BUSY);
}
//---------------------------------------------------------------


