#pragma once
#include <array>
#include <chip_eight_constants.hpp>
#include <chip_exceptions.hpp>

// The Chip-8 language is capable of accessing up to 4KB (4,096 bytes) of RAM,
// from location 0x000 (0) to 0xFFF (4095).
// The first 512 bytes, from 0x000 to 0x1FF,
// are where the original interpreter was located,
// and should not be used by programs.
class Memory {
    private:
    std::array<u8, MEMORY_SIZE> mmry;

    void checkMemoryAccess(u16) const;

    public:
    Memory();
    void read(u16, u8*, u8) const; // TODO: Change to std::array
    void write(u16, u8*, u8);
    void writeByte(u16 addr, u8 num);
    u16 getFontAddr(u8) const;
    void loadGame(std::array<u8, MAX_ROM_SIZE>);
    u16 fetchInstruction(u16) const;
};