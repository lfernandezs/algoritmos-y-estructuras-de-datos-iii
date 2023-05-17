#include <iostream>
#include <vector>
#include <iomanip>

#define ll long long
using namespace std;
ll n;
vector<vector<int>> adj;
vector<pair<int,int> > aristas;
vector<bool> visitado;
vector<int> tin, low;
vector<int>padre;
int timer;
vector<vector<int> > nuevoAdj;
vector<bool>color;

void IS_BRIDGE(int a, int b)
{
    return;
}

void dfs(int v, int p = -1) {
    visitado[v] = true;
    tin[v] = low[v] = timer++;
    for (int to : adj[v]) {
        if (to == p) continue;
        if (visitado[to]) {
            low[v] = min(low[v], tin[to]);
        } else {
            padre[to] = v;
            dfs(to, v);
            low[v] = min(low[v], low[to]);
            if (low[to] > tin[v])
                IS_BRIDGE(v, to);
            else aristas.push_back({v, to}), aristas.push_back({to,v});
        }
    }
}

void find_bridges() {
    timer = 0;
    visitado.assign(n+1, false);
    tin.assign(n+1, -1);
    low.assign(n+1, -1);
    padre.assign(n+1, -1);
    for (int i = 0; i < n; ++i) {
        if (!visitado[i])
            dfs(i);
    }
}
long long d(int actual)
{
    long long nodos = 0;
    color[actual] = true;
    for(int hijo: nuevoAdj[actual])
    {
        if(!color[hijo]) nodos += d(hijo);
    }
    return 1 + nodos;
}
int main()
{
    int m;
    cin >> n >> m;
    
    adj.resize(n+1);
    for(int i = 0; i < m; i++)
    {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    find_bridges();
    
    for(int i = 1; i <= n; i++)
    {
        for(auto x: adj[i])
        {
            if(padre[i] != x && padre[x] != i)
                aristas.push_back({i,x});
        }
    }
    ///Armado grafo sin los puentes
    nuevoAdj.resize(n+1);
    color.resize(n+1);
    for(auto x: aristas)
    {
        nuevoAdj[x.first].push_back(x.second);
    }
    long long ganar = 0;
    //Conteo de la cantidad de nodos por componente
    //cout << "Componentes: " << endl;
    for(int i = 1; i <=n; i++)
    {
        if(!color[i])
        {
            long long c = d(i);
            ganar += (c * (c-1))/2;
            //cout << c << endl;
        }
    }
    long long jugadas = (n*(n-1))/2;
    double probabilidad = 1 - ((ganar*1.0)/jugadas);
    //cout << ganar << " " << jugadas << endl;
    printf("%.5f\n", probabilidad);
    return 0;
}