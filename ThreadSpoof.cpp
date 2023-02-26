#include <iostream>
#include <Windows.h>
#include <cinttypes>
#include <time.h>
#include "ThreadSpoof.h"

typedef struct _CLIENT_ID
{
    PVOID UniqueProcess;
    PVOID UniqueThread;
} CLIENT_ID, * PCLIENT_ID;

using RtlCreateUserThread_t = NTSTATUS(NTAPI*)
(
    IN      HANDLE               ProcessHandle,
    IN      PSECURITY_DESCRIPTOR SecurityDescriptor,
    IN      BOOLEAN              CreateSuspended,
    IN      ULONG                StackZeroBits,
    IN OUT  PULONG               StackReserved,
    IN OUT  PULONG               StackCommit,
    IN      PVOID                StartAddress,
    IN      PVOID                StartParameter,
    OUT     PHANDLE              ThreadHandle,
    OUT     PCLIENT_ID           ClientID
    );

void SpoofThread(void* thread, HMODULE hMod)
{

    LoadLibraryA("ntdll");
    HMODULE hNtdll = GetModuleHandleA("ntdll");
    if (!hNtdll) return;
    auto _RtlCreateUserThread = GetProcAddress(hNtdll, "RtlCreateUserThread");
    if (!_RtlCreateUserThread) return;

    std::uintptr_t tAddress = NULL;
    int DEFAULT_THREAD_SIZE = 1000;

    srand(time(NULL));

    for (int i = 1; i < 4; ++i)
    {
        tAddress |= (rand() & 0xFF) << i * 8;
        tAddress |= (rand() & 0xFF) << i * 8;
        tAddress |= (rand() & 0xFF) << i * 8;
    }

    while (tAddress < 0x7FFFFFFF)
        tAddress -= 0x1000;

    VirtualProtect(reinterpret_cast<PVOID>(tAddress), DEFAULT_THREAD_SIZE, PAGE_EXECUTE_READWRITE, nullptr);

    CONTEXT tContext;
    HANDLE tHandle = nullptr;

    RtlCreateUserThread_t RtlCreateUserThread_f = reinterpret_cast<RtlCreateUserThread_t>(_RtlCreateUserThread);
    RtlCreateUserThread_f(GetCurrentProcess(), nullptr, TRUE, NULL, nullptr, nullptr, (PTHREAD_START_ROUTINE)tAddress, hMod, &tHandle, nullptr);

    tContext.ContextFlags = CONTEXT_INTEGER | CONTEXT_CONTROL;

    GetThreadContext(tHandle, &tContext);

#ifdef _WIN32
    tContext.Eax = reinterpret_cast<ULONG32>(thread);
#else
    tContext.Rcx = reinterpret_cast<ULONG64>(thread);
#endif
    tContext.ContextFlags = CONTEXT_INTEGER | CONTEXT_CONTROL;

    SetThreadContext(tHandle, &tContext);
    ResumeThread(tHandle);

}