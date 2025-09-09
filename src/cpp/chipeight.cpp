#include <chipeight.hpp>

GameLoader::GameLoader(std::string file_path) {
    this->file_path = file_path;
}

GameLoader::~GameLoader() {}

bool GameLoader::validate() {
    std::ifstream file(this->file_path, std::ios::binary | std::ios::ate);
    if (!file) return false;
    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);
    if (size < MIN_ROM_SIZE || size > MAX_ROM_SIZE) return false;
    char header[4];
    file.read(header, 4);
    if (header[0] == '\xEF' && header[1] == '\xBB' && header[2] == '\xBF') return false;
    return true;
}

std::array<u8, MAX_ROM_SIZE> GameLoader::load() {
    // Open the file in binary input mode.
    std::ifstream bnry_file(this->file_path, std::ios::in | std::ios::binary);
    // Create fixed-size array.
    std::array<u8, MAX_ROM_SIZE> read_rom;
    // Read the entire file into the array. Raw binary data is read.
    bnry_file.read(reinterpret_cast<char*>(read_rom.data()), MAX_ROM_SIZE);
    // Return the read rom.
    return read_rom;
}

//---CHIP8---//

CHIP8::CHIP8(std::string file_path) {
    // Loading CHIP-8 ROM.
    GameLoader game_lder(file_path);
    if(!game_lder.validate()) throw ROMLoadingException(file_path);

    // Component initialization.
    this->regr_mngr = new RegistersManager();
    this->mory = new Memory();
    this->dspy = new MonochromeDisplay("CHIP 8 Emulator");
    this->cnsl = new HexConsole();

    this->inst_exec = new InstructionSetExecutor(
        regr_mngr,
        mory,
        dspy,
        cnsl
    );

    this->inst_dcdr = new InstructionDecoder(inst_exec);

    // Setting up components.
    this->mory->loadGame(game_lder.load());
    this->regr_mngr->program_counter = ROM_STARTING_POS;
}

void CHIP8::cycle() {
    this->inst_dcdr->breakIntoNibbles(
        this->mory->fetchInstruction(this->regr_mngr->program_counter)
    );

    this->inst_dcdr->decode();
}

CHIP8::~CHIP8() {
    delete this->inst_dcdr;
    delete this->inst_exec;
    delete this->dspy;
    delete this->cnsl;
    delete this->regr_mngr;
    delete this->mory;

    this->regr_mngr = nullptr;
    this->mory = nullptr;
    this->dspy = nullptr;
    this->cnsl = nullptr;
    this->inst_exec = nullptr;
    this->inst_dcdr = nullptr;
}

//---//