//
// Created by Eugenio Moro on 26/10/22.
//

#include "client.h"

#define PAYLOAD "this is our payload, use it well"
#define HEADER 'k'

int main(){
    std::cout << "Starting client\n";

    // build message
    Message msg;
    msg.set_header((uint32_t) HEADER);
    std::string payload = PAYLOAD;
    msg.set_payload_length(payload.length());
    msg.set_payload(payload.c_str());
    std::cout << "Message created, now printing:\n";
    msg.PrintDebugString();

    // create socket and send
    UDP_socket socket(6656,6655);
    std::string msg_buffer;
    msg.SerializeToString(&msg_buffer);
    std::size_t sentlen = socket.sendAsString(msg_buffer);
    std::cout << "Sent " << sentlen << " bytes";

    return 0;
}
