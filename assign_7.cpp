#include <iostream>
#include <list>
using namespace std;

const int MAX = 100;

// Adjacency Matrix Functions
void addEdgeMatrix(int adjMatrix[MAX][MAX], int u, int v) {
    adjMatrix[u][v] = 1;
    adjMatrix[v][u] = 1;  // For undirected graph
}

void displayMatrix(int adjMatrix[MAX][MAX], int vertices) {
    cout << "Adjacency Matrix:" << endl;
    for (int i = 0; i < vertices; ++i) {
        for (int j = 0; j < vertices; ++j) {
            cout << adjMatrix[i][j] << " ";
        }
        cout << endl;
    }
}

// Adjacency List Functions
void addEdgeList(list<int> adjList[MAX], int u, int v) {
    adjList[u].push_back(v);
    adjList[v].push_back(u);  // For undirected graph
}

void displayList(list<int> adjList[MAX], int vertices) {
    cout << "Adjacency List:" << endl;
    for (int i = 0; i < vertices; ++i) {
        cout << "Vertex " << i << ":";
        for (int vertex : adjList[i]) {
            cout << " -> " << vertex;
        }
        cout << endl;
    }
}

int main() {
    int vertices, edges;
    cout << "Enter the number of vertices: ";
    cin >> vertices;
    cout << "Enter the number of edges: ";
    cin >> edges;

    // Adjacency Matrix
    int adjMatrix[MAX][MAX] = {0};

    // Adjacency List
    list<int> adjList[MAX];

    cout << "Enter the edges (u v) one by one:" << endl;
    for (int i = 0; i < edges; ++i) {
        int u, v;
        cin >> u >> v;
        addEdgeMatrix(adjMatrix, u, v);
        addEdgeList(adjList, u, v);
    }

    displayMatrix(adjMatrix, vertices);
    cout << endl;
    displayList(adjList, vertices);

    return 0;
}
