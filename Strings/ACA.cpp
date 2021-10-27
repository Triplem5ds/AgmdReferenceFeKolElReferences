const int A = 26;
int trie[N][A];
int go[N][A];
bool isLeaf[N]; ///this node is a string terminator;
int fail[N];    ///the failure function for each
void BFS() {
    queue<int> q;
    f(i,0,A) {
        if(trie[0][i]) {
            q.push(trie[0][i]);
            fail[trie[0][i]] = 0;
        }
    }

    while(q.size()) {
        auto node = q.front();
        q.pop();
        for(int i = 0; i < A; i++) {
            if(trie[node][i]) { ///calculate failure for you child
                int to = trie[node][i];
                int cur = fail[node]; ///int g = pi[i-1]
                while(cur && !trie[cur][i]) ///while(g && s[g] != s[i])
                    cur = fail[cur];    ///g = pi[g-1]
                if(trie[cur][i])cur = trie[cur][i]; ///g += s[i] == s[g]
                fail[to] = cur; ///pi[i] = g
                q.push(to);
                go[node][i] = trie[node][i]; ///
            }   else {
                go[node][i] = go[fail[node]][i]; ///note that the go of t
            }
        }
    }

}
void ins(string s) {
    int cur = 0;
    for(char c : s) {
        if(!trie[cur][c - 'a']) {
            trie[cur][c - 'a'] += 1;
        }
        cur = trie[cur][c - 'a'];
    }
    isLeaf[cur] = true;
}