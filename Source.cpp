#include <Windows.h>
#include <vector>
#include <cinttypes>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <filesystem>

DWORD base = (DWORD)GetModuleHandleA("GameAssembly.dll");
DWORD ACTIVATE_SCAN = base + 0x452260;
DWORD player_control_address = base + 0x01C6861C;
DWORD rpc_play_animation = base + 0x451990;
DWORD SetLocalPlayerColorAddress = base + 0x44DFD0;
DWORD call_name = base + 0x44E080;
DWORD SetPetAddress = base + 0x4521C0;
DWORD RpcSetColor = base + 0x451E50;
DWORD SetHat = base + 0x451EF0;
DWORD RpcSetName = base + 0x452120;
DWORD RpcRepairSystem = base + 0x490D10;
DWORD RRSPointerFirstAddress = base + 0x1B6A56C;
DWORD call_RpcCloseDoors = base + 0x490B40;
DWORD RpcSetSkin = base + 0x452360;
DWORD RpcCompleteTask = base + 0x451840;

bool activatescanreceived = false;
bool playweaponsanimationsignal = false;
bool playtrashanimationsignal = false;
bool playshieldsanimationsignal = false;
bool RainbowOpInitiated = false;
bool allsamecolorinitiated = false;
bool changepetinitiated = false;
bool changeskininitiated = false;
bool changehatinitiated = false;
bool changecolorinitiated = false;
bool changenameinitiated = false;
bool sabotageinitiated = false;
bool closealldoorsinitiated = false;
bool ColorAvailable = false;
bool SabotageLights = false;
bool SabotageComms = false;
bool SabotageO2 = false;
bool SabotageReactor = false;
bool RepairO2 = false;
bool RepairComms = false;
bool RepairReactor = false;
bool RepairLights = false;
bool AllSameNameInitiated = false;
bool RainbowName = false;
bool AllPlayersRainbowInitiated = false;
bool FakeCamerasEnabled = false;
bool DisableFakeCamera = false;
bool DisableLights = false;
bool Re_enableLights = false;
bool LightsState = false;
bool CompleteTasksActive = false;

DWORD ColorSelected = 0;
DWORD NameColorAddress;
int PetSelected = 1;
int HatSelected = 1;
int AllColor = 1;
int SkinSelected = 0;

struct system_string
{
    DWORD instance;
    DWORD padding;
    DWORD length;
    wchar_t content[1024];
};

int player_amount;

static uint32_t cnt = 0;
float freq = .1f;


std::vector<unsigned int> Local_Player_Offsets = { 0x5C, 0x00, 0x00 };

float RGBz[] = { 0, 0, 0 };

#include "json.hpp"
using json = nlohmann::json;

EXTERN_C IMAGE_DOS_HEADER __ImageBase;

std::wstring SpaceCheatModePath = L"\\SpaceCheatMode.exe";
std::wstring JsonFileName = L"\\Addresses.json";

std::wstring getDllPath()
{
    TCHAR DllPath[MAX_PATH] = { 0 };
    GetModuleFileName((HINSTANCE)&__ImageBase, DllPath, _countof(DllPath));
    return DllPath;
}
std::wstring getDllDirectory()
{
    std::wstring DllDir = getDllPath();
    std::filesystem::path NewDir(DllDir);
    return NewDir.parent_path().wstring();
}

std::wstring XFORCEPATH;
std::wstring SpaceCheatModeFullPath;

system_string name_container;
system_string name_container2;
system_string name_container3;
system_string name_container4;

DWORD load_pointer(DWORD paddr, std::vector<DWORD> offsets)
{
    DWORD oldProtect, newProtect;
    
    DWORD addr = paddr;

    if (VirtualProtect((LPVOID)addr, 4, PAGE_EXECUTE_READWRITE, &oldProtect))
        VirtualProtect((LPVOID)addr, 4, oldProtect, &newProtect);
    else
        return 0;

    for (DWORD i = 0; i < offsets.size(); ++i)
    {
        Sleep(8);
        addr = *(DWORD*)addr;

        addr += offsets[i];

        if (VirtualProtect((LPVOID)addr, 4, PAGE_EXECUTE_READWRITE, &oldProtect))
            VirtualProtect((LPVOID)addr, 4, oldProtect, &newProtect);
        else
            return 0;
    }

    return addr;
}

