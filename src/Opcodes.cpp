#include "Chip8.h"

#include <iostream>
#include <random>
#include <bitset>

#include "Opcodes.h"

Opcodes::Opcodes(Chip8 *chip8) {
    this->chip8 = chip8;
    std::cout << "Opcodes in" << std::endl;
}

Opcodes::~Opcodes() {
    std::cout << "Opcodes out" << std::endl;
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
    printf("%04X - %s - Call RCA 1802 program at address 0x%04X\n", opcode, "0NNN", nnn);
}

void Opcodes::handle00E0(uint16_t opcode) {
    // Clear screen
    printf("*%04X - %s - Clear screen\n", opcode, "00E0");

    chip8->clearScreen();
}

void Opcodes::handle00EE(uint16_t opcode) {
    // Return from subroutine
    printf("*%04X - %s - Return from subroutine\n", opcode, "00EE");

    chip8->PC = chip8->stack.top();
    chip8->stack.pop();
    printf("Returned from subroutine to 0x%04X\n", chip8->PC);
}

void Opcodes::handle1NNN(uint16_t opcode) {
    uint16_t nnn = getNNN(opcode);

    // Jump to address NNN
    printf("*%04X - %s - Jump to address 0x%04X\n", opcode, "1NNN", nnn);

    chip8->PC = nnn;
    printf("Jumped to 0x%04X\n", chip8->PC);
}

void Opcodes::handle2NNN(uint16_t opcode) {
    uint16_t nnn = getNNN(opcode);

    // Call subroutine at NNN
    printf("*%04X - %s - Call subroutine at 0x%04X\n", opcode, "2NNN", nnn);

    chip8->stack.push(chip8->PC);
    chip8->PC = nnn;
    printf("Called subroutine at 0x%04X\n", chip8->PC);
}

void Opcodes::handle3XNN(uint16_t opcode) {
    uint16_t vx = getVX(opcode);
    uint16_t nn = getNN(opcode);

    // Skip the next instruction if VX equals NN
    printf("*%04X - %s - Skip the next instruction if V%01X (0x%02X) equals 0x%02X\n", opcode, "3XNN", vx, chip8->V[vx], nn);

    if (chip8->V[vx] == nn) {
        chip8->PC +=2;
        printf("Skipping to 0x%04X\n", chip8->PC);
    }
}

void Opcodes::handle4XNN(uint16_t opcode) {
    uint16_t vx = getVX(opcode);
    uint16_t nn = getNN(opcode);

    // Skip the next instruction if VX doesn't equal NN
    printf("*%04X - %s - Skip the next instruction if V%01X (0x%02X) doesn't equal 0x%02X\n", opcode, "4XNN", vx, chip8->V[vx], nn);

    if (chip8->V[vx] != nn) {
        chip8->PC +=2;
        printf("Skipping to 0x%04X\n", chip8->PC);
    }
}

void Opcodes::handle5XY0(uint16_t opcode) {
    uint16_t vx = getVX(opcode);
    uint16_t vy = getVY(opcode);

    // Skip the next instruction if VX equals VY
    printf("*%04X - %s - Skip the next instruction if V%01X equals V%01X\n", opcode, "5XY0", vx, vy);

    if (chip8->V[vx] == vy) {
        chip8->PC +=2;
        printf("Skipping to 0x%04X\n", chip8->PC);
    }
}

void Opcodes::handle6XNN(uint16_t opcode) {
    uint16_t vx = getVX(opcode);
    uint16_t nn = getNN(opcode);

    // Set VX to NN
    printf("*%04X - %s - Set V%01X to 0x%02X\n", opcode, "6XNN", vx, nn);

    chip8->V[vx] = nn;
}

void Opcodes::handle7XNN(uint16_t opcode) {
    uint16_t vx = getVX(opcode);
    uint16_t nn = getNN(opcode);

    // Add NN to VX. (Carry flag is not changed)
    printf("*%04X - %s - Add 0x%02X to V%01X\n", opcode, "7XNN", nn, vx);

    chip8->V[vx] += nn;
}

void Opcodes::handle8XY0(uint16_t opcode) {
    uint16_t vx = getVX(opcode);
    uint16_t vy = getVY(opcode);

    // Set VX to the value of VY
    printf("*%04X - %s - Set V%01X to the value of V%01X\n", opcode, "8XY0", vx, vy);

    chip8->V[vx] = chip8->V[vy];
}

void Opcodes::handle8XY1(uint16_t opcode) {
    uint16_t vx = getVX(opcode);
    uint16_t vy = getVY(opcode);

    // Set VX to VX or VY. (Bitwise OR operation)
    printf("*%04X - %s - Set V%01X to V%01X or V%01X\n", opcode, "8XY1", vx, vx, vy);

    chip8->V[vx] = chip8->V[vx] | chip8->V[vy];
}

