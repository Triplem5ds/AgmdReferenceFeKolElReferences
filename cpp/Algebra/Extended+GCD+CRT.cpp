ll extended(ll a, ll b, ll &x, ll &y) {

    if(b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    ll x0, y0;
    ll g = extended(b, a % b, x0, y0);
    x = y0;
    y = x0 - a / b * y0;

    return g ;
}
ll de(ll a, ll b, ll c, ll &x, ll &y) {

    ll g = extended(abs(a), abs(b), x, y);
    if(c % g) return -1;

    x *= c / g;
    y *= c / g;

    if(a < 0)x = -x;
    if(b < 0)y = -y;
    return g;
}
pair<ll, ll> CRT(vector<ll> r, vector<ll> m) {

    ll r1 = r[0], m1 = m[0];

    for(int i = 1; i < r.size(); i++) {

        ll r2 = r[i], m2 = m[i];
        ll x0, y0;
        ll g = de(m1, -m2, r2 - r1, x0, y0);

        if(g == -1) return {-1, -1} ;
        
        x0 %= m2;
        ll nr = x0 * m1 + r1;
        ll nm = m1 / g * m2;

        r1 = (nr % nm + nm) % nm;
        m1 = nm;
    }
    return {r1, m1};
}