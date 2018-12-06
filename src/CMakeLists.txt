# subdirectories
include_directories (BEFORE 
    ${PROJECT_SOURCE_DIR}/src/KryptonPdf
    ${PROJECT_SOURCE_DIR}/src/PdfFactory
    ${PROJECT_SOURCE_DIR}/src/ToolBox
    ${PROJECT_SOURCE_DIR}/src/TritiumPdf
    ${PROJECT_SOURCE_DIR}/src/TritiumSpectrum
)
# Since we don't use these libraries from the outside, there is no need to build a .dylib from these
add_subdirectory (ToolBox)
add_subdirectory (TritiumSpectrum)

add_subdirectory (PdfFactory)
add_subdirectory (TritiumPdf)
add_subdirectory (KryptonPdf)
IF (Phylloxera_ENABLE_EXECUTABLES)
    include_directories(${PROJECT_SOURCE_DIR}/src/exe)
    add_subdirectory (exe)
ENDIF(Phylloxera_ENABLE_EXECUTABLES)

if( Phylloxera_ADD_PHYLLOXERA_PY )

    # Add extra libraries to load below. Remember to add it to python/Phylloxera.py.in
    set( KryptonPdflib_target KryptonPdf${Phylloxera_PARENT_LIB_NAME_SUFFIX} )
    set( PdfFactorylib_target PdfFactory${Phylloxera_PARENT_LIB_NAME_SUFFIX} )
    set( TritiumPdflib_target TritiumPdf${Phylloxera_PARENT_LIB_NAME_SUFFIX} )

    configure_file( ${CMAKE_CURRENT_SOURCE_DIR}/python/PhylloxeraPy.py.in ${CMAKE_CURRENT_BINARY_DIR}/PhylloxeraPy.py.gen.in )
    file( GENERATE OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/PhylloxeraPy.py INPUT ${CMAKE_CURRENT_BINARY_DIR}/PhylloxeraPy.py.gen.in )
    
    pbuilder_install_files( ${LIB_INSTALL_DIR}/PhylloxeraPy ${CMAKE_CURRENT_BINARY_DIR}/PhylloxeraPy.py )
    pbuilder_install_files( ${LIB_INSTALL_DIR}/PhylloxeraPy ${CMAKE_CURRENT_SOURCE_DIR}/python/__init__.py )
endif( Phylloxera_ADD_PHYLLOXERA_PY )