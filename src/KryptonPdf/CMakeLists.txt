#################
#   KryptonPdf  #
#################

set( lib_name KryptonPdf )
set( dict_name KryptonPdfDict )

set (HEADERFILES
    AsymmetricKryptonLine.hh
    KryptonLine.hh
)

set (SOURCEFILES
    AsymmetricKryptonLine.cxx
    KryptonLine.cxx 
)

set (LINKDEF_HEADERFILE LinkDef/KryptonPdfLinkDef.hh)

set (PROJECT_LIBS ToolBox )

# ###########
# # Library #
# ###########

pbuilder_add_library(
    TARGET ${lib_name}
    SOURCES ${SOURCEFILES}
)

message( STATUS "Generating ROOT dictionary <${dict_name}>")
ROOT_GENERATE_DICTIONARY( ${dict_name} ${HEADERFILES} MODULE ${lib_name} LINKDEF ${LINKDEF_HEADERFILE} OPTIONS -inlineInputHeader )
pbuilder_install_files (${LIB_INSTALL_DIR} ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_SHARED_LIBRARY_PREFIX}${lib_name}_rdict.pcm)

pbuilder_link_library( 
    TARGET ${lib_name} 
    PROJECT_LIBRARIES ${PROJECT_LIBS}
    PUBLIC_EXTERNAL_LIBRARIES ${PUBLIC_EXT_LIBS}
)

pbuilder_component_install_and_export( 
    COMPONENT Library
    LIBTARGETS ${lib_name}
)

pbuilder_install_headers( ${HEADERFILES} )
