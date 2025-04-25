#pragma once
#include "NtFunctions.h"
#include <stdint.h>
constexpr uint64_t CLIENT_START_ADDR = 0x0000000000;
constexpr uint64_t INSTR_START_ADDR = 0x000000000;
constexpr uint64_t CLIENT_EXE_START_ADDR = 0x1000000000;
constexpr uint64_t INSTR_END_ADDR = 0x1500000000;
constexpr uint64_t CLIENT_EXE_END_ADDR = 0x30000000000;
constexpr uint64_t REDIRECT_PTR = 0x3F400000;
constexpr uint64_t MIN_PTR = 0x20000000;

#include <Windows.h>
#include <vector>
#include <string>

class Scanner {
protected:
    static inline bool hasInit = false;
    enum markPos {
        NONE,
        BOTH,
        FIRST,
        SECOND
    };

    static inline HWND minecraft_hwnd;
    static inline DWORD minecraft_id;
    static inline HANDLE minecraft_handle;
    static inline float minecraftVersion_numeric;
    static inline std::string minecraftVersion_string;

protected:

    static std::vector<std::pair<markPos, uint8_t>> initPattern(const std::string& patter);

    static void byteScanner(const HANDLE& hndl, const std::string& target_sequence, const LPVOID* start_addr, const LPVOID* end_addr,
        const size_t* sleep_time, const unsigned short* max_results, std::vector<uint64_t>& results, bool executable, bool (*condition)(uint64_t, HANDLE));

    template<typename T>
    static T convertBytes(const std::vector<uint8_t>& bytes, const size_t& i);

    Scanner() {};

public:

    static bool initScanners(const HWND hwnd);
};