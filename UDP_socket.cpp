//
// Created by Eugenio Moro on 25/10/22.
//

#include "UDP_socket.h"

UDP_socket::UDP_socket(uint16_t in_port, uint16_t out_port) {
    this->in_port = in_port;
    this->out_port = out_port;
    in_ep = new basio::ip::udp::endpoint(boost::asio::ip::make_address(LOOPBACK), in_port);
    out_ep = new basio::ip::udp::endpoint(boost::asio::ip::make_address(LOOPBACK), out_port);
    in_socket = new basio::ip::udp::socket(io_context, *in_ep);
    out_socket.open(basio::ip::udp::v4());
}

std::size_t UDP_socket::send(char *buf, std::size_t len) {
    std::size_t sentlen;
    try{
        sentlen = out_socket.send_to(basio::buffer(buf, len), *out_ep);
    }
    catch (std::exception& e){
        std::cout << e.what() << std::endl;
        return 0;
    }
    return sentlen;
}

std::size_t UDP_socket::sendAsString(std::string buffer) {
    std::size_t sentlen;
    try{
        sentlen = out_socket.send_to(basio::buffer(buffer), *out_ep);
    }
    catch (std::exception& e){
        std::cout << e.what() << std::endl;
        return 0;
    }
    return sentlen;
}

std::size_t UDP_socket::receive(char **buf) {
    try{
        basio::ip::udp::endpoint sender;
        *buf = (char*) malloc(MAXLEN);
        std::size_t recvlen = in_socket->receive_from(basio::buffer(*buf, MAXLEN), sender);
        return recvlen;
    }
    catch (std::exception& e){
        std::cout << e.what() << std::endl;
        return 0;
    }
}