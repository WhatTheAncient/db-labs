.PHONY: test build run

test: build
	docker run -it treap ./build/node_test && ./build/treap_test"

test-node: build
	docker run -it treap ./build/node_test

test-treap: build
	docker run -it treap ./build/treap_test

build:
	docker build . --tag "treap"

run:
	docker run -it treap ./main.exe
