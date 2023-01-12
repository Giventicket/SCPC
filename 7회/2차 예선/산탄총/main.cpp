#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define INF 360000000000001
#define UNDEFINED 360000000000000

typedef long long int ll;
int N; 
ll K;
vector<vector<ll>> arr, left_up_ksum, right_down_ksum, long_sum, left_triangle_sum, right_triangle_sum, santan_sum;

void input() {
	//cout << "input" << endl;
	cin >> N >> K;
	
	arr.clear();
	left_up_ksum.clear();
	right_down_ksum.clear();
	long_sum.clear();
	left_triangle_sum.clear();
	right_triangle_sum.clear();
	santan_sum.clear();
	
	arr.resize(N + 4 * K - 2);
	for (int i = 0; i < N + 4 * K - 2; i++)
		arr[i].resize(N + 4 * K - 2);
	
	left_up_ksum.resize(N + 4 * K - 2);
	for (int i = 0; i < N + 4 * K - 2; i++)
		left_up_ksum[i] = vector<ll>(N + 4 * K - 2, UNDEFINED);

	right_down_ksum.resize(N + 4 * K - 2);
	for (int i = 0; i < N + 4 * K - 2; i++)
		right_down_ksum[i] = vector<ll>(N + 4 * K - 2, UNDEFINED);

	long_sum.resize(N + 2 * K);
	for (int i = 0; i < N + 2 * K; i++)
		long_sum[i] = vector<ll>(N + 2 * K, UNDEFINED);
	
	left_triangle_sum.resize(N + 2 * K);
	for (int i = 0; i < N + 2 * K; i++)
		left_triangle_sum[i] = vector<ll>(N + 2 * K, UNDEFINED);
	
	right_triangle_sum.resize(N + 2 * K);
	for (int i = 0; i < N + 2 * K; i++)
		right_triangle_sum[i] = vector<ll>(N + 2 * K, UNDEFINED);
	
	santan_sum.resize(N + 2 * K);
	for (int i = 0; i < N + 2 * K; i++)
		santan_sum[i] = vector<ll>(N + 2 * K, UNDEFINED);
	
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> arr[i + 2 * K - 1][j + 2 * K - 1]; 
		}
	}
	
	return;
}

void update_left_up_ksum(int i, int j) {
	//cout << "update_left_up_ksum" << endl;
	if (left_up_ksum[i][j] != UNDEFINED)
		return;
		
	else if (i - K + 1 < 0 || j + K - 1 >= N + 4 * K - 2) {
		left_up_ksum[i][j] = INF;
		return;
	} else if (i + 1 >= N + 4 * K - 2 || j - 1 < 0) {
		left_up_ksum[i][j] = 0;
		for (ll k = 0; k < K; k++)
			left_up_ksum[i][j] += arr[i - k][j + k];
		return;
	}
	update_left_up_ksum(i + 1, j - 1);
	left_up_ksum[i][j] = left_up_ksum[i + 1][j - 1] - arr[i + 1][j - 1] + arr[i - K + 1][j + K - 1];
	return;
}

void update_right_down_ksum(int i, int j) {
	//cout << "update_right_down_ksum" << endl;
	if (right_down_ksum[i][j] != UNDEFINED)
		return;
	else if (i + K - 1 >= N + 4 * K - 2 || j + K - 1 >= N + 4 * K - 2) {
		right_down_ksum[i][j] = INF;
		return;
	} else if (i - 1 < 0 || j - 1 < 0) {
		right_down_ksum[i][j] = 0;
		for (ll k = 0; k < K; k++)
			right_down_ksum[i][j] += arr[i + k][j + k];
		return;
	} 
	
	update_right_down_ksum(i - 1, j - 1);
	right_down_ksum[i][j] = right_down_ksum[i - 1][j - 1] - arr[i - 1][j - 1] + arr[i + K - 1][j + K - 1];
	return;
}

void update_long_sum(int i, int j) {
	//cout << "update_long_sum" << endl;
	
	if (long_sum[i][j] != UNDEFINED) {
		return;
	}
		
	int ii = i + K - 1;
	int jj = j + K - 1;

	if (i == 0) {
		long_sum[i][j] = 0;
		for (ll k = -K + 1; k <= K - 1; k++)
			long_sum[i][j] += arr[ii + k][jj];
		return;
	} 

	update_long_sum(i - 1, j);
	long_sum[i][j] = long_sum[i - 1][j] - arr[ii - K][jj] + arr[ii + K - 1][jj];
	return;
}

