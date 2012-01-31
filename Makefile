includes = modified_dijkstra.h
objects = modified_dijkstra.o
sources = modified_dijkstra.c
out = modified_dijkstra

all: $(objects) dijkstra

$(objects): $(includes)

dijkstra: 
	cc -o modified_dijkstra modified_dijkstra.o -lm -lpthread

.PHONY: clean 
clean:
	rm -f $(out) $(objects)