void Opcodes::handle8XY2(uint16_t opcode) {
    uint16_t vx = getVX(opcode);
    uint16_t vy = getVY(opcode);

    // Set VX to VX and VY. (Bitwise AND operation)
    printf("*%04X - %s - Set V%01X to V%01X and V%01X\n", opcode, "8XY2", vx, vx, vy);

    chip8->V[vx] = chip8->V[vx] & chip8->V[vy];
}

void Opcodes::handle8XY3(uint16_t opcode) {
    uint16_t vx = getVX(opcode);
    uint16_t vy = getVY(opcode);

    // Set VX to VX xor VY. (Bitwise XOR operation)
    printf("*%04X - %s - Set V%01X to V%01X xor V%01X\n", opcode, "8XY3", vx, vx, vy);

    chip8->V[vx] = chip8->V[vx] ^ chip8->V[vy];
}

void Opcodes::handle8XY4(uint16_t opcode) {
    uint16_t vx = getVX(opcode);
    uint16_t vy = getVY(opcode);

    // Add VY to VX. VF is set to 1 when there's a carry, and to 0 when there isn't
    printf("*%04X - %s - Add V%01X to V%01X\n", opcode, "8XY4", vy, vx);

    uint16_t result = chip8->V[vx] + chip8->V[vy];

    chip8->V[vx] = result;
    chip8->V[0xF] = result > 255;
}

void Opcodes::handle8XY5(uint16_t opcode) {
    uint16_t vx = getVX(opcode);
    uint16_t vy = getVY(opcode);

    // VY is subtracted from VX. VF is set to 0 when there's a borrow, and 1 when there isn't
    printf("*%04X - %s - V%01X is subtracted from V%01X\n", opcode, "8XY5", vy, vx);

    uint8_t x = chip8->V[vx];
    uint8_t y = chip8->V[vy];
    int result = x - y;

    chip8->V[vx] = result;
    chip8->V[0xF] = result < 0;
    
    printf("Computed %i - %i = %i. Borrow: %i\n", x, y, result, result < 0);
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
    printf("*%04X - %s - Skip the next instruction if V%01X doesn't equal V%01X\n", opcode, "9XY0", vx, vy);

    if (chip8->V[vx] != chip8->V[vy]) {
        chip8->PC +=2;
        printf("Skipping to 0x%04X\n", chip8->PC);
    }
}

void Opcodes::handleANNN(uint16_t opcode) {
    uint16_t nnn = getNNN(opcode);

    // Set I to the address NNN
    printf("*%04X - %s - Set I to the address 0x%04X\n", opcode, "ANNN", nnn);

    chip8->I = nnn;
}

void Opcodes::handleBNNN(uint16_t opcode) {
    uint16_t nnn = getNNN(opcode);

    // Jump to the address NNN plus V0
    printf("%04X - %s - Jump to the address 0x%04X plus V0\n", opcode, "BNNN", nnn);
}

void Opcodes::handleCXNN(uint16_t opcode) {
    uint16_t vx = getVX(opcode);
    uint16_t nn = getNN(opcode);

    // Set VX to the result of a bitwise and operation on a random number (Typically: 0 to 255) and NN
    printf("*%04X - %s - Set V%01X to the result of a bitwise and operation on a random number and 0x%02X\n", opcode, "CXNN", vx, nn);

    unsigned int randomNumber = generateRandomNumber(0, 255);
    chip8->V[vx] = randomNumber & nn;

    printf("Generated random number 0x%02X and set V%01X (0x%02X)\n", randomNumber, vx, chip8->V[vx]);
}

/**
 * Draws a sprite at coordinate (VX, VY) that has a width of 8 pixels and a height of N pixels.
 * Each row of 8 pixels is read as bit-coded starting from memory location I;
 * I value doesn't change after the execution of this instruction.
 * As described above, VF is set to 1 if any screen pixels are flipped from set to unset when the sprite is drawn,
 * and to 0 if that doesn't happen.
 *
 * 8 bit-coded pixels means that a 1 at a location in the byte represents a visible pixel at that column and 0 does not.
 * Like this:
 *
 * 00111100 = '  ****  '
 * 11000011 = '**    **'
 */
void Opcodes::handleDXYN(uint16_t opcode) {
    uint16_t vx = getVX(opcode);
    uint16_t vy = getVY(opcode);
    uint16_t n = getN(opcode);

     // Draw a sprite at coordinate (VX, VY) that has a width of 8 pixels and a height of N pixels
    printf("*%04X - %s - Draw a sprite at coordinate (V%01X, V%01X) that has a width of 8 pixels and a height of %01X pixels\n", opcode, "DXYN", vx, vy, n);

    bool unsetPixels = false;
    int initialXPosition = chip8->V[vx];
    int initialYPosition = chip8->V[vy];

    for (int yIndex = 0; yIndex < n; yIndex++) { // Height/Rows
        uint8_t &pixelsAtRow = chip8->memory[chip8->I + yIndex]; // The 8 bit-coded pixels for this row

        for (int xIndex = 0; xIndex < 8; xIndex++) { // Width/Columns
            int xPosition = initialXPosition + xIndex;
            int yPosition = initialYPosition + yIndex;

            // Only draw a pixel if it's a 1 at the current column in the bit-coded pixels
            if ((pixelsAtRow & (0x80 >> xIndex)) != 0) {
                if (chip8->drawSpritePixel(xPosition, yPosition)) {
                    unsetPixels = true;
                }

                std::cout << "Draw at: [" << xPosition << "," << yPosition << "] - Bits: "
                          << std::bitset<sizeof(uint8_t *)>(pixelsAtRow) << " - Unset: " << unsetPixels << std::endl;
            }
        }
    }

    chip8->V[0xF] = unsetPixels;
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
    printf("*%04X - %s - Set V%01X to the value of the delay timer (0x%02X)\n", opcode, "FX07", vx, chip8->delayTimer);

    chip8->V[vx] = chip8->delayTimer;
}

