#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "kosaraju_stack.h"

   
    Node *createNode(int vertex)
    {
        Node *newNode = (Node *)malloc(sizeof(Node));
        newNode->vertex = vertex;
        newNode->next = NULL;
        return newNode;
    }

    Graph *createGraph(int vertices)
    {
        Graph *graph = (Graph *)malloc(sizeof(Graph));
        graph->numVertices = vertices;

        graph->adjLists = (Node **)malloc(vertices * sizeof(Node *));
        graph->visited = (bool *)malloc(vertices * sizeof(bool));

        for (int i = 0; i < vertices; i++)
        {
            graph->adjLists[i] = NULL;
            graph->visited[i] = false;
        }

        return graph;
    }

    void freeGraph(Graph *graph)
    {
        for (int i = 0; i < graph->numVertices; i++)
        {
            Node *temp = graph->adjLists[i], *next = NULL;
            while (temp)
            {
                next = temp->next;
                free(temp);
                temp = next;
            }
        }

        free(graph->adjLists);
        free(graph->visited);
        free(graph);
    }
    void addEdge(Graph *graph, int src, int dest)
    {
        // printf("adding edge %d, %d\n", src, dest);
        Node *newNode = createNode(dest - 1);
        newNode->next = graph->adjLists[src - 1];
        graph->adjLists[src - 1] = newNode;
    }

    void dfs(Graph *graph, int vertex, int *stack, int *stackIndex)
    {
        graph->visited[vertex] = true;

        Node *temp = graph->adjLists[vertex];

        while (temp)
        {
            int adjVertex = temp->vertex;
            if (!graph->visited[adjVertex])
            {
                dfs(graph, adjVertex, stack, stackIndex);
            }
            temp = temp->next;
        }

        stack[(*stackIndex)++] = vertex;
    }

    Graph *getTranspose(Graph *graph)
    {
        Graph *transpose = createGraph(graph->numVertices);

        for (int v = 0; v < graph->numVertices; v++)
        {
            Node *temp = graph->adjLists[v];
            while (temp)
            {
                addEdge(transpose, temp->vertex + 1, v + 1);
                temp = temp->next;
            }
        }

        return transpose;
    }

    void dfsPrint(Graph *graph, int vertex)
    {
        graph->visited[vertex] = true;
        printf("%d ", vertex + 1);
       // std::cout<<" "<<vertex+1;

        Node *temp = graph->adjLists[vertex];
        while (temp)
        {
            int adjVertex = temp->vertex;
            if (!graph->visited[adjVertex])
            {
                dfsPrint(graph, adjVertex);
            }
            temp = temp->next;
        }
    }

    void kosaraju(Graph *graph)
    {
        int vertices = graph->numVertices;
        int stack[vertices];
        int stackIndex = 0;

        for (int i = 0; i < vertices; i++)
        {
            if (!graph->visited[i])
            {
                dfs(graph, i, stack, &stackIndex);
            }
        }

        Graph *transpose = getTranspose(graph);

        for (int i = 0; i < vertices; i++)
        {
            transpose->visited[i] = false;
        }

        while (stackIndex > 0)
        {
            int v = stack[--stackIndex];
            if (!transpose->visited[v])
            {
                dfsPrint(transpose, v);
                printf("\n");
               //std::cout<<std::endl;
            }
        }
        freeGraph(transpose);
    }




// int main()
// {
//     // for (int j = 0; j < 10; j++)
//     // {
//     // for (int i = 0; i < 1000000; i++)
//     // {
//     int vertices = 8;
//     stack::Graph *graph = stack::createGraph(vertices);
//     stack::addEdge(graph, 1, 2);
//     stack::addEdge(graph, 2, 3);
//     stack::addEdge(graph, 3, 4);
//     stack::addEdge(graph, 4, 5);
//     stack::addEdge(graph, 5, 1);
//     stack::addEdge(graph, 6, 7);
//     stack::addEdge(graph, 7, 6);
//     // printf("Strongly Connected Components:\n");
//     stack::kosaraju(graph);
//     stack::freeGraph(graph);
//     // }
//     // }
//     return 0;
// }
