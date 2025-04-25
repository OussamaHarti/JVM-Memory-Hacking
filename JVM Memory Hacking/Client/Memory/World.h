#pragma once
#include "Entity.h"

class World : private Entity {

private:

	World() {};

public:

	static std::vector<Entity::EntityStruct> getEntityList(const std::string& target_type);
};


