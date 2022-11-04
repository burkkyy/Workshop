CC = g++
CFLAGS = -std=c++17 -O2 -I include/ impl/*.cpp
LDFLAGS = -lglfw -lvulkan -ldl -lpthread -lX11 -lXxf86vm -lXrandr -lXi

bin/a.out: main.cpp impl/*.cpp include/*.hpp
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) main.cpp $(LDFLAGS) -o $@

shaders/first_shader.frag.spv: shaders/first_shader.frag
	glslc $^ -o $@

shaders/first_shader.vert.spv: shaders/first_shader.vert
	glslc $^ -o $@


.PHONY: all test clean
all: bin/a.out shaders/first_shader.frag.spv shaders/first_shader.vert.spv

test: all
	./bin/a.out

clean:
	rm -rf bin
