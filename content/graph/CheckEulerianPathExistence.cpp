// checks if an eulerian path starting at u and ending at v exists in an undirected graph
// u and v can assume -1 value if you don't want to specify the starting or ending vertice
//
// if u and v are -1 the function returns if any eulerian path exists
// if only u is -1 the function returns if there is any path that starts at any vertice and end in v
// if only v is true, it's similar to the above
vector<ll> graph[200010];
ll n;
bool eulerian_path_exists(ll u, ll v){
    vector<ll> impares;
    ll edges = 0;
    for(ll i=1;i<=n;i++){
        edges += graph[i].size();
        if(graph[i].size() % 2 == 0) continue;
        impares.push_back(i);
        if(impares.size() > 2) return 0;
    }
    auto cmp = [](ll x, ll y){ return x == -1 || y == -1 ? 1 : x == y; };
    if(!edges) return cmp(u, v);
    ll cnt = 0, found[n+1] = {0};
    function<void(ll)> dfs = [&](ll v){
        found[v] = 1;
        for(ll u: graph[v]){
            cnt += 1;
            if(found[u]) continue;
            dfs(u);
        }
    };
    for(int i=1;i<=n;i++){
        if(graph[i].empty()) continue;
        dfs(i);
        break;
    }
    if(cnt != edges) return 0;
    if(impares.empty()){
        if(!cmp(u, v)) return 0;
        u = max(u, v);
        if(u != -1 && !found[u]) return 0;
        return 1;
    }
    int x = impares.front();
    int y = impares.back();
    if(!(cmp(u, x) && cmp(v, y)) && !(cmp(u, y) && cmp(v, x))) return 0;
    return found[x] && found[y];
}
