/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx_hal.h"
#include "main.h"


/* USER CODE BEGIN Prototypes */
void setRotAFlag(void);
void resetRotAFlag(void);
uint8_t getRotAFlag(void);

void setRotBFlag(void);
void resetRotBFlag(void);
uint8_t getRotBFlag(void);

void setButton1Flag(void);
void resetButton1Flag(void);
uint8_t getButton1Flag(void);

void checkRotationDirection(void);
void EncoderButtonPressed(void);

void RotaryEncoderRight(void);
void RotaryEncoderLeft(void);
uint8_t mapIndiexOfLED(uint8_t);



/* USER CODE END Prototypes */
