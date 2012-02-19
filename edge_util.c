#include "edge_disjoint.h"


void print_shortest_path(int index){
	int i;
	double cost = 0.0f;
	Path *p;
	p = path[index];
	printf("Path %d is:",index+1);
	while(p!=NULL){
		if(p->next != NULL)
			printf("\t%d",p->nodes[0]+1);
		else
			printf("\t%d\t%d",p->nodes[0]+1,p->nodes[1]+1);
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
        int pathflag=0;
        Path *p,*q,*pslow,*qslow;
        Path *pstart,*pend,*qstart,*qend;
	pslow = path[0];
//	qslow = path[1];
	p = pslow->next;
//	q = qslow->next;
	while(p!=NULL){
		qslow = path[1];
		q = qslow->next;
		while(q!=NULL){
			if((p->nodes[0] == q->nodes[0] && p->nodes[1] == q->nodes[1]) || (p->nodes[0] == q->nodes[1] && p->nodes[1] == q->nodes[0])){ 
                               flag=1;
                                //interlace found
                                if(pathflag==0){
                                        pathflag = 1;
                                        pstart = pslow;
                                        qend = q;
                                }
                                pend = p;
                                qstart = qslow;
                                //printf("Interlace Found for Edges: %d-%d \t %d-%d\n",p->nodes[0]+1,p->nodes[1]+1,q->nodes[0]+1,q->nodes[1]+1);
                                break;
                                //pslow->next = q->next;
                                //qslow->next = p->next;
                                //q = qslow->next;
                                //p = pslow->next;
                        }
                        qslow = q;
                        q = q->next;
                }

                if(flag==0 && pathflag == 1){
                        pathflag=0;
			//printf("manipulating pointers\n");
                        pstart->next = qend->next;
                        qstart->next = pend->next;
                        pslow = pstart;
                        p = pstart->next;
                }
                else{   //interlace found
                        pslow = p;
                        p = p->next;
                }

				//interlace found
/*				printf("Interlace Found for Edges: %d-%d \t %d-%d\n",p->nodes[0]+1,p->nodes[1]+1,q->nodes[0]+1,q->nodes[1]+1);
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
		}*/

		flag = 0;
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
	//print_path(src,dest);

	Path *temp,*p;
	int next_hop = node[src].next_hop;
	temp = malloc(sizeof(Path));
	temp->nodes[0] = src;
	temp->nodes[1] = next_hop;
	temp->cost = node[src].edge_cost[next_hop];
	//temp->cost = node[src].cost;
	path[flag] = temp; //head
	if(flag == 0){
		  //    temp->cost = node[src].edge_cost[next_hop];

		node[src].edge_cost[next_hop] = INF;
		if(node[next_hop].edge_cost[src]!=INF)
			node[next_hop].edge_cost[src] = -node[next_hop].edge_cost[src];

	}
	else{  //revert Edges
		if(node[next_hop].edge_cost[src]!=INF)
			node[next_hop].edge_cost[src] = -node[next_hop].edge_cost[src];
		node[src].edge_cost[next_hop] = node[next_hop].edge_cost[src];
		 //     temp->cost = node[src].edge_cost[next_hop];

	}

	//j = src;
	i = next_hop;
	p = temp;
	while(i!=dest){
		next_hop = node[i].next_hop;
		temp = malloc(sizeof(Path));
		temp->nodes[0] = i;
		temp->nodes[1] = next_hop;
		temp->cost = node[i].edge_cost[next_hop];
		//temp->cost = node[i].cost;
		temp->next = NULL;
		if(flag == 0){
	        //      temp->cost = node[i].edge_cost[next_hop];
                	node[i].edge_cost[next_hop] = INF;
			 if(node[next_hop].edge_cost[i]!=INF)
		                node[next_hop].edge_cost[i] = -node[next_hop].edge_cost[i];
		}
	        else{  //revert Edges
			 if(node[next_hop].edge_cost[i]!=INF)
	                	node[next_hop].edge_cost[i] = -node[next_hop].edge_cost[i];
        	        node[i].edge_cost[next_hop] = node[next_hop].edge_cost[i];
	          //    temp->cost = node[i].edge_cost[next_hop];

	        }
		
		p->next = temp;
		p = p->next;
		i = next_hop;
	}


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
	//printf("Before Initializing Path\n");	
	path = (Path **)malloc(sizeof(Path *) * 2);
	//printf("Path Initialized\n");
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
	int flag = 0;
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
		flag = 0;
                //Find next min
                for(i=0;i<total_nodes;i++)
                {
                        if(node[i].flag ==0 && node[i].cost < min)
                        {
                                min = node[i].cost;
                                k=i;
				flag = 1;
                        }
                }
		if( flag == 0  ) //cannot move ahead to find next minimum from given 'k' .. no shortest path will exist
		{
			return 0;	
		}
                node[k].flag=1;
                for(i=0;i<total_nodes;i++)
                {
			//change - if condition is only if i is not neighbor of k 
                        if(node[k].edge_cost[i]!=INF)
                        {
                                if(node[k].cost + node[k].edge_cost[i] < node[i].cost-0.00001)  //update predecessor and cost to src node
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
	return 1;
}

