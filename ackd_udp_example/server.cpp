//
// Created by Eugenio Moro on 26/10/22.
//

#include "../UDP_socket.h"
#include "datagram.pb.h"

#define RX_FAIL_PROB 10
#define RX_FAILED (rand()%100<RX_FAIL_PROB)

int main(){
    std::cout << "Starting server\n";
    UDP_socket socket(6655,6656);
    char* recvbuf;
    std::size_t recvlen;

    ack a;
    a.set_ackd(true);
    std::string ackbuf;

    datagram dt;
    int seg_no;
    char* databuf;
    std::string data = "";

    for(;;){
        recvlen = socket.receive(&recvbuf);
        //std::cout << std::string(recvbuf, recvlen) << "   size " << recvlen << std::endl;
        std::cout << "Received " << recvlen << " bytes\nDecoding as datagram\n";
        dt.ParseFromArray(recvbuf,recvlen);
        std::cout << "Received segment " << dt.segment_no() << std::endl;
        if (RX_FAILED){
            a.set_ackd(false);
            std::cout << "Sending NACK\n";
            a.set_segment_no(dt.segment_no());
            a.SerializeToString(&ackbuf);
            socket.sendAsString(ackbuf);
            continue;
        } else {
            a.set_ackd(true);
            data = data + (std::string(dt.data()));
            std::cout << "Sending ACK\n";
            a.set_segment_no(dt.segment_no());
            a.SerializeToString(&ackbuf);
            socket.sendAsString(ackbuf);
        }

        if(dt.more_segments()){
            std::cout << "Waiting for more segments\n";
        } else {
            std::cout << "This was the last segment, printing received data:\n";
            std::cout << data;
            std::cout << std::endl;
            data = "";
            //break;
        }
        free(recvbuf);
    }
    //std::cout << data;
}