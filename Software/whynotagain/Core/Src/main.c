/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  * SOURCES(WIP):
  * https://github.com/dekuNukem/STM32_tutorials/blob/master/lesson1_serial_helloworld/HAL_UART_Transmit_details.md
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "ST7735.h"
#include "GFX_FUNCTIONS.h"
#include "minmea.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
//PEdometer
#include "i2c.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
typedef enum _menuState {
	StatsDisplay,
	Main,
	MusicTest,
	ConnorDemo
}menuStates;
struct latLon
{
 float lat;
 float lon;
};
struct gameInfo
{
	struct minmea_time time;
	unsigned char evo; //0=Egg, 1=Baby, 2=Adult
	unsigned char mood; //Implement mood states here
	unsigned int numLocations; //number of locations
	struct latLon positions[32];
	unsigned int allSteps;
    unsigned int weeklySteps;
    unsigned int stepsToday;
    unsigned int challengeGoal;
    char uid[32];
	//need to implement:
	//current time
	//weekly steps
	//steps today
};

struct Img
{
	uint16_t* Body;
	unsigned int Size;
};
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
struct gameInfo game;
struct latLon dummy;
volatile uint16_t msCounter = 0;
volatile uint16_t i = 0;
volatile char rmcCheck;
volatile uint16_t ii = 0;
volatile uint8_t beacon = 0;
volatile uint16_t thi = 1000;
volatile uint16_t whileI=0;
volatile uint16_t petXPos;
const uint16_t dayLength=24;
const uint16_t weekLength=168;
struct minmea_sentence_rmc rmcStruct;
struct minmea_sentence_gga ggaStruct;
char buffer[128];
char sendBuffer[400];
unsigned int updateScreen = 0;
uint16_t testImage [296][2] = {{0, 789}, {1, 4}, {0, 59}, {1, 1}, {3, 4}, {1, 1}, {0, 58}, {1, 1}, {3, 2}, {1, 1}, {3, 1}, {4, 1}, {1, 5}, {0, 52}, {1, 1}, {3, 5}, {4, 1}, {3, 5}, {1, 2}, {0, 50}, {1, 1}, {3, 5}, {4, 1}, {3, 7}, {1, 2}, {0, 48}, {1, 1}, {3, 15}, {1, 1}, {0, 47}, {1, 1}, {3, 5}, {1, 3}, {3, 7}, {1, 1}, {0, 39}, {1, 9}, {3, 4}, {1, 2}, {5, 2}, {1, 1}, {4, 1}, {3, 6}, {1, 1}, {0, 27}, {1, 2}, {0, 8}, {1, 1}, {3, 6}, {4, 2}, {1, 1}, {3, 4}, {1, 2}, {5, 2}, {1, 1}, {4, 1}, {3, 6}, {1, 1}, {0, 27}, {1, 1}, {4, 1}, {1, 1}, {0, 6}, {1, 1}, {3, 7}, {4, 2}, {1, 1}, {3, 4}, {6, 1}, {5, 1}, {1, 3}, {4, 1}, {3, 7}, {1, 1}, {0, 26}, {1, 1}, {4, 2}, {1, 6}, {3, 9}, {4, 1}, {1, 1}, {3, 5}, {6, 1}, {1, 2}, {4, 1}, {3, 8}, {1, 2}, {0, 25}, {1, 2}, {4, 6}, {1, 1}, {3, 10}, {1, 1}, {3, 17}, {1, 1}, {2, 1}, {1, 1}, {0, 24}, {1, 1}, {3, 1}, {1, 1}, {4, 4}, {1, 1}, {3, 11}, {1, 1}, {3, 17}, {1, 1}, {2, 2}, {1, 1}, {0, 23}, {1, 1}, {3, 2}, {1, 5}, {3, 11}, {1, 1}, {3, 17}, {1, 3}, {0, 24}, {1, 1}, {3, 19}, {1, 1}, {3, 15}, {1, 1}, {0, 27}, {1, 1}, {3, 15}, {1, 3}, {3, 1}, {1, 1}, {3, 15}, {1, 1}, {0, 27}, {1, 1}, {3, 14}, {1, 1}, {2, 2}, {1, 1}, {3, 2}, {1, 1}, {3, 13}, {1, 2}, {0, 27}, {1, 2}, {3, 12}, {1, 1}, {2, 4}, {1, 3}, {3, 13}, {1, 2}, {0, 28}, {1, 6}, {3, 7}, {1, 1}, {2, 4}, {1, 1}, {0, 2}, {1, 2}, {3, 9}, {1, 2}, {2, 1}, {1, 1}, {0, 33}, {1, 1}, {3, 7}, {1, 1}, {2, 4}, {1, 1}, {0, 4}, {1, 2}, {3, 5}, {1, 2}, {2, 3}, {1, 1}, {0, 33}, {1, 1}, {3, 7}, {1, 1}, {2, 4}, {1, 1}, {0, 6}, {1, 5}, {2, 5}, {1, 1}, {0, 34}, {1, 1}, {3, 6}, {1, 1}, {2, 4}, {1, 1}, {0, 8}, {1, 1}, {2, 7}, {1, 1}, {0, 34}, {1, 1}, {3, 6}, {1, 1}, {2, 4}, {1, 1}, {0, 9}, {1, 1}, {2, 7}, {1, 1}, {0, 33}, {1, 1}, {3, 6}, {1, 1}, {2, 4}, {1, 1}, {0, 10}, {1, 2}, {2, 5}, {1, 1}, {0, 32}, {1, 1}, {3, 7}, {1, 1}, {2, 4}, {1, 1}, {0, 12}, {1, 6}, {0, 26}, {1, 2}, {0, 4}, {1, 1}, {3, 7}, {1, 1}, {2, 4}, {1, 1}, {0, 44}, {1, 1}, {3, 1}, {1, 1}, {0, 3}, {1, 1}, {3, 7}, {1, 1}, {2, 3}, {1, 1}, {0, 45}, {1, 1}, {3, 2}, {1, 3}, {3, 8}, {1, 1}, {2, 2}, {1, 2}, {0, 45}, {1, 1}, {3, 13}, {1, 1}, {2, 1}, {1, 2}, {0, 46}, {1, 1}, {3, 13}, {1, 2}, {3, 1}, {1, 1}, {0, 46}, {1, 1}, {3, 12}, {1, 2}, {3, 2}, {1, 1}, {0, 46}, {1, 1}, {3, 7}, {1, 5}, {3, 4}, {1, 1}, {0, 47}, {1, 7}, {0, 4}, {1, 1}, {3, 5}, {1, 1}, {0, 57}, {1, 1}, {3, 6}, {1, 1}, {0, 57}, {1, 1}, {3, 6}, {1, 1}, {0, 57}, {1, 1}, {3, 6}, {1, 2}, {0, 56}, {1, 2}, {3, 6}, {1, 1}, {0, 57}, {1, 7}, {0, 936}};
uint16_t imgSitting0[307][2] = {{0, 1152}, {3, 2}, {0, 62}, {3, 1}, {4, 1}, {3, 1}, {0, 3}, {1, 7}, {0, 51}, {3, 1}, {4, 2}, {1, 4}, {2, 6}, {1, 1}, {0, 17}, {1, 7}, {0, 26}, {3, 1}, {4, 6}, {3, 1}, {2, 6}, {1, 1}, {0, 7}, {1, 9}, {2, 7}, {1, 2}, {0, 24}, {3, 1}, {4, 7}, {3, 1}, {2, 6}, {1, 1}, {0, 5}, {1, 1}, {4, 9}, {3, 1}, {2, 8}, {1, 1}, {0, 23}, {3, 1}, {4, 8}, {3, 3}, {2, 3}, {1, 1}, {0, 4}, {1, 1}, {4, 3}, {3, 1}, {1, 2}, {5, 1}, {4, 4}, {3, 1}, {2, 6}, {1, 1}, {0, 24}, {3, 3}, {4, 9}, {3, 3}, {1, 1}, {0, 3}, {1, 1}, {4, 3}, {3, 1}, {6, 1}, {1, 3}, {5, 1}, {4, 4}, {3, 1}, {2, 4}, {1, 1}, {0, 25}, {3, 1}, {4, 1}, {3, 1}, {4, 12}, {3, 1}, {0, 2}, {1, 1}, {4, 4}, {1, 2}, {6, 2}, {1, 1}, {5, 1}, {4, 5}, {3, 1}, {2, 1}, {1, 2}, {0, 26}, {3, 1}, {4, 1}, {3, 3}, {4, 11}, {3, 2}, {4, 5}, {1, 2}, {6, 2}, {1, 1}, {5, 1}, {4, 6}, {1, 1}, {0, 28}, {3, 1}, {4, 4}, {3, 3}, {4, 9}, {3, 1}, {4, 6}, {1, 3}, {4, 8}, {1, 1}, {0, 28}, {3, 1}, {4, 14}, {5, 1}, {3, 1}, {4, 2}, {3, 1}, {4, 1}, {5, 1}, {4, 13}, {1, 1}, {0, 28}, {3, 1}, {4, 13}, {5, 2}, {3, 1}, {4, 4}, {5, 2}, {4, 12}, {1, 1}, {0, 28}, {3, 6}, {4, 8}, {5, 2}, {3, 1}, {4, 4}, {5, 2}, {4, 12}, {1, 1}, {0, 28}, {3, 1}, {4, 13}, {5, 2}, {3, 1}, {4, 4}, {5, 2}, {4, 12}, {1, 1}, {0, 28}, {3, 1}, {4, 14}, {5, 1}, {3, 1}, {4, 2}, {3, 1}, {4, 1}, {5, 1}, {4, 13}, {1, 1}, {0, 28}, {3, 1}, {4, 4}, {3, 3}, {4, 9}, {3, 1}, {4, 6}, {1, 3}, {4, 8}, {1, 1}, {0, 28}, {3, 1}, {4, 1}, {3, 3}, {4, 11}, {3, 2}, {4, 5}, {1, 2}, {6, 2}, {1, 1}, {5, 1}, {4, 6}, {1, 1}, {0, 28}, {3, 1}, {4, 1}, {3, 1}, {4, 12}, {3, 1}, {0, 2}, {1, 1}, {4, 4}, {1, 2}, {6, 2}, {1, 1}, {5, 1}, {4, 5}, {3, 1}, {2, 1}, {1, 2}, {0, 26}, {3, 3}, {4, 9}, {3, 3}, {1, 1}, {0, 3}, {1, 1}, {4, 3}, {3, 1}, {6, 1}, {1, 3}, {5, 1}, {4, 4}, {3, 1}, {2, 4}, {1, 1}, {0, 25}, {3, 1}, {4, 8}, {3, 3}, {2, 3}, {1, 1}, {0, 4}, {1, 1}, {4, 3}, {3, 1}, {1, 2}, {5, 1}, {4, 4}, {3, 1}, {2, 6}, {1, 1}, {0, 24}, {3, 1}, {4, 7}, {3, 1}, {2, 6}, {1, 1}, {0, 5}, {1, 1}, {4, 9}, {3, 1}, {2, 8}, {1, 1}, {0, 23}, {3, 1}, {4, 6}, {3, 1}, {2, 6}, {1, 1}, {0, 7}, {1, 9}, {2, 7}, {1, 2}, {0, 24}, {3, 1}, {4, 2}, {1, 4}, {2, 6}, {1, 1}, {0, 17}, {1, 7}, {0, 26}, {3, 1}, {4, 1}, {3, 1}, {1, 1}, {0, 2}, {1, 7}, {0, 51}, {3, 2}, {4, 1}, {1, 1}, {0, 60}, {1, 1}, {4, 3}, {1, 1}, {0, 59}, {1, 1}, {4, 3}, {1, 1}, {0, 59}, {1, 1}, {4, 3}, {1, 1}, {0, 59}, {1, 1}, {4, 2}, {1, 1}, {0, 60}, {1, 1}, {4, 2}, {1, 1}, {0, 60}, {1, 1}, {4, 2}, {1, 1}, {0, 60}, {1, 1}, {4, 2}, {1, 1}, {0, 60}, {1, 1}, {4, 1}, {1, 1}, {0, 61}, {1, 2}, {0, 830}};
uint16_t imgSitting1[305][2] = {{0, 1152}, {3, 2}, {0, 62}, {3, 1}, {4, 1}, {3, 1}, {0, 3}, {1, 8}, {0, 50}, {3, 1}, {4, 2}, {1, 4}, {2, 7}, {1, 1}, {0, 16}, {1, 7}, {0, 26}, {3, 1}, {4, 6}, {3, 1}, {2, 7}, {1, 1}, {0, 6}, {1, 9}, {2, 7}, {1, 2}, {0, 24}, {3, 1}, {4, 7}, {3, 1}, {2, 7}, {1, 1}, {0, 4}, {1, 1}, {4, 9}, {3, 1}, {2, 8}, {1, 1}, {0, 23}, {3, 1}, {4, 8}, {3, 3}, {2, 4}, {1, 1}, {0, 3}, {1, 1}, {4, 3}, {3, 1}, {1, 2}, {5, 1}, {4, 4}, {3, 1}, {2, 6}, {1, 1}, {0, 24}, {3, 3}, {4, 9}, {3, 3}, {2, 1}, {1, 1}, {0, 2}, {1, 1}, {4, 3}, {3, 1}, {6, 1}, {1, 3}, {5, 1}, {4, 4}, {3, 1}, {2, 4}, {1, 1}, {0, 25}, {3, 1}, {4, 1}, {3, 1}, {4, 12}, {3, 1}, {0, 2}, {1, 1}, {4, 4}, {1, 2}, {6, 2}, {1, 1}, {5, 1}, {4, 5}, {3, 1}, {2, 1}, {1, 2}, {0, 26}, {3, 1}, {4, 1}, {3, 3}, {4, 11}, {3, 2}, {4, 5}, {1, 2}, {6, 2}, {1, 1}, {5, 1}, {4, 6}, {1, 1}, {0, 28}, {3, 1}, {4, 4}, {3, 3}, {4, 9}, {3, 1}, {4, 6}, {1, 3}, {4, 8}, {1, 1}, {0, 28}, {3, 1}, {4, 14}, {5, 1}, {3, 1}, {4, 2}, {3, 1}, {4, 1}, {5, 1}, {4, 13}, {1, 1}, {0, 28}, {3, 1}, {4, 13}, {5, 2}, {3, 1}, {4, 4}, {5, 2}, {4, 12}, {1, 1}, {0, 28}, {3, 6}, {4, 8}, {5, 2}, {3, 1}, {4, 4}, {5, 2}, {4, 12}, {1, 1}, {0, 28}, {3, 1}, {4, 13}, {5, 2}, {3, 1}, {4, 4}, {5, 2}, {4, 12}, {1, 1}, {0, 28}, {3, 1}, {4, 14}, {5, 1}, {3, 1}, {4, 2}, {3, 1}, {4, 1}, {5, 1}, {4, 13}, {1, 1}, {0, 28}, {3, 1}, {4, 4}, {3, 3}, {4, 9}, {3, 1}, {4, 6}, {1, 3}, {4, 8}, {1, 1}, {0, 28}, {3, 1}, {4, 1}, {3, 3}, {4, 11}, {3, 2}, {4, 5}, {1, 2}, {6, 2}, {1, 1}, {5, 1}, {4, 6}, {1, 1}, {0, 28}, {3, 1}, {4, 1}, {3, 1}, {4, 12}, {3, 1}, {0, 2}, {1, 1}, {4, 4}, {1, 2}, {6, 2}, {1, 1}, {5, 1}, {4, 5}, {3, 1}, {2, 1}, {1, 2}, {0, 26}, {3, 3}, {4, 9}, {3, 3}, {2, 1}, {1, 1}, {0, 2}, {1, 1}, {4, 3}, {3, 1}, {6, 1}, {1, 3}, {5, 1}, {4, 4}, {3, 1}, {2, 4}, {1, 1}, {0, 25}, {3, 1}, {4, 8}, {3, 3}, {2, 4}, {1, 1}, {0, 3}, {1, 1}, {4, 3}, {3, 1}, {1, 2}, {5, 1}, {4, 4}, {3, 1}, {2, 6}, {1, 1}, {0, 24}, {3, 1}, {4, 7}, {3, 1}, {2, 7}, {1, 1}, {0, 4}, {1, 1}, {4, 9}, {3, 1}, {2, 8}, {1, 1}, {0, 23}, {3, 1}, {4, 6}, {3, 1}, {2, 7}, {1, 1}, {0, 6}, {1, 9}, {2, 7}, {1, 2}, {0, 24}, {3, 1}, {4, 2}, {1, 4}, {2, 7}, {1, 1}, {0, 16}, {1, 7}, {0, 26}, {3, 1}, {4, 1}, {3, 1}, {1, 1}, {0, 2}, {1, 8}, {0, 50}, {3, 2}, {4, 1}, {1, 1}, {0, 60}, {1, 1}, {4, 2}, {1, 1}, {0, 60}, {1, 1}, {4, 2}, {1, 1}, {0, 60}, {1, 1}, {4, 2}, {1, 1}, {0, 60}, {1, 1}, {4, 3}, {1, 1}, {0, 59}, {1, 1}, {4, 3}, {1, 2}, {0, 58}, {1, 1}, {4, 4}, {1, 2}, {0, 58}, {1, 1}, {4, 4}, {1, 1}, {0, 59}, {1, 5}, {0, 889}};
struct Img sitting0;
struct Img sitting1;
struct Img animSitting[2];
unsigned int currentFrame = 0;
volatile uint16_t palette[8] = {BLACK, BLACK, YELLOW, BLUE, GREEN, BLUE, WHITE, WHITE};
volatile float lat;
volatile float lon;
volatile double freq;
volatile double freqs[] = {440*2, 332*2, 365*2, 274*2, 292*2, 220*2, 290*2, 322*2,};
volatile uint16_t toneIndex=0;
//Pedometer Variables
char buffer2[100];

