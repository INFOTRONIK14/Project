/*
 * StateMachine.c
 *
 *  Created on: 01.12.2014
 *      Author: Imhof Dominik
 */


#include "Motor.h"
#include "Accel.h"
#include "Ultrasonic.h"
#include "Event.h"
#include "Keys.h"
#include "FRTOS1.h"

typedef enum {
  START,
  DRIVE,
  REFLECTANCE,
  TURN,
  ULTRASONIC,
  ATTACK
} RefStateType;
static volatile RefStateType refState = START; /* state machine state */






void Calibration_Run(void){


// Wenn SW1 pressed, kommt er da rein. beim 2ten mal stopt er calibration.
	EVNT_SetEvent(EVNT_REF_START_STOP_CALIBRATION);


  }



/*
void Motor_Run(void){


	MOT_SetDirection(MOT_GetMotorHandle(MOT_MOTOR_LEFT), MOT_DIR_FORWARD);
	MOT_SetDirection(MOT_GetMotorHandle(MOT_MOTOR_RIGHT), MOT_DIR_FORWARD);
	MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_LEFT), 10);
	MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_RIGHT), 40);


  }
  */


static void StateMachine_Run(void){



	  int i;

	  switch (refState) {
	    case START:
	      //SHELL_SendString((unsigned char*)"INFO: No calibration data present.\r\n");


	    	    MOT_SetDirection(MOT_GetMotorHandle(MOT_MOTOR_LEFT), MOT_DIR_FORWARD);
	    		MOT_SetDirection(MOT_GetMotorHandle(MOT_MOTOR_RIGHT), MOT_DIR_FORWARD);
	    		MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_LEFT), -40);
	    		MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_RIGHT), 40);




	      refState = DRIVE;
	      break;


	    case DRIVING:

	      if (EVNT_EventIsSet(EVNT_REF_START_STOP_CALIBRATION)) {
	        EVNT_ClearEvent(EVNT_REF_START_STOP_CALIBRATION);
	        refState = REFLECTANCE;
	        refState = ULTRASONIC;
	        break;
	      }
	      break;

	    case REFLECTANCE:
	      //SHELL_SendString((unsigned char*)"start calibration...\r\n");

// umdrehen
	      refState = DRIVING;
	      break;



	    case ULTRASONIC:
	      //SHELL_SendString((unsigned char*)"...stopping calibration.\r\n");

	    	// ATTACK
	      refState = DRIVING;
	      break;


	  } /* switch */
	}







static portTASK_FUNCTION(StateMachineTask, pvParameters) {
  (void)pvParameters; /* not used */
  for(;;) {
    StateMachine_Run();
    FRTOS1_vTaskDelay(10/portTICK_RATE_MS);
  }
}

void StateMachine_Deinit(void) {
}



void StateMachine_Init(void) {
  //refState = REF_STATE_INIT;
  //timerHandle = RefCnt_Init(NULL);
  /*! \todo You might need to adjust priority or other task settings */
  if (FRTOS1_xTaskCreate(StateMachineTask, "StateMachine", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, NULL) != pdPASS) {
    for(;;){} /* error */
  }
}
