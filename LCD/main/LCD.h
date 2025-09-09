#ifdef __cplusplus
extern "C" {
#endif

// 5x7 ASCII字模库声明
extern const unsigned char ASCII_5x7[96][7];

#ifdef __cplusplus
}
#endif
#ifndef LCD_H
#define LCD_H

#include "esp_lcd_panel_vendor.h"

// 屏幕参数定义
#define LCD_HOST SPI2_HOST // 推荐使用SPI2_HOST，部分ESP32型号SPI1_HOST不可用
#define LCD_PIXEL_CLOCK_HZ (5 * 1000 * 1000) // SPI时钟频率，10MHz

// 引脚定义 (已修改：IO21为CLK，IO47为SDA)
#define PIN_NUM_SCLK GPIO_NUM_21 // SPI时钟
#define PIN_NUM_MOSI GPIO_NUM_47 // SPI数据（SDA）
#define PIN_NUM_MISO GPIO_NUM_NC // ST7789通常不需要MISO
#define PIN_NUM_CS GPIO_NUM_44 // 如果屏幕没有CS引脚，可以设置为-1
#define PIN_NUM_DC GPIO_NUM_43
#define PIN_NUM_RST GPIO_NUM_NC
#define PIN_NUM_BCKL GPIO_NUM_48

// 屏幕分辨率 (请根据你的屏幕修改，常见的有240x240, 240x320, 135x240等)
#define LCD_H_RES 240
#define LCD_V_RES 240


void lcd_init(void);
void lcd_draw_char(int x, int y, char c, uint16_t color);
void lcd_draw_string(int x, int y, const char *str, uint16_t color);
void lcd_draw_int32(int x, int y, long int value, uint16_t color);
void lcd_draw_image(int x, int y, int width, int height, const uint16_t *image);
void lcd_clear_buffer(int x, int y, int width, int height, uint16_t color);

// extern const uint16_t font16x16_ascii[36][16];

#endif // LCD_H