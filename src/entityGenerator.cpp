#include "include/entityGenerator.hpp"


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

std::unique_ptr<Entity> EntityGenerator::generateEntity(std::string _name, EntityTypes::Type _type)
{
    // Use a unique_ptr to manage the new object's memory.
    std::unique_ptr<Entity> newEntity;

    if (_type == EntityTypes::PLAYER)
    {
        helper->logAsGenerator("WRONG Generating new player");
        // Use std::make_unique to safely create a Player object on the heap
        //newEntity = std::make_unique<Player>(nextEntityID++, _type, _name, 100, 0, 0);
    }
    else if (_type == EntityTypes::ENEMY) // Assuming you have an ENEMY type
    {
        helper->logAsGenerator("Generating new enemy");
        newEntity = std::make_unique<HostileEntity>(nextEntityID++, _type, _name, 100, 0, 0);
    }
    else
    {
        // Throw an exception for unsupported types
        //throw std::invalid_argument("Unsupported entity type.");
        helper->logError("Unsuported type: " + _type);
    }

    helper->logAsGenerator("Generated entity: ID= " + std::to_string(newEntity->getID())
        + ", Name= '" + newEntity->getName() + "', Type= " + std::to_string(newEntity->getType()));

    return newEntity; // Ownership is transferred to the caller
}

std::unique_ptr<Player> EntityGenerator::generatePlayer(std::string _name, EntityTypes::Type _type, int _x, int _y)
{
    std::unique_ptr<Player> playerEntity;
    if (_type == EntityTypes::PLAYER)
    {
        helper->logAsGenerator("Generating new player");
        // Use std::make_unique to safely create a Player object on the heap
        playerEntity = std::make_unique<Player>(nextEntityID++, _type, _name, 100, _x, _y);
    }
    else {
        // Throw an exception for unsupported types
        //throw std::invalid_argument("Unsupported entity type.");
        helper->logError("Unsuported type: " + _type);
		return nullptr;
	}
    return playerEntity;
}
