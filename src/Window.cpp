#include <iostream>

#include "Window.h"

Window::Window(const std::string& windowTitle, int width, int height) {
    this->windowTitle = windowTitle;
    this->width = width;
    this->height = height;

    this->closed = true;
    this->window = nullptr;
}

void Window::show() {
    if (init()) {
        closed = false;
    }
}

Window::~Window() {
    SDL_DestroyWindow(window);
    SDL_Quit();
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

    return true;
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
