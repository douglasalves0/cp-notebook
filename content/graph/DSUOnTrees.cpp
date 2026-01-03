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
void upd(ll v, ll p, ll to_add){
    if(to_add); // add vertex v to the answer [MODIFY]
    else; // remove vertex v from the answer [MODIFY]
    for(ll u: graph[v]){
        if(u == p) continue;
        upd(u, v, to_add);
    }
}
// then call this second: dfs(root, -1, 0)
void dfs(ll v, ll p, ll keep){
    for(ll u: graph[v]){
        if(u == p || u == heavy[v]) continue;
        dfs(u, v, 0);
    }
    if(heavy[v] != -1) dfs(heavy[v], v, 1);
    for(ll u: graph[v]){
        if(u == p || u == heavy[v]) continue;
        upd(u, v, 1); // add everyone from u's subtree
    }
    // at this point you should have the answer calculated
    // to the v's subtree
    // [MODIFY]
    if(keep) return;
    for(ll u: graph[v]){
        if(u == p) continue;
        upd(u, v, 0); // remove everyone from u's subtree
    }
}
