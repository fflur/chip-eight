#pragma once
#include <array>
#include <chip_exceptions.hpp>

// GeneralRegisters represent the 16 general purpose 8-bit registers (V0 to VF).
// VF is used as a flag register for some instructions.
// Therefore, the VF register should be handled differently.
// The VF register is the 16th register (index 15).
class GeneralRegisters {
    private:
    // Array of 16 8-bit registers.
    std::array<u8, 16> registers;
    // Check if the register access is legal (0 to 14).
    bool isAccessLegal(u8) const;

    public:
    // Read the value of a register at a given index.
    u8 read(u8) const;
    // Write a value to a register at a given index.
    void write(u8, u8);
    // Gets the value of the flag register (VF).
    u8 getFlag() const;
    // Sets the value of the flag register (VF).
    void setFlag(u8);
    // Resets all registers to 0.
    void reset();
};

// This is the 16-bit register called I.
// This register is generally used to store memory addresses,
// so only the lowest (rightmost) 12 bits are usually used.
class IndexRegister {
    private:
    u16 register_i;

    public:
    // Set the value of the index register.
    void set(u16);
    // Get the value of the index register.
    u16 get() const;
    // Reset the index register to 0.
    void reset();
};

// The program counter (PC) should be 16-bit,
// and is used to store the currently executing address.
class ProgramCounter {
    private:
    u16 program_counter;

    public:
    // Set the value of the program counter.
    void set(u16);
    // Get the value of the program counter.
    u16 get() const;
    // Increment the program counter by 2 (since each instruction is 2 bytes).
    void increment();
    // Reset the program counter to 0.
    void reset();
};

class Timer {
    private:
    u8 timer_value;

    public:
    // Set the value of the timer.
    void set(u8);
    // Get the value of the timer.
    u8 get() const;
    // Decrement the timer by 1 if it's greater than 0.
    void decrement();
    // Reset the timer to 0.
    void reset();
};