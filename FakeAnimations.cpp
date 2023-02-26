#include "FakeAnimations.h"
#include "GameFunctionsBaseAddresses.hpp"

namespace Hacks
{
    void PlayWeaponsAnimation()
    {  
        reinterpret_cast<void(*)(DWORD, DWORD)>(GeneralInfo::Addresses::RpcPlayAnimation)(GeneralInfo::Addresses::PlayerControlBase, 6);
    }

    void PlayTrashAnimation()
    {
        reinterpret_cast<void(*)(DWORD, DWORD)>(GeneralInfo::Addresses::RpcPlayAnimation)(GeneralInfo::Addresses::PlayerControlBase, 9);
    }

    void PlayShieldsAnimation()
    {
        reinterpret_cast<void(*)(DWORD, DWORD)>(GeneralInfo::Addresses::RpcPlayAnimation)(GeneralInfo::Addresses::PlayerControlBase, 1);
    }
}