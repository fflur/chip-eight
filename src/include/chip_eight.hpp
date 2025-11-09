#pragma once
#include <string>
#include <array>
#include <fstream>
#include <chip_eight_constants.hpp>

class ROMFileChecker {
    private:
    std::string file_path;

    public:
    ROMFileChecker(std::string);
    bool isValidROM();
    bool isExtensionCorrect();
    bool isOfValidSize();
};