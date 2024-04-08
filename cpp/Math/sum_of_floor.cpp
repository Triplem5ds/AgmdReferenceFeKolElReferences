// return sum_{i=0}^{n-1} floor((ai + b) / m) (mod 2^64)
#define ull unsigned long long
ull floor_sum_unsigned(ull n, ull m, ull a, ull b) {
    ull ans = 0;
    while (true) {
        if (a >= m) {
            ans += n * (n - 1) / 2 * (a / m);
            a %= m;
        }
        if (b >= m) {
            ans += n * (b / m);
            b %= m;
        }
        ull y_max = a * n + b;
        if (y_max < m) break;
        // y_max < m * (n + 1)
        // floor(y_max / m) <= n
        n = (ull)(y_max / m);
        b = (ull)(y_max % m);
        std::swap(m, a);
    }
    return ans;
}