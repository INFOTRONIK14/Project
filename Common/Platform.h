/**
 * \file
 * \brief Platform Interface.
 * \author Erich Styger, erich.styger@hslu.ch
 *
 * This implements the platform interface.
 * Here the platform gets initialized, and all platform dependent macros get defined.
 */

#ifndef PLATFORM_H_
#define PLATFORM_H_

#include "PE_Types.h" /* for common Processor Expert types used throughout the project, e.g. 'bool' */
#include "PE_Error.h" /* global error constants */
#include <stddef.h>   /* for NULL */

/* List of supported platforms. The PL_BOARD_IS_xxx is defined in the compiler command line settings.  */
#define PL_IS_FRDM   (defined(PL_BOARD_IS_FRDM))
  /*!< Macro is defined through compiler option for the FRDM board */
#define PL_IS_ROBO  (defined(PL_BOARD_IS_ROBO))
  /*!< Macro is defined through compiler option for the Robot board */
#define PL_IS_INTRO_ZUMO_K22_V2  (0)
  /*!< either prototype (0) or production (1) */

#define PL_HAS_LED            (1)
  /*!< Set to 1 to enable LED support, 0 otherwise */
#define PL_HAS_EVENTS         (1)
  /*!< Set to 1 to enable event support, 0 otherwise */
#define PL_HAS_TIMER          (1)
  /*!< Set to 1 to enable timer support, 0 otherwise */
#define PL_HAS_KEYS           (1)
  /*!< Set to 1 to enable key/push button support, 0 otherwise */
#define PL_HAS_KBI            (1)
  /*!< Set to 1 to enable key interrupt support, 0 otherwise */
#define PL_HAS_KBI_NMI        (1 && PL_IS_FRDM && PL_HAS_JOYSTICK)
  /*!< Set to 1 for special case on NMI/PTA pin on FRDM board, 0 otherwise */
#define PL_HAS_RESET_KEY      (0 && PL_IS_FRDM && PL_HAS_KEYS)
  /*!< Set to 1 to use reset switch on FRDM as button, 0 otherwise */
#define PL_HAS_JOYSTICK       (1 && PL_IS_FRDM && PL_HAS_KEYS)
  /*!< Set to 1 to enable joystick shield support, 0 otherwise */
#define PL_HAS_MEALY          (0 && PL_NOF_LEDS>=1 && PL_NOF_KEYS>=1)
  /*!< Set to 1 to enable Mealy FSM, 0 otherwise */
#define PL_HAS_SHELL          (1 && (PL_IS_FRDM || (PL_IS_ROBO && PL_HAS_USB_CDC)))
  /*!< Set to 1 to enable shell, 0 otherwise */
#define PL_HAS_TRIGGER        (1 && PL_HAS_TIMER)
  /*!< Set to 1 to enable triggers, 0 otherwise */
#define PL_HAS_BUZZER         (1 && PL_HAS_TRIGGER && PL_IS_ROBO)
  /*!< Set to 1 to enable buzzer, 0 otherwise */
#define PL_HAS_DEBOUNCE       (1 && PL_HAS_KEYS)
  /*!< Set to 1 to enable triggers, 0 otherwise */
#define PL_HAS_RTOS           (1)
  /*!< Set to 1 if using FreeRTOS, 0 otherwise */
#define PL_HAS_USB_CDC        (1)
  /*!< Set to 1 if using USB CDC, 0 otherwise */
#define PL_HAS_BLUETOOTH      (1 && PL_IS_ROBO)
  /*!< Set to 1 if using Bluetooth, 0 otherwise */
#define PL_HAS_SHELL_QUEUE    (0 && PL_HAS_SHELL)
  /*!< Set to 1 if using shell queues, 0 otherwise */
#define PL_HAS_SEMAPHORE      (1)
  /*!< Set to 1 if using semaphore labs, 0 otherwise */
#define PL_HAS_LINE_SENSOR    (1 && PL_IS_ROBO)
  /*!< Set to 1 if using line sensor, 0 otherwise */
#define PL_HAS_REFLECTANCE    (1 && PL_HAS_LINE_SENSOR)
  /*!< Set to 1 if using reflectance sensor array, 0 otherwise */
