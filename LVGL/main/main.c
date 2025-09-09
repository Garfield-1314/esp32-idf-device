#include <stdio.h>
#include "User_LVGL.h"
#include "freertos/FreeRTOS.h"

// 主函数
void app_main() {
    
    // 初始化LVGL
    init_lvgl();
    
    // 创建用户界面
    create_ui();
    // 主循环（可以处理其他任务）
    while(1) {
        lv_tick_inc(5);
        
        // 处理LVGL任务
        lv_timer_handler();
        vTaskDelay(pdMS_TO_TICKS(5)); // 1秒延迟
    }
}
