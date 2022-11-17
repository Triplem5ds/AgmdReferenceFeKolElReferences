int S[N];
for(int i = 2; i < N; i++) S[i] = S[i >> 1] + 1;
 
for (int i = 1; i <= K; i++)
    for (int j = 0; j + (1 << i) <= N; j++)
        st[i][j] = f(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);


int query(int l, int r) {
    int k = S[r - l + 1];
    return mrg(st[k][l], st[k][r-(1<<k)+1]);
}