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
    // Clear screen
    printf("%04X - %s - Clear screen\n", opcode, "00E0");
}

void Opcodes::handle00EE(uint16_t opcode) {
    // Return from subroutine
    printf("%04X - %s - Return from subroutine\n", opcode, "00EE");
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
    // Skip the next instruction if VX equals NN
}

void Opcodes::handle4XNN(uint16_t opcode) {
    // Skip the next instruction if VX doesn't equal NN
}

void Opcodes::handle5XY0(uint16_t opcode) {
    uint16_t vx = getVX(opcode);
    uint16_t vy = getVY(opcode);

    // Skip the next instruction if VX equals VY
    printf("%04X - %s - Skip the next instruction if V%01X equals V%01X\n", opcode, "5XY0", vx, vy);
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
    uint16_t vx = getVX(opcode);
    uint16_t vy = getVY(opcode);

    // Set VX to VX or VY. (Bitwise OR operation)
    printf("%04X - %s - Set V%01X to V%01X or V%01X\n", opcode, "8XY1", vx, vx, vy);
}

void Opcodes::handle8XY2(uint16_t opcode) {
    uint16_t vx = getVX(opcode);
    uint16_t vy = getVY(opcode);

    // Set VX to VX and VY. (Bitwise AND operation)
    printf("%04X - %s - Set V%01X to V%01X and V%01X\n", opcode, "8XY2", vx, vx, vy);
}

void Opcodes::handle8XY3(uint16_t opcode) {
    uint16_t vx = getVX(opcode);
    uint16_t vy = getVY(opcode);

    // Set VX to VX xor VY. (Bitwise XOR operation)
    printf("%04X - %s - Set V%01X to V%01X xor V%01X\n", opcode, "8XY3", vx, vx, vy);
}

void Opcodes::handle8XY4(uint16_t opcode) {
    uint16_t vx = getVX(opcode);
    uint16_t vy = getVY(opcode);

    // Add VY to VX. VF is set to 1 when there's a carry, and to 0 when there isn't
    printf("%04X - %s - Add V%01X to V%01X\n", opcode, "8XY4", vy, vx);
}

void Opcodes::handle8XY5(uint16_t opcode) {
    uint16_t vx = getVX(opcode);
    uint16_t vy = getVY(opcode);

    // VY is subtracted from VX. VF is set to 0 when there's a borrow, and 1 when there isn't
    printf("%04X - %s - V%01X is subtracted from V%01X\n", opcode, "8XY5", vy, vx);
}

void Opcodes::handle8XY6(uint16_t opcode) {
    uint16_t vx = getVX(opcode);

    // Store the least significant bit of VX in VF and then shifts VX to the right by 1
    printf("%04X - %s - Store the least significant bit of V%01X in VF and then shifts V%01X to the right by 1\n", opcode, "8XY6", vx, vx);
}

void Opcodes::handle8XY7(uint16_t opcode) {
    uint16_t vx = getVX(opcode);
    uint16_t vy = getVY(opcode);

    // Set VX to VY minus VX. VF is set to 0 when there's a borrow, and 1 when there isn't
    printf("%04X - %s - Set V%01X to V%01X minus V%01X\n", opcode, "8XY7", vx, vy, vx);
}

void Opcodes::handle8XYE(uint16_t opcode) {
    uint16_t vx = getVX(opcode);

    // Stores the most significant bit of VX in VF and then shifts VX to the left by 1
    printf("%04X - %s - Store the most significant bit of V%01X in VF and then shifts V%01X to the left by 1\n", opcode, "8XYE", vx, vx);
}

void Opcodes::handle9XY0(uint16_t opcode) {
    uint16_t vx = getVX(opcode);
    uint16_t vy = getVY(opcode);

    // Skips the next instruction if VX doesn't equal VY
    printf("%04X - %s - Skips the next instruction if V%01X doesn't equal V%01X\n", opcode, "8XY7", vx, vy);
}

void Opcodes::handleANNN(uint16_t opcode) {
    uint16_t nnn = getNNN(opcode);

    // Sets I to the address NNN
    printf("%04X - %s - Sets I to the address %03X\n", opcode, "ANNN", nnn);
}

void Opcodes::handleBNNN(uint16_t opcode) {
    uint16_t nnn = getNNN(opcode);

    // Jumps to the address NNN plus V0
    printf("%04X - %s - Jumps to the address %03X plus V0\n", opcode, "BNNN", nnn);
}

void Opcodes::handleCXNN(uint16_t opcode) {
    // Sets VX to the result of a bitwise and operation on a random number (Typically: 0 to 255) and NN
}

void Opcodes::handleDXYN(uint16_t opcode) {
     // Draws a sprite at coordinate (VX, VY) that has a width of 8 pixels and a height of N pixels
}

void Opcodes::handleEX9E(uint16_t opcode) {
    // Skips the next instruction if the key stored in VX is pressed
}

void Opcodes::handleEXA1(uint16_t opcode) {
    // Skips the next instruction if the key stored in VX isn't pressed
}

void Opcodes::handleFX07(uint16_t opcode) {
    // Sets VX to the value of the delay timer
}

void Opcodes::handleFX0A(uint16_t opcode) {
    // A key press is awaited, and then stored in VX
}

void Opcodes::handleFX15(uint16_t opcode) {
    // Sets the delay timer to VX
}

void Opcodes::handleFX18(uint16_t opcode) {
    // Sets the sound timer to VX
}

void Opcodes::handleFX1E(uint16_t opcode) {
    // Adds VX to I. VF is set to 1 when there is a range overflow, and to 0 when there isn't
}

void Opcodes::handleFX29(uint16_t opcode) {
    // Sets I to the location of the sprite for the character in VX
}

void Opcodes::handleFX33(uint16_t opcode) {
    // Stores the binary-coded decimal representation of VX
}

void Opcodes::handleFX55(uint16_t opcode) {
    // Stores V0 to VX (including VX) in memory starting at address I
}

void Opcodes::handleFX65(uint16_t opcode) {
    // Fills V0 to VX (including VX) with values from memory starting at address I
}

void Opcodes::handleInvalid(uint16_t opcode) {
    // Invalid opcode
    printf("%04X - %s - Invalid opcode\n", opcode, "----");
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
