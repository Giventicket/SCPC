#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define INF 360000000000001
#define UNDEFINED 360000000000000

typedef long long int ll;
int N; 
ll K;
vector<vector<ll>> arr, 
left_up_ksum, right_down_ksum, 
vertical_long_sum, horizontal_long_sum, 
left_triangle_sum, right_triangle_sum, up_triangle_sum, down_triangle_sum,
santan_sum;

void update_left_up_ksum(int i, int j);
void update_right_down_ksum(int i, int j);
void update_vertical_long_sum(int i, int j);
void update_horizontal_long_sum(int i, int j);
void update_left_triangle_sum(int i, int j);
void update_right_triangle_sum(int i, int j);
void update_santan_sum(int i, int j);

void input() {
	//cout << "input" << endl;
	cin >> N >> K;
	
	arr.clear();
	left_up_ksum.clear();
	right_down_ksum.clear();
	vertical_long_sum.clear();
	horizontal_long_sum.clear();
	left_triangle_sum.clear();
	right_triangle_sum.clear();
	up_triangle_sum.clear();
	down_triangle_sum.clear();
	santan_sum.clear();
	
	arr.resize(N + 2 * K - 2);
	for (int i = 0; i < N + 2 * K - 2; i++)
		arr[i].resize(N + 2 * K - 2);
	
	left_up_ksum.resize(N + 2 * K - 2);
	for (int i = 0; i < N + 2 * K - 2; i++)
		left_up_ksum[i] = vector<ll>(N + 2 * K - 2, UNDEFINED);

	right_down_ksum.resize(N + 2 * K - 2);
	for (int i = 0; i < N + 2 * K - 2; i++)
		right_down_ksum[i] = vector<ll>(N + 2 * K - 2, UNDEFINED);

	vertical_long_sum.resize(N);
	for (int i = 0; i < N; i++)
		vertical_long_sum[i] = vector<ll>(N, UNDEFINED);
	
	horizontal_long_sum.resize(N);
	for (int i = 0; i < N; i++)
		horizontal_long_sum[i] = vector<ll>(N, UNDEFINED);
	
	left_triangle_sum.resize(N);
	for (int i = 0; i < N; i++)
		left_triangle_sum[i] = vector<ll>(N, UNDEFINED);
	
	right_triangle_sum.resize(N);
	for (int i = 0; i < N; i++)
		right_triangle_sum[i] = vector<ll>(N, UNDEFINED);

	up_triangle_sum.resize(N);
	for (int i = 0; i < N; i++)
		up_triangle_sum[i] = vector<ll>(N, UNDEFINED);
	
	down_triangle_sum.resize(N);
	for (int i = 0; i < N; i++)
		down_triangle_sum[i] = vector<ll>(N, UNDEFINED);
	
	santan_sum.resize(N);
	for (int i = 0; i < N; i++)
		santan_sum[i] = vector<ll>(N, UNDEFINED);
	
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			cin >> arr[i + K - 1][j + K - 1]; 
	
	return;
}

void update_left_up_ksum(int i, int j) {
	//cout << "update_left_up_ksum" << endl;
	if (left_up_ksum[i][j] != UNDEFINED)
		return;
		
	else if (i - K + 1 < 0 || j + K - 1 >= N + 2 * K - 2) {
		left_up_ksum[i][j] = INF;
		return;
	} else if (i + 1 >= N + 2 * K - 2 || j - 1 < 0) {
		left_up_ksum[i][j] = 0;
		for (ll k = 0; k < K; k++)
			left_up_ksum[i][j] += arr[i - k][j + k];
		return;
	} else {
		update_left_up_ksum(i + 1, j - 1);
		left_up_ksum[i][j] = left_up_ksum[i + 1][j - 1] - arr[i + 1][j - 1] + arr[i - K + 1][j + K - 1];
		return;	
	}	
}

void update_right_down_ksum(int i, int j) {
	//cout << "update_right_down_ksum" << endl;
	if (right_down_ksum[i][j] != UNDEFINED)
		return;
	else if (i + K - 1 >= N + 2 * K - 2 || j + K - 1 >= N + 2 * K - 2) {
		right_down_ksum[i][j] = INF;
		return;
	} else if (i - 1 < 0 || j - 1 < 0) {
		right_down_ksum[i][j] = 0;
		for (ll k = 0; k < K; k++)
			right_down_ksum[i][j] += arr[i + k][j + k];
		return;
	} else {
		update_right_down_ksum(i - 1, j - 1);
		right_down_ksum[i][j] = right_down_ksum[i - 1][j - 1] - arr[i - 1][j - 1] + arr[i + K - 1][j + K - 1];
		return;	
	}	
}

