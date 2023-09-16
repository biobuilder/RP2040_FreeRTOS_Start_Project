// Damon Printz
// example code using FreeRTOS
// 9/13/2023

// application libraries
#include "application.h"

// execute the application
int main()
{
    stdio_init_all();

    // build tasks
    xTaskCreate(vMainApplication, "MYAPP", configMINIMAL_STACK_SIZE+30, NULL, 1, NULL);

    // start scheduler and run the tasks
    vTaskStartScheduler();
    while(1);
}