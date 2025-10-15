#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <memory>

#include "helper.hpp"
#include "entity.hpp"
#include "player.hpp"

class EntityManager 
{
private:
	std::vector<std::unique_ptr<Entity>> entities;
	Helper* helper;

public:
	EntityManager(Helper* _helper) : helper(_helper) {}
	~EntityManager() = default;
	int addEntity(std::unique_ptr<Entity> _entity);
	int deleteEntityByID(Entity::EntityID _ID);
	Entity* getEntityByID(Entity::EntityID _ID);
	void printAllEntities();
	void printEntity(Entity::EntityID _ID);

};