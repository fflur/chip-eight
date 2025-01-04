#include <Interpreter.hpp>

//---MemoryException---//

MemoryException::MemoryException(u16 addr) {
    this->message =
        "Error: Trying to write at " +
        std::to_string(addr) +
        " which belongs to the system!";
}

const char* MemoryException::what() const noexcept {
    return this->message.c_str();
}

//---RegistersManager---//

RegistersManager::RegistersManager() {
    this->register_delay_timer, this->register_sound_timer = NULL;
    this->register_i, this->program_counter = NULL;
    this->stack_pointer = this->mem_addresses[0];
}

void RegistersManager::checkRegisterAccess(u8 reg_x) {
    if ((reg_x > 14) || (reg_x < 0)) throw MemoryException(reg_x);
}

void RegistersManager::setMemoryAddress(u16 addr) {
    this->register_i = addr;
}

u16 RegistersManager::getMemoryAddress() const {
    return this->register_i;
}

void RegistersManager::setFlag(u8 f) { this->registers[15] = f; }

u8 RegistersManager::getFlag() const { return this->registers[15]; }

bool RegistersManager::isEqual(u8 reg_no, u8 value) const {
    return this->registers[reg_no] == value;
}

bool RegistersManager::compareRegister(u8 x, u8 y) const {
    return this->registers[x] == this->registers[y];
}

void RegistersManager::setRegisterValue(u8 reg_x, u8 value) {
    this->checkRegisterAccess(reg_x);
    this->registers[reg_x] = value;
}

u8 RegistersManager::getRegisterValue(u8 reg_x) const {
    return this->registers[reg_x];
}

void RegistersManager::setDelayTimer(u8 value) {
    this->register_delay_timer = value;
}

u8 RegistersManager::getDelayTimer() const {
    return this->register_delay_timer;
}

void RegistersManager::setSoundTimer(u8 value) {
    this->register_sound_timer = value;
}

u8 RegistersManager::getSoundTimer() const {
    this->register_sound_timer;
}

//---Memory---//

Memory::Memory() {
    u8 fonts[] = {
        0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
        0x20, 0x60, 0x20, 0x20, 0x70, // 1
        0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
        0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
        0x90, 0x90, 0xF0, 0x10, 0x10, // 4
        0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
        0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
        0xF0, 0x10, 0x20, 0x40, 0x40, // 7
        0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
        0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
        0xF0, 0x90, 0xF0, 0x90, 0x90, // A
        0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
        0xF0, 0x80, 0x80, 0x80, 0xF0, // C
        0xE0, 0x90, 0x90, 0x90, 0xE0, // D
        0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
        0xF0, 0x80, 0xF0, 0x80, 0x80, // F
    };

    u8 font_size = sizeof(fonts)/sizeof(u8);
    for (u8 i = 0; i < font_size; i++) this->mem[i] = fonts[i];
}

void Memory::checkMemoryAccess(u16 addr) const {
    if (addr <= 0x01FF || addr >= 0x0FFF)
        throw MemoryException(addr);
}

void Memory::read(u16 addr, u8* bytes_array, u8 arr_len) const {
    for (u8 i = 0; i < arr_len; i++)
        *(bytes_array + i) = this->mem[addr + i];
}

void Memory::write(u16 addr, u8* bytes, u8 arr_len) {
    for (u8 i = 0; i < arr_len; i++) {
        this->checkMemoryAccess(addr + i);
        this->mem[addr + i] = *(bytes + i);
    }
}

u16 getFontAddr(u8 hex_font_val) {
    return 0x000 + (hex_font_val * 5);
}

//------//
