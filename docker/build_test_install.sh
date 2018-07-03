#!/bin/bash
set -evu

PREFIX=/usr/local

if [ "$OS" == "arch" ] || [ "$OS" == "fedora" ]
then
	PREFIX=/usr
fi

mkdir -p build && cd build

echo "PREFIX: $PREFIX"
cmake -G "Ninja" ..
cmake --build .

echo "Running test suite"
ctest -V --timeout 3

# if [ "$OS" != "osx" ]
# then
#  	make install
# 	ldconfig
# else
# 	sudo make install
# fi

# cd ../src/examples
# g++ -std=c++11 simpleclient.cpp $CLIENT_LIBS -o simpleclient
# g++ -std=c++11 simpleserver.cpp $SERVER_LIBS -o simpleserver

# mkdir -p gen && cd gen
# jsonrpcstub ../spec.json --cpp-server=AbstractStubServer --cpp-client=StubClient
# cd ..
# g++ -std=c++11 stubclient.cpp $CLIENT_LIBS -o stubclient
# g++ -std=c++11 stubserver.cpp $SERVER_LIBS -o stubserver

# test -f simpleclient
# test -f simpleserver
# test -f stubserver
# test -f stubclient

# cd ../../build

# if [ "$OS" != "osx" ]
# then
# 	make uninstall
# else
# 	sudo make uninstall
# fi
