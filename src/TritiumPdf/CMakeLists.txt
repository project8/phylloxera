#################
# TritiumPdf #
#################

set (TritiumPdf_dict_headers
DistortedTritiumSpectrum.hh
RealTritiumSpectrum.hh
SimpleTritiumSpectrum.hh
)

set (TritiumPdf_headers
    ${TritiumPdf_dict_headers}
)

set (TritiumPdf_sources
    DistortedTritiumSpectrum.cxx
    RealTritiumSpectrum.cxx
    SimpleTritiumSpectrum.cxx
)

set (dict_headers
DistortedTritiumSpectrum.hh
RealTritiumSpectrum.hh
SimpleTritiumSpectrum.hh
)


set (TritiumPdf_dependencies
TritiumSpectrum
)

set (TritiumPdf_linkdef_header LinkDef/TritiumPdfLinkDef.hh)
set (TritiumPdf_sources ${TritiumPdf_sources} ${CMAKE_CURRENT_BINARY_DIR}/TritiumPdfDict.cxx)
set (TritiumPdf_dict_pcmfile ${CMAKE_CURRENT_BINARY_DIR}/TritiumPdfDict_rdict.pcm)


# ###########
# # Library #
# ###########

ROOT_GENERATE_DICTIONARY (TritiumPdfDict ${TritiumPdf_dict_headers} LINKDEF ${TritiumPdf_linkdef_header} OPTIONS -inlineInputHeader)
pbuilder_install_files (${LIB_INSTALL_DIR} ${TritiumPdf_dict_pcmfile})

pbuilder_library (TritiumPdf TritiumPdf_sources TritiumPdf_dependencies )
pbuilder_install_headers (${TritiumPdf_headers})
