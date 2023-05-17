#include <bits/stdc++.h>

#define x first
#define y second

using namespace std;

using ll = long long;
const ll inf = 1e18;

int n, limit, modems, u, v;
vector<tuple<ll,int,int, int>> E;
pair<int, int> resultados[1001];
struct DSU{

    DSU(int n){
        padre = rank = vector<int>(n+1);
        for(int v = 1; v <= n; v++) padre[v] = v;
    }

    int find(int v){
        if(v == padre[v]) return v;
        return padre[v] = find(padre[v]);
    }

    void unite(int u, int v){
        u = find(u), v = find(v);
        if(u == v) return;
        if(rank[u] < rank[v]) swap(u,v);
        padre[v] = padre[u];
        rank[u] = max(rank[u],rank[v]+1);
    }

    vector<int> padre;
    vector<int> rank;
};

void kruskal(int caso){
    sort(E.begin(),E.end());
    int componentes = n;
    ll resU = 0, resV = 0;
    int aristas = 0;
    DSU dsu(n);
    for(auto [c,u,v,t] : E){
        //si (u,v) es arista segura
        if(dsu.find(u) != dsu.find(v)){
            // agregar
            dsu.unite(u,v);
            //aristas++;
            componentes--;
            if(t == 0) resU += c; else resV += c;
        }
        if(componentes == modems) break;
    }
    /*
    if(aristas == n-1) cout<<res<<endl;
    else cout<<"IMPOSSIBLE\n";
    */
    //printf("Caso #%d: %.3f %.3f\n", caso, float(resU), float(resV));
    resultados[caso].first = resU;
    resultados[caso].second = resV;
}

int dist(pair<int,int> a, pair<int,int>b)
{
    return sqrt((b.x - a.x)*(b.x - a.x) + (b.y - a.y)*(b.y - a.y));
}
int main() {
    int t, c = 0;
    scanf("%d", &t);
    while(c++ < t)
    {
        pair<int,int> coordenadas[1001];
        scanf("%d%d%d%d%d", &n, &limit, &modems, &u, &v);
        for(int i = 0; i < n; i++)
        {
            int a, b;
            cin >> a >> b;
            coordenadas[i+1].x = a;
            coordenadas[i+1].y = b;
        }
        //crear aristas
        for(int i = 1; i <= n; i++)
        {
            for(int j = 1; j <= n; j++)
            {
                if(i != j)
                {
                    int distancia = dist(coordenadas[i], coordenadas[j]);
                    if(distancia > limit)
                        E.push_back({distancia*v, i, j, 1});
                    else
                    {
                        if(u <= v)
                            E.push_back({distancia * u, i, j, 0});
                        else E.push_back({distancia * v, i, j, 1});
                    }
                }
            }
        }
        kruskal(c);
        E.clear();
    }
    for(int i = 1;i <= t; i++)
    {
        printf("Caso #%d: %.3f %.3f\n", i, float(resultados[i].first), float(resultados[i].second));
    }
    return 0;
}