#ifndef CHIP8_OPCODES_H
#define CHIP8_OPCODES_H

#include <cstdint>
#include <string>
#include <vector>

class Opcodes {

public:
    struct OpcodeEntry {
        std::string name;
        uint16_t opcode;
        uint16_t mask;
        std::string description;
    };

    OpcodeEntry findOpcode(uint16_t opcode);

private:
    std::vector<OpcodeEntry> opcodeEntries = {
            {"0NNN", 0x0000, 0xF000, "Call RCA 1802 program at address NNN."}, // TODO order
            {"00E0", 0x00E0, 0xFFFF, "Clear screen."},
            {"00EE", 0x00EE, 0xFFFF, "Return from subroutine."},
            {"1NNN", 0x1000, 0xF000, "Jump to address NNN."},
            {"2NNN", 0x2000, 0xF000, "Call subroutine at NNN."},
            {"3XNN", 0x3000, 0xF000, "Skip the next instruction if VX equals NN."},
            {"4XNN", 0x4000, 0xF000, "Skip the next instruction if VX doesn't equal NN."},
            {"5XY0", 0x5000, 0xF00F, "Skip the next instruction if VX equals VY."},
            {"6XNN", 0x6000, 0xF000, "Set VX to NN."},
            {"7XNN", 0x7000, 0xF000, "Add NN to VX. (Carry flag is not changed)"},
            {"8XY0", 0x8000, 0xF00F, "Set VX to the value of VY."},
            {"8XY1", 0x8001, 0xF00F, "Set VX to VX or VY. (Bitwise OR operation)"},
            {"8XY2", 0x8002, 0xF00F, "Set VX to VX and VY. (Bitwise AND operation)"},
            {"8XY3", 0x8003, 0xF00F, "Set VX to VX xor VY."},
            {"8XY4", 0x8004, 0xF00F, "Add VY to VX. VF is set to 1 when there's a carry, and to 0 when there isn't."},
            {"8XY5", 0x8005, 0xF00F, "VY is subtracted from VX. VF is set to 0 when there's a borrow, and 1 when there isn't."},
            {"8XY6", 0x8006, 0xF00F, "Store the least significant bit of VX in VF and then shifts VX to the right by 1"},
            {"8XY7", 0x8007, 0xF00F, "Set VX to VY minus VX. VF is set to 0 when there's a borrow, and 1 when there isn't."},
            {"8XYE", 0x800E, 0xF00F, "Stores the most significant bit of VX in VF and then shifts VX to the left by 1."},
            {"9XY0", 0x9000, 0xF00F, "Skips the next instruction if VX doesn't equal VY."},
            {"ANNN", 0xA000, 0xF000, "Sets I to the address NNN."},
            {"BNNN", 0xB000, 0xF000, "Jumps to the address NNN plus V0."},
            {"CXNN", 0xC000, 0xF000, "Sets VX to the result of a bitwise and operation on a random number (Typically: 0 to 255) and NN."},
            {"DXYN", 0xD000, 0xF000, "Draws a sprite at coordinate (VX, VY) that has a width of 8 pixels and a height of N pixels."},
            {"EX9E", 0xE09E, 0xF0FF, "Skips the next instruction if the key stored in VX is pressed."},
            {"EXA1", 0xE0A1, 0xF0FF, "Skips the next instruction if the key stored in VX isn't pressed."},
            {"FX07", 0xF007, 0xF0FF, "Sets VX to the value of the delay timer."},
            {"FX0A", 0xF00A, 0xF0FF, "A key press is awaited, and then stored in VX."},
            {"FX15", 0xF015, 0xF0FF, "Sets the delay timer to VX."},
            {"FX18", 0xF018, 0xF0FF, "Sets the sound timer to VX."},
            {"FX1E", 0xF01E, 0xF0FF, "Adds VX to I. VF is set to 1 when there is a range overflow, and to 0 when there isn't."},
            {"FX29", 0xF029, 0xF0FF, "Sets I to the location of the sprite for the character in VX."},
            {"FX33", 0xF033, 0xF0FF, "Stores the binary-coded decimal representation of VX."},
            {"FX55", 0xF055, 0xF0FF, "Stores V0 to VX (including VX) in memory starting at address I."},
            {"FX65", 0xF065, 0xF0FF, "Fills V0 to VX (including VX) with values from memory starting at address I."},
    };

    OpcodeEntry invalid {"----", 0xFFFF, 0xFFFF, "Invalid opcode"};
};

#endif //CHIP8_OPCODES_H
