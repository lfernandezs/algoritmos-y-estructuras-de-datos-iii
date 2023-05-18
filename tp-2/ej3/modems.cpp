#include <bits/stdc++.h>

#define x first
#define y second

using namespace std;

using ll = long long;
const ll inf = 1e18;

int n, limit, modems, cu, cv;
vector<tuple<double,int,int, int>> E;
struct DSU{

    DSU(int n){ for(int v = 0; v < n; v++) padre[v] = v;}

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
    int padre[1001];
    int rank[1001] = {0};
};

void kruskal(int caso){
    sort(E.begin(),E.end());
    int componentes = n;
    double resU = 0, resV = 0;
    DSU dsu(n);
    for(auto [c,u,v,t] : E){
        //si (u,v) es arista segura
        if(dsu.find(u) != dsu.find(v)){
            dsu.unite(u,v);
            if(t == 0) resU += c; else resV += c;
            componentes--;
            if(componentes == modems) break;
        }
    }
    printf("Caso #%d: %.3f %.3f\n", caso, resU, resV);
}

double dist(pair<int,int> a, pair<int,int>b)
{
    return (double)sqrt((b.x - a.x)*(b.x - a.x)+(b.y - a.y)*(b.y - a.y));
}
int main() {
    int t, c = 0;
    scanf("%d", &t);
    while(c++ < t)
    {
        pair<int,int> coordenadas[1001];
        scanf("%d%d%d%d%d", &n, &limit, &modems, &cu, &cv);
        for(int i = 0; i < n; i++)
        {
            int a, b;
            scanf("%d%d", &a, &b);
            coordenadas[i] = {a,b};
        }
        //crear aristas
        for(int i = 0; i < n; i++)
        {
            for(int j = i + 1; j < n; j++)
            {
                double d = dist(coordenadas[i], coordenadas[j]);
                if(d > limit)
                    E.push_back({d*cv, i, j, 1});
                else E.push_back({d*cu, i, j, 0});
            }
        }
        kruskal(c);
        E.clear();
    }
    return 0;
}
