#include "vertex_disjoint.h"

int main(int argc, char *argv[]){
        int i;
        total_nodes = -1;
        int src,dest;
        
        if(argc != 4){
                perror("Incorrect command line arguments\n");
                exit(-1);
        }
        file = fopen(argv[1],"r");
	//printf("Before Init\n");
        initialize_topology();
	//printf("After Init\n");
        src = atoi(argv[2])-1;
        dest = atoi(argv[3])-1;

	//Edge Disjoint Steps
	//printf("Before\n");
        modified_dijkstra(src); //Source to Dest Path
	printf("Afer Dijkstra 1\n");
	save_path_1(src,dest,0); //Save Path, Revert Edges, -ve cost
	print_shortest_path(0);
	printf("Afer Save Path 1\n");

	//Split Nodes.
	split_node(src, dest);

//	reset_topology();
//	printf("After Reset\n");
//	modified_dijkstra(src); //Run djkstra on the Updated *node Graph	
//	printf("Afer Dijkstra 2\n");
//	save_path(src,dest,1);
//	printf("Afer Save Path 2\n");
//	print_shortest_path(1);

        //print_path(src,dest);   
//	find_interlace();
//	printf("After Interlace\n");
//	print_shortest_path(0);
//	print_shortest_path(1);
        for(i=0;i<total_nodes;i++)
        {
                free(node[i].edge_cost);
//              free(node[i].saved_cost);
//              free(node[i].next_hop);
        }
        free(node);
}       


