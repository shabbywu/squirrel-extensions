<div align="center">
  ☢️🤖
</div>
<h1 align="center">
  squirrel-extensions
</h1>

<p align="center">
   A tutorial/example showing how to extend squirrel lang via windows DLL.
</p>

<br />

# Example
## jsonlib
`jsonlib` is an `nlohmann::json` to squirrel bridge, it allows you to convert `nlohmann::json` to `SQObjectPtr/HSQOBJECT` and the other way around. Simply add the `jsonlib.dll`, and the automatic conversion will be enabled.

```squirrel
local dumped = jsonlib.dumps({
    a = 1
})
// typeof dumped == string

local loaded = jsonlib.loads(dumped)
// typeof loaded == table
```

# sq-repl - Playground
`sq-repl` is an extendable squirrel interpreter, aka `repl`.
> `jsonlib` is one of the loadable plugins.

## Protocol
The `sq-repl` will load all *.dll plugins from the current directory. If a plugin provides the function `void on_squirrel_vm_init(HSQUIRRELVM)`, it will be triggerred after the Squirrel VM initialization.
