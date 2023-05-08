#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define MOD 998244353L

typedef long long int ll;
typedef complex<double> base;

struct Polynomial {
	vector<ll> coef; // start from x^0's
	
	Polynomial () {
		coef.clear();
	}
	
	Polynomial (ll sz) {
		coef.resize(sz);
	}
	
	Polynomial (vector<ll> _coef) {
		for (ll ele: _coef)
			coef.push_back(ele);
	}

	// until Kth term
	Polynomial inverse(ll K) {
		Polynomial R = Polynomial((ll)coef.size() + K + 1);
		R.coef[0] = 1;
		
		Polynomial Q = Polynomial(K + 1);
		
		ll j = -1;
		while (true) {
			while (R.coef[++j] == 0) {
				continue;
				if (j > K)
					break;
			}
			
			if (j > K)
				break;
			
			Q.coef[j] = R.coef[j];
			for (ll i = 0; i < (ll) coef.size(); i++) {
				R.coef[i + j] -= (Q.coef[j] * coef[i]) % MOD;
				R.coef[i + j] = (R.coef[i + j] + MOD) % MOD;
			}
		}		
		return Q;
	}
};

ll N, K, P;
vector<ll> q;

void fft(vector<base> &a, bool inv) {
    int n = (int) a.size();
    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        while (!((j ^= bit) & bit)) bit >>= 1;
        if (i < j) swap(a[i], a[j]);
    }
    for (int i = 1; i < n; i <<= 1) {
        double x = inv ? -M_PI / i : M_PI / i;
        base w = {cos(x), sin(x)};
        for (int j = 0; j < n; j += i << 1) {
            base th = {1, 0};
            for (int k = 0; k < i; k++) {
                base tmp = a[i + j + k] * th;
                a[i + j + k] = a[j + k] - tmp;
                a[j + k] += tmp;
                th *= w;
            }
        }
    }
    if (inv) {
        for (int i = 0; i < n; i++) {
            a[i] /= n;
        }
    }
}

Polynomial multiply (Polynomial& A, Polynomial& B) {
	vector<base> a, b, c;
	
	for (int i = 0; i < (ll) A.coef.size(); i++) {
		a.emplace_back({A.coef[i], 0});
	}
	fft(a, false);
	
	for (int i = 0; i < (ll) B.coef.size(); i++) {
		b.emplace_back({B.coef[i], 0});
	}
	fft(b, false);
	
	c.resize(min((ll) a.size(), (ll) b.size()));
	for (int i = 0; i < (ll) c.size(); i++) {
		c[i] = a[i] * b[i];
	}
	
	fft(c, true);
	
	Polynomial C(c.size());
	for(int i = 0; i < (ll) C.coef.size(); i++) {
		C.coef[i] = c[i].real();
	}
	return c;
}

ll pow(ll a, ll b) {
	ll ret = 1;
	while (b--) {
		ret *= a;
		ret %= MOD;
	} 
	return ret;
}

Polynomial add(Polynomial& X, Polynomial& Y) {
	Polynomial Z(max(X.coef.size(), Y.coef.size()));
	for (int i = 0; i < (ll) Z.coef.size(); i++) {
		Z.coef[i] = X.coef[i] + Y.coef[i];
	}
	return Z;
}

pair<Polynomial, Polynomial> add(pair<Polynomial, Polynomial>& X, pair<Polynomial, Polynomial>& Y) {
	Polynomial A = X.first;
	Polynomial B = X.second;
	Polynomial C = Y.first;
	Polynomial D = Y.second;
	
	Polynomial AD = multiply(A, D);
	Polynomial BC = multiply(B, C);
	Polynomial BD = multiply(B, D);
	
	return {add(AD, BC), BD};
}

pair<Polynomial, Polynomial> sum_all(vector<pair<Polynomial, Polynomial>> Poly, int start, int end) {
	if (start == end)
		return Poly[start];
	else if (start + 1 == end)
		return add(Poly[start], Poly[end]);
	
	pair<Polynomial, Polynomial> sum = add(Poly[start], Poly[end]);
	
	return add(sum, sum_all(start + 1, end - 1));
}

void input() {
	q.clear();
	cin >> N >> K;
	q.resize(N);
	P = 0;
	for (ll i = 0; i < N; i++) {
		ll p;
		cin >> p;
		q[i] = -p;
		P += p;
	}
	for (ll i = 0; i < N; i++) {
		q[i] += P;
	}	
	return;
}

void solve() {
	vector<pair<Polynomial, Polynomial>> Poly;
	for (ll i = 0; i < N; i++) {
		Poly.emplace_back(Polynomial({1}), Polynomial({1, -q[i]}));
	}	
	
	vector<ll> ans;
	ans.resize(K);
	
	pair<Polynomial, Polynomial> _Q = sum_all(Poly, 0, (ll) Poly.size() - 1);
	Polynomial Q = multiply(_Q.first, _Q.second.inv(K));
	
	for (ll k = 1; k <= K; k++) {
		ans[k - 1] = (N * pow(P, k)) % MOD;
		ans[k - 1] -= Q[k];
	}
	
	vector<ll> ans;
	ans.resize(K);

	
	ll fin = ans[0];
	for (ll k = 1; k < K; k++) {
		fin ^= ans[k];
	}
	cout << fin << "\n";
	return;
}

int main(){
	freopen("input.txt", "r", stdin);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);  
	cout.tie(NULL);
	
	ll T;
	cin >> T;
	
	for(ll t = 1; t <= T; t++){
		cout << "Case #" << t << "\n";
		input();
		solve();
	}
	
	return 0;
}