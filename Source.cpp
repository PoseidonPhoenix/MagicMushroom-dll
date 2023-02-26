#include <cinttypes>
#include <filesystem>
#include "ThreadSpoof.h"
#include "MainLoop.hpp"

EXTERN_C IMAGE_DOS_HEADER __ImageBase;

const std::wstring SpaceCheatModeFileName = L"\\SpaceCheatMode.exe";
const std::wstring JsonFileName = L"\\Addresses.json";

std::wstring getDllPath()
{
    TCHAR DllPath[MAX_PATH] = { 0 };
    GetModuleFileName((HINSTANCE)&__ImageBase, DllPath, _countof(DllPath));
    return DllPath;
}
std::wstring MyGetDllDirectory()
{
    std::filesystem::path NewDir(getDllPath());
    return NewDir.parent_path().wstring();
}
uintptr_t rFunction = GeneralInfo::Addresses::FixedUpdateAddress + 0x5;
__declspec(naked) void hFunction() {
    __asm push ebp;
    __asm mov ebp, esp
    __asm sub esp, 48;
    __asm call MainLoop
    __asm jmp rFunction;
}

//std::string ReadFromFile(const std::wstring& path)
//{
//    std::ifstream t(path);
//    std::stringstream buffer;
//    buffer << t.rdbuf();
//    return buffer.str();
//}

DWORD WINAPI main(LPVOID lpParam)
{
    
    std::wstring JsonFilePath = MyGetDllDirectory() + JsonFileName;
    Utils::JsonLoader::ParseAddressesToJson(JsonFilePath);
    std::wstring SpaceCheatModeFullPath = MyGetDllDirectory() + SpaceCheatModeFileName;
    
    /*if (ReadFromFile(SpaceCheatModeFullPath) == "")
    {
        MessageBoxA(0, "Could Not Find SpaceCheatMode. Make Sure Both SpaceCheatMode.exe and MagicMushroom.dll Are Located In The Same Folder.", "Error", 0);
    }*/

    Utils::Hook::placeJump(reinterpret_cast<void*>(GeneralInfo::Addresses::FixedUpdateAddress), &hFunction, 5);
    /*while (true)
    {
        MainLoop();
    }*/
    return TRUE;
}



BOOL APIENTRY DllMain(HMODULE hModule, DWORD reason, LPVOID lpReserved)
{
    if (reason == DLL_PROCESS_ATTACH)
    {
        SpoofThread(main, hModule);
        //CreateThread(0, 4096, &main, 0, 0, NULL);
    }
    return TRUE;
}
