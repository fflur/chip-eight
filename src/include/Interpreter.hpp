#ifndef INTERPRETER_HPP
#define INTERPRETER_HPP

#include <array>
#include <vector>
#include <exception>
#include <string>
#include <chip8types.hpp>

namespace {
    class MemoryException : public std::exception {
        private:
            std::string message;

        public:
            MemoryException(u16);
            const char* what() const noexcept override;
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
            std::array<u8, 4096> mem;

            void checkMemoryAccess(u16) const;

        public:
            Memory();
            void read(u16, u8*, u8) const;
            void write(u16, u8*, u8); // TODO:
            void writeByte(u16 addr, u8 num);
            u16 getFontAddr(u8);
    };
}

namespace ChipEight {
    RegistersManager reg_mgr;
    Memory mem;
}

#endif // !INTERPRETER_H
