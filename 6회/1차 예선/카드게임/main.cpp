#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <algorithm>

using namespace std;

int n, k;

vector<int> get_partial_sum(vector<int>& vt){
	vector<int> ret;
	int sum = 0;
	ret.push_back(sum);
	for(int i=1; i <= n; i++)
		ret.push_back(sum = sum + vt[i]);
	return ret;
}

int main(){
	freopen("input.txt", "r", stdin);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);  
	cout.tie(NULL);
	
	int T;
	cin >> T;
	
	for(int t = 1; t <= T; t++){
		// inputs
		cout << "Case #" << t << "\n";
		cin >> n >> k;
		vector<int> X = vector<int>(n+1);
		vector<int> Y = vector<int>(n+1);
		for(int i = 1; i <= n; i++)
			cin >> X[i];
		for(int i = 1; i <= n; i++)
			cin >> Y[i];
		
		// outputs
		vector<vector<bool>> status = vector<vector<bool>>(n+1, vector<bool>(n+1, 0));
		status[0][0] = true;
		
		vector<int> partial_sum_X = get_partial_sum(X);
		vector<int> partial_sum_Y = get_partial_sum(Y);
		vector<int> max_lose_idx_row = vector<int>(n+1, -1);
		vector<int> max_lose_idx_column = vector<int>(n+1, -1);
		
		for(int i = 0; i <= n; i++)
			for(int j = 0; j <= n; j++){
				if(i == 0 && j == 0)
					continue;
				if(max_lose_idx_row[i] != -1 && partial_sum_X[j] - partial_sum_X[max_lose_idx_row[i]] <= k)
					status[i][j] = true;
				if(max_lose_idx_column[j] != -1 && partial_sum_Y[i] - partial_sum_Y[max_lose_idx_column[j]] <= k)
					status[i][j] = true;
				if(!status[i][j]){
					max_lose_idx_row[i] = j;
					max_lose_idx_column[j] = i;
				}
			}
				
		int cnt[2] = {0, 0};
		
		for(int i = 0; i <= n; i++)
			for(int j = 0; j <= n; j++){
				cnt[status[i][j]]++;
			}
		
		cout << cnt[1] << " " << cnt[0] << "\n";
	}
	
	return 0;
}
