FROM ubuntu:latest as builder

RUN apt-get update && \
    apt-get install -y  \
    build-essential \
    cmake \
    git \
    libgrpc++-dev \
    libprotobuf-dev \
    protobuf-compiler \
    protobuf-compiler-grpc \
    libvisa-dev \
    autoconf libtool \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app
COPY server/ server/

RUN mkdir proto 
COPY proto/rfcontrol.proto proto
RUN cd proto && protoc --cpp_out=. --grpc_out=. --plugin=protoc-gen-grpc=`which grpc_cpp_plugin` rfcontrol.proto
RUN mkdir -p server/build && \
    cd server/build && \
    cmake .. && \
    make

FROM ubuntu:latest

RUN apt-get update && \
    apt-get install -y  \
    libgrpc++-dev \
    libprotobuf-dev \
    protobuf-compiler \
    protobuf-compiler-grpc \
    libvisa-dev \
    # libgrpc++1 \
    # libprotobuf23 \
    # libvisa0 \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app
COPY --from=builder /app .

EXPOSE 50051

CMD ["./server/build/rf_server"]

