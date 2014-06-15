# - Try to find Particle Universe
#  	Once done this will define
#
#	On Windows, this script will look for Particle Universe using the environment variable PUDIR
#	The variable should point to the install directory
#  
#	PARTICLE_UNIVERSE_FOUND - System has ParticleUniverse
#	PARTICLE_UNIVERSE_INCLUDE_DIRS - The ParticleUniverse include directories
#	PARTICLE_UNIVERSE_LIBRARIES - The libraries needed to use Particle Universe
#	PARTICLE_UNIVERSE_LIBRARIES_REL - The libraries needed to use Particle Universe
#	PARTICLE_UNIVERSE_LIBRARIES_DEBUG (only in Debug build) - The libraries needed to use Particle Universe
#	PARTICLE_UNIVERSE_DEFINITIONS - Compiler switches required for using Particle Universe

include(FindPkgMacros)
include(PreprocessorUtils)
findpkg_begin(ParticleUniverse)

# Get hints about paths with pkg-config
# TODO: Create and install an actual pkgconfig file through PU's buildsystem
find_package(PkgConfig)
pkg_search_module(PC_PARTICLE_UNIVERSE OGRE-ParticleUniverse ParticleUniverse)

STRING(REGEX REPLACE "\\\\" "/" PU_INSTALL_DIR $ENV{PUDIR})

find_path(PARTICLE_UNIVERSE_INCLUDE_DIR ParticleUniversePlugin.h
          HINTS ${PC_PARTICLE_UNIVERSE_INCLUDE_DIRS}
                ${PU_INSTALL_DIR}/include
                ${OGRE_INCLUDE_DIR}/Plugins/ParticleUniverse )

# Only search for the debug library if in a debug build
string(TOLOWER "${CMAKE_BUILD_TYPE}" CMAKE_BUILD_TYPE_LC)

if (CMAKE_BUILD_TYPE_LC STREQUAL "debug")
  find_library(PARTICLE_UNIVERSE_LIBRARY_DEBUG NAMES Plugin_ParticleUniverse_d Plugin_ParticleUniverse_d.so libPlugin_ParticleUniverse_d
               HINTS ${PC_PARTICLE_UNIVERSE_LIBDIR} ${PC_PARTICLE_UNIVERSE_LIBRARY_DIRS}
                     ${PU_INSTALL_DIR}/lib/Debug
                     ${OGRE_PLUGIN_DIR_DBG} )

  set(PARTICLE_UNIVERSE_LIBRARIES_DEBUG ${PARTICLE_UNIVERSE_LIBRARY_DEBUG} )
  set(PARTICLE_UNIVERSE_LIBRARIES ${PARTICLE_UNIVERSE_LIBRARY_DEBUG} )
else (CMAKE_BUILD_TYPE_LC STREQUAL "debug")
  find_library(PARTICLE_UNIVERSE_LIBRARY_REL NAMES Plugin_ParticleUniverse Plugin_ParticleUniverse.so libPlugin_ParticleUniverse
               HINTS ${PC_PARTICLE_UNIVERSE_LIBDIR} ${PC_PARTICLE_UNIVERSE_LIBRARY_DIRS}
                     ${PU_INSTALL_DIR}/lib/Release ${PU_INSTALL_DIR}/lib/RelWithDebInfo ${PU_INSTALL_DIR}/lib/MinSizeRel
                     ${OGRE_PLUGIN_DIR_REL} )

  set(PARTICLE_UNIVERSE_LIBRARIES_REL ${PARTICLE_UNIVERSE_LIBRARY_REL}  )
  set(PARTICLE_UNIVERSE_LIBRARIES ${PARTICLE_UNIVERSE_LIBRARY_REL} )
endif (CMAKE_BUILD_TYPE_LC STREQUAL "debug")

set(PARTICLE_UNIVERSE_INCLUDE_DIRS ${PARTICLE_UNIVERSE_INCLUDE_DIR} )

include(FindPackageHandleStandardArgs)
# handle the QUIETLY and REQUIRED arguments and set PARTICLE_UNIVERSE_FOUND to TRUE
# if all listed variables are TRUE
if (CMAKE_BUILD_TYPE_LC STREQUAL "debug")
  find_package_handle_standard_args(ParticleUniverse  DEFAULT_MSG
                                    PARTICLE_UNIVERSE_LIBRARY_DEBUG PARTICLE_UNIVERSE_INCLUDE_DIR )
  mark_as_advanced(PARTICLE_UNIVERSE_INCLUDE_DIR PARTICLE_UNIVERSE_LIBRARY_DEBUG )
else (CMAKE_BUILD_TYPE_LC STREQUAL "debug")
  find_package_handle_standard_args(ParticleUniverse  DEFAULT_MSG
                                    PARTICLE_UNIVERSE_LIBRARY_REL PARTICLE_UNIVERSE_INCLUDE_DIR )
  mark_as_advanced(PARTICLE_UNIVERSE_INCLUDE_DIR PARTICLE_UNIVERSE_LIBRARY_REL )
endif (CMAKE_BUILD_TYPE_LC STREQUAL "debug")
