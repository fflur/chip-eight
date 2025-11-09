#pragma once
#include <instruction_set.hpp>
#include <sdl_types.hpp>

class HexConsole : public Console {
    private:
    Event evnt; // To store the event polled from SDL. Is a union.
    KeyMap key_maps; // To map Chip-8 keys to SDL key symbols.
    usize any_error;


    public:
    HexConsole();
    ~HexConsole() = default;
    KeySymbol getKey() const override;
    KeySymbol waitForKey() override;
    u8 getMappedKey(Scancode) const override;
    KeyboardEvent getKeyboardEvent() const override;
    u8 updateEvent();
};