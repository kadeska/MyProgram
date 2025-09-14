#include "include/window.hpp"
#include <SDL3/SDL.h>
#include <iostream>

Window::Window() {}

Window::~Window() {}

bool Window::init(const char* title, int width, int height) {
    // Initialize SDL.
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        // A failure occurred, log the error and exit
        SDL_Log("SDL could not initialize! SDL_Error: %s", SDL_GetError());
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow(title, width, height, 0);
    if (!window) {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        return false;
    }

    // Store window pointer if needed for later use
    // this->window = window;

    return true;
}

void Window::mainLoop() {
    bool running = true;
    SDL_Event event;
    while (running) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_EVENT_QUIT:
                    running = false;
                    break;
                // Handle other events here (keyboard, mouse, etc.)
                default:
                    break;
			}
        }
        // Rendering code here
        SDL_Delay(16); // ~60 FPS
    }
}

void Window::cleanup() {
    // SDL_DestroyWindow(window); // if you stored the pointer
    SDL_Quit();
}