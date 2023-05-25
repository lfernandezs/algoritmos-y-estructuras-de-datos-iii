#include <bits/stdc++.h>

#define x first
#define y second

using namespace std;

using ll = long long;
const ll inf = 1e18;

int n, limit, modems, cu, cv;
vector<tuple<double,int,int, int>> E;
struct DSU_by_rank{

    DSU_by_rank(int n){ for(int v = 0; v < n; v++) padre[v] = v;}

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


struct DSU_by_size{

    DSU_by_size(int n){ for(int v = 0; v < n; v++) padre[v] = v;}

    int find(int v){
        if(v == padre[v]) return v;
        return padre[v] = find(padre[v]);
    }

    void unite(int u, int v){
        u = find(u), v = find(v);
        if(u == v) return;
        if(rank[u] < rank[v]) swap(u,v);
        padre[v] = padre[u];
        rank[u] += rank[v];
    }
    int padre[1001];
    int rank[1001] = {0};
};


struct DSU_without_path_compression{

    DSU_without_path_compression(int n){ for(int v = 0; v < n; v++) padre[v] = v;}

    int find(int v){
        if(v == padre[v]) return v;
        return find(padre[v]);
    }

    void unite(int u, int v){
        u = find(u), v = find(v);
        if(u == v) return;
        if(rank[u] < rank[v]) swap(u,v);
        padre[v] = u;
        rank[u] = max(rank[u],rank[v]+1);
    }
    int padre[1001];
    int rank[1001] = {0};
};

void kruskal_by_rank(int caso){
    sort(E.begin(),E.end());
    int componentes = n;
    double resU = 0, resV = 0;
    DSU_by_rank dsu(n);
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

void kruskal_by_size(int caso){
    sort(E.begin(),E.end());
    int componentes = n;
    double resU = 0, resV = 0;
    DSU_by_size dsu(n);
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

void kruskal_without_path_compression(int caso){
    sort(E.begin(),E.end());
    int componentes = n;
    double resU = 0, resV = 0;
    DSU_without_path_compression dsu(n);
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

void modems_union_by_rank(ifstream& input_file) {
    int t, c = 0;
    input_file >> t;
    while(c++ < t)
    {
        pair<int,int> coordenadas[1001];
        input_file >> n >> limit >> modems >> cu >> cv;
        for(int i = 0; i < n; i++)
        {
            int a, b;
            input_file >> a >> b;
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
        kruskal_by_rank(c);
        E.clear();
    }
}

void modems_union_by_size(ifstream& input_file) {
    int t, c = 0;
    input_file >> t;
    while(c++ < t)
    {
        pair<int,int> coordenadas[1001];
        input_file >> n >> limit >> modems >> cu >> cv;
        for(int i = 0; i < n; i++)
        {
            int a, b;
            input_file >> a >> b;
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
        kruskal_by_size(c);
        E.clear();
    }
}


void modems_without_path_compression(ifstream& input_file) {
    int t, c = 0;
    input_file >> t;
    while(c++ < t)
    {
        pair<int,int> coordenadas[1001];
        input_file >> n >> limit >> modems >> cu >> cv;
        for(int i = 0; i < n; i++)
        {
            int a, b;
            input_file >> a >> b;
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
        kruskal_without_path_compression(c);
        E.clear();
    }
}