unsigned char accelX;
unsigned char accelY;
unsigned char accelZ;
unsigned char steps=0;

menuStates currentMenu = Main;
char canChange = 1;

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
I2C_HandleTypeDef hi2c1;

RTC_HandleTypeDef hrtc;

SPI_HandleTypeDef hspi1;

TIM_HandleTypeDef htim17;

UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C1_Init(void);
static void MX_SPI1_Init(void);
static void MX_TIM17_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_RTC_Init(void);
/* USER CODE BEGIN PFP */
void Animate (struct Img* animation, unsigned int size);
int _ADXL343_ReadReg8 (unsigned char TargetRegister, unsigned char * TargetValue, uint8_t size);
int _ADXL343_WriteReg8 (unsigned char TargetRegister, unsigned char TargetValue);
void SendData();
void GetLatLon();
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */
  steps=0;
  sitting0.Body = *imgSitting0;
  sitting0.Size = 307;
  sitting1.Body = *imgSitting1;
  sitting1.Size = 305;
  animSitting[0] = sitting0;
  animSitting[1] = sitting1;
  game.evo=0;
  game.uid[0]='h';
  game.uid[1]='i';
  game.allSteps=0;
  game.mood=100;
  game.numLocations=3;
  game.stepsToday=0;
  game.weeklySteps=0;
  game.challengeGoal=20000;
  dummy.lat=12.34567;
  dummy.lon=-89.10111;
  game.positions[0]=dummy;
  game.positions[1]=dummy;
  game.positions[2]=dummy;
  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_I2C1_Init();
  MX_SPI1_Init();
  MX_TIM17_Init();
  MX_USART1_UART_Init();
  MX_USART2_UART_Init();
  //MX_RTC_Init();
  /* USER CODE BEGIN 2 */
  //HAL_TIM_PWM_Start(&htim17, TIM_CHANNEL_1);
  ST7735_Unselect();
  ST7735_Init(1);
  //testAll();
  buffer[0] = 'A';
  buffer[1] = 'B';
  TIM17->CCR1 = 5;
  TIM17->PSC=64;
  uint8_t ret=0;
    //_ADXL343_Init();

      //Pedometer Setup
      _ADXL343_WriteReg8(0x19, 0x02);
      ////wait

      _ADXL343_WriteReg8(0x7C, 0x01);
       _ADXL343_WriteReg8(0x1A, 0x38);
      _ADXL343_WriteReg8(0x1B, 0x04);
      _ADXL343_WriteReg8(0x1F, 0x80);
      _ADXL343_WriteReg8(0x21, 0x80);



      //  //Step Counter
      _ADXL343_WriteReg8(0x18, 0x01); // enable walking mode
      _ADXL343_WriteReg8(0x20, 0x01); // enable step interrupt
      //_ADXL343_WriteReg8(0x59, 0x01); // step ctr config
  //HAL_UART_Receive(&huart1, &buffer, 1, 0xFFFF);
  //testAll();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
      //Before entering the while, fill the screen to clear it once
      fillScreen(BLACK);
  while (1)
  {
	  SendData();
	  if((game.time.hours%dayLength)==0) game.stepsToday=0;
	  if((game.time.hours%weekLength)==0) game.weeklySteps=0;
	  game.stepsToday +=steps-game.allSteps;
	  game.weeklySteps+=steps-game.allSteps;
	  game.allSteps=steps;
	  //SendData();
	  //HAL_UART_Transmit(&huart2, "hello", 5, 100);
	  switch(currentMenu){
	  case Main:


		  if((++updateScreen)>=5)
		  {
			  //Animate character
			  Animate(animSitting,1);
			  updateScreen = 0;
			  //Update steps
			  _ADXL343_ReadReg8(0x15, &steps, 1);
			  sprintf(buffer2, "Steps today: %d ", steps);
			  drawString(0, 20, buffer2, WHITE, BLACK, 1, 1);
		  }


		  //Change current Menu
		  if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_12) == GPIO_PIN_SET ) {
			  HAL_TIM_PWM_Start(&htim17, TIM_CHANNEL_1);
			  currentMenu = MusicTest;
			  canChange = 0;
			  fillScreen(BLACK);
		  }
		  else if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_11) == GPIO_PIN_SET ) {
			  currentMenu = StatsDisplay;
			  canChange = 0;
			  fillScreen(BLACK);
		  }
		  else
			  canChange = 1;


		  break;
	  case StatsDisplay:

		  if((++updateScreen)>=5)
		  {
			  //fillScreen(BLACK);

			  drawString(0, 120, "STEPS", WHITE, BLACK, 1, 1);
			  sprintf(buffer2, "Today: %d ", game.stepsToday);
			  drawString(0, 110, buffer2, WHITE, BLACK, 1, 1);
			  sprintf(buffer2, "This week: %d ", game.weeklySteps);
			  drawString(0, 100, buffer2, WHITE, BLACK, 1, 1);
			  sprintf(buffer2, "All time: %d ", game.allSteps);
			  drawString(0, 90, buffer2, WHITE, BLACK, 1, 1);

			  //drawString(0, 70, "PET", WHITE, BLACK, 1, 1);
			  updateScreen = 0;
		  }
	  	  if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_12) == GPIO_PIN_SET ){
	  		currentMenu = Main;
	  		canChange = 0;
	  		fillScreen(BLACK);
	  	  }
	  	  else
	  	      canChange = 1;

	  	  break;
	  case MusicTest:
		  //fillScreen(BLUE);

		  freq = freqs[(toneIndex++)%8];
		  TIM17->ARR=(uint32_t)(987*(float)1000/(float)freq);

		  if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_11) == GPIO_PIN_SET) {
			  currentMenu = Main;
			  canChange = 0;
			  HAL_TIM_PWM_Stop(&htim17, TIM_CHANNEL_1);
			  fillScreen(BLACK);
		  }
		  else
			  canChange = 1;

		  break;
	  case ConnorDemo:
		  	  steps=0;

		  	  if((whileI++)%3==0)
		  		  if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_1) == GPIO_PIN_SET)
		  		  		  fillScreen(WHITE);
		  		  	  else
		  		  		  fillScreen(BLACK);
		  	  if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_11) == GPIO_PIN_SET)
		  		  petXPos-=5;
		  	  if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_12) == GPIO_PIN_SET)
		  		  petXPos+=5;
		  	  if(petXPos<3)petXPos=0;
		  	  if(petXPos>60) petXPos=60;
		  	  freq = freqs[(toneIndex++)%8];
		  	  TIM17->ARR=(uint32_t)(987*(float)1000/(float)freq);
		  	  //fillScreen(WHITE);
		  	  drawImage(testImage, palette, petXPos, 40, 64, 64, 296);
