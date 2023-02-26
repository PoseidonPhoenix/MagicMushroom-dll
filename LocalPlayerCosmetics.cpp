#include "Memory.h"
#include "LocalPlayerCosmetics.h"
#include "GameFunctionsBaseAddresses.hpp"

namespace Hacks
{
    void ColorChange()
    {
        DWORD LocalPlayer = Utils::Memory::LoadPointer(GeneralInfo::Addresses::PlayerControlBase, { 0x5C, 0x00, 0x00 });
        
        reinterpret_cast<void(*)(DWORD, DWORD)>(GeneralInfo::Addresses::CmdCheckColor)(LocalPlayer, ColorSelected);
    }

    void PetChange()
    {
        DWORD LocalPlayer = Utils::Memory::LoadPointer(GeneralInfo::Addresses::PlayerControlBase, { 0x5C, 0x00, 0x00 });

        reinterpret_cast<void(*)(DWORD, DWORD)>(GeneralInfo::Addresses::RpcSetPet)(LocalPlayer, PetSelected);
    }

    void HatChange()
    {
        DWORD LocalPlayer = Utils::Memory::LoadPointer(GeneralInfo::Addresses::PlayerControlBase, { 0x5C, 0x00, 0x00 });

        reinterpret_cast<void(*)(DWORD, DWORD)>(GeneralInfo::Addresses::RpcSetHat)(LocalPlayer, HatSelected);
    }

    void SkinChange()
    {
        DWORD LocalPlayer = Utils::Memory::LoadPointer(GeneralInfo::Addresses::PlayerControlBase, { 0x5C, 0x00, 0x00 });

        reinterpret_cast<void(*)(DWORD, DWORD)>(GeneralInfo::Addresses::RpcSetSkin)(LocalPlayer, SkinSelected);
    }

    struct system_string
    {
        DWORD instance;
        DWORD padding;
        DWORD length;
        wchar_t content[1024];
    };

    system_string name_container;
    system_string name_container2;

    DWORD set_name_inner(DWORD instance) {

        name_container.instance = instance;
        name_container.length = (DWORD)wcslen(name_container.content);
        return (DWORD)&name_container;

    }

    DWORD set_name_inner2(DWORD instance)
    {

        name_container2.instance = instance;
        name_container2.length = (DWORD)wcslen(name_container2.content);
        return (DWORD)&name_container2;

    }

    void Set_Name()
    {

        __asm
        {

            pushad
            push ebp
            mov ebp, esp

            mov eax, GeneralInfo::Addresses::PlayerControlBase
            mov eax, [eax]
            mov eax, [eax + 0x5C]
            mov eax, [eax + 0x00]

            mov ecx, eax

            mov eax, [eax + 0x34]
            mov eax, [eax + 0x0C]
            mov eax, [eax]
            push eax
            call set_name_inner
            push eax
            mov eax, GeneralInfo::Addresses::PlayerControlBase
            mov eax, [eax]
            mov eax, [eax + 0x5C]
            mov eax, [eax + 0x00]
            push eax

            call GeneralInfo::Addresses::CmdCheckName

            mov esp, ebp
            pop ebp
            popad

        }

    }

    void Set_Name_Secondary()
    {

        __asm
        {

            pushad
            push ebp
            mov ebp, esp
            mov eax, GeneralInfo::Addresses::PlayerControlBase
            mov eax, [eax]
            mov eax, [eax + 0x5C]
            mov eax, [eax + 0x00]
            mov ecx, eax
            mov eax, [eax + 0x34]
            mov eax, [eax + 0x0C]
            mov eax, [eax]
            push eax
            call set_name_inner2
            push eax
            mov eax, GeneralInfo::Addresses::PlayerControlBase
            mov eax, [eax]
            mov eax, [eax + 0x5C]
            mov eax, [eax + 0x00]
            push eax
            call GeneralInfo::Addresses::CmdCheckName
            mov esp, ebp
            pop ebp
            popad
        }

    }

}