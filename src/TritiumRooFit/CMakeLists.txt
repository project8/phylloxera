#################
# TritiumRooFit #
#################

set( headers
    RooRealTritiumSpectrum.hh
    RooSimpleTritiumSpectrum.hh
    #RooSmearedTritiumSpectrum.hh
)

set( sources
    RooRealTritiumSpectrum.cxx    
    RooSimpleTritiumSpectrum.cxx    
    #RooSmearedTritiumSpectrum.cxx
)


###########
# Library #
###########

#add_library (TritiumRooFit ${sources} )

pbuilder_library( TritiumRooFit  sources "")
target_link_libraries (TritiumRooFit ${ROOT_LIBRARIES})
pbuilder_install_libraries(TritiumRooFit)
pbuilder_install_headers( ${headers} )

