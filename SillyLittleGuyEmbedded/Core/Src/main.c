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
#include "tiny-json.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
typedef enum _menuState {
	StatsDisplay,
	Main,
	MusicTest,
	ConnorDemo,
	Settings
}menuStates;
struct latLon
{
 float lat;
 float lon;
};
enum Scale
{
    A = 440,
    B = 494,
    C = 523,
    D = 587,
    E = 659,
    F = 698,
    G = 784
};
enum Scale curNote;

enum SoundEffects {
    MenuBeep,
    EggNoise,
    YoungNoiseHappy,
	YoungNoiseSad,
    AdultNoiseHappy,
	AdultNoiseSad,
	Evolution
};
enum SoundEffects effect;

enum Buttons{
	Left=0,
	Center=1,
	Rght=2
};

enum ButtonState
{
	LOW = 0,
	HIGH = 1
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
    unsigned int dailyGoal;
    unsigned int weeklyGoal;
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

//changeable expressions
const float expDivisor = 4.0f;
const uint16_t dayLength=24;
const uint16_t weekLength=168;
const float gpsThreshold = .0001;
const int moodIncrementUp=1;
const int moodIncrementDown=1;
const int mehMood=1;
const int happyMood=2;
const int sadMood = 0;
uint16_t checkTime=1;
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
volatile enum Scale scale[] = {A, B, C, D, E, F, G, F, E, D, C, B, A};


struct minmea_sentence_rmc rmcStruct;
struct minmea_sentence_gga ggaStruct;
uint16_t totalFrames=0;
char frameGot = 0;
char buffer[128];
char sendBuffer[400];
char syncBuffer[3000];
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

unsigned int currentSetting = 0;
unsigned int editDifficulty = 0;
unsigned int userUpload = 0;

char buttonStates[] = {0,0,0};
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
void ChangeNote(enum Scale freq);
void PlayEffect(enum SoundEffects effect);
void HAL_GPIO_EXTI_Rising_Callback(uint16_t GPIO_Pin);
void PeripheralInit(void);
void StructInit(void);
void Animate (struct Img* animation, unsigned int frameCount, unsigned int xPos, unsigned int yPos, unsigned int xSize, unsigned int ySize);
int _ADXL343_ReadReg8 (unsigned char TargetRegister, unsigned char * TargetValue, uint8_t size);
int _ADXL343_WriteReg8 (unsigned char TargetRegister, unsigned char TargetValue);
void SendData();
void GetLatLon();
struct latLon GetJustLatLon();
void ReceiveData();
int CheckExp(int threshold, int comparer);
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
  StructInit();
  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_I2C1_Init();
  MX_SPI1_Init();
  MX_TIM17_Init();
  MX_USART1_UART_Init();
  MX_USART2_UART_Init();
  MX_RTC_Init();
  /* USER CODE BEGIN 2 */
  PeripheralInit();
  //HAL_TIM_PWM_Start(&htim17, TIM_CHANNEL_1);

