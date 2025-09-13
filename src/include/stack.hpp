#pragma once
#include <array>
#include <chip_types.hpp>
#include <chip_exceptions.hpp>

// The stack is an array of 16 16-bit values,
// used to store the address that the interpreter shoud return to
// when finished with a subroutine.
// Chip-8 allows for up to 16 levels of nested subroutines.
class Stack {
    private:
    // Array to hold up to 16 memory addresses (16-bit).
    std::array<u16, 16> memory_addresses;
    // Stack pointer to track the current top of the stack.
    // Just stores the index of the next free slot in the stack.
    // When the stack is empty, the stack pointer is 0.
    u8 stack_pointer;
    // Check for stack overflow (more than 16 items).
    void checkStackOverflow() const;
    // Check for stack underflow (popping from an empty stack).
    void checkStackUnderflow() const;

    public:
    // Initializes the stack pointer to 0 and fills the stack with 0s.
    Stack();
    // Destructor with the default implementation.
    ~Stack();
    // Push a memory address onto the stack.
    void push(u16);
    // Pop a memory address from the stack.
    u16 pop();
    // Reset the stack to its initial state.
    void reset();
};