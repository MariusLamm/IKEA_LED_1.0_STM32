#include "main.h"
#include "stm32f0xx_hal.h"
#include "rotaryencoder.h"
#include "pca9685.h"

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


void setRotAState(void)
{
  //toggle Rot_A_State
  Rot_A_State = 1;
  checkRotationDirection();
}

void setRotBState(void)
{
  //toggle Rot_B_State
  Rot_B_State = 1;
  checkRotationDirection();
}

void checkRotationDirection(void)
{
  if((Rot_B_State == 1) || (Rot_A_State == 1)){

    //encoder rotats Right
    if(Rot_A_State == 0){
      PrintToUART("ROT_A\n");
      RotaryEncoderRight();
    }
    //encoder rotats Left
    if(Rot_B_State == 0){
      PrintToUART("ROT_B\n");
      RotaryEncoderLeft();
    }
  }
  Rot_A_State = 0;
  Rot_B_State = 0;
}


/*Index for LEDstring*/
uint8_t LEDIndex =0;
/*Value for LEDstring*/
uint32_t LEDValue =3000;
/*Set inital Values*/

/*If encoder Button is Pressed do something*/
void EncoderButtonPressed(void)
{
  if(LEDIndex == 9){
    LEDIndex = 0;
  }
  pca9685_set_pin(LEDIndex,LEDValue);
  LEDIndex++;
}

void RotaryEncoderRight(void)
{
  if(LEDValue > 4000){
      LEDValue = 4000;
  }
  pca9685_set_pin(LEDIndex,LEDValue);
  LEDValue=LEDValue+100;
}

void RotaryEncoderLeft(void)
{
  if(LEDValue < 0){
      LEDValue = 0;
  }
  pca9685_set_pin(LEDIndex,LEDValue);
  LEDValue=LEDValue-100;
}
