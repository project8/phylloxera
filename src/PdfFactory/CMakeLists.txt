#################
#   PdfFactory  #
#################

set (headers
    PdfFactory.hh
)

set (sources
    PdfFactory.cxx 
)

set (dict_headers
    PdfFactory.hh
)

set (linkdef_header LinkDef/PdfFactoryLinkDef.hh)
set (sources ${sources} ${CMAKE_CURRENT_BINARY_DIR}/PdfFactoryDict.cxx)
set (dict_pcmfile ${CMAKE_CURRENT_BINARY_DIR}/PdfFactoryDict_rdict.pcm)


# ###########
# # Library #
# ###########


ROOT_GENERATE_DICTIONARY (PdfFactoryDict ${dict_headers} LINKDEF ${linkdef_header})
pbuilder_install_files (${LIB_INSTALL_DIR} ${dict_pcmfile} "")

# add_library (PdfFactory ${sources} ${dict_outfile})
# target_link_libraries (PdfFactory ${ROOT_LIBRARIES})

pbuilder_library ( PdfFactory sources "" )
pbuilder_install_headers (${headers})

