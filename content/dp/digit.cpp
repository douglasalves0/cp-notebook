#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll,ll> pii;

// i-th digit
// if the number is greater than L
// if the number is lower than R
const ll N = 31;
ll dp[N][2][2], L, R;
ll bit(ll mask, ll i){ return (mask & (1ll << i)) > 0; }
// this implementation simply counts the number of values in range [L, R], you can change this to do different counts on this range
ll solve(ll i, ll s1, ll s2){ // called via solve(N-1, 0, 0)
    if(i < 0) return 1;
    ll& st = dp[i][s1][s2];
    if(st != -1) return st;
    ll ans = 0;
    for(ll b=0;b<2;b++){
        if(b < bit(L, i) && !s1) continue; // if you are putting a bit lower than the i-th bit of L, and the number is not already greater than L, the number will be lower than L, and we dont want this
        if(b > bit(R, i) && !s2) continue; // if you are putting a bit greater than the i-th bit of R, and the number is not already lower than R, the number will be greater than R, and we also dont want this
        ans += solve(i - 1, s1 | (b > bit(L, i)), s2 | (b < bit(R, i)));
    }
    return st = ans;
}

int main(){

    cin.tie(0)->sync_with_stdio(0);

    for(int i=1;i<=10;i++){
        for(int j=1;j<=10;j++){
            L = i, R = j;
            memset(dp, -1, sizeof dp);
            cout << "FOR L = " << L << ", R = " << R << ", ANS IS " << solve(N-1, 0, 0) << '\n';
        }
    }

    return 0;
}
