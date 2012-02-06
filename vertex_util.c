#include "vertex_disjoint.h"


void split_node(int src, int dest){
	int i,j,split_cnt = 0;
	int split_i = 0;


	i = src;
	//change .. find the count for no of nodes to be split
	while(i != dest){
		split_cnt++;
		i = node[i].next_hop;
	}

	
    	//first create node1!!
        node1 = (Node *)malloc(sizeof(Node)*(total_nodes + split_cnt));
	
	//initialize *split structure using the count
	split = (Split *)malloc(sizeof(Split) * split_cnt);
        for(i = 0;i< total_nodes;i++){ //initialize node structure
                split[i].edge_cost = (double *)malloc(sizeof(double) * total_nodes + split_cnt);
                for(j = 0;j < total_nodes + split_cnt;j++)
                        split[i].edge_cost[j] = INF;
        }
	




	i = src;
	//fill in the *split structure
	while(i != dest){
		i = node[i].next_hop;
		
	}

}

void print_shortest_path(int index){
	int i;
	double cost = 0.0f;
	Path *p;
	p = path[index];
	printf("\nPath %d is:",index+1);
	while(p!=NULL){
		printf("\t%d-%d",p->nodes[0]+1,p->nodes[1]+1);
		cost += p->cost;
		p = p->next;
	}
	printf("\nIts Cost is: %.2f\n",cost);
}


void print_path(int src, int dest)
{
        int i=src;
        printf("The shortest path between %d and %d is:\n%d",src+1,dest+1,src+1);
        while(i!=dest)
        {
                printf("\t%d-%d = %.2f",i+1,node[i].next_hop+1,node[i].edge_cost[node[i].next_hop]);
                i = node[i].next_hop;
        }
        printf("\nThe cost of the path is: %.2lf\n\n",node[src].cost);
}

void find_interlace(){
	
	int i,j,flag = 0;
	Path *p,*q,*pslow,*qslow;
	pslow = path[0];
//	qslow = path[1];
	p = pslow->next;
//	q = qslow->next;
	while(p!=NULL){
		qslow = path[1];
		q = qslow->next;
		while(q!=NULL){
			if((p->nodes[0] == q->nodes[0] && p->nodes[1] == q->nodes[1]) || (p->nodes[0] == q->nodes[1] && p->nodes[1] == q->nodes[0])){ 
				//interlace found
				printf("Interlace Found for Edges: %d-%d \t %d-%d\n",p->nodes[0]+1,p->nodes[1]+1,q->nodes[0]+1,q->nodes[1]+1);
				pslow->next = q->next;
				qslow->next = p->next;
				q = qslow->next;
				p = pslow->next;
				flag = 1;
			}
			else{
				qslow = q;
				q = q->next;
			}
		}
		
		if(!flag){
			pslow = p;
			p = p->next;
		}
		flag = 0;

	}

}


void save_path_1(int src,int dest,int flag){
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

        //original function to print path using node structure
        print_path(src,dest);

        Path *temp,*p;
        int next_hop = node[src].next_hop;
        temp = malloc(sizeof(Path));
        temp->nodes[0] = src;
        temp->nodes[1] = next_hop;
        temp->cost = node[src].edge_cost[next_hop];
        path[flag] = temp; //head
        if(flag == 0){
               printf("First in Save Path\n");
                node[next_hop].edge_cost[src] = INF;

        }
        else{  //revert Edges
                printf("Second in Save Path\n");
                node[next_hop].edge_cost[src] = node[src].edge_cost[next_hop];

        }

        i = next_hop;
        p = temp;
        while(i!=dest){
                next_hop = node[i].next_hop;
                temp = malloc(sizeof(Path));
                temp->nodes[0] = i;
                temp->nodes[1] = next_hop;
                temp->cost = node[i].edge_cost[next_hop];
                temp->next = NULL;
                if(flag == 0){
                        node[next_hop].edge_cost[i] = INF;
                }
                else{  //revert Edges
                        node[next_hop].edge_cost[i] = node[i].edge_cost[next_hop];
                }

                p->next = temp;
                p = p->next;
                //j = i;
                i = next_hop;
        }
                          
}


void save_path(int src,int dest,int flag){
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

	//original function to print path using node structure
	print_path(src,dest);

	Path *temp,*p;
	int next_hop = node[src].next_hop;
	temp = malloc(sizeof(Path));
	temp->nodes[0] = src;
	temp->nodes[1] = next_hop;
	temp->cost = node[src].edge_cost[next_hop];
	path[flag] = temp; //head
	if(flag == 0){
		printf("First in Save Path\n");
		node[src].edge_cost[next_hop] = INF;
		if(node[next_hop].edge_cost[src]!=INF)
			node[next_hop].edge_cost[src] = -node[next_hop].edge_cost[src];
		printf("For %d-%d Zeroed Cost: %.2f  -- Negated Cost: %.2f\n",src+1,next_hop+1,node[src].edge_cost[next_hop],node[next_hop].edge_cost[src]);

	}
	else{  //revert Edges
		printf("Second in Save Path\n");
		if(node[next_hop].edge_cost[src]!=INF)
			node[next_hop].edge_cost[src] = -node[next_hop].edge_cost[src];
		node[src].edge_cost[next_hop] = node[next_hop].edge_cost[src];
		printf("For %d-%d Original Cost: %.2f  -- Original Cost: %.2f\n",src+1,next_hop+1,node[src].edge_cost[next_hop],node[next_hop].edge_cost[src]);

	}

	//j = src;
	i = next_hop;
	p = temp;
	//while(node[i].next_hop!=dest){
	while(i!=dest){
		//printf("Here\n");
		next_hop = node[i].next_hop;
		temp = malloc(sizeof(Path));
		temp->nodes[0] = i;
		temp->nodes[1] = next_hop;
		temp->cost = node[i].edge_cost[next_hop];
		temp->next = NULL;
		if(flag == 0){
                	node[i].edge_cost[next_hop] = INF;
	                node[next_hop].edge_cost[i] = -node[next_hop].edge_cost[i];
        		printf("For %d-%d Zeroed Cost: %.2f  -- Negated Cost: %.2f\n",i+1,next_hop+1,node[i].edge_cost[next_hop],node[next_hop].edge_cost[i]);
		}
	        else{  //revert Edges
                	node[next_hop].edge_cost[i] = -node[next_hop].edge_cost[i];
        	        node[i].edge_cost[next_hop] = node[next_hop].edge_cost[i];
			printf("For %d-%d Original Cost: %.2f  -- Original Cost: %.2f\n",i+1,next_hop+1,node[i].edge_cost[next_hop],node[next_hop].edge_cost[i]);

	        }
		
		p->next = temp;
		p = p->next;
		//j = i;
		i = next_hop;
	}


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

	//change
	printf("Before Initializing Path\n");	
	path = (Path **)malloc(sizeof(Path *) * 2);
	printf("Path Initialized\n");
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
	

	int temp_i = -1,temp_j = -1,faltu = -1;
	double temp_cost = 0.0f;
	while(fscanf(file,"%d %d %lf %d",&temp_i,&temp_j,&temp_cost,&faltu)!= EOF){
		//if(temp_cost<0)
		//	node[temp_i-1].edge_cost[temp_j-1] = INF;
		//else
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

