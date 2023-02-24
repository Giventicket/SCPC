#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

typedef long long int ll;

int N;
vector<pair<ll, ll>> X, Y;
map<ll, int> x_count, y_count;

void input() {
	X.clear();
	Y.clear();
	x_count.clear();
	y_count.clear();
	
	cin >> N;
	ll x, y;
	for (int i = 0; i < N; i++) {
		cin >> x >> y;
		X.push_back({x, y});
		Y.push_back({y, x});
		
		if (x_count.find(x) == x_count.end())
			x_count[x] = 1;
		else
			x_count[x]++;
		
		if (y_count.find(y) == y_count.end())
			y_count[y] = 1;
		else
			y_count[y]++;
	}
	return;
}

void solve() {
	ll x, y;
	x = y = -1;
	
	for (map<ll, int>::iterator iter = x_count.begin(); iter != x_count.end(); iter++) {
		if (iter->second % 2 != 0) {
			x = iter->first;
			break;
		}			
	}
	
	for (map<ll, int>::iterator iter = y_count.begin(); iter != y_count.end(); iter++) {
		if (iter->second % 2 != 0) {
			y = iter->first;
			break;
		}
	}
		
	if (x != -1) {
		X.erase(find(X.begin(), X.end(), make_pair(x, y)));
		Y.erase(find(Y.begin(), Y.end(), make_pair(y, x)));
	}
	
	sort(X.begin(), X.end());
	sort(Y.begin(), Y.end());
	
	ll ans = 0;
	for (int i = 1; i < X.size(); i += 2)
		ans += abs(X[i].second - X[i - 1].second);
	for (int i = 1; i < Y.size(); i += 2)
		ans += Y[i].second - Y[i - 1].second;
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
