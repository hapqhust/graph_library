#include "undirectedjrb.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
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
typedef struct Nodestack
{
    JRB Data;
    struct Nodestack* next;
} Typenode;
typedef struct
{
    Typenode *top;
} *Stacktype;
int sizestack;
void Initialize(Stacktype *stack)
{
    stack = (Stacktype*)malloc(sizeof(Stacktype));
    if(stack == NULL) return;
    (*stack)->top = NULL;
}
int empty(Stacktype stack)
{
    return (stack->top == NULL);
}
int full(Stacktype stack, int size)
{
    return(sizestack == size);
}
void push(JRB x,Stacktype *stack)
{
    Typenode *newnode = (Typenode*)malloc(sizeof(Typenode));
    newnode->Data = x;
    newnode->next = NULL;
    if((*stack)->top == NULL) (*stack)->top = newnode;
    else
    {
        newnode->next = (*stack)->top;
        (*stack)->top = newnode;
    }
}
JRB pop(Stacktype *stack)
{
    JRB Key;
    Typenode *del;
    if(empty(*stack)) return NULL;
    else
    {
        Key = (*stack)->top->Data;
        del = (*stack)->top;
        (*stack)->top = (*stack)->top->next;
        free(del);
        return Key;
    }
}
typedef JRB Graph;
typedef struct 
{
	Jval vertex;
	int dist;
} Piqueue;
Graph createGraph();
void addEdge_int(Graph graph, int v1, int v2, int w);
void addEdge_str(Graph graph, char* v1, char* v2, int w);
JRB getAdjacentVertices_int (Graph graph, int v);
JRB getAdjacentVertices_str (Graph graph, char* v);
void dropGraph(Graph graph);
Graph createGraph()
{
	Graph newGraph = make_jrb();
	return newGraph;
}
int havenedge_int(Graph g, int v1, int v2)
{
	JRB node1 = jrb_find_int(g, v1);
	if(node1 == NULL) return 0;
	JRB tree1 = (JRB) jval_v(node1->val);
	/*JRB node2 = jrb_find_str(g, v2);
	if(node2== NULL) return 0;
	JRB tree2 = (JRB) jval_v(node2->val);*/
	//int total = 0;   
	jrb_traverse(node1, tree1)
	{
		if(v2 == jval_i(node1->key)) 
		{
			return 1;
		}
	}    
	return 0;  
}
void addEdge_int(Graph graph, int v1, int v2, int w)
{
	if(v1 == v2) return;
	// do thi vo huong nen can co (v1 v2) va (v2 v1)
	// them canh v1 v2
	// check xem da co dinh tren cay chua
	JRB bn = jrb_find_int(graph, v1);
	if(bn==NULL) // neu chua co thi them vao
	{		
		JRB tree = make_jrb(); 
		jrb_insert_int(tree, v2, new_jval_i(w));
		jrb_insert_int(graph, v1, new_jval_v(tree));
	}
	else // dinh v1 da co tren cay
	{
		//node = jrb_find_int(g, v1);
		// them canh v1 v2
		JRB tree = (JRB) jval_v(bn->val);
		if(jrb_find_int(tree, v2)) return;
		jrb_insert_int(tree, v2, new_jval_i(w));			
	}
	// them canh v2 v1
	bn = jrb_find_int(graph, v2);
	if(bn==NULL) // neu chua co thi them vao
	{
		JRB tree = make_jrb();
		jrb_insert_int(tree, v1, new_jval_i(w));
		jrb_insert_int(graph, v2, new_jval_v(tree));
	}
	else  // da co dinh v2 thi chi them canh v2 v1
	{
		JRB tree = (JRB) jval_v(bn->val);
		jrb_insert_int(tree, v1, new_jval_i(w));
	}
}
int havenedge_str(Graph g, char *v1, char* v2)
{
	JRB node1 = jrb_find_str(g, v1);
	if(node1 == NULL) return 0;
	JRB tree1 = (JRB) jval_v(node1->val);
	/*JRB node2 = jrb_find_str(g, v2);
	if(node2== NULL) return 0;
	JRB tree2 = (JRB) jval_v(node2->val);*/
	//int total = 0;   
	jrb_traverse(node1, tree1)
	{
		if(strcasecmp(v2, jval_s(node1->key)) == 0) 
		{
			return 1;
		}
	}    
	return 0;  
}

