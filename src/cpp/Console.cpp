#include <console.hpp>

HexConsole::HexConsole() {
    // Initialize the key mapping between Chip-8 keys and SDL scancodes.
    this->key_maps = {
        {SDL_SCANCODE_1, 0x1},
        {SDL_SCANCODE_2, 0x2},
        {SDL_SCANCODE_3, 0x3},
        {SDL_SCANCODE_4, 0xC},
        {SDL_SCANCODE_Q, 0x4},
        {SDL_SCANCODE_W, 0x5},
        {SDL_SCANCODE_E, 0x6},
        {SDL_SCANCODE_R, 0xD},
        {SDL_SCANCODE_A, 0x7},
        {SDL_SCANCODE_S, 0x8},
        {SDL_SCANCODE_D, 0x9},
        {SDL_SCANCODE_F, 0xE},
        {SDL_SCANCODE_Z, 0xA},
        {SDL_SCANCODE_X, 0x0},
        {SDL_SCANCODE_C, 0xB},
        {SDL_SCANCODE_V, 0xF}
    };
}

KeySymbol HexConsole::getKey() const {
    return this->evnt.key.keysym;
}

KeySymbol HexConsole::waitForKey() {
    this->any_error = SDL_WaitEvent(&this->evnt);
    return this->evnt.key.keysym;
}

u8 HexConsole::updateEvent() {
    return SDL_PollEvent(&this->evnt);
}

u8 HexConsole::getMappedKey(Scancode key) const {
    return this->key_maps.at(key);
}

KeyboardEvent HexConsole::getKeyboardEvent() const {
    return this->evnt.key;
}