FROM ubuntu:18.04 AS build

RUN apt-get update && \
    apt-get install -y gcc g++ libboost-all-dev cmake

WORKDIR /code

ADD . .

RUN cd project && \
    mkdir build && \
    cd build && \
    cmake -DCMAKE_BUILD_TYPE=Release .. && \
    make -j $(nproc) 
    
FROM ubuntu:18.04 

COPY --from=build /code/project/build/mirageI /usr/bin/
COPY --from=build /code/project/build/mirageC /usr/bin/
ENTRYPOINT ["/usr/bin/mirageC"]
