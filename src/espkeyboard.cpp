#include "espkeyboard.h"
#include "Arduino.h"

uint8_t EspKB_PinsToKey[4][4] = 
{
    {0x1, 0x2, 0x3, 0xC},
    {0x4, 0x5, 0x6, 0xD},
    {0x7, 0x8, 0x9, 0xE},
    {0xA, 0x0, 0xB, 0xF}
};

EspKeyboard::EspKeyboard(uint16_t pins[8])
{
    m_logger = TLogger::getInstance();
    for (uint8_t i = 0; i < EspKB_PinCount; i++)
        m_pins[i] = pins[i];
}

void EspKeyboard::init() 
{
    // First 4 = output pins
    for (uint8_t i = 0; i < EspKB_PinHalf; i++)
        pinMode(m_pins[i], OUTPUT);
    // Other 4 = input pins
    for (uint8_t i = 0; i < EspKB_PinHalf; i++)
        pinMode(m_pins[EspKB_PinHalf + i], INPUT_PULLUP);
    m_logger->log("Keyboard ready", ELogLevel::INFO);
}

void EspKeyboard::update(uint8_t* key_map, bool* running) 
{
    for (int y = 0; y < EspKB_PinHalf; y++)
    {
        // Set row pin as low
        digitalWrite(m_pins[y], LOW);
        // Set button as pressed if collumn pin is low
        for (int x = 0; x < EspKB_PinHalf; x++)
            key_map[EspKB_PinsToKey[x][y]] = !digitalRead(m_pins[EspKB_PinHalf + x]);
        // Set row as high
        digitalWrite(m_pins[y], HIGH);
    }
}

void EspKeyboard::deinit() {}
