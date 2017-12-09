#################
#      IO       #
#################

set( headers
Dataset.hh
DatasetCollector.hh
RootFileInterface.hh
)

set( sources
Dataset.cxx
DatasetCollector.cxx  
RootFileInterface.cxx
)

###########
# Library #
###########

pbuilder_library( IO  sources "")
target_link_libraries (IO ${ROOT_LIBRARIES} Cicada_Phylloxera)
pbuilder_install_libraries(IO)
pbuilder_install_headers( ${headers} )

