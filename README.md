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
All examples tested on MacOS 12.4 and Ubuntu 20.4 (Windows not supported). 

You can also use the Dockerfile to build the environment with all the prerequisites and this repository
```
docker build -t netp-protobuf:1.0 - < Dockerfile
docker run -dit --name netp-protobuf netp-protobuf:1.0
docker exec -it netp-protobuf bash
```
A prebuilt image is also available on [Docker Hub](https://hub.docker.com/repository/docker/mychele/netp-protobuf).
