//******************
//I2C Library
//
// CREATED: 01/28/2025, by Carlos Estay
//
// FILE: i2c.h
//



#ifndef I2C_H
#define I2C_H

#include "stm32g0xx.h"

typedef enum I2C_Speed_Typedef__
{
  I2C_Standard = 0x00503D58,    //100KHz
  I2C_Fast =     0x00300617,    //400KHz
  I2C_fastPlus = 0x00200105     //1MHz
}I2C_Speed;



void I2C_Init(I2C_TypeDef* i2c, I2C_Speed speed);
void I2C_Reset(I2C_TypeDef* i2c);
int I2C_IsBusy(I2C_TypeDef* i2c);
void  I2C_ScanFirstAddr(I2C_TypeDef* i2c);
int I2C_Transmit(I2C_TypeDef* i2c, uint8_t addr, uint8_t* pData, uint8_t size);
int I2C_Writereg(I2C_TypeDef* i2c, uint8_t addr, uint8_t reg, uint8_t* pData, uint8_t size);






#endif /* I2C */

// I2C library
//
// Basic I2C functions, intended to be used in device specific libraries
//
// Simon Walker
// Created September 2024, initial build
// 
// Version 1.0
//
////////////////////////////////////////////////////////////////////////

#ifndef I2C_HS
#define I2C_HS

typedef enum
{
  _I2C_AutoEnd_Software = 0,
  _I2C_AutoEnd_Hardware = 1
} _I2C_AutoEndOption;

typedef enum
{
  _I2C_BusState_Idle = 0,
  _I2C_BusState_Busy = 1
} _I2C_BusState;

int _I2C1_Init (void);
int _I2C1_IsBusy (void);
int _I2C1_StartWrite (unsigned char address, unsigned char bytecount, unsigned char * pData, _I2C_AutoEndOption endoption);
int _I2C1_StartRead (unsigned char address, unsigned char bytecount, unsigned char * pData, _I2C_AutoEndOption endoption);
void _I2C1_BusScan (unsigned char * pAddressTable);

#endif /* I2C */