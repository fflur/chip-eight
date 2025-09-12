#ifndef CONSOLE_HPP
#define CONSOLE_HPP

#include <instruction_set.hpp>
#include <SFML/Window.hpp>

class HexConsole : public Console {
    public:
    bool isKeyPressed(u8) override;
    u8 getKey() override;
};

#endif // !CONSOLE_HPP