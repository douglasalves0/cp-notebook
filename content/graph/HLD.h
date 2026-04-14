// sample hld code that updates by summing into a range
// vertices are 0-indexed
// the root of hld is vertex 0
//
// to use this you SHOULD update
// 1. UNIT
// 2. LAZY_INVALID
// 3. f function
// 4. segtree push function
// 5. segtree update function
//
// usage:
// HLD<false> hld(adj); to define an HLD with weights on vertices
// HLD<true> hld(adj);  to define an HLD with weights on edges

#define all(x) begin(x), end(x)
#define sz(x) (ll)(x).size()
typedef long long ll;
typedef vector<ll> vi;

typedef ll TT; // type of tree nodes
static constexpr TT UNIT = 0;
vector<TT> tree;

static constexpr ll LAZY_INVALID = 0;
vector<ll> lazy;

// update this function as you wish
TT f(TT l, TT r){ return l + r; }

struct seg {
    ll n;
    seg(ll N) {
        n = N;
        tree.resize(4*n, UNIT);
        lazy.resize(4*n, LAZY_INVALID);
    }
    void push(ll no, ll l, ll r){
        if(lazy[no] == LAZY_INVALID) return;
        // update tree[no] using lazy[no]
        tree[no] += (r - l + 1) * lazy[no];
        if(l < r){
            // update lazy[no*2] using lazy[no]
            lazy[no*2] += lazy[no];
            // update lazy[no*2+1] using lazy[no]
            lazy[no*2+1] += lazy[no];
        }
        lazy[no] = LAZY_INVALID;
    }
    void update(ll no, ll l, ll r, ll x, ll y, TT v) {
        push(no, l, r);
        if(x > y || r < x || y < l) return;
        if(x <= l && r <= y){
            // update lazy[no] using v
            lazy[no] += v;
            push(no, l, r);
            return;
        }
        ll m = (l+r)/2;
        update(no*2, l, m, x, y, v);
        update(no*2+1, m+1, r, x, y, v);
        tree[no] = f(tree[no*2], tree[no*2+1]);
    }
    TT query(ll no, ll l, ll r, ll x, ll y) {
        push(no, l, r);
        if(x > y || r < x || y < l) return UNIT;
        if(x <= l && r <= y) return tree[no];
        ll m = (l+r)/2;
        return f(query(no*2, l, m, x, y), query(no*2+1, m+1, r, x, y));
    }
    void update(ll l, ll r, TT v){ update(1, 0, n-1, l, r, v); }
    TT query(ll l, ll r) { return query(1, 0, n-1, l, r); }
};

// This runs a dfs from 0, so your graph should be 0-indexed
// At the start, all the vertices have the default value of the segtree
template <bool VALS_EDGES> struct HLD {
	ll N, tim = 0;
	vector<vi> adj;
	vi par, siz, depth, rt, pos;
    seg tree;
	HLD(vector<vi> adj_)
		: N(sz(adj_)), adj(adj_), par(N, -1), siz(N, 1), depth(N),
		  rt(N),pos(N), tree(N){ dfsSz(0); dfsHld(0); }
	void dfsSz(ll v) {
		if (par[v] != -1) adj[v].erase(find(all(adj[v]), par[v]));
		for (ll& u : adj[v]) {
			par[u] = v, depth[u] = depth[v] + 1;
			dfsSz(u);
			siz[v] += siz[u];
			if (siz[u] > siz[adj[v][0]]) swap(u, adj[v][0]);
		}
	}
	void dfsHld(ll v) {
		pos[v] = tim++;
		for (ll u : adj[v]) {
			rt[u] = (u == adj[v][0] ? rt[v] : u);
			dfsHld(u);
		}
	}
	template <class B> void process(ll u, ll v, B op) {
		for (; rt[u] != rt[v]; v = par[rt[v]]) {
			if (depth[rt[u]] > depth[rt[v]]) swap(u, v);
			op(pos[rt[v]], pos[v]);
		}
		if (depth[u] > depth[v]) swap(u, v);
		op(pos[u] + VALS_EDGES, pos[v]);
	}
	void updatePath(ll u, ll v, TT val) {
		process(u, v, [&](ll l, ll r) { tree.update(l, r, val); });
	}
	TT queryPath(ll u, ll v){
		TT res = UNIT;
		process(u, v, [&](ll l, ll r) { res = f(res, tree.query(l, r)); });
		return res;
	}
	TT querySubtree(ll v){
		return tree.query(pos[v] + VALS_EDGES, pos[v] + siz[v] - 1);
	}
    void updateSubtree(ll v, TT val){
        tree.update(pos[v] + VALS_EDGES, pos[v] + siz[v] - 1, val);
    }
};