  //testAll();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
      //Before entering the while, fill the screen to clear it once
      fillScreen(BLACK);
  while (1)
  {
	  _ADXL343_ReadReg8(0x15, &steps, 1);

	  //SendData();
	  //ReceiveData();
	  //_ADXL343_ReadReg8(0x00, &steps, 1);
	  if(CheckExp(game.dailyGoal, game.stepsToday)==1)
	  {
		  game.mood+=moodIncrementUp;
		  game.stepsToday=0;
	  }
	  if(checkTime){
	  if(((game.time.minutes%dayLength)==0) && game.time.seconds>0){
		  if(CheckExp(game.dailyGoal, game.stepsToday)==-1)game.mood-=moodIncrementDown;
		  game.stepsToday=0;
		  memset(&game.positions, 0, sizeof(game.positions));
		  game.numLocations=0;
		  checkTime=0;
	  }

	  if(((game.time.minutes%weekLength)==0) && game.time.seconds>0){
		  game.weeklySteps=0;
		  checkTime=0;
	  }
	  }
	  if((game.time.minutes%dayLength)==1) checkTime=1;
	  if(steps!=0){
	  game.stepsToday +=steps;
	  game.weeklySteps+=steps;
	  game.allSteps+=steps;
	  steps=0;
	  _ADXL343_WriteReg8(0x7E, 0xB1);
	  }
	  ++updateScreen;
	  //SendData();
	  //HAL_UART_Transmit(&huart2, "hello", 5, 100);
	  switch(currentMenu){
	  case Main:
		  if((totalFrames)%600==0) GetLatLon();


		  if(updateScreen>=5)
		  {
			  updateScreen = 0;
			  //Animate character
			  switch(game.evo)
			  {
			  case 0:
				  //Animate as the egg
				  break;
			  case 1:
				  //Animate as the baby
				  Animate(animSitting,1,30,30,64,64);
				  break;
			  case 2:
				  //Animate as the adult
				  break;
			  }

			  //Update steps
			  drawString(0,150,"-SILLY LITTLE GUY-",WHITE,BLACK,1,1);
			  sprintf(buffer2, "Steps: %d ", game.stepsToday);
			  drawString(0, 10, buffer2, WHITE, BLACK, 1, 1);
			  Emote();
		  }

		  //Interact with the SLG
		  if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_1) == GPIO_PIN_SET )
		  {
			  effect = Evolution;
			  PlayEffect(effect);
			  game.stepsToday = game.dailyGoal;
			  FlashWrite();
			  StructInit();
		  }