void Opcodes::handleFX0A(uint16_t opcode) {
    uint16_t vx = getVX(opcode);

    // A key press is awaited, and then stored in VX
    printf("%04X - %s - A key press is awaited, and then stored in V%01X\n", opcode, "FX0A", vx);
}

void Opcodes::handleFX15(uint16_t opcode) {
    uint16_t vx = getVX(opcode);

    // Set the delay timer to VX
    printf("*%04X - %s - Set the delay timer to V%01X (0x%02X)\n", opcode, "FX15", vx, chip8->V[vx]);

    chip8->delayTimer = chip8->V[vx];
}

void Opcodes::handleFX18(uint16_t opcode) {
    uint16_t vx = getVX(opcode);

    // Set the sound timer to VX
    printf("*%04X - %s - Set the sound timer to V%01X (0x%02X)\n", opcode, "FX18", vx, chip8->V[vx]);

    chip8->soundTimer = chip8->V[vx];
}

void Opcodes::handleFX1E(uint16_t opcode) {
    uint16_t vx = getVX(opcode);

    // Add VX to I. VF is set to 1 when there is a range overflow, and to 0 when there isn't
    printf("%04X - %s - Add V%01X to I\n", opcode, "FX1E", vx);
}

/**
 * Sets I to the location of the sprite for the character in VX.
 * Characters 0-F (in hexadecimal) are represented by a 4x5 font.
 */
void Opcodes::handleFX29(uint16_t opcode) {
    uint16_t vx = getVX(opcode);

    // Set I to the location of the sprite for the character in VX
    printf("*%04X - %s - Set I to the location of the sprite for the character in V%01X\n", opcode, "FX29", vx);

    uint8_t character = chip8->V[vx];
    uint16_t location = Chip8::FONT_OFFSET + character * Chip8::FONT_CHARACTER_SIZE;
    chip8->I = location;

    printf("Returning character %01X at %04X\n", character, location);
}

/**
 * Stores the binary-coded decimal representation of VX, with the most significant of three digits
 * at the address in I, the middle digit at I plus 1, and the least significant digit at I plus 2.
 * (In other words, take the decimal representation of VX, place the hundreds digit in memory at
 * location in I, the tens digit at location I+1, and the ones digit at location I+2.)
 */
void Opcodes::handleFX33(uint16_t opcode) {
    uint16_t vx = getVX(opcode);

    // Store the binary-coded decimal representation of VX
    printf("*%04X - %s - Store the binary-coded decimal representation of V%01X\n", opcode, "FX33", vx);

    uint8_t value = chip8->V[vx];

    int hundredsPlace = value / 100;  // [1]23
    int tensPlace = value % 100 / 10; // 1[2]3
    int onesPlace = value % 10;       // 12[3]

    chip8->memory[chip8->I + 0] = hundredsPlace;
    chip8->memory[chip8->I + 1] = tensPlace;
    chip8->memory[chip8->I + 2] = onesPlace;

    printf("Converted %i to %i %i %i\n", value, hundredsPlace, tensPlace, onesPlace);
}

void Opcodes::handleFX55(uint16_t opcode) {
    uint16_t vx = getVX(opcode);

    // Store V0 to VX (including VX) in memory starting at address I
    printf("%04X - %s - Store V0 to V%01X in memory starting at address I\n", opcode, "FX55", vx);
}

/**
 * Fills V0 to VX (including VX) with values from memory starting at address I.
 * The offset from I is increased by 1 for each value written, but I itself is left unmodified
 */
void Opcodes::handleFX65(uint16_t opcode) {
    uint16_t vx = getVX(opcode);

    // Fill V0 to VX (including VX) with values from memory starting at address I
    printf("*%04X - %s - Fill V0 to V%01X with values from memory starting at address I\n", opcode, "FX65", vx);

    for (int i = 0; i <= vx; i++) {
        uint16_t value = chip8->memory[chip8->I + i];
        chip8->V[i] = value;
        printf("Filled V%01X with %04X\n", i, value);
    }
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

unsigned int Opcodes::generateRandomNumber(unsigned char from, unsigned char to)  {
    std::minstd_rand engine{std::random_device{}()};
    std::uniform_int_distribution<uint8_t> distribution{from, to};

    return distribution(engine);
}
