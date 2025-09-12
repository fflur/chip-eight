#include <interpreter.hpp>

//----- RegistersManager Implementation ---//

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

//---End of RegistersManager---//