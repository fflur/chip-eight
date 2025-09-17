#pragma once
#include <exception>
#include <string>
#include <chip_types.hpp>

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

class OverflowException : public ChipException {
    private:
    std::string message;

    public:
    OverflowException();
    ~OverflowException();
    const char* what() const noexcept override;
};

class UnderflowException : public ChipException {
    private:
    std::string message;

    public:
    UnderflowException();
    ~UnderflowException();
    const char* what() const noexcept override;
};