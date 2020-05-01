#include <iostream>
#include <memory>
#include <thread>
#include <vector>

#include "Debugger.h"
#include "RomLoader.h"
#include "Window.h"

#include "Chip8.h"

Chip8::Chip8() {
    opcodes = std::make_shared<Opcodes>(this);
    std::cout << "Chip8 in" << std::endl;
}

Chip8::~Chip8() {
    std::cout << "Chip8 out" << std::endl;
}

void Chip8::run(const std::string &fileName) {
    const auto window = std::make_unique<Window>("CHIP-8", 640, 480);
    const auto romLoader = std::make_unique<RomLoader>(fileName);
    const auto debugger = std::make_unique<Debugger>();

    const std::vector<uint8_t> &rom = romLoader->load();
    memory.insert(memory.begin() + ROM_OFFSET, rom.begin(), rom.end());

    debugger->hexPrint(memory, ROM_OFFSET, ROM_OFFSET + rom.size());
//    debugger->printOpcodes(opcodes, rom);

    while (PC < MEMORY_SIZE) {
        tick();
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }

    window->show();

    while (!window->isClosed()) {
        window->pollEvents();
    }
}

void Chip8::tick() {
    const uint16_t opcode = fetch();
    const Opcodes::OpcodeEntry &opcodeEntry = opcodes->findOpcode(opcode);

    printf("%04X - ", PC);
    PC += 2;

    // Execute instruction
    (opcodes.get()->*opcodeEntry.handler)(opcode);
}

uint16_t Chip8::fetch() {
    return (memory.at(PC) << 8) | memory.at(PC + 1);;
}
