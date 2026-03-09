FROM ubuntu:24.04 AS builder

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y \
    clang \
    clang-format \
    clang-tidy \
    cmake \
    make \
    libboost-all-dev \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app

COPY . .

RUN mkdir build && cd build && \
    cmake -DUSE_ASAN=OFF -DUSE_TSAN=OFF .. && \
    make -j$(nproc)

FROM ubuntu:24.04

RUN apt-get update && apt-get install -y libboost-thread1.83.0 && rm -rf /var/lib/apt/lists/*

WORKDIR /root/

COPY --from=builder /app/build/Arena/arena_bench .

CMD ["./arena_bench"]
