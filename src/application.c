// application file
// executables can be called by main

#include "application.h"

// configures GPIO
void vConfigureGpio()
{
    // initialize LED pin
    gpio_init(PIN_LED);
    gpio_set_dir(PIN_LED, GPIO_OUT);

    // Set up our UART with the required speed.
    uart_init(UART_ID, BAUD_RATE);

    // Set the TX and RX pins by using the function select on the GPIO
    // Set datasheet for more information on function select
    gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);
}

// this is the main project application
void vMainApplication()
{
    vConfigureGpio();

    // runs indefinitely
    for(;;)
    {
        gpio_put(PIN_LED, 1);
        uart_puts(UART_ID, "blink\n");

        // When using an RTOS, we no longer use sleep_ms()
        // instead, we yield the task with vTaskDelay( ticks );
        // ticks are the number of operating system ticks to delay
        // pdMS_TO_TICKS( milliseconds ) estimates the number of ticks to delay to wait a given number of milliseconds 
        // look in FreeRTOSConfig.h to see the specific tick rate settings

        // this function delays 500 milliseconds
        // if the tick rate is 100 Hz, or 10 milliseconds per tick, pdMS_TO_TICKS(500) = 50 ticks
        vTaskDelay(pdMS_TO_TICKS(500));
        gpio_put(PIN_LED, 0);
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}
