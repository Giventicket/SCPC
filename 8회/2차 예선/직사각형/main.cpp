#include <iostream>
#include <cstring>
#include <cmath>
#include <tuple>
#include <vector>
#include <algorithm>
#include <unordered_map>


using namespace std;

typedef long long ll;

int N;
int matrix[256][256];
int min_table[9][256][9][256]; // (jr, ir, jc, ic)
int max_table[9][256][9][256]; // (jr, ir, jc, ic)

int pow_result[] = {1, 2, 4, 8, 16, 32, 64, 128, 256};
int pow(int x, int y) {
	return pow_result[y];
}

int log2(int x)
{
	long long y = x;
    return 64 - __builtin_clzl(y) - 1;
}


void input() {
	// cout << "input" << endl;
	cin >> N;
	memset(matrix, 0, sizeof(matrix));
	memset(min_table, 0, sizeof(min_table));
	memset(max_table, 0, sizeof(max_table));
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
		cin >> matrix[i][j];
	return;
}

void precomute () {
	// cout << "precomute" << endl;
	
	for (int ir = 0; ir < N; ir++) {
		for (int ic = 0; ic < N; ic++) {
			min_table[0][ir][0][ic] = matrix[ir][ic];
			max_table[0][ir][0][ic] = matrix[ir][ic];
		}
		
		for (int jc = 1; jc <= (int) log2(N); jc++) {
			for (int ic = 0; ic < N; ic++) {
				min_table[0][ir][jc][ic] = min(min_table[0][ir][jc - 1][ic], min_table[0][ir][jc - 1][ic + (int) pow(2, jc - 1)]);
				max_table[0][ir][jc][ic] = max(max_table[0][ir][jc - 1][ic], max_table[0][ir][jc - 1][ic + (int) pow(2, jc - 1)]);
			}
		}
	}
	
	for (int jr = 1; jr <= (int) log2(N); jr++) {
		for (int ir = 0; ir < N; ir++) {
			for (int jc = 0; jc <= (int) log2(N); jc++) {
				for (int ic = 0; ic < N; ic++) {
					min_table[jr][ir][jc][ic] = min(min_table[jr - 1][ir][jc][ic], min_table[jr - 1][ir + (int) pow(2, jr - 1)][jc][ic]);
					max_table[jr][ir][jc][ic] = max(max_table[jr - 1][ir][jc][ic], max_table[jr - 1][ir + (int) pow(2, jr - 1)][jc][ic]);
				}
			}
		}
	}
	
	return;
}

int min_query (int x1, int y1, int x2, int y2) {
	// cout << "min_query " << x1 << " " << y1 << " " << x2 << " " << y2 << endl;
	int kx = log2(x2 - x1 + 1);
	int ky = log2(y2 - y1 + 1);
	int min1 = min(min_table[kx][x1][ky][y1], min_table[kx][x1][ky][y2 - (int) pow(2, ky) + 1]);
	int min2 = min(min_table[kx][x2 - (int) pow(2, kx) + 1][ky][y1], min_table[kx][x2 - (int) pow(2, kx) + 1][ky][y2 - (int) pow(2, ky) + 1]);
	return min(min1, min2);
}

int max_query (int x1, int y1, int x2, int y2) {
	// cout << "max_query " << x1 << " " << y1 << " " << x2 << " " << y2 << endl;
	int kx = log2(x2 - x1 + 1);
	int ky = log2(y2 - y1 + 1);
	int max1 = max(max_table[kx][x1][ky][y1], max_table[kx][x1][ky][y2 - (int) pow(2, ky) + 1]);
	int max2 = max(max_table[kx][x2 - (int) pow(2, kx) + 1][ky][y1], max_table[kx][x2 - (int) pow(2, kx) + 1][ky][y2 - (int) pow(2, ky) + 1]);
	return max(max1, max2);
}

int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, -1, 0, 1};

void solve() {
	// cout << "solve" << endl;
	precomute();
	
	int answer = N * N;
			
	for (int r = 0; r < N; r++) {
		for (int c = 0; c < N; c++) {
			int i = r;
			int j = c;
			int ii = r;
			int jj = c;
			
			// cout <<  "matrix[r][c] " << " " << r << " " << c << " " << matrix[r][c] << endl;
			vector<bool> blocked(4);
			while (true) {
				// cout << i << " " << j << " " << ii << " " << jj << endl;
				int M = N * N + 1;
				int i_candi = -1;
				int j_candi = -1;
				int ii_candi = -1;
				int jj_candi = -1;
				
				for (int idx = 0; idx < 2; idx++) {
					if (blocked[idx])
						continue;
					int next_i = i + dx[idx];
					int next_j = j + dy[idx];
					
					// cout << "for loop " << next_i << " " << next_j << " " << ii << " " << jj << endl;
					
					if (next_i < 0 || next_i >= N || next_j < 0 || next_j >= N)
						continue;	
					
					// cout << "min_query " << min_query(next_i, next_j, ii, jj)  << " " <<  matrix[r][c] << endl;
					
					if (min_query(next_i, next_j, ii, jj) != matrix[r][c]) {
						blocked[idx] = true;
						continue;
					}
					
					int m = max_query(next_i, next_j, ii, jj);
					
					if (M > m) {
						M = m;
						i_candi = next_i;
						j_candi = next_j;
						ii_candi = ii;
						jj_candi = jj;
					}
				}	

				for (int idx = 2; idx < 4; idx++) {
					if (blocked[idx])
						continue;
					int next_ii = ii + dx[idx];
					int next_jj = jj + dy[idx];
					
					// cout << "for loop " << i << " " << j << " " << next_ii << " " << next_jj << endl;
					
					if (next_ii < 0 || next_ii >= N || next_jj < 0 || next_jj >= N)
						continue;	
					
					// cout << "min_query " << min_query(i, j, next_ii, next_jj)  << " " <<  matrix[r][c] << endl;
					
					if (min_query(i, j, next_ii, next_jj) != matrix[r][c]) {
						blocked[idx] = true;
						continue;
					}
					
					int m = max_query(i, j, next_ii, next_jj);
					if (M > m) {
						M = m;
						i_candi = i;
						j_candi = j;
						ii_candi = next_ii;
						jj_candi = next_jj;
					}
				}	
				
				if (M == N * N + 1) {
					// cout << "break" << endl;
					break;
				}
				
				i = i_candi;
				j = j_candi;
				ii = ii_candi;
				jj = jj_candi;

				int sz = (ii - i + 1) * (jj - j + 1);
				// cout << "sz, M-matrix[r][c]+1 M " << sz << " " << M - matrix[r][c] + 1 << " " << M << endl;
				// cout << "i j ii jj " << i << " " <<  j << " " << ii << " " << jj << endl;
				if (sz == M - matrix[r][c] + 1) {
					// cout << i << " " << j << " " << ii << " " << jj << endl;
					answer++;
				}
			}
		}
	}
	
	cout << answer << "\n";

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