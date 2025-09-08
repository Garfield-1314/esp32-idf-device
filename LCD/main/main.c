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
    esp_lcd_panel_handle_t panel_handle = lcd_init();

    // 准备绘图缓冲区
    size_t buffer_size = LCD_H_RES * LCD_V_RES;
    uint16_t *buffer = heap_caps_malloc(buffer_size * sizeof(uint16_t), MALLOC_CAP_DMA | MALLOC_CAP_8BIT);
    if (buffer == NULL) {
        ESP_LOGE(TAG, "Failed to allocate buffer memory");
        return;
    }

    // 填充颜色
    for (size_t i = 0; i < buffer_size; i++) {
        buffer[i] = __builtin_bswap16(0x0000); // 红色，字节序适配
    }

    ESP_ERROR_CHECK(esp_lcd_panel_draw_bitmap(panel_handle, 0, 0, LCD_H_RES, LCD_V_RES, buffer));
    ESP_LOGI(TAG, "ST7789 initialization and test pattern complete");

    lcd_draw_int32(buffer, 10, 20, 234589, 0xFFFF);
    esp_lcd_panel_draw_bitmap(panel_handle, 0, 0, LCD_H_RES, LCD_V_RES, buffer);

    int a = 0;
    while (1) {
        
        lcd_draw_int32(buffer, 10, 20, a, 0xFFFF);
        esp_lcd_panel_draw_bitmap(panel_handle, 0, 0, LCD_H_RES, LCD_V_RES, buffer);
        
        a++;
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

