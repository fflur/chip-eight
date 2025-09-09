#ifndef CHIP_EIGHT_EXCEPTIONS
#define CHIP_EIGHT_EXCEPTIONS

#include <exception>
#include <iostream>
#include <ChipTypes.hpp>

class ChipException : public std::exception {
    private:
    std::string message;

    public:
    ChipException();
    ~ChipException();
    const char* what() const noexcept override;
};

class MemoryException : public ChipException {
    private:
    std::string message;

    public:
    MemoryException(u16);
    ~MemoryException();
    const char* what() const noexcept override;
};

class InvalidOpcodeException : public ChipException {
    private:
    std::string message;

    public:
    InvalidOpcodeException(u16);
    ~InvalidOpcodeException();
    const char* what() const noexcept override;
};

class InitializationException : public ChipException {
    private:
    std::string message;

    public:
    InitializationException(std::string);
    ~InitializationException();
    const char* what() const noexcept override;
};

class ROMLoadingException : public ChipException {
    private:
    std::string message;

    public:
    ROMLoadingException(std::string);
    ~ROMLoadingException();
    const char* what() const noexcept override;
};

#endif // !CHIP_EIGHT_EXCEPTIONS
