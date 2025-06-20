#include <iostream>
#include <queue>
using namespace std;

const int MAX = 100;
int graph[MAX][MAX];
int parent[MAX];
bool visited[MAX];
int n;

bool bfs(int start) {
    queue<int> q;
    visited[start] = true;
    parent[start] = -1;
    q.push(start);

    while (!q.empty()) {
        int u = q.front(); q.pop();

        for (int v = 0; v < n; v++) {
            if (graph[u][v]) {
                if (!visited[v]) {
                    visited[v] = true;
                    parent[v] = u;
                    q.push(v);
                } else if (v != parent[u]) {
                    cout << "Cycle detected: ";
                    int path[MAX], len = 0;
                    path[len++] = v;
                    int cur = u;
                    while (cur != -1 && cur != v && len < MAX) {
                        path[len++] = cur;
                        cur = parent[cur];
                    }
                    path[len++] = v;
                    for (int i = len - 1; i >= 0; i--) {
                        cout << path[i];
                        if (i > 0) cout << " -> ";
                    }
                    cout << endl;
                    return true;
                }
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
            cout << "Invalid input!! Please enter a number.\n";
        } else if (value != 0 && value != 1) {
            cout << "Invalid value!! Only 0 or 1 allowed.\n";
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
        cout << "Invalid input!! Enter a valid number between 1 and " << MAX << ": ";
    }

    cout << "\nEnter adjacency matrix:\n";
    for (int i = 0; i < n; i++){
        cout << "\n--- Row " << i << " ---\n";
        for (int j = 0; j < n; j++)
            graph[i][j] = readIntCell(i, j);
    }
    for (int i = 0; i < n; i++) {
        visited[i] = false;
        parent[i] = -1;
    }

    bool hasCycle = false;
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            if (bfs(i)) {
                hasCycle = true;
                break;
            }
        }
    }

    if (!hasCycle) {
        cout << "No cycle found using BFS.\n";
    }

    return 0;
}
