typedef vector<pii> vpii;
typedef pair<ll,ll> pii;
// parameters: 
//   - ll n --> number of vertices
//   - vector<pii> g[n+1] --> adjacency graph --> g[u] stores a pair {}
//   - ll m --> number of start vertices
//   - ll s[m] --> start vertices
//   - ll dis[n+1] --> distances from starting vertices to others
void dijkstra(ll n, vpii* g, ll m, ll* s, ll* dis){
    fill(dis, dis+(n+1), LLONG_MAX);
    set<pii> q;
    for(ll i=0;i<m;i++) dis[s[i]] = 0, q.insert({0, s[i]});
    while(!q.empty()){
        auto& [d, v] = *q.begin();
        for(auto& [u, w]: g[v]){
            if(d + w >= dis[u]) continue;
            q.erase({dis[u], u});
            dis[u] = d + w;
            q.insert({dis[u], u});
        }
        q.erase(q.begin());
    }
}
