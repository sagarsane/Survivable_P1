includes = modified_dijkstra.h
objects = modified_dijkstra.o edge_disjoint.o
sources = modified_dijkstra.c edge_disjoint.c
out = modified_dijkstra edge_disjoint

all: $(objects) edge

$(objects): $(includes)

dijkstra: 
	cc -o modified_dijkstra modified_dijkstra.o -lm -lpthread

edge:
	cc -o edge_disjoint edge_disjoint.o modified_dijkstra.o -lm -lpthread
.PHONY: clean 
clean:
	rm -f $(out) $(objects)
