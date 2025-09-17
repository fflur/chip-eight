#include <instruction_set.hpp>

//---InstructionSetExecutor---//
// This implementation still needs to be refactored.
// In-progress.

InstructionSetExecutor::InstructionSetExecutor(
    Display* dspy,
    Console* cnsl
) {
    this->dspy = dspy;
    this->cnsl = cnsl;
}

InstructionSetExecutor::~InstructionSetExecutor() {
    delete this->dspy;
    delete this->cnsl;
    this->dspy = nullptr;
    this->cnsl = nullptr;
}

// 00E0 - Clears the display.
void InstructionSetExecutor::clearDisplay() {
    this->dspy->clearScreen();
}

// 00EE - Returns from a subroutine. The interpreter sets the program counter
// to the address at the top of the stack, then subtracts the stack pointer by 1.
void InstructionSetExecutor::returnFromSubroutine() {
    this->pgrm_cntr.set(this->stck.pop());
}

// 1nnn - Jumps to address nnn. The interpreter sets the program counter to nnn.
void InstructionSetExecutor::jumpToAddr(u16 addr) {
    this->pgrm_cntr.set(addr);
}

// 2nnn - Calls subroutine at nnn. The interpreter increments the stack pointer,
// then puts the current PC on the top of the stack. The PC is then set to nnn.
void InstructionSetExecutor::callSubroutineAt(u16 addr) {
    this->stck.push(this->pgrm_cntr.get());
    this->pgrm_cntr.set(addr);
}

//3xkk - Skips the next instruction if Vx = kk. The interpreter compares
// register Vx to kk, and if they are equal, increments the program counter by 2.
void InstructionSetExecutor::skipInstructionIf(u8 rgtr_x, u8 value) {
    if (this->gnrl_rgrs.read(rgtr_x) == value)
        this->pgrm_cntr.increment();
}

// 4xkk - Skips the next instruction if Vx != kk. The interpreter compares
// register Vx to kk, and if they are not equal, increments the program counter by 2.
void InstructionSetExecutor::skipInstructionIfNot(u8 rgtr_x, u8 value) {
    if (this->gnrl_rgrs.read(rgtr_x) != value)
        this->pgrm_cntr.increment();
}

// 5xy0 - Skips the next instruction if Vx = Vy. The interpreter compares
// register Vx to register Vy, and if they are equal,
// increments the program counter by 2.
void InstructionSetExecutor::skipInstructionIfReg(u8 rgtr_x, u8 rgtr_y) {
    if (this->gnrl_rgrs.read(rgtr_x) == this->gnrl_rgrs.read(rgtr_y))
        this->pgrm_cntr.increment();
}

// 6xkk - Sets Vx = kk. The interpreter puts the value kk into register Vx.
void InstructionSetExecutor::setRegTo(u8 rgtr_x, u8 value) {
    this->gnrl_rgrs.write(rgtr_x, value);
}

// 7xkk - Adds kk to Vx. (Carry flag is not changed) The interpreter
// adds the value kk to the value of register Vx, then stores the result
// back in Vx.
void InstructionSetExecutor::addValueToReg(u8 rgtr_x, u8 value) {
    u16 result = this->gnrl_rgrs.read(rgtr_x) + value;
    this->gnrl_rgrs.write(rgtr_x, result & 0xFF);
}

// 8xy0 - Sets Vx = Vy. Stores the value of register Vy in register Vx.
// Stores the value of Vy in Vx.
void InstructionSetExecutor::storeFromToReg(u8 rgtr_x, u8 rgtr_y) {
    this->gnrl_rgrs.write(
        rgtr_x,
        this->gnrl_rgrs.read(rgtr_y)
    ); 
}

//8xy1 - Set Vx = Vx OR Vy. Performs a bitwise OR on the values of Vx and Vy,
// then stores the result in Vx.
void InstructionSetExecutor::doOrOn(u8 rgtr_x, u8 rgtr_y) {
    this->gnrl_rgrs.write(
        rgtr_x,
        this->gnrl_rgrs.read(rgtr_x) | this->gnrl_rgrs.read(rgtr_y)
    );
}

// 8xy2 - Set Vx = Vx AND Vy. Performs a bitwise AND on the values of Vx and Vy,
// then stores the result in Vx.
void InstructionSetExecutor::doAndOn(u8 rgtr_x, u8 rgtr_y) {
    this->gnrl_rgrs.write(
        rgtr_x,
        this->gnrl_rgrs.read(rgtr_x) & this->gnrl_rgrs.read(rgtr_y)
    );
}

