cmake_minimum_required(VERSION 3.15)
project(parrot_client VERSION 1.0)

add_executable(${PROJECT_NAME} src/parrot-client.cpp)
target_compile_features(${PROJECT_NAME} INTERFACE cxx_std_11)

# specify the C++ standard

option(BUILD_SHARED_LIBS "Build using shared libraries" ON)


if (APPLE)
  set(rbase "@loader_path")
else ()
  set(rbase "\$ORIGIN")
endif ()

set(CMAKE_SKIP_BUILD_RPATH FALSE)

# when building, don't use the install RPATH already
# (but later on when installing)
set(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE)

file(RELATIVE_PATH lib_dir
    "${CMAKE_INSTALL_PREFIX}/bin"
    "${CMAKE_INSTALL_PREFIX}/lib")

set(CMAKE_INSTALL_RPATH "${rbase};${rbase}/${lib_dir}"
    CACHE STRING "Install RPATH")

message("install path is ${CMAKE_INSTALL_RPATH}")
 
# add the automatically determined parts of the RPATH
# which point to directories outside the build tree to the install RPATH
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)



# control where the static and shared libraries are built so that on windows
# we don't need to tinker with the path to run the executable
# set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")
# set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")
# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")


list(APPEND dependencies
    libfutils
    libh264
    libh265
    libmedia-buffers
    libmp4
    libpomp
    librtp
    librtsp
    libsdp
    libtransport-packet
    libtransport-socket
    libvideo-decode
    libvideo-defs
    libvideo-encode
    libvideo-metadata
    libvideo-scale
    libvideo-streaming
    libyuv
    pdraw
    ulog
)


foreach(arg IN LISTS dependencies)
    message("Setting up directory -- " ${arg})
  add_subdirectory(${arg})
endforeach()

target_include_directories(${PROJECT_NAME} 
                          PUBLIC
                          $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/pdraw/libpdraw-vsink/include/> 
                          $<INSTALL_INTERFACE:include/> 
)

target_link_libraries(${PROJECT_NAME}
    ulog
    pomp
    futils
    pdraw-vsink
)

install(TARGETS ${PROJECT_NAME}
    EXPORT ${PROJECT_NAME}-targets
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
)
