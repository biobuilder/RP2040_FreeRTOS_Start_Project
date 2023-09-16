// application-specific header file
// Damon Printz
// 9/13/2023

#ifndef APPLICATION_H
#define APPLICATION_H

// external libraries
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/uart.h"
#include "FreeRTOS.h"
#include "task.h"


// hardware definitions
#define PIN_LED   25

// We are using pins 0 and 1, but see the GPIO function select table in the
// datasheet for information on which other pins can be used.
#define UART_TX_PIN 0
#define UART_RX_PIN 1

#define UART_ID uart0
#define BAUD_RATE 115200


// function definitions
void vConfigureGpio();
void vMainApplication();

#endif