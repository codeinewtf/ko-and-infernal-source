
#include <dxgi.h>

#include <winnt.h>
#include <winternl.h>
#include "vmp_sdk.h"
#include "imports.h"



#define Release release

#define nocrt_max(a,b)            (((a) > (b)) ? (a) : (b))
#define nocrt_min(a,b)            (((a) < (b)) ? (a) : (b))

bool wake = true;
DWORD64 __go;

// #include "eac.h"


using _CreateDirectoryA___ = bool(__cdecl*)(LPCSTR, LPSECURITY_ATTRIBUTES);
_CreateDirectoryA___ m_CreateDirectoryA;

void UI_Update(void* instance) {
    if (wake) {
        __go = Il2cpp::recreated_object_new(Il2cpp::InitClass(_("GameObject"), _("UnityEngine")));

        GUI::GuiMethods::create(__go, _(L""));
        GUI::GuiMethods::add_component(__go, Il2cpp::TypeGetObject(_(""), _("DevControls")));
        GUI::dont_destroy_on_load(__go);
        wake = false;
    }
    GUI::GuiMethods::Update(instance);
}

namespace module
{
    DWORD64 kernel32 = 0;
}

namespace util
{
    auto __CreateThread = reinterpret_cast<void(*)(int, int, LPTHREAD_START_ROUTINE, int, int, int)>(0);
}


DWORD64 GetFunction(const char* modename, const char* func)
{
    return Il2cpp_Utils::GetExport((DWORD64)Il2cpp_Utils::GetModuleBase_Wrapper(modename), func);
}

bool initAllMethods()
{


    static bool isInited = false;

    if (!isInited) {
        g_Base = (DWORD64)Il2cpp_Utils::GetModuleBase_Wrapper(_("GameAssembly.dll"));
        Crt_strstr = (strstrf___)Il2cpp_Utils::GetExport((DWORD64)Il2cpp_Utils::GetModuleBase_Wrapper(_("ucrtbase.dll")), _("strstr"));
        m_PlaySound = (playsoundf___)Il2cpp_Utils::GetExport((DWORD64)Il2cpp_Utils::GetModuleBase_Wrapper(_("Winmm.dll")), _("PlaySound"));
        f_swprint = (_swprintf___)Il2cpp_Utils::GetExport((DWORD64)Il2cpp_Utils::GetModuleBase_Wrapper(_("msvcrt.dll")), _("swprintf"));

        auto initMethod = reinterpret_cast<__int64(*)(__int64, __int64)>(Il2cpp::FindPattern(_("48 89 5C 24 18 41 56 48 83 EC 40 33 DB 44 0F B6 D2 44 8B CB 4C 8B F1"), _("GameAssembly.dll")));
        initMethod(g_Base + offsets::Method$BaseEntity_ServerRPCPlayerProjectileShoot__, 1);
        initMethod(g_Base + offsets::Method$BaseEntity_ServerRPC_PlayerProjectileAttack___, 1);

        // URLDownloadToFile((LPUNKNOWN)NULL, _(L"https://cdn.discordapp.com/attachments/1101583798409384017/1125104206462849114/kozimozi"),_(L"C:\\testassets\\kozimozi"), (DWORD)0, (LPBINDSTATUSCALLBACK)NULL);

        // LPCWSTR,_In_opt_ LPCWSTR,DWORD, _In_opt_ LPBINDSTATUSCALLBACK
        // URLDownloadToFileA((LPUNKNOWN)0, (LPCWSTR)0, _In_opt_ LPCWSTR, DWORD, _In_opt_ LPBINDSTATUSCALLBACK);


       // Urlmon.dll
        // m_URLDownloadToFile = (_URLDownloadToFile___)Il2cpp_Utils::GetExport((DWORD64)Il2cpp_Utils::GetModuleBase_Wrapper(_("Urlmon.dll")), _("URLDownloadToFile"));
        m_CreateFileA = (CFW)GetFunction(_("kernel32.dll"), _("CreateFileA"));
        m_WriteFile = (WFEX)GetFunction(_("kernel32.dll"), _("WriteFile"));
        m_ReadFile = (RFEX)GetFunction(_("kernel32.dll"), _("ReadFile"));
        m_CloseHandle = (CH)GetFunction(_("kernel32.dll"), _("CloseHandle"));
        m_DeleteFileW = (DFW)GetFunction(_("kernel32.dll"), _("DeleteFileW"));
        m_GetFileSizeEx = (GFSEX)GetFunction(_("kernel32.dll"), _("GetFileSizeEx"));
        m_PathFileExistsW = (PFEW)GetFunction(_("shlwapi.dll"), _("PathFileExistsW"));
        m_SHGetFolderPathW = (SHGFPW)GetFunction(_("shell32.dll"), _("SHGetFolderPathW"));
        // f_swprint = (_swprintf___)Il2cpp_Utils::GetExport((DWORD64)Il2cpp_Utils::GetModuleBase_Wrapper(_("msvcrt.dll")), _("swprintf"));
      /*  m_DeleteFile = (_DeleteFile)GetFunction(_("kernel32.dll"), _("DeleteFileW"));
        m_WriteFile = (_WriteFile)GetFunction(_("kernel32.dll"), _("WriteFile"));
        m_CreateFileW = (_CreateFileW)GetFunction(_("kernel32.dll"), _("CreateFileW"));*/

        Il2cpp::Il2cppInit();
        GUI::GuiMethods::InitMethods();
        GUI::GuiMethods::InitMethods2();
        Unity::InitUnity();
        Classes::InitClasses();
        Classes::InitClasses2();
        Hooks::InitHooks();
        Dump::InitDumper1();
        Dump::InitDumper2();
        Dump::InitDumper3();
        InitExploits();

        isInited = true;
    }

    return isInited;
}

