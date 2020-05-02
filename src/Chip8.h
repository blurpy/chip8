#ifndef CHIP8_CHIP8_H
#define CHIP8_CHIP8_H

#include <memory>
#include <string>
#include <vector>

#include "Window.h"

#include "Opcodes.h"

class Chip8 {

public:
    static const int ROM_OFFSET = 0x200;
    static const int MEMORY_SIZE = 4096;

    Chip8();
    ~Chip8();

    void run(const std::string &fileName);

private:
    friend class Opcodes;

    std::shared_ptr<Opcodes> opcodes;
    std::unique_ptr<Window> window;

    std::vector<uint8_t> memory = std::vector<uint8_t>(MEMORY_SIZE); // 4096 8-bit memory locations

    uint8_t V[16]{}; // V0 to VF 8-bit registers
    uint16_t I = 0;  // 16 bit I-register
    uint16_t PC = ROM_OFFSET; // 16-bit Program counter

    uint8_t delayTimer = 0;
    uint8_t soundTimer = 0;

    bool running = false;

    void mainLoop();
    void tick();
    uint16_t fetch();
    void increaseProgramCounter();
    void executeInstruction(uint16_t opcode, const Opcodes::OpcodeEntry &opcodeEntry) const;
    void sleep(int milliseconds) const;

    void clearScreen();
};

#endif //CHIP8_CHIP8_H
