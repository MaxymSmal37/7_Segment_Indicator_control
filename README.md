
# MSP430 Seven-Segment Display Driver

This project demonstrates driving a common-anode seven-segment display using an MSP430 microcontroller. The code is written in C and targets the MSP430 family microcontrollers.

## Description

The main purpose of this code is to display numbers on a seven-segment display. It provides functions to initialize the display, clear the display, print digits, print numbers, and control various animations on the display.

## Components

- MSP430 microcontroller
- Common-anode seven-segment display
- Resistors (if necessary)

## Pin Configuration

- Seven-Segment Display:
  - A - P1.3
  - B - P1.5
  - C - P1.7
  - D - P1.1
  - E - P1.0
  - F - P1.4
  - G - P1.6
  - DT - P1.2

- Display Digits:
  - D1 - P2.0
  - D2 - P2.1
  - D3 - P2.2
  - D4 - P2.5

## Functions

- `initDisplay()`: Initializes the display pins.
- `clearDisplay()`: Turns off all segments of the display.
- `printDigit(unsigned int digit, unsigned int numberOfDisplay)`: Prints a digit on a specific display.
- `printLine(unsigned int numberOfDisplay)`: Selects a display line to print on.
- `printNumber(int number)`: Prints a number on the display.
  

## Usage

1. Connect the MSP430 microcontroller and the seven-segment display according to the pin configuration.
2. Include the provided code in your MSP430 project.
3. Call the necessary functions to display numbers or run animations on the seven-segment display.

## Notes

- This code assumes a common-anode seven-segment display. Modify the segment pin configurations if you are using a common-cathode display.
- Adjust the delay times in the animation functions according to your preference.
