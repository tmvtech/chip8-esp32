#ifndef __ESPKEYBOARD_H__
#define __ESPKEYBOARD_H__

#include <cstdint>

#include "keyboard.h"
#include "logger.h"

#define EspKB_PinCount 8
#define EspKB_PinHalf (EspKB_PinCount / 2)

using EspKB_Callback = void (*)();

class EspKeyboard : public TKeyboard
{
    // Logging
    std::shared_ptr<TLogger> m_logger;
    uint16_t m_pins[8];

public:
    EspKeyboard(uint16_t pins[8]);
    virtual void init() override;
    virtual void update(uint8_t* key_map, bool* running) override;
    virtual void deinit() override;
};

#endif
