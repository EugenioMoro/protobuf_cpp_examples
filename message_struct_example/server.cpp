//
// Created by Eugenio Moro on 25/10/22.
//

#include "../UDP_socket.h"
#include "./message.h"

#define PRINT_PAYLOAD 0

int main(){
    std::cout << "Starting server" << std::endl;
    UDP_socket socket(6655,6656);
    std::cout << "Waiting for datagrams..." << std::endl;
    char* recv_buf;
    message_t* msg;
    for(;;){
        std::size_t revlen = socket.receive(&recv_buf);
        std::cout << "Received " << revlen << " bytes" << std::endl;
        msg = (message_t*) recv_buf;
        std::cout << "Decoding as message_t:" << std::endl;
        std::cout << "\theader: " << msg->header << "\n\tpayload length: " << msg->payload_len << std::endl;
        if(PRINT_PAYLOAD) {
            std::cout << "\tpayload: " << msg->payload << std::endl;
        }
        
        delete msg;
    };
}
