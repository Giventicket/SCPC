#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

#define MAXN 300
#define INF 1000000000

int n;
vector<pair<long double, long double>> V;
int dp[MAXN][MAXN];
int isIn[MAXN][MAXN];

void input() {
	memset(isIn, 0, sizeof(isIn));
	cin >> n;
	V.clear();
	V.resize(n);
	for (int i = 0; i < n; i++)
		cin >> V[i].first >> V[i].second;
	return;
}

long double funcValue(int i, int j, long double x) {
	return ((V[i].second - V[j].second) / (V[i].first - V[j].first)) * (x - V[i].first) + V[i].second;
}

long double funcDiffValue(int i, int j, int ii, int jj, long double x) {
	return funcValue(i, j, x) - funcValue(ii, jj, x);
}

bool isCross(int i, int j, int ii, int jj) {
	if (V[i].first > V[j].first)
		return isCross(j, i, ii, jj);
	if (V[ii].first > V[jj].first)
		return isCross(i, j, jj, ii);
	if (V[i].first > V[jj].first)
		return isCross(jj, ii, i, j);
		

	if (!(V[i].first < V[ii].first && V[ii].first < V[j].first)){
		//cout << "isCross " << i << " " << j << " " << ii << " " << jj << " " << false << endl;
		return false;
	}
		
	
	long double minX = max(V[i].first, V[ii].first);
	long double maxX = min(V[j].first, V[jj].first);
	
	if (funcDiffValue(i, j, ii, jj, minX) * funcDiffValue(i, j, ii, jj, maxX) < 0){
		//cout << "isCross " << i << " " << j << " " << ii << " " << jj << " " << true << endl;
		return true;
	}
		
	//cout << "isCross " << i << " " << j << " " << ii << " " << jj << " " << false << endl;
	return false;
}

int dist(int i, int j, int d) {
	// cout << "dp call " << i << " " << j << " " << d << endl;		
	int & ret = dp[i][j];
	if (ret != -1)
		return ret;
	
	if ((i + 1) % n == j)
		return ret = 0;
	
	ret = INF;
	for (int k = (i + 1) % n; k != j; k = (k + 1) % n)
		if (isIn[i][k] && isIn[k][j]) {
			if (dist(i, k, d) + dist(k, j, d) + 1 <= d)
				ret = min(ret, max(dist(i, k, d), dist(k, j, d)) + 1);
		}
	
	// cout << "dp " << i << " " << j << " " << d << " " << dp[i][j] << endl;		
	return ret;
}

void solve() {
	// renew isIn, inner line cannot be cross
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			isIn[i][j] = isIn[j][i] = 1;
			for (int k = 0; k < n; k++) {
				int ii = k;
				int jj = (k + 1) % n;
				if (isCross(i, j, ii, jj)) {
					isIn[i][j] = isIn[j][i] = 0;
					break;
				}
			}
		}	
	}
	
	// renew isIn, consider if polygon is convex
	// todo

	/*
	for (int i = 0; i < n; i++)
		for (int j = i + 1; j < n; j++)
			cout << "isIn " << i << " " << j << " " << isIn[i][j] << endl;
	*/
			
	// solve
	
	int left = 0;
	int right = n;
	
	while (left < right) {
		memset(dp, -1, sizeof(dp));
		int mid = (left + right) / 2;
		int val = dist(1, 0, mid);
		// cout << "while " << left << " " << mid << " " << right << " " << val << endl; 
		if (val != INF)
			right = mid;
		else
			left = mid + 1;
	}
	cout << right - 1 << "\n";
	return;	
}

int main() {
	freopen("input.txt", "r", stdin);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);  
	cout.tie(NULL);
	
	int T;
	cin >> T;	
	
	for (int t = 1; t <= T; t++) {
		cout << "Case #" << t << "\n";
		input();
		solve();
	}
	
	return 0;
}