#include "main.h"
#include "stm32f0xx_hal.h"
#include "rotaryencoder.h"
#include "pca9685.h"
#include "usart.h"

#define STEP 20

/*
Rotary encoders are devices which are connected to the CPU or other
peripherals with two wires. The outputs are phase-shifted by 90 degrees
and by triggering on falling and rising edges, the turn direction can
be determined.

The phase diagram of these two outputs look like this:

                  _____       _____       _____
                 |     |     |     |     |     |
  Channel A  ____|     |_____|     |_____|     |____

                 :  :  :  :  :  :  :  :  :  :  :  :
            __       _____       _____       _____
              |     |     |     |     |     |     |
  Channel B   |_____|     |_____|     |_____|     |__

                 :  :  :  :  :  :  :  :  :  :  :  :
  Event          a  b  c  d  a  b  c  d  a  b  c  d

                |<-------->|
	          one step


For more information, please see
	http://en.wikipedia.org/wiki/Rotary_encoder
*/


uint8_t Rot_A_State =0;
uint8_t Rot_B_State =0;

uint8_t Last_Rot_A_State =1;
uint8_t Last_Rot_B_State =1;

uint8_t sequenz_A=0;
uint8_t sequenz_B=0;

uint8_t position=0;


void setRotAState(void)
{
  RotaryEncoderRight();
}

void setRotBState(void)
{
  RotaryEncoderRight();
}





void checkRotationDirection(void)
{

  uint8_t Rot_A_State =HAL_GPIO_ReadPin(Rot_A_GPIO_Port,Rot_A_Pin);
  uint8_t Rot_B_State =HAL_GPIO_ReadPin(Rot_B_GPIO_Port,Rot_B_Pin);

  // Record the A and B signals in seperate sequences
  sequenz_A <<= 1;
  sequenz_A |= Rot_A_State;

  sequenz_B <<= 1;
  sequenz_B |= Rot_B_State;

  // Mask the MSB four bits
  sequenz_A &= 0b00001111;
  sequenz_B &= 0b00001111;

  // Compare the recorded sequence with the expected sequence
  if (sequenz_A == 0b00001001 && sequenz_B == 0b00000011) {
    position++;
  }

  if (sequenz_A == 0b00000011 && sequenz_B == 0b00001001) {
    position++;
  }

  char string[20];
  sprintf(string,"%d",position);
  PrintToUART(string);
  PrintToUART("\n");



}


/*Index for LEDstring*/
uint8_t LEDIndex =0;
/*Value for LEDstring*/
uint32_t LEDValue =0;
/*Set inital Values*/

/*If encoder Button is Pressed do something*/
void EncoderButtonPressed(void)
{
  LEDIndex++;

  if(LEDIndex >9){
    LEDIndex = 0;
  }

  char string[20];
  sprintf(string,"%d",LEDIndex);
  PrintToUART(string);
  PrintToUART("\n");

}

void RotaryEncoderRight(void)
{
  if(LEDValue > 4000){
      LEDValue = 0;
  }
  pca9685_set_pin(mapIndiexOfLED(LEDIndex),LEDValue);

  char string[20];
  sprintf(string,"%d",LEDValue);
  PrintToUART(string);
  PrintToUART("\n");

  LEDValue=LEDValue+STEP;
}

void RotaryEncoderLeft(void)
{
  if(LEDValue < 0){
      LEDValue = 0;
  }
  pca9685_set_pin(LEDIndex,LEDValue);

  char string[20];
  sprintf(string,"%d",LEDValue);
  PrintToUART(string);
  PrintToUART("\n");

  LEDValue=LEDValue-STEP;
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
