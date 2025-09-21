#pragma once
#include <instruction_set.hpp>
#include <SDL2/SDL_Keyboard.h>

class HexConsole : public Console {
    public:
    bool isKeyPressed(u8) override;
    u8 getKey() override;
    u8 waitForKey() override;
};