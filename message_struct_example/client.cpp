//
// Created by Eugenio Moro on 25/10/22.
//

#include "../UDP_socket.h"
#include "./message.h"

#define PAYLOAD "this is our payload"
#define HEADER 'k'

int main(){
    std::cout << "Starting client" << std::endl;
    UDP_socket socket(6656,6655);

    // build message
    message_t* msg;
    msg = (message_t*) malloc(sizeof(message_t));
    std::string payload{PAYLOAD};
    msg->payload_len = payload.length() + 1;
    msg->payload = (char*) malloc(payload.length()+1);
    msg->payload = payload.c_str();
    msg->header = HEADER;
    std::cout << "Message struct created:\n\theader is: " << msg->header << "\n\tpayload is: " << msg->payload << "\n\tstruct size is: " << sizeof(msg) << std::endl;

    // send message
    std::size_t sent_len = socket.send((char*) msg, sizeof(msg));
    std::cout << "Sent " << sent_len << " bytes" << std::endl;

    delete msg;
}
