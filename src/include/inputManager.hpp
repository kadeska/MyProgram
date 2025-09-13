#pragma once

#include <iostream>
#include <string>

#include "helper.hpp"


int waitForInput(Helper& helper);

bool update();
void stopWaiting();
bool isWaiting();
bool processInput(std::string& input, Helper& helper);
int printPrompt(Helper& helper);
void selectMode(Helper& helper);
