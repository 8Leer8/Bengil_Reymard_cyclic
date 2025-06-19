#include <iostream>
using namespace std;

const int MAX = 100;
int graph[MAX][MAX];
int visited[MAX];
int n;

bool dfs(int u, int parent, int &start, int &end) {
    visited[u] = 1;
    for (int v = 0; v < n; v++) {
        if (graph[u][v]) {
            if (!visited[v]) {
                if (dfs(v, u, start, end)) {
                    return true;
                }
            } else if (v != parent) {
                start = u;
                end = v;
                return true;
            }
        }
    }
    return false;
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
        visited[i] = 0;
    }

    bool hasCycle = false;
    int start = -1, end = -1;

    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            if (dfs(i, -1, start, end)) {
                hasCycle = true;
                break;
            }
        }
    }

    cout << "\n--- DFS Result ---\n";
    if (hasCycle) {
        cout << "Cycle detected between vertices: " << start << " and " << end << endl;
    } else {
        cout << "No cycle found using DFS.\n";
    }

    return 0;
}
