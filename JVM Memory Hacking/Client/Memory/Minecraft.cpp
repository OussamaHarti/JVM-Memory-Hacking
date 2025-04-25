#include "Minecraft.h"
#include "..\Scanner\NtFunctions.h"

bool Minecraft::injectionOnline(const int& start_index, const std::vector<uint8_t>& mem, const uint64_t& base_address) {

	for (size_t i = start_index; i < mem.size() - 20; i += 4) {
		if (Scanner::convertBytes<uint32_t>(mem, i) > MIN_PTR &&
			Scanner::convertBytes<uint32_t>(mem, i + 4) > MIN_PTR &&
			Scanner::convertBytes<uint32_t>(mem, i + 8) > MIN_PTR &&
			Scanner::convertBytes<uint32_t>(mem, i + 12) > MIN_PTR &&
			Scanner::convertBytes<uint32_t>(mem, i + 16) == 0) {

			for (size_t k = i + 20; k < mem.size() - 4; k += 4) {
				if (Scanner::convertBytes<uint32_t>(mem, i + 12) == Scanner::convertBytes<uint32_t>(mem, k)) {
					entityList_ptr = base_address + i + 8;
					localPlayer_ptr = base_address + i + 12;
					return true;
				}
			}
		}
	}

	return false;
};

bool Minecraft::injectionOffline(const int& start_index, const std::vector<uint8_t>& mem, const uint64_t& base_address) {

	for (size_t i = start_index; i < mem.size() - 24; i += 4) {
		if (Scanner::convertBytes<uint32_t>(mem, i) == 0 &&
			Scanner::convertBytes<uint32_t>(mem, i + 4) == 0 &&
			Scanner::convertBytes<uint32_t>(mem, i + 8) == 0 &&
			Scanner::convertBytes<uint32_t>(mem, i + 12) == 0 &&
			Scanner::convertBytes<uint32_t>(mem, i + 16) == 0 &&
			Scanner::convertBytes<uint32_t>(mem, i + 20) == 0) {

			for (size_t k = i + 24; k < mem.size() - 12; k += 4) {
				if (Scanner::convertBytes<uint32_t>(mem, k) > MIN_PTR &&
					Scanner::convertBytes<uint32_t>(mem, k + 4) > MIN_PTR &&
					Scanner::convertBytes<uint32_t>(mem, k + 8) == 0) {
					entityList_ptr = base_address + k - 24;
					localPlayer_ptr = base_address + k - 20;
					return true;
				}
			}
		}
	}

	return false;
};

bool Minecraft::injectClient() {
	const LPVOID start_addr = (LPVOID)INSTR_START_ADDR, end_addr = (LPVOID)INSTR_END_ADDR;
	std::vector<uint64_t> results;

	Scanner::byteScanner(Scanner::minecraft_handle, target, &start_addr, &end_addr, nullptr, nullptr, results, false, nullptr);

	for (auto tmp : results) {
		tmp -= 32;

		std::vector<uint8_t> mem(BASE_SIZE);
		NtFunctions::ReadMemory(Scanner::minecraft_handle, (void*)(tmp), mem.data(), BASE_SIZE, nullptr);

		clientBase_adr = 0x1000000000 * floor(tmp / 0x1000000000); //Adjusts lunar client
		int start_index = 0;

		for (size_t i = 4 - (tmp % 4); i < mem.size() - 12; i += 4) {

			if (Scanner::convertBytes<uint32_t>(mem, i) == 0 &&
				(Scanner::convertBytes<uint32_t>(mem, i + 4) == 0 || Scanner::convertBytes<uint32_t>(mem, i + 4) == 0x2710) &&
				Scanner::convertBytes<uint32_t>(mem, i + 12) > 0 && Scanner::convertBytes<uint32_t>(mem, i + 12) < 0xFFFF &&
				Scanner::convertBytes<uint32_t>(mem, i + 16) == 0 &&
				Scanner::convertBytes<uint32_t>(mem, i + 20) != 0 &&
				clientEntrance_ptr == NULL) {
				clientEntrance_ptr = tmp + i + 4;
			}

			if (clientEntrance_ptr != NULL && ASM_PTR_MULTIPLIER == NULL &&
				Scanner::convertBytes<uint32_t>(mem, i) > MIN_PTR &&
				Scanner::convertBytes<uint32_t>(mem, i + 4) > MIN_PTR &&
				Scanner::convertBytes<uint32_t>(mem, i + 8) > MIN_PTR) {
				start_index = i;
				ASM_PTR_MULTIPLIER = round((double)tmp / (double)Scanner::convertBytes<uint32_t>(mem, i)); //Adjusts different ram settings
			}

			if (ASM_PTR_MULTIPLIER != NULL && (injectionOffline(start_index, mem, tmp) || injectionOnline(start_index, mem, tmp)))
				return true;
		}

		ASM_PTR_MULTIPLIER = 0;
		clientEntrance_ptr = 0;
	}

	return false;
};

