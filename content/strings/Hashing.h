mt19937 rng((ll) chrono::steady_clock::now().time_since_epoch().count());
const ll NN = 6e5 + 10, K = 2;
const ll P = uniform_int_distribution<ll>(1e8, 1e9)(rng);
const ll MOD[] = {
    1000893493, 
    1013782387
};
ll pw[NN][K], pre[NN][K], IT; 
 
// SE ESTIVER DANDO PROBLEMA NO CÓDIGO
// VEJA SE ESTÁ CHAMANDO PRECALC ANTES DE TUDO
void precalc(){
    for(ll j=0;j<K;j++) pw[0][j] = 1;
    for(ll i=1;i<NN;i++){
        for(ll j=0;j<K;j++){
            pw[i][j] = pw[i - 1][j] * P % MOD[j];
        }
    }
}
 
struct RollingHash {
    ll L;
    RollingHash(const string &s){
        L = IT, IT += s.length();
        for(ll j=0;j<K;j++) pre[L][j] = s[0];
        for(ll i=1;i<s.length();i++){
            for(ll j=0;j<K;j++){
                pre[L + i][j] = (pre[L + i - 1][j] * P + s[i]) % MOD[j];
            }
        }
    }
    array<ll, K> operator()(ll l, ll r){
        array<ll, K> ans;
        for(ll j=0;j<K;j++){
            if(l > r){
                ans[j] = 0;
                continue;
            }
            ll right = pre[L + r][j], left = 0;
            if(l) left = pre[L + l - 1][j] * pw[r - l + 1][j] % MOD[j];
            ans[j] = (right - left + MOD[j]) % MOD[j];
        }
        return ans;
    }
};
