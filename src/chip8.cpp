#include <iostream>
#include <chrono>
#include <thread>

#include "chip8.h"
#include "cpu.h"
#include "logger.h"

TChip8::TChip8()
{
    m_logger = TLogger::getInstance();
    m_cpu = new TCpu(this);
    m_emulatorRunning = true;
    m_key_pressed = false;
    m_display = nullptr;
    m_keyboard = nullptr;
    m_sound = nullptr;
}

TChip8::~TChip8()
{

}

void TChip8::init(std::string rom_path)
{
	// Clear frame buffer
    for(auto i = 0; i < SCREEN_HEIGHT; i++)
        for(auto j = 0; j < SCREEN_WIDTH; j++)
            m_screen[i][j] = 0;

    // Clear stack
    for(auto i = 0; i < STACK_SIZE; i++)
        m_stack[i] = 0;

    // Clear RAM
    for(auto i = 0; i < TOTAL_RAM; i++)
        m_ram[i] = 0;

    // Load font set into memory
    for(auto i = 0; i < FONTSET_SIZE; i++)
        m_ram[i] = FONTSET[i];

    // Reset timers
    m_delay_timer = 0;
    m_sound_timer = 0;

    // Start keyboard state as all unpressed
    for (auto i = 0; i < NUM_KEYS; i++)
        m_keys[i] = 0;

    m_key_pressed = false;
    
    // Init cpu registers
    m_cpu->init();
    
    // Load ROM to the ram
    m_loader = new TRomLoader();
    m_loader->loadRom(rom_path, m_ram+PROGRAM_START_ADDR);
    delete m_loader;
    
    // Initialize display lib
    m_display->init();

    // Initialize sound lib
    m_sound->init();
  
    // Initialize keyboard lib
    m_keyboard->init();
}

// Executes one cycle of the processor
void TChip8::run()
{
    if (!m_emulatorRunning)
        return;

    using clock = std::chrono::high_resolution_clock;
    clock::time_point start = clock::now(), end;

    m_cpu->fetch();
    m_cpu->decode();
    m_cpu->execute();

    m_keyboard->update(m_keys, &m_emulatorRunning);

    if(m_tickCounter >= 20)
    {
        m_tickCounter = 0;
        m_display->draw(m_screen, SCREEN_WIDTH, SCREEN_HEIGHT);
        m_display->update();
    
        // Update timers ~60Hz
        if(m_delay_timer > 0)
            m_delay_timer--;

        if(m_sound_timer > 0)
        {
            m_sound_timer--;
            m_sound->playTune();
        }
        else
            m_sound->pauseTune();
            
    }

    m_tickCounter++;
    end = clock::now();

    // Calculate tick time
    int64_t t = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    // if t is less than 1ms, sleep (1000 - t)µs
    int64_t sleepTime = 1000 - t;
    if (sleepTime > 0) 
        delayMicroseconds(sleepTime);
}

void TChip8::deinit()
{
	m_cpu->deinit();
	
    m_display->deinit();
    
    m_keyboard->deinit();

    m_sound->deinit();
}

void TChip8::setDisplay(TDisplay* display)
{
    m_display = display;
}

void TChip8::setKeyboard(TKeyboard* keyboard)
{
    m_keyboard = keyboard;
}

void TChip8::setSound(TSound* sound)
{
    m_sound = sound;
}
