#pragma once

#include "entity.hpp"

class HostileEntity : public Entity
{
private:
	/**
	* @brief The health attribute represents the entity's current health points.
	*/
	int health;

	/**
	* @brief The (x, y) coordinates represent the entity's position on a 2D grid or map.
	*/
	int x, y;

	/**
	* @brief The attack power attribute determines the damage dealt to
	* other entities during an attack.
	*/
	int attackPower;

	/**
	* @brief The defense attribute reduces incoming damage from attacks by percentage.
	*/
	int defense;

	/**
	* @brief Modifier value that adjusts the entity's attributes or behaviors.
	*
	*
	* The modifier can be positive or negative, affecting aspects such as:
	*
	* - Attack Power
	* - Defense
	* - Speed
	* - Health Regeneration
	* - Critical Hit Chance
	*/
	int modifier;
public:
	HostileEntity(EntityID _id, Entity::EntityType _type, std::string _name, int _health, int _x, int _y)
		: Entity(_id, _name, _type), health(_health), x(_x), y(_y) {
	}
	~HostileEntity() {}

	// getters

	EntityID getID() const { return Entity::getID(); }
	int getX() const { return x; }
	int getY() const { return y; }
	int getHealth() const { return health; }
	int getAttackPower() { return attackPower; }
	int getDefense() { return defense; }
	int getModifier() { return modifier; }


	// setters 

	void setHealth(int _health) { health = _health; }
	void setPosition(int _x, int _y) { x = _x; y = _y; }
	void setAttackPower(int _attackPower) { attackPower = _attackPower; }
	void setDefense(int _defense) { defense = _defense; }
	void setModifier(int _modifier) { modifier = _modifier; }

	// functions

	void move(int deltaX, int deltaY) {
		x += deltaX;
		y += deltaY;
	}
	void hunt();
};