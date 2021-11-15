int trie[N][A];
int go[N][A]; ///holds the node that you will go to after failure and stuff
int ptr;
ll ans[N]; ///this node is a string terminator;
int fail[N];    ///the failure function for each
void BFS() {
    queue<int> q;
    f(i,0,A) {
        if(trie[0][i]) {
            q.push(trie[0][i]);
            fail[trie[0][i]] = 0;
        }
        go[0][i] = trie[0][i];
    }

    while(q.size()) {
        auto node = q.front();
        q.pop();
        ans[node] += ans[fail[node]];   ///propagate fail[i] to ans[i]
        for(int i = 0; i < A; i++) {
            if(trie[node][i]) { ///calculate failure for you child
                int to = trie[node][i];
                int cur = fail[node]; ///int g = pi[i-1]
                while(cur && !trie[cur][i]) ///while(g && s[g] != s[i])
                    cur = fail[cur];    ///g = pi[g-1]
                if(trie[cur][i])cur = trie[cur][i]; ///g += s[i] == s[g]
                fail[to] = cur; ///pi[i] = g
                q.push(to);
                go[node][i] = trie[node][i]; 
            }   else {
                go[node][i] = go[fail[node]][i];
            }
        }
    }
}
void ins(string s, ll val) {
    int cur = 0;
    string sx = "";
    for(char c : s) {
        sx.push_back(c);
        if(!trie[cur][c - 'a']) {
            trie[cur][c - 'a'] = ++ptr;
        }
        cur = trie[cur][c - 'a'];
    }
    ans[cur] += val;
}