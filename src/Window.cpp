#include <iostream>

#include "Window.h"

Window::Window(const std::string& windowTitle, int scale) {
    this->windowTitle = windowTitle;
    this->scale = scale;
    this->width = ORIGINAL_WIDTH * scale;
    this->height = ORIGINAL_HEIGHT * scale;

    this->closed = true;
    this->window = nullptr;
    this->renderer = nullptr;

    std::cout << "Window in" << std::endl;
}

Window::~Window() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    std::cout << "Window out" << std::endl;
}

void Window::show() {
    if (init()) {
        closed = false;
    }
}

bool Window::init() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL Init video failed: " << SDL_GetError() << std::endl;
        return false;
    }

    window = SDL_CreateWindow(
            windowTitle.c_str(),
            SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,
            width, height,
            SDL_WINDOW_ALLOW_HIGHDPI
    );

    if (window == nullptr) {
        std::cerr << "SDL Window failed: " << SDL_GetError() << std::endl;
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (renderer == nullptr) {
        std::cerr << "SDL Renderer failed: " << SDL_GetError() << std::endl;
        return false;
    }

    return true;
}

void Window::clearScreen() {
    // Fills screen with black
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
}

void Window::pollEvents() {
    SDL_Event windowEvent;

    if (SDL_PollEvent(&windowEvent)) {
        if (windowEvent.type == SDL_QUIT) {
            closed = true;
        }
    }
}

bool Window::isClosed() const {
    return closed;
}
