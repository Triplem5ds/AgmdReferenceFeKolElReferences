/*	
	Notes:
		make sure you notice the #define int ll
		focus on the data types of the max flow everythign inside is integer
		addEdge(u,v,cap,cost)
		minCostFlow(int source, int dest, int maxflow), maxflow is to bind that no flow is more than this flow
		note that for min cost max flow the cost is sum of cost * flow over all edges
*/
struct Edge {
    int to;
    int cost;
    int cap, flow, backEdge;
};
const int mxN = 3005;
struct MCMF {

    const int inf = 1000000010;
    int s, t, n;
    vector<Edge> g[mxN];
    MCMF(int _s, int _t, int _n) {
        s = _s, t = _t, n = _n+1;
    }
    void addEdge(int u, int v, int cap, int cost) {
        Edge e1 = { v, cost, cap, 0, (int)g[v].size() };
        Edge e2 = { u, -cost, 0, 0, (int)g[u].size() };
        g[u].push_back(e1); g[v].push_back(e2);
    }
    pair<int, int> minCostMaxFlow() {
        int flow = 0;
        int cost = 0;
        vector<int> state(n), from(n), from_edge(n);
        vector<int> d(n);
        deque<int> q;
        while (true) {
            for (int i = 0; i < n; i++)
                state[i] = 2, d[i] = inf, from[i] = -1;
            state[s] = 1; q.clear(); q.push_back(s); d[s] = 0;
            while (!q.empty()) {
                int v = q.front(); q.pop_front(); state[v] = 0;
                for (int i = 0; i < (int) g[v].size(); i++) {
                    Edge e = g[v][i];
                    if (e.flow >= e.cap || (d[e.to] <= d[v] + e.cost) )
                        continue;
                    int to = e.to; d[to] = d[v] + e.cost;
                    from[to] = v; from_edge[to] = i;
                    if (state[to] == 1) continue;
                    if (!state[to] || (!q.empty() && d[q.front()] > d[to]))
                        q.push_front(to);
                    else q.push_back(to);
                    state[to] = 1;
                }
            }
            if (d[t] == inf) break;
            int it = t, addflow = inf;
            while (it != s) {
                addflow = min(addflow,
                              g[from[it]][from_edge[it]].cap
                              - g[from[it]][from_edge[it]].flow);
                it = from[it];
            }
            it = t;
            while (it != s) {
                g[from[it]][from_edge[it]].flow += addflow;
                g[it][g[from[it]][from_edge[it]].backEdge].flow -= addflow;
                cost += g[from[it]][from_edge[it]].cost * addflow;
                it = from[it];
            }
            flow += addflow;
        }
        return {cost,flow};
    }
};