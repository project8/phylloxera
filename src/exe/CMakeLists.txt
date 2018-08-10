set (APPS_HEADERFILES

)

set( LIB_DEPENDENCIES
KryptonPdf
PdfFactory
TritiumPdf
)

set( PROGRAMS
KuriePlot
)

pbuilder_executables( PROGRAMS LIB_DEPENDENCIES )
pbuilder_install_headers (${APPS_HEADERFILES})