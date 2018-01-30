# ##############
# # PdfFactory #
# ##############

# set( headers
#     PdfFactory.hh
# )


# set( sources
#     PdfFactory.cxx
# )

# ###########
# # library # 
# ###########

# pbuilder_library( PdfFactory sources "" )
# target_link_libraries (PdfFactory ${ROOT_LIBRARIES} KryptonPdf)
# pbuilder_install_libraries(PdfFactory)
# pbuilder_install_headers( ${headers} )

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

set (linkdef_header LinkDef/KryptonPdfLinkDef.hh)
set (dict_outfile ${CMAKE_CURRENT_BINARY_DIR}/PdfFactoryDict.cxx)
set (dict_pcmfile ${CMAKE_CURRENT_BINARY_DIR}/PdfFactoryDict_rdict.pcm)


# ###########
# # Library #
# ###########


ROOT_GENERATE_DICTIONARY (PdfFactoryDict ${dict_headers} LINKDEF ${linkdef_header})
pbuilder_install_files (${LIB_INSTALL_DIR} ${dict_pcmfile} "")

add_library (PdfFactory ${sources} ${dict_outfile})
target_link_libraries (PdfFactory ${ROOT_LIBRARIES})

pbuilder_install_headers (${headers})
pbuilder_install_libraries (PdfFactory)

