#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <stack>
#include <cmath>

using namespace std;

#define MAXN 300
#define INF 1000000000

int n;
vector<pair<double, double>> P; // points of polygon: (x, y)
int dp[MAXN][MAXN];
int isIn[MAXN][MAXN];

void input() {
	memset(isIn, 0, sizeof(isIn));
	cin >> n;
	P.clear();
	P.resize(n);
	for (int i = 0; i < n; i++)
		cin >> P[i].first >> P[i].second;
	return;
}


int ccw(
	pair<double, double>& a, 	
	pair<double, double>& b, 
	pair<double, double>& c 
) {
	double x0 = b.first - a.first;
	double y0 = b.second - a.second;
	double x1 = c.first - b.first;
	double y1 = c.second - b.second;
	double val = x0 * y1 - y0 * x1;
	if (val == 0)
		return 0;
	else if (val > 0)
		return 1;
	else
		return -1;
}

bool intersect(
	pair<double, double>& a,
	pair<double, double>& b,
	pair<double, double>& c,
	pair<double, double>& d	
) {
	if (a.first > b.first)
		return intersect(b, a, c, d);
	if (c.first > d.first)
		return intersect(a, b, d, c);
	if (a.first > c.first)
		return intersect(c, d, a, b);
	
	int val0 = ccw(a, b, c) * ccw(a, b, d);
	int val1 = ccw(c, d, a) * ccw(c, d, b);
	if(!val0 && !val1)
		return a.first <= d.first && c.first <= b.first;
	else if (!val0)
		return val1 < 0;
	else if (!val1)
		return val0 < 0;	
	else 
		return val0 < 0 && val1 < 0;	
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
	/*
	// renew isIn, inner line cannot be cross
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			isIn[i][j] = isIn[j][i] = 1;
			for (int k = 0; k < n; k++) {
				if (intersect(P[i], P[j], P[k], P[(k + 1) % n])) {
					// cout << i << " " << j << " and " << ii << " " << jj << " intersect" << endl;
					isIn[i][j] = isIn[j][i] = 0;
					break;
				}
			}
		}	
	}
	
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			if (abs(i - j) % n == 1 || abs(i - j) % n == n - 1) {
				isIn[i][j] = isIn[j][i] = 1;
				continue;
			}
			if (!isIn[i][j])
				continue;
			
			pair<double, double> m = {(P[i].first + P[j].first) / 2 + 0.001, (P[i].second + P[j].second) / 2};
			pair<double, double> e = {m.first, 1000001};
			int cnt = 0;
			for (int k = 0; k < n; k++) {
				if(intersect(m, e, P[k], P[(k + 1) % n])) {
			//		cout << k << " " << (k + 1) % n << " intersect" << endl;			
					cnt++;
				}
			}		
			//cout << i << " " << j << " " << m.first << " " << m.second << " has cnt " << cnt << endl;			
			if (cnt % 2 == 0)
				isIn[i][j] = isIn[j][i] = 0;	
		}
	}
	*/
	
	for (int i = 0; i < n; i++)
		isIn[i][(i + 1) % n] = isIn[(i + 1) % n][i] = 1;

	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			if (abs(i - j) % n == 1 || abs(i - j) % n == n - 1)
				continue;
			
			pair<double, double> m = {(P[i].first + P[j].first) / 2, (P[i].second + P[j].second) / 2};
			pair<double, double> e = {m.first + 1, 1000001};
			int cnt = 0;
			bool intersected = false;
			for (int k = 0; k < n; k++) {	
				if(intersect(m, e, P[k], P[(k + 1) % n])) {
			//		cout << k << " " << (k + 1) % n << " intersect" << endl;			
					cnt++;
				}
				
				if (i == k || i == (k + 1) % n || j == k || j == (k + 1) % n )
					continue;
				
				if(intersect(P[i], P[j], P[k], P[(k + 1) % n])) {
					intersected = true;
					break;
				}
			}		
			//cout << i << " " << j << " " << m.first << " " << m.second << " has cnt " << cnt << endl;			
			if (intersected || cnt % 2 == 0)
				isIn[i][j] = isIn[j][i] = 0;	
			else
				isIn[i][j] = isIn[j][i] = 1;	
		}
	}
	
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