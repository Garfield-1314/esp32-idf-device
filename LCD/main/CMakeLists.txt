idf_component_register(SRCS "main.c"
                    "LCD.c"
                    PRIV_REQUIRES spi_flash
                    PRIV_REQUIRES esp_lcd    # 添加 esp_lcd 依赖
                    INCLUDE_DIRS "")
