#include <memory>
#include <vector>

#include "Debugger.h"
#include "RomLoader.h"
#include "Window.h"

#include "Chip8.h"

static const int ROM_OFFSET = 512;
static const int MEMORY_SIZE = 4096;

void Chip8::run(const std::string &fileName) {
    std::vector<uint8_t> memory(MEMORY_SIZE);

    const auto window = std::make_unique<Window>("CHIP-8", 640, 480);
    const auto romLoader = std::make_unique<RomLoader>(fileName);
    const auto debugger = std::make_unique<Debugger>();
    const auto opcodes = std::make_unique<Opcodes>();

    const std::vector<uint8_t> &rom = romLoader->load();
    memory.insert(memory.begin() + ROM_OFFSET, rom.begin(), rom.end());

    debugger->hexPrint(rom);
    debugger->printOpcodes(opcodes, rom);

    window->show();

    while (!window->isClosed()) {
        window->pollEvents();
    }
}
