#include "Doors.h"
#include "GameFunctionsBaseAddresses.hpp"

namespace Hacks
{
    inline void CloseAllDoors(const std::vector<DWORD>& ids)
    {
        DWORD ShipStatusInstancePointer = Utils::Memory::LoadPointer(GeneralInfo::Addresses::ShipStatusBase, { 0x5C, 0x00, 0x00 });

        for (const auto& it : ids)
        {
            reinterpret_cast<void(*)(DWORD, DWORD)>(GeneralInfo::Addresses::RpcCloseDoorsOfType)(ShipStatusInstancePointer, it);
            //Sleep(150);
        }
    }

    void Call_CloseAllDoorsFunction()
    {
        DWORD MapID = Utils::Memory::LoadPointer(GeneralInfo::Addresses::PlayerControlBase, { 0x5C, 0x04, 0x10 });

        if (*(int*)MapID == 0)
        {
            CloseAllDoors({ 0x01, 0x02, 0x04, 0x07, 0x0B, 0x0A, 0x0D });
        }
        else if (*(int*)MapID == 2)
        {
            CloseAllDoors({ 0x01, 0x15, 0x17, 0x07, 0x08, 0x0E, 0x0C });
        }
        else if (*(int*)MapID == 3)
        {
            CloseAllDoors({ 0x0E, 0x2E, 0x28, 0x2A, 0x2D, 0x21 });
        }

    }
}