#include <iostream>
#include <utility>

#include "Window.h"

Window::Window(std::string windowTitle, int scale, std::shared_ptr<Keyboard> keyboard) :
windowTitle(std::move(windowTitle)), scale(scale), keyboard(std::move(keyboard)) {
    this->width = ORIGINAL_WIDTH * scale;
    this->height = ORIGINAL_HEIGHT * scale;

    this->closed = true;
    this->dirty = false;

    this->pixelSize = sizeof(uint32_t); // Should match SDL_PIXELFORMAT_ARGB8888
    this->pixels = std::vector<uint8_t>(width * height * pixelSize);

    this->window = nullptr;
    this->renderer = nullptr;
    this->texture = nullptr;

    std::cout << "Window in" << std::endl;
}

Window::~Window() {
    SDL_DestroyTexture(texture);
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

    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, width, height);

    if (texture == nullptr) {
        std::cerr << "SDL Texture failed: " << SDL_GetError() << std::endl;
        return false;
    }

    return true;
}

/**
 * Graphics are drawn to the screen solely by drawing sprites, which are 8 pixels wide and may be
 * from 1 to 15 pixels in height. Sprite pixels are XOR'd with corresponding screen pixels.
 * In other words, sprite pixels that are set flip the color of the corresponding screen pixel,
 * while unset sprite pixels do nothing.
 *
 * @param x coordinate of pixel.
 * @param y coordinate of pixel.
 * @return If any screen pixels are flipped from set to unset.
 */
bool Window::drawSpritePixel(unsigned int x, unsigned int y) {
    unsigned int offset = (width * pixelSize * y) + (pixelSize * x);

    int originalColor = pixels[offset];
    int newColor = pixels[offset] ^ WHITE;

    // A bit overkill, but ARGB pixels drawn as either 0 (black) or 255 (white) and no transparency
    pixels[offset + 0] = newColor; // b
    pixels[offset + 1] = newColor; // g
    pixels[offset + 2] = newColor; // r
    pixels[offset + 3] = SDL_ALPHA_OPAQUE; // a

    dirty = true;

    return originalColor == WHITE && originalColor != newColor;
}

/**
 * Transfers current pixels to the screen, according to specified scale.
 */
void Window::redraw() {
    if (!dirty) {
        return;
    }

    SDL_Rect textureSize = {0, 0, ORIGINAL_WIDTH, ORIGINAL_HEIGHT};
    SDL_Rect windowSize = {0, 0, width, height};

    SDL_RenderClear(renderer);
    SDL_UpdateTexture(texture, nullptr, &pixels[0], width * pixelSize);
    SDL_RenderCopy(renderer, texture, &textureSize, &windowSize);
    SDL_RenderPresent(renderer);

    dirty = false;
}

/**
 * Fills screen with black.
 */
void Window::clearScreen() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);

    for (uint8_t &pixel : pixels) {
        pixel = 0;
    }

    dirty = false;
}

void Window::pollEvents() {
    SDL_Event windowEvent;

    if (SDL_PollEvent(&windowEvent)) {
        if (windowEvent.type == SDL_QUIT) {
            closed = true;
        } else if (windowEvent.type == SDL_KEYUP) {
            keyboard->handleKeyUp(windowEvent.key);
        } else if (windowEvent.type == SDL_KEYDOWN) {
            keyboard->handleKeyDown(windowEvent.key);
        }
    }
}

bool Window::isClosed() const {
    return closed;
}
