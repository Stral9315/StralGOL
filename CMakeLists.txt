# Specify the minimum version for CMake

cmake_minimum_required(VERSION 3.6)
project(StralGOL)

set (StralGOL_VERSION_MAJOR 0)
set (StralGOL_VERSION_MINOR 1)

configure_file (
  "${PROJECT_SOURCE_DIR}/include/stralGOL.h.in"
  "${PROJECT_SOURCE_DIR}/include/stralGOL.h"
  )

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

include_directories("${PROJECT_SOURCE_DIR}/include/")
if(WIN32)
	include_directories("${PROJECT_SOURCE_DIR}/include/pdcurses/")
endif()
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT StralGOL)

if(MSVC)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++latest")
endif()

add_executable(StralGOL ${PROJECT_SOURCE_DIR}/entry.cpp)
if(WIN32)
	find_library(PDCURSES_LIB pdcurses lib)
elseif(UNIX)
	find_package(Curses)
	if(CURSES_FOUND)
		target_link_libraries(StralGOL ${CURSES_LIBRARIES})
	endif()
endif()
target_link_libraries(StralGOL ${PDCURSES_LIB})
MESSAGE( STATUS "CMAKE_CURRENT_BINARY_DIR: " ${CMAKE_CURRENT_BINARY_DIR} )