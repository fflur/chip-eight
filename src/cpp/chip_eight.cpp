#include <chip_eight.hpp>

ROMFileChecker::ROMFileChecker(std::string file_path) {
    this->file_path = file_path;
}

bool ROMFileChecker::isExtensionCorrect() {
    usize dot_pos = this->file_path.find_last_of('.');
    if (dot_pos == std::string::npos) return false;
    std::string extension = this->file_path.substr(dot_pos);
    return (extension == ".ch8" || extension == ".c8");
}

bool ROMFileChecker::isOfValidSize() {
    std::ifstream file(this->file_path, std::ios::binary | std::ios::ate);
    if (!file) return false;
    std::streamsize size = file.tellg();
    return (size >= MIN_ROM_SIZE && size <= MAX_ROM_SIZE);
}

bool ROMFileChecker::isValidROM() {
    return this->isExtensionCorrect() && this->isOfValidSize();
}