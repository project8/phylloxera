FROM guiguem/root-docker:python3

MAINTAINER Mathieu Guigue "Mathieu.Guigue@pnnl.gov"

COPY . /phylloxera

RUN chmod +x /phylloxera/install_docker.sh &&\
    /phylloxera/install_docker.sh

CMD ['source /setup.sh']
