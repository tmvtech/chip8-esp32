#ifndef __ESPSOUND_H__
#define __ESPSOUND_H__

#include "logger.h"
#include "sound.h"

class EspSound : public TSound
{
    uint16_t m_pin, m_channel, m_freq;
    // Logging
    std::shared_ptr<TLogger> m_logger;

public:
    EspSound(uint16_t pin, uint8_t channel, uint32_t freq);

    virtual void init() override;
    virtual void playTune() override;
    virtual void pauseTune() override;
    virtual void deinit() override;
};

#endif
