//
// Created by Eugenio Moro on 31/10/22.
//

#include "client.h"
#define PING_TARGET "www.google.com"
#define PING_COUNT 1

int main(){
    std::cout << "Starting client\n";
    UDP_socket socket(6656,6655);
    char* recvbuf;
    std::size_t recvlen;
    std::size_t sentlen;

    // master request
    MasterRequest master_req;
    std::string master_req_buf;

    // ping
    std::cout << "Building and sending ping request\n";
    PingRequest* ping_request = new PingRequest;
    ping_request->set_target(PING_TARGET);
    ping_request->set_count(PING_COUNT);
    master_req.set_allocated_ping_request(ping_request);
    master_req_buf = master_req.SerializeAsString();
    sentlen = socket.sendAsString(master_req_buf);
    std::cout << sentlen << " bytes sent. Waiting for ping response...\n";
    recvlen = socket.receive(&recvbuf);
    std::cout << "Received " << recvlen << " bytes\n";
    PingResponse pr;
    pr.ParseFromArray(recvbuf, recvlen);
    std::cout << "Printing ping response...\n";
    pr.PrintDebugString();
    // clear master request and memory
    master_req.release_ping_request();
    delete(ping_request);
    free(recvbuf);
    press_any_k_to_continue();

    // iface ipv4
    std::cout << "\n----------\nBuilding and sending ipv4 interface list request\n";
    IfaceListRequest* iface_req = new IfaceListRequest;
    iface_req->set_ip_version(::ipv4);
    master_req.set_allocated_iface_list_request(iface_req);
    master_req_buf = master_req.SerializeAsString();
    sentlen = socket.sendAsString(master_req_buf);
    std::cout << sentlen << " bytes sent. Waiting for ping response...\n";
    recvlen = socket.receive(&recvbuf);
    std::cout << "Received " << recvlen << " bytes\n";
    IfaceListResposne rsp;
    rsp.ParseFromArray(recvbuf,recvlen);
    std::cout << "Printing interface list response...\n";
    rsp.PrintDebugString();
    free(recvbuf);
    press_any_k_to_continue();

    // iface ipv6
    std::cout << "\n----------\nBuilding and sending ipv4 interface list request\n";
    iface_req = master_req.release_iface_list_request();
    iface_req->set_ip_version(::ipv6);
    master_req.set_allocated_iface_list_request(iface_req);
    master_req_buf = master_req.SerializeAsString();
    sentlen = socket.sendAsString(master_req_buf);
    std::cout << sentlen << " bytes sent. Waiting for ping response...\n";
    recvlen = socket.receive(&recvbuf);
    std::cout << "Received " << recvlen << " bytes\n";
    rsp.ParseFromArray(recvbuf,recvlen);
    std::cout << "Printing interface list response...\n";
    rsp.PrintDebugString();
    free(recvbuf);
    return 0;
}

void press_any_k_to_continue(){
    std::cout << "Press any key to continue\n";
    system("read");
}