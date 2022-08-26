/*
 * timers.c
 *
 *      Author: Arnav Mehta
 */

#include "timers.h"
/*
 * Code used to initialize the timers in HW01
 */

/****************************************************
 * Configure Timer32_1 to configure a periodic interrupt
 *
 * Parameters
 *      ticks: number of interrupts per milli second
 * Returns
 *      None
 ****************************************************/
void ece353_T32_1_Interrupt_Ms(uint16_t ms) {

    //ticks = ( desired period / core clock period ) = (core clock freq * desired period in s)
    uint32_t ticks = (SystemCoreClock * ms)/1000 -1;

    //Stop the timer
    TIMER32_1->CONTROL = 0;

    //Set the Load register
    TIMER32_1->LOAD = ticks;

    //Enable the Timer32 interrupt in NVIC
    __enable_irq();
    NVIC_EnableIRQ(T32_INT1_IRQn);
    NVIC_SetPriority(T32_INT1_IRQn, 0);

    //Start Timer32 and enable interrupt
    TIMER32_1->CONTROL = TIMER32_CONTROL_ENABLE |   //turn timer 0n
                         TIMER32_CONTROL_MODE |     //periodic mode
                         TIMER32_CONTROL_SIZE |     //32 bit timer
                         TIMER32_CONTROL_IE;        //enable interrupt
}

/****************************************************
 * Configure Timer32_1 to configure a periodic interrupt
 *
 * Parameters
 *      ticks: number of interrupts per millisecond
 * Returns
 *      None
 ****************************************************/
void ece353_T32_2_Interrupt_Ms(uint16_t ms) {

    //ticks = ( desired period / core clock period ) = (core clock freq * desired period in s)
    uint32_t ticks = (SystemCoreClock * ms)/1000 -1;

    //Stop the timer
    TIMER32_2->CONTROL = 0;

    //Set the Load register
    TIMER32_2->LOAD = ticks;

    //Enable the Timer32 interrupt in NVIC
    __enable_irq();
    NVIC_EnableIRQ(T32_INT2_IRQn);
    NVIC_SetPriority(T32_INT2_IRQn, 0);

    //Start Timer32 and enable interrupt
    TIMER32_2->CONTROL = TIMER32_CONTROL_ENABLE |   //turn timer 0n
                         TIMER32_CONTROL_MODE |     //periodic mode
                         TIMER32_CONTROL_SIZE |     //32 bit timer
                         TIMER32_CONTROL_IE;        //enable interrupt
}


