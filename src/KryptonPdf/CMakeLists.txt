#################
#   KryptonPdf  #
#################

set (KRYPTONPDF_HEADERFILES
KryptonLine.hh
)

set (KRYPTONPDF_SOURCEFILES
KryptonLine.cxx 
)

set (KRYPTONPDF_DICT_HEADERFILES
KryptonLine.hh
)

set (KRYPTONPDF_LINKDEF_HEADERFILE LinkDef/KryptonPdfLinkDef.hh)
set (KRYPTONPDF_DICT_OUTFILE ${CMAKE_CURRENT_BINARY_DIR}/KryptonPdfDict.cxx)
set (KRYPTONPDF_DICT_PCMFILE ${CMAKE_CURRENT_BINARY_DIR}/KryptonPdfDict_rdict.pcm)


# ###########
# # Library #
# ###########


ROOT_GENERATE_DICTIONARY (KryptonPdfDict ${KRYPTONPDF_DICT_HEADERFILES} LINKDEF ${KRYPTONPDF_LINKDEF_HEADERFILE})
pbuilder_install_files (${LIB_INSTALL_DIR} ${KRYPTONPDF_DICT_PCMFILE} "")

add_library (KryptonPdf ${KRYPTONPDF_SOURCEFILES} ${KRYPTONPDF_DICT_OUTFILE})
target_link_libraries (KryptonPdf ${ROOT_LIBRARIES})

pbuilder_install_headers (${KRYPTONPDF_HEADERFILES})
pbuilder_install_libraries (KryptonPdf)