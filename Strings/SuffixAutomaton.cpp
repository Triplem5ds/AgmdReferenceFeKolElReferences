///Note it's better to use addNode to clear a node before using it
///at the start of each test case use initAutomaton

int last = 0, cntState = 1;
int nxt[N * 2][26];
int len[N * 2], link[N * 2], firstPos[N * 2], cnt[N * 2];

void addNode(int i) {
    memset(nxt[i], 0, sizeof nxt[i]);
    link[i] = -1;
    cnt[i] = 0;
}

void initAutomaton() {
    cntState = 1;
    last = 0;
    addNode(last);
}

int addChar(char c) {

    c -= 'a';   ///note this offset
    int p = last;
    int cur = cntState++;
    addNode(cur);
    cnt[cur] = 1; ///extra
    len[cur] = len[last] + 1;
    firstPos[cur] = len[cur] - 1;   ///extra
    while(p != -1 && nxt[p][c] == 0) {
        nxt[p][c] = cur;
        p = link[p];
    }

    if(p == -1) {
        link[cur] = 0;
    }   else {
        int q = nxt[p][c];
        if(len[q] == len[p] + 1) {
            link[cur] = q;
        }   else {
            int clone = cntState++;
            link[clone] = link[q];
            firstPos[clone] = firstPos[q];  ///extra
            len[clone] = len[p] + 1;
            link[q] = link[cur] = clone;
            memcpy(nxt[clone], nxt[q], sizeof nxt[q]);
            cnt[clone] = 0; ///extra
            f(i,0,26)nxt[clone][i] = nxt[q][i];
            while(p != -1 && nxt[p][c] == q) {
                nxt[p][c] = clone;
                p = link[p];
            }
        }
    }
    last = cur;
    return cur;
}