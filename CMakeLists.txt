cmake_minimum_required(VERSION 3.15)
project(parrot-client VERSION 1.0)
add_executable(parrot-client src/parrot-client.cpp)

# specify the C++ standard
add_library(parrot-client_compiler_flags INTERFACE)
target_compile_features(parrot-client_compiler_flags INTERFACE cxx_std_11)

option(BUILD_SHARED_LIBS "Build using shared libraries" ON)

# control where the static and shared libraries are built so that on windows
# we don't need to tinker with the path to run the executable
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")

add_subdirectory(libulog)
add_subdirectory(libpomp)
add_subdirectory(libfutils)
add_subdirectory(libh264)
add_subdirectory(libh265)
add_subdirectory(libmedia-buffers)
add_subdirectory(libvideo-defs)
add_subdirectory(libvideo-metadata)

target_link_libraries(parrot-client 
                        PUBLIC 
                        ulog
                        pomp
                        futils 
                        parrot-client_compiler_flags
)
