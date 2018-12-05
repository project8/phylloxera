# CMakeLists for Phylloxera
# Author: M. Guigue
# Date: Jan 15, 2018

# Minimum cmake verison 3.1 required for the variable CMAKE_CXX_STANDARD
cmake_minimum_required (VERSION 3.1)

#########
# setup #
#########

cmake_policy( SET CMP0048 NEW ) # version in project()
project( Phylloxera VERSION 1.2.3 ) 

list( APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/Scarab/cmake)
include( PackageBuilder )

pbuilder_prepare_project()

########################
# options #
########################

option( Phylloxera_ADD_PHYLLOXERA_PY "Add PhylloxeraPy file in the build" TRUE )
option( Phylloxera_ENABLE_EXECUTABLES "Build executables" TRUE )

########################
# dependencies #
########################

########
# Scarab
########

set( Scarab_BUILD_CODEC_JSON OFF )
set( Scarab_BUILD_CODEC_YAML OFF )
set( Scarab_BUILD_AUTHENTICATION OFF )
set( Scarab_BUILD_PARAM OFF )
set( Scarab_ENABLE_EXECUTABLES OFF )

pbuilder_add_submodule( Scarab Scarab/library )

######
# ROOT
######

find_package (ROOT 6.00)
if (ROOT_FOUND)
    pbuilder_add_ext_libraries (${ROOT_LIBRARIES})
    #message(STATUS "${ROOT_LIBRARIES}")
else (ROOT_FOUND)
    message(FATAL "Unable to find ROOT")
endif (ROOT_FOUND)
include_directories (${ROOT_INCLUDE_DIR})

######
# FFTW
######

find_package(FFTW REQUIRED)
if (NOT FFTW_THREADS_FOUND)
  message(FATAL "FFTW_THREADS not found")
endif (NOT FFTW_THREADS_FOUND)
    pbuilder_add_ext_libraries (${FFTW_LIBRARIES})
    set (FFTW_NTHREADS 1 CACHE STRING "Number of threads to use for FFTW processes")
    add_definitions (-DFFTW_NTHREADS=${FFTW_NTHREADS})
    message (STATUS "FFTW configured to use up to ${FFTW_NTHREADS} threads.")
message (STATUS "FFTW_LIBRARIES is ${FFTW_LIBRARIES}")
include_directories (${FFTW_INCLUDE_DIR})
message (STATUS "FFTW_LIBRARIES is ${FFTW_LIBRARIES}")

#############
# Sources
#############

add_subdirectory (src)

#######################
# installation config #
#######################

configure_file( this_phylloxera.sh.in this_phylloxera.sh )
pbuilder_install_files( ${BIN_INSTALL_DIR} ${CMAKE_CURRENT_BINARY_DIR}/this_phylloxera.sh )

pbuilder_variables_for_parent()

