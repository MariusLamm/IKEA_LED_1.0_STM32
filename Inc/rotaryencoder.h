/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx_hal.h"
#include "main.h"


/* USER CODE BEGIN Prototypes */
void setRotAFlag(void);
void setRotBFlag(void);
void resetRotAFlag(void);
void resetRotBFlag(void);
uint8_t getRotBFlag(void);
uint8_t getRotAFlag(void);


void checkRotationDirection(void);
void EncoderButtonPressed(void);

void RotaryEncoderRight(void);
void RotaryEncoderLeft(void);
uint8_t mapIndiexOfLED(uint8_t);



/* USER CODE END Prototypes */
