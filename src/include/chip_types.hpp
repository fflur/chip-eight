#ifndef CHIP_EIGHT_TYPES
#define CHIP_EIGHT_TYPES

#include <cstdint>

using u8  = std::uint8_t;
using u16 = std::uint16_t;
using u32 = std::uint32_t;
using i8  = std::int8_t;
using i16 = std::int16_t;
using i32 = std::int32_t;

constexpr size_t MAX_MEMORY_SIZE = 4096;
constexpr size_t MAX_ROM_SIZE = 3584;
constexpr size_t MIN_ROM_SIZE = 32;
constexpr size_t ROM_STARTING_POS = 512;

#endif // CHIP_EIGHT_TYPES