#include <Windows.h>
#include <vector>

namespace Utils
{
	namespace Memory
	{
		DWORD LoadPointer(DWORD paddr, const std::vector<DWORD>& offsets);
		BYTE read(DWORD address);
	}
}