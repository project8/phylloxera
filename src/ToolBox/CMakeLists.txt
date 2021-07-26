###########
# ToolBox #
###########

set (lib_name ToolBox)

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

pbuilder_library( 
    TARGET ${lib_name}
    SOURCES ${sources} 
    PUBLIC_EXTERNAL_LIBRARIES ${PUBLIC_EXT_LIBS}
)

pbuilder_component_install_and_export(
    COMPONENT Library
    LIBTARGETS ${lib_name}
)

pbuilder_install_headers( ${headers} )
