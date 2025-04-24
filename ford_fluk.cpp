#include <iostream>
#include <limits.h>
#include <queue>
#include <string.h>
#include <vector>

using namespace std;

bool bfs(int rGraph[][100], int s, int t, int parent[], int V) {
    bool visited[100];
    memset(visited, 0, sizeof(visited));

    queue<int> q;
    q.push(s);
    visited[s] = true;
    parent[s] = -1;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v = 0; v < V; v++) {
            if (visited[v] == false && rGraph[u][v] > 0) {
                if (v == t) {
                    parent[v] = u;
                    return true;
                }
                q.push(v);
                parent[v] = u;
                visited[v] = true;
            }
        }
    }
    return false;
}

int fordFulkerson(int graph[][100], int s, int t, int V) {
    int u, v;
    int rGraph[100][100];

    for (u = 0; u < V; u++)
        for (v = 0; v < V; v++)
            rGraph[u][v] = graph[u][v];

    int parent[100];
    int max_flow = 0;

    while (bfs(rGraph, s, t, parent, V)) {
        int path_flow = INT_MAX;
        for (v = t; v != s; v = parent[v]) {
            u = parent[v];
            path_flow = min(path_flow, rGraph[u][v]);
        }

        for (v = t; v != s; v = parent[v]) {
            u = parent[v];
            rGraph[u][v] -= path_flow;
            rGraph[v][u] += path_flow;
        }

        max_flow += path_flow;
    }

    return max_flow;
}

int main() {
    int V, E;
    cout << "Enter the number of vertices: ";
    cin >> V;
    cout << "Enter the number of edges: ";
    cin >> E;

    int graph[100][100] = {0};

    cout << "Enter the edges (source, destination, capacity):\n";
    for (int i = 0; i < E; i++) {
        int u, v, cap;
        cout << "Edge " << i + 1 << ": ";
        cin >> u >> v >> cap;
        graph[u][v] = cap;
    }

    cout << "The maximum possible flow is " << fordFulkerson(graph, 0, V - 1, V) << endl;

    return 0;
}
