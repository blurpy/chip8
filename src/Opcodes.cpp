#include "Opcodes.h"

Opcodes::OpcodeEntry Opcodes::findOpcode(uint16_t opcode) {
    for (auto &entry : opcodeEntries) {
        if ((opcode & entry.mask) == entry.opcode) {
            return entry;
        }
    }

    return invalid;
}

void Opcodes::handle0NNN(uint16_t opcode) {
    uint16_t nnn = getNNN(opcode);

    // Call RCA 1802 program at address NNN
    printf("%04X - %s - Call RCA 1802 program at address %03X\n", opcode, "0NNN", nnn);
}

void Opcodes::handle00E0(uint16_t opcode) {

}

void Opcodes::handle00EE(uint16_t opcode) {

}

void Opcodes::handle1NNN(uint16_t opcode) {
    uint16_t nnn = getNNN(opcode);

    // Jump to address NNN
    printf("%04X - %s - Jump to address %03X\n", opcode, "1NNN", nnn);
}

void Opcodes::handle2NNN(uint16_t opcode) {
    uint16_t nnn = getNNN(opcode);

    // Call subroutine at NNN
    printf("%04X - %s - Call subroutine at %03X\n", opcode, "2NNN", nnn);
}

void Opcodes::handle3XNN(uint16_t opcode) {
    uint16_t nnn = getNNN(opcode);

    // Call subroutine at NNN
    printf("%04X - %s - Call subroutine at %03X\n", opcode, "2NNN", nnn);
}

void Opcodes::handle4XNN(uint16_t opcode) {

}

void Opcodes::handle5XY0(uint16_t opcode) {

}

void Opcodes::handle6XNN(uint16_t opcode) {
    uint16_t vx = getVX(opcode);
    uint16_t nn = getNN(opcode);

    // Set VX to NN
    printf("%04X - %s - Set V%01X to %02X\n", opcode, "6XNN", vx, nn);
}

void Opcodes::handle7XNN(uint16_t opcode) {
    uint16_t vx = getVX(opcode);
    uint16_t nn = getNN(opcode);

    // Add NN to VX. (Carry flag is not changed)
    printf("%04X - %s - Add %02X to V%01X\n", opcode, "7XNN", nn, vx);
}

void Opcodes::handle8XY0(uint16_t opcode) {
    uint16_t vx = getVX(opcode);
    uint16_t vy = getVY(opcode);

    // Set VX to the value of VY
    printf("%04X - %s - Set V%01X to the value of V%01X\n", opcode, "8XY0", vx, vy);
}

void Opcodes::handle8XY1(uint16_t opcode) {

}

void Opcodes::handle8XY2(uint16_t opcode) {

}

void Opcodes::handle8XY3(uint16_t opcode) {

}

void Opcodes::handle8XY4(uint16_t opcode) {

}

void Opcodes::handle8XY5(uint16_t opcode) {

}

void Opcodes::handle8XY6(uint16_t opcode) {

}

void Opcodes::handle8XY7(uint16_t opcode) {

}

void Opcodes::handle8XYE(uint16_t opcode) {

}

void Opcodes::handle9XY0(uint16_t opcode) {

}

void Opcodes::handleANNN(uint16_t opcode) {

}

void Opcodes::handleBNNN(uint16_t opcode) {

}

void Opcodes::handleCXNN(uint16_t opcode) {

}

void Opcodes::handleDXYN(uint16_t opcode) {

}

void Opcodes::handleEX9E(uint16_t opcode) {

}

void Opcodes::handleEXA1(uint16_t opcode) {

}

void Opcodes::handleFX07(uint16_t opcode) {

}

void Opcodes::handleFX0A(uint16_t opcode) {

}

void Opcodes::handleFX15(uint16_t opcode) {

}

void Opcodes::handleFX18(uint16_t opcode) {

}

void Opcodes::handleFX1E(uint16_t opcode) {

}

void Opcodes::handleFX29(uint16_t opcode) {

}

void Opcodes::handleFX33(uint16_t opcode) {

}

void Opcodes::handleFX55(uint16_t opcode) {

}

void Opcodes::handleFX65(uint16_t opcode) {

}

void Opcodes::handleInvalid(uint16_t opcode) {

}

uint16_t Opcodes::getVX(uint16_t opcode) {
    return (opcode & 0x0F00) >> 8;
}

uint16_t Opcodes::getVY(uint16_t opcode) {
    return (opcode & 0x00F0) >> 4;
}

uint16_t Opcodes::getNN(uint16_t opcode) {
    return opcode & 0x00FF;
}

uint16_t Opcodes::getNNN(uint16_t opcode) {
    return opcode & 0x0FFF;
}