void ParseAddressesToJson()
{
    json jsonx = {
      {"ActivateScanAddress", (DWORD)&activatescanreceived},
      {"playweaponsanimationsignal",(DWORD)&playweaponsanimationsignal },
      {"playtrashanimationsignal", (DWORD)&playtrashanimationsignal},
      {"playshieldsanimationsignal", (DWORD)&playshieldsanimationsignal},
      {"RainbowOpInitiated", (DWORD)&RainbowOpInitiated},
      {"allsamecolorinitiated", (DWORD)&allsamecolorinitiated},
      {"changepetinitiated", (DWORD)&changepetinitiated},
      {"changeskininitiated", (DWORD)&changeskininitiated},
      {"changehatinitiated", (DWORD)&changehatinitiated},
      {"changecolorinitiated", (DWORD)&changecolorinitiated},
      {"changenameinitiated", (DWORD)&changenameinitiated},
      {"sabotageinitiated", (DWORD)&sabotageinitiated},
      {"closealldoorsinitiated", (DWORD)&closealldoorsinitiated},
      {"ColorAvailable", (DWORD)&ColorAvailable},
      {"SabotageLights", (DWORD)&SabotageLights},
      {"SabotageComms", (DWORD)&SabotageComms},
      {"SabotageO2", (DWORD)&SabotageO2},
      {"SabotageReactor", (DWORD)&SabotageReactor},
      {"RepairO2", (DWORD)&RepairO2},
      {"RepairComms", (DWORD)&RepairComms},
      {"RepairReactor", (DWORD)&RepairReactor},
      {"RepairLights", (DWORD)&RepairLights},
      {"AllSameNameInitiated", (DWORD)&AllSameNameInitiated},
      {"RainbowName", (DWORD)&RainbowName},
      {"AllPlayersRainbowInitiated", (DWORD)&AllPlayersRainbowInitiated},
      {"ColorSelected", (DWORD)&ColorSelected},
      {"PetSelected", (DWORD)&PetSelected},
      {"HatSelected", (DWORD)&HatSelected},
      {"SkinSelected", (DWORD)&SkinSelected},
      {"AllColor", (DWORD)&AllColor},
      {"name_container", (DWORD)&name_container+12},
      {"name_container2", (DWORD)&name_container2+12},
      {"name_container3", (DWORD)&name_container3+12},
      {"name_container4", (DWORD)&name_container4+12},
      {"FakeCamerasEnabled", (DWORD)&FakeCamerasEnabled},
      {"DisableFakeCamera", (DWORD)&DisableFakeCamera},
      {"DisableLights", (DWORD)&DisableLights},
      {"Re_enableLights", (DWORD)&Re_enableLights},
      {"CompleteTasksActive", (DWORD)&CompleteTasksActive}
    };
    std::ofstream outSettings(XFORCEPATH);
    outSettings << std::setw(4) << jsonx << std::endl;
}

template <typename T> T read(DWORD address)
{
    T buffer;
    ReadProcessMemory(GetCurrentProcess(), (LPCVOID)address, &buffer, sizeof(T), NULL);
    return buffer;
}

void play_weapons_animation()
{
    __asm {

        push ebp
        mov ebp, esp
        push 6
        mov eax, player_control_address
        mov eax, [eax]
        mov eax, [eax + 0x5C]
        test eax, eax
        je endsc
        mov eax, [eax + 0x00]
        test eax, eax
        je endsc
        push eax
        call rpc_play_animation
        endsc :
        mov esp, ebp
        pop ebp
        xor eax, eax
        inc eax

    }


}

void RefreshPlayersCount()
{
    player_amount = 0;
    
    DWORD Player1Instance = load_pointer(player_control_address, { 0x5C, 0x08, 0x08, 0x10 });
    DWORD Player2Instance = load_pointer(player_control_address, { 0x5C, 0x08, 0x08, 0x14 });
    DWORD Player3Instance = load_pointer(player_control_address, { 0x5C, 0x08, 0x08, 0x18 });
    DWORD Player4Instance = load_pointer(player_control_address, { 0x5C, 0x08, 0x08, 0x1C });
    DWORD Player5Instance = load_pointer(player_control_address, { 0x5C, 0x08, 0x08, 0x20 });
    DWORD Player6Instance = load_pointer(player_control_address, { 0x5C, 0x08, 0x08, 0x24 });
    DWORD Player7Instance = load_pointer(player_control_address, { 0x5C, 0x08, 0x08, 0x28 });
    DWORD Player8Instance = load_pointer(player_control_address, { 0x5C, 0x08, 0x08, 0x2C });
    DWORD Player9Instance = load_pointer(player_control_address, { 0x5C, 0x08, 0x08, 0x30 });
    DWORD Player10Instance = load_pointer(player_control_address, { 0x5C, 0x08, 0x08, 0x34 });

    if (*(int*)Player1Instance != 0)
    {
        ++player_amount;
    }
    if (*(int*)Player2Instance != 0)
    {
        ++player_amount;
    }
    if (*(int*)Player3Instance != 0)
    {
        ++player_amount;
    }
    if (*(int*)Player4Instance != 0)
    {
        ++player_amount;
    }
    if (*(int*)Player5Instance != 0)
    {
        ++player_amount;
    }
    if (*(int*)Player6Instance != 0)
    {
        ++player_amount;
    }
    if (*(int*)Player7Instance != 0)
    {
        ++player_amount;
    }
    if (*(int*)Player8Instance != 0)
    {
        ++player_amount;
    }
    if (*(int*)Player9Instance != 0)
    {
        ++player_amount;
    }
    if (*(int*)Player10Instance != 0)
    {
        ++player_amount;
    }
}

