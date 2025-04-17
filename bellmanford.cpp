#include <vector>
#include<chrono>
#include<thread>
#include <climits>
using namespace std;

struct Edge {
    int u, v, weight;
};

bool bellmanFord(int V, int E, vector<Edge>& edges, int src) {
    vector<int> dist(V, INT_MAX);
    dist[src] = 0;

    for (int i = 1; i <= V - 1; ++i) {
        for (int j = 0; j < E; ++j) {
            int u = edges[j].u;
            int v = edges[j].v;
            int weight = edges[j].weight;

            if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
            }
        }
    }

    for (int i = 0; i < E; ++i) {
        int u = edges[i].u;
        int v = edges[i].v;
        int weight = edges[i].weight;

        if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
            cout << "Graph contains negative weight cycle\n";
            return false;
        }
    }

    for (int i = 0; i < V; ++i) {
        cout << "Distance from source " << src << " to vertex " << i << " is " << dist[i] << endl;
    }

    return true;
}

int main() {
    int V, E;
    cout << "Enter the number of vertices: ";
    cin >> V;
    cout << "Enter the number of edges: ";
    cin >> E;

    vector<Edge> edges(E);

    cout << "Enter the edges (source vertex, destination vertex, weight):\n";
    for (int i = 0; i < E; ++i) {
        cout << "Edge " << i + 1 << " - ";
        cin >> edges[i].u >> edges[i].v >> edges[i].weight;
    }

    int src;
    cout << "Enter the source vertex: ";
    cin >> src;

    if (!bellmanFord(V, E, edges, src)) {
        cout << "Negative weight cycle detected!" << endl;
    }

    for (int i = 5; i > 0; i--) {
        cout << "\r" << i << flush;
        this_thread::sleep_for(chrono::seconds(1));
    }
    cout << "\rExited!!\n";
    return 0;
}

