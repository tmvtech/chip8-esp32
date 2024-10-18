#include <Arduino.h>
#include <memory>

#include "logger.h"
#include "chip8.h"

#include "espdisplay.h"
#include "espkeyboard.h"
#include "espsound.h"

#define BTN_NEXT_ROM_PIN GPIO_NUM_12

std::shared_ptr<TLogger> logger = TLogger::getInstance();
TChip8 emulator;
std::string roms[] = {"t", "b", "p", "m"};
uint8_t curr_rom = 0;
void nextRom()
{
    curr_rom++;
    if (curr_rom > sizeof(roms) / sizeof(*roms))
        curr_rom = 0;
    logger->log("Switching to rom " + roms[curr_rom], ELogLevel::WARN);
    emulator.deinit();
    emulator.init(roms[curr_rom]);
}

// U8g2 driver for the oled display
U8G2_SH1106_128X64_NONAME_F_4W_HW_SPI oled(U8G2_R0, 2, 4, 5);
EspDisplay display(&oled);
// Pins for the keyboard, first 4 are output, other 4 are input
uint16_t kbpins[] = { GPIO_NUM_32, GPIO_NUM_33, GPIO_NUM_25, GPIO_NUM_26,
                     GPIO_NUM_36, GPIO_NUM_39, GPIO_NUM_34, GPIO_NUM_35 };
EspKeyboard keyboard(kbpins);
EspSound sound(15, 4, 500);

void setup() 
{
    // Set 'next rom''s button pin as input
    pinMode(BTN_NEXT_ROM_PIN, INPUT_PULLUP);

    // Set log level as info (emulator runs slow in debug)
    logger->setLogLevel(ELogLevel::INFO);
    // Set modules
    emulator.setDisplay(&display);
    emulator.setKeyboard(&keyboard);
    emulator.setSound(&sound);
    // Initialize the emulator with the given rom
    emulator.init(roms[0]);
}

void loop() 
{
    // Check if next rom button is pressed
    if (!digitalRead(BTN_NEXT_ROM_PIN))
        nextRom();

    // Run emulator cycle
    emulator.run();
}
