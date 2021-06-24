#include "undirectjrbgraph.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <bits/stdc++.h>
#define Infinity 999999
using namespace std;

// BEGIN Prufer_code
typedef struct Node{
    int value;
    Node* next;
}Node;
int a;
typedef struct Danhsach{
    Node*head;
}Danhsach;
void Prufer_Code();
void Coloring(Graph graph);
void BFStraversal(Graph graph, int start, int stop);
void BFS(Graph graph, int start, int stop);
void DFStraversal(Graph graph, int start, int stop);
void DFS(Graph graph, int start, int stop);
void DFS_Component(Graph graph, int start, int stop);
void DFSComponent(Graph graph);
int Prim(Graph graph, int start);
int Dijkstra_int(Graph graph, int u, int end);
void Kruskal(Graph graph);
Danhsach Khoitao(int x){
    Danhsach ds;
    ds.head = (Node*)malloc(x*sizeof(Node));
    for(int i=0; i<x; i++){
        ds.head[i].value = i;
        ds.head[i].next = NULL;
    }
    return ds;
}

void Danhsachke(Node *p, int x){
    Node*temp = (Node*)malloc(sizeof(Node));
    temp->value = x;
    temp->next = NULL;
    while(p->next != NULL) p = p->next;
    p->next = temp;
}

void Delete(Node*p, int x){
    Node*Front = p;
    p = p->next;
    while(p->value != x){
        Front = p;
        p = p->next;
    }
    Front->next = p->next;
    free(p);
}

void Prufer_Code(){
	FILE *fptr = fopen("prufercode.txt", "w+");
    int n = 0;
    Danhsach ds = Khoitao(10005);
    int a, b, f[10009];
    char s1[10], s2[10], s3[10];
    for(int i=0; i<= 10005; i++)
        f[i] = 0;
    FILE*inp = fopen("cp.txt","r");
    fscanf(inp, "%s%s", s1, s2);
    while(!feof(inp)){
        strcpy(s1, "");
        strcpy(s3, "");
        fscanf(inp, "%s", s1);
        fscanf(inp, "%s%s", s2, s3);
        if(strcmp(s1, "}")==0) break;
        a = atoi(s1);
        b = atoi(s3);
        f[a]++;
        f[b]++;
        Danhsachke(&ds.head[a], b);
        Danhsachke(&ds.head[b], a);
        n++;
    }
    printf("Day prufer code la prufercode.txt\n");
    for(int i = 1; i <= n; i++){
        if(f[i] == 1){
            int res = (ds.head[i].next)->value;
            if (i==n && res == 0) break;
            fprintf(fptr, "%d ", res);
            Delete(&ds.head[res], i);
            f[res]--;
            while(f[res]==1 && res < i && res != 0){
                int res2 = (ds.head[res].next)->value;
                if (i==n && res2 == 0) break;
                fprintf(fptr, "%d ", res2);
                Delete(&ds.head[res2], res);
                f[res2]--;
                res = res2;
            }
        }
    }
    fclose(inp);
	fclose(fptr);
}
//END Prufer_code

// BEGIN COLORING
void Coloring(Graph graph){
    queue<int> Q;
    int cnt = 0, i;
    int bl[10005], visited[10005], color[10005];
    JRB node1;
    jrb_traverse(node1, graph)
	{
	    visited[jval_i(node1->key)] = 0;
		Q.push(jval_i(node1->key));
		cnt++;
	}
	while(!Q.empty()){
        int x = Q.front();
        JRB bn = jrb_find_int(graph, x);
        Q.pop();
        JRB tree = (JRB)jval_v(bn->val);

        for(i=1; i<=cnt; i++) bl[i] = 0;
        JRB node;
        jrb_traverse(node, tree)
        {
            if(visited[jval_i(node->key)] == 1) bl[color[jval_i(node->key)]] = 1;
        }
        int p = 1;
        while(bl[p] == 1) p++;
        color[jval_i(bn->key)] = p;
        visited[jval_i(bn->key)] = 1;
	}
    for(i=1; i<=cnt; i++) cout << color[i] << " ";
}
//END COLORING

