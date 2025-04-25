#pragma once
#include <Windows.h>
#include <winternl.h>
#include <winnt.h>
#include <iostream>

class NtFunctions{
public:
    static inline bool initialized = false;

    enum MEMORY_INFORMATION_CLASS
    {
        MemoryBasicInformation, 
        MemoryWorkingSetInformation, 
        MemoryMappedFilenameInformation, 
        MemoryRegionInformation, 
        MemoryWorkingSetExInformation, 
        MemorySharedCommitInformation, 
        MemoryImageInformation,
        MemoryRegionInformationEx, 
        MemoryPrivilegedBasicInformation,
        MemoryEnclaveImageInformation, 
        MemoryBasicInformationCapped,
        MemoryPhysicalContiguityInformation,
        MemoryBadInformation,
        MemoryBadInformationAllProcesses,
        MaxMemoryInfoClass
    };

    typedef NTSTATUS(NTAPI* NtReadVirtualMemory_t)(HANDLE ProcessHandle, PVOID BaseAddress, LPVOID Buffer, SIZE_T BufferSize, PSIZE_T NumberOfBytesRead);

    typedef NTSTATUS(NTAPI* NtWriteVirtualMemory_t)(HANDLE ProcessHandle, PVOID BaseAddress, LPVOID Buffer, SIZE_T BufferSize, PSIZE_T NumberOfBytesWritten);

    typedef NTSTATUS(NTAPI* NtQueryVirtualMemory_t)(HANDLE ProcessHandle, PVOID BaseAddress, NtFunctions::MEMORY_INFORMATION_CLASS MemoryInformationClass, PVOID MemoryInformation,
        SIZE_T MemoryInformationLength, PSIZE_T ReturnLength);

    static inline NtReadVirtualMemory_t NtReadVirtualMemory = nullptr;
    static inline NtWriteVirtualMemory_t NtWriteVirtualMemory = nullptr;
    static inline NtQueryVirtualMemory_t NtQueryVirtualMemory = nullptr;

private:
    static void initialize();

    NtFunctions() {};

public:

    static bool ReadMemory(const HANDLE ProcessHandle, const PVOID BaseAddress, LPVOID Buffer, const SIZE_T BufferSize, PSIZE_T NumberOfBytesRead);

    static bool WriteMemory(const HANDLE ProcessHandle, const PVOID BaseAddress, LPVOID Buffer, const SIZE_T BufferSize, PSIZE_T NumberOfBytesRead);

    static SIZE_T QueryMemory(const HANDLE ProcessHandle, PVOID BaseAddress, MEMORY_INFORMATION_CLASS MemoryInformationClass, PVOID MemoryInformation,
        const SIZE_T MemoryInformationLength);

    static void CreateThread(HANDLE ThreadHandle, const ACCESS_MASK DesiredAccess, const POBJECT_ATTRIBUTES ObjectAttributes, const HANDLE ProcessHandle, PVOID StartRoutine,
        PVOID Argument, const ULONG CreateFlags, ULONG_PTR ZeroBits, const SIZE_T StackSize, const SIZE_T MaximumStackSize, PVOID AttributeList);
};