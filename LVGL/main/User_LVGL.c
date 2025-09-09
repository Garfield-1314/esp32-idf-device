#include "lvgl.h"  
#include "LCD.h"

// 定义屏幕尺寸（根据你的实际屏幕修改）
#define LCD_WIDTH  240
#define LCD_HEIGHT 240

// 定义LVGL缓冲区（双缓冲，各为屏幕高度的1/10）
static lv_color_t lvgl_buf1[LCD_WIDTH * (LCD_HEIGHT / 10)];
static lv_color_t lvgl_buf2[LCD_WIDTH * (LCD_HEIGHT / 10)];

// LVGL显示刷新回调函数
void lvgl_flush_cb(lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_p) {
    int32_t w = area->x2 - area->x1 + 1;
    int32_t h = area->y2 - area->y1 + 1;
    
    // 调用你的LCD驱动刷新函数
    lcd_draw_image(area->x1, area->y1, w, h, (const uint16_t *)color_p);
    
    // 必须调用！通知LVGL刷新完成
    lv_disp_flush_ready(disp_drv);
}

// 初始化LVGL和显示驱动
void init_lvgl(void) {

    // 初始化LCD硬件
    lcd_init();

    // 初始化LVGL核心
    lv_init();
    
    // 初始化显示驱动
    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);
    
    // 设置屏幕分辨率
    disp_drv.hor_res = LCD_WIDTH;
    disp_drv.ver_res = LCD_HEIGHT;
    
    // 设置刷新回调
    disp_drv.flush_cb = lvgl_flush_cb;
    
    // 设置显示缓冲区
    static lv_disp_draw_buf_t disp_buf;
    lv_disp_draw_buf_init(&disp_buf, lvgl_buf1, lvgl_buf2, LCD_WIDTH * (LCD_HEIGHT / 10));
    disp_drv.draw_buf = &disp_buf;
    
    // 注册显示驱动
    lv_disp_drv_register(&disp_drv);
}

// 按钮事件回调函数：根据按钮状态切换状态标签内容和颜色
static void btn_event_cb(lv_event_t *e) { // e 为 LVGL 事件对象
    lv_obj_t *btn = lv_event_get_target(e); // 获取事件目标对象（按钮）
    lv_obj_t *status = (lv_obj_t *)lv_event_get_user_data(e); // 获取事件注册时传递的用户数据（状态标签）
    if(lv_obj_has_state(btn, LV_STATE_CHECKED)) { // 判断按钮是否被选中
        lv_label_set_text(status, "ON"); // 按钮选中，状态标签显示“ON”
        lv_obj_set_style_text_color(status, lv_color_hex(0xff0000), 0); // 状态标签文字颜色设为红色
    } else { // 按钮未选中
        lv_label_set_text(status, "OFF"); // 状态标签显示“OFF”
        lv_obj_set_style_text_color(status, lv_color_hex(0x00ff00), 0); // 状态标签文字颜色设为绿色
    }
}


static int number = 0;
lv_obj_t *label;
// 定时器回调函数
static void update_label_cb(lv_timer_t *timer) {
    number++;
    char buf[32];
    snprintf(buf, sizeof(buf), "nums: %d", number);
    lv_label_set_text(label, buf);
}


// 创建主界面，包括标题、按钮和状态标签
void create_ui(void) {
    lv_obj_t *scr = lv_scr_act(); // 获取当前活动屏幕对象，所有控件都添加到该屏幕
    lv_obj_set_style_bg_color(scr, lv_color_hex(0x003a57), LV_PART_MAIN); // 设置屏幕背景色为深蓝色

    lv_obj_t *title = lv_label_create(scr); // 创建标题标签
    lv_label_set_text(title, "ESP32 LVGL Demo"); // 设置标题文本
    lv_obj_set_style_text_font(title, &lv_font_montserrat_14, 0); // 设置标题字体
    lv_obj_set_style_text_color(title, lv_color_white(), 0); // 设置标题文字颜色为白色
    lv_obj_align(title, LV_ALIGN_TOP_MID, 0, 20); // 标题标签顶部居中，向下偏移 20 像素

    lv_obj_t *btn = lv_btn_create(scr); // 创建按钮控件
    lv_obj_set_size(btn, 120, 50); // 设置按钮尺寸为 120x50
    lv_obj_align(btn, LV_ALIGN_CENTER, 0, 0); // 按钮居中显示
    lv_obj_add_flag(btn, LV_OBJ_FLAG_CHECKABLE); // 设置按钮为可切换状态

    lv_obj_t *btn_label = lv_label_create(btn); // 在按钮上创建标签
    lv_label_set_text(btn_label, "Click!"); // 设置按钮标签文本
    lv_obj_center(btn_label); // 按钮标签居中显示

    lv_obj_t *status = lv_label_create(scr); // 创建状态标签
    lv_label_set_text(status, "Ready"); // 设置状态标签初始文本
    lv_obj_set_style_text_font(status, &lv_font_montserrat_14, 0); // 设置状态标签字体
    lv_obj_set_style_text_color(status, lv_color_white(), 0); // 设置状态标签文字颜色为绿色
    lv_obj_align(status, LV_ALIGN_BOTTOM_MID, 0, -50); // 状态标签底部居中，向上偏移 20 像素

    lv_obj_add_event_cb(btn, btn_event_cb, LV_EVENT_VALUE_CHANGED, status); // 注册按钮事件回调，将状态标签作为用户数据传递，实现按钮与状态标签联动

        // 创建一个标签
    label = lv_label_create(lv_scr_act());
    lv_obj_set_style_text_font(label, &lv_font_montserrat_14, 0); // 设置标签字体
    lv_obj_set_style_text_color(label, lv_color_white(), 0); // 设置标签文字颜色为白色
    lv_label_set_text(label, "nums: 0");
    lv_obj_align(label, LV_ALIGN_BOTTOM_MID, 0, -20);

        // 创建定时器，每 500ms 更新一次
    lv_timer_create(update_label_cb, 500, NULL);
}

