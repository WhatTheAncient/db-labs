.PHONY: test build run

test: build
	docker run -it treap ./build/node_test && ./build/treap_test"

build:
	docker build . --tag "treap"

run:
	docker run -it treap ./main.exe

local-run: local-build
	./main.exe

local-test:
	cmake -S . -B build && cmake --build build && ./build/tests

local-build: 
	g++ main.cpp -o main.exe -std=c++20
