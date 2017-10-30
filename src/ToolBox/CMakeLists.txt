###########
# control #
###########

set( sources
    #Constant.cpp
    Conversion.cpp
    Plots.cpp
    RooFitTools.cpp
    VectorTools.cpp
)

###########
# library #
###########


#add_library (ToolBox ${sources} )

pbuilder_library( ToolBox sources "" )
target_link_libraries (ToolBox ${ROOT_LIBRARIES})

pbuilder_install_headers( ${headers} )