void update_left_triangle_sum(int i, int j) {
	//cout << "update_left_triangle_sum" << endl;
	
	if (left_triangle_sum[i][j] != UNDEFINED) {
		return;
	}
		
	int ii = i + K - 1;
	int jj = j + K - 1;

	if (i == 0 && j == 0) {
		left_triangle_sum[i][j] = 0;
		return;
	} else if (j != 0) {
		update_left_triangle_sum(i, j - 1);
		update_left_up_ksum(ii, jj - K);
		update_right_down_ksum(ii, jj - K);
		update_long_sum(i, j);
		left_triangle_sum[i][j] = left_triangle_sum[i][j - 1] - (left_up_ksum[ii][jj - K] + right_down_ksum[ii][jj - K] - arr[ii][jj - K]) + long_sum[i][j];
		return;
	}

	update_left_triangle_sum(i - 1, j);
	update_left_up_ksum(ii - 1, jj - K + 1);
	update_right_down_ksum(ii, jj - K + 1);
	left_triangle_sum[i][j] = left_triangle_sum[i - 1][j] - left_up_ksum[ii - 1][jj - K + 1] + right_down_ksum[ii][jj - K + 1];
	return;
}

void update_right_triangle_sum(int i, int j) {
	//cout << "update_right_triangle_sum" << i << j << endl;
	
	if (right_triangle_sum[i][j] != UNDEFINED) {
		return;
	}
		
	int ii = i + K - 1;
	int jj = j + K - 1;

	if (i == 0 && j == 0) {
		right_triangle_sum[i][j] = 0;
		return;
	} else if (j != 0) {
		update_right_triangle_sum(i, j - 1);
		update_long_sum(i, j - 1);
		update_left_up_ksum(ii + K - 1, jj);
		update_right_down_ksum(ii - K + 1, jj);
		right_triangle_sum[i][j] = right_triangle_sum[i][j - 1] - long_sum[i][j - 1] + (left_up_ksum[ii + K - 1][jj] + right_down_ksum[ii - K + 1][jj] - arr[ii][jj + K - 1]);
		return;
	}

	update_right_triangle_sum(i - 1, j);
	update_right_down_ksum(ii - K, jj);
	update_left_up_ksum(ii + K - 1, jj);
	right_triangle_sum[i][j] = right_triangle_sum[i - 1][j] - right_down_ksum[ii - K][jj] + left_up_ksum[ii + K - 1][jj];
	return;
}

void update_santan_sum(int i, int j) {
	//cout << "update_santan_sum" << endl;
	if (santan_sum[i][j] != UNDEFINED)
		return;
	
	int ii = i + K - 1;
	int jj = j + K - 1;
	
	if (i == 0 && j == 0) {
		santan_sum[i][j] = 0;
		return;
	} else if (j != 0) {
		update_santan_sum(i, j - 1);
		update_left_triangle_sum(i, j - 1);
		update_right_triangle_sum(i, j);
		santan_sum[i][j] = santan_sum[i][j - 1] - left_triangle_sum[i][j - 1] + right_triangle_sum[i][j];
		return;	
	}
	
	update_santan_sum(i - 1, j);
	update_left_up_ksum(ii - 1, jj - K + 1);
	update_right_down_ksum(ii - K, jj);
	update_right_down_ksum(ii, jj - K + 1);
	update_left_up_ksum(ii + K - 1, jj);
	santan_sum[i][j] = santan_sum[i - 1][j];
	santan_sum[i][j] -= left_up_ksum[ii - 1][jj - K + 1] + right_down_ksum[ii - K][jj] - arr[ii - K][jj];
	santan_sum[i][j] += right_down_ksum[ii][jj - K + 1] + left_up_ksum[ii + K - 1][jj] - arr[ii + K - 1][jj];
	return;
}

void solve() {
	//cout << "solve" << endl;
	/*
	for (int i = 0; i < N + 4 * K - 2; i++) {
		for (int j = 0; j < N + 4 * K - 2; j++) {
			cout << arr[i][j] << " ";
		}
		cout << endl;
	}
	*/
	
	/*
	for (int i = 0; i < N + 4 * K - 2; i++) {
			for (int j = 0; j < N + 4 * K - 2; j++) {
				update_left_up_ksum(i, j);
				update_right_down_ksum(i, j);
				//cout << "left_up_ksum " << i << " " << j << " " << left_up_ksum[i][j] << endl;
				//cout << "right_down_ksum " << i << " " << j << " " << right_down_ksum[i][j] << endl;
		}
	}
	
	for (int i = 0; i < N + 2 * K; i++)
		for (int j = 0; j < N + 2 * K; j++) {
			update_long_sum(i, j);
			//cout << "long_sum " << i << " " << j << " " << long_sum[i][j] << endl;
		}
	
	for (int i = 0; i < N + 2 * K; i++)
		for (int j = 0; j < N + 2 * K; j++) {
			update_left_triangle_sum(i, j);
			update_right_triangle_sum(i, j);
			//cout << "left_triangle_sum " << i << " " << j << " " << left_triangle_sum[i][j] << endl;
			//cout << "right_triangle_sum " << i << " " << j << " " << right_triangle_sum[i][j] << endl;
		}
			
	*/
	ll ans = -INF;
	for (int i = 0; i < N + 2 * K; i++)
		for (int j = 0; j < N + 2 * K; j++) {
			update_santan_sum(i, j);
			//cout << "santan " << i << " " << j << " " << santan_sum[i][j] << endl;
			ans = max(ans, santan_sum[i][j]);
		}
	
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
