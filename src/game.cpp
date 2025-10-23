#include "include/game.hpp"
#include "include/entity.hpp"

std::vector<std::string> map;

std::unique_ptr<Player> player;

Game::Game(Helper* _helper, IOmanager* _ioMan, InputManager* _inputMan,
    EntityManager* _entityMan, EntityGenerator* _entityGen, MapGenerator* _mapGen)
    : helper(_helper), ioMan(_ioMan), inputMan(_inputMan), entityMan(_entityMan), entityGen(_entityGen),
	mapGen(_mapGen), dt(0.0f),
    level(1), isRunning(true), fixed_delta_time(1.0f / 60.0f), time_accumulator(0.0f),
    last_frame_time(std::chrono::high_resolution_clock::now()), max_updates_per_frame(5)
{
    helper->logAsGame("Initializing game...");
    helper->inGame = true;
    initConsoleBuffer(40, 25); // Set your desired console dimensions

#ifdef _WIN32
    //windows
    mapGen->generateMap(bufferSize.X, bufferSize.Y);

#else
    // linux
	helper->mapGen->generateMap(bufferWidth, bufferHeight);

#endif

    
}

Game::~Game()
{
}

void Game::initEntities()
{
	player = entityGen->generatePlayer("Player 1", EntityTypes::PLAYER);
    int px = getPlayerSpawnLocation().at(0);
    int py = getPlayerSpawnLocation().at(1);
    player->setPosition(px, py);
    helper->logInfo("Created player. ID: " 
        + std::to_string(player->getID()) 
        + "Location: " + std::to_string(px) 
        + " " + std::to_string(py));
}

void Game::initConsoleBuffer(int width, int height) {
#ifdef _WIN32
    // Windows Initialization
    bufferSize = { (short)width, (short)height };
    writeRegion = { 0, 0, (short)(width - 1), (short)(height - 1) };
    backBuffer.resize(width * height);
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
#else
    // Linux Initialization
    bufferWidth = width;
    bufferHeight = height;
    backBuffer.resize(bufferWidth * bufferHeight, ' ');

    // Set up terminal (optional: make it more interactive)
    std::cout << "\033[2J\033[H";  // Clear screen and move cursor to home position

    initscr();              // Initialize ncurses mode
    cbreak();               // Disable line buffering
    noecho();               // Don't echo pressed keys
    keypad(stdscr, TRUE);   // Enable function keys and arrow keys
    nodelay(stdscr, TRUE);  // Make getch non-blocking

#endif
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

    // Check input
	checkInput();
}

void Game::render() {
#ifdef _WIN32
    // Windows-specific rendering
    // 1. Clear the back buffer by filling with empty spaces
    for (size_t i = 0; i < backBuffer.size(); ++i) {
        backBuffer[i].Char.AsciiChar = ' ';
        backBuffer[i].Attributes = FOREGROUND_GREEN; // Set default character color
    }
    //helper->mapGen->generateMap(bufferSize.X, bufferSize.Y);
	

    // 2. Render the map to the back buffer
    mapGen->renderMapToBuffer(backBuffer, bufferSize.X, bufferSize.Y);

    // 3. Write the completed back buffer to the console in one operation
    WriteConsoleOutput(hConsoleOutput, backBuffer.data(), bufferSize, { 0, 0 }, &writeRegion);
#else
    // Linux-specific rendering using ncurses
    // 1. Clear the back buffer by filling with empty spaces
    std::fill(backBuffer.begin(), backBuffer.end(), ' '); // Fill with spaces

    // 2. Render the map to the back buffer
    helper->mapGen->renderMapToBuffer(backBuffer, bufferWidth, bufferHeight);

    // 3. Write the completed back buffer to the console in one operation
    for (int y = 0; y < bufferHeight; ++y) {
        for (int x = 0; x < bufferWidth; ++x) {
            mvaddch(y, x, backBuffer[y * bufferWidth + x]); // Move to (x,y) and add character
        }
    }

    // 4. Refresh the screen to display the new content
    refresh();
#endif
}

void Game::run()
{
    initEntities();

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


void Game::checkInput() 
{
    // input check


#ifdef _WIN32
    if (GetAsyncKeyState(VK_ESCAPE)) { // Check for Escape key
        exit(0);
    }
    if (GetAsyncKeyState('W')) {
        //std::cout << "'W' key is pressed" << std::endl;
        //move player up
		movePlayer(0, -1);
       
    }
    if (GetAsyncKeyState('A')) {
        //std::cout << "'A' key is pressed" << std::endl;
		movePlayer(-1, 0);
    }
    if (GetAsyncKeyState('S')) {
        //std::cout << "'S' key is pressed" << std::endl;
        movePlayer(0, 1);
    }
    if (GetAsyncKeyState('D')) {
        //std::cout << "'D' key is pressed" << std::endl;
        movePlayer(1, 0);
    }
    if (GetAsyncKeyState('E')) {
        std::cout << "'E' key is pressed. Show inventory" << std::endl;
    }
    if (GetAsyncKeyState('F')) {
        std::cout << "'F' key is pressed. Fight" << std::endl;
    }
#else

    int ch = getch();  // Get the pressed key

    if (ch == 27) { // Escape key (ASCII 27)
        endwin();   // End ncurses mode
        exit(0);
    }
    switch (ch) {
    case 'w':
    case 'W':
        std::cout << "'W' key is pressed" << std::endl;
        // Move player
        break;
    case 'a':
    case 'A':
        std::cout << "'A' key is pressed" << std::endl;
        break;
    case 's':
    case 'S':
        std::cout << "'S' key is pressed" << std::endl;
        break;
    case 'd':
    case 'D':
        std::cout << "'D' key is pressed" << std::endl;
        break;
    case 'e':
    case 'E':
        std::cout << "'E' key is pressed" << std::endl;
        break;
    case 'f':
    case 'F':
        std::cout << "'F' key is pressed" << std::endl;
        break;
    default:
        break;  // Do nothing if no recognized key is pressed
    }
#endif
}

// Returns player spawn location as {x, y}
std::vector<int> Game::getPlayerSpawnLocation() {
    // Get player spawn location
    map = mapGen->getMap();

    for (int i = 0; i < map.size(); i++) {
        const auto& row = map.at(i); // Store the row in a variable for clarity
        for (int x = 0; x < row.size(); x++) {
            // Find character 'P' in the map
            if (row.at(x) == mapGen->getTileType().player) {
                helper->logAsGame("Found Location" + std::to_string(x) + " " + std::to_string(i));
                return { x, i }; // Return found location as {x, y}
            }
        }
    }

    return {}; // Return an empty vector if player not found
}

bool Game::movePlayer(int _X, int _Y)
{
	int newX = player->getX() + _X;
    int newY = player->getY() + _Y;

    curTileType = mapGen->getTileType(player->getX(), player->getY());
    nextTileType = mapGen->getTileType(newX, newY);

    if (newX >= mapGen->getMaxX() || newY >= mapGen->getMaxY()) 
    {
        // Out of bounds
        //return false to indicate cant move
        return false;
    }

    if (nextTileType == mapGen->getTileType().solid) 
    {
        // Cant move into solid tile
        return false;
    }

    if (nextTileType == mapGen->getTileType().loot) 
    {
        helper->logAsGame("Player found some loot!");
		// Handle loot pickup logic here
    }



    // Move player
    mapGen->setTileType(player->getX(), player->getY(), mapGen->getTileType().empty);
    player->move(_X, _Y);
    mapGen->setTileType(player->getX(), player->getY(), mapGen->getTileType().player);
    return true;
}
