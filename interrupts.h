/*
 * interrupts.h
 *
 *      Author: Arnav Mehta
 */

#ifndef INTERRUPTS_H_
#define INTERRUPTS_H_

#include <stdint.h>
#include <stdbool.h>
#include "msp.h"

extern volatile uint32_t PS2_X_DIR;
extern volatile uint32_t PS2_Y_DIR;
extern volatile uint32_t ALERT_2S;
extern volatile uint32_t ALERT_S1;
extern volatile uint32_t ALERT_S2;
extern volatile uint32_t ALERT_JOY;
extern volatile uint32_t count;

/****************************************************
 * Handler for T32_1 which starts ADC and clears interrupt
 *
 * Parameters
 *      None
 * Returns
 *      None
 ****************************************************/
void T32_INT1_IRQHandler();

/****************************************************
 * Handler for T32_2 which Alerts every 2 seconds
 *
 * Parameters
 *      None
 * Returns
 *      None
 ****************************************************/
void T32_INT2_IRQHandler();

/****************************************************
 * ADC14 Handler gets analog inputs for x and y
 *
 * Parameters
 *      None
 * Returns
 *      None
 ****************************************************/
void ADC14_IRQHandler(void);

#endif /* INTERRUPTS_H_ */
