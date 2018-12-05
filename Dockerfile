FROM project8/p8compute_dependencies:v0.2.0 as phylloxera_common

ARG build_type=Release
ENV PHLLOXERA_BUILD_TYPE=$build_type

ENV PHLLOXERA_TAG=v1.2.4
ENV PHLLOXERA_BUILD_PREFIX=/usr/local/p8/phylloxera/$PHLLOXERA_TAG

RUN mkdir -p $PHLLOXERA_BUILD_PREFIX &&\
    cd $PHLLOXERA_BUILD_PREFIX &&\
    echo "source ${COMMON_BUILD_PREFIX}/setup.sh" > setup.sh &&\
    echo "export PHLLOXERA_TAG=${PHLLOXERA_TAG}" >> setup.sh &&\
    echo "export PHLLOXERA_BUILD_PREFIX=${PHLLOXERA_BUILD_PREFIX}" >> setup.sh &&\
    echo 'ln -sf $PHLLOXERA_BUILD_PREFIX $PHLLOXERA_BUILD_PREFIX/../current || /bin/true' >> setup.sh &&\
    echo 'export PATH=$PHLLOXERA_BUILD_PREFIX/bin:$PATH' >> setup.sh &&\
    echo 'export LD_LIBRARY_PATH=$PHLLOXERA_BUILD_PREFIX/lib:$LD_LIBRARY_PATH' >> setup.sh &&\
    /bin/true

########################
FROM phylloxera_common as phylloxera_done

COPY Scarab /tmp_source/Scarab
COPY src /tmp_source/src
COPY CMakeLists.txt /tmp_source/CMakeLists.txt
COPY this_phylloxera.sh.in /tmp_source/this_phylloxera.sh.in
COPY .git /tmp_source/.git

# repeat the cmake command to get the change of install prefix to set correctly (a package_builder known issue)
RUN source $PHLLOXERA_BUILD_PREFIX/setup.sh &&\
    cd /tmp_source &&\
    mkdir build &&\
    cd build &&\
    cmake -D CMAKE_BUILD_TYPE=$PHLLOXERA_BUILD_TYPE \
          -D CMAKE_INSTALL_PREFIX:PATH=$PHLLOXERA_BUILD_PREFIX \
          -D CMAKE_SKIP_INSTALL_RPATH:BOOL=True .. &&\
    cmake -D CMAKE_BUILD_TYPE=$PHLLOXERA_BUILD_TYPE \
          -D CMAKE_INSTALL_PREFIX:PATH=$PHLLOXERA_BUILD_PREFIX \
          -D CMAKE_SKIP_INSTALL_RPATH:BOOL=True .. &&\
    make -j3 install &&\
    /bin/true

########################
FROM phylloxera_common

COPY --from=phylloxera_done $PHLLOXERA_BUILD_PREFIX $PHLLOXERA_BUILD_PREFIX
