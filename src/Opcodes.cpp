#include "Chip8.h"

#include "Opcodes.h"

#include <utility>

Opcodes::Opcodes(std::shared_ptr<Chip8> chip8) {
    this->chip8 = std::move(chip8);
}

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
    printf("*%04X - %s - Jump to address %03X\n", opcode, "1NNN", nnn);

    chip8->PC = nnn;
    printf("Jumped to %04X\n", chip8->PC);
}

void Opcodes::handle2NNN(uint16_t opcode) {
    uint16_t nnn = getNNN(opcode);

    // Call subroutine at NNN
    printf("%04X - %s - Call subroutine at %03X\n", opcode, "2NNN", nnn);
}

void Opcodes::handle3XNN(uint16_t opcode) {
    uint16_t vx = getVX(opcode);
    uint16_t nn = getNN(opcode);

    // Skip the next instruction if VX equals NN
    printf("*%04X - %s - Skip the next instruction if V%01X equals %02X\n", opcode, "3XNN", vx, nn);

    if (chip8->V[vx] == nn) {
        chip8->PC +=2;
        printf("Skipping to %04X\n", chip8->PC);
    }
}

void Opcodes::handle4XNN(uint16_t opcode) {
    uint16_t vx = getVX(opcode);
    uint16_t nn = getNN(opcode);

    // Skip the next instruction if VX doesn't equal NN
    printf("%04X - %s - Skip the next instruction if V%01X doesn't equal %02X\n", opcode, "4XNN", vx, nn);
}

void Opcodes::handle5XY0(uint16_t opcode) {
    uint16_t vx = getVX(opcode);
    uint16_t vy = getVY(opcode);

    // Skip the next instruction if VX equals VY
    printf("*%04X - %s - Skip the next instruction if V%01X equals V%01X\n", opcode, "5XY0", vx, vy);

    if (chip8->V[vx] == vy) {
        chip8->PC +=2;
        printf("Skipping to %04X\n", chip8->PC);
    }
}

void Opcodes::handle6XNN(uint16_t opcode) {
    uint16_t vx = getVX(opcode);
    uint16_t nn = getNN(opcode);

    // Set VX to NN
    printf("*%04X - %s - Set V%01X to %02X\n", opcode, "6XNN", vx, nn);

    chip8->V[vx] = nn;
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

    // Store the most significant bit of VX in VF and then shift VX to the left by 1
    printf("%04X - %s - Store the most significant bit of V%01X in VF and then shift V%01X to the left by 1\n", opcode, "8XYE", vx, vx);
}

void Opcodes::handle9XY0(uint16_t opcode) {
    uint16_t vx = getVX(opcode);
    uint16_t vy = getVY(opcode);

    // Skip the next instruction if VX doesn't equal VY
    printf("%04X - %s - Skip the next instruction if V%01X doesn't equal V%01X\n", opcode, "9XY0", vx, vy);
}

void Opcodes::handleANNN(uint16_t opcode) {
    uint16_t nnn = getNNN(opcode);

    // Set I to the address NNN
    printf("*%04X - %s - Set I to the address %03X\n", opcode, "ANNN", nnn);

    chip8->I = nnn;
}

void Opcodes::handleBNNN(uint16_t opcode) {
    uint16_t nnn = getNNN(opcode);

    // Jump to the address NNN plus V0
    printf("%04X - %s - Jump to the address %03X plus V0\n", opcode, "BNNN", nnn);
}

void Opcodes::handleCXNN(uint16_t opcode) {
    uint16_t vx = getVX(opcode);
    uint16_t nn = getNN(opcode);

    // Set VX to the result of a bitwise and operation on a random number (Typically: 0 to 255) and NN
    printf("%04X - %s - Set V%01X to the result of a bitwise and operation on a random number and %02X\n", opcode, "CXNN", vx, nn);
}

void Opcodes::handleDXYN(uint16_t opcode) {
    uint16_t vx = getVX(opcode);
    uint16_t vy = getVY(opcode);
    uint16_t n = getN(opcode);

     // Draw a sprite at coordinate (VX, VY) that has a width of 8 pixels and a height of N pixels
    printf("%04X - %s - Draw a sprite at coordinate (V%01X, V%01X) that has a width of 8 pixels and a height of %01X pixels\n", opcode, "DXYN", vx, vy, n);
}

void Opcodes::handleEX9E(uint16_t opcode) {
    uint16_t vx = getVX(opcode);

    // Skip the next instruction if the key stored in VX is pressed
    printf("%04X - %s - Skip the next instruction if the key stored in V%01X is pressed\n", opcode, "EX9E", vx);
}

void Opcodes::handleEXA1(uint16_t opcode) {
    uint16_t vx = getVX(opcode);

    // Skip the next instruction if the key stored in VX isn't pressed
    printf("%04X - %s - Skip the next instruction if the key stored in V%01X isn't pressed\n", opcode, "EXA1", vx);
}

void Opcodes::handleFX07(uint16_t opcode) {
    uint16_t vx = getVX(opcode);

    // Set VX to the value of the delay timer
    printf("%04X - %s - Set V%01X to the value of the delay timer\n", opcode, "FX07", vx);
}

void Opcodes::handleFX0A(uint16_t opcode) {
    uint16_t vx = getVX(opcode);

    // A key press is awaited, and then stored in VX
    printf("%04X - %s - A key press is awaited, and then stored in V%01X\n", opcode, "FX0A", vx);
}

void Opcodes::handleFX15(uint16_t opcode) {
    uint16_t vx = getVX(opcode);

    // Set the delay timer to VX
    printf("%04X - %s - Set the delay timer to V%01X\n", opcode, "FX15", vx);
}

void Opcodes::handleFX18(uint16_t opcode) {
    uint16_t vx = getVX(opcode);

    // Set the sound timer to VX
    printf("%04X - %s - Set the sound timer to V%01X\n", opcode, "FX18", vx);
}

void Opcodes::handleFX1E(uint16_t opcode) {
    uint16_t vx = getVX(opcode);

    // Add VX to I. VF is set to 1 when there is a range overflow, and to 0 when there isn't
    printf("%04X - %s - Add V%01X to I\n", opcode, "FX1E", vx);
}

void Opcodes::handleFX29(uint16_t opcode) {
    uint16_t vx = getVX(opcode);

    // Set I to the location of the sprite for the character in VX
    printf("%04X - %s - Set I to the location of the sprite for the character in V%01X\n", opcode, "FX29", vx);
}

void Opcodes::handleFX33(uint16_t opcode) {
    uint16_t vx = getVX(opcode);

    // Store the binary-coded decimal representation of VX
    printf("%04X - %s - Store the binary-coded decimal representation of V%01X\n", opcode, "FX33", vx);
}

void Opcodes::handleFX55(uint16_t opcode) {
    uint16_t vx = getVX(opcode);

    // Store V0 to VX (including VX) in memory starting at address I
    printf("%04X - %s - Store V0 to V%01X in memory starting at address I\n", opcode, "FX55", vx);
}

void Opcodes::handleFX65(uint16_t opcode) {
    uint16_t vx = getVX(opcode);

    // Fill V0 to VX (including VX) with values from memory starting at address I
    printf("%04X - %s - Fill V0 to V%01X with values from memory starting at address I\n", opcode, "FX65", vx);
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

uint16_t Opcodes::getN(uint16_t opcode) {
    return opcode & 0x000F;
}

uint16_t Opcodes::getNN(uint16_t opcode) {
    return opcode & 0x00FF;
}

uint16_t Opcodes::getNNN(uint16_t opcode) {
    return opcode & 0x0FFF;
}