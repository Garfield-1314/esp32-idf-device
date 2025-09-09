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
    vTaskDelay(pdMS_TO_TICKS(100)); // 等待LCD初始化完成

   
    vTaskDelay(pdMS_TO_TICKS(500)); // 显示2秒

    // 屏幕填充测试：红、绿、蓝、白、黑
    uint16_t colors[] = {0xF800, 0x07E0, 0x001F, 0xFFFF, 0x0000};
    const char* color_names[] = {"RED", "GREEN", "BLUE", "WHITE", "BLACK"};
    for (int i = 0; i < 5; i++) {
        lcd_clear_buffer(0,0,0,0,colors[i]);
        printf("Fill color: %s\n", color_names[i]);
        vTaskDelay(pdMS_TO_TICKS(100));
    }
    lcd_draw_string(2, 2, "Hello, ESP32!", 0xFFFF);
    vTaskDelay(pdMS_TO_TICKS(1000)); // 显示1秒
        // 进入原有循环
    int a = 0;
    while (1) {
        lcd_draw_int32(2, 20, a, 0xFFFF);
        a++;
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

