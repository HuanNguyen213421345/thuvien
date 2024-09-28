#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/timers.h"
#include "freertos/event_groups.h"
#include "sdkconfig.h"
#include "esp_system.h"
#include "esp_spi_flash.h"
#include "input_iot.h"
#include "output_iot.h"

#define BIT_EVENT_BUTTON_PRESS (1<<0)
#define BIT_EVENT_UARTN_RECV (1<<1)

TimerHandle_t xTimers[ 2 ];//khai bao so luong timer
EventGroupHandle_t xEventGroup;

void vTask1( void * pvParameters )
{
    for( ;; )
    {
        EventBits_t uxBits = xEventGroupWaitBits(
               xEventGroup,   /* The event group being tested. */
               BIT_EVENT_BUTTON_PRESS | BIT_EVENT_UARTN_RECV, /* The bits within the event group to wait for. */
               pdTRUE,        /* BIT_0 & BIT_4 should be cleared before returning. */
               pdFALSE,       /* Don't wait for both bits, either bit will do. */
               portMAX_DELAY);/* Wait a maximum of 100ms for either bit to be set. */

        if(uxBits & BIT_EVENT_BUTTON_PRESS)
        {
            printf("BUTTON_PRESS\n");
            output_io_toggle(2);
        }
        if(uxBits & BIT_EVENT_UARTN_RECV)
        {
            printf("UART_DATA\n");
        }
    }
}

void vTimerCallback( TimerHandle_t xTimer )
{
    configASSERT( xTimer );
    int ulCount = ( uint32_t ) pvTimerGetTimerID( xTimer );
    if(ulCount == 0)
    {
        output_io_toggle(2);
    }
    else if(ulCount == 1)
    {
        printf("hello\n");
    }
   
}         

void button_callback(int pin){
    if(pin == GPIO_NUM_0)
    {
        BaseType_t pxHigherPriorityTaskWoken;
        xEventGroupSetBitsFromISR(xEventGroup, BIT_EVENT_BUTTON_PRESS, &pxHigherPriorityTaskWoken );/* The bits being set. */
    }
}

void app_main(void)
{
    xTimers[ 0 ] = xTimerCreate( "TimerBlink", pdMS_TO_TICKS( 500 ),pdTRUE, ( void * ) 0, vTimerCallback );
    xTimers[ 1 ] = xTimerCreate( "Timerprintf", pdMS_TO_TICKS( 1000 ),pdTRUE, ( void * ) 1, vTimerCallback );

//    xTimerStart(xTimers[0],0);
//    xTimerStart(xTimers[1],0);
    
    output_io_create(2);
    input_io_create(0, HI_TO_LO);
    input_set_callback(button_callback);

    xEventGroup = xEventGroupCreate();

    xTaskCreate(
                    vTask1,       /* Function that implements the task. */
                    "vTask1",          /* Text name for the task. */
                    1024*2,      /* Stack size in words, not bytes. */
                    NULL,    /* Parameter passed into the task. */
                    4,/* Priority at which the task is created. */
                    NULL );      /* Used to pass out the created task's handle. */

}





