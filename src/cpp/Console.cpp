#include <console.hpp>

bool HexConsole::isKeyPressed(u8 ky_name) const {
    if (ky_name != 2) return false;
    return true;
}

u8 HexConsole::getKey() const { return 0; }

u8 HexConsole::waitForKey() { return 0; }

u8 HexConsole::updateEvent() {
    return SDL_PollEvent(&this->evnt);
}