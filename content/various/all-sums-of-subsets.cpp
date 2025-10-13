// For a vector input a of size N, returns a vector f where
// f[i] = -1, if is impossible to create sum i using the elements from a
// f[i] = x >= 0, if it's possible to create sum i
// each element can be used only once
// O(S sqrt(S) + N log N), where S is the sum of all the elements on the vector
vector<ll> bounded_knapsack(vector<ll> a){
    ll s = 0;
    map<ll,ll> mp;
    for(ll x: a) s += x, mp[x] += 1;
    vector<pii> b;
    for(auto [k, v]: mp) b.push_back({k, v});
    vector<ll> old(s+1, -1), cur(s+1);
    old[0] = 0;
    for(auto [k, v]: b){ // sqrt(S)
        for(int i=0;i<=s;i++){ // S
            op++;
            if(old[i] >= 0){
                cur[i] = 0;
            }else if(i - k >= 0 && cur[i - k] >= 0 && cur[i - k] < v){
                cur[i] = cur[i - k] + 1;
            }else{
                cur[i] = -1;
            }
        }
        old = cur;
    }
    return old;
}