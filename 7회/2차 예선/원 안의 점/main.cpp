#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

typedef long long int ll;

ll R;

void input() {
	cin >> R;
	return;
}

void solve() {
	ll ans = 2 * (R - 1) + 1;
	for (ll i = 1; i < R; i++) {
		ll j = ((ll)sqrt(R * R - i * i));
		if (i * i + j * j == R * R)
			ans += (2 * (j - 1) + 1) * 2;
		else
			ans += (2 * (j) + 1) * 2;
		
	}	
	cout << ans << '\n';
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
