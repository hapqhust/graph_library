#include <stdio.h>
#include <stdlib.h>
#include "directedjrbgraph.h"
#include <time.h>
int main()
{
    FILE *f = fopen("chuotbach.txt", "w+");
    JRB BoyTree = make_jrb();
    JRB GirlTree = make_jrb();
    int girl, boy, love;
    JRB back;
    srand(time(NULL));
    clock_t start, end;
    double jikan;
    //Graph g = createGraph();
    start = clock();
    //Quy ước: Nam: 1-500, Nữ: 5001-5500
    for(int i = 1; i <= 500; i++) 
    {
        JRB tree = make_jrb();
        jrb_insert_int(BoyTree, i, new_jval_v(tree));
    }
    for(int i = 5001; i <= 5500; i++) 
    {
        JRB tree = make_jrb();
        jrb_insert_int(GirlTree, i, new_jval_v(tree));
    }
    end = clock();
    jikan = (double)(end - start)/CLOCKS_PER_SEC;
    printf("Time generation: %lf\n", jikan);
    start = clock();
    for(long i = 1; i <= 500; i++)
    {
        boy = i;
        fprintf(f, "%d:", boy);
        back = make_jrb();
        for(int j = 1; j <= 500; j++){
        love = j;
        do 
        {
            girl = 5001 + rand() % 500;
        } while(jrb_find_int(back, girl));
        if(j == 500) fprintf(f, "%d\n", girl);
        else fprintf(f, "%d ", girl);
        jrb_insert_int(back, girl, new_jval_v(NULL));
        //addEdge_int(g, boy, girl, love);
        //jrb_insert_int((JRB)jrb_find_int(BoyTree, boy)->val.v, love, new_jval_i(girl));
        }
        jrb_free_tree(back);
    }
    for(long i = 5001; i <= 5500; i++)
    {
        girl = i;
        back = make_jrb();
        fprintf(f, "%d:", girl);
        for(int j = 1; j <= 500; j++){
        love = j;
        do 
        {
            boy = 1 + rand() % 500;
        } while(jrb_find_int(back, boy));
        if(j == 500) fprintf(f, "%d\n", boy);
        else fprintf(f, "%d ", boy);
        jrb_insert_int(back, boy, new_jval_v(NULL));
        //addEdge_int(g, boy, girl, love);
        //jrb_insert_int((JRB)jrb_find_int(GirlTree, girl)->val.v, love, new_jval_i(boy));
        }
        jrb_free_tree(back);
    }
    fclose(f);
    f = fopen("chuotbach.txt", "r");
    int data; char c; 
    for(int i = 1; i <= 500; i++)
    {
        boy = i;
        love = 0;
        do
        {
            fscanf(f, "%d%c", &data, &c);
            girl = data;
            if(c != ':') 
            {
                love++;
                jrb_insert_int((JRB)jrb_find_int(BoyTree, boy)->val.v, love, new_jval_i(girl));
            }
        } while(c != '\n');
    }
    for(int i = 5001; i <= 5500; i++)
    {
        girl = i;
        do
        {
            fscanf(f, "%d%c", &data, &c);
            boy = data;
            if(c != ':') 
            {
                love++;
                jrb_insert_int((JRB)jrb_find_int(GirlTree, girl)->val.v, love, new_jval_i(boy));
            }
        } while(c != '\n');
    }
    end = clock();
    jikan = (double)(end - start)/CLOCKS_PER_SEC;
    printf("Time generation of input data of graph: %lf\n", jikan);
    start = clock();
    StableMatching(BoyTree, GirlTree);
    end = clock();
    jikan = (double)(end - start)/CLOCKS_PER_SEC;
    printf("Time generation of stable matching: %lf\n", jikan);
    fclose(f);
    return 0;
}