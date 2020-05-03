#include <iostream>
#include <memory>

#include "Opcodes.h"

#include "Debugger.h"

Debugger::Debugger() {
    std::cout << "Debugger in" << std::endl;
}

Debugger::~Debugger() {
    std::cout << "Debugger out" << std::endl;
}

void Debugger::hexPrint(const std::string &name, const std::vector<uint8_t> &vector, int startPos, int endPos) {
    std::cout << std::endl << "Printing: " << name;

    int padding = LINE_LENGTH * 2;
    int paddedStartPos = std::max(0, startPos - padding);
    int paddedEndPos = std::min(endPos + padding, (int) vector.size());

    for (int i = paddedStartPos; i < paddedEndPos; i++) {
        if (i % LINE_LENGTH == 0) {
            std::cout << std::endl;
            printf("%04X ", i);
        }

        if (i % 4 == 0) {
            std::cout << " ";
        }

        printf("%02X ", vector[i]);
    }

    std::cout << std::endl;
}

void Debugger::printOpcodes(const std::shared_ptr<Opcodes> &opcodes, const std::vector<uint8_t> &vector) {
    for (int i = 0; i < vector.size(); i +=2) {
        uint16_t opcode = (vector[i] << 8) | vector[i + 1];
        Opcodes::OpcodeEntry opcodeEntry = opcodes->findOpcode(opcode);

        printf("%04X - %s - %s\n", opcode, opcodeEntry.name.c_str(), opcodeEntry.description.c_str());
        (opcodes.get()->*opcodeEntry.handler)(opcode);
    }

    std::cout << std::endl << std::endl;
}
