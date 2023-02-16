# parrot-client

https://code.visualstudio.com/docs/cpp/config-mingw

https://stackoverflow.com/questions/70197831/unable-to-determine-what-cmake-generator-to-use-vs-code-windows-10


https://github.com/Microsoft/vcpkg/
.\vcpkg.EXE install json-c protobuf-c[tools] eigen3 libyuv --triplet=x64-windows
.\vcpkg.exe install ffmpeg[avcodec,avdevice,avfilter,avformat,swresample,swscale]:x64-windows

If it fails (see here: https://github.com/microsoft/vcpkg/issues/29677)
do this patch in your vcpkg directory
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

https://github.com/microsoft/vcpkg/issues/28446

 .\vcpkg.exe integrate install

https://www.40tude.fr/how-to-use-vcpkg-with-vscode-and-cmake/

add C:\vcpkg\installed\x64-windows\tools\protobuf-c to PATH