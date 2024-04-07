int g (int n) {
    return n ^ (n >> 1);
}
int rev_g (int g) {
  int n = 0;
  for (; g; g >>= 1)
    n ^= g;
  return n;
}
int calc(int x, int y) { ///2D Gray Code
    int a = g(x), b = g(y);
    int res = 0;
    f(i,0,LG) {
        int k1 = (a & (1 << i));
        int k2 = b & (1 << i);
        res |= k1 << (i + 1);
        res |= k2 << i;
    }
    return res;
}