void update_vertical_long_sum(int i, int j) {
	//cout << "update_vertical_long_sum" << endl;
	
	if (vertical_long_sum[i][j] != UNDEFINED) {
		return;
	}
		
	int ii = i + K - 1;
	int jj = j + K - 1;

	if (i == 0) {
		vertical_long_sum[i][j] = 0;
		for (ll k = -K + 1; k <= K - 1; k++)
			vertical_long_sum[i][j] += arr[ii + k][jj];
		return;
	} 

	update_vertical_long_sum(i - 1, j);
	vertical_long_sum[i][j] = vertical_long_sum[i - 1][j] - arr[ii - K][jj] + arr[ii + K - 1][jj];
	return;
}

void update_horizontal_long_sum(int i, int j) {
	//cout << "update_horizontal_long_sum" << endl;
	
	if (horizontal_long_sum[i][j] != UNDEFINED) {
		return;
	}
		
	int ii = i + K - 1;
	int jj = j + K - 1;

	if (j == 0) {
		horizontal_long_sum[i][j] = 0;
		for (ll k = -K + 1; k <= K - 1; k++)
			horizontal_long_sum[i][j] += arr[ii][jj + k];
		return;
	} 

	update_horizontal_long_sum(i, j - 1);
	horizontal_long_sum[i][j] = horizontal_long_sum[i][j - 1] - arr[ii][jj - K] + arr[ii][jj + K - 1];
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
		for (ll k = 0; k < K; k++) {
			for (int l = 0; l <= k; l++) {
				left_triangle_sum[i][j] += arr[ii + l][jj - k + l];
				left_triangle_sum[i][j] += arr[ii - l][jj - k + l];
			}
			left_triangle_sum[i][j] -= arr[ii][jj - k];	
		}
		return;
	} else if (j != 0) {
		update_left_triangle_sum(i, j - 1);
		update_left_up_ksum(ii, jj - K);
		update_right_down_ksum(ii, jj - K);
		update_vertical_long_sum(i, j);
		left_triangle_sum[i][j] = left_triangle_sum[i][j - 1] - (left_up_ksum[ii][jj - K] + right_down_ksum[ii][jj - K] - arr[ii][jj - K]) + vertical_long_sum[i][j];
		return;
	} else {

	update_left_triangle_sum(i - 1, j);
	update_left_up_ksum(ii - 1, jj - K + 1);
	update_right_down_ksum(ii, jj - K + 1);
	left_triangle_sum[i][j] = left_triangle_sum[i - 1][j] - left_up_ksum[ii - 1][jj - K + 1] + right_down_ksum[ii][jj - K + 1];
	return;
	}
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
		for (ll k = 0; k < K; k++) {
			for (int l = 0; l <= k; l++) {
				right_triangle_sum[i][j] += arr[ii + l][jj + k - l];
				right_triangle_sum[i][j] += arr[ii - l][jj + k - l];
			}
			right_triangle_sum[i][j] -= arr[ii][jj + k];
		}
		return;
	} else if (j != 0) {
		update_right_triangle_sum(i, j - 1);
		update_vertical_long_sum(i, j - 1);
		update_left_up_ksum(ii + K - 1, jj);
		update_right_down_ksum(ii - K + 1, jj);
		right_triangle_sum[i][j] = right_triangle_sum[i][j - 1] - vertical_long_sum[i][j - 1] + (left_up_ksum[ii + K - 1][jj] + right_down_ksum[ii - K + 1][jj] - arr[ii][jj + K - 1]);
		return;
	} else {
		update_right_triangle_sum(i - 1, j);
		update_right_down_ksum(ii - K, jj);
		update_left_up_ksum(ii + K - 1, jj);
		right_triangle_sum[i][j] = right_triangle_sum[i - 1][j] - right_down_ksum[ii - K][jj] + left_up_ksum[ii + K - 1][jj];
		return;
	}
}

void update_up_triangle_sum(int i, int j) {
	//cout << "update_up_triangle_sum" << i << j << endl;
	
	if (up_triangle_sum[i][j] != UNDEFINED) {
		return;
	}
		
	int ii = i + K - 1;
	int jj = j + K - 1;

	if (i == 0 && j == 0) {
		up_triangle_sum[i][j] = 0;
		for (ll k = 0; k < K; k++) {
			for (int l = 0; l <= k; l++) {
				up_triangle_sum[i][j] += arr[ii - k + l][jj + l];
				up_triangle_sum[i][j] += arr[ii - k + l][jj - l];
			}
			up_triangle_sum[i][j] -= arr[ii - k][jj];
		}
		return;
	} else if (j != 0) {
		update_up_triangle_sum(i, j - 1);
		update_left_up_ksum(ii, jj - K);
		update_right_down_ksum(ii - K + 1, jj);
		up_triangle_sum[i][j] = up_triangle_sum[i][j - 1] - left_up_ksum[ii][jj - K] + right_down_ksum[ii - K + 1][jj];
		return;
	} else {
		update_up_triangle_sum(i - 1, j);
		update_right_down_ksum(ii - K, jj);
		update_left_up_ksum(ii - 1, jj - K + 1);
		update_horizontal_long_sum(i, j);
		up_triangle_sum[i][j] = up_triangle_sum[i - 1][j] - (left_up_ksum[ii - 1][jj - K + 1] + right_down_ksum[ii - K][jj] - arr[ii - K][jj]) + horizontal_long_sum[i][j];
		return;
	}
}

