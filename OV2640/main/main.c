#include "esp_camera.h"
#include "esp_log.h"
#include "LCD.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "jpeg_decoder.h"


void process_image(int width, int height, int format, uint8_t *buf, size_t len) {
    // TODO: 实现图像处理逻辑
}

//WROVER-KIT PIN Map
#define CAM_PIN_PWDN    -1 //power down is not used
#define CAM_PIN_RESET   -1 //software reset will be performed
#define CAM_PIN_XCLK    15
#define CAM_PIN_SIOD    4
#define CAM_PIN_SIOC    5

#define CAM_PIN_D7      16
#define CAM_PIN_D6      17
#define CAM_PIN_D5      18
#define CAM_PIN_D4      12
#define CAM_PIN_D3      10
#define CAM_PIN_D2      8
#define CAM_PIN_D1       9
#define CAM_PIN_D0       11
#define CAM_PIN_VSYNC   6
#define CAM_PIN_HREF    7
#define CAM_PIN_PCLK    13

static camera_config_t camera_config = {
    .pin_pwdn  = CAM_PIN_PWDN,
    .pin_reset = CAM_PIN_RESET,
    .pin_xclk = CAM_PIN_XCLK,
    .pin_sccb_sda = CAM_PIN_SIOD,
    .pin_sccb_scl = CAM_PIN_SIOC,

    .pin_d7 = CAM_PIN_D7,
    .pin_d6 = CAM_PIN_D6,
    .pin_d5 = CAM_PIN_D5,
    .pin_d4 = CAM_PIN_D4,
    .pin_d3 = CAM_PIN_D3,
    .pin_d2 = CAM_PIN_D2,
    .pin_d1 = CAM_PIN_D1,
    .pin_d0 = CAM_PIN_D0,
    .pin_vsync = CAM_PIN_VSYNC,
    .pin_href = CAM_PIN_HREF,
    .pin_pclk = CAM_PIN_PCLK,

    .xclk_freq_hz = 20000000,
    .ledc_timer = LEDC_TIMER_0,
    .ledc_channel = LEDC_CHANNEL_0,

    .pixel_format = PIXFORMAT_RGB565, //YUV422,GRAYSCALE,RGB565,JPEG
    .frame_size = FRAMESIZE_QVGA, // 可选: FRAMESIZE_QQVGA, FRAMESIZE_QVGA, FRAMESIZE_UXGA 等

    .jpeg_quality = 12, //0-63, for OV series camera sensors, lower number means higher quality
    .fb_count = 1, //When jpeg mode is used, if fb_count more than one, the driver will work in continuous mode.
    .grab_mode = CAMERA_GRAB_WHEN_EMPTY//CAMERA_GRAB_LATEST. Sets when buffers should be filled
};

esp_err_t camera_init(){
    //power up the camera if PWDN pin is defined
    if(CAM_PIN_PWDN != -1){
        gpio_set_direction(CAM_PIN_PWDN, GPIO_MODE_OUTPUT);
        gpio_set_level(CAM_PIN_PWDN, 0);
    }
    //initialize the camera

    esp_err_t err = esp_camera_init(&camera_config);

    if (err != ESP_OK) {
        ESP_LOGE("OV2640", "Camera Init Failed");
        lcd_draw_string(0,10,"CIF",0xF800);
        while(1);
        return err;
    }
    lcd_draw_string(0,10,"CIC",0xF800);
    return ESP_OK;
}

// esp_err_t camera_capture(){
//     //acquire a frame
//     camera_fb_t * fb = esp_camera_fb_get();
//     if (!fb) {
//         ESP_LOGE("OV2640", "Camera Capture Failed");
//         return ESP_FAIL;
//     }
//     // 图像处理函数
//     process_image(fb->width, fb->height, fb->format, fb->buf, fb->len);
//     // 归还帧缓冲区
//     esp_camera_fb_return(fb);
//     return ESP_OK;
// }

// 主函数调用
void app_main() {
    // 初始化 LCD
    lcd_init();
    lcd_draw_string(0,10,"CIS",0xF800);
    // 初始化摄像头
    camera_init(&camera_config);

    int a = 0;
    while (1) {
        camera_fb_t *fb = esp_camera_fb_get();
        if (fb) {
            // 直接将 RGB565 数据送到 LCD，无需转换
            lcd_draw_image(0, 0, fb->width, fb->height, (uint16_t *)fb->buf);
            lcd_draw_int32(10, 20, a, 0xFFFF);
            esp_camera_fb_return(fb);
            a++;
        }
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}

