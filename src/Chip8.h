#ifndef CHIP8_CHIP8_H
#define CHIP8_CHIP8_H

#include <memory>
#include <stack>
#include <string>
#include <vector>

#include "Keyboard.h"
#include "Window.h"

#include "Opcodes.h"

class Chip8 {

public:
    static const int ROM_OFFSET = 0x200;
    static const int FONT_OFFSET = 0x50;
    static const int FONT_CHARACTER_SIZE = 5; // Bytes
    static const int MEMORY_SIZE = 4096;

    Chip8();
    ~Chip8();

    void run(const std::string &fileName);

private:
    friend class Opcodes;

    std::shared_ptr<Opcodes> opcodes;
    std::shared_ptr<Keyboard> keyboard;
    std::unique_ptr<Window> window;

    std::vector<uint8_t> memory = std::vector<uint8_t>(MEMORY_SIZE); // 4096 8-bit memory locations

    uint8_t V[16]{}; // V0 to VF 8-bit registers
    uint16_t I = 0;  // 16 bit I-register
    uint16_t PC = ROM_OFFSET; // 16-bit Program counter
    std::stack<uint16_t> stack = std::stack<uint16_t>(); // 16-bit stack

    uint8_t delayTimer = 0;
    uint8_t soundTimer = 0;

    std::vector<uint8_t> font = {
                    0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
                    0x20, 0x60, 0x20, 0x20, 0x70, // 1
                    0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
                    0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
                    0x90, 0x90, 0xF0, 0x10, 0x10, // 4
                    0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
                    0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
                    0xF0, 0x10, 0x20, 0x40, 0x40, // 7
                    0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
                    0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
                    0xF0, 0x90, 0xF0, 0x90, 0x90, // A
                    0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
                    0xF0, 0x80, 0x80, 0x80, 0xF0, // C
                    0xE0, 0x90, 0x90, 0x90, 0xE0, // D
                    0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
                    0xF0, 0x80, 0xF0, 0x80, 0x80  // F
    };

    bool running = false;

    void mainLoop();
    void tick();
    uint16_t fetch();
    void increaseProgramCounter();
    void executeInstruction(uint16_t opcode, const Opcodes::OpcodeEntry &opcodeEntry) const;
    void sleep(int milliseconds) const;

    bool drawSpritePixel(unsigned int x, unsigned int y);
    void clearScreen();

    bool keyIsPressed(uint8_t key);
};

#endif //CHIP8_CHIP8_H
