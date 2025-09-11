// Loading the game ROM.
// Component initialization.
// Loads fonts.
// Enters the execution loop.
// Display & Input handling.
// RegistersManager, Memory, Display, Console, InstructionSetExecutor,
// InstructionDecoder.

#ifndef SDL_MAIN_HANDLED
#define SDL_MAIN_HANDLED

#include <chip_eight.hpp>
#include <chip_exceptions.hpp>

int main (int argc, char *argv[]) {
    CHIP8 chp8;
    while () { chp8.cycle(); }
    return 0;
}

#endif
