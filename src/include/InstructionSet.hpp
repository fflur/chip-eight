#ifndef INSTRUCTION_SET_HPP
#define INSTRUCTION_SET_HPP

#include <random>
#include <Interpreter.hpp>

class Display {
    public:
        virtual void renderSprite(u8*, u8, u8, u8);
        virtual bool hasPixelErased();
        virtual void clearScreen();
};

class Console {
    public:
        virtual bool isKeyPressed(u8);
        virtual u8 getKey();
};

class InvalidOpcodeException : public std::exception {
    private:
        std::string message;

    public:
        InvalidOpcodeException(u16);
        const char* what() const noexcept override;
};

class InstructionSetExecutor {
    private:
        Display* dsp;
        Console* cnsl;
    public:
        InstructionSetExecutor(Display*, Console*);
        ~InstructionSetExecutor();
        void clearDisplay();//00E0
        void returnFromSubroutine();//00EE
        void jumpToAddr(u16);//1nnn
        void callSubroutineAt(u16); //2nnn
        void skipInstructionIf(u8, u8); //3xkk
        void skipInstructionIfNot(u8, u8); //4xkk
        void skipInstructionIfReg(u8, u8); //5xy0
        void setRegTo(u8, u8); //6xkk
        void addValueToReg(u8, u8); //7xkk
        void storeFromToReg(u8, u8); //8xy0
        void doOrOn(u8, u8); //8xy1
        void doAndOn(u8, u8); //8xy2
        void doXorOn(u8, u8); //8xy3
        void addAndCarry(u8, u8); //8xy4
        void subAndBorrow(u8, u8); //8xy5
        void carryAndLSB(u8); //8xy6
        void subtractAndFlag(u8, u8); //8xy7
        void carryAndMSB(u8, u8); //8xyE
        void skipInstructionIfNotReg(u8, u8); //9xy0
        void setRegI(u16); //Annn
        void jumpToAddrWithRegZero(u16); //Bnnn
        void doAndWithRandom(u8, u8); //Cxkk
        void displaySprite(u8, u8, u8); //Dxyn
        void skipInstructionIfKey(u8); //Ex9E
        void skipInstructionIfKeyNot(u8); //ExA1
        void setDelayTimerValue(u8); //Fx07
        void waitForKey(u8); //Fx0A
        void setDelayTimer(u8); //Fx15
        void setSoundTimer(u8); //Fx18
        void addStoreInRegI(u8); //Fx1E
        void setFontSpriteLocation(u8); // Fx29
        void storeBCDOf(u8); // Fx33
        void writeToMemory(u8); //Fx55
        void readFromMemory(u8); // Fx65
};

class InstructionDecoder {
    private:
        u16 instruction;
        std::array<u8, 4> nibbles;
        u8 crnt_nble_pstn; // Current nibble's position.
        InstructionSetExecutor* inst_exec;

        u16 assembleNibblesFrom(u8);
        void skipNibble();
        void decodeZeroPrefix();
        void decodeEightPrefix();
        void decodeEPrefix();
        void decodeFPrefix();
        void decodeFZero();
        void decodeFOne();

    public:
        InstructionDecoder(InstructionSetExecutor*);
        ~InstructionDecoder();
        void breakIntoNibbles(u16);
        void decode();
};

class InstructionSetReader {
};

#endif // !INSTRUCTION_SET_H
