#include <iostream>
using namespace std;

const int MAX = 100;
int graph[MAX][MAX];
int parent[MAX];
int n;

int find(int i) {
    while (parent[i] != -1) {
        i = parent[i];
    }
    return i;
}

bool unionSet(int u, int v) {
    int pu = find(u);
    int pv = find(v);
    if (pu == pv) {
        return false;
    }
    parent[pu] = pv;
    return true;
}

int readIntCell(int i, int j) {
    int value;
    while (true) {
        cout << "Enter value for row " << i << " column " << j << " (0 or 1): ";
        cin >> value;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input! Please enter a number.\n";
        } else if (value != 0 && value != 1) {
            cout << "Invalid value! Only 0 or 1 allowed.\n";
        } else {
            return value;
        }
    }
}

int main() {
    cout << "Enter number of vertices: ";
    while (!(cin >> n) || n <= 0 || n > MAX) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid input! Enter a valid number between 1 and " << MAX << ": ";
    }

    cout << "\nEnter adjacency matrix:\n";
    for (int i = 0; i < n; i++) {
        cout << "\n--- Row " << i << " ---\n";
        for (int j = 0; j < n; j++) {
            graph[i][j] = readIntCell(i, j);
        }
    }

    for (int i = 0; i < n; i++) {
        parent[i] = -1;
    }

    bool hasCycle = false;
    int u = -1, v = -1;

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (graph[i][j]) {
                if (!unionSet(i, j)) {
                    hasCycle = true;
                    u = i;
                    v = j;
                    break;
                }
            }
        }
        if (hasCycle) {
            break;
        }
    }

    cout << "\n--- BFS (Union-Find) Result ---\n";
    if (hasCycle) {
        cout << "Cycle detected between vertices: " << u << " and " << v << endl;
    } else {
        cout << "No cycle found using BFS.\n";
    }

    return 0;
}
