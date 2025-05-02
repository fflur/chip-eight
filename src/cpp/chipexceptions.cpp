#include <ChipExceptions.hpp>

//---ChipException---//



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

//---InitializationException---//

InitializationException::InitializationException(std::string msge) {
    this->message = msge;
}

const char* InitializationException::what() const noexcept {
    return this->message.c_str();
}

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
