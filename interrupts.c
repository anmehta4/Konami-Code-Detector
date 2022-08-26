/*
 * interrupts.c
 *
 *      Author: Arnav Mehta
 */

#include "interrupts.h"
#include "gpio.h"
#include <stdbool.h>
#include <stdint.h>

volatile uint32_t PS2_X_DIR = false;
volatile uint32_t PS2_Y_DIR = false;
volatile uint32_t ALERT_2S = false;
volatile uint32_t ALERT_S1 = false;
volatile uint32_t ALERT_S2 = false;
volatile uint32_t ALERT_JOY = false;
volatile uint32_t count = 0;


// All Interrupt service routines used MUST be written in this file

/****************************************************
 * Handler for T32_1 which starts ADC and clears interrupt
 *
 * Parameters
 *      None
 * Returns
 *      None
 ****************************************************/
void T32_INT1_IRQHandler() {

    //Start an ADC Conversion
    ADC14->CTL0 |= ADC14_CTL0_SC | ADC14_CTL0_ENC;

    //clear the Timer interrupt
    TIMER32_1->INTCLR = BIT0;

    static uint8_t button_state_1 = 0x00;
    static uint8_t button_state_2 = 0x00;
    static uint8_t button_state_3 = 0x00;

    //debounce push buttons S1, S2 and S3

    button_state_1 = button_state_1 << 1; //S1
    button_state_2 = button_state_2 << 1; //S2
    button_state_3 = button_state_3 << 1; //JOY

    //If any button is pressed append a one to the button_state
    if((P5->IN & BIT1) == 0) {
        button_state_1 |= 0x01;
    }

    if((P3->IN & BIT5) == 0) {
        button_state_2 |= 0x01;
    }

    if((P4->IN & BIT1) == 0) {
       button_state_3 |= 0x01;
    }

    // checking for 0x3 => 11 for previous and current reaading
    if(button_state_1 == 0x3) {
        ALERT_S1 = true;
    } else {
        ALERT_S1 = false;
    }

    if(button_state_2 == 0x3) {
        ALERT_S2 = true;
    } else {
        ALERT_S2 = false;
    }

    if(button_state_3 == 0x3) {
        ALERT_JOY = true;
    } else {
        ALERT_JOY = false;
    }
}

/****************************************************
 * Handler for T32_2 which Alerts every 2 seconds
 *
 * Parameters
 *      None
 * Returns
 *      None
 ****************************************************/
void T32_INT2_IRQHandler() {

    ALERT_2S = false;

    count = count + 1;
    //ensure it runs for 2seconds = 20*100ms
    if(count == 20) {
        ALERT_2S = true;
        count = 0;
    }

    TIMER32_2->INTCLR = BIT0;
}

/****************************************************
 * ADC14 Handler gets analog inputs for x and y
 *
 * Parameters
 *      None
 * Returns
 *      None
 ****************************************************/
void ADC14_IRQHandler(void) {

    PS2_X_DIR = ADC14->MEM[0];
    PS2_Y_DIR = ADC14->MEM[1];
}