bool isColorAvailable(DWORD n)
{
    RefreshPlayersCount();
    for (DWORD i = 0; i < player_amount; i++)
    {
        if (read<DWORD>(load_pointer(player_control_address, { 0x5C, 0x08, 0x08, 0x10 + (i * 0x04), 0x34, 0x14 })) == n)
            return false;
    }
    return true;
}


std::string read_from_file(std::wstring const& path)
{
    std::ifstream t(path);
    std::stringstream buffer;
    buffer << t.rdbuf();
    return buffer.str();
}

void ACTIVATE_SCAN1()
{
    __asm {

        push ebp
        mov ebp, esp
        mov eax, 0x01
        push eax
        mov eax, player_control_address
        mov eax, [eax]
        mov eax, [eax + 0x5C]
        mov eax, [eax + 0x00]
        test eax, eax
        push eax
        call ACTIVATE_SCAN
        mov esp, ebp
        pop ebp
        xor eax, eax
        inc eax


    }
}

void DEACTIVATE_SCAN123()
{
    __asm {

        push ebp
        mov ebp, esp
        mov eax, 0x00
        push eax
        mov eax, player_control_address
        mov eax, [eax]
        mov eax, [eax + 0x5C]
        mov eax, [eax + 0x00]
        test eax, eax
        push eax
        call ACTIVATE_SCAN
        mov esp, ebp
        pop ebp
        xor eax, eax
        inc eax


    }
}


void play_trash_animation()
{
    __asm {

        push ebp
        mov ebp, esp
        push 9
        mov eax, player_control_address
        mov eax, [eax]
        mov eax, [eax + 0x5C]
        test eax, eax
        je endsc
        mov eax, [eax + 0x00]
        test eax, eax
        je endsc
        push eax
        call rpc_play_animation
        endsc:
        mov esp, ebp
        pop ebp
        xor eax, eax
        inc eax



    }


}

void play_shields_animation()
{
    __asm 
    {
        push ebp
        mov ebp, esp
        push 1
        mov eax, player_control_address
        mov eax, [eax]
        mov eax, [eax + 0x5C]
        test eax, eax
        je endsc
        mov eax, [eax + 0x00]
        test eax, eax
        je endsc
        push eax
        call rpc_play_animation
        endsc:
        mov esp, ebp
        pop ebp
        xor eax, eax
        inc eax


    }


}

void Color_Change()
{
    __asm {

        push ebp
        mov ebp, esp
        mov eax, ColorSelected
        push eax
        mov eax, player_control_address
        mov eax, [eax]
        mov eax, [eax + 0x5C]
        mov eax, [eax + 0x00]
        test eax, eax
        push eax
        call SetLocalPlayerColorAddress
        mov esp, ebp
        pop ebp
        xor eax, eax
        inc eax
        

    }
}

void Pet_Change()
{
    __asm {

        push ebp
        mov ebp, esp
        mov eax, PetSelected
        push eax
        mov eax, player_control_address
        mov eax, [eax]
        mov eax, [eax + 0x5C]
        mov eax, [eax + 0x00]
        test eax, eax
        push eax
        call SetPetAddress
        mov esp, ebp
        pop ebp
        xor eax, eax
        inc eax


    }
}

void Hat_Change()
{
    __asm {

        push ebp
        mov ebp, esp
        mov eax, HatSelected
        push eax
        mov eax, player_control_address
        mov eax, [eax]
        mov eax, [eax + 0x5C]
        mov eax, [eax + 0x00]
        test eax, eax
        push eax
        call SetHat
        mov esp, ebp
        pop ebp
        xor eax, eax
        inc eax


    }
}

