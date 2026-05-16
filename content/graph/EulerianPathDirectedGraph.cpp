// Calculates a cycle from v that passes through all the edges of the graph
// It solves the problem for directed graphs and supposes that
//   1. All the vertices have in_degree = out_degree;
//   2. Ignoring vertices isolated, the graph must be weakly-connected*;
// * weakly connected means that if you consider the edges undirected, the graph is connected
//
// (After the execution of the algorithm you should reverse the cycle variable)
vector<ll> graph[100010], cycle;
void eulerian_cycle(int v){
    while(!graph[v].empty()){
        int u = graph[v].back();
        graph[v].pop_back();
        eulerian_cycle(u);
    }
    cycle.push_back(v);
}
