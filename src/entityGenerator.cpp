#include "include/entityGenerator.hpp"
#include "include/player.hpp"

unsigned int nextEntityID = 0; // Global variable to keep track of the next entity ID

EntityGenerator::EntityGenerator(IOmanager* _ioManager, Helper* _helper)
{
	ioMan = _ioManager;
	helper = _helper;
	seed = 3; // seed for stat generation. Make configurable later.
}

EntityGenerator::~EntityGenerator()
{
}

Entity EntityGenerator::generateEntity(std::string _name, EntityTypes::Type _type)
{
	if (_type == EntityTypes::PLAYER) 
	{
		helper->logAsGenerator("Generating new player");
		Player newPlayer(nextEntityID++, _type, _name, 100, 0, 0);
	}
	Entity newEntity(nextEntityID++, _name, _type);
	helper->logAsGenerator("Generated entity: ID= " + std::to_string(newEntity.getID()) 
		+ ", Name= '" + newEntity.getName() + "', Type= " + std::to_string(newEntity.getType()));
	return newEntity;

}


