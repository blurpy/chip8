#ifndef CHIP8_CHIP8_H
#define CHIP8_CHIP8_H

#include <string>
#include <vector>

static const int MEMORY_SIZE = 4096;

class Chip8 {

public:
    void run(const std::string &fileName);

private:
    std::vector<uint8_t> memory = std::vector<uint8_t>(MEMORY_SIZE); // 4096 8-bit memory locations

    uint8_t V[16]{}; // V0 to VF 8-bit registers
    uint16_t I = 0;  // 16 bit I-register
    uint16_t PC = 0; // 16-bit Program counter
};

#endif //CHIP8_CHIP8_H
