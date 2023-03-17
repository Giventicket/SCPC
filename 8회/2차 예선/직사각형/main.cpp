#include <iostream>
#include <cstring>
#include <cmath>
#include <tuple>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;

int N;
vector<vector<int>> matrix;
int min_table[9][256][9][256]; // (jr, ir, jc, ic)
int max_table[9][256][9][256]; // (jr, ir, jc, ic)

void input() {
	// cout << "input" << endl;
	cin >> N;
	matrix.resize(N);
	memset(min_table, 0, sizeof(min_table));
	memset(max_table, 0, sizeof(max_table));
	for (int i = 0; i < N; i++)
		matrix[i].resize(N);
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
		cin >> matrix[i][j];
	return;
}

void precomute () {
	for (int ir = 0; ir < N; ir++) {
		for (int ic = 0; ic < N; ic++) {
			min_table[0][ir][0][ic] = matrix[ir][ic];
			max_table[0][ir][0][ic] = matrix[ir][ic];
		}
		
		for (int jc = 1; jc <= (int) log2(N); jc++) {
			for (int ic = 0; ic < N; ic++) {
				min_table[0][ir][jc][ic] = min(min_table[0][ir][jc - 1][ic], min_table[0][ir][jc - 1][ic + (int) pow(2, jc - 1)]);
				max_table[0][ir][jc][ic] = min(max_table[0][ir][jc - 1][ic], max_table[0][ir][jc - 1][ic + (int) pow(2, jc - 1)]);
			}
		}
	}
	
	for (int jr = 1; jr <= (int) log2(N); jr++) {
		for (int ir = 0; ir < N; ir++) {
			for (int jc = 1; jc <= (int) log2(N); jc++) {
				for (int ic = 0; ic < N; ic++) {
					min_table[jr][ir][jc][ic] = min(min_table[jr - 1][ir][jc][ic], min_table[jr - 1][ir + (int) pow(2, jr - 1)][jc][ic]);
					max_table[jr][ir][jc][ic] = min(max_table[jr - 1][ir][jc][ic], max_table[jr - 1][ir + (int) pow(2, jr - 1)][jc][ic]);
				}
			}
		}
	}
	
	return;
}

int min_query (int x1, int y1, int x2, int y2) {
	int kx = log2(x2 - x1 + 1);
	int ky = log2(y2 - y1 + 1);
	int min1 = min(min_table[kx][x1][ky][y1], min_table[kx][x1][ky][y2 - (int) pow(2, ky) + 1]);
	int min2 = min(min_table[kx][x2 - (int) pow(2, kx) + 1][ky][y1], min_table[kx][x2 - (int) pow(2, kx) + 1][ky][y2 - (int) pow(2, ky) + 1]);
	return min(min1, min2);
}

int max_query (int x1, int y1, int x2, int y2) {
	int kx = log2(x2 - x1 + 1);
	int ky = log2(y2 - y1 + 1);
	int max1 = max(max_table[kx][x1][ky][y1], max_table[kx][x1][ky][y2 - (int) pow(2, ky) + 1]);
	int max2 = max(max_table[kx][x2 - (int) pow(2, kx) + 1][ky][y1], max_table[kx][x2 - (int) pow(2, kx) + 1][ky][y2 - (int) pow(2, ky) + 1]);
	return max(max1, max2);
}

int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, -1, 0, 1};

void solve() {
	cout << "solve" << endl;
	int answer = 0;
			
	for (int r = 0; r < N; r++) {
		for (int c = 0; c < N; c++) {
			int i = r;
			int j = c;
			int ii = r;
			int jj = c;
			
			while (true) {
				vector<tuple<int, pair<int, int>, pair<int, int>>> candidates;
				
				for (int x = 0; x < 2; x++) {
					for (int y = 0; y < 2; y++) {
						int next_i = i + dx[x];
						int next_j = j + dx[y];
						
						if (next_i < 0 || next_i >= N || next_j < 0 || next_j >= N)
							continue;	
						if (min_query(next_i, next_j, ii, jj) != matrix[r][c])
							continue;
						
						candidates.emplace_back(max_query(next_i, next_j, ii, jj), make_pair(next_i, next_j), make_pair(ii, jj));
					}
				}	

				for (int x = 2; x < 4; x++) {
					for (int y = 2; y < 4; y++) {
						int next_ii = ii + dx[x];
						int next_jj = jj + dx[y];
						
						if (next_ii < 0 || next_ii >= N || next_jj < 0 || next_jj >= N)
							continue;	
						if (min_query(i, j, next_ii, next_jj) != matrix[r][c])
							continue;
						
						candidates.emplace_back(max_query(i, j, next_ii, next_jj), make_pair(i, j), make_pair(next_ii, next_jj));
					}
				}	

				sort(candidates.begin(), candidates.end());
				int M = get<0>(candidates[0]);
				auto [i, j] = get<1>(candidates[0]);
				auto [ii, jj] = get<2>(candidates[0]);
				
				int sz = (ii - i + 1) * (jj - j + 1);
				if (sz == M - matrix[r][c] + 1)
					answer++;
			}
		}
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