// 8xy3 - Set Vx = Vx XOR Vy. Performs a bitwise exclusive OR on the values of
// Vx and Vy, then stores the result in Vx.
void InstructionSetExecutor::doXorOn(u8 rgtr_x, u8 rgtr_y) {
    this->gnrl_rgrs.write(
        rgtr_x,
        this->gnrl_rgrs.read(rgtr_x) ^ this->gnrl_rgrs.read(rgtr_y)
    );
}

// 8xy4 - Set Vx = Vx + Vy, set VF = carry. If the sum of Vx and Vy
// exceeds 8 bits (i.e., is greater than 255), VF is set to 1, otherwise 0.
void InstructionSetExecutor::addAndCarry(u8 rgtr_x, u8 rgtr_y) {
    u16 result = this->gnrl_rgrs.read(rgtr_x) + this->gnrl_rgrs.read(rgtr_y);

    if (result > 255) this->gnrl_rgrs.setFlag(1);
    else this->gnrl_rgrs.setFlag(0);

    this->gnrl_rgrs.write(rgtr_x, result & 0xFF);
}

// 8xy5 - Set Vx = Vx - Vy, set VF = NOT borrow. If Vx > Vy, then VF is set to 1,
// otherwise 0. Then Vy is subtracted from Vx, and the results stored in Vx.
void InstructionSetExecutor::subAndBorrow(u8 rgtr_x, u8 rgtr_y) {
    if (this->gnrl_rgrs.read(rgtr_x) > this->gnrl_rgrs.read(rgtr_y))
        this->gnrl_rgrs.setFlag(1);
    else
        this->gnrl_rgrs.setFlag(0);

    u16 result = this->gnrl_rgrs.read(rgtr_x) - this->gnrl_rgrs.read(rgtr_y);
    this->gnrl_rgrs.write(rgtr_x, result & 0xFF);
}

// 8xy6 - Set Vx = Vx SHR 1. Stores the least significant bit of Vx in VF,
// then shifts Vx to the right by 1 effectively dividing it by 2.
void InstructionSetExecutor::carryAndLSB(u8 rgtr_x) {
    if ((this->gnrl_rgrs.read(rgtr_x) & 0b00000001) == 1)
        this->gnrl_rgrs.setFlag(1);
    else
        this->gnrl_rgrs.setFlag(0);

    this->gnrl_rgrs.write(
        rgtr_x,
        this->gnrl_rgrs.read(rgtr_x) >> 1
    );
}

// 8xy7 - Set Vx = Vy - Vx, set VF = NOT borrow.
// If Vy > Vx, then VF is set to 1,
// otherwise 0. Then Vx is subtracted from Vy, and the results stored in Vx.
void InstructionSetExecutor::subtractAndFlag(u8 rgtr_x, u8 rgtr_y) {
    if (this->gnrl_rgrs.read(rgtr_y) > this->gnrl_rgrs.read(rgtr_x))
        this->gnrl_rgrs.setFlag(1);
    else
        this->gnrl_rgrs.setFlag(0);

    u16 result = this->gnrl_rgrs.read(rgtr_y) - this->gnrl_rgrs.read(rgtr_x);
    this->gnrl_rgrs.write(rgtr_x, result & 0xFF);
}

// 8xyE - Set Vx = Vx SHL 1. If the MSB of Vx is 1, then VF is set to 1,
// otherwise 0. Then Vx is multiplied by 2.
void InstructionSetExecutor::carryAndMSB(u8 rgtr_x, u8 rgtr_y) {
    if ((this->gnrl_rgrs.read(rgtr_x) & 0b10000000) == 0b10000000)
        this->gnrl_rgrs.setFlag(1);
    else
        this->gnrl_rgrs.setFlag(0);

    this->gnrl_rgrs.write(
        rgtr_x,
        (this->gnrl_rgrs.read(rgtr_x) << 1) & 0xFF
    );
}

// 9xy0 - Skips the next instruction if Vx != Vy. The interpreter compares
// register Vx to register Vy, and if they are not equal,
// increments the program counter by 2.
void InstructionSetExecutor::skipInstructionIfNotReg(u8 rgtr_x, u8 rgtr_y) {
    if (this->gnrl_rgrs.read(rgtr_x) != this->gnrl_rgrs.read(rgtr_y))
        this->pgrm_cntr.increment();
}

// Annn - Sets I = nnn. The interpreter sets the index register to nnn.
void InstructionSetExecutor::setRegI(u16 addr) {
    this->indx_rgtr.set(addr);
}

