//
// Created by Eugenio Moro on 31/10/22.
//

#include "server.h"

int main(){
    std::cout << "Starting server\n";
    UDP_socket socket(6655,6656);
    char* recvbuf;
    std::string outbuf;
    std::size_t recvlen;
    std::size_t sentlen;
    MasterRequest master_req;
    std::cout << "Waiting for datagrams...\n";

    for(;;){
        recvlen = socket.receive(&recvbuf);
        std::cout << "Received " << recvlen << " bytes\n";
        master_req.ParseFromArray(recvbuf,recvlen);
        if (master_req.has_ping_request()){
            std::cout << "Handling ping request for target " << master_req.ping_request().target() <<
                " with count " << master_req.ping_request().count() << std::endl;
            PingResponse pr = handle_ping_request(master_req.ping_request());
            outbuf = pr.SerializeAsString();
            sentlen = socket.sendAsString(outbuf);
            std::cout << "Ping response of " << sentlen << " bytes sent\n";
        } else if (master_req.has_iface_list_request()){
            std::cout << "Handling interface list request\n";
            IfaceListResposne rsp = handle_iface_request(master_req.iface_list_request());
            outbuf= rsp.SerializeAsString();
            sentlen = socket.sendAsString(outbuf);
            std::cout << "Interface list response of " << sentlen << " bytes sent\n";
        }
    }
}

PingResponse handle_ping_request(PingRequest ping_request){
    std::string cmd = build_ping_cmd(ping_request.target(), ping_request.count());
    std::string res = exec(cmd.c_str());
    PingResponse pr;
    pr.set_target(ping_request.target());
    std::string token;
    int i=0;
    std::stringstream ss(res);
    while (std::getline(ss, token, '\n')) {
        switch (i){
            case 0:
                pr.set_min(std::stod(token));
                break;
            case 1:
                pr.set_avg(std::stod(token));
                break;
            case 2:
                pr.set_max(std::stod(token));
                break;
        }
        i++;
        if (i>2){
            break;
        }
    }
    return pr;
}

IfaceListResposne handle_iface_request(IfaceListRequest req){
    IfaceListResposne rsp;
    std::vector<std::string> i_names;
    std::vector<std::string> i_addrs;
    std::string token;
    std::string names_cmd;
    std::string addrs_cmd;
    if (req.ip_version() == ::ipv4){
        names_cmd = V4_IFACES_NAMES;
        addrs_cmd = V4_IFACES_ADDRS;
    } else if (req.ip_version() == ::ipv6){
        names_cmd = V6_IFACES_NAMES;
        addrs_cmd = V6_IFACES_ADDRS;
    }
    std::stringstream ss(exec(names_cmd.c_str()));
    while (std::getline(ss, token, '\n')){
        i_names.push_back(token);
    }
    ss = std::stringstream(exec(addrs_cmd.c_str()));
    while (std::getline(ss, token, '\n')){
        i_addrs.push_back(token);
    }
    assert(i_names.size() == i_addrs.size());
    for (int i=0; i<i_names.size(); i++){
        Iface* iface = rsp.add_interfaces();
        iface->set_ip_version(req.ip_version());
        iface->set_name(i_names[i]);
        iface->set_address(i_addrs[i]);
    }
    return rsp;
}

std::string exec(const char* cmd) {
    std::array<char, 128> buffer;
    std::string result;
    std::shared_ptr<FILE> pipe(popen(cmd, "r"), pclose);
    if (!pipe) throw std::runtime_error("popen() failed!");
    while (!feof(pipe.get())) {
        if (fgets(buffer.data(), 128, pipe.get()) != nullptr)
            result += buffer.data();
    }
    return result;
}

std::string build_ping_cmd(std::string target, int count){
    std::string ret = "ping " + target + " -c" + std::to_string(count) + " " + PING_TRAILER;
    return ret;
}