		  //Change current Menu
		  if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_2) == GPIO_PIN_SET ) {
			  effect = MenuBeep;
			  PlayEffect(effect);

			  currentMenu = Settings;
			  canChange = 0;
			  fillScreen(BLACK);
		  }
		  else if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_11) == GPIO_PIN_SET ) {
			  effect = MenuBeep;
			  PlayEffect(effect);

			  currentMenu = StatsDisplay;
			  canChange = 0;
			  fillScreen(BLACK);
		  }
		  else
			  canChange = 1;


		  break;
	  case StatsDisplay:

		  if(updateScreen>=5)
		  {
			  //fillScreen(BLACK);

			  drawString(0, 150, "STEPS", WHITE, BLACK, 1, 1);
			  sprintf(buffer2, "Today: %d ", game.stepsToday);
			  drawString(0, 140, buffer2, WHITE, BLACK, 1, 1);
			  sprintf(buffer2, "This week: %d ", game.weeklySteps);
			  drawString(0, 130, buffer2, WHITE, BLACK, 1, 1);
			  sprintf(buffer2, "All time: %d ", game.allSteps);
			  drawString(0, 120, buffer2, WHITE, BLACK, 1, 1);
			  drawString(0, 110, "POSITIONS", WHITE, BLACK, 1,1);
			  sprintf(buffer2, "Count/Mult: %d", game.numLocations);
			  drawString(0, 100, buffer2, WHITE, BLACK, 1, 1);
			  sprintf(buffer2, "Old Lat: %d.%d", (int)(game.positions[game.numLocations-1].lat), abs((int)(((game.positions[game.numLocations-1].lat)*10000))%10000));
			  drawString(0, 90, buffer2, WHITE, BLACK, 1, 1);
			  sprintf(buffer2, "Old Lon: %d.%d", (int)(game.positions[game.numLocations-1].lon), abs((int)(((game.positions[game.numLocations-1].lon)*10000))%10000));
			  drawString(0, 80, buffer2, WHITE, BLACK, 1, 1);
			  if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_1)==GPIO_PIN_SET){
			  sprintf(buffer2, "Lat: %d.%d", (int)(GetJustLatLon().lat), abs(((int)((GetJustLatLon().lat)*10000))%10000));
			  drawString(0, 70, buffer2, WHITE, BLACK, 1, 1);
			  sprintf(buffer2, "Lon: %d.%d", (int)(GetJustLatLon().lon), abs((int)(((GetJustLatLon().lon)*10000))%10000));
			  drawString(0, 60, buffer2, WHITE, BLACK, 1, 1);
			  }
			  updateScreen = 0;
		  }
	  	  if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_2) == GPIO_PIN_SET ){
	  		effect = MenuBeep;
	  		PlayEffect(effect);

	  		currentMenu = Main;
	  		canChange = 0;
	  		fillScreen(BLACK);
	  	  }
	  	  else
	  	      canChange = 1;

	  	  break;

	  case Settings:
		  //Just commenting this out really quick so I can test my settings menu x)
		  //if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_1)==GPIO_PIN_SET)
		  //{
			  //SendData();
			  //ReceiveData();
		  //}

		  if(updateScreen>=2)
		  {
			  updateScreen = 0;
			  drawString(0, 150, "-OPTIONS-", WHITE, BLACK, 1, 1);
			  sprintf(buffer2, "GOAL: %d ", game.dailyGoal);
			  drawString(0, 130, buffer2, WHITE, BLACK, 1, 1); //Display the current difficulty
			  drawString(0,110,"UPLOAD DATA",WHITE,BLACK,1,1);
			  if(editDifficulty)
			  {
				  //Editing difficulty
				  drawLine(0,125,128,125,WHITE);
				  //GET OUT when the center button is pressed!
				  if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_1))
				  {
					  editDifficulty = 0;
					  drawLine(0,125,128,125,BLACK);
				  }
				  //Right increments the goal
				  else if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_2))
				  {
					  game.dailyGoal += 1000;
				  }
				  //Left decrements the goal
				  else if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_11))
				  {
					  game.dailyGoal -= 1000;
				  }

				  if(game.dailyGoal>=999000)
				  {
					  game.dailyGoal = 0;
				  }
				  else if (game.dailyGoal<=0)
				  {
					  game.dailyGoal=999000;
				  }
				  sprintf(buffer2, "DIFFICULTY: %d ", game.dailyGoal);

			  }
			  else if(userUpload)
			  {
				  userUpload=0;
				  SendData();
				  ReceiveData();
			  }
			  else{
			  //Difficulty
			  if(currentSetting==0)
			  {
				  //Try to underline the option being selected
				  drawLine(0,125,20,125,WHITE);
				  //Then erase the highlight under the other option not being selected
				  drawLine(0,105,20,105,BLACK);
			  }
			  //Upload
			  else if(currentSetting==1)
			  {
				  drawLine(0,105,20,105,WHITE);
				  drawLine(0,125,20,125,BLACK);
			  }
			  //IF RIGHT BUTTON IS PRESSED, INCREMENT THE SETTINGS MENU
			  if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_2) == GPIO_PIN_SET)
			  {
				  ++currentSetting;
				  if(currentSetting>1)
					  currentSetting=0;
			  }
			  //PD6=Center button
			  else if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_1) && currentSetting==0)
			  {
				  editDifficulty=1;
			  }
			  else if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_1) && currentSetting==1)
			  {
				  userUpload=1;
			  }
		  }
		  }

		  if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_11) == GPIO_PIN_SET && !editDifficulty) {
			  effect = MenuBeep;
			  PlayEffect(effect);

			  currentMenu = Main;
			  canChange = 0;
			  fillScreen(BLACK);
		  }
		  else
			  canChange = 1;
		  break;

	 /* case ConnorDemo:
		  	  steps=0;

		  	  if((whileI++)%3==0)
		  		  if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_1) == GPIO_PIN_SET)
		  		  		  fillScreen(WHITE);
		  		  	  else
		  		  		  fillScreen(BLACK);
		  	  if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_11) == GPIO_PIN_SET)
		  		  petXPos-=5;
		  	  if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_2) == GPIO_PIN_SET)
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

		  break;*/

	  }
	  totalFrames++;





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
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_15, GPIO_PIN_RESET);

  /*Configure GPIO pin : PC1 */
  GPIO_InitStruct.Pin = GPIO_PIN_1;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : PA0 PA4 PA5 PA15 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : PB2 */
  GPIO_InitStruct.Pin = GPIO_PIN_2;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : PA11 */
  GPIO_InitStruct.Pin = GPIO_PIN_11;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI0_1_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI0_1_IRQn);

  HAL_NVIC_SetPriority(EXTI2_3_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI2_3_IRQn);

  HAL_NVIC_SetPriority(EXTI4_15_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI4_15_IRQn);

  /* USER CODE BEGIN MX_GPIO_Init_2 */
  /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
