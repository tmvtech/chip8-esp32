#ifndef __ESPDISPLAY_H__
#define __ESPDISPLAY_H__

#include <cstdint>
#include "display.h"
#include "logger.h"
#include "U8g2lib.h"

class EspDisplay: public TDisplay
{
    U8G2* oled;
    std::shared_ptr<TLogger> logger;

public:
    EspDisplay(U8G2* oled);
    virtual void init() override; 
    virtual void draw(uint8_t framebuffer[][64], uint16_t width, uint16_t height) override;
    virtual void update() override;
    virtual void deinit() override;
};

#endif
