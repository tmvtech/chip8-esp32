#include "espdisplay.h"
#include "chip8.h"

EspDisplay::EspDisplay(U8G2* oled)
{
    logger = TLogger::getInstance();
    this->oled = oled;
}

void EspDisplay::init()
{
    oled->begin();
    oled->clearDisplay();
    logger->log("Display ready", ELogLevel::INFO);
}

void EspDisplay::deinit() 
{
    delete oled;
}

void EspDisplay::draw(uint8_t framebuffer[][64], uint16_t width, uint16_t height) 
{
    for (int y = 0; y < SCREEN_HEIGHT; y++)
        for (int x = 0; x < SCREEN_WIDTH; x++)
            if (framebuffer[y][x])
                oled->drawBox(x * 2, y * 2, 2, 2); // 1 chip8 pixel is 2*2 pixels in oled
}

void EspDisplay::update()
{
    oled->sendBuffer();
    oled->clearBuffer();
}
