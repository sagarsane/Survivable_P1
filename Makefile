includes = edge_disjoint.h vertex_disjoint.h
objects = edge_util.o edge_disjoint.o vertex_disjoint.o vertex_util.o
sources = edge_util.c edge_disjoint.c vertex_disjoint.o vertex_util.o
out = edge_disjoint vertex_disjoint

all: $(objects) edge vertex

$(objects): $(includes)

edge:
	cc -o edge_disjoint edge_disjoint.o edge_util.o -lm -lpthread

vertex: 
	cc -o vertex_disjoint vertex_disjoint.o vertex_util.o -lm -lpthread
.PHONY: clean 
clean:
	rm -f $(out) $(objects)
