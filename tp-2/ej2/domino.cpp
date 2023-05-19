#include <iostream>
#include <vector>

using namespace std;
vector<vector<int>> adj;
vector<int> parent;
vector<bool> visitado;
vector<int> d;
vector<int> comp;
vector<int> orphans;
vector<int> result;


void dfs(int actual)
{
    visitado[actual] = true;
    for(auto hijo:adj[actual])
    {
        if(!visitado[hijo])
        {
            parent[hijo] = actual;
            d[hijo] = 1 + d[actual];
            comp[hijo] = comp[actual];
            dfs(hijo);
        }
    }
}

int main()
{
    int n, m;
    scanf("%d%d",&n,&m);
    adj.resize(n+1);
    parent.resize(n+1, -1);
    visitado.resize(n+1, false);
    d.resize(n+1, 0);
    comp.resize(n+1);

    for(int i = 1; i <= n; i++) comp[i] = i;

    for(int i = 0; i < m; i++)
    {
        int a, b;
        scanf("%d%d",&a,&b);
        adj[a].push_back(b);
    }

    for(int i = 1; i <= n; i++)
    {
        if(!visitado[i])
            dfs(i);
    }

    for (int i = 1; i <= n; i++) {
        if (parent[i] == -1) {
            orphans.push_back(i);
            result.push_back(i);
        }
    }

    parent.resize(n+1, -1);
    visitado.resize(n+1, false);

    for (auto orphan:orphans) {
        dfs(orphan);
    }

    // El resto son componentes fuertemente conexas (creo)
    for (int i = 1; i <= n; i++) {
        if (!visitado[i]) {
            result.push_back(i);
            dfs(i);
        }
    }

    cout << result.size() << endl;
    for (int i = 0; i < result.size(); i++) {
        if (i != result.size() - 1) {
            cout << result[i] << " ";
        } else {
            cout << result[i] << endl;
        }
    }

    return 0;
}