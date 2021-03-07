FROM ubuntu:18.04

RUN apt-get update && \
    apt-get install -y gcc g++ libboost-all-dev cmake

WORKDIR /code

ADD . .

RUN cd project && \
    mkdir build && \
    cd build && \
    cmake .. && \
    make -j $(nproc) && \
    mv /code/project/build/mirage* /usr/bin && \
    rm -rf /code/*