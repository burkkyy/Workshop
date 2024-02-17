CC=gcc

bin/server.bin: src/server.cpp
	mkdir -p $(dir $@) && \
	$(CC) $^ -o $@

bin/client.bin: src/client.cpp
	mkdir -p $(dir $@) && \
	$(CC) $^ -o $@

.PHONY: server
server: bin/server.bin
	./bin/server.bin

.PHONY: client
client: bin/client.bin
	./bin/client.bin

