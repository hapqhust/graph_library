#include <stdio.h>
#include "algorithm.h"
#include <time.h>
#include <stdlib.h>
int main()
{
    Graph g = createGraph();
    FILE *f = fopen("data.txt", "w+");
    clock_t start, end;
    double jikan;
    int u, v, w;
    int A;
    srand(time(NULL));
    start = clock();
    for(int i = 1; i <= 10000; i++) 
    {
        JRB tree = make_jrb();
        jrb_insert_int(g, i, new_jval_v(tree));
    }
    end = clock();
    jikan = (double)(end - start)/CLOCKS_PER_SEC;
    printf("Time generation: %lf\n", jikan);
    start = clock();
    printf("Nhap 1 dinh co dinh: ");
    scanf("%d", &A);
    for(long i = 0; i < 200000; i++)
    {
        u = 1 + rand() % 10000;
        v = 1 + rand() % 10000;
        w = 1 + rand() % 100;
        fprintf(f, "%d-%d:%d\n", u, v, w);
        addEdge_int(g, u, v, w);
        w = 1 + rand() % 10;
        fprintf(f, "%d-%d:%d\n", A, u, w);
        addEdge_int(g, A, u, w);
        w = 1 + rand() % 10;
        fprintf(f, "%d-%d:%d\n", A, v, w);
        addEdge_int(g, A, v, w);
    }
    end = clock();
    jikan = (double)(end - start)/CLOCKS_PER_SEC;
    printf("Time generation: %lf\n", jikan);
    /*addEdge_int(g, 2, 4, 1);
    addEdge_int(g, 2, 5, 3);
    addEdge_int(g, 2, 9, 2);
    addEdge_int(g, 3, 4, 2);
    addEdge_int(g, 7, 1, 4);
    addEdge_int(g, 3, 6, 1);
    addEdge_int(g, 1, 6, 5);
    addEdge_int(g, 3, 1, 2);
    addEdge_int(g, 5, 4, 7);
    addEdge_int(g, 8, 3, 4);
    addEdge_int(g, 8, 2, 5);
    addEdge_int(g, 9, 5, 5);
    addEdge_int(g, 9, 7, 5);
    addEdge_int(g, 1, 5, 3);
    addEdge_int(g, 4, 6, 3);
    addEdge_int(g, 9, 1, 8);
    addEdge_int(g, 2, 8, 5);
    addEdge_int(g, 3, 5, 2);
    addEdge_int(g, 7, 6, 5);
    addEdge_int(g, 1, 8, 6);
    addEdge_int(g, 5, 8, 4);
    addEdge_int(g, 2, 7, 5);
    addEdge_int(g, 7, 8, 1);
    addEdge_int(g, 6, 9, 3);*/
    start = clock();
    Kruskal(g);
    end = clock();
    jikan = (double)(end - start)/CLOCKS_PER_SEC;
    printf("\nTime generation of Kruskal: %lf\n", jikan);
    start = clock();
    printf("%d\n", Prim(g, 2));
    end = clock();
    jikan = (double)(end - start)/CLOCKS_PER_SEC;
    printf("Time generation of Prim:  %lf\n", jikan);
    start = clock();
    BFS(g, 2, 7);
    end = clock();
    jikan = (double)(end - start)/CLOCKS_PER_SEC;
    printf("Time generation of BFS: %lf\n", jikan);
    start = clock();
    DFStraversal(g, 5, 9);
    end = clock();
    jikan = (double)(end - start)/CLOCKS_PER_SEC;
    printf("Time generation of DFStraversal: %lf\n", jikan);
    start = clock();
    Coloring(g);
    printf("\n");
    end = clock();
    jikan = (double)(end - start)/CLOCKS_PER_SEC;
    printf("Time generation of Coloring: %lf\n", jikan);
    start = clock();
    Prufer_Code();
    end = clock();
    jikan = (double)(end - start)/CLOCKS_PER_SEC;
    printf("Time generation of Prufer_Code: %lf\n", jikan);
    int min = Dijkstra_int(g, 5, 7);
    ShortestPath_int(g, 5, 7);
    printf("\nShortest path has sum: %d\n", min);
    end = clock();
    jikan = (double)(end - start)/CLOCKS_PER_SEC;
    printf("Time generation of Dijkstra: %lf\n", jikan);
    start = clock();
    DFSComponent(g);
    printf("Numbers of component: %d\n", Component);
    end = clock();
    jikan = (double)(end - start)/CLOCKS_PER_SEC;
    printf("Time generation of Component_Counting: %lf\n", jikan);
    fclose(f);
}