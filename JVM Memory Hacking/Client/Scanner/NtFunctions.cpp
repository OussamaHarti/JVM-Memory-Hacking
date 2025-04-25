#include "NtFunctions.h"

void NtFunctions::initialize() {
    HMODULE hNtDll = GetModuleHandle("ntdll.dll");

    if (!hNtDll) {
        std::cerr << "ntdll.dll loading error" << std::endl;
        exit(0);
    }

    NtReadVirtualMemory = (NtReadVirtualMemory_t)GetProcAddress(hNtDll, "NtReadVirtualMemory");

    NtWriteVirtualMemory = (NtWriteVirtualMemory_t)GetProcAddress(hNtDll, "NtWriteVirtualMemory");

    NtQueryVirtualMemory = (NtQueryVirtualMemory_t)GetProcAddress(hNtDll, "NtQueryVirtualMemory");

    NtFunctions::initialized = true;
};

bool NtFunctions::ReadMemory(const HANDLE ProcessHandle, const PVOID BaseAddress, LPVOID Buffer, const SIZE_T BufferSize, PSIZE_T NumberOfBytesRead) {
    static int counter = 0;
    if (!NtFunctions::initialized) NtFunctions::initialize();

    if (NtReadVirtualMemory != nullptr) {
        NTSTATUS status = NtReadVirtualMemory(ProcessHandle, BaseAddress, Buffer, BufferSize, NumberOfBytesRead);
        return NT_SUCCESS(status);
    }
    
    return ReadProcessMemory(ProcessHandle, BaseAddress, Buffer, BufferSize, NumberOfBytesRead);
};

bool NtFunctions::WriteMemory(const HANDLE ProcessHandle, const PVOID BaseAddress, LPVOID Buffer, const SIZE_T BufferSize, PSIZE_T NumberOfBytesRead) {
    if (!NtFunctions::initialized) NtFunctions::initialize();

    if (NtWriteVirtualMemory != nullptr) {
        NTSTATUS status = NtWriteVirtualMemory(ProcessHandle, BaseAddress, Buffer, BufferSize, NumberOfBytesRead);
        return NT_SUCCESS(status);
    }

    return WriteProcessMemory(ProcessHandle, BaseAddress, Buffer, BufferSize, NumberOfBytesRead);
};

SIZE_T NtFunctions::QueryMemory(const HANDLE ProcessHandle, PVOID BaseAddress, MEMORY_INFORMATION_CLASS MemoryInformationClass, PVOID MemoryInformation,
    const SIZE_T MemoryInformationLength) {
    if (!NtFunctions::initialized) NtFunctions::initialize();

    SIZE_T tmp;
    if (NtQueryVirtualMemory != nullptr) NtQueryVirtualMemory(ProcessHandle, BaseAddress, MemoryInformationClass, MemoryInformation, MemoryInformationLength, &tmp);
    else tmp = VirtualQueryEx(ProcessHandle, BaseAddress, (PMEMORY_BASIC_INFORMATION)MemoryInformation, MemoryInformationLength);

    return tmp;
};

void NtFunctions::CreateThread(HANDLE ThreadHandle, const ACCESS_MASK DesiredAccess, const POBJECT_ATTRIBUTES ObjectAttributes, const HANDLE ProcessHandle, PVOID StartRoutine,
    PVOID Argument, const ULONG CreateFlags, ULONG_PTR ZeroBits, const SIZE_T StackSize, const SIZE_T MaximumStackSize, PVOID AttributeList) {
    if (!NtFunctions::initialized) NtFunctions::initialize();

    static int(__stdcall * ZwCreateThreadEx)(HANDLE, ACCESS_MASK, POBJECT_ATTRIBUTES, HANDLE, PVOID, PVOID, ULONG, ULONG_PTR, SIZE_T, SIZE_T, PVOID)
        = (decltype(ZwCreateThreadEx))GetProcAddress(GetModuleHandle("ntdll.dll"), "ZwCreateThreadEx");

    if (ZwCreateThreadEx == nullptr) {
        std::cerr << "ZwCreateThreadEx loading error" << std::endl;
        exit(0);
    }

    ZwCreateThreadEx(ThreadHandle, DesiredAccess, ObjectAttributes, ProcessHandle,
        StartRoutine, Argument, CreateFlags, ZeroBits, StackSize, MaximumStackSize, AttributeList);
};