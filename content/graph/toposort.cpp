typedef vector<ll> vi;
const ll N = 2e5 + 10;
ll n;
vi graph[N]; // adjacency list (1-indexed)
pair<vi,vi> toposort(){
    vi ans; // topological order
    vi idx(n+1); // idx[v] = index of vertex v on the topological order (0-indexed)
    vi deg(n+1);
    for(ll v=1;v<=n;v++) for(ll u: graph[v]) deg[u] += 1;
    queue<ll> q;
    for(ll i=1;i<=n;i++) if(!deg[i]) q.push(i);
    while(!q.empty()){
        ll v = q.front();
        q.pop();
        idx[v] = ans.size();
        ans.push_back(v);
        for(ll u: graph[v]){
            deg[u] -= 1;
            if(deg[u] == 0) q.push(u);
        }
    }
    return {ans, idx};
} // if ans.size() < n, there is no answer, otherwise, ans is the topological order
