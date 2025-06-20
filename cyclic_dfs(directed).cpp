#include <iostream>
using namespace std;

const int MAX = 100;
int graph[MAX][MAX], n;
bool visited[MAX], recStack[MAX];
int parent[MAX];

bool dfs(int u) {
    visited[u] = true;
    recStack[u] = true;

    for (int v = 0; v < n; v++) {
        if (graph[u][v]) {
            if (!visited[v]) {
                parent[v] = u;
                if (dfs(v)) return true;
            } else if (recStack[v]) {
                cout << "Cycle detected: ";
                int cur = u;
                cout << v;
                while (cur != v && cur != -1) {
                    cout << " -> " << cur;
                    cur = parent[cur];
                }
                cout << " -> " << v << endl;
                return true;
            }
        }
    }

    recStack[u] = false;
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

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            graph[i][j] = readIntCell(i, j);

    for (int i = 0; i < n; i++) {
        visited[i] = false;
        recStack[i] = false;
        parent[i] = -1;
    }

    bool hasCycle = false;
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            if (dfs(i)) {
                hasCycle = true;
                break;
            }
        }
    }

    if (!hasCycle) cout << "No cycle found using DFS.\n";
    return 0;
}
