// Calculates an Eulerian cycle starting from vertex v
// and passing through every edge exactly once.
//
// It solves the problem for UNDIRECTED graphs and supposes that:
//   1. Every vertex has even degree;
//   2. Ignoring isolated vertices, the graph is connected.
//
// Graph format:
//   - Each undirected edge must appear twice in g:
//         g[a].push_back({b, id});
//         g[b].push_back({a, id});
//   - id must be unique for each undirected edge.
//
// used[id] must have size = number of edges.
//
// (After the execution of the algorithm you should reverse the cycle variable)
vector<pair<int,int>> graph[200010]; // (to, edge_id)
vector<int> used, cycle;
void eulerian_cycle(int v){
    while(!graph[v].empty()){
        auto [u, id] = graph[v].back();
        graph[v].pop_back();
        if(used[id]) continue;
        used[id] = 1;
        eulerian_cycle(u);
    }
    cycle.push_back(v);
}
