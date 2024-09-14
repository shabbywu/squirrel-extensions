#include "plugins.h"
#include <map>

namespace plugins {
static std::map<std::string, BYTE *> plugins;

void load_plugins(LauncherContext *ctx) {
  std::filesystem::path plugin_dir = ctx->plugin_dir;
  if (!std::filesystem::exists(plugin_dir) ||
      !std::filesystem::is_directory(plugin_dir)) {
    return;
  }
  AddDllDirectory((PCWSTR)plugin_dir.wstring().c_str());

  for (const auto &entry : std::filesystem::directory_iterator(plugin_dir)) {
    if (entry.path().extension() != ".dll") {
      continue;
    }
    std::cout << "loading plugin: " << entry.path() << std::endl;
    size_t v_size = 0;
    BYTE *dll = peconv::load_pe_executable(
        (LPCTSTR)entry.path().string().c_str(), v_size, NULL);
    if (!dll) {
      std::cerr << "[!] Loading failed!" << std::endl;
      continue;
    }
    // if the loaded PE needs to access resources, you may need to connect it to
    // the PEB: peconv::set_main_module_in_peb((HMODULE)dll); load delayed
    // imports (if present):
    const ULONGLONG loadBase = (ULONGLONG)dll;
    peconv::load_delayed_imports(dll, loadBase);
    // if needed, you can run TLS callbacks before the Entry Point:
    peconv::run_tls_callbacks(dll, v_size);
    // calculate the Entry Point of the manually loaded module
    DWORD ep_rva = peconv::get_entry_point_rva(dll);
    if (!ep_rva) {
      std::cerr << "[!] Cannot fetch EP!" << std::endl;
      continue;
    }
    const ULONG_PTR ep_va = ep_rva + (ULONG_PTR)dll;
    // the prototype of the DllMain fuction:
    BOOL WINAPI _DllMain(HINSTANCE hinstDLL,  // handle to DLL module
                         DWORD fdwReason,     // reason for calling function
                         LPVOID lpvReserved); // reserved
    auto dll_main = reinterpret_cast<decltype(&_DllMain)>(ep_va);
    // call the Entry Point of the manually loaded PE :
    dll_main((HINSTANCE)dll, DLL_PROCESS_ATTACH, 0);

    // store dll
    plugins[entry.path().root_name().string()] = dll;
  }
}

void before_game_start(LauncherContext *ctx) {
  for (const auto [name, entry] : plugins) {
    FARPROC nOffset =
        peconv::get_exported_func(entry, (LPCSTR) "before_game_start");
    if (nOffset == NULL) {
      continue;
    }
    auto call = (void(__cdecl *)(LauncherContext *))nOffset;
    call(ctx);
  }
}

void on_squirrel_vm_init(LauncherContext *ctx) {
  for (const auto [name, entry] : plugins) {
    FARPROC nOffset;
    if (nOffset =
            peconv::get_exported_func(entry, (LPCSTR) "on_squirrel_vm_init");
        nOffset != NULL) {
      auto call = (void(__cdecl *)(HSQUIRRELVM))nOffset;
      call(ctx->root_vm);
    }

    if (nOffset = peconv::get_exported_func(entry,
                                            (LPCSTR) "on_squirrel_vm_init_ext");
        nOffset != NULL) {
      auto call = (void(__cdecl *)(LauncherContext *))nOffset;
      call(ctx);
    }
  }
}

void after_game_exit(LauncherContext *ctx) {}
} // namespace plugins
