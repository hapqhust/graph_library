#include "directedjrb.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define Infinity 999999
typedef struct _Graph{
	JRB vertices;
	JRB outedges;
	JRB inedges;
} *Graph;
typedef struct 
{
	Jval vertex;
	int dist;
} Piqueue;
typedef struct Nodequeue
{
    JRB data;
    struct Nodequeue *next;
} typenode;
typedef struct queuetype
{
    typenode *front, *rear;
} *Queuetype;
typenode *curqueue;
void init(Queuetype *queue)
{
    *queue = (Queuetype)malloc(sizeof(struct queuetype));
    (*queue)->front = (*queue)->rear = NULL;
}
int isEmpty(Queuetype queue)
{
    return (queue->front == NULL);
}
int SizeQueue(Queuetype queue)
{
    int count = 0;
    for (typenode *cur = queue->front; cur != NULL ; cur = cur->next) count++;
    return count;
}
typenode *Front_is(Queuetype queue)
{
    return (queue->front);
}
void Enqueue(Queuetype *queue, JRB x)
{
    //if(isFull(*queue, SizeQueue(*queue))) return;
    typenode *newnode = (typenode*)malloc(sizeof(typenode));
    newnode->data = x;
    newnode->next = NULL;
    if(isEmpty(*queue))
    {
        (*queue)->front = newnode;
        (*queue)->rear = (*queue)->front;
    }
    else
    {
        (*queue)->rear->next = newnode;
        (*queue)->rear = newnode;
    }
    
}
JRB Dequeue(Queuetype *queue)
{
    JRB Key;
    if(isEmpty(*queue)) return NULL;
    else
    {
        typenode *del;
        del = (*queue)->front;
        Key = del->data;
        (*queue)->front = (*queue)->front->next;
        free(del);
        return Key;
    }
    
}
void DestroyQueue(Queuetype q)
{
	while(!isEmpty(q)) Dequeue(&q);
	free(q);
}
Graph createGraph();
void addVertex_int(Graph graph, int id);
void addVertex_str(Graph graph, char *id);
void addEdge_int(Graph graph, int v1, int v2, int w);
void addEdge_str(Graph graph, char* v1, char* v2, int w);
JRB getoutedges_int (Graph graph, int v);
JRB getinedges_int (Graph graph, int v);
JRB getoutedges_str (Graph graph, char* v);
JRB getinedges_str (Graph graph, char* v);
void DropGraph(Graph graph);
int visitbool(Graph graph, char *s);
void visiting(Graph graph, char *s);
void StableMatching(JRB Boy, JRB Girl);
void DFStraversal(Graph graph, int start, int stop);
void DFStraversal_Post(Graph graph);
void DFS_Post(Graph graph, int start, int stop);
void DFS(Graph graph, int start, int stop);
void BFS(Graph graph, int start, int stop);
void DFS_R(Graph graph, int start,int stop);
void DFStraversal_R(Graph graph);
void StrongComponent(Graph g);
int Dijkstra_int(Graph graph, int u, int end);
Graph createGraph(){
  Graph g = (Graph)malloc(sizeof(struct _Graph));
  if(g==NULL) {
	  printf("NULL, can not allocate mem, abort...\n");
	  return NULL;
  }
  g->vertices = make_jrb();
  g->outedges = make_jrb();
  g->inedges = make_jrb();
  return g;
}
void addVertex_int(Graph graph, int id)
{
	if(jrb_find_int(graph->vertices, id) !=NULL) return;
	jrb_insert_int(graph->vertices, id, new_jval_v(NULL));
}
void addVertex_str(Graph graph, char *id)
{
	if(jrb_find_str(graph->vertices, id) !=NULL) return;
	jrb_insert_str(graph->vertices, id, new_jval_v(NULL));
}
int havenoutedge_int(Graph g, int v1, int v2)
{
	JRB node1 = jrb_find_int(g->outedges, v1);
	if(node1 == NULL) return 0;
	JRB tree1 = (JRB) jval_v(node1->val);
	//f(!tree1) return 0;
	/*JRB node2 = jrb_find_str(g, v2);
	if(node2== NULL) return 0;
	JRB tree2 = (JRB) jval_v(node2->val);*/
	//int total = 0;   
	jrb_traverse(node1, tree1)
	{
		if(v2 == jval_i(node1->key)) return 1;
	}    
	return 0;  
}
int haveninedge_int(Graph g, int v1, int v2)
{
	JRB node1 = jrb_find_int(g->inedges, v1);
	if(node1 == NULL) return 0;
	JRB tree1 = (JRB) jval_v(node1->val);
	//if(!tree1) return 0;
	/*JRB node2 = jrb_find_str(g, v2);
	if(node2== NULL) return 0;
	JRB tree2 = (JRB) jval_v(node2->val);*/
	//int total = 0;   
	jrb_traverse(node1, tree1)
	{
		if(v2 == jval_i(node1->key)) return 1;
	}    
	return 0;  
}
int havenoutedge_str(Graph g, char *v1, char* v2)
{
	JRB node1 = jrb_find_str(g->outedges, v1);
	if(node1 == NULL) return 0;
	JRB tree1 = (JRB) jval_v(node1->val);
	//f(!tree1) return 0;
	/*JRB node2 = jrb_find_str(g, v2);
	if(node2== NULL) return 0;
	JRB tree2 = (JRB) jval_v(node2->val);*/
	//int total = 0;   
	jrb_traverse(node1, tree1)
	{
		if(strcasecmp(v2, jval_s(node1->key)) == 0) return 1;
	}    
	return 0;  
}
int haveninedge_str(Graph g, char *v1, char* v2)
{
	JRB node1 = jrb_find_str(g->inedges, v1);
	if(node1 == NULL) return 0;
	JRB tree1 = (JRB) jval_v(node1->val);
	//if(!tree1) return 0;
	/*JRB node2 = jrb_find_str(g, v2);
	if(node2== NULL) return 0;
	JRB tree2 = (JRB) jval_v(node2->val);*/
	//int total = 0;   
	jrb_traverse(node1, tree1)
	{
		if(strcasecmp(v2, jval_s(node1->key)) == 0) return 1;
	}    
	return 0;  
}
void addEdge_str(Graph graph, char* v1, char* v2, int w)
{

	if(havenoutedge_str(graph, v1, v2) == 1) return;
	// do thi vo huong nen can co (v1 v2) va (v2 v1)
	// them canh v1 v2
	// check xem da co dinh tren cay chua
	JRB bn = jrb_find_str(graph->outedges, v1);
	if(bn==NULL) // neu chua co thi them vao
	{		
		JRB tree = make_jrb(); 
		jrb_insert_str(tree, strdup(v2), new_jval_i(w));
		jrb_insert_str(graph->outedges, strdup(v1), new_jval_v(tree));
	}
	else // dinh v1 da co tren cay
	{
		//node = jrb_find_int(g, v1);
		// them canh v1->v2 xuôi
		JRB tree = (JRB)jval_v(bn->val);
		jrb_insert_str(tree, strdup(v2), new_jval_i(w));			
	}
    if(haveninedge_str(graph, v2, v1) == 1) return;
    bn = jrb_find_str(graph->inedges, v2);
	if(bn==NULL) // neu chua co thi them vao
	{		
		JRB tree = make_jrb(); 
		jrb_insert_str(tree, strdup(v1), new_jval_i(w));
		jrb_insert_str(graph->inedges, strdup(v2), new_jval_v(tree));
	}
	else // dinh v2 da co tren cay
	{
		//node = jrb_find_int(g, v1);
		// them canh v1->v2 chiều ngc
		JRB tree = (JRB)jval_v(bn->val);
		jrb_insert_str(tree, strdup(v1), new_jval_i(w));			
	}
}

