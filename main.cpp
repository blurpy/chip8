#include <iostream>
#include "SDL2/SDL.h"

int main() {
    std::cout << "Hello, CHIP-8!" << std::endl;

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL Init video failed: " << SDL_GetError() << std::endl;
        return EXIT_FAILURE;
    }

    SDL_Window *window = SDL_CreateWindow(
            "CHIP-8",
            SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,
            640,480,
            SDL_WINDOW_ALLOW_HIGHDPI
    );

    if (window == nullptr) {
        std::cerr << "SDL Window failed: " << SDL_GetError() << std::endl;
        return EXIT_FAILURE;
    }

    SDL_Event windowEvent;

    while (true) {
        if (SDL_PollEvent(&windowEvent)) {
            if (windowEvent.type == SDL_QUIT) {
                break;
            }
        }
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    std::cout << "Good bye, CHIP-8!" << std::endl;

    return EXIT_SUCCESS;
}
