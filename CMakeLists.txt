# Specify the minimum version for CMake

cmake_minimum_required(VERSION 3.0.2)
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

set(IncludeDir "${PROJECT_SOURCE_DIR}/include")
set(SourceDir "${PROJECT_SOURCE_DIR}")
include_directories(${IncludeDir})

if(WIN32)
	include_directories("${IncludeDir}/pdcurses/") #use pdcurses
endif()


if(${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++latest")
	if(${CMAKE_VERSION} VERSION_GREATER "3.6.3")
		set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT StralGOL)
		message("cmake version > 3.6.3, VS_STARTUP_PROJECT set to StralGOL")
	endif()
elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL GNU)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif()

set(StralGOLFiles
	"${SourceDir}/entry.cpp"
	"${SourceDir}/game.cpp"
	)


set(StralGOLHeaders
	"${IncludeDir}/common.h"
	"${IncludeDir}/StralGOL.h"
	"${IncludeDir}/game.h"
	)


source_group("Headers" FILES ${StralGOLHeaders})

add_executable(StralGOL ${StralGOLFiles} ${StralGOLHeaders})

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