// Bnnn - Jumps to address nnn + V0. The interpreter sets the program counter
// to nnn plus the value of V0.
void InstructionSetExecutor::jumpToAddrWithRegZero(u16 addr) {
    u16 jump_addr = addr + this->gnrl_rgrs.read(0);
    this->pgrm_cntr.set(jump_addr);
}

// Cxkk - Sets Vx = random byte AND kk. The interpreter generates a random byte,
// which is then ANDed with the value kk. The results are stored in Vx.
void InstructionSetExecutor::doAndWithRandom(u8 rgtr_x, u8 value) {
    std::random_device rand_dvc;
    std::uniform_int_distribution<u8> dist(0, 255);
    u8 num = dist(rand_dvc);
    u8 anded_value = num & value;
    this->gnrl_rgrs.write(rgtr_x, anded_value);
}

// Dxyn - Display n-byte sprite starting at memory location I at (Vx, Vy),
// set VF = collision. The interpreter reads n bytes from memory, starting at
// the address stored in I. These bytes are then displayed as sprites on screen
// at coordinates (Vx, Vy). Sprites are XORed onto the existing screen.
void InstructionSetExecutor::displaySprite(u8 rgtr_x, u8 rgtr_y, u8 n_byte) {
    u8 x_coord = this->gnrl_rgrs.read(rgtr_x);
    u8 y_coord = this->gnrl_rgrs.read(rgtr_y);
    std::vector<u8> sprite_data;

    this->mmry.read(
        this->indx_rgtr.get(), // Read from this memory address.
        sprite_data // Buffer to store read data.
    );

    this->dspy->renderSprite(sprite_data, x_coord, y_coord);

    if (this->dspy->hasPixelErased())
        this->gnrl_rgrs.setFlag(1);
    else
        this->gnrl_rgrs.setFlag(0);
}

//Ex9E
void InstructionSetExecutor::skipInstructionIfKey(u8 rgtr_x) {
    u8 key_value = this->rgtr_mngr->getRegisterValue(rgtr_x);
    if (this->cnsl->isKeyPressed(key_value))
        this->rgtr_mngr->program_counter += 2;
}

//ExA1
void InstructionSetExecutor::skipInstructionIfKeyNot(u8 rgtr_x) {
    u8 key_value = this->rgtr_mngr->getRegisterValue(rgtr_x);
    if (!this->cnsl->isKeyPressed(key_value))
        this->rgtr_mngr->program_counter += 2;
}

//Fx07
void InstructionSetExecutor::setDelayTimerValue(u8 rgtr_x) {
    this->rgtr_mngr->setRegisterValue(
        rgtr_x,
        this->rgtr_mngr->getDelayTimer()
    );
}

//Fx0A
void InstructionSetExecutor::waitForKey(u8 rgtr_x) {
    this->rgtr_mngr->setRegisterValue(
        rgtr_x,
        this->cnsl->getKey()
    );
}

//Fx15
void InstructionSetExecutor::setDelayTimer(u8 rgtr_x) {
    this->rgtr_mngr->setDelayTimer(
        this->rgtr_mngr->getRegisterValue(rgtr_x)
    );
}

//Fx18
void InstructionSetExecutor::setSoundTimer(u8 rgtr_x) {
    this->rgtr_mngr->setSoundTimer(
        this->rgtr_mngr->getRegisterValue(rgtr_x)
    );
}

//Fx1E
void InstructionSetExecutor::addStoreInRegI(u8 rgtr_x) {
    this->rgtr_mngr->setMemoryAddress(
        this->rgtr_mngr->getMemoryAddress() +
        this->rgtr_mngr->getRegisterValue(rgtr_x)
    );
}

//Fx29
void InstructionSetExecutor::setFontSpriteLocation(u8 hex_val) {
    this->rgtr_mngr->setMemoryAddress(
        this->mmory->getFontAddr(hex_val)
    );
}

//Fx33
void InstructionSetExecutor::storeBCDOf(u8 rgtr_x) {
    std::array<u8, 3> digits;
    u8 num = this->rgtr_mngr->getRegisterValue(rgtr_x);
    u8 i = 0;

    while (num != 0) {
        digits[i++] = num % 10;
        num /= 10;
    }

    u8 k = 2;

    for(u8 digit : digits) {
        this->mmory->writeByte(
            this->rgtr_mngr->getMemoryAddress() + k,
            digit
        );

        k -= 1;
    }
}

