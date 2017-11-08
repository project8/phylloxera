#################
# TritiumRooFit #
#################

set( headers
    RooKryptonLine.hh
    RooKrTest.hh
)

set( sources
    RooKryptonLine.cxx    
    RooKrTest.cxx    
)


###########
# Library #
###########

pbuilder_library( KryptonRooFit  sources "")
target_link_libraries (KryptonRooFit ${ROOT_LIBRARIES})
pbuilder_install_libraries(KryptonRooFit)
pbuilder_install_headers( ${headers} )

