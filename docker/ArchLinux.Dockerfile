FROM base/archlinux:latest
MAINTAINER Peter Spiess-Knafl <dev@spiessknafl.at>
ENV OS=arch

RUN pacman -Sy --noconfirm \
     expac fakeroot git perl binutils pacutils perl-libwww \
     perl-term-ui perl-json perl-data-dump perl-lwp-protocol-https \
     perl-term-readline-gnu \
     cmake ninja jsoncpp libmicrohttpd curl hiredis redis

RUN useradd user
USER user
RUN cd /tmp && git clone https://aur.archlinux.org/trizen.git && \
     cd /tmp/trizen && makepkg
USER root
RUN pacman -U --noconfirm /tmp/trizen/*.pkg.tar.xz
RUN trizen -S argtable catch2-git
# RUN mkdir /app 
# COPY docker/build_test_install.sh /app
# COPY . /app
# RUN chmod a+x /app/build_test_install.sh
# RUN cd /app && ./build_test_install.sh