void addEdge_int(Graph graph, int v1, int v2, int w)
{
	//if(havenoutedge_int(graph, v1, v2) == 1) return;
	// do thi vo huong nen can co (v1 v2) va (v2 v1)
	// them canh v1 v2
	// check xem da co dinh tren cay chua
	JRB bn = jrb_find_int(graph->outedges, v1);
	if(bn==NULL) // neu chua co thi them vao
	{		
		JRB tree = make_jrb(); 
		jrb_insert_int(tree, v2, new_jval_i(w));
		jrb_insert_int(graph->outedges, v1, new_jval_v(tree));
	}
	else // dinh v1 da co tren cay
	{
		//node = jrb_find_int(g, v1);
		// them canh v1->v2 xuôi
		JRB tree = (JRB)jval_v(bn->val);
		if(jrb_find_int(tree, v2)) return;
		jrb_insert_int(tree, v2, new_jval_i(w));			
	}
    //if(haveninedge_int(graph, v2, v1) == 1) return;
    bn = jrb_find_int(graph->inedges, v2);
	if(bn==NULL) // neu chua co thi them vao
	{		
		JRB tree = make_jrb(); 
		jrb_insert_int(tree, v1, new_jval_i(w));
		jrb_insert_int(graph->inedges, v2, new_jval_v(tree));
	}
	else // dinh v2 da co tren cay
	{
		//node = jrb_find_int(g, v1);
		// them canh v1->v2 chiều ngc
		JRB tree = (JRB)jval_v(bn->val);
		jrb_insert_int(tree, v1, new_jval_i(w));			
	}
}
JRB getoutedges_str(Graph graph, char* v)
{
	JRB Out = make_jrb();
	JRB node = jrb_find_str(graph->outedges, v);
	if (node == NULL) return NULL;
	JRB tree = (JRB) jval_v(node->val);
	if(!tree) return NULL;
	int total = 0;   
	jrb_traverse(node, tree)
	{
		//output[total] = (char*)malloc(20*sizeof(char));
		//printf("key: %s\n", jval_s(node->key));
		jrb_insert_str(Out, strdup(node->key.s), new_jval_i(node->val.i));
		total++;
	}    
	if(total == 0) return NULL;
	Out->size = total;
	return Out;
}
JRB getinedges_str(Graph graph, char *v)
{
	JRB In = make_jrb();
	JRB node = jrb_find_str(graph->inedges, v);
	if (node == NULL) return 0;
	JRB tree = (JRB) jval_v(node->val);
	if(!tree) return 0;
	int total = 0;   
	jrb_traverse(node, tree)
	{
		//output[total] = (char*)malloc(20*sizeof(char));
		//printf("key: %s\n", jval_s(node->key));
		jrb_insert_str(In, strdup(node->key.s), new_jval_i(node->val.i));
		total++;
	}  
	if(total == 0) return NULL;
	In->size = total;
	return In;
}
JRB getoutedges_int(Graph graph, int v)
{
	JRB Out = make_jrb();
	JRB node = jrb_find_int(graph->outedges, v);
	if (node == NULL) return NULL;
	JRB tree = (JRB) jval_v(node->val);
	if(!tree) return NULL;
	int total = 0;   
	jrb_traverse(node, tree)
	{
		//output[total] = (char*)malloc(20*sizeof(char));
		//printf("key: %s\n", jval_s(node->key));
		jrb_insert_int(Out, node->key.i, new_jval_i(node->val.i));
		total++;
	}    
	if(total == 0) return NULL;
	Out->size = total;
	return Out;
}
JRB getinedges_int(Graph graph, int v)
{
	JRB In = make_jrb();
	JRB node = jrb_find_int(graph->inedges, v);
	if (node == NULL) return 0;
	JRB tree = (JRB) jval_v(node->val);
	if(!tree) return 0;
	int total = 0;   
	jrb_traverse(node, tree)
	{
		//output[total] = (char*)malloc(20*sizeof(char));
		//printf("key: %s\n", jval_s(node->key));
		jrb_insert_int(In, node->key.i, new_jval_i(node->val.i));
		total++;
	}  
	if(total == 0) return NULL;
	In->size = total;
	return In;
}
void reset(Graph graph)
{
	JRB node;
	jrb_traverse(node, graph->vertices)
	{
		node->visited = 0;
	} 
}
int visitbool_str(Graph graph, char *v)
{
	JRB i = jrb_find_str(graph->vertices, v);
	if (i)
	{
		if(i->visited == 1) return 1;
	}
	 return 0;
}
int visitbool_int(Graph graph, int v)
{
	JRB i = jrb_find_int(graph->vertices, v);
	if (i)
	{
		if(i->visited == 1) return 1;
	}
	 return 0;
}
void visiting_str(Graph graph, char *v)
{
	JRB i = jrb_find_str(graph->vertices, v);
	if (i)
	{
		i->visited = 1;
	}
}
void visiting_int(Graph graph, int v)
{
	JRB i = jrb_find_int(graph->vertices, v);
	if (i)
	{
		i->visited = 1;
	}
}
int clock_count = 1;
int iden;
int Component = 0;
int order = 0;
int P[10000];
void previsit_str(Graph g, char *v)
{
	JRB n = jrb_find_str(g->vertices, v);
	if (n)
	{
		n->pre = clock_count;
	}
	clock_count++;
	
}
void postvisit_str(Graph g, char *v)
{
	JRB n = jrb_find_str(g->vertices, v);
	if (n)
	{
		n->post = clock_count;
	}
	clock_count++;
	
}
void previsit_int(Graph g, int v)
{
	JRB n = jrb_find_int(g->vertices, v);
	if (n)
	{
		n->pre = clock_count;
	}
	clock_count++;
	
}
void postvisit_int(Graph g, int v)
{
	JRB n = jrb_find_int(g->vertices, v);
	if (n)
	{
		n->post = clock_count;
	}
	clock_count++;
	P[order] = clock_count-1;
	order++;
}
void dropGraph(Graph graph)
{
	JRB node;
	jrb_traverse(node, graph->vertices)
	{
		jrb_free_tree((JRB)jval_v(node->val) );
	}
	jrb_traverse(node, graph->inedges)
	{
		jrb_free_tree((JRB)jval_v(node->val) );
	}
	jrb_traverse(node, graph->outedges)
	{
		jrb_free_tree((JRB)jval_v(node->val) );
	}
	free(graph);
}
JRB Maxlove(JRB node)
{
	int i = 0;
	JRB tmp;
	JRB list = (JRB)jval_v(node->val);
	jrb_traverse(tmp, list)
	{
		if(i == node->visited) return tmp;
		else i++;
	}
}
int NoWife(JRB Boy)
{
	JRB node;
	jrb_traverse(node ,Boy)
	{
		if(!node->marry) return 1;
	}
	return 0;
}
void StableMatching(JRB Boy, JRB Girl)
{
	FILE *f = fopen("HAPPY_FOREVER.txt", "w+");
	JRB node;
	JRB tmp;
	JRB list;
	JRB nowgirl;
	int nowboy, backboy;
	jrb_traverse(tmp, Girl) tmp->marry = 0;
	jrb_traverse(tmp, Boy) 
	{
		tmp->marry = 0;
		tmp->visited = 0;
	}
	while(NoWife(Boy))
	{
		jrb_traverse(node, Boy)
		{
		if(node->marry == 0){	
			node->marry = Maxlove(node)->val.i;
			node->visited++;
			nowgirl = jrb_find_int(Girl, node->marry);
			if(!nowgirl->marry) nowgirl->marry = node->key.i;
			else
			{
				list = (JRB)jval_v(nowgirl->val);
				jrb_traverse(tmp, list)
				{
					if(tmp->val.i == node->key.i) 
					{
						nowboy = tmp->key.i;
						continue;
					}
					if(tmp->val.i == nowgirl->marry) 
					{
						backboy = tmp->key.i;
					}
				}
				if(nowboy < backboy) //so sánh trọng số
				{
					jrb_find_int(Boy, nowgirl->marry)->marry = 0;
					nowgirl->marry = node->key.i;
				}
				else
				{
					node->marry = 0;
				}
			}
		}
		}
	}
	printf("Stable couples: Let's see in HAPPY_FOREVER.txt \n");
	jrb_traverse(node, Boy)
	{
		fprintf(f, "%d <3 %d\n", node->key.i, node->marry);
	}
	fclose(f);
}

