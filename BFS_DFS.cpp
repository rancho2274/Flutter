#include <iostream>
#include <list>
#include <queue>
#include <stack>
#include <vector>

using namespace std;

const int MAX = 100;

void addEdge(list<int> adjList[MAX], int u, int v) {
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

void BFS(list<int> adjList[MAX], int startVertex, int vertices) {
    vector<bool> visited(vertices, false);
    queue<int> q;

    visited[startVertex] = true;
    q.push(startVertex);

    cout << "BFS Traversal starting from vertex " << startVertex << ": ";

    while (!q.empty()) {
        int v = q.front();
        cout << v << " ";
        q.pop();

        for (int adj : adjList[v]) {
            if (!visited[adj]) {
                visited[adj] = true;
                q.push(adj);
            }
        }
    }
    cout << endl;
}

void DFSUtil(list<int> adjList[MAX], int vertex, vector<bool> &visited) {
    visited[vertex] = true;
    cout << vertex << " ";

    for (int adj : adjList[vertex]) {
        if (!visited[adj]) {
            DFSUtil(adjList, adj, visited);
        }
    }
}

void DFS(list<int> adjList[MAX], int startVertex, int vertices) {
    vector<bool> visited(vertices, false);
    cout << "DFS Traversal starting from vertex " << startVertex << ": ";
    DFSUtil(adjList, startVertex, visited);
    cout << endl;
}

int main() {
    int vertices, edges;
    cout << "Enter the number of vertices: ";
    cin >> vertices;
    cout << "Enter the number of edges: ";
    cin >> edges;

    list<int> adjList[MAX];

    cout << "Enter the edges (u v) one by one:" << endl;
    for (int i = 0; i < edges; ++i) {
        int u, v;
        cin >> u >> v;
        addEdge(adjList, u, v);
    }

    displayList(adjList, vertices);

    int startVertex;
    cout << "Enter the starting vertex for BFS and DFS: ";
    cin >> startVertex;

    BFS(adjList, startVertex, vertices);
    DFS(adjList, startVertex, vertices);

    return 0;
}
