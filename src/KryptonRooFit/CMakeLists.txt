#################
# TritiumRooFit #
#################

set( headers
    RooKryptonLine.hh
)

set( sources
    RooKryptonLine.cxx    
)


###########
# Library #
###########

pbuilder_library( RooKryptonLine  sources "")
target_link_libraries (RooKryptonLine ${ROOT_LIBRARIES})
pbuilder_install_libraries(RooKryptonLine)
pbuilder_install_headers( ${headers} )

