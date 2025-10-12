#pragma once

#include <iostream>
#include <string>
#include <filesystem>
#include "entityTypes.hpp"


class Entity {
public:
	// A lightweight ID for the entity
	using EntityID = unsigned int;
	using EntityType = EntityTypes::Type;
private:
	EntityID id;
	std::string name;
	EntityType type;

public:
	Entity(EntityID _id, std::string _name, EntityType _type) 
		: id(_id), name(_name), type(_type) 
	{
		/*std::cout << "Entity created: ID= " << id << ", Name= '" << name << "', Type= " << std::to_string(type)
		 << std::endl;*/
	}
	~Entity() {}
	EntityID getID() const { return id; }
	void setID(EntityID _id) { id = _id; }
	std::string getName() const { return name; }
	void setType(EntityTypes::Type _type) { type = _type; }
	EntityTypes::Type getType() const { return type; }
};