void BFS(Graph graph, int start, int stop)
{
	JRB Adjacent;
	JRB node = jrb_find_int(graph->outedges, start);
	//JRB node = jrb_find_str(graph, stop);
	if (node == NULL) 
	{
		//printf("Khong co lich bay\n");
		return;   
	}
	JRB tmp = node;
	//reset(graph);
	Queuetype Q;
	init(&Q);
	Enqueue(&Q, tmp);
	visiting_int(graph, tmp->key.i);
	while(!isEmpty(Q))
	{
		Adjacent = make_jrb();
		tmp = Dequeue(&Q);
		if(stop == tmp->key.i) iden = 1;
		
			//printf("%3d", tmp->key.i); //thăm node
			
			//if(strcasecmp(s->key.s, stop) == 0) return;
			Adjacent = getoutedges_int(graph, tmp->key.i);
			if(!Adjacent) 
			{
				continue;
			}
			else
			{
				JRB newnode;
				jrb_traverse(newnode, Adjacent)	
				{
					JRB n = jrb_find_int(graph->vertices, newnode->key.i);
					if(!visitbool_int(graph, n->key.i)){
						Enqueue(&Q, n); 
						visiting_int(graph, n->key.i);
						n->back = new_jval_i(tmp->key.i);
						}
				}
				jrb_free_tree(Adjacent);
			}
		}
}
void BFStraversal(Graph graph, int start, int stop)
{
	reset(graph);
	JRB node;
	BFS(graph, start, stop);
	jrb_traverse(node, graph->vertices)
	{
		if(!visitbool_int(graph, node->key.i) && node->key.i != start) BFS(graph, node->key.i, stop);
	} 
}