void addEdge_str(Graph graph, char* v1, char* v2, int w)
{
	if(strcmp(v1, v2) == 0) return;
	if(havenedge_str(graph, v1, v2) == 1) return;
	// do thi vo huong nen can co (v1 v2) va (v2 v1)
	// them canh v1 v2
	// check xem da co dinh tren cay chua
	JRB bn = jrb_find_str(graph, v1);
	if(bn==NULL) // neu chua co thi them vao
	{		
		JRB tree = make_jrb(); 
		jrb_insert_str(tree, strdup(v2), new_jval_i(w));
		jrb_insert_str(graph, strdup(v1), new_jval_v(tree));
	}
	else // dinh v1 da co tren cay
	{
		//node = jrb_find_int(g, v1);
		// them canh v1 v2
		JRB tree = (JRB)jval_v(bn->val);
		jrb_insert_str(tree, strdup(v2), new_jval_i(w));			
	}
	//JRB tree2 = make_jrb();
	//jrb_insert_str(graph, strdup(v2), new_jval_v(tree2));
	// them canh v2 v1
	bn = jrb_find_str(graph, v2);
	if(bn==NULL) // neu chua co thi them vao
	{
		JRB tree = make_jrb();
		jrb_insert_str(tree, strdup(v1), new_jval_i(w));
		jrb_insert_str(graph, strdup(v2), new_jval_v(tree));
	}
	else  // da co dinh v2 thi chi them canh v2 v1
	{
		JRB tree = (JRB) jval_v(bn->val);
		jrb_insert_str(tree, strdup(v1), new_jval_i(w));			
	}
}

JRB getAdjacentVertices_int(Graph graph, int v)
{
	JRB Adjacent = make_jrb();
	JRB node = jrb_find_int(graph, v);
	if (node == NULL) return NULL;
	JRB tree = (JRB) jval_v(node->val);
	if(!tree) return NULL;
	int total = 0;   
	jrb_traverse(node, tree)
	{
		//output[total] = (char*)malloc(20*sizeof(char));
		//printf("key: %s\n", jval_s(node->key));
		jrb_insert_int(Adjacent, node->key.i, new_jval_i(node->val.i));
		total++;
	}    
	if(total == 0) return NULL;
	Adjacent->size = total;
	return Adjacent;
}
JRB getAdjacentVertices_str(Graph graph, char* v)
{
	JRB Adjacent;
	JRB node = jrb_find_str(graph, v);
	if (node == NULL) return 0;
	JRB tree = (JRB) jval_v(node->val);
	if(!tree) return 0;
	int total = 0;   
	jrb_traverse(node, tree)
	{
		//output[total] = (char*)malloc(20*sizeof(char));
		//printf("key: %s\n", jval_s(node->key));
		jrb_insert_str(Adjacent, strdup(node->key.s), new_jval_i(node->val.i));
		total++;
	}    
	if(total == 0) return NULL;
	Adjacent->size = total;
	return Adjacent;
}
void unvisit(Graph graph, int s)
{
	JRB node = jrb_find_int(graph, s);
	if(node) node->visited = 0;
}
void visit(Graph graph, int s)
{
	JRB node = jrb_find_int(graph, s);
	if(node) 
	{
		node->visited = 1;
	}
}
int Checkvisit(Graph graph, int s)
{
	JRB node = jrb_find_int(graph, s);
	if(node->visited == 1) return 1;
	else return 0;
}


void dropGraph(Graph graph)
{
	JRB node;
	jrb_traverse(node, graph)
	{
		jrb_free_tree((JRB)jval_v(node->val));
	}
	free(graph);
}


