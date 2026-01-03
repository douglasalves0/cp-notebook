const ll N = 1e6 + 10; // maybe you want a smaller number
vector<ll> graph[N];
ll sz[N], heavy[N];
// call this first: pre(root, -1)
void pre(ll v, ll p){
    sz[v] = 1, heavy[v] = -1;
    for(ll u: graph[v]){
        if(u == p) continue;
        pre(u, v);
        sz[v] += sz[u];
        if(heavy[v] == -1 || sz[u] > sz[heavy[v]]) heavy[v] = u;
    }
}
void upd(ll v, ll p, ll to_ignore, ll to_add){
    if(to_add){ /* add vertex v to the answer [MODIFY] */ }
    else{ /* remove vertex v from the answer [MODIFY] */ }
    for(ll u: graph[v]){
        if(u == p || u == to_ignore) continue;
        upd(u, v, to_ignore, to_add);
    }
}
// then call this second: dfs(root, -1, 0)
void dfs(ll v, ll p, ll keep){
    for(ll u: graph[v]){
        if(u == p || u == heavy[v]) continue;
        dfs(u, v, 0);
    }
    if(heavy[v] != -1) dfs(heavy[v], v, 1);
    upd(v, p, heavy[v], 1); // add everyone from v's subtree, except the heavy[v]'s subtree
    // at this point you should have the answer calculated
    // to the v's subtree
    // [MODIFY]
    if(keep) return;
    upd(v, p, -1, 0); // remove everyone from v's subtree
}
