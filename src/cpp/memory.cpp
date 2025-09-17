#include <memory.hpp>

Memory::Memory() {
    std::array<u8, 80> fonts = {
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

    for (u8 i = 0; i < fonts.size(); i++) this->mmry[i] = fonts[i];
}

usize Memory::totalMemorySize() const noexcept {
    return this->mmry.size();
}

bool Memory::isMemoryAccessLegal(u16 addr) const noexcept {
    if (addr <= 0x01FF || addr >= 0x0FFF) return false;
    return true;
}

bool Memory::isMemoryAccessLegal(u16 addr, u16 len) const noexcept {
    if (addr <= 0x01FF || (addr + len) > 0x0FFF) return false;
    return true;
}

u8 Memory::read(u16 mory_addr) const {
    if (!this->isMemoryAccessLegal(mory_addr)) throw MemoryException(mory_addr);
    return this->mmry[mory_addr];
}

void Memory::read(u16 mory_addr, std::vector<u8>& data_bffr) const {
    if (!this->isMemoryAccessLegal(mory_addr, data_bffr.size()))
        throw MemoryException(mory_addr);


    // Use std::size_t for the loop index to prevent overflow
    for (std::size_t i = 0; i < data_bffr.size(); ++i)
        data_bffr[i] = this->mmry[mory_addr + i];

}

void Memory::write(u16 mory_addr, u8 data) {
    if (!this->isMemoryAccessLegal(mory_addr)) throw MemoryException(mory_addr);
    this->mmry[mory_addr] = data;
}

void Memory::write(u16 mory_addr, std::span<const u8> write_data) {
    if (!this->isMemoryAccessLegal(mory_addr)) throw MemoryException(mory_addr);

    for (u8 i = 0; i < write_data.size(); i++)
        this->mmry[mory_addr + i] = write_data[i];
}

u16 Memory::getFontAddr(u8 hxdcml_font_vl) const {
    return 0x000 + (hxdcml_font_vl * 5);
}