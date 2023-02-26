#include "PlayerCount.h"
#include "Memory.h"
#include "GameFunctionsBaseAddresses.hpp"

namespace GeneralInfo
{
    void RefreshPlayersCount()
    {
        DWORD Player1Instance = Utils::Memory::LoadPointer(GeneralInfo::Addresses::PlayerControlBase, { 0x5C, 0x08, 0x08, 0x10 });
        DWORD Player2Instance = Utils::Memory::LoadPointer(GeneralInfo::Addresses::PlayerControlBase, { 0x5C, 0x08, 0x08, 0x14 });
        DWORD Player3Instance = Utils::Memory::LoadPointer(GeneralInfo::Addresses::PlayerControlBase, { 0x5C, 0x08, 0x08, 0x18 });
        DWORD Player4Instance = Utils::Memory::LoadPointer(GeneralInfo::Addresses::PlayerControlBase, { 0x5C, 0x08, 0x08, 0x1C });
        DWORD Player5Instance = Utils::Memory::LoadPointer(GeneralInfo::Addresses::PlayerControlBase, { 0x5C, 0x08, 0x08, 0x20 });
        DWORD Player6Instance = Utils::Memory::LoadPointer(GeneralInfo::Addresses::PlayerControlBase, { 0x5C, 0x08, 0x08, 0x24 });
        DWORD Player7Instance = Utils::Memory::LoadPointer(GeneralInfo::Addresses::PlayerControlBase, { 0x5C, 0x08, 0x08, 0x28 });
        DWORD Player8Instance = Utils::Memory::LoadPointer(GeneralInfo::Addresses::PlayerControlBase, { 0x5C, 0x08, 0x08, 0x2C });
        DWORD Player9Instance = Utils::Memory::LoadPointer(GeneralInfo::Addresses::PlayerControlBase, { 0x5C, 0x08, 0x08, 0x30 });
        DWORD Player10Instance = Utils::Memory::LoadPointer(GeneralInfo::Addresses::PlayerControlBase, { 0x5C, 0x08, 0x08, 0x34 });

        if (*(int*)Player1Instance)
            ++player_amount;
        if (*(int*)Player2Instance)
            ++player_amount;
        if (*(int*)Player3Instance)
            ++player_amount;
        if (*(int*)Player4Instance)
            ++player_amount;
        if (*(int*)Player5Instance)
            ++player_amount;
        if (*(int*)Player6Instance)
            ++player_amount;
        if (*(int*)Player7Instance)
            ++player_amount;
        if (*(int*)Player8Instance)
            ++player_amount;
        if (*(int*)Player9Instance)
            ++player_amount;
        if (*(int*)Player10Instance)
            ++player_amount;
    }
}