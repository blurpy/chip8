#include "Opcodes.h"

Opcodes::OpcodeEntry Opcodes::findOpcode(uint16_t opcode) {
    for (auto &entry : opcodeEntries) {
        if ((opcode & entry.mask) == entry.opcode) {
            return entry;
        }
    }

    return invalid;
}
