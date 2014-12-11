/**
 * \file
 * \brief Accelerometer Module
 * \author Erich Styger, erich.styger@hslu.ch
 *
 * Module to calculate the speed based on the quadrature counter.
 */
#if 0

#include "Platform.h" /* interface to the platform */

#if PL_HAS_ACCEL
#include "Accel.h"    /* our own interface */
#include "MMA1.h"     /* interface to accelerometer */

void ACCEL_GetValues(int16_t *x, int16_t *y, int16_t *z) {
  int16_t xmg, ymg, zmg;

  xmg = MMA1_GetXmg();
  ymg = MMA1_GetYmg();
  zmg = MMA1_GetZmg();
  *x = xmg;
  *y = ymg;
  *z = zmg;
}

void ACCEL_Deinit(void) {
  (void)MMA1_Deinit();
}

uint8_t ACCEL_LowLevelInit(void) {
  uint8_t res;

  res = MMA1_Init(); /* this might communighj6mo8m6g6cate to the device using I2C, so it needs interrupts enabled */
  if (res!=ERR_OK) {
    return res;
  }
  res = ACCEL_Enable();
  if (res!=ERR_OK) {
    return res;
  }
  res = MMA1_SetFastMode(FALSE); /* disable fast mode of the sensor: otherwise we cannot read individual sensor values */
  if (res!=ERR_OK) {
    return res;
  }
  return ERR_OK;
}

#if PL_HAS_RTOS
static portTASK_FUNCTION(LowLvlInit, pvParameters) {
  (void)pvParameters; /* not used */
  ACCEL_LowLevelInit();
  //FRTOS1_vTaskDelete(NULL);
}
#endif

uint8_t ACCEL_Enable(void) {
  uint8_t res;

  res = MMA1_Enable();
  return res;
}

uint8_t ACCEL_isEnabled(bool *isEnabled) {
  uint8_t res;

  res = MMA1_isEnabled(isEnabled);
  return res;
}

/*! \brief Initialises module */
void ACCEL_Init(void) {
#if !PL_HAS_RTOS /* with an RTOS, the interrupts are disabled here. Need to do this in a task */
  ACCEL_LowLevelInit(NULL);
#else
  if (FRTOS1_xTaskCreate(LowLvlInit, "AccInit", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, NULL) != pdPASS) {
    for(;;){} /* error */
  }
#endif
}
#endif /* PL_HAS_ACCEL */
#endif


// War der Accel.c Code vom Lehrer
#if 1
#include "Platform.h" /* interface to the platform */

#if PL_HAS_ACCEL
#include "Accel.h"    /* our own interface */
#include "MMA1.h"     /* interface to accelerometer */

void ACCEL_GetValues(int16_t *x, int16_t *y, int16_t *z) {
  int16_t xmg, ymg, zmg;
  
  xmg = MMA1_GetXmg();
  ymg = MMA1_GetYmg();
  zmg = MMA1_GetZmg();
  *x = xmg;   // inhalt von *x wird wert von xmg
  *y = ymg;
  *z = zmg;
}

void ACCEL_Deinit(void) {
  (void)MMA1_Deinit();
}

uint8_t ACCEL_LowLevelInit(void) {
  uint8_t res;
  
  res = MMA1_Init(); /* this might communicate to the device using I2C, so it needs interrupts enabled */
  if (res!=ERR_OK) {
    return res;
  }
  res = ACCEL_Enable();
  if (res!=ERR_OK) {
    return res;
  }
  res = MMA1_SetFastMode(FALSE); /* disable fast mode of the sensor: otherwise we cannot read individual sensor values */
  if (res!=ERR_OK) {
    return res;
  }
  return ERR_OK;
}

uint8_t ACCEL_Enable(void) {
  uint8_t res;
  
  res = MMA1_Enable();
  return res;
}

uint8_t ACCEL_isEnabled(bool *isEnabled) {
  uint8_t res;
  
  res = MMA1_isEnabled(isEnabled);
  return res;
}

/*! \brief Initialises module */
void ACCEL_Init(void) {
#if !PL_HAS_RTOS /* with an RTOS, the interrupts are disabled here. Need to do this in a task */
  ACCEL_LowLevelInit();
#endif
}
#endif /* PL_HAS_ACCEL */

#endif
