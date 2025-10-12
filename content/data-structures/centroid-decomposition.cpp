// para usar tk deve estar todo zerado e deve-se chamar cdfs();
// retorna apenas o array de pais na arvore de centroid decomposition
const int N = 2e5+10;
vector<int> g[N];
int n;
int tk[N];
int fat[N]; // father in centroid decomposition
int szt[N]; // size of subtree
int calcsz(int v, int f){
    szt[v] = 1;
    for(int u: g[v]) if(u != f && !tk[u]) szt[v] += calcsz(u, v);
    return szt[v];
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
    tk[v] = 1;
    fat[v] = f;
    for(int u: g[v]) if(!tk[u]) cdfs(u, v);
}