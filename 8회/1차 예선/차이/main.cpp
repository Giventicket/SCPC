#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long int ll;

int N;
vector<ll> P, V;

void input() {
	P.clear();
	V.clear();
	
	cin >> N;
	P.resize(N);
	V.resize(N);
	
	for (int i = 0; i < N; i++) 
		cin >> P[i];
	for (int i = 0; i < N; i++)
		cin >> V[i];
	
	return;
}

void solve() {
	vector<pair<ll, ll>> vt;
	for (int i = 0; i < N; i++)
		vt.push_back({V[i], P[i]});
	sort(vt.begin(), vt.end());
	
	ll ans = 0;
	for (int i = 0; i < N; i++)
		ans += abs(vt[i].second - P[i]);
	cout << ans << "\n";
	
	return;
}

int main(){
	freopen("input.txt", "r", stdin);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);  
	cout.tie(NULL);
	
	int T;
	cin >> T;
	
	for(int t = 1; t <= T; t++){
		cout << "Case #" << t << "\n";
		input();
		solve();
	}
	
	return 0;
}
