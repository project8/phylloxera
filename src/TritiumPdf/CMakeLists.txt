#################
# TritiumPdf #
#################

set (headers
    DistortedTritiumSpectrum.hh
    RealTritiumSpectrum.hh
    SimpleTritiumSpectrum.hh
)

set (sources
    DistortedTritiumSpectrum.cxx
    RealTritiumSpectrum.cxx    
    SimpleTritiumSpectrum.cxx   
)

set (dict_headers
DistortedTritiumSpectrum.hh
RealTritiumSpectrum.hh
SimpleTritiumSpectrum.hh
)

set (dep_libraries
    TritiumSpectrum
)

set (linkdef_header LinkDef/TritiumPdfLinkDef.hh)
set (sources ${sources} ${CMAKE_CURRENT_BINARY_DIR}/TritiumPdfDict.cxx)
set (dict_pcmfile ${CMAKE_CURRENT_BINARY_DIR}/TritiumPdfDict_rdict.pcm)


# ###########
# # Library #
# ###########


ROOT_GENERATE_DICTIONARY (TritiumPdfDict ${dict_headers} LINKDEF ${linkdef_header})
pbuilder_install_files (${LIB_INSTALL_DIR} ${dict_pcmfile})

pbuilder_library (TritiumPdf sources dep_libraries )
pbuilder_install_headers (${headers})
