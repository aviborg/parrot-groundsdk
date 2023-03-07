# parrot-groundsdk


This is an adaptation of the parrot groundsdk to run on Windows, but as CMake is used it, compiles on Linux too.
This has been done:
- Some code fixes
- Most of the work has been to translate the ```atom.mk``` files to ```CMakeLists.txt``` build files.

## To use

```powershell
git clone [path-to-this-repo]
git submodule update --init --recursive
git submodule foreach "git switch master"
```

## Windows

### MinGW toolchain
Mingw-x64 gcc must be installed and used, MSVC does not work! Below is a good guide to follow. Consider installing VSCode too.
https://code.visualstudio.com/docs/cpp/config-mingw
1. Get the latest version of Mingw-w64 via MSYS2, which provides up-to-date native builds of GCC, Mingw-w64, and other helpful C++ tools and libraries. You can download the latest installer from the MSYS2 page or use this [link to the installer](https://github.com/msys2/msys2-installer/releases).
1. Follow the Installation instructions on the [MSYS2 website](https://www.msys2.org/) to install Mingw-w64. Take care to run each required Start menu and pacman command.
1. Install the Mingw-w64 toolchain 
```pacman -S --needed base-devel mingw-w64-x86_64-toolchain``` Run the pacman command in a MSYS2 terminal. Accept the default to install all the members in the toolchain group.
1. Add the path to your Mingw-w64 bin folder to the Windows PATH environment variable. 
1. You also need to add the MingW-CMake
```pacman -S mingw-w64-x86_64-cmake```

### vcpkg
Then you need vcpkg and some packages. How to install vcpkg is described [here](https://github.com/Microsoft/vcpkg/) but it is just a few powershell commands.
https://learn.microsoft.com/en-us/vcpkg/users/platforms/mingw

Microsoft recommend vcpkg to be installed somewhere like C:\src\vcpkg or C:\dev\vcpkg, since otherwise you may run into path issues for some port build systems. Below the install is at ```C:\vcpkg```
```powershell
cd C:\
git clone https://github.com/microsoft/vcpkg
.\vcpkg\bootstrap-vcpkg.bat
$Env:VCPKG_DEFAULT_TRIPLET="x64-mingw-dynamic"
$Env:VCPKG_DEFAULT_HOST_TRIPLET="x64-mingw-dynamic"
.\vcpkg.exe install json-c eigen3 ffmpeg[avcodec,avdevice,avfilter,avformat,swresample,swscale,zlib] --triplet=x64-mingw-dynamic
```
Take some coffee as the above will take a while.
```powershell
.\vcpkg.exe install protobuf-c[tools] --triplet=x64-mingw-dynamic
```
If it fails (see here: https://github.com/microsoft/vcpkg/issues/29677)

Then do this patch in your vcpkg directory.
```git
diff --git a/ports/protobuf-c/portfile.cmake b/ports/protobuf-c/portfile.cmake
index 0a972cb27..4bcce7017 100644
--- a/ports/protobuf-c/portfile.cmake
+++ b/ports/protobuf-c/portfile.cmake
@@ -26,7 +26,7 @@ vcpkg_copy_pdbs()

 if("tools" IN_LIST FEATURES)
     vcpkg_copy_tools(
-        TOOL_NAMES protoc-gen-c protoc-c
+        TOOL_NAMES protoc-gen-c
         AUTO_CLEAN
     )
 endif()
```
and run again
```powershell
.\vcpkg.exe install protobuf-c[tools] --triplet=x64-mingw-dynamic
```
Then run
```powershell
.\vcpkg.exe integrate install
```

You need to add ```[path to vcpkg]\installed\x64-mingw-dynamic\tools\protobuf-c``` to the PATH environment variable in order for the protobuf generator to find protoc-gen-c executable.

## Linux

To run on Linux it is only a few shell commands:

```shell
sudo apt install -y cmake gcc g++ gdb curl pkg-config ninja-build nasm
cd ~
git clone https://github.com/microsoft/vcpkg
./vcpkg/bootstrap-vcpkg.sh
./vcpkg/vcpkg install json-c eigen3 protobuf-c[tools] ffmpeg[avcodec,avdevice,avfilter,avformat,swresample,swscale,zlib]

~/vcpkg integrate install

```
You need to add ```[path to vcpkg]/installed/x64-linux/tools/protobuf-c``` to the PATH 
## VS Code

If you use VSCode, add this to your settings (press ```Ctrl+,```) to open settings in UI mode. Switch to json text mode by clickin the first of the 3 icons on the top right-hand side (the one looking like a file).
Add this to the ```settings.json```:
```json
{
    "cmake.configureSettings": {
            "CMAKE_TOOLCHAIN_FILE": "[path to vcpkg]/scripts/buildsystems/vcpkg.cmake",
            "CMAKE_INSTALL_PREFIX": "${workspaceFolder}/install"
        }
}
```

## Build with CMake

To build with CMake manually do this in the workdirectory:
```powershell
mkdir build
mkdir install
cd build
cmake "-DCMAKE_TOOLCHAIN_FILE=[path to vcpkg]/scripts/buildsystems/vcpkg.cmake" "-DCMAKE_INSTALL_PREFIX=../install" ..
cmake --build .
cmake --build . --target install
```

## Test

You may test the application with the following file [https://drive.google.com/file/d/1FjdZM7qyQEJHX9SPQCBFUkr0ptrn5vO1/view?usp=sharing](https://drive.google.com/file/d/1FjdZM7qyQEJHX9SPQCBFUkr0ptrn5vO1/view?usp=sharing)

```powershell
./install/bin/parrot.exe P0260026.MP4
```
