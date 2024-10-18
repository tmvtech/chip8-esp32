#include "romLoader.h"
#include "chip8.h"

TRomLoader::TRomLoader()
{
    m_logger = TLogger::getInstance();
}

TRomLoader::~TRomLoader()
{

}

void TRomLoader::loadRom(std::string& file_path, uint8_t* mem)
{
    m_logger->log("Loading ROM: " + file_path, ELogLevel::INFO);

    const uint8_t* pointer = nullptr; // rom data
    uint32_t size = 0;                // rom size in bytes
    switch (file_path.c_str()[0]) // use first letter of the name
    {
        // set pointer and size
        case 'b': pointer = rom_Breakout1; size = rom_Breakout1_size; break;
        case 'p': pointer = rom_Pong1; size = rom_Pong1_size; break;
        case 'm': pointer = rom_Maze1; size = rom_Maze1_size; break;
        case 't': pointer = rom_KeypadTest; size = rom_KeypadTest_size; break;
    }

    // check if pointer was set and size is valid
    if (pointer == nullptr || size == 0 || size > (PROGRAM_END_ADDR - PROGRAM_START_ADDR))
    {
        m_logger->log("Can't load ROM", ELogLevel::ERROR);
        exit(1);
        return;
    }

    // load rom to ram
    memcpy(mem, pointer, size);
    m_logger->log("Rom loaded successfully", ELogLevel::INFO);
}
