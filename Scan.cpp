#include "GameFunctionsBaseAddresses.hpp"

namespace Hacks 
{
    void ActivateScan()
    {
        __asm {

            push ebp
            mov ebp, esp
            push 0x1
            mov eax, GeneralInfo::Addresses::PlayerControlBase
            mov eax, [eax]
            mov eax, [eax + 0x5C]
            mov eax, [eax + 0x00]
            test eax, eax
            push eax
            call GeneralInfo::Addresses::RpcSetScanner
            mov esp, ebp
            pop ebp
            xor eax, eax
            inc eax


        }
    }

    void DeactivateScan()
    {
        __asm {

            push ebp
            mov ebp, esp
            push 0x0
            mov eax, GeneralInfo::Addresses::PlayerControlBase
            mov eax, [eax]
            mov eax, [eax + 0x5C]
            mov eax, [eax + 0x00]
            test eax, eax
            push eax
            call GeneralInfo::Addresses::RpcSetScanner
            mov esp, ebp
            pop ebp
            xor eax, eax
            inc eax


        }
    }
}