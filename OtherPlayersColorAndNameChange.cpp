#include "OtherPlayersColorAndNameChange.h"
#include "Memory.h"
#include "PlayerCount.h"
#include "GameFunctionsBaseAddresses.hpp"

namespace Hacks 
{
    void Server_SideColorChange1()
    {
        __asm {

            push ebp
            mov ebp, esp
            mov eax, AllColor
            push eax
            mov eax, GeneralInfo::Addresses::PlayerControlBase
            mov eax, [eax]
            mov eax, [eax + 0x5C]
            mov eax, [eax + 0x8]
            mov eax, [eax + 0x8]
            mov eax, [eax + 0x10]
            test eax, eax
            push eax
            call GeneralInfo::Addresses::RpcSetColor
            mov esp, ebp
            pop ebp
            xor eax, eax
            inc eax


        }
    }

    void Server_SideColorChange2()
    {
        __asm {

            push ebp
            mov ebp, esp
            mov eax, AllColor
            push eax
            mov eax, GeneralInfo::Addresses::PlayerControlBase
            mov eax, [eax]
            mov eax, [eax + 0x5C]
            mov eax, [eax + 0x8]
            mov eax, [eax + 0x8]
            mov eax, [eax + 0x14]
            test eax, eax
            push eax
            call GeneralInfo::Addresses::RpcSetColor
            mov esp, ebp
            pop ebp
            xor eax, eax
            inc eax


        }
    }

    void Server_SideColorChange3()
    {
        __asm {

            push ebp
            mov ebp, esp
            mov eax, AllColor
            push eax
            mov eax, GeneralInfo::Addresses::PlayerControlBase
            mov eax, [eax]
            mov eax, [eax + 0x5C]
            mov eax, [eax + 0x8]
            mov eax, [eax + 0x8]
            mov eax, [eax + 0x18]
            test eax, eax
            push eax
            call GeneralInfo::Addresses::RpcSetColor
            mov esp, ebp
            pop ebp
            xor eax, eax
            inc eax


        }
    }

    void Server_SideColorChange4()
    {
        __asm {

            push ebp
            mov ebp, esp
            mov eax, AllColor
            push eax
            mov eax, GeneralInfo::Addresses::PlayerControlBase
            mov eax, [eax]
            mov eax, [eax + 0x5C]
            mov eax, [eax + 0x8]
            mov eax, [eax + 0x8]
            mov eax, [eax + 0x1C]
            test eax, eax
            push eax
            call GeneralInfo::Addresses::RpcSetColor
            mov esp, ebp
            pop ebp
            xor eax, eax
            inc eax


        }
    }

    void Server_SideColorChange5()
    {
        __asm {

            push ebp
            mov ebp, esp
            mov eax, AllColor
            push eax
            mov eax, GeneralInfo::Addresses::PlayerControlBase
            mov eax, [eax]
            mov eax, [eax + 0x5C]
            mov eax, [eax + 0x8]
            mov eax, [eax + 0x8]
            mov eax, [eax + 0x20]
            test eax, eax
            push eax
            call GeneralInfo::Addresses::RpcSetColor
            mov esp, ebp
            pop ebp
            xor eax, eax
            inc eax


        }
    }

    void Server_SideColorChange6()
    {
        __asm {

            push ebp
            mov ebp, esp
            mov eax, AllColor
            push eax
            mov eax, GeneralInfo::Addresses::PlayerControlBase
            mov eax, [eax]
            mov eax, [eax + 0x5C]
            mov eax, [eax + 0x8]
            mov eax, [eax + 0x8]
            mov eax, [eax + 0x24]
            test eax, eax
            push eax
            call GeneralInfo::Addresses::RpcSetColor
            mov esp, ebp
            pop ebp
            xor eax, eax
            inc eax


        }
    }

    void Server_SideColorChange7()
    {
        __asm {

            push ebp
            mov ebp, esp
            mov eax, AllColor
            push eax
            mov eax, GeneralInfo::Addresses::PlayerControlBase
            mov eax, [eax]
            mov eax, [eax + 0x5C]
            mov eax, [eax + 0x8]
            mov eax, [eax + 0x8]
            mov eax, [eax + 0x28]
            test eax, eax
            push eax
            call GeneralInfo::Addresses::RpcSetColor
            mov esp, ebp
            pop ebp
            xor eax, eax
            inc eax


        }
    }

    void Server_SideColorChange8()
    {
        __asm {

            push ebp
            mov ebp, esp
            mov eax, AllColor
            push eax
            mov eax, GeneralInfo::Addresses::PlayerControlBase
            mov eax, [eax]
            mov eax, [eax + 0x5C]
            mov eax, [eax + 0x8]
            mov eax, [eax + 0x8]
            mov eax, [eax + 0x2C]
            test eax, eax
            push eax
            call GeneralInfo::Addresses::RpcSetColor
            mov esp, ebp
            pop ebp
            xor eax, eax
            inc eax


        }
    }

    void Server_SideColorChange9()
    {
        __asm {

            push ebp
            mov ebp, esp
            mov eax, AllColor
            push eax
            mov eax, GeneralInfo::Addresses::PlayerControlBase
            mov eax, [eax]
            mov eax, [eax + 0x5C]
            mov eax, [eax + 0x8]
            mov eax, [eax + 0x8]
            mov eax, [eax + 0x30]
            test eax, eax
            push eax
            call GeneralInfo::Addresses::RpcSetColor
            mov esp, ebp
            pop ebp
            xor eax, eax
            inc eax


        }
    }

