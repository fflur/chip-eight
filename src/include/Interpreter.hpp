#ifndef INTERPRETER
#define INTERPRETER

#include <array>
#include <vector>
#include <string>
#include <chip_exceptions.hpp>

// GeneralRegisters represent the 16 general purpose 8-bit registers (V0 to VF).
// VF is used as a flag register for some instructions.
// Therefore, the VF register should be handled differently.
// The VF register is the 16th register (index 15).
class GeneralRegisters {
    private:
    std::array<u8, 16> registers;
};

// This is the 16-bit register called I.
// This register is generally used to store memory addresses,
// so only the lowest (rightmost) 12 bits are usually used.
class IndexRegister {
    private:
    u16 register_i;
};

// The program counter (PC) should be 16-bit,
//and is used to store the currently executing address.
class ProgramCounter {
    private:
    u16 program_counter;
};


// The stack is an array of 16 16-bit values,
// used to store the address that the interpreter shoud return to
// when finished with a subroutine.
// Chip-8 allows for up to 16 levels of nested subroutines.
class Stack {
    private:
    std::array<u16, 16> memory_addresses; //stores address for control.
    u8 stack_pointer; //points to topmost level of stack.
};

class RegistersManager {
    private:
    std::array<u8, 16> registers;
    u8 register_delay_timer;
    u8 register_sound_timer;
    u16 register_i; //used to store memory address.

    void checkRegisterAccess(u8);

    public:
    std::array<u16, 16> mem_addresses; //stores address for control.
    u8 stack_pointer; //points to topmost level of stack.
    u16 program_counter; //currently executing address.

    RegistersManager();
    void setMemoryAddress(u16);
    u16 getMemoryAddress() const;
    void setFlag(u8);
    u8 getFlag() const;
    bool isEqual(u8, u8) const;
    bool compareRegister(u8, u8) const;
    void setRegisterValue(u8, u8);
    u8 getRegisterValue(u8) const;
    void setDelayTimer(u8);
    u8 getDelayTimer() const;
    void setSoundTimer(u8);
    u8 getSoundTimer() const;
};

class Memory {
    private:
    std::array<u8, MAX_MEMORY_SIZE> mem;

    void checkMemoryAccess(u16) const;

    public:
    Memory();
    void read(u16, u8*, u8) const;
    void write(u16, u8*, u8);
    void writeByte(u16 addr, u8 num);
    u16 getFontAddr(u8) const;
    void loadGame(std::array<u8, MAX_ROM_SIZE>);
    u16 fetchInstruction(u16) const;
};

#endif // !INTERPRETER_H
