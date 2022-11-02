//
// Created by Eugenio Moro on 26/10/22.
//

#include "../UDP_socket.h"
#include "message.pb.h"

int main(){
    std::cout << "Starting server\n";

    UDP_socket socket(6655,6656);
    std::cout << "Waiting for datagrams..." << std::endl;
    char* recv_buf;

    for(;;){
        std::size_t recvlen = socket.receive(&recv_buf);
        std::cout << "\n\nRecevied " << recvlen << " bytes\nDecoding as message\n";
        Message msg;
        msg.ParseFromArray(recv_buf, recvlen);
        msg.PrintDebugString();
        std::cout << "Header casted as char: " <<(char) msg.header() << std::endl;
        free(recv_buf);

    }

    return 0;
}