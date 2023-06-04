#include <iostream>
#include <vector>

using namespace std;
long long n, m;
vector<vector<int> > adj;
vector<vector<int> > treeEdges;
vector<int> inferiorEn;
vector<int> superiorEn;
vector<int> color;
vector<int>memo;
vector<pair<int, int> > aristas;
vector<bool>visitado;
vector<vector<int> > nuevoAdj;
void dfs(int actual, int padre = -1)
{
    color[actual] = 1;
    for(int hijo: adj[actual])
    {
        if(color[hijo] == 0)
        {
            treeEdges[actual].push_back(hijo);
            dfs(hijo, actual);
        }
        else if(color[hijo] == 1 && hijo != padre)
        {
            inferiorEn[actual]++;
            superiorEn[hijo]++;
            aristas.push_back({actual, hijo});
        }
    }
    color[actual] = 2;
}

int cubren(int v, int p = -1)
{
    if (memo[v] != -1) return memo[v];
    int res = 0;
    res += inferiorEn[v];
    res -= superiorEn[v];
    for (int hijo : treeEdges[v])
    {
        int BE = cubren(hijo, v);
        if (hijo != p) res += BE;
        if(BE != 0) aristas.push_back({v,hijo});
    }
    memo[v] = res;
    return res;
}
long long d(int actual)
{
    long long nodos = 0;
    visitado[actual] = true;
    for(int hijo: nuevoAdj[actual])
    {
        if(!visitado[hijo]) nodos += d(hijo);
    }
    return 1 + nodos;
}

int main()
{
    scanf("%lld%lld",&n,&m);
    adj.resize(n+1);
    treeEdges.resize(n+1);
    inferiorEn.resize(n+1, 0);
    superiorEn.resize(n+1, 0);
    color.resize(n+1, 0);
    memo.resize(n+1, -1);
    visitado.resize(n+1, false);
    for(int i = 0; i < m; i++)
    {
        int a, b;
        scanf("%d%d",&a,&b);
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    for(int i = 1; i < n+1; i++) if(color[i] == 0) dfs(i);

    for(int i = 1; i < n+1; i++) cubren(i);
    
    nuevoAdj.resize(n+1);
    for(auto x: aristas)
    {
        nuevoAdj[x.first].push_back(x.second);
        nuevoAdj[x.second].push_back(x.first);
    }
    long long ganar = 0;
    for(int i = 1; i <=n; i++)
    {
        if(!visitado[i])
        {
            long long c = d(i);
            ganar += (c * (c-1))/2;
        }
    }
    long long jugadas = (n*(n-1))/2;
    double probabilidad = 1 - ((ganar*1.0)/jugadas);
    printf("%.5f\n", probabilidad);
    
    return 0;
}