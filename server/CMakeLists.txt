cmake_minimum_required(VERSION 3.10)
project(rf_controller_server2)

set(CMAKE_CXX_STANDARD 17)
include_directories(${CMAKE_SOURCE_DIR}/../proto)

set(PROTO_SRCS
    ../../proto/rfcontrol.pb.cc
    ../../proto/rfcontrol.grpc.pb.cc
)
set(PROTO_HDRS
    ../../proto/rfcontrol.pb.h
    ../../proto/rfcontrol.grpc.pb.h
)

add_executable(rf_server 
    server.cpp 
    visa_handler.cpp
    ${PROTO_SRCS} 
    ${PROTO_HDRS}
)

target_link_libraries(rf_server
    grpc++
    grpc
    gpr
    absl_synchronization
    protobuf
    # ${Protobuf_LIBRARIES}
    # ${GRPC_LIBRARIES}
    # ${GRPC_GRPCPP_LIBRARY}
    visa
    pthread
)
