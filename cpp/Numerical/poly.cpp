struct Poly {
	vector<double> a;
	double operator()(double x) const {
		double val = 0;
		for (int i = sz(a); i--;) (val *= x) += a[i];
		return val;
	}
	void diff() {
		rep(i,1,sz(a)) a[i-1] = i*a[i];
		a.pop_back();
	}
	void divroot(double x0) {
		double b = a.back(), c; a.back() = 0;
		for(int i=sz(a)-1; i--;) c = a[i], a[i] = a[i+1]*x0+b, b=c;
		a.pop_back();
	}
};

// Finds the real roots to a polynomial
// O(n^2 log(1/e))
vector<double> polyRoots(Poly p, double xmin, double xmax) {
	if (sz(p.a) == 2) { return {-p.a[0]/p.a[1]}; }
	vector<double> ret;
	Poly der = p;
	der.diff();
	auto dr = polyRoots(der, xmin, xmax);
	dr.push_back(xmin-1);
	dr.push_back(xmax+1);
	sort(all(dr));
	rep(i,0,sz(dr)-1) {
		double l = dr[i], h = dr[i+1];
		bool sign = p(l) > 0;
		if (sign ^ (p(h) > 0)) {
			rep(it,0,60) { // while (h - l > 1e-8)
				double m = (l + h) / 2, f = p(m);
				if ((f <= 0) ^ sign) l = m;
				else h = m;
			}
			ret.push_back((l + h) / 2);
		}
	}
	return ret;
}

// Given n points (x[i], y[i]), computes an n-1-degree polynomial that passes through them.
// For numerical precision pick x[k] = c * cos(k / (n - 1) * pi).
// O(n^2)
typedef vector<double> vd;
vd interpolate(vd x, vd y, int n) {
	vd res(n), temp(n);
	rep(k,0,n-1) rep(i,k+1,n)
		y[i] = (y[i] - y[k]) / (x[i] - x[k]);
	double last = 0; temp[0] = 1;
	rep(k,0,n) rep(i,0,n) {
		res[i] += y[k] * temp[i];
		swap(last, temp[i]);
		temp[i] -= last * x[k];
	}
	return res;
}

// Recovers any n-order linear recurrence relation from the first 2n terms of the recurrence.
// Useful for guessing linear recurrences after bruteforcing the first terms.
// Should work on any field, but numerical stability for floats is not guaranteed.
// O (n^2)
vector<ll> berlekampMassey(vector<ll> s) {
	int n = sz(s), L = 0, m = 0;
	vector<ll> C(n), B(n), T;
	C[0] = B[0] = 1;

	ll b = 1;
	rep(i,0,n) { ++m;
		ll d = s[i] % mod;
		rep(j,1,L+1) d = (d + C[j] * s[i - j]) % mod;
		if (!d) continue;
		T = C; ll coef = d * modpow(b, mod-2) % mod;
		rep(j,m,n) C[j] = (C[j] - coef * B[j - m]) % mod;
		if (2 * L > i) continue;
		L = i + 1 - L; B = T; b = d; m = 0;
	}
	C.resize(L + 1); C.erase(C.begin());
	for (ll& x : C) x = (mod - x) % mod;
	return C;
}

// Generates the kth term of an n-order linear recurrence
// S[i] = S[i - j - 1]tr[j], given S[0..>= n - 1] and tr[0..n - 1]
// Useful together with Berlekamp-Massey.
// O(n^2 * log(k))
typedef vector<ll> Poly;
ll linearRec(Poly S, Poly tr, ll k) {
	int n = sz(tr);
	auto combine = [&](Poly a, Poly b) {
		Poly res(n * 2 + 1);
		rep(i,0,n+1) rep(j,0,n+1)
			res[i + j] = (res[i + j] + a[i] * b[j]) % mod;
		for (int i = 2 * n; i > n; --i) rep(j,0,n)
			res[i - 1 - j] = (res[i - 1 - j] + res[i] * tr[j]) % mod;
		res.resize(n + 1);
		return res;
	};
	Poly pol(n + 1), e(pol);
	pol[0] = e[1] = 1;
	for (++k; k; k /= 2) {
		if (k % 2) pol = combine(pol, e);
		e = combine(e, e);
	}
	ll res = 0;
	rep(i,0,n) res = (res + pol[i + 1] * S[i]) % mod;
	return res;
}