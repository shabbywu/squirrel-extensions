#pragma once
#include "json_dumps.hpp"
#include "json_loads.hpp"
#include "vm.hpp"

namespace sqext_json {
void static sqext_register_jsonlib_impl(sqbind17::detail::VM &v) {
  auto roottable = sqbind17::detail::Table(_table(vm->roottable()), *vm);

  auto jsonlib_table = sqbind17::detail::Table(*vm);
  jsonlib_table.bindFunc(std::string("dumps"),
                         [](SQObjectPtr obj) { return json_dumps(obj); });
  jsonlib_table.bindFunc(
      std::string("loads"),
      static_cast<SQObjectPtr (*)(SQObjectPtr)>(&json_loads));
  roottable.set(std::string("jsonlib"), jsonlib_table);
}
} // namespace sqext_json
