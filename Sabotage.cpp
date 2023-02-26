#include "Sabotage.h"
#include "GameFunctionsBaseAddresses.hpp"

namespace Hacks
{
    void CallSabotageOrRepair(DWORD firstarg, DWORD secarg)
    {
        DWORD ShipStatusInstancePointerForSabotage = Utils::Memory::LoadPointer(GeneralInfo::Addresses::ShipStatusBase, { 0x5C, 0x00, 0x00 });

        reinterpret_cast<void(*)(DWORD, DWORD, DWORD)>(GeneralInfo::Addresses::RpcRepairSystem)(ShipStatusInstancePointerForSabotage, firstarg, secarg);

    }

    DWORD GetSwitchBase()
    {
        DWORD ShipStatusInstancePointerForSabotage = Utils::Memory::LoadPointer(GeneralInfo::Addresses::ShipStatusBase, { 0x5C, 0x00, 0x00 });
        return Utils::Memory::LoadPointer(ShipStatusInstancePointerForSabotage + 0x8C, { 0x0C, 0x1C, 0x00 });
    }

    void RepairLight()
    {
        DWORD ShipStatusInstancePointerForSabotage = Utils::Memory::LoadPointer(GeneralInfo::Addresses::ShipStatusBase, { 0x5C, 0x00, 0x00 });

        DWORD switch_base = GetSwitchBase();
        BYTE current_state, expected_state;

        current_state = Utils::Memory::read(switch_base + 0x14);
        expected_state = Utils::Memory::read(switch_base + 0x15);
        if (current_state != expected_state) {
            for (auto i = 0; i < 5; ++i) {
                auto switchMask = 1 << (i & 0x1F);
                if ((current_state & switchMask) != (expected_state & switchMask)) {
                    reinterpret_cast<void(*)(DWORD, DWORD, DWORD)>(GeneralInfo::Addresses::RpcRepairSystem)(ShipStatusInstancePointerForSabotage, 7, (DWORD)i);
                    //Sleep(250);
                }
            }
        }

    }
}