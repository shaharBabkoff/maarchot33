#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "kosaraju_matrix.h"


    Graph *createGraph(int vertices)
    {
        Graph *graph = (Graph *)malloc(sizeof(Graph));
        graph->numVertices = vertices;

        // Allocate memory for the adjacency matrix
        graph->adjMatrix = (int **)malloc(vertices * sizeof(int *));
        for (int i = 0; i < vertices; i++)
        {
            graph->adjMatrix[i] = (int *)malloc(vertices * sizeof(int));
            for (int j = 0; j < vertices; j++)
            {
                graph->adjMatrix[i][j] = 0;
            }
        }

        graph->visited = (bool *)malloc(vertices * sizeof(bool));
        for (int i = 0; i < vertices; i++)
        {
            graph->visited[i] = false;
        }

        return graph;
    }

    void addEdge(Graph *graph, int src, int dest)
    {
        graph->adjMatrix[src - 1][dest - 1] = 1;
    }

    void dfs(Graph *graph, int vertex, int *stack, int *stackIndex)
    {
        graph->visited[vertex] = true;

        for (int i = 0; i < graph->numVertices; i++)
        {
            if (graph->adjMatrix[vertex][i] && !graph->visited[i])
            {
                dfs(graph, i, stack, stackIndex);
            }
        }

        // Push to stack when finished
        stack[(*stackIndex)++] = vertex;
    }

    Graph *getTranspose(Graph *graph)
    {
        Graph *transpose = createGraph(graph->numVertices);

        for (int i = 0; i < graph->numVertices; i++)
        {
            for (int j = 0; j < graph->numVertices; j++)
            {
                transpose->adjMatrix[j][i] = graph->adjMatrix[i][j];
            }
        }

        return transpose;
    }

    void dfsPrint(Graph *graph, int vertex)
    {
        graph->visited[vertex] = true;
        printf("%d ", vertex + 1);
        // std::cout << " " << vertex + 1;
        for (int i = 0; i < graph->numVertices; i++)
        {
            if (graph->adjMatrix[vertex][i] && !graph->visited[i])
            {
                dfsPrint(graph, i);
            }
        }
    }

    void kosaraju(Graph *graph)
    {
        int vertices = graph->numVertices;
        int stack[vertices];
        int stackIndex = 0;

        // First pass: Fill stack with vertices based on finishing times
        for (int i = 0; i < vertices; i++)
        {
            if (!graph->visited[i])
            {
                dfs(graph, i, stack, &stackIndex);
            }
        }

        // Create transpose of the graph
        Graph *transpose = getTranspose(graph);

        // Mark all vertices as not visited for the second pass
        for (int i = 0; i < vertices; i++)
        {
            transpose->visited[i] = false;
        }

        // Second pass: Process all vertices in order defined by stack
        while (stackIndex > 0)
        {
            int v = stack[--stackIndex];
            if (!transpose->visited[v])
            {
                dfsPrint(transpose, v);
                printf("\n");
                // std::cout << std::endl;
            }
        }
    }


// int main()
// {
//     // for (int i = 0; i < 1000000; i++)
//     // {

//         int vertices = 5;
//        Graph *graph =createGraph(vertices);
//        addEdge(graph, 1, 2);
//        addEdge(graph, 2, 3);
//        addEdge(graph, 3, 1);
//        addEdge(graph, 3, 4);
//        addEdge(graph, 4, 5);

//         // printf("Strongly Connected Components:\n");
//        kosaraju(graph);

//         // Free allocated memory
//         for (int i = 0; i < vertices; i++)
//         {
//             free(graph->adjMatrix[i]);
//         }
//         free(graph->adjMatrix);
//         free(graph->visited);
//         free(graph);
//     //}
//     return 0;
// }
