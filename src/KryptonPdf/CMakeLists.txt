#################
#   KryptonPdf  #
#################

set (KRYPTONPDF_HEADERFILES
AsymmetricKryptonLine.hh
KryptonLine.hh
)

set (KRYPTONPDF_SOURCEFILES
AsymmetricKryptonLine.cxx
KryptonLine.cxx 
)

set (KRYPTONPDF_DICT_HEADERFILES
AsymmetricKryptonLine.hh
KryptonLine.hh
)

set (KRYPTONPDF_LINKDEF_HEADERFILE LinkDef/KryptonPdfLinkDef.hh)
set (KRYPTONPDF_SOURCEFILES ${KRYPTONPDF_SOURCEFILES} ${CMAKE_CURRENT_BINARY_DIR}/KryptonPdfDict.cxx)
set (KRYPTONPDF_DICT_PCMFILE ${CMAKE_CURRENT_BINARY_DIR}/KryptonPdfDict_rdict.pcm)


# ###########
# # Library #
# ###########


ROOT_GENERATE_DICTIONARY (KryptonPdfDict ${KRYPTONPDF_DICT_HEADERFILES} LINKDEF ${KRYPTONPDF_LINKDEF_HEADERFILE})
pbuilder_install_files (${LIB_INSTALL_DIR} ${KRYPTONPDF_DICT_PCMFILE})

pbuilder_library( KryptonPdf KRYPTONPDF_SOURCEFILES ToolBox )
pbuilder_install_headers (${KRYPTONPDF_HEADERFILES})