#include <iostream>
#include <vector>
#include <stack>

using namespace std;

vector<int> color;
vector<int> comp;
stack<int> pila;

void dfs(int actual, vector<vector<int>> &adj, bool kosaraju)
{
    color[actual] = 1;
    for(auto hijo:adj[actual])
    {
        if(color[hijo] == 0)
        {
            comp[hijo] = comp[actual];
            dfs(hijo, adj, kosaraju);
        }
    }
    color[actual] = 2;
    if(!kosaraju) pila.push(actual);
}

int main()
{
    int n, m;
    scanf("%d%d",&n,&m);
    color.resize(n+1, 0);
    comp.resize(n+1);
    vector<vector<int>> adj(n+1);
    vector<vector<int>> adj_invertido(n+1);

    for(int i = 1; i <= n; i++) comp[i] = i;

    for(int i = 0; i < m; i++)
    {
        int a, b;
        scanf("%d%d",&a,&b);
        adj[a].push_back(b);
        adj_invertido[b].push_back(a);
    }

    // Kosaraju
    // Primer corrida de dfs
    for(int i = 1; i <= n; i++) if(color[i] == 0) dfs(i, adj, false);

    // DFS sobre grafo invertido
    color.clear();
    color.resize(n+1, 0);
    for(int i = 1; i <= n; i++) comp[i] = i;
    while (pila.size()) {
        int nodo = pila.top();
        pila.pop();
        dfs(nodo, adj_invertido, true);
    }

    // verificamos que aristas nos sirven y contamos las entradas a cada componente
    vector<int>entradas(n+1, 0);
    for (int a = 1; a <= n; a++)
    {
        for (auto b : adj[a])
            if(comp[a] != comp[b]) entradas[comp[b]]++;
    }
    
    vector<int> result;
    for (int i = 1; i <= n; i++) {
        if (comp[i] == i && entradas[i] == 0) result.push_back(i);
    }

    printf("%d\n", result.size());
    for (int i = 0; i < result.size(); i++) printf("%d ", result[i]);

    return 0;
}