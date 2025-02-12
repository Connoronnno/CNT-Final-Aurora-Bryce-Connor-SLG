//******************
//GPIO Library
//
// CREATED: 10/27/2023, by Carlos Estay
//
// FILE: gpio.h
//
#include "stm32g031xx.h"

#ifndef GPIO_H
#define GPIO_H

typedef enum GPIO_IO_ModeTypedef__
{
  IO_None = 0b00,
  IO_PullUp = 0b01,
  IO_PullDown = 0b10,
  IO_Mask = 0b11
}IO_Mode;

  /// @brief Set GPIO pin as output
  /// @param  GPIO Port
  /// @param GPIO pin 
  void GPIO_InitInput(GPIO_TypeDef*, uint16_t);
  /// @brief Set GPIO pin as input
  /// @param  GPIO Port
  /// @param GPIO pin  
  void GPIO_InitOutput(GPIO_TypeDef*, uint16_t);
  /// @brief Set pull-up or pull-down
  /// @param  GPIO Port
  /// @param GPIO pin  
  /// @param  mode
  void GPIO_SetIO(GPIO_TypeDef*, uint16_t, IO_Mode);
  /// @brief Set alternate function (AFx MUX)
  /// @param  GPIO Port
  /// @param GPIO pin   
  /// @param AF 
  void GPIO_InitAlternateF(GPIO_TypeDef*, uint16_t, uint16_t);
  /// @brief Set bit in Port
  /// @param Port 
  /// @param pin  
  void GPIO_Set(GPIO_TypeDef*, uint16_t);
  /// @brief Clear bit in Port
  /// @param Port 
  /// @param pin  
  void GPIO_Clear(GPIO_TypeDef*, uint16_t);
  /// @brief Toggle bit in Port
  /// @param Port 
  /// @param pin   
  void GPIO_Toggle(GPIO_TypeDef* , uint16_t);
  /// @brief Reads pin in Port
  /// @param Port 
  /// @param pin       
  int GPIO_Read(GPIO_TypeDef*, uint16_t);

#endif /* GPIO_H */