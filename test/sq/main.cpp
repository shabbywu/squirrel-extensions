#include "plugins.h"
#include <format>
#include <iostream>
#include <sqbind17/sqbind17.hpp>

using namespace sqbind17;

void PrintVersionInfos() {
  std::cout << std::format("{} {} ({} bits)", SQUIRREL_VERSION,
                           SQUIRREL_COPYRIGHT, ((int)(sizeof(SQInteger) * 8)))
            << std::endl;
}

void Interactive(detail::GenericVM vm) {
  SQInteger done = 0;
  vm.bindFunc("exit", [&done]() { done = true; });

  PrintVersionInfos();
  while (!done) {
    std::string prev;
    std::string line;
    std::stringstream buff;
    std::cout << "\nsq>>> ";
    while (std::getline(std::cin, line)) {
      if (line.empty() && prev.empty()) {
        break;
      }
      prev = line;
      buff << line;
      std::cout << "... ";
    }
    try {
      vm.ExecuteString(buff.str());
    } catch (const std::exception &e) {
      std::cerr << e.what() << '\n';
    }
  }
}

int main(int argc, char *argv[]) {
  detail::GenericVM vm;
  LauncherContext ctx = {
      .plugin_dir = std::filesystem::current_path(),
      .root_vm = vm.GetSQVM(),
  };

  plugins::load_plugins(&ctx);
  plugins::on_squirrel_vm_init(&ctx);

  try {
    Interactive(vm.GetSQVM());
  } catch (const std::exception &e) {
    std::cerr << e.what() << '\n';
    return 1;
  }

  system("pause");
  return 0;
}