void UpdateComponent(Graph graph, int s)
{
	JRB o = jrb_find_int(graph->vertices, s);
	if(!o) return;
	else 
	{
		o->component = Component;
	}
}
void MinResult(Graph g, int start, int stop)
{
	JRB tmp;
	JRB o = jrb_find_int(g->outedges, start);
	if(!o) 
		{
			printf("No path\n");
			return;
		}
	JRB n = jrb_find_int(g->inedges, stop);
	if(!n) 
		{
			printf("No path\n");
			return;
		}
	else n = jrb_find_int(g->vertices, stop);
	JRB k;
	int b;
	k = getoutedges_int(g, start); 
	if(!k)
	{
			printf("No path\n");
			return;
		}
		k = getinedges_int(g, stop); 
	if(!k)
	{
			printf("No path\n");
			return;
		}
	do{
		printf("%d <- ", n->key.i);
		b = n->back.i;
		n = jrb_find_int(g->vertices, n->back.i);
		if(!n) break;
	}while(b != start); 
	if(!n && b != start) 
	{
		printf("Here end. No path\n");
		return;
	}
	else printf("%d\n", start);
}
int tra; 
int Check(int A[], int s, int length)
{
	for(int i = 0; i < length; i++) if(s == A[i]) return 1;
	return 0;
}
int haspath = 0;
void DFStraversal_Post(Graph graph)
{
	tra = order;
	int OrderVertex[order];
	reset(graph);
	JRB node;
	while((order-1)>=0){

	jrb_traverse(node, graph->vertices){
			if(node->post == P[order-1])  
			{
				OrderVertex[order-1] = node->key.i;
				order--;
			}
		} 
	}
	for(int i = tra-1; i >= 0; i--){
		if(jrb_find_int(graph->vertices, OrderVertex[i]) && !visitbool_int(graph, OrderVertex[i]))
		{
			Component++;
			DFS_Post(graph, OrderVertex[i], 0);
		}
	} 
}
void DFStraversal(Graph graph, int start, int stop)
{
	reset(graph);
	JRB node;
	DFS(graph, start, stop);
	jrb_traverse(node, graph->vertices)
	{
		if(node->visited == 0 && node->key.i != start) 
		{
			DFS(graph, node->key.i, stop);
		}
	} 
}
void DFS(Graph graph, int start, int stop)
{
	JRB Adjacent;
	JRB node = jrb_find_int(graph->outedges, start);
	if (node == NULL) 
	{
		//printf("%5d", start);
		if(start == stop) haspath = 1;
		visiting_int(graph, start);
		return;
	}
	JRB tmp = node;
	visiting_int(graph, start);
	//printf("%5d", start);
	if(start == stop) haspath = 1;
	Adjacent = getoutedges_int(graph, tmp->key.i);
	if(Adjacent) 
	{
		jrb_traverse(tmp, Adjacent)	
		{
			if(!visitbool_int(graph, tmp->key.i)) 
			{
				//luu dinh lien trc
				DFS(graph, tmp->key.i, stop);
			}
		}
		
	}
	jrb_free_tree(Adjacent);
}
void Path(Graph graph, int start, int stop)
{
	JRB Adjacent;
	JRB node = jrb_find_int(graph->outedges, start);
	if (node == NULL) 
	{
		if(start == stop) 
		{
			haspath = 1;
			return;
		}
		visiting_int(graph, start);
		return;
	}
	JRB tmp = node;
	visiting_int(graph, start);
	if(start == stop) 
	{
		haspath = 1;
		return;
	}
	Adjacent = getoutedges_int(graph, tmp->key.i);
	if(Adjacent) 
	{
		jrb_traverse(tmp, Adjacent)	
		{
			if(!visitbool_int(graph, tmp->key.i)) 
			{
				//luu dinh lien trc
				Path(graph, tmp->key.i, stop);
			}
		}
		
	}
	jrb_free_tree(Adjacent);
}
void DFS_Post(Graph graph, int start, int stop)
{
	JRB Adjacent;
	JRB node = jrb_find_int(graph->outedges, start);
	if (node == NULL) 
	{
		UpdateComponent(graph, start);
		visiting_int(graph, start);
		tra--;
		return;
	}
	JRB tmp = node;
	UpdateComponent(graph, tmp->key.i);
	visiting_int(graph, start);
	tra--;
	Adjacent = getoutedges_int(graph, tmp->key.i);
	if(Adjacent) 
	{
		
		jrb_traverse(tmp, Adjacent)	
		{
			if(!visitbool_int(graph, tmp->key.i)) 
			{
				//luu dinh lien trc
				DFS_Post(graph, tmp->key.i, stop);
			}
		}
		
	}
	jrb_free_tree(Adjacent);
}
void DFStraversal_R(Graph graph)
{
	reset(graph);
	JRB node;
	jrb_traverse(node, graph->vertices)
	{
		if(visitbool_int(graph, node->key.i) == 0) 
		{
			DFS_R(graph, node->key.i, 0);
		}
	} 
}
void DFS_R(Graph graph, int start,int stop)
{
	JRB Adjacent;
	JRB node = jrb_find_int(graph->inedges, start);
	if (node == NULL) 
	{
		visiting_int(graph, start);
		previsit_int(graph, start);
		postvisit_int(graph, start);
		return;
	}
	JRB tmp = node;
	visiting_int(graph, start);
	previsit_int(graph, start);
	Adjacent = getinedges_int(graph, tmp->key.i);
	if(Adjacent) 
	{
		jrb_traverse(tmp, Adjacent)	
		{
			if(!visitbool_int(graph, tmp->key.i)) 
			{
				DFS_R(graph, tmp->key.i, stop);
			}
		}
	}
	postvisit_int(graph, start);
	jrb_free_tree(Adjacent);
}
void StrongComponent(Graph g)
{
	DFStraversal_R(g);
    DFStraversal_Post(g);
}
void ListComponet(Graph g, int v)
{
	JRB cur;
	JRB node = jrb_find_int(g->vertices, v);
	int alone = 1;
	jrb_traverse(cur, g->vertices)
	{ 
		if(cur->component == node->component && cur->key.i != v) 
		{
			printf("%d ", cur->key.i);
			alone = 0;
		}
	}
	if(alone == 1) printf("Only %d\n", v);
	printf("\n");
}
int deletemin_int(Graph g, Piqueue *A, int *size)
{
	JRB n;
	int min = A[0].dist;
	int interrupt = 0;
	for(int i = 0; i < *size; i++)
	{
	if(A[i].dist < min) 
	{
		min = A[i].dist;
		interrupt = i;
	}
	}
	for(int i = interrupt; i < (*size - 1); i++) 
	{
		A[i] = A[i+1]; 
		n = jrb_find_int(g->vertices, jval_i(A[i].vertex));
		n->pijority = i;
	}
	(*size)--;
	return min;
			
}
JRB minvertex(Graph graph, int d)
{
	JRB node;
	jrb_traverse(node, graph->vertices)
	{
		if(node->dist == d) return node;
	}
}
int length(Graph graph, int start, int end)
{
	JRB n =  jrb_find_int(graph->outedges, start);
	JRB e = (JRB)jval_v(n->val);
	jrb_traverse(n, e)
	{
		if(end == jval_i(n->key)) return jval_i(n->val);
	}
	return Infinity;
}
int Dijkstra_int(Graph graph, int u, int end)
{
	if(!jrb_find_int(graph->outedges, u) || !jrb_find_int(graph->inedges, end)) return -1;
	Path(graph, u, end);
	if(haspath == 0) return -1;
	Piqueue path[10000];
	int length[10000];
	int i = 1;
	int j;
	int d;
	path[0].vertex = new_jval_i(u);
	path[0].dist = 0;
	JRB n;
	JRB e, tmp, m;
	n = jrb_find_int(graph->vertices, u);
	n->dist = 0;
	if(!n) return -1;
	jrb_traverse(n, graph->vertices)
	{
		if(n->key.i != u) {n->dist = Infinity;
		path[i].dist = Infinity;
		path[i].vertex = n->key;
		n->pijority = i;
		i++;
		}
	}
	while(i > 0)
	{
		d = deletemin_int(graph, path, &i);
		n = minvertex(graph, d);
		m = jrb_find_int(graph->outedges, n->key.i);
		if(!m) 
		{
			for(int j = n->pijority; j < i; j++) 
			{
				path[j] = path[j+1];
				n = jrb_find_int(graph->vertices, jval_i(path[i].vertex));
				n->pijority = i;
			}
			continue;
		}
		e = (JRB)jval_v(m->val);
		j = 0;
		jrb_traverse(tmp, e)
		{
			length[j] = jval_i(tmp->val);
			j++;
		}
		j = 0;
		jrb_traverse(m, e)
		{
			tmp = jrb_find_int(graph->vertices, m->key.i);
			if(tmp->dist > (n->dist + length[j]))
			{
				tmp->dist = n->dist + length[j];
				tmp->back = n->key;
				path[tmp->pijority].dist = tmp->dist;
			}
			j++;
		}
	}
	haspath = 0;
		jrb_traverse(n, graph->vertices)
		{
			if(n->key.i == end) return n->dist;
		}
}
void ShortestPath_int(Graph g, int start, int end)
{
	JRB n = jrb_find_int(g->vertices, end);
	while(n->key.i != start){
		printf("%d <- ", n->key.i);
		n = jrb_find_int(g->vertices, n->back.i);
	} 
	printf("%d\n", start);
}