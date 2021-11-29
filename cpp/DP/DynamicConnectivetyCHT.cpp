/// MANGA
#pragma GCC optimize("O3")
#pragma GCC optimize ("unroll-loops")
#pragma GCC target("avx,avx2,fma")
using namespace std;

#include "bits/stdc++.h"

#define pb push_back
#define F first
#define S second
#define f(i, a, b)  for(int i = a; i < b; i++)
#define all(a)  a.begin(),a.end()
#define rall(a) a.rbegin(),a.rend()
#define sz(x) (int)(x).size()
//#define mp make_pair
#define popCnt(x) (__builtin_popcountll(x))
typedef long long ll;
typedef pair<int, int> ii;
using ull = unsigned long long;
const int N = 1e5+5, LG = 17, MOD = 1e9 + 7;
const long double PI = acos(-1);
struct PT{
    ll x, y;
    PT() {}
    PT(ll a, ll b):x(a), y(b){}
    PT operator - (const PT & o) {return PT{x-o.x,y-o.y};}
    bool operator < (const PT & o) const {return make_pair(x,y) < make_pair(o.x,o.y);}
};
ll cross(PT x, PT y) {
    return x.x * y.y - x.y * y.x;
}
PT val[300005];
bool in[300005];
ll qr[300005];
bool ask[300005];
ll ans[N];
vector<PT> t[300005 * 4];   ///segment tree holding points to queries
void update(int node, int s, int e, int l, int r, PT x) {
    if(r < s || e < l)return;
    if(l <= s && e <= r) {  ///add this point to maximize it with queries in this range
        t[node].pb(x);
        return;
    }
    int md = (s + e) >> 1;
    update(node<<1,s,md,l,r,x);
    update(node<<1|1,md+1,e,l,r,x);
}
vector<PT> stk;
inline void addPts(vector<PT> v) {
    stk.clear();    ///reset the data structure you are using
    sort(all(v));
    ///build upper envelope
    for(int i = 0; i < v.size(); i++) {
        while(sz(stk) > 1 && cross(v[i] - stk.back(), stk.back() - stk[stk.size()-2]) <= 0)
            stk.pop_back();
        stk.push_back(v[i]);
    }
}
inline ll calc(PT x, ll val) {
    ///mb+y
    return x.x * val + x.y;
}

ll query(ll x) {
    if(stk.empty())
        return LLONG_MIN;
    int lo = 0, hi = stk.size() - 1;
    while(lo + 10 < hi) {
        int md = lo + (hi-lo) / 2;
        if(calc(stk[md+1],x) > calc(stk[md],x))
            lo = md + 1;
        else
            hi = md;
    }
    ll ans = LLONG_MIN;
    for(int i = lo; i <= hi; i++)
        ans = max(ans, calc(stk[i], x));
    return ans;
}
void solve(int node, int s, int e) {    ///Solve queries
    addPts(t[node]);    ///note that there is no need to add/delete just build for t[node]
    f(i,s,e+1){
        if(ask[i]) { 
            ans[i] = max(ans[i], query(qr[i]));
        }
    }
    if(s==e)return;
    int md = (s + e) >> 1;
    solve(node<<1,s,md);
    solve(node<<1|1,md+1,e);
}
void doWork() {

    int n;
    cin >> n;
    stk.reserve(n);
    f(i,1,n+1) {
        int tp;
        cin >> tp;
        if(tp == 1) {   ///Add Query
            int x, y;
            cin >> x >> y;
            val[i] = PT(x, y);
            in[i] = 1;
        }   else if(tp == 2) {  ///Delete Query
            int x;
            cin >> x;
            if(in[x])update(1, 1, n, x, i - 1, val[x]);
            in[x] = 0;
        }   else {
            cin >> qr[i];
            ask[i] = true;
        }
    }
    f(i,1,n+1)  ///Finalize Query
        if(in[i])
            update(1, 1, n, i, n, val[i]);

    f(i,1,n+1)ans[i] = LLONG_MIN;
    solve(1, 1, n);
    f(i,1,n+1)
    if(ask[i]) {
        if(ans[i] == LLONG_MIN)
            cout << "EMPTY SET\n";
        else
            cout << ans[i] << '\n';
    }

}
int32_t main() {
#ifdef ONLINE_JUDGE
    ios_base::sync_with_stdio(0);
    cin.tie(0);
#endif // ONLINE_JUDGE
    int t = 1;
//    cin >> t;
    while (t--) {
        doWork();
    }
    return 0;
}
