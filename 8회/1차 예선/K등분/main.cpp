#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

typedef long long ll;

ll N;
ll K;
ll C;
vector<ll> V;
vector<ll> pSum;
vector<vector<ll>> group;
map<pair<ll, ll>, ll> cache;

void input() {
	// cout << "input" << endl;
	cache.clear();
	cin >> N >> K;
	C = 0;
	V.clear();
	pSum.clear();
	group.clear();
	
	V.resize(N);
	pSum.resize(N);
	group.resize(N + 1);
	
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
	
	sum = pSum[N - 1] / K;
	
	for (ll i = 0; i < N; i++) {
		if (sum == 0) {
			if (pSum[i] == 0) {
				C++;
			}
		} else if (pSum[i] % sum == 0)
			group[pSum[i] / sum].push_back(i);
	}
		
	return;
}

ll dp(ll g_idx, ll idx) {
	// cout << "dp" << endl;	
	if (g_idx == K)
		return idx == N - 1;
	if (cache.find({g_idx, idx}) != cache.end())
		return cache[{g_idx, idx}];
	cache[{g_idx, idx}] = 0;
	ll& ret = cache[{g_idx, idx}];
	for (ll n_idx: group[g_idx + 1])
		if (idx < n_idx) {
			ret += dp(g_idx + 1, n_idx);
			ret = ret % 1000000007;
		}
	return ret = ret % 1000000007;
}

ll calc(ll n, ll k) {
	// cout << "calc" << endl;
	if (k == 0 || n == k)
		return 1;
	if (cache.find({n, k}) != cache.end())
		return cache[{n, k}];
	cache[{n, k}] = 0;
	ll& ret = cache[{n, k}];
	ret = calc(n - 1, k) + calc(n - 1, k - 1);
	return ret = ret % 1000000007;
}

void solve() {
	// cout << "solve" << endl;
	if (C == 0) {
		ll ans = 0;
		for(ll idx: group[1]) {
		    ans += dp(1, idx);
			ans %= 1000000007;
		}
		cout << ans << "\n";
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
	
	for(ll t = 1; t <= T; t++){
		cout << "Case #" << t << "\n";
		input();
		solve();
	}
	
	return 0;
}
