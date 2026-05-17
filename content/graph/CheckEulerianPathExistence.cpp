// checks if an eulerian path starting at u and ending at v exists in an undirected graph
// u and v can assume -1 value if you don't want to specify the starting or ending vertice
//
// if u and v are -1 the function returns if any eulerian path exists
// if only u is -1 the function returns if there is any path that starts at any vertice and end in v
// if only v is true, it's similar to the above
vector<ll> graph[200010];
ll n;
bool eulerian_path_exists(ll u, ll v){
    vector<ll> odd;
    ll e = 0;
    for(ll i=1;i<=n;i++){
        e += graph[i].size();
        if(graph[i].size() % 2 == 0) continue;
        odd.push_back(i);
        if(odd.size() > 2) return 0;
    }
    auto cmp = [](ll x, ll y){ return x == -1 || y == -1 ? 1 : x == y; };
    if(!e) return cmp(u, v);
    ll cnt = 0, ok[n+1] = {0};
    function<void(ll)> dfs = [&](ll v){
        ok[v] = 1;
        for(ll u: graph[v]){
            cnt += 1;
            if(ok[u]) continue;
            dfs(u);
        }
    };
    for(int i=1;i<=n;i++){
        if(graph[i].empty()) continue;
        dfs(i);
        break;
    }
    if(cnt != e) return 0;
    if(odd.empty()){
        if(!cmp(u, v)) return 0;
        u = max(u, v);
        if(u != -1 && !ok[u]) return 0;
        return 1;
    }
    int x = odd[0], y = odd[1];
    if(!(cmp(u, x) && cmp(v, y)) && !(cmp(u, y) && cmp(v, x))) return 0;
    return ok[x] && ok[y];
}
