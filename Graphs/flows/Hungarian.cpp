/*  
    Notes:
        note that n must be <= m
        so in case in your problem n >= m, just swap them
*/
struct Hungarian {
	int n,m;
	vector<vector<ll> > a;
	vector<ll> u,v;vector<int> p,way;
	Hungarian(int n, int m):
	n(n),m(m),a(n+1,vector<ll>(m+1,INF-1)),u(n+1),v(m+1),p(m+1),way(m+1){}
	void set(int x, int y, ll v){a[x+1][y+1]=v;}
	ll assign(){
		for(int i = 1; i <= n; i++){
			int j0=0;p[0]=i;
			vector<ll> minv(m+1,INF);
			vector<char> used(m+1,false);
			do {
				used[j0]=true;
				int i0=p[j0],j1;ll delta=INF;
				for(int j = 1; j <= m; j++)if(!used[j]){
					ll cur=a[i0][j]-u[i0]-v[j];
					if(cur<minv[j])minv[j]=cur,way[j]=j0;
					if(minv[j]<delta)delta=minv[j],j1=j;
				}
				for(int j = 0; j <= m; j++)
					if(used[j])u[p[j]]+=delta,v[j]-=delta;
					else minv[j]-=delta;
				j0=j1;
			} while(p[j0]);
			do {
				int j1=way[j0];p[j0]=p[j1];j0=j1;
			} while(j0);
		}
		return -v[0];
	}
};