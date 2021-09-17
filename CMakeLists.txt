# CMakeLists for Phylloxera
# Author: M. Guigue
# Date: Jan 15, 2018

# Minimum cmake verison 3.12 required by Scarab
cmake_minimum_required (VERSION 3.12)

#########
# setup #
#########

cmake_policy( SET CMP0048 NEW ) # version in project()
project( Phylloxera VERSION 1.3.0 )

list( APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/Scarab/cmake)
include( PackageBuilder )

########################
# options #
########################

option( Phylloxera_ADD_PHYLLOXERA_PY "Add PhylloxeraPy file in the build" TRUE )
option( Phylloxera_ENABLE_EXECUTABLES "Build executables" TRUE )

option (FFTW_NTHREADS 1 "Number of threads to use for FFTW processes")

if( PBUILDER_STANDALONE )
    set( Scarab_BUILD_CLI OFF )
    set( Scarab_BUILD_CODEC_JSON OFF )
    set( Scarab_BUILD_CODEC_YAML OFF )
    set( Scarab_BUILD_AUTHENTICATION OFF )
    set( Scarab_BUILD_PARAM OFF )
    set( Scarab_ENABLE_EXECUTABLES OFF )
endif()

########################
# dependencies #
########################

set( PUBLIC_EXT_LIBS )

######
# ROOT
######

set( root_components Core Hist RooStats RooFit RooFitCore )
find_package (ROOT 6.20 REQUIRED CONFIG COMPONENTS ${root_components} )
foreach( component ${root_components} )
    list( APPEND PUBLIC_EXT_LIBS ROOT::${component} )
endforeach()
message( STATUS "ROOT libraries: ${root_components}" )

######
# FFTW
######

find_package(FFTW REQUIRED)
if( NOT TARGET FFTW::FFTW3 )
    add_library( FFTW::FFTW3 UNKNOWN IMPORTED GLOBAL )
    target_link_libraries( FFTW::FFTW3 INTERFACE ${FFTW_LIBRARIES} )
    target_include_directories( FFTW::FFTW3 INTERFACE ${FFTW_INCLUDE_DIR} )
    set_property( TARGET FFTW::FFTW3 PROPERTY IMPORTED_LOCATION ${FFTW_LIBRARIES} )
endif()
message (STATUS "FFTW_LIBRARIES is ${FFTW_LIBRARIES}")
list( APPEND PUBLIC_EXT_LIBS FFTW::FFTW3 )

add_definitions (-DFFTW_NTHREADS=${FFTW_NTHREADS})
message (STATUS "FFTW configured to use up to ${FFTW_NTHREADS} threads.")
if( FFTW_NTHREADS GREATER 1 )
    if (NOT FFTW_THREADS_FOUND)
        message(FATAL "FFTW_THREADS not found")
    endif (NOT FFTW_THREADS_FOUND)
    if( NOT TARGET FFTW::FFTW3_THREADS )
        add_library( FFTW::FFTW3_THREADS UNKNOWN IMPORTED GLOBAL )
        target_link_libraries( FFTW::FFTW3_THREADS INTERFACE ${FFTW_THREADS_LIBRARIES} )
        target_include_directories( FFTW::FFTW3_THREADS INTERFACE ${FFTW_INCLUDE_DIR} )
        set_property( TARGET FFTW::FFTW3_THREADS PROPERTY IMPORTED_LOCATION ${FFTW_THREADS_LIBRARIES} )
    endif()
endif()

#######################
# Prepare for build 
#######################

pbuilder_prepare_project()

################
# Submodules
################

pbuilder_add_submodule( Scarab Scarab )

#############
# Sources
#############

add_subdirectory (src)

#######################
# installation config #
#######################

configure_file( this_phylloxera.sh.in this_phylloxera.sh )
pbuilder_install_files( ${BIN_INSTALL_DIR} ${CMAKE_CURRENT_BINARY_DIR}/this_phylloxera.sh )

##################
# Package Config #
##################

configure_file( ${PROJECT_SOURCE_DIR}/PhylloxeraConfig.cmake.in ${CMAKE_CURRENT_BINARY_DIR}/PhylloxeraConfig.cmake @ONLY )

pbuilder_do_package_config()
