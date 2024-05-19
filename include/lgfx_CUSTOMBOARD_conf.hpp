/**
 * @file lgfx_CUSTOMBOARD_conf.hpp
 * @author Jordi Gauchía (jgauchia@gmx.es)
 * @brief  LOVYANGFX TFT driver for CUSTOMBOARD
 * @version 0.1.8
 * @date 2024-05
 */

#ifndef LGFX_CUSTOMBOARD_CONF_HPP
#define LGFX_CUSTOMBOARD_CONF_HPP

#define LGFX_USE_V1

#include "LovyanGFX.hpp"

class LGFX : public lgfx::LGFX_Device
{
    lgfx::Panel_ILI9481 _panel_instance;
    lgfx::Bus_SPI _bus_instance;
    lgfx::Touch_XPT2046 _touch_instance;

public:
    LGFX(void)
    {
        {
            auto cfg = _bus_instance.config();
            cfg.spi_host = VSPI_HOST;
            cfg.spi_mode = 0;
            cfg.freq_write = 15000000;
            cfg.freq_read =  10000000;
            cfg.spi_3wire = true;
            cfg.use_lock = false;
            cfg.dma_channel = SPI_DMA_CH_AUTO;
            cfg.pin_sclk = 18;
            cfg.pin_mosi = 23;
            cfg.pin_miso = 19;
            cfg.pin_dc = 2;
            _bus_instance.config(cfg);
            _panel_instance.setBus(&_bus_instance);
        }

        {
            auto cfg = _panel_instance.config();
            cfg.pin_cs = 15;
            cfg.pin_rst = 4;
            cfg.pin_busy = -1;
            cfg.panel_width = 480;
            cfg.panel_height = 320;
            cfg.memory_width = 480;
            cfg.memory_height = 320;
            cfg.offset_x = 0;
            cfg.offset_y = 0;
            cfg.offset_rotation = 0;
            cfg.dummy_read_pixel = 8;
            cfg.dummy_read_bits = 1;
            cfg.readable = true;
            cfg.invert = true;
            cfg.rgb_order = false;
            cfg.dlen_16bit = false;
            cfg.bus_shared = true;
            _panel_instance.config(cfg);
        }

        {
            auto cfg = _touch_instance.config();
            cfg.x_min = 0;
            cfg.x_max = 480;
            cfg.y_min = 0;
            cfg.y_max = 320;
            cfg.pin_int = 5;
            cfg.bus_shared = true;
            cfg.offset_rotation = 0;
            cfg.spi_host = VSPI_HOST;
            cfg.freq = 2500000;
            cfg.pin_sclk = 18;
            cfg.pin_mosi = 23;
            cfg.pin_miso = 19;
            cfg.pin_cs = 21;
            _touch_instance.config(cfg);
            _panel_instance.setTouch(&_touch_instance);
        }
        setPanel(&_panel_instance);
    }
};

#endif