#define PL_HAS_MOTOR          (1 && PL_IS_ROBO)
  /*!< Set to 1 if using motors, 0 otherwise */
#define PL_HAS_CONFIG_NVM     (1)
  /*!< Set to 1 if using NVMC, 0 otherwise */
#define PL_HAS_MCP4728        (1 && PL_IS_ROBO)
  /*!< Set to 1 if using MCP4728, 0 otherwise */
#define PL_HAS_QUAD_CALIBRATION (1 && PL_HAS_MCP4728)
  /*!< Set to 1 if using quadrature calibration, 0 otherwise */
#define PL_HAS_QUADRATURE     (1 && PL_IS_ROBO)
  /*!< Set to 1 if using quadrature counters, 0 otherwise */
#define PL_HAS_MOTOR_TACHO    (1 && PL_HAS_QUADRATURE)
  /*!< Set to 1 if using speed estimation, 0 otherwise */
#define PL_HAS_PID            (1 && PL_HAS_MOTOR_TACHO)
  /*!< Set to 1 if using PID, 0 otherwise */
#define PL_HAS_DRIVE          (1 && PL_HAS_PID)
  /*!< Set to 1 if using PID, 0 otherwise */
#define PL_HAS_ULTRASONIC     (1 && PL_IS_ROBO)
  /*!< Set to 1 if using ultrasonic sensor, 0 otherwise */
#define PL_HAS_ACCEL          (1)
  /*!< Set to 1 if using an accelerometer, 0 otherwise */
#define PL_HAS_ACCEL_STOP     (1 && PL_HAS_ACCEL && PL_HAS_MOTOR && PL_IS_ROBO)
  /*!< Set to 1 if stopping robot with accelerometer, 0 otherwise */
#define PL_HAS_RADIO          (1)
  /*!< Set to 1 if using an radio transceiver, 0 otherwise */
#define PL_HAS_REMOTE         (0 && PL_HAS_RADIO && PL_HAS_ACCEL)

#define PL_APP_ACCEL_CONTROL_SENDER (PL_HAS_REMOTE && PL_IS_FRDM)

#define PL_HAS_RTOS_TRACE     (0 && PL_HAS_RTOS && configUSE_TRACE_HOOKS)
  /*!< Set to 1 if Percepio trace, 0 otherwise */

/* additional hardware configuration */

/* if keys are using interrupts or are polled */
#if PL_IS_FRDM
  #define PL_KEY_POLLED_KEY1    (0)
  #define PL_KEY_POLLED_KEY2    (0)
  #define PL_KEY_POLLED_KEY3    (0)
  #define PL_KEY_POLLED_KEY4    (0)
  #define PL_KEY_POLLED_KEY5    (1)
  #define PL_KEY_POLLED_KEY6    (1)
  #define PL_KEY_POLLED_KEY7    (0)
#elif PL_IS_ROBO
  #define PL_KEY_POLLED_KEY1    (0)
#endif

#if PL_IS_FRDM
  #if PL_HAS_JOYSTICK
    #define PL_NOF_LEDS       (2)
      /*!< FRDM board has 2 LEDs (blue is used by joystick shield/nrf24L01+ SPI CLK) */
    #define PL_NOF_KEYS       (7)
       /*!< FRDM board has no keys without joystick shield */
  #else
    #define PL_NOF_LEDS       (3)
       /*!< FRDM board has up to 3 LEDs (RGB) */
#if PL_HAS_RESET_KEY
    #define PL_NOF_KEYS       (1)
       /*!< FRDM board with using the reset button */
#else
    #define PL_NOF_KEYS       (0)
       /*!< FRDM board has no keys without joystick shield */
#endif
  #endif
#elif PL_IS_ROBO
  #define PL_NOF_LEDS       (1)
     /*!< We have up to 2 LED's on the robo board */
  #define PL_NOF_KEYS       (1)
     /*!< We have up to 1 push button */
#else
  #error "unknown configuration?"
#endif

/*!
 * \brief Platform initialization
 */
void PL_Init(void);

/*!
 * \brief Platform de-initialization
 */
void PL_Deinit(void);

#endif /* PLATFORM_H_ */
