# VGFramework

## What is VGFramework? ⚙️

**VGFramework** is a framework for the [**Space Rangers HD**](https://store.steampowered.com/app/214730/Space_Rangers_HD_A_War_Apart/) game , which is designed to facilitate and extend the **modding** of the game, as well as **optimize** the game engine in parallel.

### Some new features in modding 🔨

1. Replace **.dat** to **.rml** **.rcss** **.json**
2. Replace **.scr** to **.lua**
3. Use **RML/RCSS** to create forms/interfaces
4. Use new **debug system**
5. Use new **modding functions**

Learn more at [**Vertix Games VGFramework**](https://vertix.games/vgframework)

## What is Injector?🧪

Injector is an exe file that allows you to inject **VGFramework.dll** into the **Rangers.exe** process so that the framework can run from the start of the game.

## How to build? 🧰

⚠️ **ATTENTION** ⚠️

Build works only with **MSVC**

**Install requirements**

1. Install [**vcpkg**](https://github.com/microsoft/vcpkg/releases/) 
2. Install packages 

``````bash
vcpkg install boost
vcpkg install lua
vcpkg install rmlui
``````

**Configure project**

``````bash
cmake -A Win32 -G "Visual Studio 17 2022" -B ./build -DCMAKE_TOOLCHAIN_FILE=VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake -DCMAKE_BUILD_TYPE=Release
``````

Change **Visual Studio 17 2022** to your Visual Studio version

Change **VCPKG_ROOT** to your vcpkg directory

**Build project**

``````bash
cmake --build ./build --config Release
``````

## Sponsoring 💎

1. **Monero** 46Vvmi4pnRggWJjFo3Do4jGAB8eSYvYQvGkEF2xtAqBE9n13GEEPiHn7rU2eSxuTA3HKKwoxhTT2QgGxEwwLhTL99pSbZ4B
2. **TRON** TB4iWbLynygTpCALUTHSk3bbPvjCymAwBh