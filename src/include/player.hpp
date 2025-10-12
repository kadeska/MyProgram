#pragma once
#include <iostream>
#include <string>

#include "entity.hpp"

class Player : public Entity {
private:
	int health;
	int x, y; // Player position on the map

public:
	Player(EntityID _id, Entity::EntityType _type, std::string _name, int _health, int _x, int _y)
		: Entity(_id, _name, _type), health(_health), x(_x), y(_y) {
		/*std::cout << "Player created: ID= " << getID() << ", Name= '" << _name 
			<< "', Health= " << health << ", Position= (" << x << ", " << y << ")" << std::endl;*/
	}
	~Player() {}
	EntityID getID() const { return Entity::getID(); }
	int getHealth() const { return health; }
	void setHealth(int _health) { health = _health; }
	int getX() const { return x; }
	int getY() const { return y; }
	void setPosition(int _x, int _y) { x = _x; y = _y; }
	void move(int deltaX, int deltaY) {
		x += deltaX;
		y += deltaY;
	}

};