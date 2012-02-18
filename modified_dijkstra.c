#include "modified_dijkstra.h"

void save_path(int src, int dest){
	int i;
	int j = 0,k;
	      i = dest;
	double cost = 0.0f;
        while(i!=src)
        {
                j = node[i].pred;
                node[j].next_hop = i;
                cost+=node[j].edge_cost[i];
                i = j;
        }
        node[i].cost = cost;

	
}


void print_path(int src, int dest)
{
        int i=src;
        printf("Src: %d, Dest: %d ->\n",src+1,dest+1);
	printf("%d\t",i+1);
        while(i!=dest)
        {
                printf("%d\t",node[i].next_hop+1);
                i = node[i].next_hop;
        }
        printf("\nIts Cost is: %.2lf\n\n",node[src].cost);
}


void reset_topology(){
	int i;
	for(i=0;i<total_nodes;i++){
		node[i].flag = 0;
		node[i].pred = i;
	}
	
}



void initialize_topology(){
	int i,j;
	if(!file){
		perror("Cannot Open File\n");
		exit(-1);
	}
	fseek(file,0,SEEK_SET);	
	fscanf(file,"%d\n",&total_nodes);
	//printf("%d\n",total_nodes);

	node = (Node *)malloc(sizeof(Node)*total_nodes);

	for(i = 0;i< total_nodes;i++){ //initialize node structure
		node[i].edge_cost = (double *)malloc(sizeof(double) * total_nodes);
		for(j = 0;j < total_nodes;j++)
			node[i].edge_cost[j] = INF;	
		node[i].pred = i;
		node[i].flag=0; //not yet permanent
	//	node[i].cost=INF;//start all nodes with infinite cost
	}
	

	int temp_i = -1,temp_j = -1, faltu = -1;
	double temp_cost = 0.0f; 
	while(fscanf(file,"%d %d %lf %d",&temp_i,&temp_j,&temp_cost,&faltu)!= EOF){
		node[temp_i-1].edge_cost[temp_j-1] = temp_cost;
		node[temp_j-1].edge_cost[temp_i-1] = temp_cost;
	}
}

int all_flags_set()
{
	int i;
	for(i=0;i<total_nodes;i++)
	{	
		if(node[i].flag==0)
			return 0;
	}
	return 1;
}

void modified_dijkstra(int src, char flag){
	
	int i,k;
	double min;

	k=src;
        //node[src-1].cost=0.0f;
        node[k].flag=1;

	for(i=0;i<total_nodes;i++)
	{
		if(i!=k)
		{
			if(node[k].edge_cost[i]!=INF){
				//printf("D[%d] = C(%d,%d) = %lf\n",i+1,k+1,i+1,node[k].edge_cost[i]);
				node[i].cost = node[k].edge_cost[i]; //initialize D(v) = c(u,v)
				node[i].pred = k;
			}
			else{
				//printf("D[%d] = INFININTY\n",i+1);
				node[i].cost = INF;
			}
		}
		else{
			node[i].cost = 0.0f;
			//printf("D[%d] = 0\n",i+1);
		}
	//	printf("i: %d\n",i);
	}
        do
        {
	        min=INF;
                //Find next min
                for(i=0;i<total_nodes;i++)
                {
                        if(node[i].flag ==0 && node[i].cost < min)
                        {
                                min = node[i].cost;
                                k=i;
                        }
                }
                node[k].flag=1;
                for(i=0;i<total_nodes;i++)
                {
			//change - if condition is only if i is not neighbor of k 
                        if(node[k].edge_cost[i]!=INF)
                        {
                                if(node[k].cost + node[k].edge_cost[i] < node[i].cost)  //update predecessor and cost to src node
				{
					//printf("Setting Pred for %d to %d\n", i+1,k+1);
                                        node[i].pred = k;
                                        node[i].cost = node[k].cost+node[k].edge_cost[i];
					//change
					node[k].flag = 0; // S = S U {i}
                                }
                        }
			

                }

        }while(!all_flags_set());
	
}



int main(int argc, char *argv[]){
        int i, src, dest;
        total_nodes = -1;

        if(argc != 4){
                perror("Incorrect command line arguments\n");
                exit(-1);
        }
        file = fopen(argv[1],"r");
        initialize_topology();
        src = atoi(argv[2])-1;
        dest = atoi(argv[3])-1;
	//printf("1\n");
        modified_dijkstra(src,0);
	//printf("2\n");
        save_path(src,dest);
	//printf("3\n");
        print_path(src, dest);
        //reset_topology();
//              printf("Time taken for source Node %d is : %.15lf microseconds\n",i+1,(double)(end.tv_usec-start.tv_usec + (end.tv_sec-start.tv_sec)));






        for(i=0;i<total_nodes;i++)
        {
                free(node[i].edge_cost);
        }
        free(node);
}



