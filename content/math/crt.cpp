struct ExtendedCRT {
    ll normalize(ll x, ll mod) {
        x %= mod;
        if (x < 0) x += mod;
        return x;
    }
 
    ll extGCD(ll a, ll b, ll &x, ll &y) {
        if (b == 0) {
            x = 1;
            y = 0;
            return a;
        }
        ll x1, y1;
        ll d = extGCD(b, a % b, x1, y1);
        x = y1;
        y = x1 - y1 * (a / b);
        return d;
    }
 
    pair<ll, ll> solve(const vector<ll>& rem, const vector<ll>& mod) {
        if (rem.empty() || mod.empty()) return {0, 1};
 
        ll ans_r = normalize(rem[0], mod[0]);
        ll ans_m = mod[0];
 
        for (int i = 1; i < (int)rem.size(); i++) {
            ll r1 = ans_r, m1 = ans_m;
            ll r2 = normalize(rem[i], mod[i]);
            ll m2 = mod[i];
 
            ll x, y;
            ll g = extGCD(m1, m2, x, y);
 
            if ((r2 - r1) % g != 0) {
                return {-1, -1};
            }
 
            ll next_m = (m1 / g) * m2;
            ll temp = normalize((r2 - r1) / g, m2 / g);
            ll step = (ll)((normalize(x, m2 / g) * temp) % (m2 / g));
 
            ans_r = normalize(r1 + step * m1, next_m);
            ans_m = next_m;
        }
        return {ans_r, ans_m};
    }
};