void Skin_Change()
{
    __asm {

        push ebp
        mov ebp, esp
        mov eax, SkinSelected
        push eax
        mov eax, player_control_address
        mov eax, [eax]
        mov eax, [eax + 0x5C]
        mov eax, [eax + 0x00]
        test eax, eax
        push eax
        call RpcSetSkin
        mov esp, ebp
        pop ebp
        xor eax, eax
        inc eax


    }
}

void Server_SideColor_Change1()
{
    __asm {

        push ebp
        mov ebp, esp
        mov eax, AllColor
        push eax
        mov eax, player_control_address
        mov eax, [eax]
        mov eax, [eax + 0x5C]
        mov eax, [eax + 0x8]
        mov eax, [eax + 0x8]
        mov eax, [eax + 0x10]
        test eax, eax
        push eax
        call RpcSetColor
        mov esp, ebp
        pop ebp
        xor eax, eax
        inc eax


    }
}

void Server_SideColor_Change2()
{
    __asm {

        push ebp
        mov ebp, esp
        mov eax, AllColor
        push eax
        mov eax, player_control_address
        mov eax, [eax]
        mov eax, [eax + 0x5C]
        mov eax, [eax + 0x8]
        mov eax, [eax + 0x8]
        mov eax, [eax + 0x14]
        test eax, eax
        push eax
        call RpcSetColor
        mov esp, ebp
        pop ebp
        xor eax, eax
        inc eax


    }
}

void Server_SideColor_Change3()
{
    __asm {

        push ebp
        mov ebp, esp
        mov eax, AllColor
        push eax
        mov eax, player_control_address
        mov eax, [eax]
        mov eax, [eax + 0x5C]
        mov eax, [eax + 0x8]
        mov eax, [eax + 0x8]
        mov eax, [eax + 0x18]
        test eax, eax
        push eax
        call RpcSetColor
        mov esp, ebp
        pop ebp
        xor eax, eax
        inc eax


    }
}

void Server_SideColor_Change4()
{
    __asm {

        push ebp
        mov ebp, esp
        mov eax, AllColor
        push eax
        mov eax, player_control_address
        mov eax, [eax]
        mov eax, [eax + 0x5C]
        mov eax, [eax + 0x8]
        mov eax, [eax + 0x8]
        mov eax, [eax + 0x1C]
        test eax, eax
        push eax
        call RpcSetColor
        mov esp, ebp
        pop ebp
        xor eax, eax
        inc eax


    }
}

void Server_SideColor_Change5()
{
    __asm {

        push ebp
        mov ebp, esp
        mov eax, AllColor
        push eax
        mov eax, player_control_address
        mov eax, [eax]
        mov eax, [eax + 0x5C]
        mov eax, [eax + 0x8]
        mov eax, [eax + 0x8]
        mov eax, [eax + 0x20]
        test eax, eax
        push eax
        call RpcSetColor
        mov esp, ebp
        pop ebp
        xor eax, eax
        inc eax


    }
}

void Server_SideColor_Change6()
{
    __asm {

        push ebp
        mov ebp, esp
        mov eax, AllColor
        push eax
        mov eax, player_control_address
        mov eax, [eax]
        mov eax, [eax + 0x5C]
        mov eax, [eax + 0x8]
        mov eax, [eax + 0x8]
        mov eax, [eax + 0x24]
        test eax, eax
        push eax
        call RpcSetColor
        mov esp, ebp
        pop ebp
        xor eax, eax
        inc eax


    }
}

void Server_SideColor_Change7()
{
    __asm {

        push ebp
        mov ebp, esp
        mov eax, AllColor
        push eax
        mov eax, player_control_address
        mov eax, [eax]
        mov eax, [eax + 0x5C]
        mov eax, [eax + 0x8]
        mov eax, [eax + 0x8]
        mov eax, [eax + 0x28]
        test eax, eax
        push eax
        call RpcSetColor
        mov esp, ebp
        pop ebp
        xor eax, eax
        inc eax


    }
}

void Server_SideColor_Change8()
{
    __asm {

        push ebp
        mov ebp, esp
        mov eax, AllColor
        push eax
        mov eax, player_control_address
        mov eax, [eax]
        mov eax, [eax + 0x5C]
        mov eax, [eax + 0x8]
        mov eax, [eax + 0x8]
        mov eax, [eax + 0x2C]
        test eax, eax
        push eax
        call RpcSetColor
        mov esp, ebp
        pop ebp
        xor eax, eax
        inc eax


    }
}

