#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;

#define MAXN 500001
#define MOD 1000000007

typedef long long ll;

ll N;
ll K;
ll C;
ll S;
ll V[MAXN];
ll pSum[MAXN];
ll cache[MAXN];
ll fac[MAXN];
ll ifac[MAXN];

void input() {
	// cout << "input" << endl;	
	memset(V, 0, sizeof(V));
	memset(pSum, 0, sizeof(pSum));
	memset(cache, 0, sizeof(cache));
	cin >> N >> K;
	C = 0;
	ll sum = 0;
	for (ll i = 0; i < N; i++) {
		cin >> V[i];
		sum += V[i];
		pSum[i] = sum;
	}
	
	if (pSum[N - 1] % K != 0) {
		C--;
		return;
	}
	
	S = pSum[N - 1] / K;
	
	for (ll i = 0; i < N; i++) {		
		if (sum == 0) {
			if (pSum[i] == 0) {
				C++;
			}
		}
	}
	
	return;
}

void pre_calc() {
	fac[0] = 1;
	for (ll i = 1; i < MAXN; i++) {
		fac[i] = i * fac[i - 1]; 
		fac[i] %= MOD;
	}
	
	for (ll i = 0; i < MAXN; i++) {
		ll r = 1;
		ll x = fac[i];
		for (ll k = MOD - 2; k; k /= 2, x = x * x % MOD)
			if (k & 1){
				r *= x;
				r %= MOD;
			}
		ifac[i] = r;
	}
	return;
}

ll calc(ll n, ll k) {
	// cout << "calc" << endl;
	ll ret = fac[n] * ifac[k] % MOD;
	ret = ret * ifac[n - k] % MOD;
	return  ret;
}

void solve() {
	// cout << "solve" << endl;
	if (C == 0) {
		cache[0] = 1;
		for(ll idx = 0; idx < N; idx++) {
			ll g_idx = pSum[idx] / S;
			if (pSum[idx] % S == 0 && g_idx >= 1 && g_idx <= K) {
				cache[g_idx] += cache[g_idx - 1];					
				cache[g_idx] %= MOD;
			}
		}
		cout << cache[K - 1] << "\n";
	} else if (C == -1) 
		cout << 0 << "\n";
	else {
		cout << calc(C - 1, K - 1) << "\n";
	}
	return;
}

int main(){
	freopen("input.txt", "r", stdin);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);  
	cout.tie(NULL);
	
	ll T;
	cin >> T;
	
	pre_calc();
	
	for(ll t = 1; t <= T; t++){
		cout << "Case #" << t << "\n";
		input();
		solve();
	}
	
	return 0;
}
