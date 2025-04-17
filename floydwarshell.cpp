#include <iostream>
#include <vector>
#include <climits>
#include<thread>
#include<chrono>
using namespace std;

void floydWarshall(int V, vector<vector<int>>& dist) {
    for (int k = 0; k < V; ++k) {
        for (int i = 0; i < V; ++i) {
            for (int j = 0; j < V; ++j) {
                if (dist[i][k] != INT_MAX && dist[k][j] != INT_MAX && dist[i][j] > dist[i][k] + dist[k][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    for (int i = 0; i < V; ++i) {
        for (int j = 0; j < V; ++j) {
            if (dist[i][j] == INT_MAX) {
                cout << "INF ";
            } else {
                cout << dist[i][j] << " ";
            }
        }
        cout << endl;
    }
}

int main() {
    int V;
    cout << "Enter number of vertices: ";
    cin >> V;

    vector<vector<int>> dist(V, vector<int>(V, INT_MAX));

    cout << "Enter the adjacency matrix (use a large number or INT_MAX for no edge):\n";
    for (int i = 0; i < V; ++i) {
        for (int j = 0; j < V; ++j) {
            cin >> dist[i][j];
            if (i == j) {
                dist[i][j] = 0;
            }
        }
    }

    floydWarshall(V, dist);

    for (int i = 5; i > 0; i--) {
        cout << "\r" << i << flush;
        this_thread::sleep_for(chrono::seconds(1));
    }
    cout << "\rExited!!\n";

    return 0;
}

