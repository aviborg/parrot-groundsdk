cmake_minimum_required(VERSION 3.15)

macro(set_up_rpath)
  if(WIN32)
    message(STATUS "Can't set rpath for windows")
  elseif(CMAKE_INSTALL_PREFIX STREQUAL "/usr/local")
    message(STATUS "Not setting rpath since no special install")
  else()
    message("Setting up rpath for ${PROJECT_NAME}")
    if (APPLE)
      set(rbase "@loader_path")
    else ()
      set(rbase "\\\$ORIGIN/../lib")
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

    # TODO only if install?
    set_target_properties(${PROJECT_NAME}
                          PROPERTIES
                          INSTALL_RPATH "\\\$ORIGIN/../lib"
                          )

    # add the automatically determined parts of the RPATH
    # which point to directories outside the build tree to the install RPATH
    set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
  endif()

endmacro()
