#include "modified_dijkstra.h"

void save_path(int src,int dest){
	int i,j,cost=0;
	
	i = dest;	

	while(i!=src)
	{
		j = node[i].pred;
		node[j].next_hop = i;
		cost+=node[j].edge_cost[i];
		i = j;
	}
	node[i].cost = cost;
	
/*
	for(i=0;i<total_nodes;i++)
	{
		//printf("Pred for %d is: %d\n",i+1,node[i].pred+1);
		if(i!=current_node - 1){
			//node[current_node - 1].saved_cost
			k = i;
			j = node[i].pred;
		
			while(j!=current_node-1){
				k = j;
				j = node[j].pred;
			}	
			node[current_node - 1].next_hop[i] = k;
			node[current_node - 1].saved_cost[i] = node[i].cost;	
		}
		else{
			node[current_node - 1].next_hop[i] = i;
			node[current_node - 1].saved_cost[i] = 0.0f;
		}	
	}
*/	
}


void reset_topology(){
	int i;
	for(i=0;i<total_nodes;i++){
		node[i].flag = 0;
		node[i].pred = i;
	}
	
}

void print_path(int src, int dest)
{
	int i=src;
	printf("The shortest path between %d and %d is:\n%d",src+1,dest+1,src+1);
	while(i!=dest)
	{
		printf("\t%d",node[i].next_hop+1);
		i = node[i].next_hop;
	}
	printf("\nThe cost of the path is: %.2lf\n\n",node[src].cost);
}

int main(int argc, char *argv[]){
	int i;
	total_nodes = -1;
	int src,dest;
	
	if(argc != 4){
		perror("Incorrect command line arguments\n");
		exit(-1);
	}
	file = fopen(argv[1],"r");
	initialize_topology();
	src = atoi(argv[2])-1;
	dest = atoi(argv[3])-1;
//	for(i=0;i<total_nodes;i++)
//	{
	modified_dijkstra(src);
	save_path(src,dest);
//	reset_topology();
//		printf("Time taken for source Node %d is : %.15lf microseconds\n",i+1,(double)(end.tv_usec-start.tv_usec + (end.tv_sec-start.tv_sec)));


//	}

	print_path(src,dest);	

	for(i=0;i<total_nodes;i++)
	{
		free(node[i].edge_cost);
//		free(node[i].saved_cost);
//		free(node[i].next_hop);
	}
	free(node);
}	

void initialize_topology(){
	int i,j;
	if(!file){
		perror("Cannot Open File\n");
		exit(-1);
	}
	fseek(file,0,SEEK_SET);	
	fscanf(file,"%d\n",&total_nodes);
//	printf("%d\n",total_nodes);

	node = (Node *)malloc(sizeof(Node)*total_nodes);

	for(i = 0;i< total_nodes;i++){ //initialize node structure
		node[i].edge_cost = (double *)malloc(sizeof(double) * total_nodes);
		//node[i].next_hop = (int *)malloc(sizeof(int) * total_nodes);
		//node[i].saved_cost = (double *)malloc(sizeof(double) * total_nodes);
		for(j = 0;j < total_nodes;j++)
			node[i].edge_cost[j] = INF;	
		node[i].pred = i;
		node[i].flag=0; //not yet permanent
	//	node[i].cost=INF;//start all nodes with infinite cost
	}
	

	int temp_i = -1,temp_j = -1;
	double temp_cost = 0.0f;
	while(fscanf(file,"%d %d %lf",&temp_i,&temp_j,&temp_cost)!= EOF){
		if(temp_cost<0)
			node[temp_i-1].edge_cost[temp_j-1] = INF;
		else
			node[temp_i-1].edge_cost[temp_j-1] = temp_cost;
		node[temp_j-1].edge_cost[temp_i-1] = temp_cost;
	}
}


void initialization()
{
	int k = 0;
	int i;	
	for(i=0;i<total_nodes;i++)
        {
                if(i!=k)
                {
                        if(node[k].edge_cost[i]!=INF){
                                //printf("D[%d] = C(%d,%d) = %lf\n",i+1,k+1,i+1,node[k].edge_cost[i]);
                                node[i].cost = node[k].edge_cost[i]; //initialize D(v) = c(u,v)
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
        }


}
/*void print_topology(int src)
{
	int k;
	printf("\nRouting table of node %d -->\n\n",src);
        printf("  Destination\t  Next Hop \tCost to Destination\n");
        printf("---------------------------------------------------\n");

        for(k = 0;k < total_nodes; k++){
                       // if(node[i].edge_cost[k]!=0)
                        //if(node[k].cost!=999999)
                        printf("  %d\t\t  %d   \t\t\t   %.2lf\n",k+1,node[src-1].next_hop[k]+1,node[src-1].saved_cost[k]);
                        //else
                        //printf("  %d\t  %d\tINFINITY\n",src,k+1);
        }

}*/

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

int modified_dijkstra(int src){
	
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

