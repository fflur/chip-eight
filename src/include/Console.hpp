#pragma once
#include <instruction_set.hpp>
#include <SFML/Window.hpp>

class HexConsole : public Console {
    public:
    bool isKeyPressed(u8) override;
    u8 getKey() override;
};