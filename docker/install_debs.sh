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
    catch
