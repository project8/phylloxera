###########
# ToolBox #
###########

set( sources
    Conversion.cpp
    Plots.cpp
    RooFitTools.cpp
    VectorTools.cpp
)

###########
# library #
###########

pbuilder_library( ToolBox sources "" )
target_link_libraries (ToolBox ${ROOT_LIBRARIES})
pbuilder_install_libraries(ToolBox)
pbuilder_install_headers( ${headers} )

