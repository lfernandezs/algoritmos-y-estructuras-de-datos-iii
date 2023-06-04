#include <iostream>
#include <vector>
#include <math.h>
#include <queue>

using namespace std;

typedef int vertex;
typedef int cost;


vector<cost> dijkstra(int n, int s, vector<vector<pair<vertex, cost>>> &adj) {
    vector<cost> distance(n + 1, (int)INFINITY);
    vector<bool> processed(n + 1, false);
    priority_queue<pair<cost, vertex>> q;

    distance[s] = 0;
    q.push({0, s});

    while (!q.empty()) {
        int a = q.top().second; q.pop();
        if (processed[a]) continue;
        processed[a] = true;
        for (auto u: adj[a]) {
            vertex b = u.first;
            cost w = u.second;
            if (distance[a] + w < distance[b]) {
                distance[b] = distance[a] + w;
                q.push({-distance[b], b});
            }
        }
    }

    return distance;
}

int main() {
    int casos;
    cin >> casos;

    for (int c = 0; c < casos; c++) {
        int n, m, k, s, t;
        cin >> n >> m >> k >> s >> t;

        vector<vector<pair<vertex, cost>>> adj(n + 1);
        vector<vector<pair<vertex, cost>>> adj_inv(n + 1);
        for (int i = 0; i < m; i++) {
            int d, c, l;
            cin >> d >> c >> l;
            adj[d].push_back({c, l});
            adj_inv[c].push_back({d, l});
        }

        vector<cost> distance_from_s = dijkstra(n, s, adj);
        vector<cost> distance_from_t = dijkstra(n, t, adj_inv);

        int minimum_distance = distance_from_s[t];

        for (int i = 0; i < k; i++) {
            int u, v, q;
            cin >> u >> v >> q;

            int distance = distance_from_s[u] + q + distance_from_t[v];
            if (distance < minimum_distance) {
                minimum_distance = distance;
            }
        }

        if (minimum_distance == INFINITY) {
            cout << "-1" << endl;
        } else {
            cout << minimum_distance << endl;
        }
    }
    return 0;
}