void CleanOverlay()
{

}


void DownloadAssets()
{
    /* m_URLDownloadToFile(NULL, _("https://cdn.discordapp.com/attachments/1101583798409384017/1125104205745639444/Asset.bundle"), _("C:\\Infernal\\Bundle\\"), 0, NULL);
     m_URLDownloadToFile(NULL, _("https://cdn.discordapp.com/attachments/1101583798409384017/1125104206156673136/babekfont"), _("C:\\Infernal\\Bundle\\"), 0, NULL);
     m_URLDownloadToFile(NULL, _("https://cdn.discordapp.com/attachments/1101583798409384017/1125104206462849114/kozimozi"), _("C:\\Infernal\\Bundle\\"), 0, NULL);*/
}

void OnViewmodelEvent()
{

}

bool CanHit(DWORD64 asdasd, HitTest info)
{
    return true;
}

DWORD64 LastUpdatedProjectile;
DWORD64 orig_blm;
int LoadTime = 0;



__int64 blm_hk() {
    if (!cokksdf) {
        m_PlaySound(reinterpret_cast<LPCUTSTR>(_("C:\\Infernal\\hit.wav")), NULL, SND_FILENAME | SND_ASYNC);
        cokksdf = true;
    }
    return 1;
}



bool Setup()
{
    // LI_FN(Sleep)(30000);

    if (initAllMethods()) {
        Il2cpp_Hook(&UI_Update, _("Update"), _("PerformanceUI"), _("Facepunch"), 0);
        Il2cpp_Hook(&OnGUI, _("OnGUI"), _("DevControls"), _(""), 0);
        Il2cpp_Hook(&UpdateProjectile_Hook, _("Update"), _("Projectile"), _(""), 0);

        // Il2cpp_Hook(&CleanOverlay, _("Update"), _("CameraMan"), _(""), 0);
        Il2cpp_Hook(&CleanOverlay, _("Update"), _("WaterOverlay"), _(""), 0);
        Il2cpp_Hook(&CleanOverlay, _("Update"), _("ColdOverlay"), _(""), 0);

        Virtual_Hook(_("BasePlayer"), _("ClientInput"), &hk_ClientInput); // LaunchProjectile_hk
        Virtual_Hook(_("BaseMelee"), _("ProcessAttack"), &ProcessAttack_hk); // ProcessAttack
        //Virtual_Hook(_("Projectile"), _("CalculateEffectScale"), &CalculateEffectScale_hk); // LaunchProjectile_hk // ProcessAttack
        Virtual_Hook(_("BaseProjectile"), _("CanAttack"), &CanAttack_hk); // public virtual bool CanAttack() { }
        Virtual_Hook(_("BaseProjectile"), _("CanAim"), &CanAim_hk); // public virtual bool CanAttack() { }

        return true;
    }

    return false;
}

//extern "C" IMAGE_DOS_HEADER __ImageBase;
//
//
//
//BOOL __stdcall DllMain(std::uintptr_t mod, std::uint32_t call_reason, std::uintptr_t reserved) {
//    if (call_reason == DLL_PROCESS_ATTACH) {
//
//       static bool thread_inited = false;
//        const auto NtHeader = (PIMAGE_NT_HEADERS)(((PUINT8)&__ImageBase) + __ImageBase.e_lfanew);
//        const auto EacBase = (PUINT8)mod;
//        const auto EOS_Entry = &EacBase[NtHeader->OptionalHeader.AddressOfEntryPoint];
//
//        if (!thread_inited) {
//            LI_FN(CreateThread).cached()(NULL, NULL, reinterpret_cast<LPTHREAD_START_ROUTINE>(&Setup), 0, 0, 0);
//            thread_inited = true;
//        }
//
//        auto EacMain = (decltype(&DllMain))(EOS_Entry);
//        return EacMain(mod, call_reason, reserved);
//    
//
//        LI_FN(CreateThread).cached()(NULL, NULL, reinterpret_cast<LPTHREAD_START_ROUTINE>(&Setup), 0, 0, 0);
//    }
//
//    return true;
//}

extern "C" IMAGE_DOS_HEADER __ImageBase;

