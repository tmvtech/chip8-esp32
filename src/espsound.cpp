#include "Arduino.h"
#include "espsound.h"

EspSound::EspSound(uint16_t pin, uint8_t channel, uint32_t freq)
{
    m_pin = pin;
    m_channel = channel;
    m_freq = freq;
    m_logger = TLogger::getInstance();
}

void EspSound::init()
{
    pinMode(m_pin, OUTPUT);
    m_logger->log("Sound ready", ELogLevel::INFO);
}

void EspSound::deinit() {}

void EspSound::playTune() 
{
    ledcAttachPin(m_pin, m_channel);
    ledcWriteTone(m_channel, m_freq);
}

void EspSound::pauseTune() 
{
    ledcDetachPin(m_pin);
}
