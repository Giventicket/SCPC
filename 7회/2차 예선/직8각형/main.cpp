#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define INF 2000000000

long long int K;
pair<long long int, long long int> P[8] = {
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0}
};
long long int ans;

void input() {
	cin >> K;
	ans = INF;
	
	for (int i = 0; i < 8; i++)
		cin >> P[i].first >> P[i].second;
	return;
}

long long int calc(int* indices, long long int* x_offsets, long long int* y_offsets) {
	long long int xs[8], ys[8];
	for (int i = 0; i < 8; i++) {
		xs[i] = (-(x_offsets[i] - P[indices[i]].first));
		ys[i] = (-(y_offsets[i] - P[indices[i]].second));
	}
	
	sort(xs, xs + 8);
	sort(ys, ys + 8);
	
	long long int ret = 0;
	for (int i = 0; i < 8; i++) {
		ret += abs(xs[3] - xs[i]) + abs(ys[3] - ys[i]);
	}
	
	return ret;
}

void solve() {
	int indices[8] = {0, 1, 2, 3, 4, 5, 6, 7};
	long long int x_offsets[8] = {0, K, 2*K, 3*K, 3*K, 2*K, K, 0};
	long long int y_offsets[8] = {0, -K, -K, 0, K, 2*K, 2*K, K};
	do {
		ans = min(ans, calc(indices, x_offsets, y_offsets));
	} while(next_permutation(indices, indices + 8));
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
