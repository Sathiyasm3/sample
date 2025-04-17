#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Graph {
    int V;
    vector<vector<int>> adj;
    vector<int> disc, low, parent;
    vector<bool> visited;
    vector<pair<int, int>> bridges;
    vector<int> articulationPoints;

public:
    Graph(int V) {
        this->V = V;
        adj.resize(V);
        disc.resize(V, -1);
        low.resize(V, -1);
        parent.resize(V, -1);
        visited.resize(V, false);
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void DFS(int u, int time) {
        visited[u] = true;
        disc[u] = low[u] = time;
        time++;

        int children = 0;
        for (int v : adj[u]) {
            if (!visited[v]) {
                parent[v] = u;
                children++;
                DFS(v, time);

                low[u] = min(low[u], low[v]);

                if (parent[u] == -1 && children > 1) {
                    articulationPoints.push_back(u);
                }

                if (parent[u] != -1 && low[v] > disc[u]) {
                    articulationPoints.push_back(u);
                }

                if (low[v] > disc[u]) {
                    bridges.push_back({u, v});
                }
            }
            else if (v != parent[u]) {
                low[u] = min(low[u], disc[v]);
            }
        }
    }

    void findBiconnectivity() {
        int time = 0;
        for (int i = 0; i < V; ++i) {
            if (!visited[i]) {
                DFS(i, time);
            }
        }

        cout << "Articulation Points: ";
        for (int ap : articulationPoints) {
            cout << ap << " ";
        }
        cout << endl;

        cout << "Bridges: ";
        for (auto bridge : bridges) {
            cout << "(" << bridge.first << ", " << bridge.second << ") ";
        }
        cout << endl;
    }
};

int main() {
    int V, E;
    cin >> V >> E;

    Graph g(V);

    for (int i = 0; i < E; ++i) {
        int u, v;
        cin >> u >> v;
        g.addEdge(u, v);
    }

    g.findBiconnectivity();

    return 0;
}
