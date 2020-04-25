#include <iostream>
#include <memory>
#include "Window.h"

int main() {
    std::cout << "Hello, CHIP-8!" << std::endl;

    const auto window = std::make_unique<Window>("CHIP-8", 640, 480);

    while (!window->isClosed()) {
        window->pollEvents();
    }

    std::cout << "Good bye, CHIP-8!" << std::endl;

    return EXIT_SUCCESS;
}
