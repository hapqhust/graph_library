#include <stdio.h>
#include "directedjrbgraph.h"
#include <time.h>
#include <stdlib.h>
int main()
{
    Graph g = createGraph();
    clock_t start, end;
    double jikan;
    int u, v, w;
    srand(time(NULL));
    start = clock();
    for(int i = 1; i <= 10000; i++) 
    {
        JRB tree = make_jrb();
        addVertex_int(g, i);
    }
    end = clock();
    jikan = (double)(end - start)/CLOCKS_PER_SEC;
    printf("Time generation: %lf\n", jikan);
    start = clock();
    for(long i = 0; i < 50000; i++)
    {
        u = 1 + rand() % 10000;
        v = 1 + rand() % 10000;
        w = 1 + rand() % 100;
        addEdge_int(g, u, v, w);
    }
    end = clock();
    jikan = (double)(end - start)/CLOCKS_PER_SEC;
    printf("Time generation: %lf\n", jikan);
    /*for(int i = 1; i <= 12 ; i++) 
    {
        addVertex_int(g, i);
    }
    addEdge_int(g, 1, 2, 1);
    addEdge_int(g, 2, 3, 1);
    addEdge_int(g, 2, 4, 1);
    addEdge_int(g, 2, 5, 1);
    addEdge_int(g, 5, 2, 1);
    addEdge_int(g, 3, 6, 1);
    addEdge_int(g, 6, 3, 1);
    addEdge_int(g, 7, 8, 1);
    addEdge_int(g, 5, 7, 1);
    addEdge_int(g, 6, 8, 1);
    addEdge_int(g, 5, 6, 1);
    addEdge_int(g, 9, 7, 1);
    addEdge_int(g, 10, 9, 1);
    addEdge_int(g, 7, 10, 1);
    addEdge_int(g, 8, 11, 1);
    addEdge_int(g, 11, 12, 1);
    addEdge_int(g, 12, 10, 1);*/
    /*addEdge_int(g, 2, 1, 1);
    addEdge_int(g, 1, 3, 1);
    addEdge_int(g, 2, 7, 1);
    addEdge_int(g, 1, 8, 1);
    addEdge_int(g, 5, 1, 1);
    addEdge_int(g, 4, 6, 1);
    addEdge_int(g, 6, 10, 1);
    addEdge_int(g, 10, 3, 1);
    addEdge_int(g, 5, 9, 1);
    addEdge_int(g, 8, 7, 1);
    addEdge_int(g, 7, 9, 1);
    addEdge_int(g, 9, 8, 1);
    addEdge_int(g, 8, 6, 1);
    addEdge_int(g, 3, 4, 1);*/
    /*addEdge_int(g, 1, 2, 1);
    addEdge_int(g, 1, 4, 1);
    addEdge_int(g, 2, 5, 1);
    addEdge_int(g, 2, 3, 1);
    addEdge_int(g, 3, 6, 1);
    addEdge_int(g, 4, 8, 1);
    addEdge_int(g, 5, 1, 1);
    addEdge_int(g, 6, 9, 1);
    addEdge_int(g, 7, 4, 1);
    addEdge_int(g, 5, 8, 1);
    addEdge_int(g, 8, 9, 1);
    addEdge_int(g, 8, 7, 1);
    addEdge_int(g, 9, 8, 1);
    addEdge_int(g, 8, 6, 1);*/
    /*for(int i = 1; i <= 5; i++) addVertex_int(g, i);
    addEdge_int(g, 1, 2, 4);
    addEdge_int(g, 1, 3, 2);
    addEdge_int(g, 2, 4, 2);
    addEdge_int(g, 2, 3, 3);
    addEdge_int(g, 2, 5, 3);
    addEdge_int(g, 3, 2, 1);
    addEdge_int(g, 3, 4, 4);
    addEdge_int(g, 3, 5, 5);
    addEdge_int(g, 5, 4, 1);*/
    start = clock();
    BFStraversal(g, 2, 5);
    end = clock();
    jikan = (double)(end - start)/CLOCKS_PER_SEC;
    printf("Time generation of BFS: %lf\n", jikan);
    start = clock();
    DFStraversal(g, 2, 5);
    end = clock();
    jikan = (double)(end - start)/CLOCKS_PER_SEC;
    printf("Time generation of DFS: %lf\n", jikan);
    start = clock();
    StrongComponent(g);
    printf("The numbers of strongly connected components: %d\n", Component);
    end = clock();
    jikan = (double)(end - start)/CLOCKS_PER_SEC;
    printf("Time generation of StrongComponent: %lf\n", jikan);
    //ListComponet(g, 9);
    int startver, endver;
    printf("Start: "); scanf("%d", &startver);
    printf("End: "); scanf("%d", &endver);
    start = clock();
    int min = Dijkstra_int(g, startver, endver);
    printf("\n");
    if(min < 0) printf("No path\n");
    else 
    {
        ShortestPath_int(g, startver, endver);
        printf("\nShortest path has sum: %d\n", min);
    }
    end = clock();
    jikan = (double)(end - start)/CLOCKS_PER_SEC;
    printf("Time generation of Dijkstra: %lf\n", jikan);
    return 0;
}