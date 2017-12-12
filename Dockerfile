FROM guiguem/root-docker:latest

MAINTAINER Mathieu Guigue "Mathieu.Guigue@pnnl.gov"

ADD . /phylloxera

RUN /bin/bash -c "pip install pip --upgrade &&\
    source /setup.sh &&\
    pip install colorlog &&\
    mkdir -p /phylloxera/build &&\
    cd /phylloxera/build &&\
    git submodule update --init --recursive &&\
    cmake .. &&\
    make -j3 &&\
    make -j3 install"

ADD setup_phylloxera.sh setup_phylloxera.sh
