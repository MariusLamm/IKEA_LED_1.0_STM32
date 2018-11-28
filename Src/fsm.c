
/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx_hal.h"
#include "main.h"
#include "fsm.h"
#include "ledstringdriver.h"

/* Variables -----------------------------------------------------------------*/
/*char array to display time for RTC*/
char sTime[20];
char string[20];

/*enum for all states*/
enum states {
    S1,S2,S3,
}state;

/*Init State of the FSM*/
state = S1; // init status = S1


void stateMachine()
{
  if(state == S1){
    state1();
    state = S2;
  }

  else if(state == S2){
    state2();
    state = S2;
  }

  else if(state == S3){
    state3();
    state = S1;
  }

  else{
    state = S2;
  }
}


/* write RTc with Rotary Encoder */
void state1()
{
  PrintToUART("set hours for RTC:\n");
  PrintToUART("turn rotary encoder left/right\n");
  /*Wait for Conformation with Button 1*/
  while(getButton1Flag(); == 0){
    //display the current Hour
      Hours = getRotEncoderData();//TODO Implement rotary encoder
      sprintf(string,"Hour: %d\n",Hours);
      PrintToUART("press Button 1 to confirm:\n");
      PrintToUART(string);
  }

  PrintToUART("set minutes for RTC:\n");
  PrintToUART("turn rotary encoder left/right\n");
  /*Wait for Conformation with Button 1*/
  while(getButton1Flag(); == 0){
    //display the current Minute
    Minute = getRotEncoderData();//TODO Implement rotary encoder
    sprintf(string,"Minute: %d\n",Minute);
    PrintToUART("press Button 1 to confirm:\n");
    PrintToUART(string);
  }

  RTC_Set_Hours_Minutes_Seconds(Hours,Minutes,0);
  sprintf(string,"Time set to: %d:",Hours);
  sprintf(string,"%d\n",Minutes);
  PrintToUART(string);

  /*Reset Button 1 Flag */
  resetButton1Flag();
}


/*Display time on UART*/
void state2()
{
  /*Read RTC Minutes and Hours and display on UART*/
  RTC_CalendarShow(Time, Date);
  sprintf(sTime,"%02d:%02d:%02d\n",Time[0],Time[1],Time[2]);
  PrintToUART(sTime);
  HAL_Delay(5000);
}


/*Get Data from Rotary Encoder
and set LED String with Value and Index*/
void state3()
{
  PrintToUART("set Index of LED String (0-9):\n");
  PrintToUART("turn rotary encoder left/right\n");

  /*Wait for Conformation with Button 1*/
  while(getButton1Flag(); == 0)){
    //display the current position of LED Index
    setLEDStringIndex();
  }

  PrintToUART("set Value of LED String (0-4000):\n");
  PrintToUART("turn rotary encoder left/right\n");

  /*Wait for Conformation with Button 1*/
  while(getButton1Flag(); == 0)){
    //display the current position of LED Value
    setLEDStringValue();
  }

  /*Reset Button 1 Flag */
  resetButton1Flag();
}
