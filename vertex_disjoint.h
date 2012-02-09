#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<math.h>
#include<stdint.h>
#include<string.h>
#include<time.h>
#include<sys/time.h>
#include<sys/resource.h>
#define INF 999999.0
typedef struct node_{
	double *edge_cost;
	int pred;
	int flag; //denotes whether node's distance to src is permanent or can change
	double cost; // length of node to source
	int next_hop;
	//int split_index[2];
}Node;

typedef struct path_edge_{
	int nodes[2];
	double cost;
	struct path_edge_ *next;
}Path;

typedef struct split_node_{
	int node1_index[2];
	double *edge_cost;
}Split;

Split *split;
Node *node,*node1;
Path **path;
FILE *file;
int total_nodes;
int split_cnt;

void initialize_topology();
void print_topology(int);
void initialization();