uint64_t Minecraft::getClientBase() { return clientBase_adr; };

uint64_t Minecraft::getLocalPlayerAddress(){
	uint32_t buffer = NULL;
	NtFunctions::ReadMemory(Scanner::minecraft_handle, (void*)(localPlayer_ptr), &buffer, sizeof(uint32_t), NULL);
	return (uint64_t)buffer * ASM_PTR_MULTIPLIER + clientBase_adr;
};

uint32_t Minecraft::getLocalPlayerPtr() {
	uint32_t buffer = NULL;
	NtFunctions::ReadMemory(Scanner::minecraft_handle, (void*)(localPlayer_ptr), &buffer, sizeof(uint32_t), NULL);
	return buffer;
};

uint64_t Minecraft::getEntityListAddress() {
	uint32_t bytes_4 = NULL;
	NtFunctions::ReadMemory(Scanner::minecraft_handle, (void*)entityList_ptr, &bytes_4, sizeof(uint32_t), NULL);
	if (bytes_4 == NULL) return NULL;

	if (entityList_offset_one == NULL || (entityList_offset_two == NULL && entityList_offset_three == NULL)) { //Gets the 2 ptrs offsets to entity list
		std::vector<uint8_t> mem(BASE_SIZE);
		NtFunctions::ReadMemory(Scanner::minecraft_handle, (void*)((uint64_t)bytes_4 * ASM_PTR_MULTIPLIER + clientBase_adr + 60), mem.data(), BASE_SIZE, NULL);
		bytes_4 = NULL; //resets the buffer

		for (size_t i = 0; i < mem.size() - 24; i += 4) {
			if (convertBytes<uint32_t>(mem, i) < MIN_PTR && convertBytes<uint32_t>(mem, i + 4) < MIN_PTR && convertBytes<uint32_t>(mem, i + 8) > MIN_PTR &&
				convertBytes<uint32_t>(mem, i + 12) > MIN_PTR && convertBytes<uint32_t>(mem, i + 16) > MIN_PTR && convertBytes<uint32_t>(mem, i + 20) > MIN_PTR) {

				entityList_offset_one = i + 12;
				bytes_4 = convertBytes<uint32_t>(mem, entityList_offset_one);
				entityList_offset_one += 60;
				break;
			}
		}

		if (bytes_4 == NULL)  return NULL;
		uint32_t saver = bytes_4;
		NtFunctions::ReadMemory(Scanner::minecraft_handle, (void*)((uint64_t)bytes_4 * ASM_PTR_MULTIPLIER + clientBase_adr + 12), &bytes_4, sizeof(uint32_t), NULL);
		if (bytes_4 == NULL)  return NULL;

		std::vector<uint8_t> mem_two(BASE_SIZE);
		NtFunctions::ReadMemory(Scanner::minecraft_handle, (void*)((uint64_t)bytes_4 * ASM_PTR_MULTIPLIER + clientBase_adr), mem_two.data(), BASE_SIZE, NULL);
		for (size_t i = 0; i < mem_two.size() - 24; i += 4) {
			if (convertBytes<uint32_t>(mem_two, i) == REDIRECT_PTR && convertBytes<uint32_t>(mem_two, i + 8) > MIN_PTR && convertBytes<uint32_t>(mem_two, i + 12) > MIN_PTR && convertBytes<uint32_t>(mem_two, i + 16) > MIN_PTR) {
				entityList_offset_two = i + 12;
				bytes_4 = convertBytes<uint32_t>(mem_two, entityList_offset_two);
				break;
			}
		}

		NtFunctions::ReadMemory(Scanner::minecraft_handle, (void*)((uint64_t)saver * ASM_PTR_MULTIPLIER + clientBase_adr + 16), &saver, sizeof(uint32_t), NULL);
		if (saver == NULL)  return NULL;

		NtFunctions::ReadMemory(Scanner::minecraft_handle, (void*)((uint64_t)saver * ASM_PTR_MULTIPLIER + 12), &saver, sizeof(uint32_t), NULL);
		if (saver == NULL)  return NULL;
		std::vector<uint8_t> mem_three(BASE_SIZE);

		NtFunctions::ReadMemory(Scanner::minecraft_handle, (void*)((uint64_t)saver * ASM_PTR_MULTIPLIER + clientBase_adr), mem_three.data(), BASE_SIZE, NULL);
		for (size_t i = 0; i < mem_three.size() - 24; i += 4) {
			if (convertBytes<uint32_t>(mem_three, i) == REDIRECT_PTR && convertBytes<uint32_t>(mem_three, i + 8) > MIN_PTR && convertBytes<uint32_t>(mem_three, i + 12) > MIN_PTR && convertBytes<uint32_t>(mem_three, i + 16) > MIN_PTR) {

				entityList_offset_three = i + 12;
				bytes_4 = convertBytes<uint32_t>(mem_three, entityList_offset_three);
				break;
			}
		}

		return (uint64_t)bytes_4 * ASM_PTR_MULTIPLIER + clientBase_adr;
	}
	else {
		NtFunctions::ReadMemory(Scanner::minecraft_handle, (void*)((uint64_t)bytes_4 * ASM_PTR_MULTIPLIER + clientBase_adr + entityList_offset_one), &bytes_4, sizeof(uint32_t), NULL);
		if (bytes_4 == NULL)  return NULL;

		uint32_t saver = bytes_4;
		NtFunctions::ReadMemory(Scanner::minecraft_handle, (void*)((uint64_t)bytes_4 * ASM_PTR_MULTIPLIER + clientBase_adr + 12), &bytes_4, sizeof(uint32_t), NULL);
		if (bytes_4 != NULL) {
			uint32_t check = NULL;
			NtFunctions::ReadMemory(Scanner::minecraft_handle, (void*)((uint64_t)bytes_4 * ASM_PTR_MULTIPLIER + entityList_offset_two - 12), &check, sizeof(uint32_t), NULL);
			if (check == REDIRECT_PTR) {
				NtFunctions::ReadMemory(Scanner::minecraft_handle, (void*)((uint64_t)bytes_4 * ASM_PTR_MULTIPLIER + entityList_offset_two), &bytes_4, sizeof(uint32_t), NULL);
				return (uint64_t)bytes_4 * ASM_PTR_MULTIPLIER + clientBase_adr;
			}
			else entityList_offset_two = NULL;
		}

		NtFunctions::ReadMemory(Scanner::minecraft_handle, (void*)((uint64_t)saver * ASM_PTR_MULTIPLIER + clientBase_adr + 16), &saver, sizeof(uint32_t), NULL);
		if (saver != NULL) {
			NtFunctions::ReadMemory(Scanner::minecraft_handle, (void*)((uint64_t)saver * ASM_PTR_MULTIPLIER + clientBase_adr + 12), &saver, sizeof(uint32_t), NULL);
			if (saver != NULL) {
				uint32_t check = NULL;
				NtFunctions::ReadMemory(Scanner::minecraft_handle, (void*)((uint64_t)saver * ASM_PTR_MULTIPLIER + entityList_offset_three - 12), &check, sizeof(uint32_t), NULL);
				if (check == REDIRECT_PTR) {
					NtFunctions::ReadMemory(Scanner::minecraft_handle, (void*)((uint64_t)saver * ASM_PTR_MULTIPLIER + entityList_offset_three), &saver, sizeof(uint32_t), NULL);
					return (uint64_t)saver * ASM_PTR_MULTIPLIER + clientBase_adr;
				}
				else entityList_offset_three = NULL;
			}
		}
	}

	return NULL;
};