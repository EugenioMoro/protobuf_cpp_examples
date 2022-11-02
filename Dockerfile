FROM ubuntu:20.04

ARG DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get -y install wget gpg

RUN wget -O - https://apt.kitware.com/keys/kitware-archive-latest.asc 2>/dev/null | gpg --dearmor - | tee /usr/share/keyrings/kitware-archive-keyring.gpg >/dev/null

RUN echo "deb [signed-by=/usr/share/keyrings/kitware-archive-keyring.gpg] https://apt.kitware.com/ubuntu/ focal main" | tee /etc/apt/sources.list.d/kitware.list >/dev/null


RUN apt-get update && \
	apt-get install -y libboost-all-dev \
	git g++ iputils-ping netcat net-tools libprotobuf-dev protobuf-compiler && \
	apt-get clean

RUN rm /usr/share/keyrings/kitware-archive-keyring.gpg && apt-get install kitware-archive-keyring

RUN apt-get install -y cmake

RUN cd root && git clone https://github.com/EugenioMoro/protobuf_cpp_examples.git && cd protobuf_cpp_examples && mkdir build && cd build && cmake .. && make

