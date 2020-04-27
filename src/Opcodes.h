#ifndef CHIP8_OPCODES_H
#define CHIP8_OPCODES_H

#include <cstdint>
#include <functional>
#include <string>
#include <vector>

class Opcodes {

public:
    struct OpcodeEntry {
        std::string name;
        uint16_t opcode;
        uint16_t mask;
        void (Opcodes::*handler)(uint16_t);
        std::string description;
    };

    OpcodeEntry findOpcode(uint16_t opcode);

private:
    std::vector<OpcodeEntry> opcodeEntries = {
            {"0NNN", 0x0000, 0xF000, &Opcodes::handle0NNN, "Call RCA 1802 program at address NNN."}, // TODO order
            {"00E0", 0x00E0, 0xFFFF, &Opcodes::handle00E0, "Clear screen."},
            {"00EE", 0x00EE, 0xFFFF, &Opcodes::handle00EE, "Return from subroutine."},
            {"1NNN", 0x1000, 0xF000, &Opcodes::handle1NNN, "Jump to address NNN."},
            {"2NNN", 0x2000, 0xF000, &Opcodes::handle2NNN, "Call subroutine at NNN."},
            {"3XNN", 0x3000, 0xF000, &Opcodes::handle3XNN, "Skip the next instruction if VX equals NN."},
            {"4XNN", 0x4000, 0xF000, &Opcodes::handle4XNN, "Skip the next instruction if VX doesn't equal NN."},
            {"5XY0", 0x5000, 0xF00F, &Opcodes::handle5XY0, "Skip the next instruction if VX equals VY."},
            {"6XNN", 0x6000, 0xF000, &Opcodes::handle6XNN, "Set VX to NN."},
            {"7XNN", 0x7000, 0xF000, &Opcodes::handle7XNN, "Add NN to VX. (Carry flag is not changed)"},
            {"8XY0", 0x8000, 0xF00F, &Opcodes::handle8XY0, "Set VX to the value of VY."},
            {"8XY1", 0x8001, 0xF00F, &Opcodes::handle8XY1, "Set VX to VX or VY. (Bitwise OR operation)"},
            {"8XY2", 0x8002, 0xF00F, &Opcodes::handle8XY2, "Set VX to VX and VY. (Bitwise AND operation)"},
            {"8XY3", 0x8003, 0xF00F, &Opcodes::handle8XY3, "Set VX to VX xor VY."},
            {"8XY4", 0x8004, 0xF00F, &Opcodes::handle8XY4, "Add VY to VX. VF is set to 1 when there's a carry, and to 0 when there isn't."},
            {"8XY5", 0x8005, 0xF00F, &Opcodes::handle8XY5, "VY is subtracted from VX. VF is set to 0 when there's a borrow, and 1 when there isn't."},
            {"8XY6", 0x8006, 0xF00F, &Opcodes::handle8XY6, "Store the least significant bit of VX in VF and then shifts VX to the right by 1"},
            {"8XY7", 0x8007, 0xF00F, &Opcodes::handle8XY7, "Set VX to VY minus VX. VF is set to 0 when there's a borrow, and 1 when there isn't."},
            {"8XYE", 0x800E, 0xF00F, &Opcodes::handle8XYE, "Stores the most significant bit of VX in VF and then shifts VX to the left by 1."},
            {"9XY0", 0x9000, 0xF00F, &Opcodes::handle9XY0, "Skips the next instruction if VX doesn't equal VY."},
            {"ANNN", 0xA000, 0xF000, &Opcodes::handleANNN, "Sets I to the address NNN."},
            {"BNNN", 0xB000, 0xF000, &Opcodes::handleBNNN, "Jumps to the address NNN plus V0."},
            {"CXNN", 0xC000, 0xF000, &Opcodes::handleCXNN, "Sets VX to the result of a bitwise and operation on a random number (Typically: 0 to 255) and NN."},
            {"DXYN", 0xD000, 0xF000, &Opcodes::handleDXYN, "Draws a sprite at coordinate (VX, VY) that has a width of 8 pixels and a height of N pixels."},
            {"EX9E", 0xE09E, 0xF0FF, &Opcodes::handleEX9E, "Skips the next instruction if the key stored in VX is pressed."},
            {"EXA1", 0xE0A1, 0xF0FF, &Opcodes::handleEXA1, "Skips the next instruction if the key stored in VX isn't pressed."},
            {"FX07", 0xF007, 0xF0FF, &Opcodes::handleFX07, "Sets VX to the value of the delay timer."},
            {"FX0A", 0xF00A, 0xF0FF, &Opcodes::handleFX0A, "A key press is awaited, and then stored in VX."},
            {"FX15", 0xF015, 0xF0FF, &Opcodes::handleFX15, "Sets the delay timer to VX."},
            {"FX18", 0xF018, 0xF0FF, &Opcodes::handleFX18, "Sets the sound timer to VX."},
            {"FX1E", 0xF01E, 0xF0FF, &Opcodes::handleFX1E, "Adds VX to I. VF is set to 1 when there is a range overflow, and to 0 when there isn't."},
            {"FX29", 0xF029, 0xF0FF, &Opcodes::handleFX29, "Sets I to the location of the sprite for the character in VX."},
            {"FX33", 0xF033, 0xF0FF, &Opcodes::handleFX33, "Stores the binary-coded decimal representation of VX."},
            {"FX55", 0xF055, 0xF0FF, &Opcodes::handleFX55, "Stores V0 to VX (including VX) in memory starting at address I."},
            {"FX65", 0xF065, 0xF0FF, &Opcodes::handleFX65, "Fills V0 to VX (including VX) with values from memory starting at address I."},
    };

