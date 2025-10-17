[game]: https://github.com/kadeska/MyProgram/blob/main/images/DefaultRunNoArgs.png "game"
[default]: https://github.com/kadeska/MyProgram/blob/main/images/defaultArgument.png "default"
[server]: https://github.com/kadeska/MyProgram/blob/main/images/server.png "server"
[client]: https://github.com/kadeska/MyProgram/blob/main/images/client.png "client"



# MyProgram
Some console app


## What is this for?
* Deploy server/client
* Generate server/client data
* Generate 2D maps
* Generate characters
* Launch game

## Dependencies 
* sudo apt-get install libncurses5-dev libncursesw5-dev

## Build and Run
* Build with CMake
* * In the root dir configure Cmake using "cmake -S . -B build/release"
* * Then use "cmake --build build/release --config Release" to build
* * Run using "./MyProgram" or "./MyProgram <server/client/default>"
  * For linux, after building run this command in the root dir "./build/bin/Release/MyProgram <server/client/default>"


## Screenshots
* Executing the program without cmd arguments will bring you straight into the game. The following screen shot shows the current state of the game. A 2d map is generated with player and loot.

![alt text][game]

* Run the program in a cmd prompt with cmd argument 'default' will prompt you with something like this

![alt text][default]

* Run the program in a cmd prompt with cmd argument 'server' will prompt you with something like this

![alt text][server]

* Run the program in a cmd prompt with cmd argument 'client' will prompt you with something like this

![alt text][client]

* enter 'map' command and the program will generate a 2D map using a cellular automata algorithm.
* * (as of right now) this has been moved to be used in the game generation. Later I will add a map generation system for making custom maps.

