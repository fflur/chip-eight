#pragma once
#include <random>
#include <registers.hpp>
#include <memory.hpp>
#include <stack.hpp>

// This class represents the display interface. This is to inverse the control
// and allow for different display implementations.
// In this way, this module does not depend on a specific display implementation.
// The same applies to the Console class below.
class Display {
    public:
    virtual ~Display() = default;
    virtual void renderSprite(u8*, u8, u8, u8) = 0;
    virtual bool hasPixelErased() = 0;
    virtual void clearScreen() = 0;
};

class Console {
    public:
    virtual ~Console() = default;
    virtual bool isKeyPressed(u8) = 0;
    virtual u8 getKey() = 0;
};

// This class is responsible for executing the instructions.
// Each method corresponds to an instruction in the Chip-8 instruction set.
// This class is crucial for the functioning of the Chip-8 interpreter,
// as it directly manipulates the state of the machine.
class InstructionSetExecutor {
    // To keep track of the state of the machine this class will,
    // have an instance of each component known to the machine.
    // Only Display and Console are pointers, as they are interfaces.
    // The rest are actual instances of the components.
    private:
    GeneralRegisters gnrl_rgrs;
    IndexRegister indx_rgtr;
    ProgramCounter pgrm_cntr;
    Stack stck;
    Memory mmry;
    Display* dspy;
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
    void displaySprite(u8, u8, u8); //Dxyn // TODO
    void skipInstructionIfKey(u8); //Ex9E // TODO
    void skipInstructionIfKeyNot(u8); //ExA1 // TODO
    void setDelayTimerValue(u8); //Fx07 // TODO
    void waitForKey(u8); //Fx0A // TODO
    void setDelayTimer(u8); //Fx15 // TODO
    void setSoundTimer(u8); //Fx18 // TODO
    void addStoreInRegI(u8); //Fx1E // TODO
    void setFontSpriteLocation(u8); // Fx29 // TODO
    void storeBCDOf(u8); // Fx33 // TODO
    void writeToMemory(u8); //Fx55 // TODO
    void readFromMemory(u8); // Fx65 // TODO
};

class InstructionDecoder {
    private:
    u16 instruction;
    std::array<u8, 4> nibbles;
    u8 crnt_nble_pstn;
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