//		  	  drawImage(testImage, palette, 10, 40, 64, 64);
//		  	  drawImage(testImage, palette, 70, 40, 64, 64);
//		  	  drawImage(testImage, palette, 100, 40, 64, 64);
//		  	  _ADXL343_ReadReg8(0x04, &accelX, 1);
//		  	  _ADXL343_ReadReg8(0x05, &accelY, 1);
//		  	  _ADXL343_ReadReg8(0x06, &accelZ, 1);
//		  	  _ADXL343_ReadReg8(0x07, &accelX, 1);
//		  	  _ADXL343_ReadReg8(0x08, &accelY, 1);
//		  	  _ADXL343_ReadReg8(0x09, &accelZ, 1);

		  	  sprintf(buffer2, "X:%d - Y:%d - Z:%d ", accelX, accelY, accelZ);
		  	  drawString(0, 10, buffer2, BLACK, GREEN, 1, 1);

		  	  _ADXL343_ReadReg8(0x15, &steps, 1);
		  	  sprintf(buffer2, "Steps: %d ", steps);
		  	  drawString(0, 20, buffer2, BLACK, GREEN, 1, 1);

		  	  	  //only run this code every few seconds

		  	  drawString(70, 70, buffer, BLACK, GREEN, 1, 1);

		  break;
	  }





    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_LSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSIDiv = RCC_HSI_DIV1;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = RCC_PLLM_DIV1;
  RCC_OscInitStruct.PLL.PLLN = 8;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.Timing = 0x10B17DB5;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Analogue filter
  */
  if (HAL_I2CEx_ConfigAnalogFilter(&hi2c1, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Digital filter
  */
  if (HAL_I2CEx_ConfigDigitalFilter(&hi2c1, 0) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief RTC Initialization Function
  * @param None
  * @retval None
  */
static void MX_RTC_Init(void)
{

  /* USER CODE BEGIN RTC_Init 0 */

  /* USER CODE END RTC_Init 0 */

  RTC_TimeTypeDef sTime = {0};
  RTC_DateTypeDef sDate = {0};
  RTC_AlarmTypeDef sAlarm = {0};

  /* USER CODE BEGIN RTC_Init 1 */

  /* USER CODE END RTC_Init 1 */

  /** Initialize RTC Only
  */
  hrtc.Instance = RTC;
  hrtc.Init.HourFormat = RTC_HOURFORMAT_24;
  hrtc.Init.AsynchPrediv = 127;
  hrtc.Init.SynchPrediv = 255;
  hrtc.Init.OutPut = RTC_OUTPUT_DISABLE;
  hrtc.Init.OutPutRemap = RTC_OUTPUT_REMAP_NONE;
  hrtc.Init.OutPutPolarity = RTC_OUTPUT_POLARITY_HIGH;
  hrtc.Init.OutPutType = RTC_OUTPUT_TYPE_OPENDRAIN;
  hrtc.Init.OutPutPullUp = RTC_OUTPUT_PULLUP_NONE;
  if (HAL_RTC_Init(&hrtc) != HAL_OK)
  {
    Error_Handler();
  }

  /* USER CODE BEGIN Check_RTC_BKUP */

  /* USER CODE END Check_RTC_BKUP */

  /** Initialize RTC and set the Time and Date
  */
  sTime.Hours = 0x0;
  sTime.Minutes = 0x0;
  sTime.Seconds = 0x0;
  sTime.SubSeconds = 0x0;
  sTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
  sTime.StoreOperation = RTC_STOREOPERATION_RESET;
  if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BCD) != HAL_OK)
  {
    Error_Handler();
  }
  sDate.WeekDay = RTC_WEEKDAY_MONDAY;
  sDate.Month = RTC_MONTH_JANUARY;
  sDate.Date = 0x1;
  sDate.Year = 0x0;

  if (HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BCD) != HAL_OK)
  {
    Error_Handler();
  }

  /** Enable the Alarm A
  */
  sAlarm.AlarmTime.Hours = 0x0;
  sAlarm.AlarmTime.Minutes = 0x0;
  sAlarm.AlarmTime.Seconds = 0x1;
  sAlarm.AlarmTime.SubSeconds = 0x0;
  sAlarm.AlarmTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
  sAlarm.AlarmTime.StoreOperation = RTC_STOREOPERATION_RESET;
  sAlarm.AlarmMask = RTC_ALARMMASK_NONE;
  sAlarm.AlarmSubSecondMask = RTC_ALARMSUBSECONDMASK_ALL;
  sAlarm.AlarmDateWeekDaySel = RTC_ALARMDATEWEEKDAYSEL_DATE;
  sAlarm.AlarmDateWeekDay = 0x1;
  sAlarm.Alarm = RTC_ALARM_A;
  if (HAL_RTC_SetAlarm_IT(&hrtc, &sAlarm, RTC_FORMAT_BCD) != HAL_OK)
  {
    Error_Handler();
  }

  /** Enable the WakeUp
  */
  if (HAL_RTCEx_SetWakeUpTimer_IT(&hrtc, 0x500B, RTC_WAKEUPCLOCK_RTCCLK_DIV16) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN RTC_Init 2 */

  /* USER CODE END RTC_Init 2 */

}

/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_1LINE;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_32;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 7;
  hspi1.Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;
  hspi1.Init.NSSPMode = SPI_NSS_PULSE_ENABLE;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

}

