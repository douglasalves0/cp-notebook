#define all(v) v.begin(),v.end()
vector<int> ca; // compressed array
void compress(vector<int> v){
    sort(all(v));
    v.resize(unique(all(v)) - v.begin());
    ca = v;
}
int get_idx(int x){
    auto it = lower_bound(ca.begin(), ca.end(), x);
    if(it == ca.end() || *it != x) return -1;
    return it - ca.begin();
}
