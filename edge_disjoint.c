#include "edge_disjoint.h"

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
	printf("Src: %d, Dest: %d ->\n",src + 1,dest + 1);
	if(src >= total_nodes || dest >= total_nodes || src < 0 || dest < 0){
                printf("Source or Destination out of bounds. Exiting..\n\n");
                exit(1);
        }
	else if(src == dest){
		printf("Source and Destination are Same. Exiting..\n\n");
		exit(1);
	}
	//Edge Disjoint Steps
	//printf("Before\n");
        modified_dijkstra(src); //Source to Dest Path
	//printf("Afer Dijkstra 1\n");
	save_path(src,dest,0); //Save Path, Revert Edges, -ve cost
	//print_shortest_path(0);
	//printf("Afer Save Path 1\n");
	reset_topology();
	//printf("After Reset\n");
	if(!modified_dijkstra(src)){ //Run djkstra on the Updated *node Graph	
		print_shortest_path(0);
		printf("No Pair of Shortest path exist. Exiting..\n\n");
		exit(1);
	}
	//printf("Afer Dijkstra 2\n");
	save_path(src,dest,1);
	//printf("Afer Save Path 2\n");

    	print_shortest_path(0);
        print_shortest_path(1);

        //print_path(src,dest);   
	find_interlace();

	//save path for all paths
	//printf("After Interlace\n");
	print_shortest_path(0);
	print_shortest_path(1);
	printf("\n");
        for(i=0;i<total_nodes;i++)
        {
                free(node[i].edge_cost);
//              free(node[i].saved_cost);
//              free(node[i].next_hop);
        }
        free(node);
}       


