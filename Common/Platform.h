/*
 * Platform.h
 *
 *  Created on: 26.09.2014
 *      Author: Imhof Dominik
 */

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
#define PL_IS_FRDM   (defined(PL_BOARD_IS_FRDM))  // kann man nun in FRDM Properties einstellen / Settings / Cross ARM C Compiler / Preprocessor
  /*!< Macro is defined through compiler option for the FRDM board */
#define PL_IS_ROBO  (defined(PL_BOARD_IS_ROBO))
  /*!< Macro is defined through compiler option for the Robot board */

#define PL_HAS_LED  (1)
  /*!< Set to 1 to enable LED support, 0 otherwise */




#if PL_IS_FRDM
  #define PL_NOF_LEDS       (3)
     /*!< FRDM board has up to 3 LEDs (RGB) */
#elif PL_IS_ROBO
  #define PL_NOF_LEDS       (0)
     /*!< We have up to 2 LED's on the robo board */
#else
 /* #error "unknown configuration?"*/
#endif
<<<<<<< HEAD
#define PL HAS HAS TIMER  (1)
  /*!< Set to 1 to enable LED support, 0 otherwise */
=======


#define PL_HAS_EVENTS  (1)
  /*!< Set to 1 to enable Event support, 0 otherwise */

#define PL_SW1_POLL  (1)
  /*!< Set to 1 to enable Event support, 0 otherwise */

#define PL_HAS_HAS_TIMER  (1)
  /*!< Set to 1 to enable TIMER support, 0 otherwise */

#define PL_HAS_KEYS  (1)
  /*!< Set to 1 to enable TIMER support, 0 otherwise */

#define PL_NOF_KEYS       (7)
     /*!< FRDM board has up to 3 LEDs (RGB) */

#define PL_HAS_KBI  (1)
  /*!< Set to 1 to enable TIMER support, 0 otherwise */

#define PL_HAS_JOYSTICK  (1)
  /*!< Set to 1 to enable TIMER support, 0 otherwise */



>>>>>>> 709726a0cb6cd10bd262484610bdcb71fcfcafbf
/*!
 * \brief Platform initialization
 */
void PL_Init(void);

/*!
 * \brief Platform de-initialization
 */
void PL_Deinit(void);

#endif /* PLATFORM_H_ */
