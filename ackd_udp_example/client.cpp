//
// Created by Eugenio Moro on 26/10/22.
//

#include "client.h"

#define DATA_TO_SEND "This is quite a long string, it will be divided into segments because the wire cannot support so much data all at once"

int main(){
    std::cout << "Starting client\n";
    UDP_socket socket(6656,6655);

    std::string dataToSend(DATA_TO_SEND);
    int segments = ceil((double)dataToSend.length() / (double)MAX_SEGMENT_SIZE);
    std::cout << "Data length is " << dataToSend.length() << std::endl;
    std::cout << "Will send " << segments << " segments of length " << MAX_SEGMENT_SIZE << std::endl;

    char* databuf = dataToSend.data();

    ack a;
    char* ackbuf;

    size_t sentlen;
    size_t recvlen;

    datagram dt;
    std::string dt_buffer;
    dt.set_more_segments(true);

    int seg=0;
    int retry_count=0;
    for(seg=0; seg < segments-1; seg++){

        dt.set_segment_no(seg);
        dt.set_data(&databuf[seg*MAX_SEGMENT_SIZE], MAX_SEGMENT_SIZE);
        dt.SerializeToString(&dt_buffer);
        sentlen=socket.sendAsString(dt_buffer);
        std::cout << "Sent segment " << seg+1 << " of " << segments << ", size " << sentlen << std::endl;

        // wait for ack
        std::cout << "Waiting for ACK\n";
        recvlen = socket.receive(&ackbuf);
        a.ParseFromArray(ackbuf, recvlen);
        if(a.ackd() && a.segment_no() == seg) {
            std::cout << "Ack received\n";
        } else {
            std::cout << "Bad ack, resending\n";
            seg--;
            retry_count++;
            continue;
        }
    }
    do {
        std::cout << "Sending last segment\n";
        dt.set_more_segments(false);
        dt.set_segment_no(seg);
        dt.set_data(databuf + seg * MAX_SEGMENT_SIZE, dataToSend.length() - seg * MAX_SEGMENT_SIZE);
        dt.SerializeToString(&dt_buffer);
        sentlen = socket.sendAsString(dt_buffer);
        std::cout << "Sent " << sentlen << " bytes\n";
        std::cout << "Waiting for ACK\n";
        recvlen = socket.receive(&ackbuf);
        a.ParseFromArray(ackbuf, recvlen);
        if (a.ackd() && a.segment_no() == seg) {
            std::cout << "Ack received\n";
        } else {
            std::cout << "Bad ack, resending\n";
            retry_count++;
        }
    } while (!(a.ackd() && a.segment_no() == seg));
    if(!retry_count){
       std::cout << dataToSend.length() << " bytes sent without retransmissions\n";
    } else{
        std::cout << dataToSend.length() << " bytes sent with " << retry_count << " retransmissions\n";
    }
}
