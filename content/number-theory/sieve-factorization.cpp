const int MAXN = 1e6;
int pf[MAXN+1]; // pf[x] = lowest prime factor of x
void sieve(){ // x is prime if pf[x] = x
    for(int i=2;i<=MAXN;i++){
        if(pf[i]) continue;
        pf[i] = i;
        for(int j=i;j<=MAXN;j+=i) if(!pf[j]) pf[j] = i;
    }
}

vector<int> fact(int x){
    vector<int> ans;
    while(pf[x]){
        ans.push_back(pf[x]);
        x /= pf[x];
    }
    return ans;
}
