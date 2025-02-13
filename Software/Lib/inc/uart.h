//******************
//UART Library
//
// CREATED: 11/05/2023, by Carlos Estay
//
// FILE: uart.h
//
#ifndef UART_H
#define UART_H

#include "stm32g031xx.h"


/// @brief 
/// @param  UartStructPtr
/// @param  BaudRate
/// @param  Interrupt 
void UART_Init(USART_TypeDef*, uint32_t, char);

/// @brief 
/// @param  UartStructPtr
/// @param  byte
void UART_TxByte(USART_TypeDef*, uint8_t);

/// @brief 
/// @param  string
void UART_TxStr(USART_TypeDef*, const char*);

/// @brief 
/// @param  array
void UART_TxBuffer(USART_TypeDef*, uint8_t*);

/// @brief read a byte, non-blocking,
/// @param  pointer to a character
/// @return 1 if byte read, 0 if not
uint8_t UART_RxByte(USART_TypeDef* , uint8_t*); 


#endif /* UART_H */