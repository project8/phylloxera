##############
# PdfFactory #
##############

set( headers
    PdfFactory.hh
)


set( sources
    PdfFactory.cxx
)

###########
# library # 
###########

pbuilder_library( PdfFactory sources "" )
target_link_libraries (PdfFactory ${ROOT_LIBRARIES} KryptonPdf)
pbuilder_install_libraries(PdfFactory)
pbuilder_install_headers( ${headers} )

