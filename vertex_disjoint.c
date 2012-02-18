#include "vertex_disjoint.h"
//int split_cnt;
int main(int argc, char *argv[]){
        int i;
        total_nodes = -1;
	split_cnt = 0;
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
	//printf("Before\n");
	
        modified_dijkstra(src,node,total_nodes); //Source to Dest Path
	//printf("Afer Dijkstra 1\n");
	save_path_1(src,dest,0,node); //Save Path, Revert Edges, -ve cost
//	print_shortest_path(0);
	//printf("Afer Save Path 1\n");

	//Split Nodes.
	split_node(src, dest);
	//printf("After Split Node\n");
	reverse_and_negate(src,dest);
	//printf("After Reverse and Negate\n");
	//printf("Node1 is: \n\n");
	//print_graph(node1,total_nodes + split_cnt);
	reset_topology(node1,total_nodes + split_cnt);
	//printf("After Reset\n");
	if(!modified_dijkstra(src, node1, total_nodes + split_cnt)){ //Run djkstra on the Updated *node Graph   
                print_shortest_path(0);
                printf("No Pair of Shortest path exist. Exiting..\n\n");
                exit(1);
        }
	
	//printf("Afer Dijkstra 2\n");
	coalease_graph(src, dest);
	//printf("After Coalease\n");

//	print_graph(node,total_nodes);
	save_path_1(src,dest,1,node);
	
//	printf("Afer Save Path 2\n");
	//print_graph(node,total_nodes);
	
	print_shortest_path(0);
	print_shortest_path(1);
	
        //print_path(src,dest);   
	find_interlace();
	//printf("After Interlace\n");
	print_shortest_path(0);
	print_shortest_path(1);
	printf("\n");
}       