BOOL __stdcall DllMain(std::uintptr_t mod, std::uint32_t call_reason, std::uintptr_t reserved) {
    if (call_reason == DLL_PROCESS_ATTACH) {
#ifdef INJECTOR
        static bool thread_inited = false;
        const auto NtHeader = (PIMAGE_NT_HEADERS)(((PUINT8)&__ImageBase) + __ImageBase.e_lfanew);
        const auto EacBase = (PUINT8)mod;
        const auto EOS_Entry = &EacBase[NtHeader->OptionalHeader.AddressOfEntryPoint];

        if (!thread_inited) {
            LI_FN(CreateThread).cached()(NULL, NULL, reinterpret_cast<LPTHREAD_START_ROUTINE>(&Setup), 0, 0, 0);
            thread_inited = true;
        }

        auto EacMain = (decltype(&DllMain))(EOS_Entry);
        return EacMain(mod, call_reason, reserved);

#else
        LI_FN(CreateThread).cached()(NULL, NULL, reinterpret_cast<LPTHREAD_START_ROUTINE>(&Setup), 0, 0, 0);
#endif
    }

    return TRUE;
}

//bool DllMain(uint64_t hModule, int ul_reason_for_call, uint64_t lpReserved)
//{
//    if (ul_reason_for_call == DLL_PROCESS_ATTACH)
//    {
//        /*static bool thread_inited = false;
//
//        module::kernel32 = (DWORD64)Il2cpp_Utils::GetModuleBase_Wrapper(_("kernel32.dll"));
//        eac::base = hModule;
//
//        eac::entry = (hModule + eac_data.entry);
//
//        if (!thread_inited)
//        {
//            util::__CreateThread = reinterpret_cast<decltype(util::__CreateThread)>(Il2cpp_Utils::GetExport(module::kernel32, _("CreateThread")));
//            util::__CreateThread(NULL, NULL, reinterpret_cast<LPTHREAD_START_ROUTINE>(Setup), NULL, 0, 0);
//            thread_inited = true;
//        }
//
//        const auto eac_dll_fn = reinterpret_cast<decltype(&DllMain)>(hModule + eac_data.entry);
//
//        const auto result = eac_dll_fn(hModule, ul_reason_for_call, lpReserved);
//        return result;*/
//
//        Setup();
//    }
//
//    return true;
//}

//static bool thread_inited = false;
//
//module::kernel32 = (DWORD64)Il2cpp_Utils::GetModuleBase_Wrapper(_("kernel32.dll"));
//eac::base = hModule;
//
//eac::entry = (hModule + eac_data.entry);
//
//if (!thread_inited)
//{
//    util::__CreateThread = reinterpret_cast<decltype(util::__CreateThread)>(Il2cpp_Utils::GetExport(module::kernel32, _("CreateThread")));
//    util::__CreateThread(NULL, NULL, reinterpret_cast<LPTHREAD_START_ROUTINE>(Setup), NULL, 0, 0);
//    thread_inited = true;
//}
//
//const auto eac_dll_fn = reinterpret_cast<decltype(&DllMain)>(hModule + eac_data.entry);
//
//const auto result = eac_dll_fn(hModule, ul_reason_for_call, lpReserved);
//return result;

//static bool thread_inited = false;
//
//module::kernel32 = (DWORD64)Il2cpp_Utils::GetModuleBase_Wrapper(_("kernel32.dll"));
//eac::base = hModule;
//
//eac::entry = (hModule + eac_data.entry);
//
//if (!thread_inited)
//{
//    util::__CreateThread = reinterpret_cast<decltype(util::__CreateThread)>(Il2cpp_Utils::GetExport(module::kernel32, _("CreateThread")));
//    util::__CreateThread(NULL, NULL, reinterpret_cast<LPTHREAD_START_ROUTINE>(Setup), NULL, 0, 0);
//    thread_inited = true;
//}
//
//const auto eac_dll_fn = reinterpret_cast<decltype(&DllMain)>(hModule + eac_data.entry);
//
//const auto result = eac_dll_fn(hModule, ul_reason_for_call, lpReserved);
//return result;

//bool DllMain(uint64_t hModule, int ul_reason_for_call, uint64_t lpReserved)
//{
//    if (ul_reason_for_call == DLL_PROCESS_ATTACH)
//    {
//#ifdef EAC_RUN
//        static bool thread_inited = false;
//
//        module::kernel32 = mem::GetModuleAddress(XS(L"kernel32.dll"));
//        eac::base = hModule;
//
//        eac::entry = (hModule + eac_data.entry);
//
//        if (!thread_inited)
//        {
//            util::__CreateThread = reinterpret_cast<decltype(util::__CreateThread)>(mem::FindExportedFunction(module::kernel32, XS("CreateThread")));
//            util::__CreateThread(NULL, NULL, reinterpret_cast<LPTHREAD_START_ROUTINE>(Setup), NULL, 0, 0);
//            thread_inited = true;
//        }
//
//        const auto eac_dll_fn =
//            reinterpret_cast<decltype(&DllMain)>(hModule + eac_data.entry);
//
//        const auto result = eac_dll_fn(hModule, ul_reason_for_call, lpReserved);
//        return result;
//#else
//        Setup();
//#endif
//    }
//    return true;
//}