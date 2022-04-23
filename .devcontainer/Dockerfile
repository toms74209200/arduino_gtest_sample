FROM debian:bullseye

RUN apt-get update && apt-get install -y \
    git \
    make \
    cmake \
    curl \
    clang \
    clang-format \
    clang-tidy \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*

# install arduino-cli
RUN curl -fsSL https://raw.githubusercontent.com/arduino/arduino-cli/master/install.sh | BINDIR=/usr/local/bin sh -s 0.21.1

COPY arduino-cli.yaml /root/.arduino15/arduino-cli.yaml

RUN arduino-cli core update-index \
    && arduino-cli core install arduino:avr

# install GoogleTest
RUN git clone https://github.com/google/googletest.git -b release-1.11.0 \
    && cd googletest \
    && mkdir build \
    && cd build \
    && cmake .. \
    && make \
    && make install