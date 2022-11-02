//
// Created by Eugenio Moro on 31/10/22.
//

#ifndef PROTOBUF_CPP_EXAMPLES_COMMON_H
#define PROTOBUF_CPP_EXAMPLES_COMMON_H

#define V4_IFACES_NAMES "netstat -in | grep -E '[0-9]{1,3}\\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}' | cut -f1 -d ' '"
#define V4_IFACES_ADDRS "netstat -in | grep -E '[0-9]{1,3}\\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}' | tr -s ' ' | cut -f4 -d ' '"
#define V6_IFACES_NAMES "netstat -in | grep -E ':' | cut -f1 -d ' '"
#define V6_IFACES_ADDRS "netstat -in | grep -E ':' | tr -s ' ' |cut -f4 -d ' '"

#define PING_TRAILER "-q | tail -n 1 | cut -f 4,5,6 -d '/' | cut -c 10- | tr '/' '\n'"

#endif //PROTOBUF_CPP_EXAMPLES_COMMON_H
