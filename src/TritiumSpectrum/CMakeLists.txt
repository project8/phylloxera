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

    set( lib_target Phylloxera${Phylloxera_PARENT_LIB_NAME_SUFFIX} )

MESSAGE( status ${lib_target})