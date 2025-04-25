#pragma once
constexpr unsigned short COORDX_OFFSET = 16;
constexpr unsigned short COORDY_OFFSET = 24;
constexpr unsigned short COORDZ_OFFSET = 32;
constexpr unsigned short FACEX_OFFSET = 84;
constexpr unsigned short MAX_NAMETAG_LENGHT = 16;
constexpr double M_PI = 3.14159265358979323846;

#include "Minecraft.h"

class Entity : public Minecraft {
private:
	static inline bool initialized_ptr = false;

public:
	template<typename T>
	struct Vec3 {
		T x = 0;
		T y = 0;
		T z = 0;
	};

	struct EntityStruct {
		uint32_t entity_ptr = NULL;
		Vec3<double> position;
		std::string entity_type = "";
	};

protected:
	static inline int entityType_offest = NULL;

protected:

	static std::string getMemoryString(const uint64_t& mem, const unsigned int& min_lenght, const unsigned int& max_lenght);

	static void getEntityType(const std::vector<uint8_t>& mem, EntityStruct& entity);

	static void getEntityPosition(const std::vector<uint8_t>& mem, EntityStruct& entity);

	static bool initializeEntity();

public:

	static double getEntityFaceX(const uint64_t& entity);

	static EntityStruct getEntity(const uint32_t& entity, const std::string& target_type, const bool& initialization);
};