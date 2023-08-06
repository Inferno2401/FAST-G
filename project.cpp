#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

const int INF = INT_MAX;

class HungarianAlgorithm {
private:
    int n, m;
    vector<vector<int>> cost;
    vector<int> u, v, p, way;
    vector<bool> used;

public:
    HungarianAlgorithm(int n, int m) : n(n), m(m) {
        cost.resize(n + 1, vector<int>(m + 1));
        u.resize(n + 1);
        v.resize(m + 1);
        p.resize(m + 1);
        way.resize(m + 1);
        used.resize(m + 1);
    }

    void addEdge(int a, int b, int weight) {
        cost[a][b] = weight;
    }

    int hungarian() {
        for (int i = 1; i <= n; i++) {
            p[0] = i;
            int j0 = 0;
            vector<int> minv(m + 1, INF);
            vector<bool> used(m + 1, false);
            do {
                used[j0] = true;
                int i0 = p[j0], delta = INF, j1;
                for (int j = 1; j <= m; j++) {
                    if (!used[j]) {
                        int cur = cost[i0][j] - u[i0] - v[j];
                        if (cur < minv[j]) {
                            minv[j] = cur;
                            way[j] = j0;
                        }
                        if (minv[j] < delta) {
                            delta = minv[j];
                            j1 = j;
                        }
                    }
                }
                for (int j = 0; j <= m; j++) {
                    if (used[j]) {
                        u[p[j]] += delta;
                        v[j] -= delta;
                    } else {
                        minv[j] -= delta;
                    }
                }
                j0 = j1;
            } while (p[j0] != 0);

            do {
                int j1 = way[j0];
                p[j0] = p[j1];
                j0 = j1;
            } while (j0);
        }

        return -v[0];
    }
};

int main() {
    // Example usage
    int n = 4; // Number of vertices in the first partite set
    int m = 4; // Number of vertices in the second partite set

    HungarianAlgorithm hungarian(n, m);

    // Example edges with weights
    hungarian.addEdge(1, 1, 1);
    hungarian.addEdge(1, 2, 2);
    hungarian.addEdge(1, 3, 3);
    hungarian.addEdge(2, 1, 3);
    hungarian.addEdge(2, 2, 2);
    hungarian.addEdge(2, 3, 1);
    hungarian.addEdge(3, 1, 2);
    hungarian.addEdge(3, 2, 3);
    hungarian.addEdge(3, 3, 1);
    hungarian.addEdge(4, 1, 5);
    hungarian.addEdge(4, 2, 6);
    hungarian.addEdge(4, 3, 4);

    int maxMatchingWeight = hungarian.hungarian();
    cout << "Maximum matching weight: " << maxMatchingWeight << endl;

    return 0;
}
