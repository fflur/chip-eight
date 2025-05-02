#ifndef CHIP_EIGHT_EXCEPTIONS
#define CHIP_EIGHT_EXCEPTIONS

#include <exception>
#include <ChipTypes.hpp>

class ChipException : public std::exception {
    private:
        std::string message;

    public:
        const char* what() const noexcept override;
};

class MemoryException : public ChipException {
    private:
        std::string message;

    public:
        MemoryException(u16);
        const char* what() const noexcept override;
};

class InvalidOpcodeException : public ChipException {
    private:
        std::string message;

    public:
        InvalidOpcodeException(u16);
        const char* what() const noexcept override;
};

class InitializationException : public ChipException {
    private:
        std::string message;

    public:
        InitializationException(std::string);
        const char* what() const noexcept override;
};

#endif // !CHIP_EIGHT_EXCEPTIONS