//Begin KrusKal
void makeSet(int x, int*pa, int*ranks){
    pa[x] = x;
    ranks[x] = 0;
}

int finds(int x, int*pa){
    while(x != pa[x]) x = pa[x];
    return x;
}

void unions(int x, int y, int*pa, int*ranks){
    int r1 = finds(x, pa);
    int r2 = finds(y, pa);
    if(r1 == r2) return;
    if(ranks[r1] > ranks[r2]) pa[r2] = r1;
    else{
        pa[r1] = r2;
        if(pa[r1]==pa[r2]) ranks[r2] = ranks[r1] + 1;
    }
}

void Kruskal(Graph graph){
    int parent[10005], ranks[10005];
    typedef pair<int, pair<int, int> > pi;
    priority_queue<pi, vector<pi>, greater<pi> > Q;
    queue<pair<int, int> > caykhung;
    JRB node, node2;
    jrb_traverse(node, graph)
	{
	    makeSet(jval_i(node->key), parent, ranks);
	    JRB tree = (JRB)jval_v(node->val);
	    jrb_traverse(node2, tree){
            int a = jval_i(node->key);
            int b = jval_i(node2->key);
            if(a < b) Q.push(make_pair(jval_i(node2->val), make_pair(a, b)));

	    }
	}
	int cnt = 0;
	while(!Q.empty()){
        pair<int, pair<int, int> > top = Q.top();
        Q.pop();
        int weigh = top.first;
        int dinh1 = top.second.first;
        int dinh2 = top.second.second;
        if (finds(dinh1, parent) != finds(dinh2, parent)){
            caykhung.push(make_pair(dinh1, dinh2));
            cout << dinh1 << " - " << dinh2 <<endl;
            cnt += weigh;
            unions(dinh1, dinh2, parent, ranks);
        }
	}
	printf("Tong trong so cua cay khung la: %d", cnt);
	a = cnt;
}
//End KrusKal2
void MinResult(Graph g, int start, int stop)
{
	JRB n = jrb_find_int(g, stop);
	while(n->key.i != start){
		printf("%d <- ", n->key.i);
		n = jrb_find_int(g, n->back.i);
	} 
	printf("%d\n", start);
}
void BFS(Graph graph, int start, int stop)
{
	JRB Adjacent;
	int n;
	JRB node = jrb_find_int(graph, start);
	//JRB node = jrb_find_str(graph, stop);
	if (node == NULL) 
	{
		//printf("Khong co lich bay\n");
		return;   
	}
	JRB tmp = node;
	jrb_traverse(node, graph)
	{
		node->visited = 0;
	} 
	Queuetype Q;
	init(&Q);
	Enqueue(&Q, tmp);
	tmp->visited = 1;
	while(!isEmpty(Q))
	{
		tmp = Dequeue(&Q);
		
			//printf("%s\n", tmp->key.s); //thăm node
			Adjacent = getAdjacentVertices_int(graph, tmp->key.i);
			if(!Adjacent) 
			{
				printf("No path\n");
				return;
			}
			else
			{
				JRB newnode;
				jrb_traverse(newnode, Adjacent)	
				{
					JRB n = jrb_find_int(graph, newnode->key.i);
					if(!Checkvisit(graph, n->key.i)){
						Enqueue(&Q, n); 
						n->visited = 1;
						n->back = new_jval_i(tmp->key.i);
						}
				}
				jrb_free_tree(Adjacent);
			}
		}
}
void BFStraversal(Graph graph, int start, int stop)
{
	JRB node;
	jrb_traverse(node, graph)
	{
		node->visited = 0;
	} 
    DFS(graph, start, stop);
	jrb_traverse(node, graph)
	{
		if(node->visited == 0 && node->key.i != start) BFS(graph, node->key.i, stop);
	} 
}
int Component;
int clock_count = 1;
void previsit(Graph g, int v)
{
	JRB i = jrb_find_int(g, v);
	if (i)
	{
		i->pre = clock_count;
	}
	clock_count++;
	
}
void postvisit(Graph g, int v)
{
	JRB i = jrb_find_int(g, v);
	if (i)
	{
		i->post = clock_count;
	}
	clock_count++;
	
}
void previsitComponent(JRB n, int c)
{
	n->component = c;
}
void DFSComponent(Graph graph)
{
	Component = 0;
	JRB node;
	jrb_traverse(node, graph)
	{
		unvisit(graph, node->key.i);
	} 
	jrb_traverse(node, graph)
	{
		if(!Checkvisit(graph, node->key.i)) {
			Component++;
			DFS_Component(graph, node->key.i, 0);
		}
	} 
}
void DFStraversal(Graph graph, int start, int stop)
{
	JRB node;
	jrb_traverse(node, graph)
	{
		node->visited = 0;
	} 
	DFS(graph, start, stop);
	jrb_traverse(node, graph)
	{
		if(node->visited == 0 && node->key.i != start) {
			DFS(graph, node->key.i, stop);
		}
	} 
}
void DFS(Graph graph, int start, int stop)
{
	JRB Adjacent;
	JRB node = jrb_find_int(graph, start);
	if (node == NULL) 
	{
		//printf("Khong co lich bay\n");
		return;   
	}
	JRB tmp = node;
	visit(graph, start);
	previsit(graph, start);
	Adjacent = getAdjacentVertices_int(graph, tmp->key.i);
	if(Adjacent) 
	{
		jrb_traverse(tmp, Adjacent)	
		{
			if(!Checkvisit(graph, tmp->key.i)) 
			{
				//lưu đỉnh liền trước
				DFS(graph, tmp->key.i, stop);
			}
		}
	}
	postvisit(graph, start);
	jrb_free_tree(Adjacent);
}
void DFS_Component(Graph graph, int start, int stop)
{
	JRB Adjacent;
	int n;
	JRB node = jrb_find_int(graph, start);
	if (node == NULL) 
	{
		//printf("Khong co lich bay\n");
		return;   
	}
	JRB tmp = node;
	visit(graph, start);
	previsit(graph, start);
	previsitComponent(tmp, Component);
	Adjacent = getAdjacentVertices_int(graph, tmp->key.i);
	if(n) 
	{
		jrb_traverse(tmp, Adjacent)	
		{
			if(!Checkvisit(graph, tmp->key.i)) 
			{
				//lưu đỉnh liền trước
				DFS(graph, tmp->key.i, stop);
			}
		}
	}
	postvisit(graph, start);
	jrb_free_tree(Adjacent);
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
		n = jrb_find_int(g, jval_i(A[i].vertex));
		n->pijority = i;
	}
	(*size)--;
	return min;
			
}
JRB minvertex(JRB graph, int d)
{
	JRB node;
	jrb_traverse(node, graph)
	{
		if(node->dist == d && !node->visited) return node;
	}
}
int length(Graph graph, int start, int end)
{
	JRB n =  jrb_find_int(graph, start);
	JRB e = (JRB)jval_v(n->val);
	jrb_traverse(n, e)
	{
		if(end == jval_i(n->key)) return jval_i(n->val);
	}
}
int Prim(Graph graph, int u)
{
	FILE *f = fopen("MSTprim.dot", "w+");
	Piqueue path[10000];
	int sum = 0;
	int length[10000];
	int i = 1;
	int j;
	int d;
	path[0].vertex = new_jval_i(u);
	path[0].dist = 0;
	JRB n;
	JRB e, tmp, m;
	n = jrb_find_int(graph, u);
	n->dist = 0;
	if(!n) return 0;
	jrb_traverse(n, graph)
	{
		if(n->key.i != u) {n->dist = Infinity;
		path[i].dist = Infinity;
		path[i].vertex = n->key;
		n->pijority = i;
		n->visited = 0;
		i++;
		}
	}
	printf("MST:\n");
	while(i > 0)
	{
		d = deletemin_int(graph, path, &i);
		n = minvertex(graph, d);
		e = (JRB)jval_v(n->val);
		j = 0;
		jrb_traverse(tmp, e)
		{
			length[j] = jval_i(tmp->val);
			j++;
		}
		j = 0;
		jrb_traverse(tmp, e)
		{
			m = jrb_find_int(graph, tmp->key.i);
			if(m->visited != 1 && m->dist > length[j])
			{
				m->dist = length[j];
				m->back = n->key;
				path[m->pijority].dist = m->dist;
			}
			j++;
			
		}
		n->visited = 1;
	}
	fprintf(f, "graph\n{\n");
	jrb_traverse(n, graph)
	{
		if(n->key.i == u) continue;
		if(n->dist != Infinity && n->dist != 0){
			fprintf(f, "%d -- %d\n", n->back.i, n->key.i);
			sum += n->dist;
		}
	}
	fprintf(f, "}");
	fclose(f);
	return sum;
}
void Primb(Graph graph, int start)
{
	set <int> Unconnected;
	int visited[10005];
	for(int i=0;i<=10000;i++)visited[i] = 0;
	int totalweight = 0;
	// them cac dinh tren do thi vao tap chua co tren cay
	for(JRB ptr = jrb_first(graph); ptr != jrb_nil(graph); ptr = jrb_next(ptr))
	{
		Unconnected.insert(jval_i(ptr->key));
	}
	visited[start] = 1;
	Unconnected.erase(start);
	int u, c, minc, minu;
	int minn, i = 1;
	while(!Unconnected.empty())
	{
		minn = 99999;
		JRB dothi;
		// can tim canh co trogn so nho nhat ma 1 dinh thuoc C và dinh thuoc U
		jrb_traverse(dothi, graph){
            if(visited[jval_i(dothi->key)] == 1){
                c = jval_i(dothi->key);
                JRB node = jrb_find_int(graph, c);
                JRB tree = (JRB) jval_v(node->val);
                JRB node1;
                jrb_traverse(node1, tree){
                    if(Unconnected.find(jval_i(node1->key)) != Unconnected.end())
                    {
                        int edgeweight = jval_i(node1->val);
                        if(minn>edgeweight)
                        {
                            minn = edgeweight;
                            minc = c;
                            minu = jval_i(node1->key);
                        }
                    }
                }
            }
		}
        printf("them canh (%d,%d), weight %d\n",minu,minc,minn);
        // bo sung them canh (minc, minu)
        totalweight = totalweight + minn;
        visited[minu]=1;
        Unconnected.erase(minu);
	}
	printf("Tong trong so: %d\n",totalweight);
}
int Dijkstra_int(Graph graph, int u, int end)
{
	Piqueue path[10000];
	int length[10000];
	int i = 1;
	int j;
	int d;
	path[0].vertex = new_jval_i(u);
	path[0].dist = 0;
	JRB n;
	jrb_traverse(n, graph)
	{
		n->visited = 0;
	}
	JRB e, tmp, m;
	n = jrb_find_int(graph, u);
	n->dist = 0;
	if(!n) return -1;
	jrb_traverse(n, graph)
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
		e = (JRB)jval_v(n->val);
		j = 0;
		jrb_traverse(tmp, e)
		{
			length[j] = jval_i(tmp->val);
			j++;
		}
		j = 0;
		jrb_traverse(m, e)
		{
			tmp = jrb_find_int(graph, m->key.i);
			if(tmp->dist > (n->dist + length[j]))
			{
				tmp->dist = n->dist + length[j];
				tmp->back = n->key;
				path[tmp->pijority].dist = tmp->dist;
			}
			j++;
		}
	}
		jrb_traverse(n, graph)
		{
			if(n->key.i == end) return n->dist;
		}
}
void ShortestPath_int(Graph g, int start, int end)
{
	JRB n = jrb_find_int(g, end);
	while(n->key.i != start){
		printf("%d <- ", n->key.i);
		n = jrb_find_int(g, n->back.i);
	} 
	printf("%d\n", start);
}