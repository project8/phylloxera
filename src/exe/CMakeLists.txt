set( PROJECT_LIBS
    KryptonPdf
    PdfFactory
    TritiumPdf
)

set( PROGRAMS )


set( SOURCEFILES
    KuriePlot.cxx
)

pbuilder_executables( 
    SOURCES ${SOURCEFILES}
    TARGETS_VAR PROGRAMS
    PROJECT_LIBRARIES ${PROJECT_LIBS}
    PUBLIC_EXTERNAL_LIBRARIES ${PUBLIC_EXT_LIBS}
)


# Export
pbuilder_component_install_and_export( 
    COMPONENT Executables
    EXETARGETS ${PROGRAMS}
)
