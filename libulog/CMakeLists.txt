cmake_minimum_required(VERSION 3.15)
project(libulog VERSION 1.0)

add_library(ulog INTERFACE)
target_include_directories(ulog INTERFACE
                            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
                            $<INSTALL_INTERFACE:include>
)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    "${PROJECT_BINARY_DIR}/ulogConfigVersion.cmake"
    VERSION ${VERSION}
    COMPATIBILITY AnyNewerVersion
)

install(TARGETS ulog
    EXPORT ulogTargets
    LIBRARY DESTINATION lib COMPONENT Runtime
    ARCHIVE DESTINATION lib COMPONENT Development
    RUNTIME DESTINATION bin COMPONENT Runtime
    PUBLIC_HEADER DESTINATION include COMPONENT Development
    BUNDLE DESTINATION bin COMPONENT Runtime
)

include(CMakePackageConfigHelpers)
configure_package_config_file(
    "${PROJECT_SOURCE_DIR}/cmake/ulogConfig.cmake.in"
    "${PROJECT_BINARY_DIR}/ulogConfig.cmake"
    INSTALL_DESTINATION lib/cmake/ulog
)

install(EXPORT ulogTargets DESTINATION lib/cmake/ulog)
install(FILES "${PROJECT_BINARY_DIR}/ulogConfigVersion.cmake"
              "${PROJECT_BINARY_DIR}/ulogConfig.cmake"
        DESTINATION lib/cmake/ulog)
install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/ DESTINATION include)