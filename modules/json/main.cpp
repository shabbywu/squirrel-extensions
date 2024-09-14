#include "detail/register.hpp"

extern "C" __declspec(dllexport) void on_squirrel_vm_init(HSQUIRRELVM v) {
  vm = new sqbind17::detail::VM(v);
  sqext_json::sqext_register_jsonlib_impl(*vm);
};

#include <windows.h>

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpReserved) {
  switch (fdwReason) {
  case DLL_PROCESS_ATTACH:
    break;
  case DLL_THREAD_ATTACH:
    break;
  case DLL_THREAD_DETACH:
    break;
  case DLL_PROCESS_DETACH:
    break;
  }
  return TRUE;
}
