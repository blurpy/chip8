#include <iostream>
#include <memory>
#include <thread>
#include <vector>

#include "Debugger.h"
#include "RomLoader.h"

#include "Chip8.h"

Chip8::Chip8() {
    opcodes = std::make_shared<Opcodes>(this);
    keyboard = std::make_shared<Keyboard>();
    window = std::make_unique<Window>("CHIP-8", 10, keyboard);
    timer = std::make_unique<Timer>();
    sound = std::make_unique<Sound>();

    std::cout << "Chip8 in" << std::endl;
}

Chip8::~Chip8() {
    std::cout << "Chip8 out" << std::endl;
}

void Chip8::run(const std::string &fileName) {
    const auto romLoader = std::make_unique<RomLoader>(fileName);
    const auto debugger = std::make_unique<Debugger>();

    const std::vector<uint8_t> &rom = romLoader->load();

    if (rom.empty()) {
        return; // Quit if unable to load the rom
    }

    memory.insert(memory.begin() + FONT_OFFSET, font.begin(), font.end());
    memory.insert(memory.begin() + ROM_OFFSET, rom.begin(), rom.end());

    debugger->hexPrint("Font", memory, FONT_OFFSET, FONT_OFFSET + font.size());
    debugger->hexPrint("ROM", memory, ROM_OFFSET, ROM_OFFSET + rom.size());
//    debugger->printOpcodes(opcodes, rom);

    running = true;
    std::thread mainThread(&Chip8::mainLoop, this);

    window->show();

    while (!window->isClosed()) {
        window->pollEvents();
    }

    running = false;
    mainThread.join();
}

void Chip8::mainLoop() {
    std::cout << std::endl << "Starting main loop" << std::endl << std::endl;
    timer->init();

    while (running) {
        tick();

        if (timer->tick()) {
            delayTimer = std::max(0, delayTimer - 1);
            soundTimer = std::max(0, soundTimer - 1);
        }

        sleep(1);
    }
}

void Chip8::tick() {
    const uint16_t opcode = fetch();
    const Opcodes::OpcodeEntry &opcodeEntry = opcodes->findOpcode(opcode);

    if (DEBUG_OPCODES) {
        printf("%04X - ", PC);
    }

    increaseProgramCounter();
    executeInstruction(opcode, opcodeEntry);
    doSound();

    window->redraw();
}

uint16_t Chip8::fetch() {
    return (memory.at(PC) << 8) | memory.at(PC + 1);;
}

void Chip8::increaseProgramCounter() {
    PC += 2;
}

void Chip8::executeInstruction(const uint16_t opcode, const Opcodes::OpcodeEntry &opcodeEntry) const {
    (opcodes.get()->*opcodeEntry.handler)(opcode);
}

void Chip8::doSound() {
    if (soundTimer > 0) {
        sound->play();
    } else {
        sound->pause();
    }
}

void Chip8::sleep(int milliseconds) const {
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}

bool Chip8::drawSpritePixel(unsigned int x, unsigned int y) {
    return window->drawSpritePixel(x, y);
}

void Chip8::clearScreen() {
    window->clearScreen();
}

bool Chip8::keyIsPressed(uint8_t key) {
    return keyboard->keyIsPressed(key);
}

uint8_t Chip8::waitForKeyPress() {
    uint8_t currentKey;

    do {
        currentKey = keyboard->getCurrentKeyPressed();
        sleep(1);
    } while (running && currentKey == Keyboard::NO_KEY_PRESSED);

    return currentKey;
}
