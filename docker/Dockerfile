FROM ubuntu:22.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && \
    apt-get install -y \
    build-essential \
    valgrind \
    linux-tools-common \
    linux-tools-generic \
    time \
    git \
    nano \
    cmake \
    gdb \
    && apt-get clean

# Create a working directory
WORKDIR /app


COPY . .


RUN g++ -O2 -std=c++17 -o benchmark main.cpp


CMD ["./benchmark"]