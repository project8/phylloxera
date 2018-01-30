#################
# TritiumPdf #
#################

# set( headers
#     RealTritiumSpectrum.hh
#     SimpleTritiumSpectrum.hh
# )

# set( sources
#     RealTritiumSpectrum.cxx    
#     SimpleTritiumSpectrum.cxx    
# )


# ###########
# # Library #
# ###########

# pbuilder_library( TritiumPdf  sources "")
# target_link_libraries (TritiumPdf ${ROOT_LIBRARIES})
# pbuilder_install_libraries(TritiumPdf)
# pbuilder_install_headers( ${headers} )


set (headers
    RealTritiumSpectrum.hh
    SimpleTritiumSpectrum.hh
)

set (sources
    RealTritiumSpectrum.cxx    
    SimpleTritiumSpectrum.cxx   
)

set (dict_headers
RealTritiumSpectrum.hh
SimpleTritiumSpectrum.hh
)

set (linkdef_header LinkDef/TritiumPdfLinkDef.hh)
set (dict_outfile ${CMAKE_CURRENT_BINARY_DIR}/TritiumPdfDict.cxx)
set (dict_pcmfile ${CMAKE_CURRENT_BINARY_DIR}/TritiumPdfDict_rdict.pcm)


# ###########
# # Library #
# ###########


ROOT_GENERATE_DICTIONARY (TritiumPdfDict ${dict_headers} LINKDEF ${linkdef_header})
pbuilder_install_files (${LIB_INSTALL_DIR} ${dict_pcmfile} "")

add_library (TritiumPdf ${sources} ${dict_outfile})
target_link_libraries (TritiumPdf ${ROOT_LIBRARIES})

pbuilder_install_headers (${headers})
pbuilder_install_libraries (TritiumPdf)
