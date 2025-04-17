#include <iostream>
#include <vector>
#include <stack>
using namespace std;

void dfsRecursive(int node, vector<bool>& visited, const vector<vector<int>>& graph) {
    visited[node] = true;
    cout << node << " ";

    for (int neighbor : graph[node]) {
        if (!visited[neighbor]) {
            dfsRecursive(neighbor, visited, graph);
        }
    }
}

void dfsIterative(const vector<vector<int>>& graph, int startNode) {
    vector<bool> visited(graph.size(), false);
    stack<int> s;
    s.push(startNode);

    while (!s.empty()) {
        int node = s.top();
        s.pop();

        if (!visited[node]) {
            visited[node] = true;
            cout << node << " ";

            for (auto it = graph[node].rbegin(); it != graph[node].rend(); ++it) {
                if (!visited[*it]) {
                    s.push(*it);
                }
            }
        }
    }
}

int main() {
    int V, E;
    cout << "Enter the number of vertices and edges: ";
    cin >> V >> E;

    vector<vector<int>> graph(V);

    cout << "Enter the edges (u v):\n";
    for (int i = 0; i < E; ++i) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    cout << "Recursive DFS: ";
    vector<bool> visited(V, false);
    dfsRecursive(0, visited, graph);
    cout << endl;

    cout << "Iterative DFS: ";
    dfsIterative(graph, 0);
    cout << endl;

    return 0;
}
