#ifndef CONSOLE_HPP
#define CONSOLE_HPP

#include <InstructionSet.hpp>
#include <SDL2/SDL.h>

class HexConsole {
    public:
        HexConsole();
        ~HexConsole();
        bool isKeyPressed(u8);
        u8 getKey();
};

#endif // !CONSOLE_HPP
