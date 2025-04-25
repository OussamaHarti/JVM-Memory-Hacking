#pragma once
#include <stdint.h>
constexpr unsigned short BASE_SIZE = 1000;
constexpr unsigned short ENTITY_LIST_SIZE = 1500;

#include "..\Scanner\Scanner.h"

class Minecraft: public Scanner {
protected:
	static inline unsigned short ASM_PTR_MULTIPLIER = 0;

private:
	static inline uint64_t clientEntrance_ptr, clientBase_adr, localPlayer_ptr, entityList_ptr;
	static inline const std::string target = "01 01 00 00 00 00 01 00 00 00 01";
	static inline int entityList_offset_one, entityList_offset_two, entityList_offset_three;

private:
	static bool injectionOnline(const int& start_index, const std::vector<uint8_t>& mem, const uint64_t& base_address);

	static bool injectionOffline(const int& start_index, const std::vector<uint8_t>& mem, const uint64_t& base_address);

public:

	static bool injectClient();

public:

	static uint64_t getClientBase();

	static uint64_t getLocalPlayerAddress();

	static uint32_t getLocalPlayerPtr();

	static uint64_t getEntityListAddress();
};