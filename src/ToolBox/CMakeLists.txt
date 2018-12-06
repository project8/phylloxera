###########
# ToolBox #
###########

set ( headers
    Constant.hh
)

set( sources
    Conversion.cpp
    Plots.cpp
    RooFitTools.cpp
    VectorTools.cpp
)

###########
# library #
###########

pbuilder_library( ToolBox sources "")
pbuilder_install_headers( ${headers} )
