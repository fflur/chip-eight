// 3584 B is the maximum size of the CHIP-8 ROMs.
// More than this and cannot fit into the memory.

#ifndef GAME_LOADER
#define GAME_LOADER

#include <string>
#include <array>
#include <fstream>
#include <chip_types.hpp>
#include <display.hpp>
#include <console.hpp>

class GameLoader {
    private:
    std::string file_path;

    public:
    GameLoader(std::string);
    ~GameLoader();
    bool validate();
    std::array<u8, MAX_ROM_SIZE> load();
};

class CHIP8 {
    private:
    RegistersManager* regr_mngr;
    Memory* mory;
    Display* dspy;
    Console* cnsl;
    InstructionSetExecutor* inst_exec;
    InstructionDecoder* inst_dcdr;

    public:
    CHIP8(std::string);
    void cycle();
    u16 fetchInstruction();
    ~CHIP8();
};

#endif