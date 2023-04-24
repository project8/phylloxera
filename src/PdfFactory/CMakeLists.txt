#################
#   PdfFactory  #
#################

set( lib_name PdfFactory )
pbuilder_expand_lib_name( ${lib_name} )
set( full_lib_name ${FULL_LIB_NAME} )
set( dict_name PdfFactoryDict )

set (HEADERFILES
    PdfFactory.hh
)

set (SOURCEFILES
    PdfFactory.cxx 
)

set (LINKDEF_HEADERFILE LinkDef/PdfFactoryLinkDef.hh)

set (PROJECT_LIBS ToolBox )

# ###########
# # Library #
# ###########

pbuilder_library(
    TARGET ${lib_name}
    SOURCES ${SOURCEFILES}
    PROJECT_LIBRARIES ${PROJECT_LIBS}
    PUBLIC_EXTERNAL_LIBRARIES ${PUBLIC_EXT_LIBS}
)

message( STATUS "Generating ROOT dictionary <${dict_name}>")
ROOT_GENERATE_DICTIONARY( ${dict_name} ${HEADERFILES} MODULE ${full_lib_name} LINKDEF ${LINKDEF_HEADERFILE} OPTIONS -inlineInputHeader )
pbuilder_install_files (${LIB_INSTALL_DIR} ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_SHARED_LIBRARY_PREFIX}${full_lib_name}_rdict.pcm)

pbuilder_component_install_and_export( 
    COMPONENT Library
    LIBTARGETS ${lib_name}
)

pbuilder_install_headers( ${HEADERFILES} )
