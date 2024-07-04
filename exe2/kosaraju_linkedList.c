#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "kosaraju_linkedList.h"


    Node *createNode(int vertex)
    {
        Node *newNode = (Node *)malloc(sizeof(Node));
        newNode->vertex = vertex;
        newNode->next = NULL;
        return newNode;
    }
    void insertAtEnd(Node **head, int vertex)
    {
        Node *newNode = createNode(vertex);
        if (*head == NULL)
        {
            *head = newNode;
        }
        else
        {
            Node *current = *head;
            while (current->next != NULL)
            {
                current = current->next;
            }
            current->next = newNode;
        }
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
    void freeList(struct Node *head)
    {
        struct Node *current = head;
        struct Node *nextNode;
        while (current != NULL)
        {
            nextNode = current->next;
            free(current);
            current = nextNode;
        }
    }
    void addEdge(Graph *graph, int src, int dest)
    {
        // printf("adding edge %d, %d\n", src, dest);
        Node *newNode = createNode(dest - 1);
        newNode->next = graph->adjLists[src - 1];
        graph->adjLists[src - 1] = newNode;
    }

    void dfs(Graph *graph, int vertex, Node **head)
    {
        graph->visited[vertex] = true;

        Node *temp = graph->adjLists[vertex];

        while (temp)
        {
            int adjVertex = temp->vertex;
            if (!graph->visited[adjVertex])
            {
                dfs(graph, adjVertex, head);
            }
            temp = temp->next;
        }

        insertAtEnd(head, vertex);
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
        // std::cout << " " << vertex + 1;

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
        struct Node *head = NULL;
        // int stack[vertices];
        // int stackIndex = 0;

        for (int i = 0; i < vertices; i++)
        {
            if (!graph->visited[i])
            {
                dfs(graph, i, &head);
            }
        }

        Graph *transpose = getTranspose(graph);

        for (int i = 0; i < vertices; i++)
        {
            transpose->visited[i] = false;
        }
        Node *current = head;
        while (current != NULL)
        {
            int v = current->vertex;
            if (!transpose->visited[v])
            {
                dfsPrint(transpose, v);
                printf("\n");
                // std::cout << std::endl;
            }
            current = current->next;
        }

        freeGraph(transpose);
    }


// int main()
// {
//     // for (int j = 0; j < 10; j++)
//     // {
//     // for (int i = 0; i < 1000000; i++)
//     // {
//         int vertices = 8;
//         Graph *graph = createGraph(vertices);
//         addEdge(graph, 1, 2);
//         addEdge(graph, 2, 3);
//         addEdge(graph, 3, 4);
//         addEdge(graph, 4,5);
//         addEdge(graph, 5, 1);
//         addEdge(graph, 6, 7);
//         addEdge(graph, 7, 6);

//         // printf("Strongly Connected Components:\n");
//         kosaraju(graph);
//         freeGraph(graph);
//   //  }
//     // }
//     return 0;
// }

