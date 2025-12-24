struct BinaryLiftingEdge{
    static const ll LOG = 20;
    ll n;
    vector<vector<pii>> adj;
    vector<vi> up, dp;
    vi depth;

    const ll UNIT = 0; // UNIT para máximo

    BinaryLiftingEdge(ll n) : n(n) {
        adj.resize(n);
        up.assign(n, vi(LOG));
        dp.assign(n, vi(LOG));
        depth.assign(n, 0);
    }

    void add_edge(ll u, ll v, ll w) {
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    ll fn(ll a, ll b){
        return max(a, b);
    }

    void dfs(ll v, ll p, ll w) {
        up[v][0] = p;
        dp[v][0] = w;
        for (ll i = 1; i < LOG; i++) {
            up[v][i] = up[ up[v][i-1] ][i-1];
            dp[v][i] = fn(dp[v][i-1], dp[ up[v][i-1] ][i-1]);
        }
        for (auto [to, weight] : adj[v]) {
            if (to == p) continue;
            depth[to] = depth[v] + 1;
            dfs(to, v, weight);
        }
    }

    void build(ll root){
        dfs(root, root, UNIT);
    }

    ll lift(ll &v, ll k) {
        ll res = UNIT;
        for (ll i = 0; i < LOG; i++) {
            if ((k & (1 << i)) == 0) continue;
            res = fn(res, dp[v][i]);
            v = up[v][i];
        }
        return res;
    }

    ll query(ll u, ll v) {
        ll res = UNIT;
        if (depth[u] < depth[v]) swap(u, v);
        res = fn(res, lift(u, depth[u] - depth[v]));
        if (u == v) return res;
        for (ll i = LOG - 1; i >= 0; i--) {
            if (up[u][i] == up[v][i]) continue;
            res = fn(res, dp[u][i]);
            res = fn(res, dp[v][i]);
            u = up[u][i];
            v = up[v][i];
        }
        res = fn(res, dp[u][0]);
        res = fn(res, dp[v][0]);
        return res;
    }

    ll lca(ll u, ll v) {
        if (depth[u] < depth[v]) swap(u, v);
        lift(u, depth[u] - depth[v]);
        if (u == v) return u;
        for (ll i = LOG - 1; i >= 0; i--) {
            if (up[u][i] == up[v][i]) continue;
            u = up[u][i];
            v = up[v][i];
        }
        return up[u][0];
    }
};

struct dsu {
    vector<int> p, rnk;
    dsu(int n) : p(n), rnk(n, 1) {
        iota(p.begin(), p.end(), 0);
    }
    int find(int x) {
        return p[x] == x ? x : p[x] = find(p[x]);
    }
    bool join(int a, int b) {
        a = find(a); b = find(b);
        if (a == b) return false;
        if (rnk[a] < rnk[b]) swap(a, b);
        p[b] = a;
        rnk[a] += rnk[b];
        return true;
    }
};
