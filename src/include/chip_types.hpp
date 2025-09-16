#pragma once
#include <cstdint>

// Define fixed-width integer types for clarity and consistency.
// We don't care how the compilers handles it internally,
// as long as we get the expected bit-width.
// This idea came from the Zig programming language.
// The naming convention is similar.
// The types are defined as follows:
using u8  = std::uint8_t;  // 8-bit unsigned integer.
using u16 = std::uint16_t; // 16-bit unsigned integer.
using u32 = std::uint32_t; // 32-bit unsigned integer.
using u64 = std::uint64_t; // 64-bit unsigned integer.
using usize = std::size_t; // Unsigned integer type for sizes.
using i8  = std::int8_t;   // 8-bit signed integer.
using i16 = std::int16_t;  // 16-bit signed integer.
using i32 = std::int32_t;  // 32-bit signed integer.
using i64 = std::int64_t;  // 64-bit signed integer.