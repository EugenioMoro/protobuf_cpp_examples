//
// Created by Eugenio Moro on 25/10/22.
//

#ifndef PROTOBUF_CPP_EXAMPLES_UDP_SOCKET_H
#define PROTOBUF_CPP_EXAMPLES_UDP_SOCKET_H

#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <boost/bind.hpp>
#include <thread>
#include <iostream>

#define LOOPBACK "127.0.0.1"
#define MAXLEN 1024

namespace basio = boost::asio;

class UDP_socket {
    basio::io_context io_context;
    basio::ip::udp::endpoint ep;
    basio::ip::udp::socket* in_socket;
    basio::ip::udp::socket out_socket{io_context};
    basio::ip::udp::endpoint* in_ep;
    basio::ip::udp::endpoint* out_ep;

public:
    uint16_t in_port;
    uint16_t out_port;
    UDP_socket(uint16_t in_port, uint16_t out_port);
    std::size_t send(char* buf, std::size_t len);
    std::size_t sendAsString(std::string buffer);
    std::size_t receive(char** buf);
};


#endif //PROTOBUF_CPP_EXAMPLES_UDP_SOCKET_H
