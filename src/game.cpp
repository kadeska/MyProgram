#include "include/game.hpp"

Game::Game(Helper* _helper, IOmanager* _ioMan, inputManager* _inputMan,
    EntityManager* _entityMan, EntityGenerator* _entityGen)
    : helper(_helper), ioMan(_ioMan), inputMan(_inputMan), entityMan(_entityMan), entityGen(_entityGen),
    level(1), isRunning(true), fixed_delta_time(1.0f / 60.0f), time_accumulator(0.0f),
    last_frame_time(std::chrono::high_resolution_clock::now()), max_updates_per_frame(5)
{
    helper->logAsGame("Initializing game...");
    helper->inGame = true;
    initConsoleBuffer(40, 25); // Set your desired console dimensions
    helper->mapGen->generateMap(bufferSize.X, bufferSize.Y);
}

Game::~Game()
{
}

void Game::initConsoleBuffer(int width, int height) {
    bufferSize = { (short)width, (short)height };
    writeRegion = { 0, 0, (short)(width - 1), (short)(height - 1) };
    backBuffer.resize(width * height);
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
}

void Game::update() {
    // All fixed game logic goes here
    // e.g., entityMan->update(fixed_delta_time);

    // For testing, generate a new map every few seconds
    //static float mapGenerationTimer = 0.0f;
    //mapGenerationTimer += fixed_delta_time;
    //if (mapGenerationTimer >= 0.50f) { // Generate a new map every 2 seconds
    //    helper->logAsGame("Generating a new map...");
    //    helper->mapGen->generateMap(bufferSize.X, bufferSize.Y);
    //    mapGenerationTimer = 0.0f; // Reset the timer
    //}


    if (GetAsyncKeyState(VK_ESCAPE)) { // Check for Escape key
		exit(0);
    }
    if (GetAsyncKeyState('W')) {
        std::cout << "'W' key is pressed" << std::endl;
        //move player
    }
    if (GetAsyncKeyState('A')) {
        std::cout << "'A' key is pressed" << std::endl;
    }
    if (GetAsyncKeyState('S')) {
        std::cout << "'S' key is pressed" << std::endl;
    }
    if (GetAsyncKeyState('D')) {
        std::cout << "'D' key is pressed" << std::endl;
    }
    if (GetAsyncKeyState('E')) {
        std::cout << "'E' key is pressed" << std::endl;
    }
    if (GetAsyncKeyState('F')) {
        std::cout << "'F' key is pressed" << std::endl;
    }
}

void Game::render() {
    
    // 1. Clear the back buffer by filling with empty spaces
    for (size_t i = 0; i < backBuffer.size(); ++i) {
        backBuffer[i].Char.AsciiChar = ' ';
        backBuffer[i].Attributes = FOREGROUND_GREEN;
    }

    // 2. Render the map to the back buffer
    helper->mapGen->renderMapToBuffer(backBuffer, bufferSize.X, bufferSize.Y);

    // 3. Write the completed back buffer to the console in one operation
    WriteConsoleOutput(hConsoleOutput, backBuffer.data(), bufferSize, { 0, 0 }, &writeRegion);
    /*clear();*/
}

void Game::run()
{
    clear();
    //helper->logAsGame("Game starting...");

    // Use a fixed time point for sleep_until for better accuracy
    auto next_frame_time = std::chrono::high_resolution_clock::now();
    const auto render_rate = std::chrono::microseconds(16667); // Approx 60 fps

    while (isRunning)
    {
        // Calculate variable delta time
        auto current_frame_time = std::chrono::high_resolution_clock::now();
        std::chrono::duration<float> delta_time_duration = current_frame_time - last_frame_time;
        float delta_time = delta_time_duration.count();
        last_frame_time = current_frame_time;

        // Add to accumulator
        time_accumulator += delta_time;

        // Perform fixed updates
        int updates_this_frame = 0;
        while (time_accumulator >= fixed_delta_time && updates_this_frame < max_updates_per_frame) {
            update();
            time_accumulator -= fixed_delta_time;
            updates_this_frame++;
        }

        if (updates_this_frame >= max_updates_per_frame) {
            helper->logAsGame("WARNING: Fixed update is falling behind!");
        }

        // Perform rendering
        render();

        // Cap the frame rate
        next_frame_time += render_rate;
        std::this_thread::sleep_until(next_frame_time);
    }
}
