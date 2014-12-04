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
#include "Events.h"
#include "Keys.h"
#include "FRTOS1.h"
#include "Ultrasonic.h"
#include "Reflectance.h"
#include "WAIT1.h"


typedef enum {
  START,
  DRIVE,
  REFLECTANCE,
  TURN,
  ULTRASONIC,
  ATTACK,
  STOP
} StateType;
static volatile StateType state = START; /* state machine state */






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

	  switch (state) {
	    case START:
	      //SHELL_SendString((unsigned char*)"INFO: No calibration data present.\r\n");

	    		WAIT1_Waitms(2000);
	    	    MOT_SetDirection(MOT_GetMotorHandle(MOT_MOTOR_LEFT), MOT_DIR_FORWARD);
	    		MOT_SetDirection(MOT_GetMotorHandle(MOT_MOTOR_RIGHT), MOT_DIR_FORWARD);
	    		MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_RIGHT), 30);
	    		MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_LEFT), 30);
	    		//MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_RIGHT), 40);

	    		if(((US_usToCentimeters(US_Measure_us(),22)<=30) != 0)){
	    			//state = DRIVE;
	    		}


	    		/*int x0;
	    		int x5;
	    		int x0_cal;
	    		int x5_cal;
	    		x0 = Get_Reflectance_Values(0);
	    		x0_cal = x0 / 15;
	    		x5 = Get_Reflectance_Values(5);
	    		x5_cal = x5 / 15;
	    		MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_RIGHT), x0_cal);
	    		MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_LEFT), x5_cal);
	    		*/


	    		//uint16_t* calib_values_pointer;
	    		//calib_values_pointer = &SensorTimeType;
	    		//calib_values_pointer = S1_GetVal();

	      break;


	    case DRIVE:


	    	MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_LEFT), 30);
	    	MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_RIGHT), 30);


	    	if(Get_Reflectance_Values(4) <= 100) // 0 = weiss / 1000 = schwarz
	    	{
	    		state = STOP;
	    		    		}


	    	//if(accel)
	    	{
	        state = STOP;

	    	}

	        state = REFLECTANCE;
	        state = ULTRASONIC;

	        break;

	      break;

	    case TURN:
	      //SHELL_SendString((unsigned char*)"start calibration...\r\n");

// umdrehen


	      state = DRIVE;
	      break;

	    case STOP:
	    	      //SHELL_SendString((unsigned char*)"...stopping calibration.\r\n");
	    	MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_RIGHT), 0);
	    	MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_LEFT), 0);
	    	    	// ATTACK

	    	if(Get_Reflectance_Values(4) >= 100)
	    		    	{
	    		    		state = DRIVE;
	    		    	}
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
