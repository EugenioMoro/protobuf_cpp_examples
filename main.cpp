#include <iostream>
#include "UDP_socket.h"

int main() {
    std::cout << "Hello, World!" << std::endl;

    UDP_socket sk(6655,6656);
    sk.send("ciao",5);

    return 0;
}