void ChangeNote(enum Scale freq)
{
    TIM17->ARR=(uint32_t)(987*(float)1000/(float)freq);
}
void PlayEffect(enum SoundEffects effect) {
	HAL_TIM_PWM_Start(&htim17, TIM_CHANNEL_1);
	HAL_Delay(5);
    switch(effect){
        case MenuBeep:

        	curNote = G*3;
        	ChangeNote(curNote);
        	HAL_Delay(25);

        	curNote = G*2;
        	ChangeNote(curNote);
        	HAL_Delay(25);

            break;
        case EggNoise:

        	curNote = A;
        	ChangeNote(curNote);
        	HAL_Delay(20);

        	curNote = C;
        	ChangeNote(curNote);
        	HAL_Delay(20);

        	curNote = A;
        	ChangeNote(curNote);
        	HAL_Delay(20);

        	curNote = C;
        	ChangeNote(curNote);
        	HAL_Delay(20);

            break;
        case YoungNoiseHappy:

        	curNote = F*4;
        	ChangeNote(curNote);
        	HAL_Delay(35);

        	curNote = B*4;
        	ChangeNote(curNote);
        	HAL_Delay(15);

            break;
        case YoungNoiseSad:

        	curNote = B*4;
        	ChangeNote(curNote);
        	HAL_Delay(35);

        	curNote = B*3;
        	ChangeNote(curNote);
        	HAL_Delay(15);

            break;
        case AdultNoiseHappy:

        	curNote = F/4;
        	ChangeNote(curNote);
        	HAL_Delay(35);

        	curNote = B/4;
        	ChangeNote(curNote);
        	HAL_Delay(15);

            break;
        case AdultNoiseSad:

        	curNote = C/4;
        	ChangeNote(curNote);
        	HAL_Delay(35);

        	curNote = A/4;
        	ChangeNote(curNote);
        	HAL_Delay(15);

        	break;
        case Evolution:

        	curNote = A*2;
        	ChangeNote(curNote);
        	HAL_Delay(50);

        	curNote = B*2;
        	ChangeNote(curNote);
        	HAL_Delay(50);

        	curNote = C*2;
        	ChangeNote(curNote);
        	HAL_Delay(50);

        	curNote = A*2;
        	ChangeNote(curNote);
        	HAL_Delay(50);

        	curNote = C*2;
        	ChangeNote(curNote);
        	HAL_Delay(50);

        	curNote = D*2;
        	ChangeNote(curNote);
        	HAL_Delay(50);

        	curNote = B*2;
        	ChangeNote(curNote);
        	HAL_Delay(50);

        	curNote = D*2;
        	ChangeNote(curNote);
        	HAL_Delay(50);

        	curNote = E*2;
        	ChangeNote(curNote);
        	HAL_Delay(50);

        	curNote = G*2;
        	ChangeNote(curNote);
        	HAL_Delay(50);

        	curNote = G*2;
        	ChangeNote(curNote);
        	HAL_Delay(50);

        	break;
    }
    HAL_TIM_PWM_Stop(&htim17, TIM_CHANNEL_1);
}
//INTERRUPTS ARE CALLED BACK HERE
void HAL_GPIO_EXTI_Rising_Callback(uint16_t GPIO_Pin)
{
	/*//Center=2
	if(GPIO_PIN==2)
	{

	}
	//Right=4
	else if(GPIO_PIN==4)
	{

	}
	//Left=2048
	else if(GPIO_PIN==2048)
	{

	}*/
}


