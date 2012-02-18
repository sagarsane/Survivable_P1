includes = edge_disjoint.h vertex_disjoint.h modified_dijkstra.h
objects = edge_util.o edge_disjoint.o vertex_disjoint.o vertex_util.o modified_dijkstra.o
sources = modified_dijkstra.c edge_util.c edge_disjoint.c vertex_disjoint.o vertex_util.o
out = edge_disjoint vertex_disjoint modified_dijkstra

all: $(objects) edge vertex dijkstra

$(objects): $(includes)

dijkstra: 
	cc -o modified_dijkstra modified_dijkstra.o -lm -lpthread

edge:
	cc -o edge_disjoint edge_disjoint.o edge_util.o -lm -lpthread

vertex: 
	cc -o vertex_disjoint vertex_disjoint.o vertex_util.o -lm -lpthread
.PHONY: clean 
clean:
	rm -f $(out) $(objects)
