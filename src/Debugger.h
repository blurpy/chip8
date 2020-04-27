#ifndef CHIP8_DEBUGGER_H
#define CHIP8_DEBUGGER_H

#include <cstdint>
#include <vector>

class Debugger {

public:
    void hexPrint(const std::vector<uint8_t> &vector);
};

#endif //CHIP8_DEBUGGER_H
