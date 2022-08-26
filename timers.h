/*
 * timers.h
 *
 *      Author: Arnav Mehta
 */

#ifndef TIMERS_H_
#define TIMERS_H_

#include <stdint.h>
#include <stdbool.h>
#include "msp.h"

// Declare any functions found in timers.c that will be used in other files here

/****************************************************
 * Configure Timer32_1 to configure a periodic interrupt
 *
 * Parameters
 *      ticks: number of interrupts per milli second
 * Returns
 *      None
 ****************************************************/
void ece353_T32_1_Interrupt_Ms(uint16_t ms);

/****************************************************
 * Configure Timer32_1 to configure a periodic interrupt
 *
 * Parameters
 *      ticks: number of interrupts per millisecond
 * Returns
 *      None
 ****************************************************/
void ece353_T32_2_Interrupt_Ms(uint16_t ms);

#endif /* TIMERS_H_ */
