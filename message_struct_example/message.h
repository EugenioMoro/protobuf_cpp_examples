//
// Created by Eugenio Moro on 26/10/22.
//

#ifndef PROTOBUF_CPP_EXAMPLES_MESSAGE_H
#define PROTOBUF_CPP_EXAMPLES_MESSAGE_H

#endif //PROTOBUF_CPP_EXAMPLES_MESSAGE_H

struct message {
    char header;
    int payload_len;
    const char* payload;
};
typedef struct message message_t;