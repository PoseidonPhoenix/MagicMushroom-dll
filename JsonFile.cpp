#include <sstream>
#include <fstream>
#include <iomanip>
#include "JsonFile.h"
#include "json.hpp"
#include "MainLoop.hpp"

using json = nlohmann::json;

namespace Utils
{
    namespace JsonLoader
    {
        void ParseAddressesToJson(const std::wstring& path)
        {
            json jsonx = {
              {"bActivateScanReceived", (DWORD)&bActivateScanReceived},
              {"bPlayWeaponsAnimationSignal",(DWORD)&bPlayWeaponsAnimationSignal},
              {"bPlayTrashAnimationSignal", (DWORD)&bPlayTrashAnimationSignal},
              {"bPlayShieldsAnimationSignal", (DWORD)&bPlayShieldsAnimationSignal},
              {"bRainbowOpInitiated", (DWORD)&bRainbowOpInitiated},
              {"bAllSameColorInitiated ", (DWORD)&bAllSameColorInitiated},
              {"bChangePetInitiated ", (DWORD)&bChangePetInitiated},
              {"bChangeSkinInitiated ", (DWORD)&bChangeSkinInitiated},
              {"bChangeHatInitiated ", (DWORD)&bChangeHatInitiated},
              {"bChangeColorInitiated ", (DWORD)&bChangeColorInitiated},
              {"bChangeNameInitiated ", (DWORD)&bChangeNameInitiated},
              {"bSabotageInitiated ", (DWORD)&bSabotageInitiated},
              {"bCloseAllDoorsInitiated ", (DWORD)&bCloseAllDoorsInitiated},
              {"bColorAvailable", (DWORD)&bColorAvailable},
              {"bSabotageLights ", (DWORD)&bSabotageLights},
              {"bSabotageComms", (DWORD)&bSabotageComms},
              {"bSabotageO2", (DWORD)&bSabotageO2},
              {"bSabotageReactor", (DWORD)&bSabotageReactor},
              {"bRepairO2", (DWORD)&bRepairO2},
              {"bRepairComms", (DWORD)&bRepairComms},
              {"bRepairReactor", (DWORD)&bRepairReactor},
              {"bRepairLights", (DWORD)&bRepairLights},
              {"bAllSameNameInitiated", (DWORD)&bAllSameNameInitiated},
              {"bAllPlayersRainbowInitiated", (DWORD)&bAllPlayersRainbowInitiated},
              {"ColorSelected", (DWORD)&Hacks::ColorSelected},
              {"PetSelected", (DWORD)&Hacks::PetSelected},
              {"HatSelected", (DWORD)&Hacks::HatSelected},
              {"SkinSelected", (DWORD)&Hacks::SkinSelected},
              {"AllColor", (DWORD)&Hacks::AllColor},
              /*{"name_container", (DWORD)&name_container+12},
              {"name_container2", (DWORD)&name_container2+12},
              {"name_container3", (DWORD)&name_container3+12},
              {"name_container4", (DWORD)&name_container4+12},*/
              {"bFakeCamerasEnabled", (DWORD)&bFakeCamerasEnabled},
              {"bDisableFakeCamera", (DWORD)&bDisableFakeCamera},
              {"bDisableLights", (DWORD)&bDisableLights},
              {"bReEnableLights", (DWORD)&bReEnableLights},
              {"bCompleteTasksActive", (DWORD)&bCompleteTasksActive}
            };
            std::ofstream outSettings(path);
            outSettings << std::setw(4) << jsonx << std::endl;
        }
    }
}