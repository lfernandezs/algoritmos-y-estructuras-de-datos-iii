#include <iostream>
#include <vector>

using namespace std;
vector<vector<int> >adj;
vector<int> parent;
vector<bool>visitado;
vector<int>d;
vector<int>comp;
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
    /*
    for(int i = 1; i <=n; i++)
        cout << d[i]<< " ";
    cout << endl; 
*/
    for(int a = 1; a <= n; a++)
    {
        for(int i = 0; i < adj[a].size(); i++)
        {
            int b = adj[a][i];
            ///Caso: hay una arista que apunta a una raiz y son de distintas comp
            if(parent[b] == -1 && comp[a] != comp[b])
            {
                parent[b] = a;
            }
        }
    }
    int c = 0;
    vector<int>solucion;
    for(int i = 1; i <= n; i++)
    {
        if(parent[i] == -1)
        {
            c++;
            solucion.push_back(i);
        }
    }
    cout << c << endl;
    for(auto domino:solucion)
    {
        cout << domino << " ";
    }
    return 0;
}