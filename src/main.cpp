#include <iostream>
#include <memory>

#include "Chip8.h"

int main(int argc, char **argv) {
    std::cout << "Hello, CHIP-8!" << std::endl;

    if (argc != 2) {
        std::cerr << "Usage: chip8 <rom.ch8>" << std::endl;
        return EXIT_FAILURE;
    }

    std::string fileName = argv[1];
    const auto chip8 = std::make_unique<Chip8>();
    chip8->run(fileName);

    std::cout << "Good bye, CHIP-8!" << std::endl;

    return EXIT_SUCCESS;
}
