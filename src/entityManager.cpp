#include "include/entityManager.hpp"

int EntityManager::addEntity(std::unique_ptr<Entity> _entity)
{
	if (_entity)
	{
		helper->logDebug("[EntityManager] Added entity to vector. Entity name= '" + _entity->getName()
			+ "', Entity type= " + std::to_string(_entity->getType()));
		// Use std::move to transfer ownership from the parameter into the vector
		entities.push_back(std::move(_entity));
		return 0;
	}
	return -1;
}

int EntityManager::deleteEntityByID(Entity::EntityID _ID)
{
	// Find the entity with the matching ID
	auto it = std::find_if(entities.begin(), entities.end(),
		[_ID](const std::unique_ptr<Entity>& entity) {
			return entity->getID() == _ID; // Assumes Entity has a getID() method
		});

	if (it != entities.end()) {
		// Erase the unique_ptr from the vector.
		// The unique_ptr's destructor will automatically delete the object.
		entities.erase(it);
		helper->logDebug("[EntityManager] Deleted entity with ID: " + std::to_string(_ID));
	}
	return 0;
}

Entity* EntityManager::getEntityByID(Entity::EntityID _ID)
{
	// Return a raw non-owning pointer for access, or a reference.
	// Do not return a smart pointer that would try to take ownership.
	for (const auto& entity : entities)
	{
		if (entity->getID() == _ID)
		{
			return entity.get(); // get() returns the raw pointer
		}
	}
	return nullptr;
}
