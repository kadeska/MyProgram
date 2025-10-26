#include "include/game.hpp"
#include "include/entity.hpp"

//std::vector<std::string> map;

std::unique_ptr<Player> player;

Game::Game(int _mapWidth, int _mapHeight, Helper* _helper, IOmanager* _ioMan, InputManager* _inputMan,
    EntityManager* _entityMan, EntityGenerator* _entityGen, MapGenerator* _mapGen)
    : helper(_helper), ioMan(_ioMan), inputMan(_inputMan), entityMan(_entityMan), entityGen(_entityGen),
	mapGen(_mapGen), dt(0.0f),
    level(1), isRunning(true), fixed_delta_time(10.0f / 12.0f), time_accumulator(0.0f),
    last_frame_time(std::chrono::high_resolution_clock::now()), max_updates_per_frame(3),
	mapWidth(_mapWidth), mapHeight(_mapHeight)
{
    helper->logAsGame("Initializing game...");
    helper->inGame = true;
    initBuffer(40, 25); // Set your desired console dimensions

    initEntities();

    // Generate the map for the game
    mapGen->generateMap(mapWidth, mapHeight);
}

Game::~Game()
{
}

void Game::initEntities()
{
	player = entityGen->generatePlayer("Player 1", EntityTypes::PLAYER, 2, 2);
	mapGen->playerSpawnX = player->getX();
    mapGen->playerSpawnY = player->getY();
    helper->logInfo("Created player. ID: " 
        + std::to_string(player->getID()) 
        + " , Location: " + std::to_string(player->getX()) 
        + " , " + std::to_string(player->getY()));
}

void Game::initBuffer(int width, int height) {
    // Rework buffer
//#ifdef _WIN32
//    // Windows Initialization
//    bufferSize = { (short)width, (short)height };
//    writeRegion = { 0, 0, (short)(width - 1), (short)(height - 1) };
//    backBuffer.resize(width * height);
//    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
//#else
//    // Linux Initialization
//    bufferWidth = width;
//    bufferHeight = height;
//    backBuffer.resize(bufferWidth * bufferHeight, ' ');
//
//    // Set up terminal (optional: make it more interactive)
//    std::cout << "\033[2J\033[H";  // Clear screen and move cursor to home position
//
//    initscr();              // Initialize ncurses mode
//    cbreak();               // Disable line buffering
//    noecho();               // Don't echo pressed keys
//    keypad(stdscr, TRUE);   // Enable function keys and arrow keys
//    nodelay(stdscr, TRUE);  // Make getch non-blocking
//
//#endif


    mapGen->setMapBuffer();


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
    // clear screen
    clear();
    // 1. Clear the buffer
    mapGen->setMapBuffer();
	
    // 2. send the current map to the buffer
    mapGen->sendMapToBuffer();

    // 3. Write the completed  buffer to the console in one operation
    helper->log(mapGen->getMapBuffer());
}

void Game::run()
{
    //initEntities();

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
            render();
            time_accumulator -= fixed_delta_time;
            updates_this_frame++;
        }

        if (updates_this_frame >= max_updates_per_frame) {
            helper->logAsGame("WARNING: Fixed update is falling behind!");
        }
        
        // Perform rendering
        //render();

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
    //map = mapGen->getMap();

    for (int x = 0; x <= mapWidth-1; x++) {
        //const auto& row = mapBuffer[x]; // Store the row in a variable for clarity
        for (int y = 0; y <= mapHeight-1; y++) {
            // Find character 'P' in the map
            helper->log(std::to_string(mapGen->getMap()[x][y].tile));
            if (mapGen->getMap()[x][y].tile == mapGen->tileList.player.tile) {
                helper->logAsGame("Found Location" + std::to_string(x) + " " + std::to_string(y));
                return { x, y }; // Return found location as {x, y}
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


    ioMan->printToLogFile("Current Tile Type: " + std::string(1, curTileType) 
		+ " Next Tile Type: " + std::string(1, nextTileType));
	ioMan->printToLogFile("Player Position: X=" + std::to_string(player->getX()) 
        + ", Y=" + std::to_string(player->getY()));


    if (newX < 0 || newX >= mapGen->getMaxX() || newY < 0 || newY >= mapGen->getMaxY())
    {
        // Out of bounds
		 ioMan->printToLogFile("MaxX: " + std::to_string(mapGen->getMaxX()) 
             + " , MaxY: " + std::to_string(mapGen->getMaxY()));
        //return false to indicate cant move
        return false;
    }

    if (nextTileType == mapGen->tileList.solid.tile) 
    {
        // Cant move into solid tile
		helper->logAsGame("Player tried to move into a solid tile!");
        return false;
    }

    if (nextTileType == mapGen->tileList.loot.tile) 
    {
        helper->logAsGame("Player found some loot!");
		// Handle loot pickup logic here
    }



    // Move player
    mapGen->setTile(player->getX(), player->getY(), mapGen->tileList.empty);
    player->move(_X, _Y);
    mapGen->setTile(player->getX(), player->getY(), mapGen->tileList.player);
    return true;
}
