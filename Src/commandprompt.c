/* Includes ------------------------------------------------------------------*/
#include "usart.h"
#include "string.h"
#include "gpio.h"



void Mainmenu(void)
{
//TODO: implment Menu for interaction over UART, exclude getCommand and debugPrint function into seperat file
  PrintToUART("IKEA LED V1.00\n");
  PrintToUART("r RTC \n");
  PrintToUART("s set ON time of LED string\n");
  PrintToUART("type 'comannd' -h for help\n");
  getCommand();
}

void getCommand(void)
{
  PrintToUART("type command:\n");
  char in[25];
  HAL_UART_Receive(&huart2, (uint8_t *)in, 25, 1000);
  PrintToUART("\n");

  if(in[0]=='r'){

  }

  if(in[0]=='s'){
    PrintToUART("command to set led: s, LED(1-10), brightness(0-255) \n");
    PrintToUART("e.g.: 's,1,100' set LED1 to brightness 100\n");
  }

}
