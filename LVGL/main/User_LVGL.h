// User_LVGL.h
#ifndef USER_LVGL_H
#define USER_LVGL_H

#include "lvgl.h"

#define LCD_WIDTH  240
#define LCD_HEIGHT 240

// LVGL 显示刷新回调函数声明
void lvgl_flush_cb(lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_p);

// LVGL 初始化函数声明
void init_lvgl(void);

// 创建用户界面
void create_ui(void);

void create_number_ui(void);

#endif // USER_LVGL_H
