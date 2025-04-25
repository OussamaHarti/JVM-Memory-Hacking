#include "Scanner.h"
#include "..\Utils\Utils.h"

#include <iostream>
#include <unordered_set>
#include <sstream>
#include <chrono>
#include <thread>
#include <tlhelp32.h>

std::vector<std::pair<Scanner::markPos, uint8_t>> Scanner::initPattern(const std::string& patter) {
    std::vector<std::pair<markPos, uint8_t>> buffer;
    std::istringstream iss(patter);
    std::string byte_tmp;

    while (std::getline(iss, byte_tmp, ' ')) {

        if (byte_tmp[0] == '?' && (byte_tmp[1] == '?')) {
            buffer.push_back(std::make_pair(BOTH, NULL));
        }
        else if (byte_tmp[0] == '?') {
            byte_tmp[0] = '0';
            buffer.push_back(std::make_pair(FIRST, std::strtoul(byte_tmp.c_str(), nullptr, 16)));
        }
        else if (byte_tmp[1] == '?') {
            byte_tmp[1] = '0';
            buffer.push_back(std::make_pair(SECOND, std::strtoul(byte_tmp.c_str(), nullptr, 16)));
        }
        else {
            buffer.push_back(std::make_pair(NONE, std::strtoul(byte_tmp.c_str(), nullptr, 16)));
        }
    }
    return buffer;
};

void Scanner::byteScanner(const HANDLE& hndl, const std::string& target_sequence, const LPVOID* start_addr, const LPVOID* end_addr,
    const size_t* sleep_time, const unsigned short* max_results, std::vector<uint64_t>& saver, bool executable, bool (*condition)(uint64_t, HANDLE)) {
    if (!hasInit) Utils::Errors::manageError("Scanner initialization");
    if (target_sequence.empty()) return;

    std::vector<std::pair<markPos, uint8_t>> pattern = initPattern(target_sequence);

    MEMORY_BASIC_INFORMATION memInfo = {};
    SYSTEM_INFO sysInfo = {};
    GetSystemInfo(&sysInfo);
    LPVOID currentAddress = (start_addr != nullptr) ? *start_addr : sysInfo.lpMinimumApplicationAddress;
    LPVOID maxAddress = (end_addr != nullptr) ? *end_addr : sysInfo.lpMaximumApplicationAddress;
    const SIZE_T blockSize = 2048 + (int)Utils::Math::generateRandomNumber(512, 1024); //Avoid high ram and cpu usage and avoid false detections
    std::unordered_set<uint64_t> visited_addresses;
    size_t sleep_manager = 0, results = 0;

    while (currentAddress < maxAddress) {

        if (NtFunctions::QueryMemory(hndl, currentAddress, NtFunctions::MemoryBasicInformation, &memInfo, sizeof(memInfo))) {

            if ((memInfo.State == MEM_COMMIT) && ((memInfo.Protect & PAGE_GUARD) == 0) &&
                (!executable && ((memInfo.Protect & PAGE_READWRITE) || (memInfo.Protect & PAGE_WRITECOPY))) //Doesn't care if executable or not
                || (executable && ((memInfo.Protect & PAGE_EXECUTE) || (memInfo.Protect & PAGE_EXECUTE_READ) || // Executable memory
                    (memInfo.Protect & PAGE_EXECUTE_READWRITE) || (memInfo.Protect & PAGE_EXECUTE_WRITECOPY)))) {

                for (LPBYTE blockStart = (LPBYTE)memInfo.BaseAddress; blockStart < (LPBYTE)memInfo.BaseAddress + memInfo.RegionSize; blockStart += blockSize) {
                    SIZE_T bytesRead;
                    std::vector<uint8_t> buffer(blockSize);

                    if (NtFunctions::ReadMemory(hndl, blockStart, buffer.data(), blockSize, &bytesRead)) {
                        for (size_t i = 0; i < bytesRead - target_sequence.size(); i++) {
                            bool match = true;
                            for (size_t j = 0; j < pattern.size(); j++) {

                                if (pattern[j].first == BOTH) continue;
                                else if (pattern[j].first == FIRST) {
                                    if ((buffer[i + j] - pattern[j].second) % 0x10 != 0) {
                                        match = false;
                                        break;
                                    }
                                }
                                else if (pattern[j].first == SECOND) {
                                    if (buffer[i + j] < pattern[j].second || buffer[i + j] > pattern[j].second + 0x0F) {
                                        match = false;
                                        break;
                                    }
                                }
                                else if (pattern[j].first == NONE) {
                                    if (buffer[i + j] != pattern[j].second) {
                                        match = false;
                                        break;
                                    }
                                }
                            }

                            if (match) {
                                uint64_t addressValue = reinterpret_cast<uint64_t>((LPBYTE)blockStart + i);
                                bool condition_check = true;
                                if (condition != nullptr) condition_check = condition(addressValue, hndl);
                                if (visited_addresses.find(addressValue) == visited_addresses.end() && condition_check) {
                                    saver.push_back(addressValue);
                                    visited_addresses.insert(addressValue);

                                    if (max_results != nullptr) {
                                        ++results;
                                        if (results >= *max_results) return;
                                    }
                                }
                            }
                        }
                    }

                    if (sleep_time != nullptr) {
                        sleep_manager++;

                        if (sleep_manager >= *sleep_time) {
                            std::this_thread::sleep_for(std::chrono::milliseconds(1));
                            sleep_manager = 0;
                        }
                    }
                }
            }
            currentAddress = (LPBYTE)memInfo.BaseAddress + memInfo.RegionSize;
        }
        else {
            currentAddress = (LPBYTE)currentAddress + sysInfo.dwPageSize;
        }
    }
};

template<typename T>
T Scanner::convertBytes(const std::vector<uint8_t>& bytes, const size_t& i) {
    if (!hasInit) Utils::Errors::manageError("Scanner initialization");
    if (i + sizeof(T) > bytes.size()) return NULL;
    T value;
    std::memcpy(&value, &bytes[i], sizeof(T));
    return value;
};
template uint16_t Scanner::convertBytes<uint16_t>(const std::vector<uint8_t>& bytes, const size_t& i);
template uint32_t Scanner::convertBytes<uint32_t>(const std::vector<uint8_t>& bytes, const size_t& i);
template uint64_t Scanner::convertBytes<uint64_t>(const std::vector<uint8_t>& bytes, const size_t& i);
template int Scanner::convertBytes<int>(const std::vector<uint8_t>& bytes, const size_t& i);
template float Scanner::convertBytes<float>(const std::vector<uint8_t>& bytes, const size_t& i);
template double Scanner::convertBytes<double>(const std::vector<uint8_t>& bytes, const size_t& i);

bool Scanner::initScanners(const HWND hwnd) {
    if(hwnd == NULL) Utils::Errors::manageError("Minecraft Handle Error");

    minecraft_hwnd = hwnd;

    GetWindowThreadProcessId(minecraft_hwnd, &minecraft_id);
    minecraft_handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, minecraft_id);

    char windowTitle[256];
    GetWindowTextA(minecraft_hwnd, windowTitle, 256);
    minecraftVersion_string = Utils::Minecraft::getMinecraftVersion(std::string(windowTitle), &minecraftVersion_numeric);

    if (minecraft_handle == NULL || minecraft_id == NULL || minecraft_hwnd == NULL) Utils::Errors::manageError("Invalid Minecraft IDs");
    hasInit = true;

    return minecraftVersion_numeric >= 18 && minecraftVersion_numeric <= 20.4;
};