set(PROJECT_NAME "ParticleUniverse")

OPTION(PU_BUILD_DEMOS "If the demo application should be build and installed." ON)
OPTION(PU_BUILD_ATLAS_IMAGE_TOOL "If the AtlasImageTool should be build and installed." ON)

project(${PROJECT_NAME} CXX C)
cmake_minimum_required(VERSION 2.8)

# Avoid source tree pollution
if(CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR)
	message(FATAL_ERROR "In-source builds are not permitted. Make a separate folder for building:\nmkdir build; cd build; cmake ..\nBefore that, remove the files already created:\nrm -rf CMakeCache.txt CMakeFiles")
endif(CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR)

SET(CMAKE_DEBUG_POSTFIX "_d")

# Include path for additional CMake library finding scripts
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

# We want the binaries to be easily accessible
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

# Add the libraries
# OGRE
find_package(OGRE REQUIRED)
link_directories(${OGRE_LIBRARY_DIRS})
include_directories(${OGRE_INCLUDE_DIRS})
list(APPEND LIBS ${OGRE_LIBRARIES})

add_definitions(-DOGRE_PLUGIN_DIR_REL="${OGRE_PLUGIN_DIR_REL}")
add_definitions(-DOGRE_PLUGIN_DIR_DBG="${OGRE_PLUGIN_DIR_DBG}")

#OGRE-Overlay
if (OGRE_VERSION_MAJOR GREATER 1 OR OGRE_VERSION_MINOR GREATER 8)
	include_directories(${OGRE_Overlay_INCLUDE_DIRS})
	list(APPEND LIBS ${OGRE_Overlay_LIBRARIES})
endif()

add_subdirectory(Plugins/ParticleUniverse)

if(PU_BUILD_DEMOS)
	add_subdirectory(Samples/ParticleUniverseDemo)
ENDIF()

if(PU_BUILD_ATLAS_IMAGE_TOOL)
	add_subdirectory(Tools/AtlasImageTool)
ENDIF()

IF(WIN32)
	FOREACH(type ${CMAKE_CONFIGURATION_TYPES})
		install(DIRECTORY "${CMAKE_BINARY_DIR}/${type}"
			DESTINATION "${CMAKE_INSTALL_PREFIX}/bin"
			FILES_MATCHING PATTERN "*.dll")
		
		install(DIRECTORY "${CMAKE_BINARY_DIR}/${type}"
			DESTINATION "${CMAKE_INSTALL_PREFIX}/lib"
			FILES_MATCHING PATTERN "*.lib"
			PATTERN "particleuniversedemo.lib" EXCLUDE
			PATTERN "atlasimagetool.lib" EXCLUDE)
	ENDFOREACH(type)
	
	install(DIRECTORY "Plugins/ParticleUniverse/include"
		DESTINATION "${CMAKE_INSTALL_PREFIX}"
		FILES_MATCHING PATTERN "*.h")
ENDIF(WIN32)