//Fx55
void InstructionSetExecutor::writeToMemory(u8 rgtr_x) {
    std::vector<u8> reg_data(rgtr_x + 1);

    for (u8 i = 0; i < rgtr_x + 1; i++)
        reg_data[i] = this->rgtr_mngr->getRegisterValue(i);

    this->mmory->write(
        this->rgtr_mngr->getMemoryAddress(),
        reg_data.data(),
        reg_data.size()
    );
}

//Fx65
void InstructionSetExecutor::readFromMemory(u8 rgtr_x) {
    u8* reg_data = new u8[rgtr_x + 1];

    this->mmory->read(
        this->rgtr_mngr->getMemoryAddress(),
        reg_data,
        rgtr_x + 1
    );

    for (u8 i = 0; i < rgtr_x + 1; i++)
        this->rgtr_mngr->setRegisterValue(i, reg_data[i]);

    delete[] reg_data;
    reg_data = nullptr;
    this->rgtr_mngr->setMemoryAddress(
        this->rgtr_mngr->getMemoryAddress() + rgtr_x + 1
    );
}

InstructionDecoder::InstructionDecoder(InstructionSetExecutor* inst_exec) {
    this->inst_exec = inst_exec;
    this->crnt_nble_pstn = 0;
}

InstructionDecoder::~InstructionDecoder() {
    delete this->inst_exec;
    this->inst_exec = nullptr;
}

u16 InstructionDecoder::assembleNibblesFrom(u8 from) {
    u16 addr = 0x000;
    u16 left_shift_mul = 2;

    for (u8 i = from; i < this->nibbles.size(); i++) {
        addr |= (this->nibbles[from] << (left_shift_mul * 4));
        left_shift_mul -= 1;
    }

    return addr;
}

void InstructionDecoder::skipNibble() {
    this->crnt_nble_pstn += 1;
}

void InstructionDecoder::breakIntoNibbles(u16 instruct_code) {
    this->instruction = instruct_code;
    u16 frst_nble_mask = 0xF000;
    u16 scnd_nble_mask = 0x0F00;
    u16 thrd_nble_mask = 0x00F0;
    u16 frth_nble_mask = 0x000F;

    this->nibbles[0] = (this->instruction & frst_nble_mask) >> 12;
    this->nibbles[1] = (this->instruction & scnd_nble_mask) >> 8;
    this->nibbles[2] = (this->instruction & thrd_nble_mask) >> 4;
    this->nibbles[3] = (this->instruction & frth_nble_mask);
}

void InstructionDecoder::decode() {
    switch (this->nibbles[this->crnt_nble_pstn]) {
        case 0x0:
        this->skipNibble();
        this->decodeZeroPrefix();
        break;

        case 0x1:
        this->inst_exec->jumpToAddr(
            this->assembleNibblesFrom(1)
        );
        break;

        case 0x2:
        this->inst_exec->callSubroutineAt(
            this->assembleNibblesFrom(1)
        );
        break;

        case 0x3:
        this->inst_exec->skipInstructionIf(
            this->nibbles[1],
            this->assembleNibblesFrom(2)
        );
        break;

        case 0x4:
        this->inst_exec->skipInstructionIfNot(
            this->nibbles[1],
            this->assembleNibblesFrom(2)
        );
        break;

        case 0x5:
        this->inst_exec->skipInstructionIfReg(
            this->nibbles[1],
            this->nibbles[2]
        );
        break;

        case 0x6:
        this->inst_exec->setRegTo(
            this->nibbles[1],
            this->assembleNibblesFrom(2)
        );
        break;

        case 0x7:
        this->inst_exec->addValueToReg(
            this->nibbles[1],
            this->assembleNibblesFrom(2)
        );
        break;

        case 0x8:
        this->skipNibble();
        this->decodeEightPrefix();
        break;

        case 0x9:
        this->inst_exec->skipInstructionIfNotReg(
            this->nibbles[1],
            this->nibbles[2]
        );
        break;

        case 0xA:
        this->inst_exec->setRegI(this->assembleNibblesFrom(1));
        break;

        case 0xB:
        this->inst_exec->jumpToAddrWithRegZero(
            this->assembleNibblesFrom(1)
        );
        break;

        case 0xC:
        this->inst_exec->doAndWithRandom(
            this->nibbles[1],
            this->assembleNibblesFrom(2)
        );
        break;

        case 0xD:
        this->inst_exec->displaySprite(
            this->nibbles[1],
            this->nibbles[2],
            this->nibbles[3]
        );
        break;

        case 0xE:
        this->skipNibble();
        this->decodeEPrefix();
        break;

        case 0xF:
        this->skipNibble();
        this->decodeFPrefix();
        break;

        default:
        throw InvalidOpcodeException(this->instruction);
        break;
    }
}

