#include "HacksIncludes.h"

inline bool bActivateScanReceived = false;
inline bool bPlayWeaponsAnimationSignal = false;
inline bool bPlayTrashAnimationSignal = false;
inline bool bPlayShieldsAnimationSignal = false;
inline bool bRainbowOpInitiated = false;
inline bool bAllSameColorInitiated = false;
inline bool bChangePetInitiated = false;
inline bool bChangeSkinInitiated = false;
inline bool bChangeHatInitiated = false;
inline bool bChangeColorInitiated = false;
inline bool bChangeNameInitiated = false;
inline bool bSabotageInitiated = false;
inline bool bCloseAllDoorsInitiated = false;
inline bool bColorAvailable = false;
inline bool bSabotageLights = false;
inline bool bSabotageComms = false;
inline bool bSabotageO2 = false;
inline bool bSabotageReactor = false;
inline bool bRepairO2 = false;
inline bool bRepairComms = false;
inline bool bRepairReactor = false;
inline bool bRepairLights = false;
inline bool bAllSameNameInitiated = false;
inline bool bAllPlayersRainbowInitiated = false;
inline bool bFakeCamerasEnabled = false;
inline bool bDisableFakeCamera = false;
inline bool bDisableLights = false;
inline bool bReEnableLights = false;
inline bool bLightsState = false;
inline bool bCompleteTasksActive = false;

