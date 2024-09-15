#pragma once
#include <filesystem>

#include <map>
#include <squirrel.h>

struct LauncherContext {
public:
  std::filesystem::path plugin_dir;
  HSQUIRRELVM root_vm;
};

namespace plugins {
void load_plugins(LauncherContext *ctx);
void before_game_start(LauncherContext *ctx);
void on_squirrel_vm_init(LauncherContext *ctx);
void after_game_exit(LauncherContext *ctx);
} // namespace plugins
