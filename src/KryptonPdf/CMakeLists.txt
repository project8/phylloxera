#################
# TritiumRooFit #
#################

set( headers
    KryptonLine.hh
    KrTest.hh
)

set( sources
    KryptonLine.cxx    
    KrTest.cxx    
)

###########
# Library #
###########

pbuilder_library( KryptonPdf  sources "")
target_link_libraries (KryptonPdf ${ROOT_LIBRARIES})
pbuilder_install_libraries(KryptonPdf)
pbuilder_install_headers( ${headers} )