void update_down_triangle_sum(int i, int j) {
	//cout << "update_down_triangle_sum" << i << j << endl;
	
	if (down_triangle_sum[i][j] != UNDEFINED) {
		return;
	}
		
	int ii = i + K - 1;
	int jj = j + K - 1;

	if (i == 0 && j == 0) {
		down_triangle_sum[i][j] = 0;
		for (ll k = 0; k < K; k++) {
			for (int l = 0; l <= k; l++) {
				down_triangle_sum[i][j] += arr[ii + k - l][jj + l];
				down_triangle_sum[i][j] += arr[ii + k - l][jj - l];
			}
			down_triangle_sum[i][j] -= arr[ii + k][jj];
		}
		return;
	} else if (j != 0) {
		update_down_triangle_sum(i, j - 1);
		update_right_down_ksum(ii, jj - K);
		update_left_up_ksum(ii + K - 1, jj);
		down_triangle_sum[i][j] = down_triangle_sum[i][j - 1] - right_down_ksum[ii][jj - K] + left_up_ksum[ii + K - 1][jj];
		return;
	} else {
		update_down_triangle_sum(i - 1, j);
		update_left_up_ksum(ii + K - 1, jj);
		update_right_down_ksum(ii, jj - K + 1);
		update_horizontal_long_sum(i - 1, j);
		down_triangle_sum[i][j] = down_triangle_sum[i - 1][j] + (right_down_ksum[ii][jj - K + 1] + left_up_ksum[ii + K - 1][jj] - arr[ii - K + 1][jj]) - horizontal_long_sum[i - 1][j];
		return;
	}
}

void update_santan_sum(int i, int j) {
	//cout << "update_santan_sum" << endl;
	if (santan_sum[i][j] != UNDEFINED)
		return;
	
	int ii = i + K - 1;
	int jj = j + K - 1;
	
	if (i == 0 && j == 0) {
		santan_sum[i][j] = K * arr[ii][jj];
		for (ll k = 0; k < K; k++) {
			for (int l = 0; l <= k; l++) {
				santan_sum[i][j] += (K - k) * arr[ii + l][jj + k - l];
				santan_sum[i][j] += (K - k) * arr[ii + k - l][jj - l];
				santan_sum[i][j] += (K - k) * arr[ii - l][jj - k + l];
				santan_sum[i][j] += (K - k) * arr[ii - k + l][jj + l];
			}
			santan_sum[i][j] -= (K - k) * arr[ii][jj + k];
			santan_sum[i][j] -= (K - k) * arr[ii + k][jj];
			santan_sum[i][j] -= (K - k) * arr[ii][jj - k];
			santan_sum[i][j] -= (K - k) * arr[ii - k][jj];
		}
		return;
	} else if (j != 0) {
		update_santan_sum(i, j - 1);
		update_left_triangle_sum(i, j - 1);
		update_right_triangle_sum(i, j);
		santan_sum[i][j] = santan_sum[i][j - 1] - left_triangle_sum[i][j - 1] + right_triangle_sum[i][j];
		return;	
	} else {
		update_santan_sum(i - 1, j);
		update_up_triangle_sum(i - 1, j);
		update_down_triangle_sum(i, j);
		santan_sum[i][j] = santan_sum[i][j - 1] - up_triangle_sum[i][j - 1] + down_triangle_sum[i][j];
		return;	
	}
}

void solve() {
	//cout << "solve" << endl;
	
	for (int i = 0; i < N + 2 * K - 2; i++) {
			for (int j = 0; j < N + 2 * K - 2; j++) {
				update_left_up_ksum(i, j);
				update_right_down_ksum(i, j);
				//cout << "left_up_ksum " << i << " " << j << " " << left_up_ksum[i][j] << endl;
				//cout << "right_down_ksum " << i << " " << j << " " << right_down_ksum[i][j] << endl;
		}
	}
	
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++) {
			update_vertical_long_sum(i, j);
			update_horizontal_long_sum(i, j);
			//cout << "vertical_long_sum " << i << " " << j << " " << vertical_long_sum[i][j] << endl;
			//cout << "horizontal_long_sum " << i << " " << j << " " << horizontal_long_sum[i][j] << endl;
		}
		
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++) {
			update_left_triangle_sum(i, j);
			update_right_triangle_sum(i, j);
			//cout << "left_triangle_sum " << i << " " << j << " " << left_triangle_sum[i][j] << endl;
			//cout << "right_triangle_sum " << i << " " << j << " " << right_triangle_sum[i][j] << endl;
		}
	
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++) {
			update_up_triangle_sum(i, j);
			update_down_triangle_sum(i, j);
			//cout << "up_triangle_sum " << i << " " << j << " " << up_triangle_sum[i][j] << endl;
			//cout << "down_triangle_sum " << i << " " << j << " " << down_triangle_sum[i][j] << endl;
		}
	
	ll ans = 0;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++) {
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
