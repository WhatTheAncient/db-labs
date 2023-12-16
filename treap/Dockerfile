FROM alpine:3.17.0 AS build

WORKDIR /app

RUN apk update && apk add --no-cache git g++ make cmake

COPY ./ ./

RUN cmake -S . -B build && cmake --build build

RUN g++ main.cpp -o main.exe -std=c++20