    void Server_SideColorChange10()
    {
        __asm {

            push ebp
            mov ebp, esp
            mov eax, AllColor
            push eax
            mov eax, GeneralInfo::Addresses::PlayerControlBase
            mov eax, [eax]
            mov eax, [eax + 0x5C]
            mov eax, [eax + 0x8]
            mov eax, [eax + 0x8]
            mov eax, [eax + 0x34]
            test eax, eax
            push eax
            call GeneralInfo::Addresses::RpcSetColor
            mov esp, ebp
            pop ebp
            xor eax, eax
            inc eax


        }
    }

    void CallAllSameColor()
    {

        //DWORD LocalPlayerInstance = Utils::Memory::LoadPointer(GeneralInfo::Addresses::PlayerControlBase, { 0x5C, 0x00, 0x00 });
        //DWORD Player2Instance = Utils::Memory::LoadPointer(GeneralInfo::Addresses::PlayerControlBase, { 0x5C, 0x08, 0x08, 0x14 });
        //DWORD Player3Instance = Utils::Memory::LoadPointer(GeneralInfo::Addresses::PlayerControlBase, { 0x5C, 0x08, 0x08, 0x18 });
        //DWORD Player4Instance = Utils::Memory::LoadPointer(GeneralInfo::Addresses::PlayerControlBase, { 0x5C, 0x08, 0x08, 0x1C });
        //DWORD Player5Instance = Utils::Memory::LoadPointer(GeneralInfo::Addresses::PlayerControlBase, { 0x5C, 0x08, 0x08, 0x20 });
        //DWORD Player6Instance = Utils::Memory::LoadPointer(GeneralInfo::Addresses::PlayerControlBase, { 0x5C, 0x08, 0x08, 0x24 });
        //DWORD Player7Instance = Utils::Memory::LoadPointer(GeneralInfo::Addresses::PlayerControlBase, { 0x5C, 0x08, 0x08, 0x28 });
        //DWORD Player8Instance = Utils::Memory::LoadPointer(GeneralInfo::Addresses::PlayerControlBase, { 0x5C, 0x08, 0x08, 0x2C });
        //DWORD Player9Instance = Utils::Memory::LoadPointer(GeneralInfo::Addresses::PlayerControlBase, { 0x5C, 0x08, 0x08, 0x30 });
        //DWORD Player10Instance = Utils::Memory::LoadPointer(GeneralInfo::Addresses::PlayerControlBase, { 0x5C, 0x08, 0x08, 0x34 });

        //Hacks::Server_SideColorChange1();
        //if (*(int*)Player2Instance)
        
        DWORD pl;
        /*for (unsigned int i = 0; i < 9; ++i)
        {
            if (pl = Utils::Memory::LoadPointer(GeneralInfo::Addresses::PlayerControlBase, { 0x5C, 0x08, 0x08, 0x10 + i * 0x04 }))
            {
                reinterpret_cast<void(*)(DWORD, DWORD)>(GeneralInfo::Addresses::RpcSetColor)(pl, AllColor);
            }
        }*/

        pl = Utils::Memory::LoadPointer(GeneralInfo::Addresses::PlayerControlBase, { 0x5C, 0x08, 0x08, 0x14 });
        reinterpret_cast<void(*)(DWORD, DWORD)>(GeneralInfo::Addresses::RpcSetColor)(pl, AllColor);

    }

    struct system_string
    {
        DWORD instance;
        DWORD padding;
        DWORD length;
        wchar_t content[1024];
    };

    system_string name_container3;
    system_string name_container4;

    void ChangeEveryName()
    {
        GeneralInfo::RefreshPlayersCount();
        DWORD s_instance_ptr = Utils::Memory::LoadPointer(GeneralInfo::Addresses::PlayerControlBase, { 0x5C, 0x00, 0x34, 0xC, 0x00, 0x00 });
        name_container3.instance = s_instance_ptr;
        name_container3.length = (DWORD)wcslen(name_container3.content);
        DWORD s_instance_ptr2 = Utils::Memory::LoadPointer(GeneralInfo::Addresses::PlayerControlBase, { 0x5C, 0x00, 0x34, 0xC, 0x00, 0x00 });
        name_container4.instance = s_instance_ptr2;
        name_container4.length = (DWORD)wcslen(name_container4.content);
        for (unsigned int p = 0; p < GeneralInfo::player_amount; ++p)
        {
            DWORD player_instance = Utils::Memory::LoadPointer(GeneralInfo::Addresses::PlayerControlBase, { 0x5C, 0x8, 0x8, (0x10 + (p * 4)), 0x0 });
            reinterpret_cast<void(*)(DWORD, DWORD)>(GeneralInfo::Addresses::RpcSetName)(player_instance, (DWORD)&name_container3);
            DWORD player_instance2 = Utils::Memory::LoadPointer(GeneralInfo::Addresses::PlayerControlBase, { 0x5C, 0x8, 0x8, (0x10 + (p * 4)), 0x0 });
            reinterpret_cast<void(*)(DWORD, DWORD)>(GeneralInfo::Addresses::RpcSetName)(player_instance2, (DWORD)&name_container4);
        }
    }

}