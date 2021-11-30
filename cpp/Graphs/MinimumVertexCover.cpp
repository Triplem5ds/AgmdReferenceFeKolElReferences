int myrandom (int i) { return std::rand()%i;}

struct MinimumVertexCover {
	int n, id;
	vector<vector<int> > g;
	vector<int> color, m, seen;
	vector<int> comp[2];
	MinimumVertexCover() {}
	MinimumVertexCover(int n, vector<vector<int> > g) {

		this->n = n;
		this->g = g;
		color = m = vector<int>(n, -1);
		seen = vector<int>(n, 0);
		makeBipartite();
	}

	void dfsBipartite(int node, int col) {
		if (color[node] != -1) {
			assert(color[node] == col); /* MSH BIPARTITE YA BASHMOHANDES */
			return;
		}
		color[node] = col;
		comp[col].push_back(node);
		for (int i = 0; i < int(g[node].size()); i++)
			dfsBipartite(g[node][i], 1 - col);
	}

	void makeBipartite() {
		for (int i = 0; i < n; i++)
			if (color[i] == -1)
				dfsBipartite(i, 0);
	}

	// match a node
	bool dfs(int node) {
	  random_shuffle(g[node].begin(),g[node].end());
		for (int i = 0; i < g[node].size(); i++) {
			int child = g[node][i];
			if (m[child] == -1) {
				m[node] = child;
				m[child] = node;
				return true;
			}
			if (seen[child] == id)
				continue;
			seen[child] = id;
			int enemy = m[child];
			m[node] = child;
			m[child] = node;
			m[enemy] = -1;
			if (dfs(enemy))
				return true;
			m[node] = -1;
			m[child] = enemy;
			m[enemy] = child;
		}
		return false;
	}

	void makeMatching() {
    for(int j = 0; j < 5; j++)
      random_shuffle(comp[0].begin(),comp[0].end(),myrandom );
		for (int i = 0; i < int(comp[0].size()); i++) {
			id++;
			if(m[comp[0][i]] == -1)
				dfs(comp[0][i]);
		}
	}


	void recurse(int node, int x, vector<int> &minCover, vector<int> &done) {
		if (m[node] != -1)
			return;
		if (done[node])return;
		done[node] = 1;
		for (int i = 0; i < int(g[node].size()); i++) {
			int child = g[node][i];
			int newnode = m[child];
			if (done[child]) continue;
			if(newnode == -1) {
				continue;
			}
			done[child] = 2;
			minCover.push_back(child);
			m[newnode] = -1;
			recurse(newnode, x, minCover, done);
		}
	}

	vector<int> getAnswer() {
		vector<int> minCover, maxIndep;
		vector<int> done(n, 0);
		makeMatching();
		for (int x = 0; x < 2; x++)
			for (int i = 0; i < int(comp[x].size()); i++) {
				int node = comp[x][i];
				if (m[node] == -1)
					recurse(node, x, minCover, done);
			}

		for (int i = 0; i < int(comp[0].size()); i++)
			if (!done[comp[0][i]]) {
				minCover.push_back(comp[0][i]);
			}
		return minCover;
	}
};