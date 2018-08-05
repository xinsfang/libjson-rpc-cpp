#!/bin/bash
apt-get update -y 
apt-get install -y \
    build-essential \
    cmake \
    ninja-build \
    libjsoncpp-dev \
    libargtable2-dev \
    libcurl4-openssl-dev \
    libmicrohttpd-dev \
    libhiredis-dev \
    redis-server \
    catch \
    wget

mkdir -p /usr/local/include/nlohmann
wget https://raw.githubusercontent.com/nlohmann/json/master/single_include/nlohmann/json.hpp -O /usr/local/include/nlohmann/json.hpp