    OpcodeEntry invalid {"----", 0xFFFF, 0xFFFF, &Opcodes::handleInvalid, "Invalid opcode"};

    void handle0NNN(uint16_t opcode);
    void handle00E0(uint16_t opcode);
    void handle00EE(uint16_t opcode);
    void handle1NNN(uint16_t opcode);
    void handle2NNN(uint16_t opcode);
    void handle3XNN(uint16_t opcode);
    void handle4XNN(uint16_t opcode);
    void handle5XY0(uint16_t opcode);
    void handle6XNN(uint16_t opcode);
    void handle7XNN(uint16_t opcode);
    void handle8XY0(uint16_t opcode);
    void handle8XY1(uint16_t opcode);
    void handle8XY2(uint16_t opcode);
    void handle8XY3(uint16_t opcode);
    void handle8XY4(uint16_t opcode);
    void handle8XY5(uint16_t opcode);
    void handle8XY6(uint16_t opcode);
    void handle8XY7(uint16_t opcode);
    void handle8XYE(uint16_t opcode);
    void handle9XY0(uint16_t opcode);
    void handleANNN(uint16_t opcode);
    void handleBNNN(uint16_t opcode);
    void handleCXNN(uint16_t opcode);
    void handleDXYN(uint16_t opcode);
    void handleEX9E(uint16_t opcode);
    void handleEXA1(uint16_t opcode);
    void handleFX07(uint16_t opcode);
    void handleFX0A(uint16_t opcode);
    void handleFX15(uint16_t opcode);
    void handleFX18(uint16_t opcode);
    void handleFX1E(uint16_t opcode);
    void handleFX29(uint16_t opcode);
    void handleFX33(uint16_t opcode);
    void handleFX55(uint16_t opcode);
    void handleFX65(uint16_t opcode);

    void handleInvalid(uint16_t opcode);

    uint16_t getVX(uint16_t opcode);
    uint16_t getVY(uint16_t opcode);
    uint16_t getNN(uint16_t opcode);
    uint16_t getNNN(uint16_t opcode);
};

#endif //CHIP8_OPCODES_H
