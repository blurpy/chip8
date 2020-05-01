#ifndef CHIP8_DEBUGGER_H
#define CHIP8_DEBUGGER_H

#include <cstdint>
#include <vector>

#include "Opcodes.h"

class Debugger {

public:
    static const int LINE_LENGTH = 16;

    void hexPrint(const std::vector<uint8_t> &vector, int startPos, int endPos);
    void printOpcodes(const std::unique_ptr<Opcodes> &opcodes, const std::vector<uint8_t> &vector);
};

#endif //CHIP8_DEBUGGER_H
