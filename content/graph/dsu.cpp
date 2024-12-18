struct dsu {
    vector<int> p, rnk;
    dsu(int n) : p(n), rnk(n, 1) { iota(p.begin(), p.end(), 0); }
    int find(int x) { return p[x] == x ? x : p[x] = find(p[x]); }
    bool join(int a, int b) {
        a = find(a); b = find(b);
        if (a == b) return false;
        if (rnk[a] < rnk[b]) swap(a, b);
        p[b] = a;
        rnk[a] += rnk[b];
        return true;
    }
    bool same(int a, int b) { return find(a) == find(b); }
};