//AURORA: Put custom functions here!
void PeripheralInit(void)
{
	ST7735_Unselect();
	ST7735_Init(1);

	fillScreen(BLACK);
	buffer[0] = 'A';
	buffer[1] = 'B';
	TIM17->CCR1 = 5;
	TIM17->PSC=64;
	//uint8_t ret=0;
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
}
//INITIALIZE GAME VALUES
void StructInit(void)
{
	  steps=0;
	  uint32_t Address =  0x0803F800;
	  //ANIMATIONS FOR EGG
	  //egg0.Body = ;
	  //ANIMATIONS FOR BABY DRAGON
	  sitting0.Body = *imgSitting0;
	  sitting0.Size = 307;
	  sitting1.Body = *imgSitting1;
	  sitting1.Size = 305;
	  animSitting[0] = sitting0;
	  animSitting[1] = sitting1;

	  if((*(__IO uint64_t*) (Address))==(uint64_t)0x12345678)
	  {
		  Address+=8;
		  game.allSteps= (unsigned int)(*(__IO uint64_t*) (Address));
		  Address+=8;
		  game.stepsToday= (unsigned int)(*(__IO uint64_t*) (Address));
		  Address+=8;
		  game.weeklySteps= (unsigned int)(*(__IO uint64_t*) (Address));
		  Address+=8;
		  game.dailyGoal= (unsigned int)(*(__IO uint64_t*) (Address));
		  Address+=8;
		  game.weeklyGoal= (unsigned int)(*(__IO uint64_t*) (Address));
		  Address+=8;
		  game.evo = (unsigned char)(*(__IO uint64_t*) (Address));
		  Address+=8;
		  game.mood = (unsigned char)(*(__IO uint64_t*) (Address));
		  Address+=8;
		  game.numLocations = (unsigned int)(*(__IO uint64_t*) (Address));
		  for(int flashI=0; flashI<32; flashI++)
		  {
			  Address+=1;
			  game.uid[flashI] = (char)(*(__IO uint8_t*) (Address));
		  }
		  for(int flashI=0; flashI<32; flashI++)
		  {
			  Address+=8;
			  game.positions[flashI].lat = ((float)(*(__IO uint8_t*) (Address)))/100000;
			  Address+=8;
			  game.positions[flashI].lon = ((float)(*(__IO uint8_t*) (Address)))/100000;
		  }
	  }
	  else{
	  game.evo=1;
	  game.uid[0]='h';
	  game.uid[1]='i';
	  game.allSteps=0;
	  game.mood=1;
	  game.numLocations=3;
	  game.stepsToday=0;
	  game.weeklySteps=0;
	  game.dailyGoal=2000;
	  dummy.lat=12.34567;
	  dummy.lon=-89.10111;
	  game.positions[0]=dummy;
	  game.positions[1]=dummy;
	  game.positions[2]=dummy;
	  game.time.hours=0;
	  }
}
//Method for displaying the evolution animation
void Evolve()
{
	if(game.evo<2)
	{
		fillScreen(WHITE);
		fillScreen(BLACK);
		game.evo +=1;
	}

}
void FlashWrite()
{
	uint32_t Address =  0x0803F800;
	uint8_t flashBuffer[496] = "I am the very model of a modern major general.";
	uint64_t flashTestBuffer[496];
	uint64_t xyz=0;
	int chunkI=8;

	FLASH_EraseInitTypeDef tryit;
	tryit.Banks = FLASH_BANK_1;
	tryit.NbPages = 1;
	tryit.Page = 127;
	tryit.TypeErase =FLASH_TYPEERASE_PAGES;
	uint32_t pgerror;
	HAL_FLASH_Unlock();
	HAL_FLASHEx_Erase(&tryit, &pgerror);
	HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, Address, (uint64_t)0x12345678);
	Address+=8;
	HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, Address, (uint64_t)game.allSteps);
	Address+=8;
	HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, Address, (uint64_t)game.stepsToday);
	Address+=8;
	HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, Address, (uint64_t)game.weeklySteps);
	Address+=8;
	HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, Address, (uint64_t)game.dailyGoal);
	Address+=8;
	HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, Address, (uint64_t)game.weeklyGoal);
	Address+=8;
	HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, Address, (uint64_t)game.evo);
	Address+=8;
	HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, Address, (uint64_t)game.mood);
	Address+=8;
	HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, Address, (uint64_t)game.numLocations);
	Address+=8;
	for(int flashI=0; flashI<32; flashI++){
	xyz+=(game.uid[flashI])<<((8-(chunkI))*8);
	if(--chunkI==0){
		HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, Address, xyz);
		chunkI=8;
		xyz=0;
		Address+=8;
	}
	}
	for(int flashI=0; flashI<32; flashI++){
		HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, Address, (uint64_t)(game.positions[flashI].lat*100000));
		Address+=8;
		HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, Address, (uint64_t)(game.positions[flashI].lon*100000));
		Address+=8;
	}
	Address =  0x0803F808;
	xyz= *(__IO uint64_t*) (Address);
	HAL_FLASH_Lock();
}
void Animate (struct Img* animation, unsigned int frameCount, unsigned int xPos, unsigned int yPos, unsigned int xSize, unsigned int ySize)
{
	++currentFrame;
	if(currentFrame > frameCount)
	{
		currentFrame = 0;
	}
	drawImage(animation[currentFrame].Body, palette, xPos, yPos, xSize, ySize, animation[currentFrame].Size);
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

  if (HAL_I2C_Master_Transmit(&hi2c1, 0x14<<1, buff, 2, 1000)==HAL_OK)
      return -1;

  return 0;
}
void SendData()
{
	unsigned int posIndex;
	unsigned int clrIndex;
	sprintf(sendBuffer, "(lifeSteps:%d),(weeklySteps:%d),(dailySteps:%d),(uid:%s),(friendship:%d),(password:password),(difficulty:%d),(evolution:%d) \n\r", game.allSteps,game.weeklySteps,game.stepsToday, game.uid, game.mood, game.dailyGoal, game.evo);
	HAL_UART_Transmit(&huart2, sendBuffer, strlen(sendBuffer), 200);
	for(posIndex=0; posIndex<game.numLocations; posIndex++)
	{       HAL_Delay(5);
		for(clrIndex=0;clrIndex<400;clrIndex++) sendBuffer[clrIndex]=0;
		sprintf(sendBuffer, "(lat:%d.%d),(lon:%d.%d),", ((int)game.positions[posIndex].lat), abs((int)((fmod((double)game.positions[posIndex].lat, (double)1))*10000)),((int)game.positions[posIndex].lon), abs((int)((fmod((double)game.positions[posIndex].lon, (double)1))*10000)));
		HAL_UART_Transmit(&huart2, sendBuffer, strlen(sendBuffer), 200);

	}
}
void ReceiveData()
{
int rI=0;
while(HAL_UART_Receive(&huart2, &(syncBuffer[rI]), 1, 1000)==HAL_OK)
{
	if(syncBuffer[rI]&&syncBuffer[rI]=='\r')
	{
	 enum { MAX_FIELDS = 255 };
	 json_t pool[ MAX_FIELDS ];
	 json_t const* parent = json_create(syncBuffer, pool, MAX_FIELDS);
	 if(parent)
	 {
		 int locI=0;
		 struct latLon tempLoc;
		 char const* uidRxStr = json_getPropertyValue(parent, "uid");
		 //HAL_UART_Transmit(&huart2, json_getPropertyValue(parent, "uid"), strlen(json_getPropertyValue(parent, "uid")), 1000);
		 for(int strI =0; strI<strlen(uidRxStr); strI++) game.uid[strI]=uidRxStr[strI];
		 game.allSteps = (unsigned int)json_getInteger(json_getProperty(parent, "lifeSteps"));
		 game.dailyGoal = (unsigned int)json_getInteger(json_getProperty(parent, "difficulty"));
		 game.evo = (unsigned int)json_getInteger(json_getProperty(parent, "evolution"));
		 game.mood = (unsigned int)json_getInteger(json_getProperty(parent, "friendship"));
		 game.stepsToday = (unsigned int)json_getInteger(json_getProperty(parent, "dailySteps"));
		 game.weeklySteps = (unsigned int) json_getInteger(json_getProperty(parent, "weeklySteps"));
		 json_t const* location;
		 json_t const* locations = json_getProperty(parent, "locations");
		 for(location = json_getChild(locations); location; location=json_getSibling(location))
		{
			 tempLoc.lat = (float)json_getReal(json_getProperty(location, "lat"));
			 tempLoc.lon = (float)json_getReal(json_getProperty(location, "lng"));
			 if(fabs(tempLoc.lat)<.00001)
			 {

				 tempLoc.lat = (float)json_getReal(json_getProperty(location, "Lat"));
				 			 tempLoc.lon = (float)json_getReal(json_getProperty(location, "Lng"));
			 }
			 game.positions[locI] = tempLoc;
			 locI++;
		}
		game.numLocations = locI;
		for(locI=locI; locI<32; locI++)
		{
			memset(&game.positions[locI], 0, sizeof(game.positions[locI]));
		}
		 //SendData();
	 }
     for(ii=0;ii<=rI;ii++) syncBuffer[ii]=0;
     rI=0;
     break;
	}
	else
	{
		rI++;
	}
}

}
int CheckExp(int threshold, int comparer)
{
	int value = (int)((float)comparer*(1.0f+((float)game.numLocations)/expDivisor));
	if(value<(threshold/4)) return -1;
	if(value<threshold) return 0;
	if(value>=threshold) return 1;
}
void GetLatLon()
{
	int gpsI=0;
	struct latLon pos;
	struct latLon tempPos;
	double checkW;
	double checkH;
	int posCheckI=0;
	//HAL_UART_Recieve();
	while(HAL_UART_Receive(&huart1, &(buffer[gpsI]), 1, 1000)==HAL_OK||1)
			  		  	{
							if(buffer[gpsI]=='$')
							{
								for(ii=0;ii<=127;ii++) buffer[ii]=0;
								buffer[0]='$';
								gpsI=0;
							}//HAL_UART_Transmit(&huart2, buffer[i], 1, 1000);
			  			  if(buffer[gpsI]=='\n')
			  				  {
			  				 /* if(minmea_parse_rmc(&rmcStruct, &(buffer))){
			  				     // pos.lat = minmea_tocoord(&rmcStruct.latitude);
			  				    //  pos.lon = minmea_tocoord(&rmcStruct.longitude);
			  				      game.time = rmcStruct.time;
			  				      frameGot=1;
			  				      for(int posCheckI=0;posCheckI<game.numLocations;posCheckI++)
			  				      {

			  				    	  tempPos = game.positions[posCheckI];
			  				    	if(tempPos.lat!=0&&pos.lat!=0){
			  				    	  checkW = (double)fabs(tempPos.lat-pos.lat);
			  				    	  checkH = (double)fabs(tempPos.lon-pos.lon);
			  				    	  if(sqrt((checkW*checkW)+(checkH*checkH))<gpsThreshold) return;
			  				    	game.positions[game.numLocations] = pos;
			  				    									  game.numLocations++;
			  				    	}
			  				    	  else return;
			  				      }

			  				      break;
			  				  }*/
			  				if(minmea_parse_gga(&ggaStruct, &(buffer))){
			  							  				      pos.lat = minmea_tocoord(&ggaStruct.latitude);
			  							  				      pos.lon = minmea_tocoord(&ggaStruct.longitude);
			  							  				      game.time = ggaStruct.time;
			  							  				      frameGot=1;
			  							  				  posCheckI=0;
			  							  				  for(posCheckI=0;posCheckI<game.numLocations;posCheckI++)
			  							  				  			  				      {

			  							  				  			  				    	  tempPos = game.positions[posCheckI];
			  							  				  			  				    	  if((tempPos.lat>.000001f||tempPos.lat<-.000001f)&&(tempPos.lon>.000001f||tempPos.lon<-.000001f)&&(pos.lat>.000001f||pos.lat<-.000001f)&&(pos.lat>.000001f||pos.lat<-.000001f)){
			  							  				  			  				    	  checkW = fabs(tempPos.lat-pos.lat);
			  							  				  			  				    	  checkH = fabs(tempPos.lon-pos.lon);
			  							  				  			  				    	  if(sqrt((checkW*checkW)+(checkH*checkH))<gpsThreshold) return;

			  							  				  			  				    	  }
			  							  				  			  				    	  else return;

			  							  				  			  				      }
			  							  				game.positions[game.numLocations] = pos;
			  							  				game.numLocations++;
			  							  				if(game.numLocations>31)game.numLocations=0;
			  							  				      break;
			  							  				  }

			  				for(ii=0;ii<=127;ii++) buffer[ii]=0;
			  				  }
			  			  gpsI++;


			  		  	}


}
void Emote()
{
	 switch(game.evo)
				  {
				  case 0:
					  if(game.time.seconds%5==0)
					  {
						  effect = EggNoise;
						  //PlayEffect(effect);
					  }
					  break;
				  case 1:
					  if(game.time.seconds%3==0)
					  					  {
						  if(game.mood>sadMood){
					  			effect = YoungNoiseHappy;
					  			//PlayEffect(effect);
					  		}
						  else
						  {
							  effect = YoungNoiseSad;
							 //PlayEffect(effect);

						  }
					  	}
					  break;
				  case 2:
					  if(game.time.seconds%5==0)
					  					  					  {
					  						  if(game.mood>sadMood){
					  					  			effect = AdultNoiseHappy;
					  					  			PlayEffect(effect);
					  					  		}
					  						  else
					  						  {
					  							  effect = AdultNoiseSad;
					  							 PlayEffect(effect);

					  						  }
					  					  	}
					  //Animate as the adult
					  break;
				  }
	if(game.mood<=sadMood)
	{
		drawString(0, 140, "Emotional State :(", WHITE, BLACK, 1, 1);
	}
	else if(game.mood<=mehMood)
	{
		drawString(0, 140, "Emotional State :|", WHITE, BLACK, 1, 1);
	}
	else if(game.mood>=happyMood)
	{
		drawString(0, 140, "Emotional State :)", WHITE, BLACK, 1, 1);
	}
}
struct latLon GetJustLatLon()
{
	int gpsI=0;
	struct latLon pos;
	struct latLon tempPos;
	double checkW;
	double checkH;
	int posCheckI=0;
	//HAL_UART_Recieve();
	while(HAL_UART_Receive(&huart1, &(buffer[gpsI]), 1, 1000)==HAL_OK||1)
			  		  	{
							if(buffer[gpsI]=='$')
							{
								for(ii=0;ii<=127;ii++) buffer[ii]=0;
								buffer[0]='$';
								gpsI=0;
							}//HAL_UART_Transmit(&huart2, buffer[i], 1, 1000);
			  			  if(buffer[gpsI]=='\n')
			  				  {
			  				 /* if(minmea_parse_rmc(&rmcStruct, &(buffer))){
			  				     // pos.lat = minmea_tocoord(&rmcStruct.latitude);
			  				    //  pos.lon = minmea_tocoord(&rmcStruct.longitude);
			  				      game.time = rmcStruct.time;
			  				      frameGot=1;
			  				      for(int posCheckI=0;posCheckI<game.numLocations;posCheckI++)
			  				      {

			  				    	  tempPos = game.positions[posCheckI];
			  				    	if(tempPos.lat!=0&&pos.lat!=0){
			  				    	  checkW = (double)fabs(tempPos.lat-pos.lat);
			  				    	  checkH = (double)fabs(tempPos.lon-pos.lon);
			  				    	  if(sqrt((checkW*checkW)+(checkH*checkH))<gpsThreshold) return;
			  				    	game.positions[game.numLocations] = pos;
			  				    									  game.numLocations++;
			  				    	}
			  				    	  else return;
			  				      }

			  				      break;
			  				  }*/
			  				if(minmea_parse_gga(&ggaStruct, &(buffer))){
			  							  				      pos.lat = minmea_tocoord(&ggaStruct.latitude);
			  							  				      pos.lon = minmea_tocoord(&ggaStruct.longitude);
			  							  				      return pos;
			  							  				      break;
			  							  				  }

			  				for(ii=0;ii<=127;ii++) buffer[ii]=0;
			  				  }
			  			  gpsI++;


			  		  	}


}
void HAL_RTC_AlarmAEventCallback(RTC_HandleTypeDef *hrtc) {
  RTC_AlarmTypeDef sAlarm;
  HAL_RTC_GetAlarm(hrtc,&sAlarm,RTC_ALARM_A,FORMAT_BIN);
  if(sAlarm.AlarmTime.Seconds>58) {
    sAlarm.AlarmTime.Seconds=0;
  }else{
    sAlarm.AlarmTime.Seconds=sAlarm.AlarmTime.Seconds+1;
  }
    //while(HAL_RTC_SetAlarm_IT(hrtc, &sAlarm, FORMAT_BIN)!=HAL_OK){}
  	 // drawString(30, 30, "testTime", BLACK, GREEN, 1, 1);
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