void Server_SideColor_Change9()
{
    __asm {

        push ebp
        mov ebp, esp
        mov eax, AllColor
        push eax
        mov eax, player_control_address
        mov eax, [eax]
        mov eax, [eax + 0x5C]
        mov eax, [eax + 0x8]
        mov eax, [eax + 0x8]
        mov eax, [eax + 0x30]
        test eax, eax
        push eax
        call RpcSetColor
        mov esp, ebp
        pop ebp
        xor eax, eax
        inc eax


    }
}

void Server_SideColor_Change10()
{
    __asm {

        push ebp
        mov ebp, esp
        mov eax, AllColor
        push eax
        mov eax, player_control_address
        mov eax, [eax]
        mov eax, [eax + 0x5C]
        mov eax, [eax + 0x8]
        mov eax, [eax + 0x8]
        mov eax, [eax + 0x34]
        test eax, eax
        push eax
        call RpcSetColor
        mov esp, ebp
        pop ebp
        xor eax, eax
        inc eax


    }
}

DWORD get_switch_base()
{
    DWORD ShipStatusInstancePointerForSabotage = load_pointer(RRSPointerFirstAddress, { 0x5C, 0x00, 0x00 });
    return load_pointer(ShipStatusInstancePointerForSabotage + 0x8C, { 0x0C, 0x1C, 0x00 });
}

void repair_light()
{
    DWORD ShipStatusInstancePointerForSabotage = load_pointer(RRSPointerFirstAddress, { 0x5C, 0x00, 0x00 });

    DWORD switch_base = get_switch_base();
    BYTE current_state, expected_state;

    current_state = read<BYTE>(switch_base + 0x14);
    expected_state = read<BYTE>(switch_base + 0x15);
    if (current_state != expected_state) {
        for (auto i = 0; i < 5; ++i) {
            auto switchMask = 1 << (i & 0x1F);
            if ((current_state & switchMask) != (expected_state & switchMask)) {
                reinterpret_cast<void(*)(DWORD, DWORD, DWORD)>(RpcRepairSystem)(ShipStatusInstancePointerForSabotage, 7, (DWORD)i);
                Sleep(250);
            }
        }
    }

}

void call_Sabotage_Or_Repair(DWORD firstarg, DWORD secarg)
{
    DWORD ShipStatusInstancePointerForSabotage = load_pointer(RRSPointerFirstAddress, { 0x5C, 0x00, 0x00 });

    reinterpret_cast<void(*)(DWORD, DWORD, DWORD)>(RpcRepairSystem)(ShipStatusInstancePointerForSabotage, firstarg , secarg );

}

void Close_All_Doors(std::vector<DWORD> ids)
{
    DWORD ShipStatusInstancePointer = load_pointer(RRSPointerFirstAddress, {0x5C, 0x00, 0x00});

    for (auto& it: ids)
    {
        reinterpret_cast<void(*)(DWORD, DWORD)>(call_RpcCloseDoors)(ShipStatusInstancePointer, it);
        Sleep(150);
    }
}

void Call_Close_All_Doors_Function()
{
    DWORD MapID = load_pointer(player_control_address, { 0x5C, 0x04, 0x10 });

    if (*(int*)MapID == 0)
    {
        Close_All_Doors({ 0x01, 0x02, 0x04, 0x07, 0x0B, 0x0A, 0x0D });
    }
    else if (*(int*)MapID == 2)
    {
        Close_All_Doors({ 0x01, 0x15, 0x17, 0x07, 0x08, 0x0E, 0x0C });
    }
    else if (*(int*)MapID == 3)
    {
        Close_All_Doors({ 0x0E, 0x2E, 0x28, 0x2A, 0x2D, 0x21 });
    }

}

