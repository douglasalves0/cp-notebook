struct seg {
    
    typedef int TT; // type of tree nodes
    static constexpr TT unit = 0;
    vector<TT> tree;

    typedef int LT; // type of lazy nodes
    static constexpr LT lazy_unit = 0;
    vector<LT> lazy;
    
    int n;
    seg(int N) {
        n = N;
        tree.resize(4*n, unit);
        lazy.resize(4*n, lazy_unit);
    }

    void push(int no, int l, int r){
        if(lazy[no] == lazy_unit) return;
        // update tree[no] using lazy[no]
        if(l < r){
            // update lazy[no*2] using lazy[no]
            // update lazy[no*2+1] using lazy[no]
        }
        lazy[no] = lazy_unit;
    }

    TT f(TT l, TT r){ return l + r; }

    void update(int no, int l, int r, int x, int y, TT v) {
        push(no, l, r);
        if(x > y || r < x || y < l) return;
        if(x <= l && r <= y){
            // update lazy[no] using v
            push(no, l, r);
            return;
        }
        int m = (l+r)/2;
        update(no*2, l, m, x, y, v);
        update(no*2+1, m+1, r, x, y, v);
        tree[no] = f(tree[no*2], tree[no*2+1]);
    }
    TT query(int no, int l, int r, int x, int y) {
        push(no, l, r);
        if(x > y || r < x || y < l) return unit;
        if(x <= l && r <= y) return tree[no];
        int m = (l+r)/2;
        return f(query(no*2, l, m, x, y), query(no*2+1, m+1, r, x, y));
    }
    void update(int l, int r, TT v){ update(1, 0, n-1, l, r, v); }
    TT query(int l, int r) { return query(1, 0, n-1, l, r); }
};
