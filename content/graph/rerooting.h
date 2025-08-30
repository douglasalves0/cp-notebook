/**
 * Author: Eu
 * Description: Calcula todas as possíveis árvores de dp para qualquer raiz 1 <= v <= n
 * Time: O(N)
 * Memory: O(N)
 */

// deve calcular f[v] antes com uma dfs e dp
function<void(ll,ll)> reroot = [&](ll v, ll p){
    ll oldfv = f[v];
    for(ll u: graph[v]){
        if(u == p) continue;
        ll oldfu = f[u];
        // tira u da arvore enraizada em v
        // coloca v na arvore enraizada em u
        reroot(u, v);
        // faz o rollback em f
        f[u] = oldfu, f[v] = oldfv;
    }
};
