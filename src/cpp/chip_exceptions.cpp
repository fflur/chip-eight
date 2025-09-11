#include <chip_exceptions.hpp>

//---ChipException---//
ChipException::ChipException() {
    this->message = "Device Crashed!!!";
}

const char* ChipException::what() const noexcept {
    return this->message.c_str();
}

ChipException::~ChipException() = default;

//---MemoryException---//

MemoryException::MemoryException(u16 addr) {
    this->message =
        "Error: Trying to write at " +
        std::to_string(addr) +
        " which belongs to the system!"
    ;
}

const char* MemoryException::what() const noexcept {
    return this->message.c_str();
}

MemoryException::~MemoryException() = default;

//---InitializationException---//

InitializationException::InitializationException(std::string comp_name) {
    this->message = "Failed to initialize " + comp_name + ".";
}

const char* InitializationException::what() const noexcept {
    return this->message.c_str();
}

InitializationException::~InitializationException() = default;

//---InvalidOpcodeException---//

InvalidOpcodeException::InvalidOpcodeException(u16 opcode) {
    this->message =
        "Error: " +
        std::to_string(opcode) +
        " is an unrecognized opcode."
    ;
}

const char* InvalidOpcodeException::what() const noexcept {
    return this->message.c_str();
}

InvalidOpcodeException::~InvalidOpcodeException() = default;

//---ROMLoadingException---//

ROMLoadingException::ROMLoadingException(std::string comp_name) {
    this->message = "Failed to load " + comp_name + " ROM file.";
}

const char* ROMLoadingException::what() const noexcept {
    return this->message.c_str();
}

ROMLoadingException::~ROMLoadingException() = default;

//---//
