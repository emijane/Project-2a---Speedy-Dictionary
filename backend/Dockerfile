FROM ubuntu:22.04

RUN apt-get update && apt-get install -y \
    cmake \
    g++ \
    make

WORKDIR /app

COPY . .

RUN cmake -B build -S . -DCMAKE_BUILD_TYPE=Release
RUN cmake --build build

EXPOSE 8080

CMD ["./build/backend"]