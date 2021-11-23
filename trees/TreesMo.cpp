int BL[N << 1], ID[N << 1];
int lvl[N], par[17][N];
int ans[N];
vector<ii> adj[N];
struct query{
  int id, l, r, lc;
  bool operator < (const query & rhs){
    return (BL[l] == BL[rhs.l]) ? (r < rhs.r) : (BL[l] < BL[rhs.l]);
  }
}Q[N];
int in[N], out[N], val[N], timer;
void dfs(int node, int p){
  in[node] = ++timer;  ID[timer] = node;
  for(int i = 1; i < 17; i++)par[i][node] = par[i-1][par[i-1][node]];
  for(auto child : adj[node])if(child.F != p){
    lvl[child.F] = lvl[node] + 1;
    par[0][child.F] = node;
    val[child.F] = child.S;
    dfs(child.F, node);
  }
  out[node] = ++timer;  ID[timer] = node;
}
int LCA(int u, int v){
  if(lvl[u] > lvl[v])swap(u,v);
  for(int k = 0; k < 17; k++)
    if((lvl[v] - lvl[u]) >> k & 1)
      v = par[k][v];
  if(u == v)
    return u;
  for(int i = 16; i >= 0; --i)
    if(par[i][u] != par[i][v])
      u = par[i][u], v = par[i][v];
  return par[0][u];
}
bool vis[N];
int inSet[N];
void add(int node, int & res){
  if(val[node] > N)return;
  if(!vis[node]){
    inSet[val[node]]++;
    while(inSet[res])res++;
  } else {
    inSet[val[node]]--;
    if(!inSet[val[node]] && val[node] < res)
      res = val[node];
  }
  vis[node] ^= 1;
}
//-------------------Adding Queries-----------------/
f(i,0,q){
    int u, v;
    cin >> u >> v;  if(lvl[u] > lvl[v])swap(u, v);
    int lca = LCA(u, v);
    Q[i].id = i;
    Q[i].lc = lca;
    if(lca == u)Q[i].l = in[u], Q[i].r = in[v];
    else {
      Q[i].l = out[u];
      Q[i].r = in[v];
    }
  }
//-------------------Processing Queries-----------------/
f(i,0,q){
		while (curL < Q[i].l) add(ID[curL++], res);
		while (curL > Q[i].l) add(ID[--curL], res);
		while (curR < Q[i].r) add(ID[++curR], res);
		while (curR > Q[i].r) add(ID[curR--], res);
		int u = ID[Q[i].l];
		int v = ID[Q[i].r];
		if(Q[i].lc == u)add(Q[i].lc, res);
		ans[Q[i].id] = res;
		if(Q[i].lc == u)add(Q[i].lc, res);
  }