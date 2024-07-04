#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Graph
{
    int numVertices;
    int **adjMatrix;
    bool *visited;
} Graph;

Graph *createGraph(int vertices);

void addEdge(Graph *graph, int src, int dest);

void dfs(Graph *graph, int vertex, int *stack, int *stackIndex);

Graph *getTranspose(Graph *graph);

void dfsPrint(Graph *graph, int vertex);

void kosaraju(Graph *graph);



