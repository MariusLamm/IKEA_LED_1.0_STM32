/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __commandprompt_H
#define __commandprompt_H
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx_hal.h"
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */


/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

extern void _Error_Handler(char *, int);

/* USER CODE BEGIN Prototypes */
void Mainmenu(void);
void getCommand(void);
void WriteRTC(void);
/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif
#endif /*__ usart_H */

/**
  * @}
  */

/**
  * @}
  */
