#include <iostream>

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
