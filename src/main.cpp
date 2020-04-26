#include <iostream>
#include <memory>
#include <vector>
#include "Window.h"
#include "RomLoader.h"
#include "Debugger.h"

static const int ROM_OFFSET = 512;
static const int MEMORY_SIZE = 4096;

int main(int argc, char **argv) {
    std::cout << "Hello, CHIP-8!" << std::endl;

    if (argc != 2) {
        std::cerr << "Usage: chip8 <rom.ch8>" << std::endl;
        return EXIT_FAILURE;
    }

    std::vector<uint8_t> memory(MEMORY_SIZE);
    std::string fileName = argv[1];

    const auto window = std::make_unique<Window>("CHIP-8", 640, 480);
    const auto romLoader = std::make_unique<RomLoader>(fileName);
    const auto debugger = std::make_unique<Debugger>();

    const std::vector<uint8_t> &rom = romLoader->load();
    memory.insert(memory.begin() + ROM_OFFSET, rom.begin(), rom.end());

    debugger->hexPrint(rom);

    window->show();

    while (!window->isClosed()) {
        window->pollEvents();
    }

    std::cout << "Good bye, CHIP-8!" << std::endl;

    return EXIT_SUCCESS;
}
