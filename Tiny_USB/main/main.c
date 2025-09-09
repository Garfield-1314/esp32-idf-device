#include "tusb.h"

// 初始化 TinyUSB
void app_main(void)
{
    tusb_init();

    while (1)
    {
        tud_task(); // 处理 USB 事件

        // 检查 CDC 是否已连接
        if (tud_cdc_connected())
        {
            // 如果有数据可读
            if (tud_cdc_available())
            {
                uint8_t buf[64];
                uint32_t count = tud_cdc_read(buf, sizeof(buf));
                // 回显收到的数据
                tud_cdc_write(buf, count);
                tud_cdc_write_flush();
            }
        }
        vTaskDelay(10 / portTICK_PERIOD_MS);
    }
}