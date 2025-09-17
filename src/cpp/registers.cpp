#include <registers.hpp>
#include <cstdint>

using u8 = std::uint8_t;
using u16 = std::uint16_t;

bool GeneralRegisters::isAccessLegal(u8 rgtr_x) const {
    if (rgtr_x <= 14) return true;
    return false;
}

u8 GeneralRegisters::read(u8 rgtr_x) const {
    if (!this->isAccessLegal(rgtr_x)) throw MemoryException(rgtr_x);
    return this->registers[rgtr_x];
}

void GeneralRegisters::write(u8 rgtr_x, u8 value) {
    if (!this->isAccessLegal(rgtr_x)) throw MemoryException(rgtr_x);
    this->registers[rgtr_x] = value;
}

u8 GeneralRegisters::getFlag() const { return this->registers[15]; }
void GeneralRegisters::setFlag(u8 value) { this->registers[15] = value; }
void GeneralRegisters::reset() { this->registers.fill(0); }

void IndexRegister::set(u16 addr) { this->register_i = addr; }
u16 IndexRegister::get() const { return this->register_i; }
void IndexRegister::reset() { this->register_i = 0; }

void ProgramCounter::set(u16 addr) { this->program_counter = addr; }
u16 ProgramCounter::get() const { return this->program_counter; }
void ProgramCounter::increment() { this->program_counter += 2; }
void ProgramCounter::reset() { this->program_counter = 0; }

void Timer::set(u8 value) { this->timer_value = value; }
u8 Timer::get() const { return this->timer_value; }

void Timer::decrement() {
    if (this->timer_value > 0) this->timer_value -= 1;
}

void Timer::reset() { this->timer_value = 0; }