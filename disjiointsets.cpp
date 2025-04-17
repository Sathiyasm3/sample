#include <vector>
using namespace std;

class DisjointSet {
private:
    vector<int> parent;
    vector<int> rank;

public:
    DisjointSet(int size) {
        parent.resize(size);
        rank.resize(size, 0);
        for (int i = 0; i < size; ++i) {
            parent[i] = i;
        }
    }

    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    void unionSets(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        if (rootX == rootY) return;

        if (rank[rootX] < rank[rootY]) {
            parent[rootX] = rootY;
        } else if (rank[rootX] > rank[rootY]) {
            parent[rootY] = rootX;
        } else {
            parent[rootY] = rootX;
            rank[rootX]++;
        }
    }

    bool isConnected(int x, int y) {
        return find(x) == find(y);
    }
};

int main() {
    int n, q;
    cout << "Enter the number of elements: ";
    cin >> n;

    DisjointSet ds(n);

    cout << "Enter the number of union queries: ";
    cin >> q;

    for (int i = 0; i < q; ++i) {
        int x, y;
        cout << "Enter pair to union (x y): ";
        cin >> x >> y;
        ds.unionSets(x, y);
    }

    cout << "Enter the number of connectivity queries: ";
    cin >> q;

    for (int i = 0; i < q; ++i) {
        int x, y;
        cout << "Enter pair to check connectivity (x y): ";
        cin >> x >> y;
        cout << "Is " << x << " connected to " << y << "? "
             << (ds.isConnected(x, y) ? "Yes" : "No") << endl;
    }

    return 0;
}

