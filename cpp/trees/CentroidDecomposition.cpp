/*
    Properties:
        1. consider path(a,b) can be decomposed to path(a,lca(a,b)) and path(b,lca(a,b))
        where lca(a,b) is the lca on the centroid tree
        2. Each one of the n^2 paths is the concatenation of two paths in a set of O(n lg(n)) 
        paths from a node to all its ancestors in the centroid decomposition.
        3. Ancestor of a node in the original tree is either an ancestor in the CD tree or
        a descendadnt
*/
vector<int> adj[N]; ///adjacency list of original graph
int n;
int sz[N];
bool used[N];
int centPar[N]; ///parent in centroid
void init(int node, int par) {  ///initialize size
    sz[node] = 1;
    for(auto p : adj[node])
        if(p != par && !used[p]) {
            init(p, node);
            sz[node] += sz[p];
        }
}
int centroid(int node, int par, int limit) {    ///get centroid
    for(int p : adj[node])
        if(!used[p] && p != par && sz[p] * 2 > limit)
        return centroid(p, node, limit);
    return node;
}
int decompose(int node) {
    init(node,node);    ///calculate size
    int c = centroid(node, node, sz[node]); ///get centroid
    used[c] = true;
    for(auto p : adj[c])if(!used[p.F]) {    ///initialize parent for others and decompose
        centPar[decompose(p.F)] = c;
    }
    return c;
}
void update(int node, int distance, int col) {
    int centroid = node;
    while(centroid){
        ///solve
        centroid = centPar[centroid];
    }
}
int query(int node) {
 
    int ans = 0;
 
    int centroid = node;
    while(centroid) {
        ///solve
        centroid = centPar[centroid];
    }
    
    return ans;
}