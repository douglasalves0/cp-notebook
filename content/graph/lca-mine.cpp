typedef vector<int> vi;
const int MAXN = 2e5;
const int MAXUP = 21;
struct LCA{
    int f[MAXN+1][MAXUP];
    int lvl[MAXN+1];
    void build(int n, vi* g, int root){
        lvl[root] = 0;
        dfs(root, g, root);
        for(int j=1;j<MAXUP;j++){
            for(int i=1;i<=n;i++){
                f[i][j] = f[f[i][j-1]][j-1];
            }
        }
    }
    void dfs(int v, vi* g, int p){
        f[v][0] = p;
        for(int u: g[v]){
            if(u == p) continue;
            lvl[u] = lvl[v] + 1;
            dfs(u, g, v);
        }
    }
    int lca(int u, int v){
        if(lvl[u] < lvl[v]) swap(u, v);
        for(int i=MAXUP-1;i>=0;i--){
            if(lvl[u] - (1 << i) < lvl[v]) continue;
            u = f[u][i];
        }
        if(u == v) return v;
        for(int i=MAXUP-1;i>=0;i--){
            if(f[u][i] == f[v][i]) continue;
            u = f[u][i];
            v = f[v][i];
        }
        return f[v][0];
    }
    int dis(int a, int b){
        int c = lca(a, b);
        return lvl[a] + lvl[b] - 2 * lvl[c];
    }
};
