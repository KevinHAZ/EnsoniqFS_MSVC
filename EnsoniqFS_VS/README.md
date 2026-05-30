# EnsoniqFS – Visual Studio Solution

This folder contains a Visual Studio 2019/2022 solution for building the
[EnsoniqFS](https://github.com/thoralt/ensoniqfs) Total Commander filesystem
plugin from source.

---

## Prerequisites

| Requirement | Notes |
|---|---|
| Visual Studio 2019 or 2022 | Community edition is fine |
| "Desktop development with C++" workload | Installed via VS Installer |
| Git | To clone the source repo |

---

## Directory layout

After following the setup steps below the layout should look like this:

```
<parent folder>/
├── EnsoniqFS_VS/           ← this folder (the VS solution)
│   ├── EnsoniqFS.sln
│   └── EnsoniqFS/
│       ├── EnsoniqFS.vcxproj
│       └── EnsoniqFS.def
└── ensoniqfs/              ← cloned source repo (same level)
    ├── EnsoniqFS.c
    ├── EnsoniqFS.h
    ├── bank.c
    ├── cache.c
    ├── choosediskdlg.c
    ├── disk.c
    ├── ini.c
    ├── log.c
    ├── optionsdlg.c
    ├── progressdlg.c
    ├── progressdlg.rc
    ├── fsplugin.h
    ├── OmniFlop.h
    └── ... (all other repo files)
```

The `.vcxproj` uses the MSBuild property `$(SourceRoot)` which resolves to
`..\..\ensoniqfs\` relative to the project file, so both folders **must be
siblings** (same parent directory).

---

## Setup steps

```bat
REM 1. Clone the source repo next to the solution folder
git clone https://github.com/thoralt/ensoniqfs.git

REM 2. Open the solution
start EnsoniqFS_VS\EnsoniqFS.sln
```

Then in Visual Studio:

1. Select your target platform — **Win32** (32-bit) or **x64** (64-bit).
2. Select **Release** or **Debug**.
3. **Build → Build Solution** (Ctrl+Shift+B).

The output plugin file will be at:

```
bin\<Platform>\<Configuration>\EnsoniqFS.wfx
```

*(The project outputs `.wfx` directly — no renaming needed.)*

---

## Installing into Total Commander

1. Copy `EnsoniqFS.wfx` and `EnsoniqFS.ico` (from the repo root) to a
   folder of your choice, e.g. `C:\TotalCMD\plugins\EnsoniqFS\`.
2. In Total Commander: **Configuration → Options → File system plugins**.
3. Click **Add** and browse to `EnsoniqFS.wfx`.
4. Restart Total Commander.

---

## Platforms

| Platform | Status |
|---|---|
| Win32 (x86) | Known-good; this is the original target |
| x64 | Work in progress (see repo README) |

---

## Compiler warnings suppressed

The original Dev-C++ code triggers a handful of benign MSVC warnings.
These are suppressed project-wide via `DisableSpecificWarnings`:

| Code | Reason |
|---|---|
| C4996 | `strcpy`, `sprintf` etc. — use `_s` variants to resolve |
| C4018 | Signed/unsigned comparison |
| C4244 | Implicit integer narrowing |
| C4267 | `size_t` to smaller type |

These can be addressed incrementally as part of the 64-bit porting work.

---

## License

The source code is published under **GPL v2** (see `LICENSE` in the repo).
The Visual Studio project files in this folder are provided as-is with no
additional restrictions.