void CallAllSameColor()
{
    
    DWORD LocalPlayerInstance = load_pointer(player_control_address, { 0x5C, 0x00, 0x00 });
    DWORD Player2Instance = load_pointer(player_control_address, { 0x5C, 0x08, 0x08, 0x14 });
    DWORD Player3Instance = load_pointer(player_control_address, { 0x5C, 0x08, 0x08, 0x18 });
    DWORD Player4Instance = load_pointer(player_control_address, { 0x5C, 0x08, 0x08, 0x1C });
    DWORD Player5Instance = load_pointer(player_control_address, { 0x5C, 0x08, 0x08, 0x20 });
    DWORD Player6Instance = load_pointer(player_control_address, { 0x5C, 0x08, 0x08, 0x24 });
    DWORD Player7Instance = load_pointer(player_control_address, { 0x5C, 0x08, 0x08, 0x28 });
    DWORD Player8Instance = load_pointer(player_control_address, { 0x5C, 0x08, 0x08, 0x2C });
    DWORD Player9Instance = load_pointer(player_control_address, { 0x5C, 0x08, 0x08, 0x30 });
    DWORD Player10Instance = load_pointer(player_control_address, { 0x5C, 0x08, 0x08, 0x34 });

    Server_SideColor_Change1();
    if (*(int*)Player2Instance != 0)
    {
        Server_SideColor_Change2();
    }
    if (*(int*)Player3Instance != 0)
    {
        Server_SideColor_Change3();
    }
    if (*(int*)Player4Instance != 0)
    {
        Server_SideColor_Change4();
    }
    if (*(int*)Player5Instance != 0)
    {
        Server_SideColor_Change5();
    }
    if (*(int*)Player6Instance != 0)
    {
        Server_SideColor_Change6();
    }
    if (*(int*)Player7Instance != 0)
    {
        Server_SideColor_Change7();
    }
    if (*(int*)Player8Instance != 0)
    {
        Server_SideColor_Change8();
    }
    if (*(int*)Player9Instance != 0)
    {
        Server_SideColor_Change9();
    }
    if (*(int*)Player10Instance != 0)
    {
        Server_SideColor_Change10();
    }

}



DWORD set_name_inner(DWORD instance){
    
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
        mov ebp,esp

        mov eax, player_control_address
        mov eax, [eax]
        mov eax, [eax + 0x5C]
        mov eax, [eax + 0x00]

        mov ecx,eax

        mov eax,[eax + 0x34]
        mov eax,[eax + 0x0C]
        mov eax,[eax]
        push eax
        call set_name_inner
        push eax
        mov eax, player_control_address
        mov eax, [eax]
        mov eax, [eax + 0x5C]
        mov eax, [eax + 0x00]
        push eax
        
        call call_name


        mov esp,ebp
        pop ebp
        popad

    }

}


void Change_every_name()
{
    RefreshPlayersCount();
    DWORD s_instance_ptr = load_pointer(player_control_address, { 0x5C, 0x00, 0x34, 0xC, 0x00, 0x00 });
    name_container3.instance = s_instance_ptr;
    name_container3.length = (DWORD)wcslen(name_container3.content);
    DWORD s_instance_ptr2 = load_pointer(player_control_address, { 0x5C, 0x00, 0x34, 0xC, 0x00, 0x00 });
    name_container4.instance = s_instance_ptr2;
    name_container4.length = (DWORD)wcslen(name_container4.content);
    for (unsigned int p = 0; p < player_amount; ++p)
    {
        DWORD player_instance = load_pointer(player_control_address, { 0x5C, 0x8, 0x8, (0x10 + (p * 4)), 0x0 });
        reinterpret_cast<void(*)(DWORD, DWORD)>(RpcSetName)(player_instance, (DWORD)&name_container3);
        DWORD player_instance2 = load_pointer(player_control_address, { 0x5C, 0x8, 0x8, (0x10 + (p * 4)), 0x0 });
        reinterpret_cast<void(*)(DWORD, DWORD)>(RpcSetName)(player_instance2, (DWORD)&name_container4);
    }
}



void Set_Name_Secondary()
{

    __asm
    {

        pushad
        push ebp
        mov ebp, esp

        mov eax, player_control_address
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
        mov eax, player_control_address
        mov eax, [eax]
        mov eax, [eax + 0x5C]
        mov eax, [eax + 0x00]
        push eax

        call call_name


        mov esp, ebp
        pop ebp
        popad

    }

}




 

