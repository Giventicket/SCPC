#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>

using namespace std;

#define MAXN 200001
int N;
vector<long long int> A, B;
long long int dp[MAXN][5];

void input() {
	memset(dp, 0, sizeof(dp));
	cin >> N;
	A = vector<long long int>(N);
	B = vector<long long int>(N);
	for (int i = 0; i < N; i++)
		cin >> A[i];
	for (int i = 0; i < N; i++)
		cin >> B[i];
	sort(A.begin(), A.end());
	sort(B.begin(), B.end());
	return;
}

void solve(){
	dp[0][0] = abs(A[0]-B[0]);
	
	dp[1][0] = dp[0][0] + abs(A[1]-B[1]);
	dp[1][1] = abs(A[1]-B[0]);
	dp[1][2] = abs(A[0]-B[1]);
	dp[1][3] = dp[0][0];
	dp[1][4] = min(min(dp[1][0], dp[1][1]), min(dp[1][2], dp[1][3]));
	dp[1][4] = min(dp[1][4], dp[0][4] + abs(A[1]-B[1]));
	
	for (int i = 1; i < N-1; i++) {
		dp[i+1][0] = dp[i][0] + abs(A[i+1]-B[i+1]);		
		
		dp[i+1][1] = min(
			dp[i-1][0] + abs(A[i+1]-B[i]), 
			dp[i][1] + abs(A[i+1]-B[i])
		);
		
		dp[i+1][2] = min(
			dp[i-1][0] + abs(A[i]-B[i+1]), 
			dp[i][2] + abs(A[i]-B[i+1])
		);
		
		dp[i+1][3] = dp[i][0];
		
		dp[i+1][4] = min(min(dp[i+1][0], dp[i+1][1]), min(dp[i+1][2], dp[i+1][3]));
		dp[i+1][4] = min(dp[i+1][4], dp[i][4] + abs(A[i+1]-B[i+1]));
	}
	return;
}

int main(){
	freopen("input.txt", "r", stdin);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);  
	cout.tie(NULL);
	
	int T;
	cin >> T;
	
	for (int t = 1; t <= T; t++) {
		// inputs
		cout << "Case #" << t << "\n";
		input();
		solve();
		cout << dp[N-1][4] << "\n";
	}
	
	return 0;
}
