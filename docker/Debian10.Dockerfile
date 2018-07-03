FROM debian:buster
MAINTAINER Peter Spiess-Knafl <dev@spiessknafl.at>
ENV OS=debian10

COPY docker/install_debs.sh /install_debs.sh
RUN chmod a+x /install_debs.sh
RUN /install_debs.sh

RUN mkdir /app
COPY docker/build_test_install.sh /app
COPY . /app
RUN chmod a+x /app/build_test_install.sh
RUN cd /app && ./build_test_install.sh
