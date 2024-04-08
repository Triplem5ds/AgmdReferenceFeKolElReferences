///O(N^5/3) note that the block size is not a standard size
/// O(2SQ + N^2 / S + Q * N^2 / S^2) = O(Q * N^(2/3)) if S = n^(2/3)
/// fact: S = (2 * n * n)^(1/3) give the best complexity
const int block_size = 2000;
struct Query{
    int l, r, t, idx;
    Query(int l,int r,int t,int idx) : l(l),r(r),t(t),idx(idx) {}
    bool operator < (Query o) const{
        if(l / block_size != o.l / block_size) return l < o.l;
        if(r / block_size != o.r/block_size) return r < o.r;
        return t < o.t;
    }
};
int L = 0, R = -1, K = -1;
while(L < Q[i].l)del(a[L++]);
while(L > Q[i].l)add(a[--L]);
while(R < Q[i].r)add(a[++R]);
while(R > Q[i].r)del(a[R--]);
while(K < Q[i].t)upd(++K);
while(K > Q[i].t)err(K--);