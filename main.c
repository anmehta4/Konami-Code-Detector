/*
 * main.c
 *
 *      Author: Arnav Mehta
 */
#include "msp.h"
#include "gpio.h"
#include "adc.h"
#include "timers.h"
#include "interrupts.h"

#define VOLT_0P85 ((int)(0.85/(3.3/4096))) //1056
#define VOLT_2P50 ((int)(2.50/(3.3/4096))) //3103

/**
 * main.c
 */

/****************************************************
 * Turn RGB LED colors ON/OFF
 *
 * Parameters
 * on: if true, turn LED on
 *     if false, turn LED off
 ****************************************************/
void ece353_RGB_led(bool red_on, bool green_on, bool blue_on) {

    if(red_on) {
        //Turn LED on
        P2->OUT |= BIT0;
    } else {
        //Turn LED off
        P2->OUT &= ~BIT0;
    }

    if(green_on) {
        //Turn LED on
        P2->OUT |= BIT1;
    } else {
        //Turn LED off
        P2->OUT &= ~BIT1;
    }

    if(blue_on) {
        //Turn LED on
        P2->OUT |= BIT2;
    } else {
        //Turn LED off
        P2->OUT &= ~BIT2;
    }
}

/*****************************************************
 * Turns off LED after 2s
 *
 * Parameters:
 *      color: true for green and false for red
 * Returns
 *      None
 *****************************************************/
void ece353_LED_off_2_seconds() {
    count = 0;
    ALERT_2S = false;
    while(1) {
        if (ALERT_2S) {
            ece353_RGB_led(false, false, false);
            ALERT_2S = false;
            break;
        }
    }
}

/*****************************************************
 * Returns value based on input
 * 0 - RIGHT
 * 1 - LEFT
 * 2 - TOP
 * 3 - BOTTOM
 * 4 - S1 PRESSED
 * 5 - S2 PRESSED
 * 6 - JOY PRESSED
 *
 * Parameters:
 *      None
 * Returns
 *      Integer value based on input
 *****************************************************/
int check_input() {

    while (1) {
        if (PS2_X_DIR < VOLT_2P50 && PS2_X_DIR > VOLT_0P85 && PS2_Y_DIR < VOLT_2P50 && PS2_Y_DIR > VOLT_0P85
                && !ALERT_S1 && !ALERT_S2 && !ALERT_JOY) {
            while(1) {
                if (PS2_X_DIR > VOLT_2P50) {
                    return 0;
                } else if (PS2_X_DIR < VOLT_0P85) {
                    return 1;
                } else if (PS2_Y_DIR > VOLT_2P50) {
                    return 2;
                } else if (PS2_Y_DIR < VOLT_0P85) {
                    return 3;
                } else if (ALERT_S1) {
                    return 4;
                } else if (ALERT_S2) {
                    return 5;
                } else if (ALERT_JOY) {
                    return 6;
                }
            }
        }
    }
}

void main(void)
{
    uint32_t event_count = 0;
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer

	ece353_RGB_led_Init();
	ece353_ADC14_Init();
	ece353_MKII_S1_Init();
	ece353_MKII_S2_Init();
	ece353_PS2_XY_Init();
	ece353_PS2_Button_Init();

	//enable interrupts T32_1
	ece353_T32_1_Interrupt_Ms(20);
    ece353_T32_2_Interrupt_Ms(100);

    // enable NVIC
    __enable_irq();

	while(1) {

	    // Checking for the Konami Code
	    if(check_input() == 2) { event_count++; }
        ece353_RGB_led(false, false, true);
        if(check_input() == 2) { event_count++; }
        if(check_input() == 3) { event_count++; }
        if(check_input() == 3) { event_count++; }
        if(check_input() == 1) { event_count++; }
        if(check_input() == 0) { event_count++; }
        if(check_input() == 1) { event_count++; }
        if(check_input() == 0) { event_count++; }
        if(check_input() == 4) { event_count++; }
        if(check_input() == 5) { event_count++; }
        if(check_input() == 6) { event_count++; }

        // If Konami Code then switch on Green for 2s else Red for 2s
        if(event_count == 11) {
            ece353_RGB_led(false, true, false);
            ece353_LED_off_2_seconds();
            event_count = 0;
        } else {
            ece353_RGB_led(true, false, false);
            ece353_LED_off_2_seconds();
            event_count = 0;
        }
	}
}


