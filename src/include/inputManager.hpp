#pragma once

#include <iostream>
#include <string>

#include "helper.hpp"
#include "mapGenerator.hpp"
#include "IOmanager.hpp"

class inputManager {
	//mapGenerator mapGen;
public:
	void initInputManager(Helper* _helper, IOmanager* _ioManager, mapGenerator* _mapGen);

	int waitForInput();

	bool update();
	void stopWaiting();
	bool isWaiting();
	bool processInput(std::string& input);
	int printPrompt();
	void selectMode();

	Helper* helper;
	IOmanager* ioManager;
	mapGenerator* mapGen;
};
