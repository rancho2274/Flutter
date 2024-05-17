#include <stdio.h>
#include <stdlib.h>

int Bellman_Ford(int G[20][20], int V, int E, int edge[20][2]) {
    int i, u, v, k, distance[20], parent[20], S, flag = 1;

    // Initialize distance and parent arrays
    for (i = 0; i < V; i++) {
        distance[i] = 1000;
        parent[i] = -1;
    }

    // Get the source vertex
    printf("Enter source: ");
    scanf("%d", &S);
    distance[S - 1] = 0;

    // Relax edges repeatedly
    for (i = 0; i < V - 1; i++) {
        for (k = 0; k < E; k++) {
            u = edge[k][0];
            v = edge[k][1];
            if (distance[u] + G[u][v] < distance[v]) {
                distance[v] = distance[u] + G[u][v];
                parent[v] = u;
            }
        }
    }

    // Check for negative-weight cycles
    for (k = 0; k < E; k++) {
        u = edge[k][0];
        v = edge[k][1];
        if (distance[u] + G[u][v] < distance[v]) {
            flag = 0;
        }
    }

    // Print the results
    if (flag) {
        for (i = 0; i < V; i++) {
            printf("Vertex %d -> cost = %d parent = %d\n", i + 1, distance[i], parent[i] + 1);
        }
    }

    return flag;
}

int main() {
    int V, edge[20][2], G[20][20], i, j, k = 0;

    printf("BELLMAN FORD\n");
    printf("Enter number of vertices: ");
    scanf("%d", &V);

    // Get the graph matrix input
    printf("Enter graph in matrix form (input 0 for no edge, positive value for edge weight):\n");
    for (i = 0; i < V; i++) {
        for (j = 0; j < V; j++) {
            printf("G[%d][%d] = ", i + 1, j + 1);
            scanf("%d", &G[i][j]);
            if (G[i][j] != 0) {
                edge[k][0] = i;
                edge[k++][1] = j;
            }
        }
    }

    // Run the Bellman-Ford algorithm
    if (Bellman_Ford(G, V, k, edge)) {
        printf("\nNo negative weight cycle\n");
    } else {
        printf("\nNegative weight cycle exists\n");
    }

    return 0;
}