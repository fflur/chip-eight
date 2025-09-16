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

    bool isMemoryAccessLegal(u16) const noexcept;

    public:
    Memory();
    usize total_memory_size() const noexcept;
    u8 read(u16) const; // throws MemoryException
    void read(u16, std::span<u8>) const; // throws MemoryException
    void write(u16, u8);
    void write(u16, std::span<const u8>);
    u16 getFontAddr(u8) const;
};

// The read function will have two versions. One where it reads a single
// byte from the memory and another version where it reads multiple bytes
// from the memory and returns them as an array.
// The same applies to the write function.