CC = g++
CFLAGS = -std=c++17 -O2 -I include/ impl/*.cpp
LDFLAGS = -lglfw -lvulkan -ldl -lpthread -lX11 -lXxf86vm -lXrandr -lXi

bin/a.out: main.cpp impl/*.cpp include/*.hpp
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) main.cpp $(LDFLAGS) -o $@

.PHONY: test clean
test: bin/a.out
	./bin/a.out

clean:
	rm -rf bin
