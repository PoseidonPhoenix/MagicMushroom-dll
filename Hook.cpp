#include <cstdint>
#include <Windows.h>
#include "Hook.h"

namespace Utils
{
    namespace Hook
    {
        bool placeJump(void* start, void* destination, size_t length) {

            DWORD oldProtect, newProtect;
            auto _start = reinterpret_cast<uintptr_t>(start);

            if (!VirtualProtect(start, length, PAGE_EXECUTE_READWRITE, &oldProtect))
                return false;

            *reinterpret_cast<uint8_t*>(start) = 0xE9;
            *reinterpret_cast<uint32_t*>(_start + 1) = reinterpret_cast<uintptr_t>(destination) - _start - 5;

            for (int i = 5; i < length; ++i)
                *reinterpret_cast<uint8_t*>(_start + i) = 0x90;

            if (!VirtualProtect(start, length, oldProtect, &newProtect))
                return false;

            return true;

        }
    }
}