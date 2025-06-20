#include <iostream>
#include <queue>
using namespace std;

const int MAX = 100;
int graph[MAX][MAX], n, inDegree[MAX];

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

    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            graph[i][j] = readIntCell(i, j);
        }
    }
    for (int i = 0; i < n; i++){ inDegree[i] = 0;
    }
    for (int u = 0; u < n; u++){
        for (int v = 0; v < n; v++){
            if (graph[u][v]){ inDegree[v]++;}
        }
    }
    queue<int> q;
    for (int i = 0; i < n; i++)
        if (inDegree[i] == 0){ q.push(i);}

    int count = 0;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        count++;
        for (int v = 0; v < n; v++) {
            if (graph[u][v]) {
                inDegree[v]--;
                if (inDegree[v] == 0) q.push(v);
            }
        }
    }

    if (count != n){
        cout << "Cycle detected using BFS.\n";
    }else{
        cout << "No cycle found using BFS.\n";
    }
    return 0;
}
