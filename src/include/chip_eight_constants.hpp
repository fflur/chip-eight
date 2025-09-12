#pragma once
#include <chip_types.hpp>

constexpr u16 MEMORY_SIZE = 4096; // 4KB of memory.
constexpr u16 MAX_ROM_SIZE = 3584; // 3.5KB of ROM.
constexpr u16 MIN_ROM_SIZE = 32; // 32 bytes minimum ROM size.
constexpr u16 ROM_STARTING_POS = 512; // ROMs start at memory address 0x200 (512).