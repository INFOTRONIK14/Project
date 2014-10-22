/*
 * Test.c
 *
 *  Created on: 30.09.2014
 *      Author: tastyger
 */

#include "CS1.h"
#include "Cpu.h"

uint8_t srcVar, dstVar;
void TEST_Test2(void) {
  Cpu_EnableInt();
  Cpu_DisableInt();
  __asm("mov r0, r0"); /* nop */

  __asm(
    "mov r0,r0    \n\t"
    "mov r0,r0    \n\t"
    "mov r0,r0"
  );

  __asm(
    "ldrb r1, %[src] \n\t" /* load src into r1 */
    "add r1,#1       \n\t" /* increment r1 */
    "strb r1,%[dst]  \n\t" /* store r1 in dst */
    : [dst] "=m" (dstVar)  /* result in memory */
    : [src] "m" (srcVar)   /* src from memory */
    : "r1"       /* clobber, changed register */
  );

}

static uint8_t bar;

void(*fn)(void);

void Interrupts(void) {
  __asm("cpsid i"); /* disable */
  __asm("cpsie i"); /* enable */
}

void ResetMe(void) {
  SCB_AIRCR = SCB_AIRCR_VECTKEY(0x5FA) | SCB_AIRCR_SYSRESETREQ_MASK;
  while(1) {};
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
    //fn();
    foo();
    ResetMe();
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