void InstructionDecoder::decodeZeroPrefix() {
    this->skipNibble();
    this->skipNibble();

    switch (this->nibbles[this->crnt_nble_pstn]) {
        case 0x0:
            this->inst_exec->clearDisplay();
            break;

        case 0xE:
            this->inst_exec->returnFromSubroutine();
            break;

        default:
            u16 addr = this->assembleNibblesFrom(1);
            if (addr > 0x1FF && addr < 0xFFF) return;
            else throw InvalidOpcodeException(this->instruction);
            break;
    }
}

void InstructionDecoder::decodeEightPrefix() {
    this->skipNibble();
    this->skipNibble();

    switch (this->nibbles[this->crnt_nble_pstn]) {
        case 0x0:
            this->inst_exec->storeFromToReg(
                this->nibbles[1],
                this->nibbles[2]
            );
            break;

        case 0x1:
            this->inst_exec->doOrOn(
                this->nibbles[1],
                this->nibbles[2]
            );
            break;

        case 0x2:
            this->inst_exec->doAndOn(
                this->nibbles[1],
                this->nibbles[2]
            );
            break;

        case 0x3:
            this->inst_exec->doXorOn(
                this->nibbles[1],
                this->nibbles[2]
            );
            break;

        case 0x4:
            this->inst_exec->addAndCarry(
                this->nibbles[1],
                this->nibbles[2]
            );
            break;

        case 0x5:
            this->inst_exec->subAndBorrow(
                this->nibbles[1],
                this->nibbles[2]
            );
            break;

        case 0x6:
            this->inst_exec->carryAndLSB(this->nibbles[1]);
            break;

        case 0x7:
            this->inst_exec->subtractAndFlag(
                this->nibbles[1],
                this->nibbles[2]
            );
            break;

        case 0xE:
            this->inst_exec->carryAndMSB(
                this->nibbles[1],
                this->nibbles[2]
            );
            break;

        default:
            throw InvalidOpcodeException(this->instruction);
            break;
    }
}

void InstructionDecoder::decodeEPrefix() {
    this->skipNibble();

    if (this->nibbles[this->crnt_nble_pstn] == 0x9)
        this->inst_exec->skipInstructionIfKey(this->nibbles[1]);
    else if (this->nibbles[this->crnt_nble_pstn] == 0xA)
        this->inst_exec->skipInstructionIfKeyNot(this->nibbles[1]);
    else throw InvalidOpcodeException(this->instruction);
}

void InstructionDecoder::decodeFPrefix() {
    this->skipNibble();

    switch (this->nibbles[this->crnt_nble_pstn]) {
        case 0x0:
            this->skipNibble();
            this->decodeFZero();
            break;

        case 0x1:
            this->skipNibble();
            this->decodeFOne();
            break;

        case 0x2:
            this->inst_exec->setFontSpriteLocation(this->nibbles[1]);
            break;

        case 0x3:
            this->inst_exec->storeBCDOf(this->nibbles[1]);
            break;

        case 0x5:
            this->inst_exec->writeToMemory(this->nibbles[1]);
            break;

        case 0x6:
            this->inst_exec->readFromMemory(this->nibbles[1]);
            break;

        default:
            throw InvalidOpcodeException(this->instruction);
            break;
    }
}

void InstructionDecoder::decodeFZero() {
    switch (this->nibbles[this->crnt_nble_pstn]) {
        case 0x7:
            this->inst_exec->setDelayTimerValue(this->nibbles[1]);
            break;

        case 0xA:
            this->inst_exec->waitForKey(this->nibbles[1]);
            break;

        default:
            throw InvalidOpcodeException(this->instruction);
            break;
    }
}

void InstructionDecoder::decodeFOne() {
    switch (this->nibbles[this->crnt_nble_pstn]) {
        case 0x5:
            this->inst_exec->setDelayTimer(this->nibbles[1]);
            break;

        case 0x8:
            this->inst_exec->setSoundTimer(this->nibbles[1]);
            break;

        case 0xE:
            this->inst_exec->addStoreInRegI(this->nibbles[1]);
            break;

        default:
            throw InvalidOpcodeException(this->instruction);
            break;
    }
}

//---//