inline void MainLoop()
{
    if (bActivateScanReceived)
    {
        Hacks::ActivateScan();
        bActivateScanReceived = false;
        Sleep(10000);
        Hacks::DeactivateScan();
    }
    if (bPlayWeaponsAnimationSignal)
    {
        Hacks::PlayWeaponsAnimation();
        bPlayWeaponsAnimationSignal = false;
    }
    if (bPlayTrashAnimationSignal)
    {
        Hacks::PlayTrashAnimation();
        bPlayTrashAnimationSignal = false;
    }
    if (bPlayShieldsAnimationSignal)
    {
        Hacks::PlayShieldsAnimation();
        bPlayShieldsAnimationSignal = false;
    }
    if (bChangeColorInitiated)
    {
        Hacks::ColorChange();
        bChangeColorInitiated = false;
    }
    if (bChangeNameInitiated)
    {
        Hacks::Set_Name();
        Hacks::Set_Name_Secondary();
        bChangeNameInitiated = false;

    }
    if (bCloseAllDoorsInitiated)
    {
        Hacks::Call_CloseAllDoorsFunction();
        bCloseAllDoorsInitiated = false;
    }
    if (bAllSameColorInitiated)
    {
        Hacks::CallAllSameColor();
        bAllSameColorInitiated = false;
    }
    if (bSabotageInitiated)
    {
        DWORD MapIDxD = Utils::Memory::LoadPointer(GeneralInfo::Addresses::PlayerControlBase, { 0x5C, 0x04, 0x10 });
        if (bSabotageLights)
        {
            Hacks::CallSabotageOrRepair(7, 0);
            Hacks::CallSabotageOrRepair(7, 1);
            Hacks::CallSabotageOrRepair(7, 2);
            Hacks::CallSabotageOrRepair(7, 3);
            bSabotageLights = false;
        }
        if (bSabotageComms)
        {
            Hacks::CallSabotageOrRepair(17, 14);
            bSabotageComms = false;
        }
        if (bSabotageO2)
        {
            if (*(int*)MapIDxD != 2)
            {
                Hacks::CallSabotageOrRepair(17, 8);
            }
            bSabotageO2 = false;
        }
        if (bSabotageReactor)
        {
            if (*(int*)MapIDxD == 2)
            {
                Hacks::CallSabotageOrRepair(17, 21);
            }
            else
            {
                Hacks::CallSabotageOrRepair(17, 3);
            }

            bSabotageReactor = false;
        }
        if (bRepairComms)
        {
            if (*(int*)MapIDxD == 0 || *(int*)MapIDxD == 2 || *(int*)MapIDxD == 4)
            {
                Hacks::CallSabotageOrRepair(14, 0);
            }
            else if (*(int*)MapIDxD == 1)
            {
                Hacks::CallSabotageOrRepair(14, 16);
                Hacks::CallSabotageOrRepair(14, 17);
            }

            bRepairComms = false;
        }
        if (bRepairO2)
        {
            if (*(int*)MapIDxD == 0 || *(int*)MapIDxD == 1)
            {
                Hacks::CallSabotageOrRepair(8, 64);
                Hacks::CallSabotageOrRepair(8, 65);
            }

            bRepairO2 = false;
        }
        if (bRepairReactor)
        {
            if (*(int*)MapIDxD == 2)
            {
                Hacks::CallSabotageOrRepair(21, 64);
                Hacks::CallSabotageOrRepair(21, 65);
            }
            else if (*(int*)MapIDxD == 0 || *(int*)MapIDxD == 1)
            {
                Hacks::CallSabotageOrRepair(3, 64);
                Hacks::CallSabotageOrRepair(3, 65);
            }
            else
            {
                Hacks::CallSabotageOrRepair(3, 16);
                Hacks::CallSabotageOrRepair(3, 17);
            }

            bRepairReactor = false;
        }
        if (bRepairLights)
        {
            Hacks::RepairLight();
            bRepairLights = false;
        }

        bSabotageInitiated = false;
    }
    if (bRainbowOpInitiated)
    {
        Hacks::ColorSelected = rand() % 11;
        DWORD LocalPlayerInstance = Utils::Memory::LoadPointer(GeneralInfo::Addresses::PlayerControlBase, { 0x5C, 0x00, 0x00 });
        reinterpret_cast<void(*)(DWORD, DWORD)>(GeneralInfo::Addresses::CmdCheckColor)(LocalPlayerInstance, Hacks::ColorSelected);

    }
    if (bAllPlayersRainbowInitiated)
    {
        GeneralInfo::RefreshPlayersCount();
        for (unsigned int APR = 0; APR < GeneralInfo::player_amount; ++APR)
        {
            Hacks::AllColor = rand() % 11;
            DWORD PlayerInstanceLocalForAPR = Utils::Memory::LoadPointer(GeneralInfo::Addresses::PlayerControlBase, { 0x5C, 0x8, 0x8, (0x10 + (APR * 4)), 0x0 });
            reinterpret_cast<void(*)(DWORD, DWORD)>(GeneralInfo::Addresses::RpcSetColor)(PlayerInstanceLocalForAPR, Hacks::AllColor);

        }
    }
    if (bAllSameNameInitiated)
    {
        Hacks::ChangeEveryName();
        bAllSameNameInitiated = false;
    }
    if (bChangePetInitiated)
    {
        Hacks::PetChange();
        bChangePetInitiated = false;
    }
    if (bChangeHatInitiated)
    {
        Hacks::HatChange();
        bChangeHatInitiated = false;
    }
    if (bChangeSkinInitiated)
    {
        Hacks::SkinChange();
        bChangeSkinInitiated = false;
    }
    if (bFakeCamerasEnabled)
    {
        DWORD ShipStatusInstancePointer = Utils::Memory::LoadPointer(GeneralInfo::Addresses::ShipStatusBase, { 0x5C, 0x00, 0x00 });
        reinterpret_cast<void(*)(DWORD, DWORD, DWORD)>(GeneralInfo::Addresses::RpcRepairSystem)(ShipStatusInstancePointer, 0xB, 1);
        bFakeCamerasEnabled = false;
    }
    if (bDisableFakeCamera)
    {
        DWORD ShipStatusInstancePointer = Utils::Memory::LoadPointer(GeneralInfo::Addresses::ShipStatusBase, { 0x5C, 0x00, 0x00 });
        reinterpret_cast<void(*)(DWORD, DWORD, DWORD)>(GeneralInfo::Addresses::RpcRepairSystem)(ShipStatusInstancePointer, 0xB, 0);
        bDisableFakeCamera = false;
    }
    if (bDisableLights)
    {
        if (bLightsState == false)
        {
            bLightsState = true;
        }
        DWORD ShipStatusInstancePointer = Utils::Memory::LoadPointer(GeneralInfo::Addresses::ShipStatusBase, { 0x5C, 0x00, 0x00 });
        reinterpret_cast<void(*)(DWORD, DWORD, DWORD)>(GeneralInfo::Addresses::RpcRepairSystem)(ShipStatusInstancePointer, 7, 5);
        bDisableLights = false;
    }
    if (bReEnableLights)
    {
        if (bLightsState)
        {
            bLightsState = false;
            DWORD ShipStatusInstancePointer = Utils::Memory::LoadPointer(GeneralInfo::Addresses::ShipStatusBase, { 0x5C, 0x00, 0x00 });
            reinterpret_cast<void(*)(DWORD, DWORD, DWORD)>(GeneralInfo::Addresses::RpcRepairSystem)(ShipStatusInstancePointer, 7, 5);
            bReEnableLights = false;
        }
    }
    if (bCompleteTasksActive)
    {
        for (unsigned int k = 0; k < *(int*)Utils::Memory::LoadPointer(GeneralInfo::Addresses::PlayerControlBase, { 0x5C, 0x00, 0x88, 0xC }); ++k)
        {
            DWORD TaskIDAddr = Utils::Memory::LoadPointer(GeneralInfo::Addresses::PlayerControlBase, { 0x5C, 0x00, 0x78, 0x8, (0x10 + (k * 0x4)), 0x10 });
            DWORD LocalPlayerInstance = Utils::Memory::LoadPointer(GeneralInfo::Addresses::PlayerControlBase, { 0x5C, 0x00, 0x00 });
            int TaskID = *(int*)TaskIDAddr;
            reinterpret_cast<void(*)(DWORD, int)>(GeneralInfo::Addresses::RpcCompleteTask)(LocalPlayerInstance, TaskID);
        }
        bCompleteTasksActive = false;
    }
}