#include "Memory.h"

namespace Utils
{
    namespace Memory
    {
        DWORD LoadPointer(DWORD paddr, const std::vector<DWORD>& offsets)
        {
            DWORD addr = paddr;

            for (const auto& offset : offsets)
            {
                addr = *(DWORD*)addr;
                addr += offset;
            }

            return addr;
        }

        BYTE read(DWORD address)
        {
            BYTE buffer;
            ReadProcessMemory(GetCurrentProcess(), reinterpret_cast<LPCVOID>(address), &buffer, sizeof(BYTE), NULL);
            return buffer;
        }
    }
}