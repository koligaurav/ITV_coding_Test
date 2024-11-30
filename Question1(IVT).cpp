#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

class BollywoodCollaboration {
public:
    // BFS function to check if an augmenting path exists
    bool bfs(vector<vector<int>> &graph, vector<int> &match, vector<int> &dist, int n) {
        queue<int> q;
        for (int i = 1; i <= n; ++i) {
            if (match[i] == -1) {
                dist[i] = 0;
                q.push(i);
            } else {
                dist[i] = -1;
            }
        }

        bool found = false;

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            for (int v : graph[u]) {
                if (match[v] == -1) {
                    found = true; 
                } else if (dist[match[v]] == -1) {
                    dist[match[v]] = dist[u] + 1;
                    q.push(match[v]);
                }
            }
        }

        return found;
    }

    // Function to find augmenting paths using BFS
    bool dfs(int u, vector<vector<int>> &graph, vector<int> &match, vector<int> &dist) {
        for (int v : graph[u]) {
            if (match[v] == -1 || (dist[match[v]] == dist[u] + 1 && dfs(match[v], graph, match, dist))) {
                match[u] = v;
                match[v] = u;
                return true;
            }
        }
        dist[u] = -1; // Mark as not part of the augmenting path
        return false;
    }

    int maxMovies(vector<vector<int>> &graph, int n) {
        vector<int> match(n + 1, -1);
        vector<int> dist(n + 1, -1);  
        int result = 0;

        
        while (bfs(graph, match, dist, n)) {
            for (int i = 1; i <= n; ++i) {
                if (match[i] == -1 && dfs(i, graph, match, dist)) {
                    result++;
                }
            }
        }

        return result;
    }
};

int main() {
    int n;
    cin >> n; 
    vector<vector<int>> preferences(n + 1);

   
    for (int i = 1; i <= n; ++i) {
        int num;
        while (cin >> num) {
          // Input ends with 0 for each superstar
            if (num == 0) break; 
            preferences[i].push_back(num);
        }
    }

    //mutual prefrerance graph
    vector<vector<int>> graph(n + 1);
    for (int i = 1; i <= n; ++i) {
        for (int j : preferences[i]) {
            // Check mutual willingness
            if (find(preferences[j].begin(), preferences[j].end(), i) != preferences[j].end()) {
                graph[i].push_back(j);
            }
        }
    }

    for (int i = 1; i <= n; ++i) {
        for (int j : graph[i]) {
            cout << j << " ";
        }
        cout << endl;
    }

    BollywoodCollaboration bc;
    cout << bc.maxMovies(graph, n) << endl;

    return 0;
}
