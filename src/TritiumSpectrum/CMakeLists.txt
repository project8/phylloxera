###################
# TritiumSpectrum #
###################

set( headers
)

set( sources
    TritiumSpectrum.cpp
)

###########
# Library #
###########

pbuilder_library( TritiumSpectrum sources headers "")
target_link_libraries (TritiumSpectrum ${ROOT_LIBRARIES})
pbuilder_install_libraries(TritiumSpectrum)
pbuilder_install_headers( ${headers} )

