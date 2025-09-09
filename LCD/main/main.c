#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/spi_master.h"
#include "driver/gpio.h"
#include "esp_lcd_panel_io.h"
#include "esp_lcd_panel_vendor.h"
#include "esp_lcd_panel_ops.h"
#include "esp_log.h"

#include "LCD.h"



// 主函数调用
void app_main(void)
{
    lcd_init();

    lcd_draw_int32(10, 20, 234589, 0xFFFF);

    int a = 0;
    while (1) {
        
        lcd_draw_int32(10, 20, a, 0xFFFF);
        
        
        a++;
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

