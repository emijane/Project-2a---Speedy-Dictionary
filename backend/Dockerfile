FROM ubuntu:22.04

RUN apt-get update && apt-get install -y \
    cmake \
    g++ \
    make

WORKDIR /app

COPY . .

RUN cmake -B build -S .
RUN cmake --build build

EXPOSE 8080

CMD ["./cmake-build-release/release/backend"]