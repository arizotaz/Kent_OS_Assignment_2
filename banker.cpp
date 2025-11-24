#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int main() {
    ifstream fin("input.txt");
    if (!fin) {
        cout << "Error: Could not open input.txt\n";
        return 1;
    }

    int n, m;
    fin >> n >> m; // number of processes (n=5) and resources (m=3)

    vector<vector<int>> allocation(n, vector<int>(m));
    vector<vector<int>> maximum(n, vector<int>(m));
    vector<vector<int>> need(n, vector<int>(m));
    vector<int> available(m);

    // Read Allocation
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            fin >> allocation[i][j];

    // Read Max
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            fin >> maximum[i][j];

    // Read Available
    for (int j = 0; j < m; j++)
        fin >> available[j];

    fin.close();

    // Compute Need matrix
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            need[i][j] = maximum[i][j] - allocation[i][j];

    vector<int> safeSequence(n);
    vector<bool> finished(n, false);
    int work[3];
    for (int i = 0; i < m; i++) work[i] = available[i];

    int count = 0;

    while (count < n) {
        bool found = false;
        for (int i = 0; i < n; i++) {
            if (!finished[i]) {
                int j;
                for (j = 0; j < m; j++)
                    if (need[i][j] > work[j])
                        break;

                if (j == m) {
                    for (int k = 0; k < m; k++)
                        work[k] += allocation[i][k];

                    safeSequence[count++] = i;
                    finished[i] = true;
                    found = true;
                }
            }
        }
        if (!found) {
            cout << "The system is NOT in a safe state.\n";
            return 0;
        }
    }

    cout << "The system *IS* in a safe state.\nSafe sequence: ";
    for (int i = 0; i < n; i++) {
        cout << "P" << safeSequence[i];
        if (i < n - 1) cout << " -> ";
    }
    cout << endl;

    return 0;
}
