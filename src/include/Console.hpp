#pragma once
#include <instruction_set.hpp>
#include <sdl_types.hpp>

class HexConsole : public Console {
    private:
    Event evnt; // To store the event polled from SDL. Is a union.

    public:
    bool isKeyPressed(u8) const override;
    u8 getKey() const override;
    u8 waitForKey() override;
    u8 updateEvent();
    Event getKeyboardEvent() const;
};