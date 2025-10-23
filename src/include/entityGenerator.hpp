#pragma once

#include <iostream>
#include <string>
#include <filesystem>

#include "helper.hpp"
#include "IOmanager.hpp"
#include "entity.hpp"
#include "entityTypes.hpp"
#include "player.hpp"
#include "include/hostileEntity.hpp"

class EntityGenerator {
private:
	IOmanager* ioMan;
	Helper* helper;
	int seed;

public:

	EntityGenerator(IOmanager* _ioManager, Helper* _helper);
	~EntityGenerator();
	std::unique_ptr<Entity> generateEntity(std::string _name, EntityTypes::Type _type);
	std::unique_ptr<Player> generatePlayer(std::string _name, EntityTypes::Type _type);
};