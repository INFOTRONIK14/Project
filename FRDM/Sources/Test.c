/*
 * Test.c
 *
 *  Created on: 30.09.2014
 *      Author: tastyger
 */

#include "CS1.h"

static uint8_t bar;

void(*fn)(void);

void Interrupts(void) {
  __asm("cpsid i"); /* disable */
  __asm("cpsie i"); /* enable */
}

void foo(void) {
  CS1_CriticalVariable()

  CS1_EnterCritical();
  bar++;
  CS1_ExitCritical();
  Interrupts();
}

void TEST_Test(void) {
  int i;

  for(i=0;i<50;i++) {
    Interrupts();
    fn();
    foo();
  }
}

/**
 *
 * @param b
 * @param c
 * @return
 */
int foo2(int b, char c){
}
