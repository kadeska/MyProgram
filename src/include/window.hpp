#pragma once

class Window {
public:
    Window();
    ~Window();
    bool init(const char* title, int width, int height);
    void mainLoop();
    void cleanup();
};