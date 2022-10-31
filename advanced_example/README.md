# Protobuf C++ Examples

## 1 - Message Struct Example
In this example we don't make use of any serialization tool. We try to send raw structs straight from the memory. 

## 2 - Message Proto Example
In this example we send the data structure of the previous example serialized with protobuf.

## 3 - Acked UDP Example
This example shows how protobuf can be useful to define custom protocol, such as this extremely simple acked UDP protocol. 

## 4 - Advanced Example
This example shows how to implement remote procedure calls with protobuf. 

# Usage
Requirements:
* Boost (for UDP sockets)
* Protobuf C++ (obviously)

Then build:
```
mkdir build && cd build
cmake ..
make
```
All examples tested on MacOS 12.4, should work on Linux (windows not supported). 