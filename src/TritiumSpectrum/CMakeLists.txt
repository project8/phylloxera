###################
# TritiumSpectrum #
###################

set( headers
    TritiumSpectrum.hh
)

set( sources
    TritiumSpectrum.cpp
)

###########
# Library #
###########

pbuilder_library( TritiumSpectrum sources ToolBox)
pbuilder_install_headers( ${headers} )
