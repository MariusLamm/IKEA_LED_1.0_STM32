/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx_hal.h"
#include "main.h"
#include "ledstringdriver.h"

/* Variables -----------------------------------------------------------------*/
char string[20];

/*Index for LEDstring*/
uint8_t LEDIndex =0;
/*Value for LEDstring*/
uint32_t LEDValue =0;

/*Set Index of LED String*/
void setLEDStringIndex(void)
{
  //TODO Implement rotary encoder
  LEDIndex++;
  if(LEDIndex >9){
    LEDIndex = 0;
  }

  sprintf(string,"%d",LEDIndex);
  PrintToUART(string);
  PrintToUART("\n");
}

/*Set Value of LED String*/
void setLEDStringValue(void)
{
//TODO Implement rotary encoder
}



/*hardware index don't match, see hardware layout of the IKEA LED
TODO: Fix Layout in version 2.0
*/
uint8_t mapIndiexOfLED(uint8_t index)
{
  if(index == 0){
    return 0;
  }
  if(index == 1){
    return 5;
  }
  if(index == 2){
    return 1;
  }
  if(index == 3){
    return 6;
  }
  if(index == 4){
    return 2;
  }
  if(index == 5){
    return 7;
  }
  if(index == 6){
    return 3;
  }
  if(index == 7){
    return 8;
  }
  if(index == 8){
    return 4;
  }
  if(index == 9){
    return 9;
  }
  else
    return 0;

}
