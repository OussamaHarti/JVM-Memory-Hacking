#include "World.h"

std::vector<Entity::EntityStruct> World::getEntityList(const std::string& target_type) {
	uint64_t tmp = getEntityListAddress();
	if (tmp == NULL) return std::vector<EntityStruct>{};

	std::vector<uint8_t> mem(ENTITY_LIST_SIZE);
	NtFunctions::ReadMemory(Scanner::minecraft_handle, (void*)tmp, mem.data(), ENTITY_LIST_SIZE, NULL);
	uint32_t localPlayer = getLocalPlayerPtr();

	std::vector<EntityStruct> tmp_list;

	//Gets all EntityStruct
	for (size_t i = 16; i < mem.size() - 8; i += 4) {
		uint32_t buffer = convertBytes<uint32_t>(mem, i);
		if (buffer == convertBytes<uint32_t>(mem, 0) || (buffer != 0 && buffer < MIN_PTR)) break;
		if (buffer > MIN_PTR && buffer != localPlayer) { //First entity is local player
			EntityStruct tmp_entity = getEntity(buffer, target_type, false);
			tmp_list.push_back(tmp_entity);
		}
	}

	return tmp_list;
};