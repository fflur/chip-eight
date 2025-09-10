#ifndef CONSOLE_HPP
#define CONSOLE_HPP

#include <InstructionSet.hpp>
#include <SDL2/SDL.h>

class HexConsole : public Console {
    public:
    bool isKeyPressed(u8) override;
    u8 getKey() override;
};

#endif // !CONSOLE_HPP