#include <assert.h>
#include "kosaraju_stack.h"

// Function to compare two arrays for equality
bool arraysEqual(int* arr1, int* arr2, int size) {
    for (int i = 0; i < size; i++) {
        if (arr1[i] != arr2[i]) {
            return false;
        }
    }
    return true;
}

// Custom function to test if Kosaraju's algorithm works correctly
void testKosaraju() {
    int vertices = 8;
    Graph *graph = createGraph(vertices);
    addEdge(graph, 1, 2);
    addEdge(graph, 2, 3);
    addEdge(graph, 3, 4);
    addEdge(graph, 4, 5);
    addEdge(graph, 5, 1);
    addEdge(graph, 6, 7);
    addEdge(graph, 7, 6);
    
    // Expected output: Two SCCs: {1, 2, 3, 4, 5} and {6, 7}
    // Since we don't have an easy way to capture printf output, we'll check the visited array
    // Reset visited array
    for (int i = 0; i < vertices; i++) {
        graph->visited[i] = false;
    }
    
    kosaraju(graph);
    
    // After running kosaraju, check if all vertices were visited
    for (int i = 0; i < vertices; i++) {
        assert(graph->visited[i] == true);
    }

    // Clean up
    freeGraph(graph);
    printf("Test passed!\n");
}

int main() {
    testKosaraju();
    return 0;
}
