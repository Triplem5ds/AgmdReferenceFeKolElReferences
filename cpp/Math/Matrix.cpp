struct Matrix {
 
    const static int D = 100;
    int a[D][D];
 
    Matrix(int val) {
        for(int i = 0; i < D; i++)
            for(int j = 0; j < D; j++)
                a[i][j] = val;
    }
    void clear() {
        memset(a, 0, sizeof a);
    }
    void initIdentity() {
        clear();
        for(int i = 0; i < D; i++)
            a[i][i] = 1;
    }
    int * operator [](int r) {
        return a[r];
    }
    const int * operator [](int r) const{
        return a[r];
    }
 
    friend Matrix operator * (const Matrix & a, const Matrix & b) {
        Matrix ret(0);
        for(int k = 0; k < D; k++)
            for(int i = 0; i < D; i++)if(a[i][k])
                for(int j = 0; j < D; j++)
                    ret[i][j] = (ret[i][j] + 1ll * a[i][k] * b[k][j]) % MOD;
        return ret;
    }
 
};
Matrix raiseMatrix(Matrix trans, ll k) {
    Matrix res(0);
    res.initIdentity();
    for(;k;k>>=1,trans = trans * trans)
        if(k & 1)
            res = res * trans;
    return res;
}
