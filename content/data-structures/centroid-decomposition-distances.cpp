// para usar tk deve estar todo zerado e deve-se chamar cdfs();
// retorna apenas o array de pais na arvore de centroid decomposition
// dis[{u, v}] não é definido para todos os pares
// apenas é definido se v é vertice do componente de u quando u é centroid
const int N = 2e5+10;
vector<int> g[N];
int n;
int tk[N];
int fat[N]; // father in centroid decomposition
int szt[N]; // size of subtree
map<pair<int,int>, int> dis;
int calcsz(int v, int f){
    szt[v] = 1;
    for(int u: g[v]) if(u != f && !tk[u]) szt[v] += calcsz(u, v);
    return szt[v];
}
void dfs(int s, int v, int p, int lvl){
    dis[{s, v}] = lvl;
    for(int u: g[v]){
        if(tk[u] || u == p) continue;
        dfs(s, u, v, lvl + 1);
    }
}
void cdfs(int v = 0, int f = -1, int sz = -1){ // O(n log n)
    if(sz < 0) sz = calcsz(v, -1);
    for(int u: g[v]){
        if(!tk[u] && szt[u] * 2 >= sz){
            szt[v] = 0;
            cdfs(u, f, sz);
            return;
        }
    }
    dfs(v, v, -1, 0);
    tk[v] = 1;
    fat[v] = f;
    for(int u: g[v]) if(!tk[u]) cdfs(u, v);
}
