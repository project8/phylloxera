#################
# TritiumPdf #
#################

set( headers
    RealTritiumSpectrum.hh
    SimpleTritiumSpectrum.hh
)

set( sources
    RealTritiumSpectrum.cxx    
    SimpleTritiumSpectrum.cxx    
)


###########
# Library #
###########

pbuilder_library( TritiumPdf  sources "")
target_link_libraries (TritiumPdf ${ROOT_LIBRARIES})
pbuilder_install_libraries(TritiumPdf)
pbuilder_install_headers( ${headers} )

