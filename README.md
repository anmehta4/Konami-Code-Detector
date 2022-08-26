# Konami-Code-Detector

## Problem Overview

This code utilizes the GPIO, ADC, and Timer peripherals found on the MSP432 Launchpad.
The table below indicates which input devices on the MKII development platform will be used to input each stage of the Konami code.
Konami Sequence	↑	  ↑	 ↓	 ↓	 ←	 →	 ←	 →	 B	 A	 START
Input Device	JOY	JOY	JOY	JOY	JOY	JOY	JOY	JOY	S1	S2	JOY DOWN

## Konami Code Detection
Prior to the user pressing a button or moving the joystick, the application will turn the Launchpad’s tri-color LED off.  
When the user presses a button or moves the joystick, the blue LED is turned on to signify that user input has been detected
After the user enters 11 different input events, the application will either turn on the red LED (invalid Konami code) or the green LED (valid Konami code) of the tri-color LED (be sure to turn the blue LED off). 
The application will keep the red or green LED on for 2 seconds.  After 2 seconds, the red/green LED will be turned off and the main application will begin examining input events for the start of the Konami Code again.
For the purposes of this assignment, an input event is defined as the user pressing a button and releasing it OR the user moves the joystick in one of the 4 directions and then returns the joystick to the center position.  The user can press a button for as long as they want, but it will only be counted as a single event.  The user can also move the joystick out of the center position for as long as they want and it will only be counted as a single event.
