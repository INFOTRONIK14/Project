/**
 * \file
 * \brief Main Application Module.
 * \author Erich Styger, erich.styger@hslu.ch
 *
 * This module is the main application module. 
 * From here the application runs and performs all tasks.
 */

#include "Platform.h"
#include "Application.h"
#include "WAIT1.h"
#if PL_HAS_LED
  #include "LED.h"
#endif
#if PL_HAS_EVENTS
  #include "Event.h"
#endif
#if PL_HAS_MEALY
  #include "Mealy.h"
#endif
#if PL_HAS_KEYS
  #include "Keys.h"
#endif
#include "Test.h"

void TestFunction(void) {
}


static uint8_t lastKeyPressed;

static void APP_EventHandler(EVNT_Handle event) {
  //TestFunction();
  switch(event) {
    case EVNT_INIT:
      LED1_On();
      WAIT1_Waitms(50);
      LED1_Off();
      LED2_On();
      WAIT1_Waitms(50);
      LED2_Off();
      LED3_On();
      WAIT1_Waitms(50);
      LED3_Off();
      break;
    case EVENT_LED_HEARTBEAT:
      LED1_Neg();
      break;
    case EVNT_SW1_PRESSED:
      lastKeyPressed = 1;
      //LED1_On();
      break;
#if PL_NOF_KEYS >= 2
    case EVNT_SW2_PRESSED:
      lastKeyPressed = 2;
      //LED1_Off();
      break;
#endif
#if PL_NOF_KEYS >= 3
    case EVNT_SW3_PRESSED:
      lastKeyPressed = 3;
      break;
#endif
#if PL_NOF_KEYS >= 4
    case EVNT_SW4_PRESSED:
      lastKeyPressed = 4;
      break;
#endif
#if PL_NOF_KEYS >= 5
    case EVNT_SW5_PRESSED:
      lastKeyPressed = 5;
      break;
#endif
#if PL_NOF_KEYS >= 6
    case EVNT_SW6_PRESSED:
      lastKeyPressed = 6;
      break;
#endif
#if PL_NOF_KEYS >= 7
    case EVNT_SW7_PRESSED:
      lastKeyPressed = 7;
      break;
#endif
    default:
      break;
  }
}

static void APP_Loop(void) {
  int i;

  for(;;) {
#if PL_HAS_EVENTS
    EVNT_HandleEvent(APP_EventHandler); /* handle pending events */
#endif
#if PL_HAS_KEYS
    KEY_Scan(); /* scan keys */
#endif
    WAIT1_Waitms(100);
  }
}

void APP_Start(void) {
  PL_Init(); /* platform initialization */
  //TEST_Test();
  EVNT_SetEvent(EVNT_INIT); /* set initial event */
  APP_Loop();
#if 0
  for(;;) {
#if PL_HAS_MEALY
    MEALY_Step();
#else
    LED1_On();
    WAIT1_Waitms(300);
    LED1_Off();
    LED2_On();
    WAIT1_Waitms(300);
    LED2_Off();
    LED3_On();
    WAIT1_Waitms(300);
    LED3_Off();
#endif
  }
#endif
  /* just in case we leave the main application loop */
  PL_Deinit();
}
