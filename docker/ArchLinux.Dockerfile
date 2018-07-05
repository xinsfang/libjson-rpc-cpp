FROM base/archlinux:latest
MAINTAINER Peter Spiess-Knafl <dev@spiessknafl.at>
ENV OS=arch

RUN pacman -Sy --noconfirm git cmake ninja gcc jsoncpp libmicrohttpd curl hiredis redis unzip perl
RUN git clone https://github.com/Microsoft/vcpkg.git && cd vcpkg && ./bootstrap-vcpkg.sh
RUN mkdir -p /usr/local/bin && ln -sf /usr/bin/core_perl/shasum /usr/local/bin/shasum
RUN cd vcpkg && ./vcpkg install argtable2 catch2

RUN mkdir /app 
COPY docker/build_test_install.sh /app
COPY . /app
RUN chmod a+x /app/build_test_install.sh
RUN cd /app && ./build_test_install.sh
