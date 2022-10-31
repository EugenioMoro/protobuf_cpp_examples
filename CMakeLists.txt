cmake_minimum_required(VERSION 3.22)
project(protobuf_cpp_examples)
set(CMAKE_CXX_STANDARD 17)

# find boost for udp sockets
find_package(Boost REQUIRED system)

# find protobuf, include proto lib directory and cmake_bin_dir where proto will be generated, then generate
find_package(Protobuf REQUIRED)
include_directories(${Protobuf_INCLUDE_DIRS} ${CMAKE_BINARY_DIR})



# message struct example
add_executable(server_struct message_struct_example/server.cpp message_struct_example/server.h UDP_socket.cpp UDP_socket.h message_struct_example/message.h)
add_executable(client_struct message_struct_example/client.cpp message_struct_example/client.h UDP_socket.cpp UDP_socket.h message_struct_example/message.h)
target_link_libraries(server_struct ${Boost_LIBRARIES})
target_link_libraries(client_struct ${Boost_LIBRARIES})

# message proto example
protobuf_generate_cpp(PROTO_MSG_SRCS PROTO_MSG_HDRS message_proto_example/message.proto)
add_executable(client_proto message_proto_example/client.cpp UDP_socket.cpp UDP_socket.h ${PROTO_MSG_SRCS} ${PROTO_MSG_HDRS})
target_link_libraries(client_proto ${Boost_LIBRARIES} ${PROTOBUF_LIBRARY})
add_executable(server_proto message_proto_example/server.h message_proto_example/server.cpp UDP_socket.h UDP_socket.cpp ${PROTO_MSG_SRCS} ${PROTO_MSG_HDRS})
target_link_libraries(server_proto ${Boost_LIBRARIES} ${PROTOBUF_LIBRARY})

# acknowledged udp
protobuf_generate_cpp(PROTO_AUDP_SRCS PROTO_AUDP_HDRS ackd_udp_example/datagram.proto)
add_executable(client_audp ackd_udp_example/client.h ackd_udp_example/client.cpp UDP_socket.h UDP_socket.cpp ${PROTO_AUDP_SRCS} ${PROTO_AUD_HDRS} ackd_udp_example/common.h)
target_link_libraries(client_audp ${Boost_LIBRARIES} ${PROTOBUF_LIBRARY})
add_executable(server_audp ackd_udp_example/server.h ackd_udp_example/server.cpp UDP_socket.h UDP_socket.cpp ${PROTO_AUDP_SRCS} ${PROTO_AUD_HDRS} ackd_udp_example/common.h)
target_link_libraries(server_audp ${Boost_LIBRARIES} ${PROTOBUF_LIBRARY})

# advanced example
protobuf_generate_cpp(PROTO_ADV_SRCS PROTO_ADV_HDRS advanced_example/requests.proto)
add_executable(client_adv advanced_example/client.h advanced_example/client.cpp UDP_socket.h UDP_socket.cpp ${PROTO_ADV_SRCS} ${PROTO_ADV_HDRS})
target_link_libraries(client_adv ${Boost_LIBRARIES} ${PROTOBUF_LIBRARY})
add_executable(server_adv advanced_example/server.h advanced_example/server.cpp UDP_socket.h UDP_socket.cpp ${PROTO_ADV_SRCS} ${PROTO_ADV_HDRS})
target_link_libraries(server_adv ${Boost_LIBRARIES} ${PROTOBUF_LIBRARY})