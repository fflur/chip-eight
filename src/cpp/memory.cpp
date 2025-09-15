#include <memory.hpp>

Memory::Memory() {
    u8 fonts[] = {
        0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
        0x20, 0x60, 0x20, 0x20, 0x70, // 1
        0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
        0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
        0x90, 0x90, 0xF0, 0x10, 0x10, // 4
        0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
        0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
        0xF0, 0x10, 0x20, 0x40, 0x40, // 7
        0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
        0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
        0xF0, 0x90, 0xF0, 0x90, 0x90, // A
        0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
        0xF0, 0x80, 0x80, 0x80, 0xF0, // C
        0xE0, 0x90, 0x90, 0x90, 0xE0, // D
        0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
        0xF0, 0x80, 0xF0, 0x80, 0x80, // F
    };

    u8 font_size = sizeof(fonts)/sizeof(u8);
    for (u8 i = 0; i < font_size; i++) this->mmry[i] = fonts[i];
}

void Memory::checkMemoryAccess(u16 addr) const {
    if (addr <= 0x01FF || addr >= 0x0FFF) throw MemoryException(addr);
}

// TODO: Change to std::array
void Memory::read(
    u16 addr,
    std::array<u8, MAX_ROM_SIZE>& bytes_array,
    u8 arr_len
) const {
    for (u8 i = 0; i < arr_len; i++)
        bytes_array[i] = this->mmry[addr + i];
}

void Memory::write(u16 addr, u8* bytes, u8 arr_len) {
    for (u8 i = 0; i < arr_len; i++) {
        this->checkMemoryAccess(addr + i);
        this->mmry[addr + i] = *(bytes + i);
    }
}

void  Memory::writeByte(u16 mory_addr, u8 value) {
    this->checkMemoryAccess(mory_addr);
    this->mmry[mory_addr] = value;
}

u16 Memory::getFontAddr(u8 hex_font_val) const {
    return 0x000 + (hex_font_val * 5);
}

void Memory::loadGame(std::array<u8, MAX_ROM_SIZE> rom_file) {
    std::copy(
        rom_file.begin(), // Source start
        rom_file.end(), // Source end
        this->mmry.begin() + ROM_STARTING_POS // Destination start (index 512)
    );
}

u16 Memory::fetchInstruction(u16 prog_cntr) const {
    return (this->mmry[prog_cntr] << 8) | this->mmry[prog_cntr + 1];
}