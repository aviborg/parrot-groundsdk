# parrot-groundsdk

This is an adaptation of the parrot groundsdk to run on Windows. But as CMake is used it should compile on Linux too, not tested though.
This has been done:
- Some code fixes
- Most of the work has been to translate the make files to Cmake build files

Running CMake on the top level creates an ```parrot-client.exe``` for test purposes

Don't forget to run
```powershell
git submodule update --init --recursive
```
after cloning this repository!

Mingw-x64 gcc must be installed and used. Below is a good guide to follow. Consider installing VSCode too.

https://code.visualstudio.com/docs/cpp/config-mingw

You also need to add the MingW-CMake:
```bash
pacman -S mingw-w64-x86_64-cmake
```

Then you need vcpkg and some packages. How to install vcpkg is described [here](https://github.com/Microsoft/vcpkg/) but it is just a few powershell commands.

Microsoft recommend vcpkg to be installed somewhere like C:\src\vcpkg or C:\dev\vcpkg, since otherwise you may run into path issues for some port build systems.
```powershell
mkdir [path to vcpkg]
cd [path to vcpkg]
git clone https://github.com/microsoft/vcpkg
.\vcpkg\bootstrap-vcpkg.bat
.\vcpkg.exe install json-c eigen3 --triplet=x64-windows
.\vcpkg.exe install ffmpeg[avcodec,avdevice,avfilter,avformat,swresample,swscale]:x64-windows
```
Take some coffee as the above will take a while.
```powershell
.\vcpkg.exe install protobuf-c[tools]
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
.\vcpkg.exe install protobuf-c[tools]
```
Then run
```powershell
.\vcpkg.exe integrate install
```

if you had the above issue with protobuf-c, add ```[path to vcpkg]\installed\x64-windows\tools\protobuf-c``` to PATH environment variable. Maybe this is necessary even if the above is fixed?

If you use VSCode, add this to your settings (press ```Ctrl+,```) to open settings in UI mode. Switch to json text mode by clickin the first of the 3 icons on the top right-hand side (the one looking like a file).
Add this to the ```settings.json```:
```json
{
    "cmake.configureSettings": {
            "CMAKE_TOOLCHAIN_FILE": "[path to vcpkg]/scripts/buildsystems/vcpkg.cmake"
        }
}
```
Then let VSCode do all the magic for you!

To build with CMake manually do this in the workdirectory:
```powershell
mkdir build
cd build
cmake "-DCMAKE_TOOLCHAIN_FILE=[path to vcpkg]/scripts/buildsystems/vcpkg.cmake" ..
cmake --build .
```

