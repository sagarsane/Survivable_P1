includes = modified_dijkstra.h vertex_disjoint.h
objects = modified_dijkstra.o edge_disjoint.o vertex_disjoint.o vertex_util.o
sources = modified_dijkstra.c edge_disjoint.c vertex_disjoint.o vertex_util.o
out = modified_dijkstra edge_disjoint vertex_disjoint

all: $(objects) edge vertex

$(objects): $(includes)

dijkstra: 
	cc -o modified_dijkstra modified_dijkstra.o -lm -lpthread

edge:
	cc -o edge_disjoint edge_disjoint.o modified_dijkstra.o -lm -lpthread

vertex: 
	cc -o vertex_disjoint vertex_disjoint.o vertex_util.o -lm -lpthread
.PHONY: clean 
clean:
	rm -f $(out) $(objects)
