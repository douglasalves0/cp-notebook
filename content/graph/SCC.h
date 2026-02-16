/**
 * Author: Lukas Polacek
 * Date: 2009-10-28
 * License: CC0
 * Source: Czech graph algorithms book, by Demel. (Tarjan's algorithm)
 * Description: Finds strongly connected components in a
 * directed graph. If vertices $u, v$ belong to the same component,
 * we can reach $u$ from $v$ and vice versa.
 * Usage: scc(graph, [\&](vi\& v) { ... }) visits all components
 * in reverse topological order. comp[i] holds the component
 * index of a node (a component only has edges to components with
 * lower index). ncomps will contain the number of components.
 * Time: O(E + V)
 * Status: Bruteforce-tested for N <= 5
 */
#pragma once

vi val, comp, z;
vector<vi> vertices;
ll Time, ncomps;
template<class G> ll dfs(ll j, G& g) {
    ll low = val[j] = ++Time, x; z.push_back(j);
    for (auto e : g[j]) if (comp[e] < 0)
        low = min(low, val[e] ?: dfs(e,g));

    if (low == val[j]) {
        vertices.push_back(vi());
        do {
            x = z.back(); 
            z.pop_back();
            comp[x] = ncomps;
            vertices[ncomps].push_back(x);
        } while (x != j);
        ncomps++;
    }
    return val[j] = low;
}
template<class G> void scc(G& g) {
	ll n = sz(g);
	val.assign(n, 0); comp.assign(n, -1);
	Time = ncomps = 0;
	rep(i,0,n) if (comp[i] < 0) dfs(i, g);
}
