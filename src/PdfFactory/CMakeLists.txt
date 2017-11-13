##############
# PdfFactory #
##############

set( headers
    Base.hh
    Project8PdfFactory.hh
)


set( sources
    Base.cxx
    Project8PdfFactory.cxx
)

###########
# library # 
###########

pbuilder_library( PdfFactory sources "" )
target_link_libraries (PdfFactory ${ROOT_LIBRARIES} KryptonPdf)
pbuilder_install_libraries(PdfFactory)
pbuilder_install_headers( ${headers} )

