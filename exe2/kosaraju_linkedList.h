#ifndef KOSARAJU_LINKEDLIST_H
#define KOSARAJU_LINKEDLIST_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>



typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

typedef struct Graph {
    int numVertices;
    Node** adjLists;
    bool* visited;
} Graph;

Node* createNode(int vertex);
void insertAtEnd(Node** head, int vertex);
Graph* createGraph(int vertices);
void freeGraph(Graph* graph);
void freeList(Node* head);
void addEdge(Graph* graph, int src, int dest);
void dfs(Graph* graph, int vertex, Node** head);
Graph* getTranspose(Graph* graph);
void dfsPrint(Graph* graph, int vertex);
void kosaraju(Graph* graph);



#endif // KOSARAJU_LINKEDLIST_H
