#include <stack.hpp>

Stack::Stack() {
    this->memory_addresses.fill(0);
    this->stack_pointer = 0;
}

Stack::~Stack() = default;

void Stack::checkStackOverflow() const {
    if (this->stack_pointer >= 15) throw OverflowException();
}

void Stack::checkStackUnderflow() const {
    if (this->stack_pointer == 0) throw UnderflowException();
}

void Stack::push(u16 addr) {
    this->checkStackOverflow();
    this->memory_addresses[this->stack_pointer] = addr;
    this->stack_pointer++;
}

u16 Stack::pop() {
    this->checkStackUnderflow();
    this->stack_pointer--;
    return this->memory_addresses[this->stack_pointer];
}

void Stack::reset() {
    this->stack_pointer = 0;
    this->memory_addresses.fill(0);
}