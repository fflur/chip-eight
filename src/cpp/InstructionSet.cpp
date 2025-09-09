#include <InstructionSet.hpp>

//---InstructionSetExecutor---//

InstructionSetExecutor::InstructionSetExecutor(
    RegistersManager* rgtr_mngr,
    Memory* mmory,
    Display* dsp,
    Console* cnsl
) {
    this->dsp = dsp;
    this->cnsl = cnsl;
    this->rgtr_mngr = rgtr_mngr;
    this->mmory = mmory;
}

InstructionSetExecutor::~InstructionSetExecutor() {
    delete this->dsp;
    delete this->cnsl;
    delete this->rgtr_mngr;
    delete this->mmory;
    this->dsp = nullptr;
    this->cnsl = nullptr;
    this->rgtr_mngr = nullptr;
    this->mmory = nullptr;
}

//00E0
void InstructionSetExecutor::clearDisplay() {
    this->dsp->clearScreen();
}

//00EE
void InstructionSetExecutor::returnFromSubroutine() {
    this->rgtr_mngr->program_counter = this->rgtr_mngr->mem_addresses[
        this->rgtr_mngr->stack_pointer
    ];

    this->rgtr_mngr->stack_pointer -= 1;
}

//1nnn
void InstructionSetExecutor::jumpToAddr(u16 addr) {
    this->rgtr_mngr->program_counter = addr;
}

//2nnn
void InstructionSetExecutor::callSubroutineAt(u16 addr) {
    this->rgtr_mngr->stack_pointer += 1;
    this->rgtr_mngr->mem_addresses[this->rgtr_mngr->stack_pointer] =
        this->rgtr_mngr->program_counter;
    this->rgtr_mngr->program_counter = addr;
}

//3xkk
void InstructionSetExecutor::skipInstructionIf(
    u8 reg_no,
    u8 value
) {
    if (this->rgtr_mngr->getRegisterValue(reg_no) == value)
        this->rgtr_mngr->program_counter += 2;
}

//4xkk
void InstructionSetExecutor::skipInstructionIfNot(
    u8 reg_no,
    u8 value
) {
    if (this->rgtr_mngr->getRegisterValue(reg_no) != value)
        this->rgtr_mngr->program_counter += 2;
}

//5xy0
void InstructionSetExecutor::skipInstructionIfReg(
    u8 reg_x,
    u8 reg_y
) {
    if (this->rgtr_mngr->getRegisterValue(reg_x) ==
        this->rgtr_mngr->getRegisterValue(reg_y)
    ) this->rgtr_mngr->program_counter += 2;
}

//6xkk
void InstructionSetExecutor::setRegTo(
    u8 reg_no,
    u8 value
) { this->rgtr_mngr->setRegisterValue(reg_no, value); }

//7xkk
void InstructionSetExecutor::addValueToReg(
    u8 reg_no,
    u8 value
) {
    this->rgtr_mngr->setRegisterValue(
        reg_no, 
        this->rgtr_mngr->getRegisterValue(reg_no) + value
    ); 
}

//8xy0
void InstructionSetExecutor::storeFromToReg(
    u8 reg_x,
    u8 reg_y
) {
    this->rgtr_mngr->setRegisterValue(
        reg_x,
        this->rgtr_mngr->getRegisterValue(reg_y)
    );
}

//8xy1
void InstructionSetExecutor::doOrOn(
    u8 reg_x,
    u8 reg_y
) {
    u8 or_operation_result =
        this->rgtr_mngr->getRegisterValue(reg_x) |
        this->rgtr_mngr->getRegisterValue(reg_y)
    ;

    this->rgtr_mngr->setRegisterValue(
        reg_x,
        or_operation_result
    );
}

//8xy2
void InstructionSetExecutor::doAndOn(
    u8 reg_x,
    u8 reg_y
) {
    u8 and_operation_result =
        this->rgtr_mngr->getRegisterValue(reg_x) &
        this->rgtr_mngr->getRegisterValue(reg_y)
    ;

    this->rgtr_mngr->setRegisterValue(
        reg_x,
        and_operation_result
    );
}

