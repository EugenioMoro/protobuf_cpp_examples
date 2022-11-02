//
// Created by Eugenio Moro on 31/10/22.
//

#ifndef PROTOBUF_CPP_EXAMPLES_SERVER_H
#define PROTOBUF_CPP_EXAMPLES_SERVER_H

#include "common.h"
#include "../UDP_socket.h"
#include "requests.pb.h"

// includes for cmd
#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>
#include <regex>
#include <vector>


PingResponse handle_ping_request(PingRequest ping_request);
IfaceListResposne handle_iface_request(IfaceListRequest req);
std::string exec(const char* cmd);
std::string build_ping_cmd(std::string target, int count);

#endif //PROTOBUF_CPP_EXAMPLES_SERVER_H
