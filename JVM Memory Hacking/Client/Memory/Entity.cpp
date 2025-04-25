#include "Entity.h"
#include "..\Scanner\Scanner.h"

#include <chrono>
#include <thread>

std::string Entity::getMemoryString(const uint64_t& mem, const unsigned int& min_lenght, const unsigned int& max_lenght) {
	if (max_lenght == 0 || mem < MIN_PTR) return std::string{};

	const short offset = 4;
	size_t size = offset + max_lenght + 4;
	std::vector<uint8_t> saver(size);
	NtFunctions::ReadMemory(Scanner::minecraft_handle, (void*)(mem + 12), saver.data(), size, NULL);
	uint32_t mem_size = convertBytes<uint32_t>(saver, 0);

	if (mem_size >= min_lenght && mem_size <= max_lenght)
		return std::string(reinterpret_cast<const char*>(saver.data() + offset), mem_size);

	return std::string{};
};

void Entity::getEntityType(const std::vector<uint8_t>& mem, EntityStruct& entity) {
	uint32_t buffer = NULL;

	if (entityType_offest == NULL) {
		for (int i = 0; i < mem.size() - 80; i += 4) {
			if (convertBytes<uint32_t>(mem, i + 4) > MIN_PTR &&
				convertBytes<uint32_t>(mem, i + 12) == 0 && convertBytes<uint32_t>(mem, i + 16) > MIN_PTR &&
				convertBytes<uint32_t>(mem, i + 44) == 0 && convertBytes<uint32_t>(mem, i + 48) > MIN_PTR &&
				convertBytes<uint32_t>(mem, i + 72) == 0 && convertBytes<uint32_t>(mem, i + 76) > MIN_PTR) {
				entityType_offest = i + 4;
				buffer = convertBytes<uint32_t>(mem, entityType_offest);
				break;
			}
		}
	}
	else NtFunctions::ReadMemory(Scanner::minecraft_handle, (void*)((uint64_t)entity.entity_ptr * ASM_PTR_MULTIPLIER + getClientBase() + entityType_offest), &buffer, sizeof(uint32_t), NULL);

	if (buffer != NULL) {
		NtFunctions::ReadMemory(Scanner::minecraft_handle, (void*)((uint64_t)buffer * ASM_PTR_MULTIPLIER + getClientBase() + 24), &buffer, sizeof(uint32_t), NULL);
		NtFunctions::ReadMemory(Scanner::minecraft_handle, (void*)((uint64_t)buffer * ASM_PTR_MULTIPLIER + getClientBase() + 24), &buffer, sizeof(uint32_t), NULL);
		NtFunctions::ReadMemory(Scanner::minecraft_handle, (void*)((uint64_t)buffer * ASM_PTR_MULTIPLIER + getClientBase() + 16), &buffer, sizeof(uint32_t), NULL);
		uint32_t tmp_buffer = NULL;
		NtFunctions::ReadMemory(Scanner::minecraft_handle, (void*)((uint64_t)buffer * ASM_PTR_MULTIPLIER + getClientBase() + 20), &tmp_buffer, sizeof(uint32_t), NULL);

		if (tmp_buffer < MIN_PTR) NtFunctions::ReadMemory(Scanner::minecraft_handle, (void*)((uint64_t)buffer * ASM_PTR_MULTIPLIER + getClientBase() + 16), &buffer, sizeof(uint32_t), NULL);
		else buffer = tmp_buffer;

		NtFunctions::ReadMemory(Scanner::minecraft_handle, (void*)((uint64_t)buffer * ASM_PTR_MULTIPLIER + getClientBase() + 20), &buffer, sizeof(uint32_t), NULL);
		if (buffer < MIN_PTR) return;

		entity.entity_type = getMemoryString((uint64_t)buffer * ASM_PTR_MULTIPLIER + getClientBase(), 0, 30);
	}
};

void Entity::getEntityPosition(const std::vector<uint8_t>& mem, EntityStruct& entity) {
	entity.position.x = convertBytes<double>(mem, COORDX_OFFSET);
	entity.position.y = convertBytes<double>(mem, COORDY_OFFSET);
	entity.position.z = convertBytes<double>(mem, COORDZ_OFFSET);
};

double Entity::getEntityFaceX(const uint64_t& entity) {
	if (entity != NULL) {
		float face_x = NULL;
		NtFunctions::ReadMemory(Scanner::minecraft_handle, (void*)(entity + FACEX_OFFSET), &face_x, sizeof(float), NULL);

		int divider_x = (face_x != 0) ? floor(abs(face_x) / 360) : 0;
		if (face_x >= 0) {
			face_x = face_x - (360 * divider_x); //set back to a max value of 360
			if (face_x > 180) face_x = -360 + face_x; //checks the value
		}
		else {
			face_x = face_x + (360 * divider_x);
			if (face_x < -180) face_x = 360 + face_x;
		}
		return face_x;
	}
	else return NULL;
};

bool Entity::initializeEntity() {
	uint32_t tmp = Minecraft::getLocalPlayerPtr();

	if (tmp != NULL) {
		getEntity(tmp, std::string{}, true);
		return true;
	}

	return false;
};

Entity::EntityStruct Entity::getEntity(const uint32_t& entity, const std::string& target_type, const bool& initialization) {
	if (entity < MIN_PTR) return EntityStruct{};

	if (!initialized_ptr && !initialization) { //Uses local player to set pointers offsets
		initialized_ptr = initializeEntity();
		if (!initialized_ptr) return EntityStruct{};
	}

	EntityStruct tmp_entity;
	tmp_entity.entity_ptr = entity;

	std::vector<uint8_t> mem(ENTITY_LIST_SIZE);
	NtFunctions::ReadMemory(Minecraft::minecraft_handle, (void*)((uint64_t)entity * ASM_PTR_MULTIPLIER + getClientBase()), mem.data(), ENTITY_LIST_SIZE, NULL);

	getEntityType(mem, tmp_entity);
	if (target_type == "player" && tmp_entity.entity_type != "zombie") { //Detection error handling
		if (!target_type.empty() && tmp_entity.entity_type != target_type || tmp_entity.entity_type == "armor_stand") return tmp_entity;
	}

	getEntityPosition(mem, tmp_entity);

	return tmp_entity;
};