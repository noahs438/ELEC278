// Assignment 3, Q3 - Serhan, Noah
// Write a function Mothvex() to find a mother vertex in the graph and main()
// function to create a graph, for example, the graph below, and output the mother
// vertex in that graph. If the mother vertex of the graph does not exist, output -1. If
// there are multiple mother vertex, output all of them.
// A mother vertex in a graph G = (V, E) is a vertex v such that all other vertices in G
// can be reached by a path from v.

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_VERTICES 100

// Graph structure
struct Graph {
    int numVertices;
    int adjacencyMatrix[MAX_VERTICES][MAX_VERTICES];
};

// Function to perform a depthfirst traversal in a graph
void depthFirst(struct Graph *graph, int vertex, bool *visited){
    // Mark the current vertex as visited
    visited[vertex] = true;
    // Visit all adjacent vertices
    for (int i = 0; i < graph->numVertices; i++){
        if (graph->adjacencyMatrix[vertex][i] && !visited[i])
            depthFirst(graph, i, visited);
    }
}

// Function to find the mother vertex in a graph
void Mothvex(struct Graph *graph){
    // Array to keep track of visited vertices
    bool visited[MAX_VERTICES];
    int motherVertex = -1;
    // Mark all vertices as not visited
    for (int i = 0; i < graph->numVertices; i++){
        visited[i] = false;
    }
    // Traverse the graph to find the mother vertex
    for (int i = 0; i < graph->numVertices; i++){
        // If the vertex has not been visited yet, do a depth-first search
        // starting from this vertex
        if (!visited[i]){
            depthFirst(graph, i, visited);
            // Set the current vertex as the mother vertex
            motherVertex = i;
        }
    }
    // If a mother vertex was found, output it
    if (motherVertex != -1){
        printf("Mother vertex: %d\n", motherVertex);
    }
    else{
        printf("Mother vertex does not exist\n");
    }
}

// Function to create a graph with the specified number of vertices
struct Graph *CreateGraph(int numVertices){
    struct Graph *graph = malloc(sizeof(struct Graph));
    graph->numVertices = numVertices;
    // Initialize the adjacency matrix
    for (int i = 0; i < numVertices; i++){
        for (int j = 0; j < numVertices; j++){
            graph->adjacencyMatrix[i][j] = 0;
        }
    }
    return graph;
}

// Function to add an edge to the graph
void AddEdge(struct Graph *graph, int source, int destination){
    // Set the value of the adjacency matrix at the specified position to 1
    graph->adjacencyMatrix[source][destination] = 1;
}

int main(){
    // Create a graph with 7 vertices (0-1-2-3-4-5-6)
    struct Graph *graph = CreateGraph(7); // Update the number of vertices if changed

    // Add edges to the graph (following the example - should return 5)
    AddEdge(graph, 0, 1);
    AddEdge(graph, 0, 2);
    AddEdge(graph, 1, 3);
    AddEdge(graph, 4, 1);
    AddEdge(graph, 5, 2);
    AddEdge(graph, 5, 6);
    AddEdge(graph, 6, 0);
    AddEdge(graph, 6, 4);

    // Find the mother vertex
    Mothvex(graph);

    return 0;
}