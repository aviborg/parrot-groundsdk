cmake_minimum_required(VERSION 3.15)

macro(set_up_rpath)
    message("Setting up rpath for ${PROJECT_NAME}")
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

endmacro()
