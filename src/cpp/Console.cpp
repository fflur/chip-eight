#include <console.hpp>

bool HexConsole::isKeyPressed(u8 ky_name) {
    if (ky_name != 2) return false;
    return true;
}

u8 HexConsole::getKey() { return 0; }

u8 HexConsole::waitForKey() { return 0; }