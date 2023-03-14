cmake_minimum_required(VERSION 3.15)

macro(INSTALL_ADD_IMPORTED_DLLS target_list target_dep_lib dest_path)

	foreach(this_trg ${target_list})
		install(CODE "set(MY_DEPENDENCY_PATHS \"${target_dep_lib}\")")
		install(CODE "set(this_trg \"\$<TARGET_FILE:${this_trg}>\")")
	
		install(CODE [[
			file(GET_RUNTIME_DEPENDENCIES
				LIBRARIES ${this_trg}
				RESOLVED_DEPENDENCIES_VAR _r_deps
				UNRESOLVED_DEPENDENCIES_VAR _u_deps
				DIRECTORIES ${MY_DEPENDENCY_PATHS}
			)
			foreach(_file ${_r_deps})
				file(INSTALL
				DESTINATION ${CMAKE_INSTALL_PREFIX}/bin
				TYPE SHARED_LIBRARY
				FOLLOW_SYMLINK_CHAIN
				FILES "${_file}"
				)
			endforeach()
		]])


#     get_target_property(one_trg_type ${one_trg} TYPE)
#      message(${one_trg_type})

#     if (NOT one_trg_type STREQUAL "INTERFACE_LIBRARY")
#        get_target_property(one_trg_dll_location ${one_trg} IMPORTED_LOCATION_RELEASE)
#        if( one_trg_dll_location MATCHES ".dll$")
# 	       message(${one_trg_dll_location})
#           install(FILES ${one_trg_dll_location} DESTINATION ${destination_folder} COMPONENT ${target_component})
#        endif()
#        get_target_property(one_trg_dll_location ${one_trg} IMPORTED_LOCATION_DEBUG)
#        message(${one_trg_dll_location})
#        if( one_trg_dll_location MATCHES ".dll$")
#           install(FILES ${one_trg_dll_location} DESTINATION ${destination_folder} CONFIGURATIONS Debug COMPONENT ${target_component})
# 	       endif()
# 	    endif()

 	endforeach()
endmacro()

macro(set_up_rpath)
	if(WIN32)
	# 	#message(STATUS "Can't set rpath for windows")
	elseif(CMAKE_INSTALL_PREFIX STREQUAL "/usr/local")
	 	message(STATUS "Not setting rpath since no special install")
	else()
	# 	message("Setting up rpath for ${PROJECT_NAME}")
		if (APPLE)
			set(rbase "@loader_path")
		else ()
			set(rbase "\\\$ORIGIN;\\\$ORIGIN/../lib")
		endif ()

		# set(CMAKE_SKIP_BUILD_RPATH FALSE)

	# 	# when building, don't use the install RPATH already
	# 	# (but later on when installing)
		# set(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE)

	# 	file(RELATIVE_PATH lib_dir
	# 		"${CMAKE_INSTALL_PREFIX}/bin"
	# 		"${CMAKE_INSTALL_PREFIX}/lib")

		set(CMAKE_INSTALL_RPATH "${rbase}" CACHE STRING "Install RPATH")

	# 	message("install path is ${CMAKE_INSTALL_RPATH}")

	# 	# TODO only if install?
		set_target_properties(${PROJECT_NAME}
			PROPERTIES
			INSTALL_RPATH "${rbase}"
		)

	# 	# add the automatically determined parts of the RPATH
	# 	# which point to directories outside the build tree to the install RPATH
	# 	set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
	endif()

endmacro()
