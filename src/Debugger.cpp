#include <iostream>
#include <memory>

#include "Opcodes.h"

#include "Debugger.h"

void Debugger::hexPrint(const std::vector<uint8_t> &vector) {
    for (int i = 0; i < vector.size(); i++) {
        if (i % 16 == 0) {
            std::cout << std::endl;
            printf("%04X ", i);
        }

        if (i % 4 == 0) {
            std::cout << " ";
        }

        printf("%02X ", vector[i]);
    }

    std::cout << std::endl << std::endl;
}

void Debugger::printOpcodes(const std::unique_ptr<Opcodes> &opcodes, const std::vector<uint8_t> &vector) {
    for (int i = 0; i < vector.size(); i +=2) {
        uint16_t opcode = (vector[i] << 8) | vector[i + 1];
        Opcodes::OpcodeEntry opcodeEntry = opcodes->findOpcode(opcode);

        printf("%04X - %s - %s\n", opcode, opcodeEntry.name.c_str(), opcodeEntry.description.c_str());
    }

    std::cout << std::endl << std::endl;
}