//8xy3
void InstructionSetExecutor::doXorOn(
    u8 reg_x,
    u8 reg_y
) {
    u8 xor_operation_result =
        this->rgtr_mngr->getRegisterValue(reg_x) ^
        this->rgtr_mngr->getRegisterValue(reg_y)
    ;

    this->rgtr_mngr->setRegisterValue(
        reg_x,
        xor_operation_result
    );
}

//8xy4
void InstructionSetExecutor::addAndCarry(
    u8 reg_x,
    u8 reg_y
) {
    u16 result =
        this->rgtr_mngr->getRegisterValue(reg_x) +
        this->rgtr_mngr->getRegisterValue(reg_y)
    ;

    if (result > 255) {
        this->rgtr_mngr->setFlag(1);
        this->rgtr_mngr->setRegisterValue(reg_x, result & 0b11111111);
        return;
    } else this->rgtr_mngr->setFlag(0);

    this->rgtr_mngr->setRegisterValue(reg_x, result);
}

//8xy5
void InstructionSetExecutor::subAndBorrow(
    u8 reg_x,
    u8 reg_y
) {
    if (
        this->rgtr_mngr->getRegisterValue(reg_x) >
        this->rgtr_mngr->getRegisterValue(reg_y)
    ) this->rgtr_mngr->setFlag(1);
    else this->rgtr_mngr->setFlag(0);

    this->rgtr_mngr->setRegisterValue(reg_x,
        this->rgtr_mngr->getRegisterValue(reg_x) -
        this->rgtr_mngr->getRegisterValue(reg_y)
    );
}

//8xy6
void InstructionSetExecutor::carryAndLSB(u8 reg_no) {
    if (this->rgtr_mngr->getRegisterValue(reg_no) & 0b1 == 1)
        this->rgtr_mngr->setFlag(1);
    else this->rgtr_mngr->setFlag(0);

    this->rgtr_mngr->setRegisterValue(
        reg_no,
        (u8) this->rgtr_mngr->getRegisterValue(reg_no) / 2
    );
}

//8xy7
void InstructionSetExecutor::subtractAndFlag(
    u8 reg_x,
    u8 reg_y
) {
    if (
        this->rgtr_mngr->getRegisterValue(reg_x) >
        this->rgtr_mngr->getRegisterValue(reg_y)
    ) this->rgtr_mngr->setFlag(1);
    else this->rgtr_mngr->setFlag(0);

    this->rgtr_mngr->setRegisterValue(
        reg_x,
        this->rgtr_mngr->getRegisterValue(reg_y) -
        this->rgtr_mngr->getRegisterValue(reg_x)
    );
}

//8xyE
void InstructionSetExecutor::carryAndMSB(
    u8 reg_x,
    u8 reg_y
) {
    if (((this->rgtr_mngr->getRegisterValue(reg_x) & 0b10000000) >> 7) == 1)
        this->rgtr_mngr->setFlag(1);
    else this->rgtr_mngr->setFlag(0);

    this->rgtr_mngr->setRegisterValue(
        reg_x,
        this->rgtr_mngr->getRegisterValue(reg_x) * 2
    );
}

//9xy0
void InstructionSetExecutor::skipInstructionIfNotReg(
        u8 reg_x,
        u8 reg_y
) {
    if (this->rgtr_mngr->getRegisterValue(reg_x) !=
        this->rgtr_mngr->getRegisterValue(reg_y)
    ) this->rgtr_mngr->program_counter += 2;
}

//Annn
void InstructionSetExecutor::setRegI(u16 addr) {
    this->rgtr_mngr->setMemoryAddress(addr);
}

//Bnnn
void InstructionSetExecutor::jumpToAddrWithRegZero(u16 addr) {
    this->rgtr_mngr->program_counter =
        addr + this->rgtr_mngr->getRegisterValue(0);
}

