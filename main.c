#include <stdio.h>
#include "esp_timer.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "driver/gpio.h"
//ESP-IDF version 5.53
//https://esp32tutorials.com/esp32-timer-interrupt-esp-idf/

#define LED 18
enum{LO, HI};
static const char *TAG = "esp_timer_callback";

void esp_timer_callback(void *param)
{
    static bool ON;
    ON = !ON;
    gpio_set_level(LED, ON);
}

void app_main(void)
{
    ESP_LOGI(TAG,"esp_timer_callback example");
    //configure gpio 18 as output
    gpio_config_t phil =
    {
        .mode = GPIO_MODE_OUTPUT,
        .pin_bit_mask = 1ULL<<LED
    };
    //install gpio config
    gpio_config(&phil);

    //create esp_timer
    esp_timer_handle_t esp_timer_handle; //define a timer handle 'esp_timer_handle'

    //Set the timer configuration parameters by defining the structure esp_timer_create_args_t 
    //which also includes the callback function
    esp_timer_create_args_t esp_timer_config = 
    {
        .callback = &esp_timer_callback,
        .name = "Phils timer"
    };
    //create timer
     esp_timer_create(&esp_timer_config, &esp_timer_handle);
     esp_timer_start_periodic(esp_timer_handle, 1000000);//start the timer in periodic mode, period is 1000000us or 1s

     while(1)
     {
        esp_timer_dump(stdout);
        vTaskDelay(pdMS_TO_TICKS(1000));
     }
}
/*I (281) esp_timer_callback: esp_timer_callback example
Timer stats:
Name                  Period      Alarm       
timer@0x3ffaffc8      1000000     1031237     
Timer stats:
Name                  Period      Alarm       
timer@0x3ffaffc8      1000000     2031237     
Timer stats:
Name                  Period      Alarm       
timer@0x3ffaffc8      1000000     3031237     
Timer stats:
Name                  Period      Alarm       
timer@0x3ffaffc8      1000000     4031237     
Timer stats:
Name                  Period      Alarm       
timer@0x3ffaffc8      1000000     5031237     */