/**
  * @brief TIM17 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM17_Init(void)
{

  /* USER CODE BEGIN TIM17_Init 0 */

  /* USER CODE END TIM17_Init 0 */

  TIM_OC_InitTypeDef sConfigOC = {0};
  TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig = {0};

  /* USER CODE BEGIN TIM17_Init 1 */

  /* USER CODE END TIM17_Init 1 */
  htim17.Instance = TIM17;
  htim17.Init.Prescaler = 0;
  htim17.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim17.Init.Period = 65535;
  htim17.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim17.Init.RepetitionCounter = 0;
  htim17.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim17) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim17) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCNPolarity = TIM_OCNPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
  sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
  if (HAL_TIM_PWM_ConfigChannel(&htim17, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  sBreakDeadTimeConfig.OffStateRunMode = TIM_OSSR_DISABLE;
  sBreakDeadTimeConfig.OffStateIDLEMode = TIM_OSSI_DISABLE;
  sBreakDeadTimeConfig.LockLevel = TIM_LOCKLEVEL_OFF;
  sBreakDeadTimeConfig.DeadTime = 0;
  sBreakDeadTimeConfig.BreakState = TIM_BREAK_DISABLE;
  sBreakDeadTimeConfig.BreakPolarity = TIM_BREAKPOLARITY_HIGH;
  sBreakDeadTimeConfig.BreakFilter = 0;
  sBreakDeadTimeConfig.AutomaticOutput = TIM_AUTOMATICOUTPUT_DISABLE;
  if (HAL_TIMEx_ConfigBreakDeadTime(&htim17, &sBreakDeadTimeConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM17_Init 2 */

  /* USER CODE END TIM17_Init 2 */
  HAL_TIM_MspPostInit(&htim17);

}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 9600;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart1.Init.ClockPrescaler = UART_PRESCALER_DIV1;
  huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetTxFifoThreshold(&huart1, UART_TXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetRxFifoThreshold(&huart1, UART_RXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_DisableFifoMode(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  huart2.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart2.Init.ClockPrescaler = UART_PRESCALER_DIV1;
  huart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetTxFifoThreshold(&huart2, UART_TXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetRxFifoThreshold(&huart2, UART_RXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_DisableFifoMode(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  /* USER CODE BEGIN MX_GPIO_Init_1 */
  /* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_15, GPIO_PIN_RESET);

  /*Configure GPIO pin : PC1 */
  GPIO_InitStruct.Pin = GPIO_PIN_1;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : PA4 PA5 PA15 */
  GPIO_InitStruct.Pin = GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PA11 PA12 */
  GPIO_InitStruct.Pin = GPIO_PIN_11|GPIO_PIN_12;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* USER CODE BEGIN MX_GPIO_Init_2 */
  /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
//AURORA: Put custom functions here!
void Animate (struct Img* animation, unsigned int size)
{
	++currentFrame;
	if(currentFrame > size)
	{
		currentFrame = 0;
	}
	drawImage(animation[currentFrame].Body, palette, 40, 40, 64, 64, animation[currentFrame].Size);
	return;
}
int _ADXL343_ReadReg8 (unsigned char TargetRegister, unsigned char * TargetValue, uint8_t size)
{
  if (!HAL_I2C_Master_Transmit(&hi2c1, 0x14<<1, &TargetRegister, 1, 1000)==HAL_OK)
      return -1;

  if (!HAL_I2C_Master_Receive(&hi2c1, 0x14<<1, TargetValue, size, 1000)==HAL_OK)
    return -2;

  return 0;
}

int _ADXL343_WriteReg8 (unsigned char TargetRegister, unsigned char TargetValue)
{
  unsigned char buff [2];
  buff[0] = TargetRegister;
  buff[1] = TargetValue;

  if (HAL_I2C_Master_Transmit(&hi2c1, 0x14<<1, buff, 2, 100))
      return -1;

  return 0;
}
void SendData()
{
	unsigned int posIndex;
	unsigned int clrIndex;
	sprintf(sendBuffer, "(lifeSteps:%d),(weeklySteps:%d),(dailySteps:%d),(uid:%s),(friendship:%d),(password:password)(difficulty:%d),(evolution:%d) \n\r", game.allSteps,game.weeklySteps,game.stepsToday, game.uid, game.mood, game.challengeGoal, game.evo);
	HAL_UART_Transmit(&huart2, sendBuffer, strlen(sendBuffer), 200);
	for(posIndex=0; posIndex<game.numLocations; posIndex++)
	{       HAL_Delay(5);
		for(clrIndex=0;clrIndex<400;clrIndex++) sendBuffer[clrIndex]=0;
		sprintf(sendBuffer, "[(lat:%d.%d), (lon:%d.%d)],", ((int)game.positions[posIndex].lat), abs((int)((fmod((double)game.positions[posIndex].lat, (double)1))*10000)),((int)game.positions[posIndex].lon), abs((int)((fmod((double)game.positions[posIndex].lon, (double)1))*10000)));
		HAL_UART_Transmit(&huart2, sendBuffer, strlen(sendBuffer), 200);

	}
}
void GetLatLon()
{
	struct latLon pos;
	while(HAL_UART_Receive(&huart1, &(buffer[i]), 1, 0xFFFF)==HAL_OK)
			  		  	{
			  			  if(buffer[i]&&buffer[i]=='\n')
			  				  {
			  				  if(minmea_parse_rmc(&rmcStruct, &(buffer[1]))){
			  				      pos.lat = minmea_tocoord(&rmcStruct.latitude);
			  				      pos.lon = minmea_tocoord(&rmcStruct.longitude);
			  				      game.time = rmcStruct.time;
			  				  }
			  				if(minmea_parse_gga(&ggaStruct, &(buffer[2]))){
			  							  				      pos.lat = minmea_tocoord(&ggaStruct.latitude);
			  							  				      pos.lon = minmea_tocoord(&ggaStruct.longitude);
			  							  				      game.time = ggaStruct.time;
			  							  				  }
			  				  for(ii=0;ii<=i;ii++) buffer[ii]=0;
			  				 i=0;
			  				 break;
			  				  }
			  			  	        i++;

			  		  	}

	game.positions[game.numLocations] = pos;
	game.numLocations++;
}
void HAL_RTC_AlarmAEventCallback(RTC_HandleTypeDef *hrtc) {
  RTC_AlarmTypeDef sAlarm;
  HAL_RTC_GetAlarm(hrtc,&sAlarm,RTC_ALARM_A,FORMAT_BIN);
  if(sAlarm.AlarmTime.Seconds>58) {
    sAlarm.AlarmTime.Seconds=0;
  }else{
    sAlarm.AlarmTime.Seconds=sAlarm.AlarmTime.Seconds+1;
  }
    while(HAL_RTC_SetAlarm_IT(hrtc, &sAlarm, FORMAT_BIN)!=HAL_OK){}
  	  drawString(30, 30, "testTime", BLACK, GREEN, 1, 1);
}


/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