DWORD WINAPI main(LPVOID lpParam)
{
    
    XFORCEPATH = getDllDirectory();
    XFORCEPATH = XFORCEPATH + JsonFileName;
    SpaceCheatModeFullPath = getDllDirectory();
    SpaceCheatModeFullPath = SpaceCheatModeFullPath + SpaceCheatModePath;
    if (read_from_file(SpaceCheatModeFullPath) == "")
    {
        MessageBoxA(0, "Could Not Find SpaceCheatMode. Make Sure Both SpaceCheatMode.exe and MagicMushroom.dll Are Located In The Same Folder.", "Error", 0);
    }

    Sleep(1000);

    ParseAddressesToJson();

    while (true)
    {
        if (activatescanreceived)
        {
            ACTIVATE_SCAN1();
            activatescanreceived = false;
            Sleep(10000);
            DEACTIVATE_SCAN123();
        }
        if (playweaponsanimationsignal)
        {
            play_weapons_animation();
            playweaponsanimationsignal = false;
            Sleep(50);
        }
        if (playtrashanimationsignal)
        {
            play_trash_animation();
            playtrashanimationsignal = false;
            Sleep(140);
        }
        if (playshieldsanimationsignal)
        {
            play_shields_animation();
            playshieldsanimationsignal = false;
            Sleep(140);
        }
        if (changecolorinitiated)
        {
            Color_Change();
            changecolorinitiated = false;
        }
        if (changenameinitiated)
        {
            Set_Name();
            Sleep(50);
            Set_Name_Secondary();
            changenameinitiated = false;
            
        }
        if (closealldoorsinitiated)
        {
            Call_Close_All_Doors_Function();
            closealldoorsinitiated = false;
        }
        if (allsamecolorinitiated)
        {
            CallAllSameColor();
            allsamecolorinitiated = false;
        }
        if (sabotageinitiated)
        {
            DWORD MapIDxD = load_pointer(player_control_address, { 0x5C, 0x04, 0x10 });
            if (SabotageLights)
            {
                call_Sabotage_Or_Repair(7, 0);
                call_Sabotage_Or_Repair(7, 1);
                call_Sabotage_Or_Repair(7, 2);
                call_Sabotage_Or_Repair(7, 3);
                SabotageLights = false;
            }
            if (SabotageComms)
            {
                call_Sabotage_Or_Repair(17, 14);
                SabotageComms = false;
            }
            if (SabotageO2)
            {
                if (*(int*)MapIDxD != 2)
                {
                    call_Sabotage_Or_Repair(17, 8);
                }
                SabotageO2 = false;
            }
            if (SabotageReactor)
            {
                if (*(int*)MapIDxD == 2)
                {
                    call_Sabotage_Or_Repair(17, 21);
                }
                else
                {
                    call_Sabotage_Or_Repair(17, 3);
                }

                SabotageReactor = false;
            }
            if (RepairComms)
            {
                if (*(int*)MapIDxD == 0 || *(int*)MapIDxD == 2 || *(int*)MapIDxD == 4)
                {
                    call_Sabotage_Or_Repair(14, 0);
                }
                else if (*(int*)MapIDxD == 1)
                {
                    call_Sabotage_Or_Repair(14, 16);
                    call_Sabotage_Or_Repair(14, 17);
                }

                RepairComms = false;
            }
            if (RepairO2)
            {
                if (*(int*)MapIDxD == 0 || *(int*)MapIDxD == 1)
                {
                    call_Sabotage_Or_Repair(8, 64);
                    call_Sabotage_Or_Repair(8, 65);
                }

                RepairO2 = false;
            }
            if (RepairReactor)
            {
                if (*(int*)MapIDxD == 2)
                {
                    call_Sabotage_Or_Repair(21, 64);
                    call_Sabotage_Or_Repair(21, 65);
                }
                else if(*(int*)MapIDxD == 0 || *(int*)MapIDxD == 1)
                {
                    call_Sabotage_Or_Repair(3, 64);
                    call_Sabotage_Or_Repair(3, 65);
                }
                else
                {
                    call_Sabotage_Or_Repair(3, 16);
                    call_Sabotage_Or_Repair(3, 17);
                }

                RepairReactor = false;
            }
            if (RepairLights)
            {
                repair_light();
                RepairLights = false;
            }

            sabotageinitiated = false;
        }
        if (RainbowOpInitiated)
        {
            ColorSelected = rand() % 11;
            DWORD LocalPlayerInstance = load_pointer(player_control_address, { 0x5C, 0x00, 0x00 });
            reinterpret_cast<void(*)(DWORD, DWORD)>(SetLocalPlayerColorAddress)(LocalPlayerInstance, ColorSelected);
            Sleep(35);
            
        }
        if (AllPlayersRainbowInitiated)
        {
            RefreshPlayersCount();
            for (unsigned int APR = 0; APR < player_amount; ++APR)
            {
                AllColor = rand() % 11;
                DWORD PlayerInstanceLocalForAPR = load_pointer(player_control_address, { 0x5C, 0x8, 0x8, (0x10 + (APR * 4)), 0x0 });
                reinterpret_cast<void(*)(DWORD, DWORD)>(RpcSetColor)(PlayerInstanceLocalForAPR, AllColor);

            }
        }
        if (RainbowName)
        {

            for (unsigned int i = 0; i < 3; ++i)
            {
                RGBz[i] = std::sin(freq * cnt + (i * 2)) * 127 + 128;
                NameColorAddress = load_pointer(player_control_address, { 0x5C, 0x00, 0x4C, 0x30 + ((i * 0x04)) });
                *(float*)NameColorAddress = RGBz[i] / 255;
            }


            // Probably redundant
            if (cnt++ >= (uint32_t)-1) cnt = 0;



            /*for (unsigned int xD = 0; xD < 3; xD++)
            {
                RGBVelocity[xD] = RGBz[xD] < 10 ? std::abs(RGBVelocity[xD]) : (RGBz[xD] > 240 ? -std::abs(RGBVelocity[xD]) : RGBVelocity[xD]);
                RGBz[xD] = RGBz[xD] + RGBVelocity[xD];
                NameColorAddress = load_pointer(player_control_address, {0x5C, 0x00, 0x4C, 0x30 + ((xD * 0x04))});
                *(float*)NameColorAddress = RGBz[xD] / 255;
            }
            */
            
        }
        if (AllSameNameInitiated)
        {
            Change_every_name();
            AllSameNameInitiated = false;
        }
        if (changepetinitiated)
        {
            Pet_Change();
            changepetinitiated = false;
        }
        if (changehatinitiated)
        {
            Hat_Change();
            changehatinitiated = false;
        }
        if (changeskininitiated)
        {
            Skin_Change();
            changeskininitiated = false;
        }
        if (FakeCamerasEnabled)
        {
            DWORD ShipStatusInstancePointer5 = load_pointer(RRSPointerFirstAddress, { 0x5C, 0x00, 0x00 });
            reinterpret_cast<void(*)(DWORD, DWORD, DWORD)>(RpcRepairSystem)(ShipStatusInstancePointer5, 0xB, 1);
            FakeCamerasEnabled = false;
        }
        if (DisableFakeCamera)
        {
            DWORD ShipStatusInstancePointer5 = load_pointer(RRSPointerFirstAddress, { 0x5C, 0x00, 0x00 });
            reinterpret_cast<void(*)(DWORD, DWORD, DWORD)>(RpcRepairSystem)(ShipStatusInstancePointer5, 0xB, 0);
            DisableFakeCamera = false;
        }
        if (DisableLights)
        {
            if (LightsState == false)
            {
                LightsState = true;
            }
            DWORD ShipStatusInstancePointer25 = load_pointer(RRSPointerFirstAddress, { 0x5C, 0x00, 0x00 });
            reinterpret_cast<void(*)(DWORD, DWORD, DWORD)>(RpcRepairSystem)(ShipStatusInstancePointer25, 7, 5);
            DisableLights = false;
        }
        if (Re_enableLights)
        {
            if (LightsState)
            {
                LightsState = false;
                DWORD ShipStatusInstancePointer25 = load_pointer(RRSPointerFirstAddress, { 0x5C, 0x00, 0x00 });
                reinterpret_cast<void(*)(DWORD, DWORD, DWORD)>(RpcRepairSystem)(ShipStatusInstancePointer25, 7, 5);
                Re_enableLights = false;
            }
        }
        if (CompleteTasksActive)
        {
            for (unsigned int k = 0; k < *(int*)load_pointer(player_control_address, { 0x5C, 0x00, 0x78, 0xC }); ++k)
            {
                DWORD TaskIDAddr = load_pointer(player_control_address, { 0x5C, 0x00, 0x78, 0x8, (0x10 + (k * 0x4)), 0x10 });
                DWORD LocalPlayerInstance = load_pointer(player_control_address, { 0x5C, 0x00, 0x00 });
                int TaskID = *(int*)TaskIDAddr;
                reinterpret_cast<void(*)(DWORD, int)>(RpcCompleteTask)(LocalPlayerInstance, TaskID);
                Sleep(150);
            }
            CompleteTasksActive = false;
        }
        Sleep(100);
    }
    return TRUE;
}



BOOL APIENTRY DllMain(HMODULE hModule, DWORD reason, LPVOID lpReserved)
{
    if (reason == DLL_PROCESS_ATTACH)
    {
        CreateThread(0, 4096, &main, 0, 0, NULL);
    }
    return TRUE;
}