//Cxkk
void InstructionSetExecutor::doAndWithRandom(u8 reg_no, u8 value) {
    std::random_device rand_dvc;
    std::uniform_int_distribution<u8> dist(0, 255);
    u8 num = dist(rand_dvc);
    u8 anded_value = num & value;
    this->rgtr_mngr->setRegisterValue(reg_no, anded_value);
}

//Dxyn
void InstructionSetExecutor::displaySprite(u8 reg_x, u8 reg_y, u8 n_byte) {
    u8* sprite_array = new u8[n_byte];

    this->mmory->read(
        this->rgtr_mngr->getMemoryAddress(),
        sprite_array,
        n_byte
    );

    this->dsp->renderSprite(
        sprite_array,
        n_byte,
        this->rgtr_mngr->getRegisterValue(reg_x),
        this->rgtr_mngr->getRegisterValue(reg_y)
    );

    delete[] sprite_array;
    sprite_array = nullptr;
}

//Ex9E
void InstructionSetExecutor::skipInstructionIfKey(u8 reg_no) {
    u8 key_value = this->rgtr_mngr->getRegisterValue(reg_no);
    if (this->cnsl->isKeyPressed(key_value))
        this->rgtr_mngr->program_counter += 2;
}

//ExA1
void InstructionSetExecutor::skipInstructionIfKeyNot(u8 reg_no) {
    u8 key_value = this->rgtr_mngr->getRegisterValue(reg_no);
    if (!this->cnsl->isKeyPressed(key_value))
        this->rgtr_mngr->program_counter += 2;
}

//Fx07
void InstructionSetExecutor::setDelayTimerValue(u8 reg_no) {
    this->rgtr_mngr->setRegisterValue(
        reg_no,
        this->rgtr_mngr->getDelayTimer()
    );
}

//Fx0A
void InstructionSetExecutor::waitForKey(u8 reg_no) {
    this->rgtr_mngr->setRegisterValue(
        reg_no,
        this->cnsl->getKey()
    );
}

//Fx15
void InstructionSetExecutor::setDelayTimer(u8 reg_no) {
    this->rgtr_mngr->setDelayTimer(
        this->rgtr_mngr->getRegisterValue(reg_no)
    );
}

//Fx18
void InstructionSetExecutor::setSoundTimer(u8 reg_no) {
    this->rgtr_mngr->setSoundTimer(
        this->rgtr_mngr->getRegisterValue(reg_no)
    );
}

//Fx1E
void InstructionSetExecutor::addStoreInRegI(u8 reg_x) {
    this->rgtr_mngr->setMemoryAddress(
        this->rgtr_mngr->getMemoryAddress() +
        this->rgtr_mngr->getRegisterValue(reg_x)
    );
}

//Fx29
void InstructionSetExecutor::setFontSpriteLocation(u8 hex_val) {
    this->rgtr_mngr->setMemoryAddress(
        this->mmory->getFontAddr(hex_val)
    );
}

//Fx33
void InstructionSetExecutor::storeBCDOf(u8 reg_x) {
    std::array<u8, 3> digits;
    u8 num = this->rgtr_mngr->getRegisterValue(reg_x);
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
void InstructionSetExecutor::writeToMemory(u8 reg_x) {
    std::vector<u8> reg_data(reg_x + 1);

    for (u8 i = 0; i < reg_x + 1; i++)
        reg_data[i] = this->rgtr_mngr->getRegisterValue(i);

    this->mmory->write(
        this->rgtr_mngr->getMemoryAddress(),
        reg_data.data(),
        reg_data.size()
    );
}

//Fx65
void InstructionSetExecutor::readFromMemory(u8 reg_x) {
    u8* reg_data = new u8[reg_x + 1];

    this->mmory->read(
        this->rgtr_mngr->getMemoryAddress(),
        reg_data,
        reg_x + 1
    );

    for (u8 i = 0; i < reg_x + 1; i++)
        this->rgtr_mngr->setRegisterValue(i, reg_data[i]);

    delete[] reg_data;
    reg_data = nullptr;
    this->rgtr_mngr->setMemoryAddress(
        this->rgtr_mngr->getMemoryAddress() + reg_x + 1
    );
}

//---InstructionDecoder---//
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
